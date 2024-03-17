//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAM_HPP__
# define __TEAM_HPP__

#include <iostream>
#include <vector>

#include "Player.hpp"

namespace Zappy {
	class Team {
		public:
			Team(const std::string name);
			Team(const Team&) = default;
			~Team();
			Team&	operator= (const Team&) = default; // const for safety... not super nesessary
		private:
			const std::string name_;
			// std::vector<Player > players;
	};

	std::ostream&	operator<<(std::ostream&, const Team&);
}
#endif

