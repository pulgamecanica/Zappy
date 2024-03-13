//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>
#include <vector>

#include "Client.hpp"

namespace Zappy {
	
	class Server;

	class Command {
		public:
			static Command* parse_server_command(const std::string & msg, Server * s);
			
			// CONSTRUCTORS
			Command(const Command&) = default;
			virtual ~Command();
			
			// MEMBER FUNCTIONS
			Command&						operator=(const Command&) = default; // const for safety... not super nesessary
			const std::string & get_cmd() const;
			// VIRTUAL MEMBER FUNCTIONS(Inherited will prioritize)
			virtual bool				is_valid() const;
			virtual void				execute();
		protected:
			// Semi-Abstract Class, prevent Command from being created on the main scope
			Command(const std::string cmd, Server * s);
			static std::vector<std::string>	get_options(const std::string & options_str);
			Server * s_;
		private:
			const std::string	cmd_;
	};

	std::ostream&	operator<<(std::ostream&, const Command&);
}

#endif

