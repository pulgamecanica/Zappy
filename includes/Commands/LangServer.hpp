//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LANGSERVER_HPP__
# define __LANGSERVER_HPP__

#include <iostream>
#include <vector>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class LangServer: public Command {
		public:
			LangServer(Server *s, std::vector<std::string> & options);
			LangServer(const LangServer&) = default;
			~LangServer();
			LangServer&	operator= (const LangServer&) = default; // const for safety... not super nesessary
			bool	is_valid() const;
			void	execute();
		private:
			std::vector<std::string> options_;
	};

	std::ostream&	operator<<(std::ostream&, const LangServer&);
}

#endif

