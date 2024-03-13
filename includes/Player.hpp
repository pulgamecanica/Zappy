//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>

#include "Client.hpp"
#include "ClientCommand.hpp"

namespace Zappy {
  
  enum Direction {
    North,
    South,
    East,
    West
  };

  class Player: public Client {
    public:
      static enum Direction get_direction(int i);

      static constexpr const char *DIRECTIONS_STR[4] = {
        "North",
        "South",
        "East",
        "West"
      };
      
      static constexpr int DIRECTIONS_VEC[4][2] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
      };
      
      Player(int fd);
      Player(const Player&) = default;
      ~Player();
      Player& operator= (const Player&) = delete; // const for safety... not super nesessary
      bool    advance();
      const int     *direction_vec();
    private:
      enum Direction  direction_;
      int             position_[2];
      // const int      fd_;
      // struct timeval created_at_;
      // Team
      // ETC...
      // Inventory
      // Objects
  };

  std::ostream& operator<<(std::ostream&, const Player&);
}
#endif
