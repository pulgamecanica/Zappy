//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/MapSize.hpp"

namespace Zappy {

	MapSize::MapSize(GameEngine * trantor, Spectator & spectator):
		ClientCommand(trantor, "msz", 0), spectator_(spectator) {
	}

	MapSize::~MapSize() {
		// std::cout << "MapSize" << " destroyed" << std::endl;
	}

	bool  MapSize::is_valid() const { return (true); };

	void	MapSize::execute() {
		std::string size_str(trantor_->get_map_size());

    ClientCommand::execute();
		spectator_.broadcast(
			std::string("msz ") + size_str);
	}

	const std::string MapSize::cmd_error() const {
    return ClientCommand::cmd_error();
  }

	std::ostream& operator<<(std::ostream& s, const MapSize& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
