//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Commands/SpectatorClientCommands/PlayerPosition.hpp"

namespace Zappy {
	PlayerPosition::PlayerPosition(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		SpectatorClientCommand(trantor, "ppo"), spectator_(spectator), bad_params_(false), player_(nullptr) {
			if (options.size() == 1) {
				try {
					player_id_ = std::stoi(options[0]);
					player_ = trantor_->get_player_by_id(player_id_);
				} catch (std::exception &e) {
					bad_params_ = true;
					player_ = nullptr;
    		}
			} else {
				bad_params_ = true;
			}
	}

	PlayerPosition::~PlayerPosition() {
		;
	}

	bool  PlayerPosition::is_valid() const {
		return !bad_params_;
	}

	void  PlayerPosition::execute() {
		ClientCommand::execute();
		if (!player_) {
			spectator_.broadcast("Player not found");
		} else {
			spectator_.broadcast(player_->get_ppo());
		}
	}

	const std::string PlayerPosition::cmd_error() const {
		if (DEBUG)
			return (ClientCommand::BAD_PARAMS_MSG + ":" + "'n' should be the index of a player > 0");
		return (ClientCommand::BAD_PARAMS_MSG);
	};

	std::ostream& operator<<(std::ostream& s, const PlayerPosition& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
