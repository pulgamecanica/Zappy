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

  Player::Player(/*int fd*/):
    /*Client(fd, ClientType::Player), */direction_(Direction::get_random()), position_(rand() % 10, rand() % 10), status_(Player::PlayerStatus::Waiting) {
    // std::string welcome_msg = "Hello, Welcome player\nJoined at: ";

    // welcome_msg.append(ctime(&created_at_ms_));
    // broadcast(welcome_msg.c_str());
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

  enum Player::PlayerStatus Player::get_status() const { return (status_); }


  Player::~Player() {
  }

  std::ostream& operator<<(std::ostream& s, const Player& p) {
    (void)p;
    // s << (Client &)p;
    return (s);
  }
}
