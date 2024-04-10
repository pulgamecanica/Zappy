//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Commands/SpectatorClientCommands/BlockContentTile.hpp"
#include "Tile.hpp"
#include "Player.hpp"

namespace Zappy {
 BlockContentTile::BlockContentTile(GameEngine *trantor, Spectator& spectator, std::vector<std::string>& options):
		SpectatorClientCommand(trantor, "bct"), spectator_(spectator), /*bad_params_(false), missing_params_(false),*/ pos_(nullptr) {
			if (options.size() == 2) {
				try {
					int x, y;
					x = std::stoi(options[0]);
					y = std::stoi(options[1]);
					pos_ = new Point(x, y);
				} catch (std::exception &e) {
					set_error(Command::Error::BadParams);
    		}
			} else {
					set_error(Command::Error::MissingParams);
			}
	}

	BlockContentTile::~BlockContentTile() {
		if (pos_)
			delete pos_;
	}
	
	void  BlockContentTile::execute() {
    ClientCommand::execute();
		spectator_.broadcast(
			std::string("bct ") +
			std::string(trantor_->get_tile(*pos_)));
	}

	const std::string BlockContentTile::cmd_error() const {
		if (DEBUG)
			return (ClientCommand::BAD_PARAMS_MSG + ": " + get_error_msg() + "(`bct X Y` where `X` & `Y` are two valid `int` numbers)");
		return (ClientCommand::BAD_PARAMS_MSG);
	}

	std::ostream& operator<<(std::ostream& s, const BlockContentTile& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
