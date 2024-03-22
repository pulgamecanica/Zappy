require 'ruby2d'
require_relative 'Socket.rb'
require_relative 'Point.rb'
require_relative 'Puddle.rb'
require_relative 'Map.rb'
require_relative 'Player.rb'

# Set the window size
WIDTH = 1040
HEIGHT = 680

set width: WIDTH, height: HEIGHT
set background: "navy"
set fps_cap: 32

def max(a, b)
  return (a > b ? a : b)
end

class Vizualisator
  attr_accessor :top_left, :show_grid, :show_ruler, :tile_size
  attr_reader :map

  def initialize
    @top_left = Point.new(0, 0)
    @show_grid = true
    @show_ruler = true
    @tile_size = 64
    @socket = Socket.new('localhost', 2121)

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

  def draw_rulers(z = 10)
    x_separations = WIDTH / @tile_size
    y_separations = HEIGHT / @tile_size
    separation_height = @tile_size / 3
    separation_height = 10 unless separation_height > 10
    mid = @tile_size / 2
    x_start = (@top_left.x * -1)
    y_start = (@top_left.y * -1)
    (0..x_separations).each do |i|
      color = (i % 2 == 0) ? 'gray' : 'silver' 
      Rectangle.new(
        x: i * @tile_size, y: 0,
        width: @tile_size, height: separation_height,
        color: color,
        z: z
      )
      Rectangle.new(
        x: i * @tile_size, y: HEIGHT - separation_height,
        width: @tile_size, height: separation_height,
        color: color,
        z: z
      )
      Text.new(
        (x_start + i).to_s,
        x: (i * @tile_size) + mid, y: separation_height / 4,
        font: 'fonts/Orbitron-VariableFont_wght.ttf',
        style: 'bold',
        size: separation_height / 2,
        color: 'black',
        z: z
      )
      Text.new(
        (x_start + i).to_s,
        x: (i * @tile_size) + mid, y: HEIGHT - separation_height,
        font: 'fonts/Orbitron-VariableFont_wght.ttf',
        style: 'bold',
        size: separation_height / 2,
        color: 'black',
        z: z
      )
    end
    (0..y_separations).each do |i|
      color = (i % 2 == 0) ? 'silver' : 'gray' 
      Rectangle.new(
        x: 0, y: i * @tile_size,
        width: separation_height, height: @tile_size,
        color: color,
        z: z
      )
      Rectangle.new(
        x: WIDTH - separation_height, y: i * @tile_size,
        width: separation_height, height: @tile_size,
        color: color,
        z: z
      )
      Text.new(
        (y_start + i).to_s,
        x: separation_height / 4, y: (i * @tile_size) + mid,
        font: 'fonts/Orbitron-VariableFont_wght.ttf',
        style: 'bold',
        size: separation_height / 2,
        color: 'black',
        z: z
      )
      Text.new(
        (y_start + i).to_s,
        x: WIDTH - (2 * separation_height / 3), y: (i * @tile_size) + mid,
        font: 'fonts/Orbitron-VariableFont_wght.ttf',
        style: 'bold',
        size: separation_height / 2,
        color: 'black',
        z: z
      )
    end
  end

  def draw
    draw_grid if @show_grid
    draw_rulers if @show_ruler
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
    when 'keypad -' then trantor.tile_size -= 1 unless (trantor.tile_size * max(trantor.map.width, trantor.map.height)) < max(WIDTH, HEIGHT)
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

