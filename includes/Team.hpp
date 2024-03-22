//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAM_HPP__
# define __TEAM_HPP__

#include <iostream>
#include <vector>

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
			const std::string& get_name() const;
			int slots_left() const;
		private:
			std::string 	name_;
			std::vector<Player>	players_;
			int 								slots_;
	};

	std::ostream&	operator<<(std::ostream&, const Team&);
}
#endif

