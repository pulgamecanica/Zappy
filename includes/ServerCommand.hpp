//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SERVERCOMMAND_HPP__
# define __SERVERCOMMAND_HPP__

#include <iostream>
#include <functional>

#include "Command.hpp"

namespace Zappy {
	class ServerCommand: public Command {
		public:
			ServerCommand(const ServerCommand&) = delete;
			ServerCommand&	operator= (const ServerCommand&) = delete;
			~ServerCommand();
      static ServerCommand* parse_command(GameEngine *trantor, const std::string &msg);
		protected:
			ServerCommand(const std::string& cmd, GameEngine *trantor, Command::Error e =  Command::Error::NoError);
		private:
			using ServerCommandFactory = std::function<ServerCommand*(GameEngine*, std::vector<std::string>&)>;
      static std::map<std::string, ServerCommandFactory> serverCommandFactoryMap;
	};
std::ostream&	operator<<(std::ostream&, const ServerCommand&);
}

#endif
