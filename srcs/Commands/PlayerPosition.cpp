//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/PlayerPosition.hpp"

namespace Zappy {

	PlayerPosition::PlayerPosition(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		ClientCommand(trantor, "ppo", 0), spectator_(spectator), bad_params_(false), player_(nullptr) {
			if (options.size() == 1) {
				try {
					player_num_ = std::stoi(options[0]);
					player_ = trantor_->get_player_by_index(player_num_);
						// throw std::runtime_error("player index should be > 0");
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
			spectator_.broadcast("KO:Player not found");
		} else {
			spectator_.broadcast(player_->get_ppo());
		}
	}

	const std::string PlayerPosition::cmd_error() const {
		return ("KO:Wrong Arguments, 'n' should be the index of a player > 0");
	};

	std::ostream& operator<<(std::ostream& s, const PlayerPosition& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
