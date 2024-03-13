//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <algorithm>

#include "Zappy.inc"
#include "LangServer.hpp"

namespace Zappy {

	LangServer::LangServer(Server *s, std::vector<std::string> & options):
		Command("lang", s), options_(options) {
	}

	LangServer::~LangServer() {
		// std::cout << "LangServer" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	bool	LangServer::is_valid() const {
		return true;
	}
	
	void	LangServer::execute() {
		std::string language;
		const std::vector<std::string>::const_iterator it = std::find(options_.begin(), options_.end(), "--help");
		const std::vector<std::string> languages(s_->get_list_of_supported_languages());
		bool help_needed = it != std::end(options_);
		
		if (help_needed) {
			std::cout << s_->get_config().get("language_help");
			std::cout << GREEN << "Langs\t" << ENDC;
			for (std::vector<std::string>::const_iterator it = languages.begin(); it != languages.end(); ++it)
				std::cout << "[" << (*it == s_->get_config().get_language_acronym() ? RED : BLUE) << *it << ENDC << "]";
			std::cout << std::endl;
		} else {
			if (options_.size() == 1) {
				s_->set_config(options_[0]);
			} else {
				std::cout << "lang: " << RED << "error" << ENDC << " `lang --help`" << std::endl;
			}
		}
	}

	std::ostream& operator<<(std::ostream& s, const LangServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
