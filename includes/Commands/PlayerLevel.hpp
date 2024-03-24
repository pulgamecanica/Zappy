//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERLEVEL_HPP__
# define __PLAYERLEVEL_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "Spectator.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

namespace Zappy {
	class PlayerLevel: public ClientCommand {
		public:
		  PlayerLevel(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options);
			PlayerLevel(const PlayerLevel&) = default;
			~PlayerLevel();
			PlayerLevel&	operator=(const PlayerLevel&) = default;
			bool  is_valid() const;
      void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			bool bad_params_;
			int player_num_;
			const Player* player_;
	};

	std::ostream&	operator<<(std::ostream&, const PlayerLevel&);
}
#endif

