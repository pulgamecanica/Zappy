//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

#include <iostream>
#include <vector>

#include "Geometry/Direction.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
  class Client;
  class Team;

  class Player {
    public:
      // STATIC PUBLIC CONST METHODS //
      static const std::string players_to_str(std::vector<Player *> lst);
      // NESTED ENUM MEMBER //
      enum PlayerStatus {
        Waiting,
        Playing,
        Dead,
        Error
      };
      // CONSTRUCTORS & DESTRUCTORS //
      Player(Team& team);
      Player(const Player&, Team& team);
      Player(const Player&) = default;
      Player& operator= (const Player&) = delete;
      ~Player();
      // CONST PUBLIC METHODS //
      bool              check_status(enum PlayerStatus status) const;
      const Direction&  get_direction() const;
      int               get_id() const;
      int               get_lvl() const;
      const Point&      get_position() const;
      const std::string get_ppo() const;
      const Team&       get_team() const;
      Client*           get_client() const;
      // PUBLIC METHODS //
      bool              advance();
      void              assign_client(Client * client);
      void              dismiss_client();
      void              move_left();
      void              move_right();
    private:
      // STATIC PRIVATE CONST METHODS ///
      static int get_next_id();
      const int         id_;
      // PRIVATE MEMBERS ///
      Client            *client_;
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
