//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"
#include "Command.hpp"
#include "HelpServer.hpp"
#include "StatusServer.hpp"

namespace Zappy {
	Command::Command(const char *cmd, const bool options_enabled):
	cmd_(cmd), options_enabled_(options_enabled) {
		// TODO (default constructor)
	}

	Command::~Command() {
		// if (DEBUG)
			// std::cout << "Command" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	const std::string & Command::get_cmd() const {return (cmd_);}

	bool Command::is_valid() const {
		return false;
	}

	bool Command::has_options() const {return (options_enabled_);}

	void Command::execute(Server & s) {(void)s;}

	/**
	 * Server commands:
	 * 
	 * help -> Returns list of available commands
	 * status -> Returns the current status of the server
	 * exit -> exits the server
	 * lang <name> -> change the server language
	 * 
	 * */
	Command * Command::parse_server_command(const std::string & msg) {
		const std::string cmd = msg.substr(0, msg.find_first_of(" \n"));
		// Missing options
		if (cmd == "help") {
			return new HelpServer();
		} else if (cmd == "status") {
			return new StatusServer();
		}
		return new Command("command not found", false);
	}

	std::ostream& operator<<(std::ostream& s, const Command& param) {
		s << param.get_cmd();
		return (s);
	}
}
