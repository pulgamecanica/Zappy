//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
}

#include "Zappy.inc"

#include "GameEngine.hpp"

namespace Zappy {
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  GameEngine::GameEngine(int default_time, std::string toml_file, std::string default_lang,
    int players_port, int spectators_port, Point p, int num_players, int timeout):
      Server(this, toml_file, default_lang, players_port, spectators_port, timeout),
      current_frame_(0), map_size_(p), t_(default_time) {
    (void)num_players;
    set_game_delay();
    updated_at_ms_ = created_at_ms_;
  }

  GameEngine::~GameEngine() {
    if (DEBUG)
      std::cout << "GameEngine destroyed | Total: [" << current_frame_ << "]frames" << std::endl;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  const Point & GameEngine::get_map_size() const {
    return (map_size_);
  }

  bool  GameEngine::is_team_valid(const std::string & team) const {
    // for (std::vector<std::string>::iterator i = .begin(); i != .end(); ++i)
    // {
      
    // }
    // Missing teams logic
    return !team.empty();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////// PUBLIC METHODS ///////////////////////////////////////////
  unsigned int GameEngine::frame() {return current_frame_;}

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