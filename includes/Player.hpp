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
      Player(const Player&, Team& team);
      ~Player();
      Player&           operator= (const Player&) = delete; // const for safety... not super nesessary
      bool              advance();
      void              move_right();
      void              move_left();
      void              assign_client(Client * client);
      void              dismiss_client();
      bool              check_status(enum PlayerStatus status) const;
      int               get_id() const;
      const Direction&  get_direction() const;
      const Point&      get_position() const;
      const Team&       get_team() const;
      const std::string get_ppo() const;
      int               get_lvl() const;
      Client            *client_;
    private:
      static int get_next_id();

      const int         id_;

      Direction         direction_;
      Point             position_;
      int               lvl_;
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
