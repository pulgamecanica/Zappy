//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERCLIENTCOMMAND_HPP__
# define __PLAYERCLIENTCOMMAND_HPP__

#include <iostream>

#include "ClientCommand.hpp"

namespace Zappy {
	class PlayerClientCommand: public ClientCommand {
		public:
			PlayerClientCommand(GameEngine * trantor, const std::string cmd, int time_cost);
			PlayerClientCommand(const PlayerClientCommand&) = delete;
			PlayerClientCommand&	operator= (const PlayerClientCommand&) = delete;
			~PlayerClientCommand();
      static PlayerClientCommand* parse_command(GameEngine *trantor, Player *p, const std::string &cmd, std::vector<std::string>& options);
		private:
      using PlayersCommandFactory = std::function<PlayerClientCommand*(GameEngine*, Player*, std::vector<std::string>&)>;
      static std::map<std::string, PlayersCommandFactory> playersCommandFactoryMap;      
	};

	std::ostream&	operator<<(std::ostream&, const PlayerClientCommand&);
}
#endif
