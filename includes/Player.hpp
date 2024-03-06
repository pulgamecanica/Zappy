//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>

namespace Zappy {
	class Player {
		public:
			Player(int fd);
			Player(const Player&) = default;
			~Player();
			Player&	operator= (const Player&) = delete; // const for safety... not super nesessary
			void handle_io();
		private:
			const int fd_;
	};

	std::ostream&	operator<<(std::ostream&, const Player&);
}
#endif
