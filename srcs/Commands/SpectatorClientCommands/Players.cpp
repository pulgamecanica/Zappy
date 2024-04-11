//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/SpectatorClientCommands/Players.hpp"
#include "Player.hpp"
#include "Team.hpp"

namespace Zappy {

	Players::Players(GameEngine * trantor, Spectator & spectator):
		SpectatorClientCommand(trantor, "players"), spectator_(spectator) {
	}

	Players::~Players() {
	}

	bool  Players::is_valid() const {
		return true;
	}

	void  Players::execute() {
		ClientCommand::execute();
    std::stringstream ss;

  	const std::vector<const Player *> players = trantor_->get_players();
	  for (std::vector<const Player *>::const_iterator i = players.begin(); i != players.end(); ++i) {
	  	ss << *(*i) << std::endl;
	  }
		spectator_.broadcast(ss.str());

	}

	const std::string Players::cmd_error() const {
		return ClientCommand::cmd_error();
	}


	std::ostream& operator<<(std::ostream& s, const Players& param) {
		(void)param;
		return (s);
	}
}
