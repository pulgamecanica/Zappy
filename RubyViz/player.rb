class Player
  attr_reader :id, :team
  attr_accessor :x, :y, :orientation, :level, :inventory

  ORIENTATIONS = {
    "North" => :up,
    "East" => :right,
    "South" => :down,
    "West" => :left
  }

  TEAM_COLORS = {
    "Team Rocket" => 'red',
    "Blue Warriors" => 'blue',
    "Green Guardians" => 'green',
    "Yellow Hawks" => 'yellow'
  }

  def initialize(id, x, y, orientation, level, team)
    @id = id
    @x = x
    @y = y
    @orientation = ORIENTATIONS[orientation] || :up
    @level = level
    @team = team
    @inventory = Array.new(7, 0) # Default empty inventory
  end

  def move_to(x, y, orientation)
    @x = x
    @y = y
    @orientation = ORIENTATIONS[orientation] || :up
  end

  def update_inventory(resources)
    @inventory = resources
  end

  def team_color
    TEAM_COLORS[@team] || 'white'
  end

  def to_s
    "Player #{@id} [#{@x}, #{@y}] (#{@orientation}) - Level: #{@level}, Team: #{@team}"
  end
end
