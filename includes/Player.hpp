//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>

#include "Client.hpp"

namespace Zappy {
	class Player: public virtual Client {
		public:
			Player(int fd);
			Player(const Player&) = default;
			~Player();
			Player&	operator= (const Player&) = delete; // const for safety... not super nesessary
		private:
			// const int 			fd_;
			// struct timeval	created_at_;
			// Team
			// ETC...
			// Inventory
			// Objects
	};

	std::ostream&	operator<<(std::ostream&, const Player&);
}
#endif
