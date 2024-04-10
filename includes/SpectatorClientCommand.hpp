//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SPECTATORCLIENTCOMMAND_HPP__
# define __SPECTATORCLIENTCOMMAND_HPP__

#include <iostream>

#include "ClientCommand.hpp"

namespace Zappy {

	class SpectatorClientCommand: public ClientCommand {
		public:
			SpectatorClientCommand(GameEngine * trantor, const std::string cmd);
			SpectatorClientCommand(const SpectatorClientCommand&) = delete;
			SpectatorClientCommand&	operator= (const SpectatorClientCommand&) = delete;
			~SpectatorClientCommand();

      void	broadcast() const;
      static SpectatorClientCommand* parse_command(GameEngine *trantor, Client *c, const std::string &cmd, std::vector<std::string>& options);
    private:
      using SpectatorsCommandFactory = std::function<SpectatorClientCommand*(GameEngine*, Spectator&, std::vector<std::string>&)>;
      static std::map<std::string, SpectatorsCommandFactory> spectatorsCommandFactoryMap;
	};

std::ostream&	operator<<(std::ostream&, const SpectatorClientCommand&);
}

#endif
