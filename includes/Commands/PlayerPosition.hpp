//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERPOSITION_HPP__
# define __PLAYERPOSITION_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "Spectator.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

namespace Zappy {
	class PlayerPosition: public ClientCommand {
		public:
		  PlayerPosition(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options);
			PlayerPosition(const PlayerPosition&) = default;
			~PlayerPosition();
			PlayerPosition&	operator=(const PlayerPosition&) = default;
			bool  is_valid() const;
      void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			bool bad_params_;
			int player_num_;
			const Player* player_;
	};

	std::ostream&	operator<<(std::ostream&, const PlayerPosition&);
}
#endif

