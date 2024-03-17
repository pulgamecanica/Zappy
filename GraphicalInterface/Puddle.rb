class Puddle
  attr_reader :pos, :animation

  def initialize(x, y)
    @pos = Point.new(x, y)
    @animation = Sprite.new(
      'images/waves.png',
      x: @pos.x,
      y: @pos.y,
      clip_width: 320,
      time: 200,
      loop: true
    )
    @animation.play
  end

  def draw(top_left, tile_size)
    map_pos = @pos.get_map_point(top_left, tile_size)
    @animation.width = tile_size
    @animation.height = tile_size
    @animation.draw(x: map_pos.x, y: map_pos.y)
  end
end
