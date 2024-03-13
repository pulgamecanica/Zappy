//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
  #include <sys/socket.h>
  #include <stdlib.h>
}

#include "Zappy.inc"
#include "Player.hpp"

namespace Zappy {

  enum Direction Player::get_direction(int i) {
    switch (i) {
      case 0:
        return Direction::North;
      case 1:
        return Direction::South;
      case 2:
        return Direction::East;
      case 3:
        return Direction::West;
      default:
        return Direction::North;
    }
  }

  Player::Player(int fd): Client(fd, ClientType::Player) {
    std::string welcome_msg = "Hello, Welcome player\nJoined at: ";

    welcome_msg.append(ctime(&created_at_ms_));
    send(fd, welcome_msg.c_str(), welcome_msg.length(), 0);

    direction_ = get_direction(rand() % 4);
    position_[0] = rand() % 10;
    position_[1] = rand() % 10;
  }

  const int *Player::direction_vec() {
    return DIRECTIONS_VEC[direction_];
  }

  bool Player::advance() {
    const int * d = direction_vec();

    position_[0] += d[0];
    position_[1] += d[1];
    return true;
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
