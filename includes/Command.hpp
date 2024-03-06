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
			static Command * parse_server_command(const std::string & msg);
			// CONSTRUCTORS
			Command(const Command&) = default;
			virtual ~Command();
			// MEMBER FUNCTIONS
			Command&						operator= (const Command&) = default; // const for safety... not super nesessary
			const std::string & get_cmd() const;
			bool 								has_options() const;
			// VIRTAUL MEMBER FUNCTIONS(Inherited will prioritize)
			virtual bool				is_valid() const;
			virtual void 				execute(Server & s);
		protected:
			// Semi-Abstract Class, prevent Command from being created on the main scope
			Command(const char *cmd, const bool options_enabled);
		private:
			const std::string	cmd_;
			const bool 				options_enabled_;
			// const std::vector<std::string> options_;
	};

	std::ostream&	operator<<(std::ostream&, const Command&);
}

#endif

