//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <unistd.h>
	#include <sys/socket.h>
}

#include "Zappy.inc"
#include "Player.hpp"

namespace Zappy {
	Player::Player(int fd): Client(fd, ClientType::Player) {
		std::string welcome_msg = "Hello, Welcome player\nJoined at: ";

		welcome_msg.append(ctime(&created_at_ms_));
		send(fd, welcome_msg.c_str(), welcome_msg.length(), 0);
	}

	Player::~Player() {
		// if (DEBUG)
			// std::cout << "Player" << " destroyed" << std::endl;
	}

	std::ostream& operator<<(std::ostream& s, const Player& p) {
		s << (Client &)p;
		return (s);
	}
}
