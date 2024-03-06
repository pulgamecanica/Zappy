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
	Player::Player(int fd): fd_(fd) {
		std::string welcome_msg = "Hello, welcome to the Zappy Server\n";
		send(fd, welcome_msg.c_str(), welcome_msg.length(), 0);
		// TODO (default constructor)
	}

	// Player::Player(const Player& param) {
	// 	// TODO (copy constructor)
	// 	(void)param;
	// }

	Player::~Player() {
		// if (DEBUG)
			// std::cout << "Player" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	// Player& Player::operator= (const Player& param) {
	// 	// TODO (Assignment operatior)
	// 	// std::swap()
	// 	(void)param;
		// return (*this);
	// }

	// void Player::handle_io() {
	// 	ssize_t total_bytes(0);
	// 	ssize_t read_bytes(0);
	// 	char buf[1024];

	// 	for (;;) {
	// 		read_bytes = recv(fd_, buf, 1024, MSG_DONTWAIT);
	// 		if (read_bytes == -1) {
	// 			if (errno == EAGAIN || errno == EWOULDBLOCK)
	// 				break ; // DONE READING
	// 			else {
	// 				perror("recv()");
	// 				exit(EXIT_FAILURE);
	// 		}
	// 	}
	// }

	std::ostream& operator<<(std::ostream& s, const Player& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
