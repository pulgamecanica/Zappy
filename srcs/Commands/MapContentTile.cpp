//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/MapContentTile.hpp"
#include "Tile.hpp"
#include "Player.hpp"

namespace Zappy {

	MapContentTile::MapContentTile(GameEngine *trantor, Spectator& spectator):
		ClientCommand(trantor, "mct", 0), spectator_(spectator) {
	}

	MapContentTile::~MapContentTile() {
		// std::cout << "MapContentTile" << " destroyed" << std::endl;
	}

	bool  MapContentTile::is_valid() const {
		return true;
	}

	void  MapContentTile::execute() {
    std::stringstream ss;
    int lowest, last_index;

		ClientCommand::execute();
    lowest = trantor_->get_lowest_index();
    last_index = lowest + trantor_->get_map_area();
    for (int i = lowest; i < last_index; ++i) {
    	ss << "bct " << std::string(trantor_->get_tile(i)) << std::endl;
    }
		spectator_.broadcast(ss.str(), false);
	}

	const std::string MapContentTile::cmd_error() const {
    return ClientCommand::cmd_error();
	}

	std::ostream& operator<<(std::ostream& s, const MapContentTile& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}