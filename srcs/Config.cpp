//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Config.hpp"

Config::Config(toml::table & table, const std::string language) {
	(void)table;
	(void)language;
	// TODO (default constructor)
}

Config::~Config() {
	std::cout << "Config" << " destroyed" << std::endl;
	// TODO (destructor)
}

std::ostream& operator<<(std::ostream& s, const Config& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

