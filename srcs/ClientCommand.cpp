//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "ClientCommand.hpp"
#include "Advance.hpp"

namespace Zappy {

	ClientCommand::ClientCommand(GameEngine *trantor, const std::string cmd, int frames_cost):
		Command(cmd), trantor_(trantor), frames_cost_(frames_cost), executed_at_frame_(-1), executed_(false) {
	}

	ClientCommand::~ClientCommand() {
	}

	bool ClientCommand::expired() const {
		if (!executed_)
			return false ;
		if (executed_at_frame_ == -1)
			return true ; // Should it be expired or not if it hasn't been executed? // maybe throw exception ?
		return (executed_at_frame_ + frames_cost_ > trantor_->frame());
	}

	int ClientCommand::get_cost() const { return (frames_cost_); }

	bool ClientCommand::is_valid() const { return (false); }

	bool ClientCommand::was_executed() const { return (executed_); }

	std::ostream& operator<<(std::ostream& s, const ClientCommand& cc) {
		s << (Command &)cc;
		return (s);
	}

	ClientCommand* ClientCommand::parse_command(GameEngine *trantor, const std::string &msg) {
		const std::string cmd = msg.substr(0, msg.find_first_of(" \n"));
		std::vector<std::string> options;

		// options = get_options(msg.substr(cmd.length()));
		if (cmd == "advance")
			return new Advance(trantor);
		// } else if (cmd == "status") {
		// 	return new ClientCommand();
		// } else if (cmd == "exit") {
		// 	return new ClientCommand();
		// } else if (cmd == "clear") {
		// 	return new ClientCommand();
		// } else if (cmd == "players") {
		// 	return new ClientCommand();
		// } else if (cmd == "lang") {
		// 	return new ClientCommand(options);
		// }
		return (new ClientCommand(trantor, cmd, 0));
	}
}

// List of commands:
/**
 * advance one square avance 7/t ok
 * turn right 90 degrees droite 7/t ok
 * turn left 90 degrees gauche 7/t ok
 * see voir 7/t {case1, case2, ...}
 * inventory inventaire 1/t {phiras n, sibur n, ...}
 * take an object prend <object> 7/t ok/ko
 * put down an object pose <object> 7/t ok/ko
 * kick the players from the square expulse 7/t ok/ko
 * broadcast broadcast <text> 7/t ok
 * begin the incantation incantation 300/t elevation en cours
 * niveau actuel : K
 * fork a player fork 42/t ok
 * know the number of unused connect_nbr 0/t value
 * connections by the team
 * death of a player - - mort
 **/
