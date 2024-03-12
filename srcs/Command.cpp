//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"
#include "Command.hpp"
#include "HelpServer.hpp"
#include "StatusServer.hpp"
#include "ExitServer.hpp"
#include "LangServer.hpp"
#include "ClearServer.hpp"
#include "PlayersServer.hpp"

#include "Server.hpp"

namespace Zappy {
	Command::Command(const std::string cmd): cmd_(cmd) {
	}

	Command::~Command() {
		// if (DEBUG)
			// std::cout << "Command" << " destroyed" << std::endl;
	}

	const std::string & Command::get_cmd() const {return (cmd_);}

	bool Command::is_valid() const {
		return false;
	}

	void Command::execute(Server & s, Client *p) {
		(void)s;(void)p;
		throw std::runtime_error("Cannot execute abstract command");
	}

	std::vector<std::string> Command::get_options(const std::string & options_str) {
		std::vector<std::string> options;

		std::istringstream stream(options_str);
		std::string option;

		while (stream >> option)
			if (!option.empty())
				options.push_back(option);

		if (DEBUG) {
			std::cout << GREEN << "Options: " << ENDC;
			if (options.empty())
				std::cout << "[]";
			for (std::vector<std::string>::iterator i = options.begin(); i != options.end(); ++i)
				std::cout << "[" << BLUE << *i << ENDC << "] ";
			std::cout << std::endl;
		}
		return (options);
	}

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
		std::vector<std::string> options;

		options = get_options(msg.substr(cmd.length()));
		if (cmd == "help") {
			return new HelpServer();
		} else if (cmd == "status") {
			return new StatusServer();
		} else if (cmd == "exit") {
			return new ExitServer();
		} else if (cmd == "clear") {
			return new ClearServer();
		} else if (cmd == "players") {
			return new PlayersServer();
		} else if (cmd == "lang") {
			return new LangServer(options);
		}
		return new Command(cmd);
	}

	std::ostream& operator<<(std::ostream& s, const Command& param) {
		s << param.get_cmd();
		return (s);
	}
}
