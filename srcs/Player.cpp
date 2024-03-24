//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
  #include <sys/socket.h>
  #include <stdlib.h>
}

#include <sstream>

#include "Zappy.inc"
#include "Player.hpp"
#include "Team.hpp"

namespace Zappy {

  ////////////////////////////////// STATIC PUBLIC CONST METHODS //////////////////////////////////
  const std::string Player::players_to_str(std::vector<Player *> lst) {
    std::stringstream ss;

    for (std::vector<Player *>::const_iterator i = lst.begin(); i != lst.end(); ++i)
      ss << " <" << (*i)->get_team() << ">:" << (*i)->get_id();
    return ss.str();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  Player::Player(const Player& p, Team& team): id_(p.id_), direction_(p.direction_),
    position_(p.position_), lvl_(p.lvl_), status_(p.status_), team_(team) {
  }

  Player::Player(Team & team): id_(Player::get_next_id()), direction_(Direction::get_random()),
      position_(rand() % 10, rand() % 10), lvl_(0), status_(Player::PlayerStatus::Waiting),
      team_(team) {
    if (DEBUG)
      std::cout << BLUE << "Player spawn {" << RED << team << BLUE <<"}: #" << id_ << " " << position_ << ENDC << " [" << BLUE << direction_.get_name() << ENDC << "]" << std::endl;
  }

  Player::~Player() {
    ;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////// CONST PUBLIC METHODS //////////////////////////////////////
  bool  Player::check_status(enum PlayerStatus status) const {
    return (status == status_);
  }

  const Direction& Player::get_direction() const {
    return (direction_);
  }

  int Player::get_id() const {
    return (id_);
  }
  
  int Player::get_lvl() const {
    return (lvl_);
  }
  
  const Point& Player::get_position() const {
    return (position_);
  }
  
  const std::string Player::get_ppo() const {
    std::stringstream ss;

    ss << "ppo " << id_ << " " << position_ << " " << direction_;
    return ss.str();
  }

  const Team& Player::get_team() const {
    return (team_);
  }

  Client* Player::get_client() const {
    return client_;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////////////// PUBLIC METHODS /////////////////////////////////////////
  bool Player::advance() {
    position_ += direction_; 
    return true;
  }

  void Player::assign_client(Client * client) {
    if (client) {
      client_ = client;
      status_ = PlayerStatus::Playing;
      client_->assign_player(this);
    }
  }

  void Player::dismiss_client() {
    if (client_) {
      client_->dismiss_player();
      client_ = nullptr;
      status_ = PlayerStatus::Waiting;
    }
  }

  void  Player::move_left() {
    direction_--;
  }

  void  Player::move_right() {
    direction_++;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////// STATIC PRIVATE CONST METHODS //////////////////////////////////
  int Player::get_next_id() {
    static int global_id_count = 1;

    return global_id_count++;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const Player& p) {
    s << "Player[" << p.get_id() << "] " << p.get_position() << " " << p.get_direction();
    return (s);
  }
}
