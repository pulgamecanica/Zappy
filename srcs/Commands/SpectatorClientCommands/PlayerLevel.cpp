//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Commands/SpectatorClientCommands/PlayerLevel.hpp"

namespace Zappy {
	PlayerLevel::PlayerLevel(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		SpectatorClientCommand(trantor, "plv"), spectator_(spectator), player_(nullptr) {
			if (options.size() == 1) {
				try {
					player_id_ = std::stoi(options[0]);
					player_ = trantor_->get_player_by_id(player_id_);
				} catch (std::exception &e) {
					set_error(Command::Error::BadParams);
					player_ = nullptr;
    		}
			} else {
				set_error(Command::Error::MissingParams);
			}
	}

	PlayerLevel::~PlayerLevel() {
		;
	}

	void  PlayerLevel::execute() {
		ClientCommand::execute();
		if (!player_) {
			spectator_.broadcast("KO:Player not found");
		} else {
			spectator_.broadcast("plv " + std::to_string(player_->get_id()) +
				" " + std::to_string(player_->get_lvl()));
		}
	}

	const std::string PlayerLevel::cmd_error() const {
		if (DEBUG)
			return (ClientCommand::BAD_PARAMS_MSG + ":" + "'n' should be the index of a player > 0");
		return (ClientCommand::BAD_PARAMS_MSG);
	};

	std::ostream& operator<<(std::ostream& s, const PlayerLevel& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
