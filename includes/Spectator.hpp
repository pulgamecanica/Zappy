//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SPECTATOR_HPP__
# define __SPECTATOR_HPP__

#include <iostream>
#include <string>

#include "Client.hpp"

namespace Zappy {

	class Spectator: public Client {
		public:
			Spectator(int fd, const std::string initial_msg);
			Spectator(const Spectator&) = default;
			~Spectator();
			Spectator&	operator= (const Spectator&) = default; // const for safety... not super nesessary
	};

	std::ostream&	operator<<(std::ostream&, const Spectator&);
}

#endif

