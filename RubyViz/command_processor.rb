require_relative 'map'

class CommandProcessor
  attr_reader :events, :players, :map

  def initialize
    @map = Map.new(20, 20)
    @players = {}
    @events = []
    @state_history = []
  end

  def process(command)
    args = command.strip.split
    return if args.empty?

    case args[0]
    when "msz" then handle_msz(args)
    when "bct" then handle_bct(args)
    when "mct" then handle_mct(args)
    when "tna" then handle_tna(args)
    when "pnw" then handle_pnw(args)
    when "ppo" then handle_ppo(args)
    when "plv" then handle_plv(args)
    when "pin" then handle_pin(args)
    end
    save_state
  end

  def save_state
    @state_history << {
      map: Marshal.dump(@map),
      players: Marshal.dump(@players),
      events: @events.dup
    }
  end

  def get_state_at(index)
    return { map: @map, players: @players } if index == -1 || @state_history.empty?

    state = @state_history[index.clamp(0, @state_history.length - 1)]
    {
      map: Marshal.load(state[:map]),
      players: Marshal.load(state[:players])
    }
  end

  def get_events_at(index)
    return @events if index == -1 || @state_history.empty?

    state = @state_history[index.clamp(0, @state_history.length - 1)]
    state[:events]
  end

  def state_count
    @state_history.length
  end

  private

  # 📌 Handles map size response: `msz X Y`
  def handle_msz(args)
    _, width, height = args
    @map.resize(width.to_i, height.to_i)
    log_event("Map size set to #{width}x#{height}")
  end

  # 📌 Handles tile resource response: `bct X Y q q q q q q q`
  def handle_bct(args)
    x, y, *resources = args[1..]
    tile = @map.get_tile(x.to_i, y.to_i)
    tile.set_resources(resources.map(&:to_i))
    log_event("Updated tile [#{x}, #{y}] with resources #{resources.join(', ')}")
  end

  # 📌 Handles multiple tiles: `mct` returns `bct` for each tile
  def handle_mct(args)
    log_event("Map content received")
  end

  # 📌 Handles team names: `tna N`
  def handle_tna(args)
    team_name = args[1]
    @map.add_team(team_name)
    log_event("Team added: #{team_name}")
  end

  # 📌 Handles player join: `pnw #n X Y O L N`
  def handle_pnw(args)
    id, x, y, orientation, level, team = args[1..]
    @players[id.to_i] = Player.new(id.to_i, x.to_i, y.to_i, orientation.to_sym, level.to_i, team)
    log_event("Player #{id} joined at (#{x},#{y}) in team #{team}")
  end

  # 📌 Handles player position update: `ppo #n X Y O`
  def handle_ppo(args)
    id, x, y, orientation = args[1..]
    player = @players[id.to_i]
    return unless player

    player.move_to(x.to_i, y.to_i, orientation.to_sym)
    log_event("Player #{id} moved to (#{x},#{y}) facing #{orientation}")
  end

  # 📌 Handles player level update: `plv #n L`
  def handle_plv(args)
    id, level = args[1..]
    player = @players[id.to_i]
    return unless player

    player.level = level.to_i
    log_event("Player #{id} is now level #{level}")
  end

  # 📌 Handles player inventory update: `pin #n X Y q q q q q q q`
  def handle_pin(args)
    id, x, y, *resources = args[1..]
    player = @players[id.to_i]
    return unless player

    player.update_inventory(resources.map(&:to_i))
    log_event("Player #{id} inventory updated: #{resources.join(', ')}")
  end

  def log_event(message)
    @events << message
    puts message # Console debug (can be sent to UI later)
  end
end
