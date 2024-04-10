//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
}

#include "Zappy.inc"
#include "GameEngine.hpp"
#include "Team.hpp"
#include "Client.hpp"
#include "Player.hpp"

namespace Zappy {
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  GameEngine::GameEngine(std::vector<std::string> teams, int default_time, std::string toml_file, std::string default_lang,
    int players_port, int spectators_port, Point map_size, int num_players, int timeout):
      Server(this, toml_file, default_lang, players_port, spectators_port, timeout),
      Map(map_size), current_frame_(0), t_(default_time) {
    set_game_delay();
    updated_at_ms_ = created_at_ms_;
    // Setup Teams
    for (std::vector<std::string>::iterator i = teams.begin(); i != teams.end(); ++i) {
      if (!teams_.count(*i))
        teams_.insert(std::pair<std::string, Team>(*i, Team(*i, num_players)));
    }
    // Get all the players pointers for each team
    for (std::map<std::string, Team>::const_iterator i = teams_.begin(); i != teams_.end(); ++i) {
      const std::map<int, const Player*> players_map = i->second.get_players_map();
      players_.insert(players_map.begin(), players_map.end());
    }
    if (DEBUG)
      std::cout << BLUE << "Loaded " << GREEN << teams_.size() << ENDC << " Teams & " << GREEN << players_.size() << ENDC << " Players" << std::endl;
  }

  GameEngine::~GameEngine() {
    players_.clear();
    teams_.clear();
    if (DEBUG)
      std::cout << "GameEngine destroyed | Total: [" << current_frame_ << "]frames" << std::endl;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  unsigned int GameEngine::frame() const {
    return current_frame_;
  }

  Point GameEngine::get_map_size() const {
    return (Map::get_map_size());
  }

  const std::vector<const Player *> GameEngine::get_players() const {
    std::vector<const Player *> vec;
    for (std::map<int, const Player *>::const_iterator i = players_.begin();
      i != players_.end(); ++i) {
      vec.push_back(i->second);
    }
    return vec;
  }

  const std::vector<const Team *> GameEngine::get_teams() const {
    std::vector<const Team *> vec;
    for (std::map<std::string, Team>::const_iterator i = teams_.begin(); i != teams_.end(); ++i) {
      vec.push_back(&(i->second));
    }
    return vec;
  }

  int GameEngine::get_time_unit() const {
    return (t_);
  }

  bool  GameEngine::is_team_valid(const std::string & team) const {
    return (teams_.count(team));
  }

  bool  GameEngine::join_team(const std::string & team, Client * client) {
    if (!is_team_valid(team))
      return false;
    return teams_.at(team).add_client(client);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////// PUBLIC METHODS ///////////////////////////////////////////
  std::vector<Player*> GameEngine::get_players_at(const Point & p) {
    std::vector<Player*> vec;
    (void)p;
    // for (std::map<std::string, Team>::iterator i = teams_.begin(); i != teams_.end(); ++i) {
      // for (std::vector<Player>::iterator j = i->second.players_.begin(); j != i->second.players_.end(); ++j) {
        // if (p == j->get_position())
          // vec.push_back(&(*j));
      // }
    // }
    return vec;
  }

  std::vector<Player*> GameEngine::get_players_at(int index) {
    return (get_players_at(index_to_point(index)));
  }

  const Player* GameEngine::get_player_by_id(int id) {
    return players_[id];
  }

  void GameEngine::set_time_unit(int t) {
    if (t_ <= 0)
      throw std::runtime_error("Time unit should be > 0");
    t_ = t;
    set_game_delay();
    if (DEBUG)
      std::cout << YELLOW << "[Server]\t" << GREEN << "updated" << ENDC ":" << BLUE << "time unit"
        << ENDC << "[" << BLUE << t_ << ENDC << "]" << std::endl;
  }

  void GameEngine::start(int * sig) {
    std::cout << get_config().get("welcome_to_server") << std::endl;
    write(1, "$> ", 3);
    while (*sig && check_health(Server::ServerHealth::Running))
      update();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////// PRIVATE METHODS ///////////////////////////////////////////
  inline bool GameEngine::is_time_to_update() {
    return (gettimeofday_ms() - updated_at_ms_ >= frame_delay_);
  }

  void GameEngine::set_game_delay() {
    /**
     * Probably should limit t_ to be a maximum amount of 1000
     * Else it can be problematic, also 1000 would be a frame of 1ms
     * Which means 1000 iterations in 1 second, which seams so many
     **/
    frame_delay_ = 1000 / t_;
  }

  /* MAIN UPDATE FUNCTION */
  void GameEngine::update() {
    Server::update();
    if (is_time_to_update()) {
      // std::cout << "1/t:[" << frame() << "]" << std::endl;
      current_frame_++;
      update_time();
    }
  }

  inline void GameEngine::update_time() {
    updated_at_ms_ += frame_delay_;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const GameEngine& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}