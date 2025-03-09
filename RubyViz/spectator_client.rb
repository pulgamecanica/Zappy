require 'ruby2d'
require_relative 'socket'
require_relative 'point'
require_relative 'tile'
require_relative 'player'
require_relative 'command_processor'

# Window Configuration
WIDTH = 1040
HEIGHT = 680
TIMELINE_HEIGHT = 40  # Height of the timeline slider
set width: WIDTH, height: HEIGHT + TIMELINE_HEIGHT
set background: "navy"
set fps_cap: 32

class SpectatorClient
  attr_accessor :tile_size, :show_grid, :selected_tile, :selected_player, :time_index, :paused, :top_left

  MIN_TILE_SIZE = 16
  MAX_TILE_SIZE = 128

  def initialize
    @socket = Socket.new('localhost', 2121)
    @processor = CommandProcessor.new
    @top_left = Point.new(0, 0)
    @selected_tile = nil
    @selected_player = nil
    @tile_size = 64
    @show_grid = true
    @time_index = -1  # -1 = "Live Mode"
    @paused = false
    @dragging_timeline = false
    @game_state = nil
    fetch_initial_data
  end

  def visible?(x, y)
    screen_x = x * @tile_size
    screen_y = y * @tile_size
    screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT
  end

  def fetch_initial_data
    response = @socket.get_full_response
    response.split("\n").each do |command|
      @processor.process(command)
    end
  end

  def update_game_state
    response = @socket.get_latest_updates
    response.split("\n").each do |command|
      @processor.process(command)
    end
  end

  def draw
    @game_state = @processor.get_state_at(@time_index)
    draw_tiles(@game_state[:map])
    draw_players(@game_state[:players])
    draw_event_log
    draw_timeline
    draw_pause_indicator if @paused
  end

  def draw_tiles(map)
    map.tiles.each do |tile|
      # Adjust positions based on top_left
      draw_x = (tile.x - @top_left.x) * @tile_size
      draw_y = (tile.y - @top_left.y) * @tile_size
      next unless draw_x.between?(0, WIDTH) && draw_y.between?(0, HEIGHT)

      tile.draw(draw_x, draw_y, @tile_size, @show_grid, @selected_tile == tile.position)
    end
  end


  def draw_players(players)
    players.each_value do |player|
      draw_x = (player.x - @top_left.x) * @tile_size
      draw_y = (player.y - @top_left.y) * @tile_size
      next unless draw_x.between?(0, WIDTH) && draw_y.between?(0, HEIGHT)

      color = player.team_color
      Square.new(
        x: draw_x, y: draw_y,
        size: @tile_size * 0.8,
        color: color,
        z: 3
      )

      if player == @selected_player
        Square.new(
          x: draw_x, y: draw_y,
          size: @tile_size * 0.9,
          color: 'white',
          z: 4
        )
      end
    end
  end

  
  def draw_event_log
    y_offset = 10
    events_to_display = @processor.get_events_at(@time_index).last(5)

    events_to_display.each do |event|
      Text.new(
        event,
        x: 10,
        y: y_offset,
        z: 99,
        size: 14,
        color: 'white'
      )
      y_offset += 20
    end
  end

  def draw_timeline
    Rectangle.new(x: 0, y: HEIGHT, width: WIDTH, height: TIMELINE_HEIGHT, color: 'gray', z: 98)

    timeline_position = (WIDTH.to_f * (@time_index + 1) / (@processor.state_count.nonzero? || 1)).clamp(0, WIDTH)
    Rectangle.new(x: timeline_position - 5, y: HEIGHT, width: 10, height: TIMELINE_HEIGHT, color: 'red', z: 99)

    Text.new(@time_index == -1 ? "Live" : "Time: #{@time_index}", x: WIDTH / 2 - 50, y: HEIGHT + 10, size: 16, color: 'white', z: 99)
  end

  def draw_pause_indicator
    Text.new("PAUSED", x: WIDTH / 2 - 50, y: HEIGHT / 2 - 20, size: 30, color: 'red', z: 100)
  end

  def move(direction)
    map = @game_state[:map]
    max_x_offset = (WIDTH / @tile_size) / 2
    max_y_offset = (HEIGHT / @tile_size) / 2

    case direction
    when 'down'
      @top_left.y -= 1 if @top_left.y > -max_y_offset
    when 'up'
      @top_left.y += 1 if @top_left.y < (map.height - (HEIGHT / @tile_size)) + max_y_offset
    when 'right'
      @top_left.x -= 1 if @top_left.x > -max_x_offset
    when 'left'
      @top_left.x += 1 if @top_left.x < (map.width - (WIDTH / @tile_size)) + max_x_offset
    end
  end

  def zoom(direction)
    old_tile_size = @tile_size

    case direction
    when 'in'
      @tile_size += 2 if @tile_size < MAX_TILE_SIZE
    when 'out'
      @tile_size -= 2 if @tile_size > MIN_TILE_SIZE
    end

    adjust_top_left_on_zoom(old_tile_size)
  end

  def adjust_top_left_on_zoom(old_tile_size)
    # Compute zoom scaling factor
    scale_factor = @tile_size.to_f / old_tile_size

    # Adjust the top left to maintain correct position
    @top_left.x = (@top_left.x * scale_factor).round
    @top_left.y = (@top_left.y * scale_factor).round

    # Ensure the top-left corner respects the movement limits
    max_x_offset = (WIDTH / @tile_size) / 2
    max_y_offset = (HEIGHT / @tile_size) / 2

    map = @game_state[:map]
    @top_left.x = @top_left.x.clamp(-max_x_offset, map.width - (WIDTH / @tile_size) + max_x_offset)
    @top_left.y = @top_left.y.clamp(-max_y_offset, map.height - (HEIGHT / @tile_size) + max_y_offset)
  end

  def select_tile(x, y)
    @selected_tile = Point.new(x, y)
  end

  def rewind
    increment = if paused then 1 else 2 end
    @time_index = [@time_index - increment, -1].max
  end

  def fast_forward
    @time_index = [@time_index + 1, @processor.state_count - 1].min
  end

  def handle_timeline_drag(x)
    @time_index = ((x.to_f / WIDTH) * @processor.state_count).to_i.clamp(-1, @processor.state_count - 1)
  end

  def toggle_pause
    @paused = !@paused
  end
