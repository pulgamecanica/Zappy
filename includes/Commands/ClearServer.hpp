//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLEARSERVER_HPP__
# define __CLEARSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class ClearServer: public Command {
		public:
			ClearServer();
			ClearServer(const ClearServer&) = default;
			~ClearServer();
			ClearServer&	operator= (const ClearServer&) = default; // const for safety... not super nesessary
			bool	is_valid() const;
			void	execute();
	};

	std::ostream&	operator<<(std::ostream&, const ClearServer&);
}

#endif

