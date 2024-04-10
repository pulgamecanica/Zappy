//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/SpectatorClientCommands/GetTimeUnit.hpp"

namespace Zappy {

	// SERVER GET TIME! //
	GetTimeUnit::GetTimeUnit(GameEngine * trantor, Spectator & spectator):
		SpectatorClientCommand(trantor, "sgt"), spectator_(spectator) {
	}

	GetTimeUnit::~GetTimeUnit() {
		;
	}

	bool GetTimeUnit::is_valid() const {
		return true;
	}

	void GetTimeUnit::execute() {
		ClientCommand::execute();
		spectator_.broadcast("sgt " + std::to_string(trantor_->get_time_unit()));
	}
	const std::string GetTimeUnit::cmd_error() const {
		return ClientCommand::cmd_error();
	}

	std::ostream& operator<<(std::ostream& s, const GetTimeUnit& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