end

viz = SpectatorClient.new

update do 
  clear
  viz.draw
  viz.fast_forward if not viz.paused  # Auto-advance in live mode
  viz.update_game_state
end

on :key_held do |event|
  viz.move(event.key) if ['up', 'down', 'left', 'right'].include?(event.key)
  viz.zoom('in') if event.key == 'keypad +'
  viz.zoom('out') if event.key == 'keypad -'
  case event.key
  when 'r' then viz.rewind
  when 'f' then viz.fast_forward
  end
end

on :mouse_down do |event|
  if event.y >= HEIGHT  # If clicking on the timeline
    viz.handle_timeline_drag(event.x)
    viz.instance_variable_set(:@dragging_timeline, true)
  else
    # Convert screen coordinates to map coordinates considering the top-left offset
    x = (event.x / viz.tile_size).to_i + viz.top_left.x
    y = (event.y / viz.tile_size).to_i + viz.top_left.y
    viz.select_tile(x, y)
  end
end

on :mouse_up do |event|
  viz.instance_variable_set(:@dragging_timeline, false)
end

on :mouse_move do |event|
  viz.handle_timeline_drag(event.x) if viz.instance_variable_get(:@dragging_timeline)
end

on :key_down do |event|
  case event.key
  when 'g' then viz.show_grid = !viz.show_grid
  when 'r' then viz.rewind
  when 'f' then viz.fast_forward
  when 'space' then viz.toggle_pause
  when 'return' then viz.time_index = -1 # Go to live mode
  end
end

show
