//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/Join.hpp"

namespace Zappy {

	Join::Join(GameEngine *trantor, Client &c, std::string team):
		ClientCommand(trantor, "join", 0), client_(c), team_(team), team_is_valid_(true) {
	}

	Join::~Join() {
	}

	bool	Join::is_valid() const {
		return trantor_->is_team_valid(team_);
	}

	void	Join::execute() {
    ClientCommand::execute();
    // Logic to join here
    // trantor.join(p, team_);
		client_.broadcast("OK:joined");
	}

	const std::string Join::cmd_error() const {
    std::string msg;

    msg.append(get_cmd());
  	if (!team_is_valid_) {
  		msg.append("<");
  		msg.append(team_);
  		msg.append(">:team is invalid");
  	} else {
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
