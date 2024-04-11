//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERPOSITION_HPP__
# define __PLAYERPOSITION_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

namespace Zappy {
	class PlayerPosition: public SpectatorClientCommand {
		public:
		  PlayerPosition(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options);
			PlayerPosition(const PlayerPosition&) = default;
			~PlayerPosition();
			PlayerPosition&	operator=(const PlayerPosition&) = default;
      void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			int player_id_;
			const Player* player_;
	};

	std::ostream&	operator<<(std::ostream&, const PlayerPosition&);
}
#endif

