require 'ruby2d'
require_relative 'Socket.rb'
require_relative 'Point.rb'
require_relative 'Puddle.rb'
require_relative 'Map.rb'
require_relative 'Player.rb'

# Set the window size
set width: 640, height: 480
set background: "navy"
set fps_cap: 32

class Vizualisator
  attr_accessor :top_left, :show_grid, :tile_size

  def initialize
    @top_left = Point.new(0, 0)
    @show_grid = true
    @tile_size = 64
    @socket = Socket.new

    # Get Map Size
    response = @socket.get("msz")
    puts "Response from server: #{response}"
    _, width, height = response.split
    @map = Map.new(width.to_i, height.to_i)

    @map.add_player(Player.new(5, 5))
  end

  def draw_grid(z = 9)
    # Calculate the width and height based on the top left corner
    map_dimensions = Point.new(@map.width, @map.height).get_map_point(@top_left, @tile_size)
    width = map_dimensions.x
    height = map_dimensions.y
    # Draw Vertical Lines
    x_gaps = width / @tile_size
    (@top_left.x..x_gaps).each do |x|
      Line.new(
        x1: x * @tile_size, y1: @top_left.y * @tile_size,
        x2: x * @tile_size, y2: height,
        width: 1, color: 'silver', z: z
      )
    end
    # Draw Horizontal Lines
    y_gaps = height / @tile_size
    (@top_left.y..y_gaps).each do |y|
      Line.new(
        x1: @top_left.x * @tile_size, y1: y * @tile_size,
        x2: width, y2: y * @tile_size,
        width: 1, color: 'silver', z: z
      )
    end
  end

  def draw
    draw_grid if @show_grid
    @map.data.each do |d|
      d.draw(@top_left, @tile_size)
    end
  end

  def move_top_left(direction)
    case direction
    when 'up' then @top_left = Point.new(@top_left.x, @top_left.y - 1)
    when 'down' then @top_left = Point.new(@top_left.x, @top_left.y + 1)
    when 'left' then @top_left = Point.new(@top_left.x - 1, @top_left.y)
    when 'right' then @top_left = Point.new(@top_left.x + 1, @top_left.y)
    end
  end
end


trantor = Vizualisator.new

update do 
  clear
  trantor.draw
end

on :key_held do |event|
  if ['up', 'down', 'left', 'right'].include?(event.key)
    trantor.move_top_left(event.key)
  end
  if ['keypad +', 'keypad -'].include?(event.key)
    case event.key
    when 'keypad +' then trantor.tile_size += 1 unless trantor.tile_size >= 256 or trantor.tile_size >= 256 / 4
    when 'keypad -' then trantor.tile_size -= 1 unless trantor.tile_size <= 8
    end 
  end
end

on :key_down do |event|
  if event.key == 'g'
    trantor.show_grid = !trantor.show_grid
  end
end

# Show the window
show

