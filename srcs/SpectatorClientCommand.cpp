//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "SpectatorClientCommand.hpp"
#include "Commands/SpectatorClientCommands/MapSize.hpp"
#include "Commands/SpectatorClientCommands/BlockContentTile.hpp"
#include "Commands/SpectatorClientCommands/MapContentTile.hpp"
#include "Commands/SpectatorClientCommands/TeamsNames.hpp"
#include "Commands/SpectatorClientCommands/PlayerPosition.hpp"
#include "Commands/SpectatorClientCommands/PlayerLevel.hpp"
#include "Commands/SpectatorClientCommands/GetTimeUnit.hpp"
#include "Commands/SpectatorClientCommands/SetTimeUnit.hpp"
#include "Commands/SpectatorClientCommands/Players.hpp"

namespace Zappy {

	std::map<std::string, SpectatorClientCommand::SpectatorsCommandFactory> SpectatorClientCommand::spectatorsCommandFactoryMap = {
    {"msz", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { (void)options; return new MapSize(trantor, s); }},
    {"bct", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { return new BlockContentTile(trantor, s, options); }},
    {"mct", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { (void)options; return new MapContentTile(trantor, s); }},
    {"tna", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { (void)options; return new TeamsNames(trantor, s); }},
    {"ppo", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { return new PlayerPosition(trantor, s, options); }},
    {"plv", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { return new PlayerLevel(trantor, s, options); }},
    {"sgt", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { (void)options; return new GetTimeUnit(trantor, s); }},
    {"sst", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { return new SetTimeUnit(trantor, s, options); }},
    {"players", [](GameEngine* trantor, Spectator& s, std::vector<std::string>& options) { (void)options; return new Players(trantor, s); }}
  };

	SpectatorClientCommand* SpectatorClientCommand::parse_command(GameEngine *trantor, Client *c, const std::string &cmd, std::vector<std::string>& options) {
		auto it = spectatorsCommandFactoryMap.find(cmd);
    if (it != spectatorsCommandFactoryMap.end()) {
      Spectator & s = *(dynamic_cast<Spectator *>(c));
      return it->second(trantor, s, options);
    }
    return nullptr;
	}

	SpectatorClientCommand::SpectatorClientCommand(GameEngine * trantor, const std::string cmd):
		ClientCommand(trantor, cmd, 0) {
	}

	SpectatorClientCommand::~SpectatorClientCommand() {
	}

	void SpectatorClientCommand::broadcast() const {
		; // Cant broadcast spectator commands... wtf?
	}

	std::ostream& operator<<(std::ostream& s, const SpectatorClientCommand& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
