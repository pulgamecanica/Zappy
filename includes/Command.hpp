//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>
#include <vector>

#include "Server.hpp"

namespace Zappy {
	class Command {
		public:
			Command(const Command&) = default;
			virtual ~Command();
			Command&	operator= (const Command&) = default; // const for safety... not super nesessary
			static Command * parse_server_command(const std::string & msg);
			const std::string & get_cmd() const;
			bool has_options() const;
			virtual bool is_valid() const;
			virtual void execute(Server & s);
			virtual const std::string get_output() const;
		protected:
			// CLASS FUNCTION MEMBERS
			Command(const char *cmd, const bool options_enabled);
		private:
			const std::string cmd_;
			const bool options_enabled_;
			// const std::vector<std::string> options_;
	};

	std::ostream&	operator<<(std::ostream&, const Command&);
}

#endif

