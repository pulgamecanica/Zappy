//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __GAMEENGINE_HPP__
# define __GAMEENGINE_HPP__

#include <iostream>

#include "Server.hpp"

namespace Zappy {
  class GameEngine: public virtual Server {
    public:
      GameEngine(int default_time = 100, std::string toml_file = "conf.toml", std::string default_lang = "en", int players_port = 4242, int spectators_port = 2121);
      GameEngine(const GameEngine&) = delete;
      ~GameEngine();
      GameEngine& operator=(const GameEngine&) = delete; // const for safety... not super nesessary
      void          start(int * sig);
      unsigned int  frame();
    private:
      // CLASS FUNCTION MEMBERS
      void          set_game_delay();
      void          update();
      void          update_time();
      bool          is_time_to_update();
      // CLASS PARAMS MEMBERS
      int           * sig_;

      /**
       * t_ <=> fps | it's the time basically;
       * let t = 100.
       * 1 / t = frame_len <==> 1 / 100 = 0.01 seconds
       * Each frame should be 0.01 seconds, or 0.01 * (1000ms)  miliseconds
       * Therefore each frame is 10 miliseconds, and so frame_delay is this defined
       **/
      int             t_; // t = fps, it's the time basically 
      int             frame_delay_; // in miliseconds
      unsigned int    current_frame_; // Just metadata
      ssize_t         updated_at_ms_;
  };

  std::ostream& operator<<(std::ostream&, const GameEngine&);
}
#endif

