//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "GameEngine.hpp"

namespace Zappy {
  GameEngine::GameEngine(int default_time, std::string toml_file, std::string default_lang, int players_port, int spectators_port, Point p):
    Server(this, toml_file, default_lang, players_port, spectators_port), t_(default_time), current_frame_(0), map_size_(p) {
    set_game_delay();
    updated_at_ms_ = created_at_ms_;
  }

  void GameEngine::set_game_delay() {
    /**
     * Probably should limit t_ to be a maximum amount of 1000
     * Else it can be problematic, also 1000 would be a frame of 1ms
     * Which means 1000 iterations in 1 second, which seams so many
     **/
    frame_delay_ = 1000 / t_;
  }

  const Point & GameEngine::get_map_size() const {
    return (map_size_);
  }

  void GameEngine::start(int * sig) {
    std::cout << get_config().get("welcome_to_server") << std::endl;
    write(1, "$> ", 3);
    while (*sig && check_health(ServerHealth::Running))
      update();
  }

  unsigned int GameEngine::frame() {return current_frame_;}

  inline bool GameEngine::is_time_to_update() {
    return (gettimeofday_ms() - updated_at_ms_ >= frame_delay_);
  }

  inline void GameEngine::update_time() {
    updated_at_ms_ += frame_delay_;
  }

  // The game engine is running an underlying Server, who is also in charge of all managing the fds
  void GameEngine::update() {
    Server::update();
    if (is_time_to_update()) {
      // std::cout << "1/t:[" << frame() << "]" << std::endl;
      current_frame_++;
      update_time();
    }
  }

  GameEngine::~GameEngine() {
    if (DEBUG)
      std::cout << "GameEngine destroyed | Total: [" << current_frame_ << "]frames" << std::endl;
  }

  std::ostream& operator<<(std::ostream& s, const GameEngine& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}