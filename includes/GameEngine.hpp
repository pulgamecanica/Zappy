//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __GAMEENGINE_HPP__
# define __GAMEENGINE_HPP__

#include <iostream>

#include "Server.hpp"
#include "Geometry/Point.hpp"

/**
 * Note: GameEngine::t_
 * 
 *    t_ <=> fps | it's the time basically;
 *    let t = 100.
 *    1 / t = frame_len <==> 1 / 100 = 0.01 seconds
 *    Each frame should be 0.01 seconds, or 0.01 * (1000ms)  miliseconds
 *    Therefore each frame is 10 miliseconds, and so frame_delay is this defined
 **/
namespace Zappy {
  class GameEngine: public virtual Server {
    public:
      // CONSTRUCTORS & DESTRUCTORS //
      GameEngine(int default_time = 100, std::string toml_file = "conf.toml",
        std::string default_lang = "en", int players_port = 4242, int spectators_port = 2121,
        Point p = {10, 10}, int num_players = 1);
      GameEngine(const GameEngine&) = delete;
      GameEngine& operator=(const GameEngine&) = delete;
      ~GameEngine();
      // CONST PUBLIC METHODS //
      const Point   &get_map_size() const;
      bool          is_team_valid(const std::string & team) const;
      // PUBLIC METHODS //
      unsigned int  frame();
      void          start(int * sig);
    private:
      // PRIVATE METHODS //
      bool          is_time_to_update();
      void          set_game_delay();
      void          update();
      void          update_time();
      // PRIVATE MEMBERS //
      unsigned int  current_frame_;
      int           frame_delay_; // in miliseconds, based on t_ ; see Note above
      Point         map_size_;
      int           *sig_;
      int           t_; // t = fps, it's the time basically 
      ssize_t       updated_at_ms_;
  };

  std::ostream& operator<<(std::ostream&, const GameEngine&);
}
#endif

