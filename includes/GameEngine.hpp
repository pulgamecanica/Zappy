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
			GameEngine();
			GameEngine(const GameEngine&) = delete;
			~GameEngine();
			GameEngine&	operator=(const GameEngine&) = delete; // const for safety... not super nesessary
			void				start(int * sig);
		private:
			// CLASS FUNCTION MEMBERS
			unsigned int	frame();
			void 					update();
			void 					update_time();
			bool 					is_time_to_update();
			// CLASS PARAMS MEMBERS
			int 					* sig_;

			/**
			 * t_ <=> fps | it's the time basically;
			 * let t = 100.
			 * 1 / t = frame_len <==> 1 / 100 = 0.01 seconds
			 * Each frame should be 0.01 seconds, or 0.01 * (1000ms)  miliseconds
			 * Therefore each frame is 10 miliseconds, and so frame_delay is this defined
			 **/
			int							t_; // t = fps, it's the time basically 
			int 						frame_delay_; // in miliseconds
			unsigned int		current_frame_; // Just metadata
			ssize_t					updated_at_ms_;
	};

	std::ostream&	operator<<(std::ostream&, const GameEngine&);
}
#endif

