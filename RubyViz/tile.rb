class Tile
  RESOURCE_COLORS = [
    'red',      # Food
    'orange',   # Linemate
    'yellow',   # Deraumère
    'green',    # Sibur
    '#00FFFF',     # Mendiane
    'blue',     # Phiras
    'purple'    # Thystame
  ]

  attr_reader :position
  attr_accessor :resources

  def initialize(x, y)
    @position = Point.new(x, y)
    @resources = Array.new(7, 0) # 7 resource types
  end

  def set_resources(resources)
    @resources = resources
  end

  def draw(draw_x, draw_y, tile_size, show_grid, is_selected, z = 3)
    size = tile_size - (if show_grid then 1 else 0 end)

    # Draw base tile background
    Square.new(
      x: draw_x, y: draw_y,
      size: size,
      color: is_selected ? '#0240f2' : '#424242',
      z: z
    )

    # Draw resources
    @resources.each_with_index do |count, index|
      next if count.zero?

      color = RESOURCE_COLORS[index]
      size = (tile_size / 6.0).clamp(3, 10)  # Ensure a reasonable dot size
      padding = (tile_size - (3 * size)) / 4

      count.times do |i|
        row = i / 3
        col = i % 3
        Square.new(
          x: draw_x + (col * (size + padding)) + padding,
          y: draw_y + (row * (size + padding)) + padding,
          size: size,
          color: color,
          z: z + 1
        )
      end
    end
  end

  def x
    @position.x
  end

  def y
    @position.y
  end

  def to_s
    "Tile [#{@position.x}, #{@position.y}] -> Resources: #{@resources.join(', ')}"
  end
end
