//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "Zappy.inc"

#include "Commands/SpectatorClientCommands/PlayerInventory.hpp"

namespace Zappy {

	PlayerInventory::PlayerInventory(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		SpectatorClientCommand(trantor, "pin"), spectator_(spectator), player_(nullptr) {
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

	PlayerInventory::~PlayerInventory() {
	}

	void  PlayerInventory::execute() {
		ClientCommand::execute();
    std::stringstream ss;

		if (!player_) {
			spectator_.broadcast("KO:Player not found");
		} else {
			ss << get_cmd() << " "
				<< player_->get_id() << " "
				<< player_->get_position() << " "
				<< player_->get_inventory();
			spectator_.broadcast(ss.str());
		}
	}

	const std::string PlayerInventory::cmd_error() const {
		if (DEBUG)
			return (ClientCommand::BAD_PARAMS_MSG + ":" + "'n' should be the index of a player > 0");
		return (ClientCommand::BAD_PARAMS_MSG);
	};


	std::ostream& operator<<(std::ostream& s, const PlayerInventory& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
