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
		// TODO (destructor)
	}

	ssize_t Player::uptime() const {
		struct timeval tv;

		if(gettimeofday(&tv, NULL) == -1) {
			perror("gettimeofday()");
			exit(EXIT_FAILURE);
		}
		return (tv.tv_sec - created_at_.tv_sec);
	}

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
