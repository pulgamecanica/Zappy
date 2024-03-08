//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>
#include "Zappy.inc"
#include "Config.hpp"

namespace Zappy {

	const std::string Config::get_value_or_empty(toml::table & table, const std::string language, const std::string key) {
		return ((std::optional<std::string>(table[language][key].value<std::string>())).value_or(""));
	}

	Config::Config(toml::table & table, const std::string language):
		language_(get_value_or_empty(table, language, "language")),
		language_acronym_(language),
	 	language_help_(get_value_or_empty(table, language, "language_help")),
		help_(get_value_or_empty(table, language, "help")),
		welcome_to_server_(get_value_or_empty(table, language, "welcome_to_server")),
		total_players_(get_value_or_empty(table, language, "total_players")),
		total_spectators_(get_value_or_empty(table, language, "total_spectators")),
	 	server_life_(get_value_or_empty(table, language, "server_life"))
	 {
	 	std::string error_msg_item;

	 	// Should implement a map to avoid so much code and repetition
	 	// Map all values, if value is not found, then error.
	 	// if maped value is empty error
	 	if (language_.empty()) {
	 		error_msg_item = "language";
	 	} else if (help_.empty()) {
	 		error_msg_item = "help";
	 	} else if (welcome_to_server_.empty()) {
	 		error_msg_item = "welcome_to_server";
	 	} else if (language_acronym_.empty()) {
	 		error_msg_item = "acronym";
	 	} else if (total_players_.empty()) {
	 		error_msg_item = "total_players";
	 	} else if (total_spectators_.empty()) {
	 		error_msg_item = "total_spectators";
	 	} else if (language_help_.empty()) {
	 		error_msg_item = "language_help";
	 	} else if (server_life_.empty()) {
	 		error_msg_item = "server_life";
	 	}
	 	if (!error_msg_item.empty()) {
	 		std::stringstream ss;
	 		
	 		ss << "Error [" << language << "]: '" << error_msg_item
	 			<< "' is empty, using the wrong type, or undefined, check the configuration toml file";
	 		throw std::runtime_error(ss.str());
	 	}
	}


	const std::string & Config::get_language() const { return (language_); }

	const std::string & Config::get_language_acronym() const { return (language_acronym_); }
	
	const std::string & Config::get_language_help() const { return (language_help_); }

	const std::string & Config::get_help() const { return (help_); }

	const std::string & Config::get_welcome_to_server() const { return (welcome_to_server_); }

	const std::string & Config::get_total_players() const { return (total_players_); }

	const std::string & Config::get_total_spectators() const { return (total_spectators_); }

	const std::string & Config::get_server_life() const { return (server_life_); }
	
	Config::~Config() {
		// std::cout << "Config" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	bool Config::operator==(const std::string& lang_acronym) const {
		return (language_acronym_ == lang_acronym);
	}

	std::ostream& operator<<(std::ostream& s, const Config& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

