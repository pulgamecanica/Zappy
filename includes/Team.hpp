//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAM_HPP__
# define __TEAM_HPP__

#include <iostream>
#include <vector>
#include <map>

namespace Zappy {
	class Player;
	class Client;

	class Team {
		public:
			Team(std::string name, int slots);
			Team(const Team&);
			~Team();
			Team&	operator= (const Team&) = default;
			bool	add_client(Client * client);
			const std::map<int, Player*> get_players_map();
			const std::string& get_name() const;
			int slots_left() const;
      explicit operator std::string() const;
      // Later move out ...
		private:
			std::vector<Player>	players_;
			std::string 	name_;
			int 								slots_;
	};

	std::ostream&	operator<<(std::ostream&, const Team&);
}
#endif

