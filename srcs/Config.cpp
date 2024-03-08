//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>
#include "Zappy.inc"
#include "Config.hpp"

namespace Zappy {
	const std::vector<std::string> Config::DIRECTIVES = {
		"language",
		"language_help",
		"help",
		"welcome_to_server",
		"total_players",
		"total_spectators",
		"server_life",
	};

	const std::string Config::get_value_or_empty(toml::table & table, const std::string language, const std::string key) {
		return ((std::optional<std::string>(table[language][key].value<std::string>())).value_or(""));
	}

	Config::Config(toml::table & table, const std::string language):
		language_acronym_(language)
	 {
	 	std::string val;
		std::stringstream ss;
	 	
	 	for (std::vector<std::string>::const_iterator it = DIRECTIVES.begin(); it != DIRECTIVES.end(); ++it) {
	 		val = get_value_or_empty(table, language, *it);
	 		if (val.empty()) {
		 		ss << "Error [" << language << "]: '" << *it
		 			<< "' is empty, using the wrong type, or undefined, check the configuration toml file";
		 		throw std::runtime_error(ss.str());
		 	}
	 		toml_contents_[*it] = (val);
	 	}
	}

	const std::string & Config::get(const std::string & directive) const { return toml_contents_.at(directive); }
	
	const std::string & Config::get_language_acronym() const { return (language_acronym_); }
	
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

