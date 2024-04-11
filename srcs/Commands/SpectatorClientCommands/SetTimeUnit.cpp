//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/SpectatorClientCommands/SetTimeUnit.hpp"

namespace Zappy {
	SetTimeUnit::SetTimeUnit(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		SpectatorClientCommand(trantor, "sgt"), spectator_(spectator), bad_params_(false) {
			if (options.size() == 1) {
				try {
					time_unit = std::stoi(options[0]);
					if (time_unit <= 0)
						set_error(Command::Error::BadParams);
				} catch (std::exception &e) {
					set_error(Command::Error::BadParams);
    		}
			} else {
				set_error(Command::Error::MissingParams);
			}
	}

	SetTimeUnit::~SetTimeUnit() {
		;
	}
	
	void  SetTimeUnit::execute() {
		ClientCommand::execute();
		trantor_->set_time_unit(time_unit);
		spectator_.broadcast("sgt " + std::to_string(trantor_->get_time_unit()));
	}
	
	const std::string SetTimeUnit::cmd_error() const {
		return "KO:Time unit should be > 0";
	}

	std::ostream& operator<<(std::ostream& s, const SetTimeUnit& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
