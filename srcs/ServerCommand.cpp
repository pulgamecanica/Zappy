//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "ServerCommand.hpp"
#include "Commands/ServerCommands/HelpServer.hpp"
#include "Commands/ServerCommands/ExitServer.hpp"
#include "Commands/ServerCommands/StatusServer.hpp"
#include "Commands/ServerCommands/LangServer.hpp"
#include "Commands/ServerCommands/ClearServer.hpp"
#include "Commands/ServerCommands/PlayersServer.hpp"

namespace Zappy {


  std::map<std::string, ServerCommand::ServerCommandFactory> ServerCommand::serverCommandFactoryMap = {
    {"help", [](GameEngine* trantor, std::vector<std::string>& options) { (void)options; return new HelpServer(trantor); }},
    {"exit", [](GameEngine* trantor, std::vector<std::string>& options) { (void)options; return new ExitServer(trantor); }},
    {"status", [](GameEngine* trantor, std::vector<std::string>& options) { (void)options; return new StatusServer(trantor); }},
    {"lang", [](GameEngine* trantor, std::vector<std::string>& options) { return new LangServer(trantor, options); }},
    {"clear", [](GameEngine* trantor, std::vector<std::string>& options) { (void)options; (void)trantor; return new ClearServer(); }},
    {"players", [](GameEngine* trantor, std::vector<std::string>& options) { (void)options; return new PlayersServer(trantor); }},
  };

	ServerCommand* ServerCommand::parse_command(GameEngine *trantor, const std::string &msg) {
		const std::string cmd = msg.substr(0, msg.find_first_of(" \n"));
    std::vector<std::string> options = Command::get_options(msg.substr(cmd.length()));

		auto it = serverCommandFactoryMap.find(cmd);
    if (it != serverCommandFactoryMap.end()) {
      return it->second(trantor, options);
    }
    return new ServerCommand(cmd, trantor, Command::Error::CommandNotFound);
	}

	ServerCommand::ServerCommand(const std::string& cmd, GameEngine *trantor, Command::Error e):
		Command(cmd, trantor, e) {
	}

	ServerCommand::~ServerCommand() {
	}

	std::ostream& operator<<(std::ostream& s, const ServerCommand& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
