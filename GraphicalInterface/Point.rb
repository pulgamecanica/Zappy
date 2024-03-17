class Point
  attr_accessor :x,:y

  def initialize(x, y)
    @x = x
    @y = y
  end

  def get_map_point(top_left, tile_size)
    Point.new((top_left.x + @x) * tile_size, (top_left.y + @y) * tile_size)
  end
end