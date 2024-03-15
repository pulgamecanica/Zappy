//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Spectator.hpp"

namespace Zappy {

	Spectator::Spectator(int fd):
    Client(fd, ClientType::Spectator) {
		std::string welcome_msg = "Hello, Welcome spectator\nJoined at: ";

    welcome_msg.append(ctime(&created_at_ms_));
    broadcast(welcome_msg.c_str());
	}

	Spectator::~Spectator() {
	}

	std::ostream& operator<<(std::ostream& s, const Spectator& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

