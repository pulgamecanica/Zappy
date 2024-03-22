//***************************//
//*Template by pulgamecanica*//
//***************************//


#include <sstream>

#include "Commands/Join.hpp"
#include "Player.hpp"
#include "Team.hpp"

namespace Zappy {

	Join::Join(GameEngine *trantor, Client &c, std::string team):
		ClientCommand(trantor, "join", 0), client_(c), team_(team), joined_(false) {
	}

	Join::~Join() {
	}
	
	void	Join::broadcast() const {
		std::stringstream ss;

		if (!is_valid() || !joined_)
			return ;
		Player *player = client_.player_;
		ss << "pnw " <<
			player->get_id() << " " <<
			player->get_position() << " " <<
			player->get_direction() << " " <<
			player->get_lvl() << " " <<
			player->get_team();
    trantor_->broadcast_spectators(ss.str());
	}

	bool	Join::is_valid() const {
		return trantor_->is_team_valid(team_);
	}

	void	Join::execute() {
		std::stringstream ss;
    ClientCommand::execute();

    joined_ = trantor_->join_team(team_, &client_);
    if (joined_) {
			// Player *player = client_.player_;
			ss << client_.player_->get_team().slots_left() << std::endl << std::string(trantor_->get_map_size());
			client_.broadcast(ss.str());
    } else {
			client_.broadcast("KO:failed to join the team");
    }
	}

	const std::string Join::cmd_error() const {
    std::string msg;

    msg.append(get_cmd());
  	if (!is_valid()) {
  		msg.append("<");
  		msg.append(team_);
  		msg.append(">:team is invalid");
  	} else if (!joined_) {
  		msg.append(":couldn't join");
  	}
    return (msg);
  }

	std::ostream& operator<<(std::ostream& s, const Join& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
