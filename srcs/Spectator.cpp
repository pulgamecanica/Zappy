//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Spectator.hpp"

namespace Zappy {

	Spectator::Spectator(int fd, const std::string initial_msg):
    Client(fd, ClientType::SpectatorT) {
		std::string welcome_msg = "Hello, Welcome spectator\nJoined at: ";
		ssize_t seconds_since_epoch = created_at_ms_ / 1000;

    welcome_msg.append(ctime(&seconds_since_epoch));
    welcome_msg.append("\n");
    welcome_msg.append(initial_msg);
    welcome_msg.append("\n");
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

