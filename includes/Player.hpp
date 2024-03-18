//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>

// #include "Client.hpp"
#include "ClientCommand.hpp"
#include "Geometry/Direction.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
  
  class Client;
  class Team;

  class Player {//: public Client {
    public:
      enum PlayerStatus {
        Waiting,
        Playing,
        Dead,
        Error
      };
      Player(Team& team);
      Player(const Player&) = default;
      ~Player();
      Player&           operator= (const Player&) = delete; // const for safety... not super nesessary
      bool              advance();
      void              move_right();
      void              move_left();
      enum PlayerStatus get_status() const;
      Client            *client_;
    private:
      Direction         direction_;
      Point             position_;
      enum PlayerStatus status_;
      Team&             team_;
      // struct timeval created_at_;
      // Team
      // ETC...
      // Inventory
      // Objects
  };

  std::ostream& operator<<(std::ostream&, const Player&);
}
#endif
