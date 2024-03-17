//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>

#include "Client.hpp"
#include "ClientCommand.hpp"
#include "Geometry/Direction.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
  class Player: public Client {
    public:
      enum PlayerStatus {
        Waiting,
        Playing,
        Dead,
        Error
      };
      Player(int fd);
      Player(const Player&) = default;
      ~Player();
      Player&           operator= (const Player&) = delete; // const for safety... not super nesessary
      bool              advance();
      void              move_right();
      void              move_left();
      enum PlayerStatus get_status() const;
    private:
      Direction         direction_;
      Point             position_;
      enum PlayerStatus status_;
      // struct timeval created_at_;
      // Team
      // ETC...
      // Inventory
      // Objects
  };

  std::ostream& operator<<(std::ostream&, const Player&);
}
#endif
