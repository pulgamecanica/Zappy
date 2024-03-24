//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/PlayerLevel.hpp"

namespace Zappy {
	PlayerLevel::PlayerLevel(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
		ClientCommand(trantor, "plv", 0), spectator_(spectator), bad_params_(false), player_(nullptr) {
			if (options.size() == 1) {
				try {
					player_num_ = std::stoi(options[0]);
					player_ = trantor_->get_player_by_index(player_num_);
				} catch (std::exception &e) {
					bad_params_ = true;
					player_ = nullptr;
    		}
			} else {
				bad_params_ = true;
			}
	}

	PlayerLevel::~PlayerLevel() {
		;
	}

	bool  PlayerLevel::is_valid() const {
		return !bad_params_;
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
		return ("KO:Wrong Arguments, 'n' should be the index of a player > 0");
	};

	std::ostream& operator<<(std::ostream& s, const PlayerLevel& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
