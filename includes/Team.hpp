//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAM_HPP__
# define __TEAM_HPP__

#include <iostream>
#include <vector>

namespace Zappy {
	class Player;

	class Team {
		public:
			Team(std::string name, int slots);
			Team(const Team&);
			~Team();
			Team&	operator= (const Team&) = default; // const for safety... not super nesessary
      // bool	operator==(const std::string&) const; // Needed in order to use find with a string
			const std::string& get_name() const;
		private:
			std::string 	name_;
			std::vector<Player>	players_;
			int 								slots_;
	};

	std::ostream&	operator<<(std::ostream&, const Team&);
}
#endif

