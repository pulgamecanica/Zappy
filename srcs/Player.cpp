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

  Player::Player(int fd):
    Client(fd, ClientType::Player), direction_(Direction::get_random()), position_(rand() % 10, rand() % 10) {
    std::string welcome_msg = "Hello, Welcome player\nJoined at: ";

    welcome_msg.append(ctime(&created_at_ms_));
    send(fd, welcome_msg.c_str(), welcome_msg.length(), 0);
  }

  bool Player::advance() {
    position_ += direction_; 
    std::cout << YELLOW << "[Server]\t" << ENDC << "advance:" << BLUE << *this << GREEN << "\tPosition:" << position_ << "  " << direction_ << ENDC << std::endl;
    return true;
  }

  void  Player::move_right() {
    direction_++;
    std::cout << YELLOW << "[Server]\t" << ENDC << "right:" << BLUE << *this << GREEN << "\tPosition:" << position_ << "  " << direction_ << ENDC << std::endl;
  }

  void  Player::move_left() {
    direction_--;
    std::cout << YELLOW << "[Server]\t" << ENDC << "right:" << BLUE << *this << GREEN << "\tPosition:" << position_ << "  " << direction_ << ENDC << std::endl;
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
