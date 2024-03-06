//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CONFIG_HPP__
# define __CONFIG_HPP__

#include <iostream>

#include <toml++/toml.hpp>

class Config {
	public:
		Config(toml::table & table, const std::string language);
		Config(const Config&) = default;
		~Config();
		Config&	operator= (const Config&) = default; // const for safety... not super nesessary
	private:
		// const std::string language_;
		// const std::string language_acronym_;
		// const std::string welcome_message_;
		// const std::string help_;
};

std::ostream&	operator<<(std::ostream&, const Config&);

#endif

