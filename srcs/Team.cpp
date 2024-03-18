//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Team.hpp"
#include "Player.hpp"

namespace Zappy {

	Team::Team(std::string name, int slots): name_(name), slots_(slots) {
		for (int i = 0; i < slots; ++i) {
			players_.emplace_back(*this);
		}
	}

	Team::Team(const Team& t): name_(t.name_), players_(t.players_), slots_(t.slots_) {
	}

	// bool	operator==(const std::string&) const; // Needed in order to use find with a string



	Team::~Team() {
	}

	const std::string& Team::get_name() const {
		return (name_);
	}


	std::ostream& operator<<(std::ostream& s, const Team& team) {
		s << team.get_name();
		return (s);
	}
}

