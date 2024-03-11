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
		ssize_t t;

		if (gettimeofday(&created_at_, NULL) == -1) {
			perror("gettimeofday()");
			exit(EXIT_FAILURE);
		}
		t = ((created_at_.tv_sec * 1000) + (created_at_.tv_usec / 1000)) / 1000;
		welcome_msg.append(ctime(&t));
		send(fd, welcome_msg.c_str(), welcome_msg.length(), 0);
	}

	Player::~Player() {
		// if (DEBUG)
			// std::cout << "Player" << " destroyed" << std::endl;
	}

	Command * Player::parse_command() const {
		return (Command::parse_server_command("not found..."));
	};


	std::ostream& operator<<(std::ostream& s, const Player& p) {
		s << (Client)p;
		return (s);
	}
}
