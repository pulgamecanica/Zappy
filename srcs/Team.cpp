//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Team.hpp"
#include "Player.hpp"
#include "Client.hpp"

namespace Zappy {

	Team::Team(std::string name, int slots): name_(name), slots_(slots) {
		for (int i = 0; i < slots; ++i) {
			players_.emplace_back(*this);
		}
	}

	Team::Team(const Team& t): name_(t.name_), slots_(t.slots_) {
		for (std::vector<Player>::const_iterator i = t.players_.begin(); i != t.players_.end(); ++i) {			
			players_.emplace_back(*i, *this);
		}
	}

	Team::~Team() {
	}

	int Team::slots_left() const {
		int players_ready;

		players_ready = 0;
		for (std::vector<Player>::const_iterator i = players_.begin(); i != players_.end(); ++i) {
			if (i->check_status(Player::PlayerStatus::Playing))
				players_ready++;
		}
		return (slots_ - players_ready);
	}

	bool Team::add_client(Client * client) {
		for (std::vector<Player>::iterator i = players_.begin(); i != players_.end(); ++i) {
			if (i->check_status(Player::PlayerStatus::Waiting)) {
				i->assign_client(client);
				return (true);
			}	
		}
		return (false);
	}

	Team::operator std::string() const {
		return (name_);
	}

	const std::map<int, const Player*> Team::get_players_map() const {
		std::map<int, const Player*> map;

		for (std::vector<Player>::const_iterator i = players_.begin(); i != players_.end(); ++i) {
			map[i->get_id()] = &*i;
		}
		return map;
	}

	const std::string& Team::get_name() const {
		return (name_);
	}

	std::ostream& operator<<(std::ostream& s, const Team& team) {
		s << std::string(team);
		return (s);
	}
}

