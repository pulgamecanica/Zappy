//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

extern "C" {
	#include <sys/time.h>
}

#include <iostream>

namespace Zappy {
	class Player {
		public:
			Player(int fd);
			Player(const Player&) = default;
			~Player();
			Player&	operator= (const Player&) = delete; // const for safety... not super nesessary
			ssize_t uptime() const;
		private:
			const int 			fd_;
			struct timeval	created_at_;
			// Team
			// ETC...
			// Inventory
			// Objects
	};

	std::ostream&	operator<<(std::ostream&, const Player&);
}
#endif
