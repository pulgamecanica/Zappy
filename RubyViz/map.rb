require_relative 'tile'

class Map
  attr_reader :width, :height, :teams

  def initialize(width, height)
    @width = width
    @height = height
    reset
    @teams = []
  end

  def resize(width, height)
    @width, @height = width, height
    reset  # Ensure new tiles are created
  end

  def reset
    @tiles = Array.new(@height) { |y| Array.new(@width) { |x| Tile.new(x, y) } }
  end

  def tiles
    @tiles.flatten
  end

  def get_tile(x, y)
    return nil if x < 0 || y < 0 || x >= @width || y >= @height
    @tiles[y][x]  # **Fixed incorrect indexing**
  end

  def add_team(team)
    @teams << team unless @teams.include?(team)
  end

  def tile_at(x, y)
    get_tile(x, y)
  end
end
