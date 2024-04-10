//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "PlayerClientCommand.hpp"
#include "Commands/PlayerClientCommands/Advance.hpp"
#include "Commands/PlayerClientCommands/Right.hpp"
#include "Commands/PlayerClientCommands/Left.hpp"

namespace Zappy {

  std::map<std::string, PlayerClientCommand::PlayersCommandFactory> PlayerClientCommand::playersCommandFactoryMap = {
    {"advance", [](GameEngine* trantor, Player* p, std::vector<std::string>& options) { (void)options; return new Advance(trantor, p); }},
    {"right", [](GameEngine* trantor, Player* p, std::vector<std::string>& options) { (void)options; return new Right(trantor, p); }},
    {"left", [](GameEngine* trantor, Player* p, std::vector<std::string>& options) { (void)options; return new Left(trantor, p); }},
  };

  PlayerClientCommand* PlayerClientCommand::parse_command(GameEngine *trantor, Player *p, const std::string &cmd, std::vector<std::string>& options) {
		auto it = playersCommandFactoryMap.find(cmd);
    if (it != playersCommandFactoryMap.end()) {
      return it->second(trantor, p, options);
    }
    return nullptr;
	}

	PlayerClientCommand::PlayerClientCommand(GameEngine * trantor, const std::string cmd, int time_cost):
		ClientCommand(trantor, cmd, time_cost) {
	}

	PlayerClientCommand::~PlayerClientCommand() {

	}

	std::ostream& operator<<(std::ostream& s, const PlayerClientCommand& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
