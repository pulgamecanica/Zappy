//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CONFIG_HPP__
# define __CONFIG_HPP__

#include <iostream>

#include <toml++/toml.hpp>

namespace Zappy {
	class Config {
		public:
			Config(toml::table & table, const std::string language);
			Config(const Config&) = default;
			~Config();
			Config&							operator= (const Config&) = default; // const for safety... not super nesessary
			bool								operator==(const std::string&) const; // Needed in order to use find with a string
			const std::string & get_language() const;
			const std::string & get_language_acronym() const;
			const std::string & get_help() const;
			const std::string & get_welcome_to_server() const;
			const std::string & get_total_players() const;
			const std::string & get_total_spectators() const;
		private:
			// CLASS FUNCTION MEMBERS
			static const std::string get_value_or_empty(toml::table & table, const std::string language, const std::string key);
			// CLASS PARAMS MEMBERS
			const std::string language_;
			const std::string language_acronym_;
			const std::string help_;
			const std::string welcome_to_server_;
			const std::string total_players_;
			const std::string total_spectators_;
			// const std::string welcome_client_;
			// const std::string help_;
	};

	std::ostream&	operator<<(std::ostream&, const Config&);
}

#endif

