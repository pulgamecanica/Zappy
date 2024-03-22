//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/BlockContentTile.hpp"

namespace Zappy {

 BlockContentTile::BlockContentTile(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options):
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
		return true;
		// return trantor_->is_valid_coordinate(pos_);
	};
	
	void  BlockContentTile::execute() {
    ClientCommand::execute();
		if (!is_valid())
			return ;
		if (bad_params_) {
			spectator_.broadcast("KO:impossible to get the coordinates requested");
		} else {
			// const Tile & t = trandtor_->get_tile(pos_);	 
			spectator_.broadcast(
				std::string("bct ") + std::string(*pos_));
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
