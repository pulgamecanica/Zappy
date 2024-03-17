class Player
  attr_reader :pos

  def initialize(x, y)
    @pos = Point.new(x, y)
    @animation = Sprite.new(
      'images/hero.png',
      x: @pos.x,
      y: @pos.y,
      clip_width: 78,
      time: 300,
      animations: {
        walk: 1..2,
        climb: 3..4,
        cheer: 5..6
      }
    )
    @animation.play
  end

  def change_direction(direction)
    case direction
    when 'up' then @animation.play animation: :climb, loop: true
    when 'down' then @animation.play animation: :climb, loop: true, flip: :vertical
    when 'right' then @animation.play animation: :walk, loop: true
    when 'left' then @animation.play animation: :walk, loop: true, flip: :horizontal
    end
  end

  def draw(top_left, tile_size)
    map_pos = @pos.get_map_point(top_left, tile_size)
    @animation.play animation: :cheer, loop: true
    @animation.width = tile_size
    @animation.height = tile_size
    @animation.draw(x: map_pos.x, y: map_pos.y)
  end
end
