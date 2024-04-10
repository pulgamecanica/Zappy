//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __GAMEENGINE_HPP__
# define __GAMEENGINE_HPP__

#include <iostream>
#include <vector>
#include <map>

#include "Server.hpp"
#include "Map.hpp"
#include "Geometry/Point.hpp"

/**
 * Note: GameEngine::t_
 * 
 *    t_ <=> fps | it's the time basically;
 *    let t = 100.
 *    1 / t = frame_len <==> 1 / 100 = 0.01 seconds
 *    Each frame should be 0.01 seconds, or 0.01 * (1000ms)  miliseconds
 *    Therefore each frame is 10 miliseconds, and so frame_delay is this defined
 **/
namespace Zappy {
  class Team;
  class Client;
  class Player;
  
  class GameEngine: public Server, public Map {
    public:
      // CONSTRUCTORS & DESTRUCTORS //
      GameEngine(
        std::vector<std::string> teams,
        int default_time = 100,
        std::string toml_file = "conf.toml",
        std::string default_lang = "en",
        int players_port = 4242,
        int spectators_port = 2121,
        Point map_size = {10, 10},
        int num_players = 1,
        int timeout = 60000);
      GameEngine(const GameEngine&) = delete;
      GameEngine& operator=(const GameEngine&) = delete;
      ~GameEngine();
      // CONST PUBLIC METHODS //
      unsigned int                      frame() const;
      Point                             get_map_size() const;
      const std::vector<const Player *> get_players() const;
      const std::vector<const Team *>   get_teams() const;
      int                               get_time_unit() const;
      bool                              is_team_valid(const std::string & team) const;
      bool                              join_team(const std::string & team, Client * client);
      // PUBLIC METHODS //
      std::vector<Player*>  get_players_at(const Point & p);
      std::vector<Player*>  get_players_at(int index);
      const Player*         get_player_by_id(int id);
      void                  set_time_unit(int t);
      void                  start(int * sig);
    private:
      // PRIVATE METHODS //
      bool          is_time_to_update();
      void          set_game_delay();
      void          update();
      void          update_time();
      // PRIVATE MEMBERS //
      unsigned int                current_frame_;
      int                         frame_delay_; // in miliseconds, based on t_ ; see Note above
      int                         *sig_;
      int                         t_; // t = fps, it's the time basically 
      std::map<std::string, Team> teams_;
      std::map<int, const Player *> players_;
      ssize_t                     updated_at_ms_;
  };

  std::ostream& operator<<(std::ostream&, const GameEngine&);
}
#endif

