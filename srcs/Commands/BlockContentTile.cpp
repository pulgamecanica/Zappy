//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/BlockContentTile.hpp"
#include "Tile.hpp"
#include "Player.hpp"

namespace Zappy {

 BlockContentTile::BlockContentTile(GameEngine *trantor, Spectator& spectator, std::vector<std::string>& options):
		ClientCommand(trantor, "bct", 0), spectator_(spectator), bad_params_(false), pos_(nullptr) {
			if (options.size() == 2) {
				try {
					int x, y;
					x = std::stoi(options[0]);
					y = std::stoi(options[1]);
					pos_ = new Point(x, y);
				} catch (std::exception &e) {
					bad_params_ = true;
    		}
			} else {
				bad_params_ = true;
			}
	}

	BlockContentTile::~BlockContentTile() {
		if (pos_)
			delete pos_;
	}

	bool  BlockContentTile::is_valid() const {
		return !bad_params_;
	};
	
	void  BlockContentTile::execute() {
    ClientCommand::execute();
		if (bad_params_) {
			spectator_.broadcast("KO:Wrong Coordinates");
		} else {
			spectator_.broadcast(
				std::string("bct ") +
				std::string(trantor_->get_tile(*pos_)));
		}
	}

	const std::string BlockContentTile::cmd_error() const {
		return ("KO:Wrong Arguments, X Y should be numeric");
	}

	std::ostream& operator<<(std::ostream& s, const BlockContentTile& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
