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
	class LangServer: public virtual Command {
		public:
			LangServer(std::vector<std::string> & options);
			LangServer(const LangServer&) = default;
			virtual ~LangServer();
			LangServer&	operator= (const LangServer&) = default; // const for safety... not super nesessary
			virtual bool	is_valid() const;
			virtual void	execute(Server & s, Client *p);
		private:
			std::vector<std::string> options_;
	};

	std::ostream&	operator<<(std::ostream&, const LangServer&);
}

#endif

