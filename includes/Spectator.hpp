//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SPECTATOR_HPP__
# define __SPECTATOR_HPP__

#include <iostream>

namespace Zappy {
	class Spectator {
		public:
			Spectator(int fd);
			Spectator(const Spectator&) = default;
			~Spectator();
			Spectator&	operator= (const Spectator&) = delete; // const for safety... not super nesessary
		private:
			const int fd_; 
	};

	std::ostream&	operator<<(std::ostream&, const Spectator&);
}

#endif

