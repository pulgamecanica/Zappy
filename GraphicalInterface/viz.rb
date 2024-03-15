require 'ruby2d'

WIDTH = 640
HEIGHT = 480
TILE_SIZE = 16

# Set the window size
set width: WIDTH, height: HEIGHT, background: "navy"

Line.new(
  x1: 0, y1: 1,
  x2: WIDTH, y2: 1,
  width: 1,
  color: 'silver',
  z: 9
)

Line.new(
  x1: 1, y1: 0,
  x2: 1, y2: HEIGHT,
  width: 1,
  color: 'silver',
  z: 9
)

# Draw Vertical Lines
x_gaps = WIDTH / TILE_SIZE
(0..x_gaps).each do |x|
  Line.new(
    x1: x * TILE_SIZE, y1: 0,
    x2: x * TILE_SIZE, y2: HEIGHT,
    width: 1,
    color: 'silver',
    z: 9
  )
end
# Draw Horizontal Lines
y_gaps = HEIGHT / TILE_SIZE
(0..y_gaps).each do |y|
  Line.new(
    x1: 0, y1: y * TILE_SIZE,
    x2: WIDTH, y2: y * TILE_SIZE,
    width: 1,
    color: 'silver',
    z: 9
  )
end

wave = Sprite.new(
  'images/waves.png',
  width: 64,
  height: 64,
  x: 16,
  y: 16,
  clip_width: 320,
  time: 300,
  loop: true
)

wave.play

wave = Sprite.new(
  'images/waves.png',
  width: 64,
  height: 64,
  x: 116,
  y: 316,
  clip_width: 320,
  time: 300,
  loop: true
)

wave.play


hero = Sprite.new(
  'images/hero.png',
  width: 16,
  height: 16,
  clip_width: 78,
  time: 250,
  animations: {
    walk: 1..2,
    climb: 3..4,
    cheer: 5..6
  }
)

on :key_held do |event|
  case event.key
    when 'left'
      hero.x -= TILE_SIZE
      hero.x = (hero.x < 0 ? (x_gaps - 1) * TILE_SIZE : hero.x)
      hero.play animation: :walk, loop: true, flip: :horizontal
    when 'right'
      hero.x += TILE_SIZE
      hero.x %= WIDTH
      hero.play animation: :walk, loop: true
    when 'up'
      hero.y -= TILE_SIZE
      hero.y = (hero.y < 0 ? (y_gaps - 1) * TILE_SIZE : hero.y)
      hero.play animation: :climb, loop: true
    when 'down'
      hero.y += TILE_SIZE
      hero.y %= HEIGHT
      hero.play animation: :climb, loop: true, flip: :vertical
    when 'c'
      hero.play animation: :cheer
  end
end

hero.play animation: :cheer

# Show the window
show