//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/SpectatorClientCommands/TeamsNames.hpp"
#include "Team.hpp"

namespace Zappy {

	TeamsNames::TeamsNames(GameEngine * trantor, Spectator & spectator):
		SpectatorClientCommand(trantor, "tna"), spectator_(spectator) {
	}

	TeamsNames::~TeamsNames() {
	}

	bool  TeamsNames::is_valid() const {
		return true;
	}

	void  TeamsNames::execute() {
		ClientCommand::execute();
    std::stringstream ss;

  	const std::vector<const Team *> teams = trantor_->get_teams();
	  for (std::vector<const Team *>::const_iterator i = teams.begin(); i != teams.end(); ++i) {
	  	ss <<	"tna " << std::string(*(*i)) << std::endl;
	  }
		spectator_.broadcast(ss.str());

	}

	const std::string TeamsNames::cmd_error() const {
		return ClientCommand::cmd_error();
	}


	std::ostream& operator<<(std::ostream& s, const TeamsNames& param) {
		(void)param;
		return (s);
	}
}
