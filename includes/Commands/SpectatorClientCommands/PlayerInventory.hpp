//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERINVENTORY_HPP__
# define __PLAYERINVENTORY_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"

namespace Zappy {

	class PlayerInventory: public SpectatorClientCommand {
		public:
		  PlayerInventory(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options);
			PlayerInventory(const PlayerInventory&);
			~PlayerInventory();
			PlayerInventory&	operator= (const PlayerInventory&);
			void  execute();
			const std::string cmd_error() const;
		public:
			Spectator & spectator_;
			int player_id_;
			const Player* player_;
	};

	std::ostream&	operator<<(std::ostream&, const PlayerInventory&);
}

#endif

