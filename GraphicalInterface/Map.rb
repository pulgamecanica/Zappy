class Map
  attr_reader :data, :width, :height

  def initialize(width, height)
    puts "Map: [#{width}, #{height}]"
    @data = [
      Puddle.new(2, 2),
      Puddle.new(2, 10),
      Puddle.new(4, 6)
    ]
    @width = width
    @height = height
  end

  def add_player(player)
    data.push(player)
  end
end