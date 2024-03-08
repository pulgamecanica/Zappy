//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __EXITSERVER_HPP__
# define __EXITSERVER_HPP__

#include <iostream>

#include "Command.hpp"

namespace Zappy {
	class ExitServer: public virtual Command {
		public:
			ExitServer();
			ExitServer(const ExitServer&) = default;
			virtual ~ExitServer();
			ExitServer&	operator= (const ExitServer&) = default; // const for safety... not super nesessary
			virtual bool	is_valid() const;
			virtual void	execute(Server & s);
	};

	std::ostream&	operator<<(std::ostream&, const ExitServer&);
}

#endif

