//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Team.hpp"

namespace Zappy {

	Team::Team(const std::string name): name_(name) {
	}

	Team::~Team() {
	}

	std::ostream& operator<<(std::ostream& s, const Team& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

