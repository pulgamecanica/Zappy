//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __ADVANCE_HPP__
# define __ADVANCE_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {

	class Advance: public ClientCommand {
		public:
			Advance(GameEngine * trantor);
			Advance(const Advance&) = delete;
			~Advance();
			Advance&			operator= (const Advance&) = delete; // const for safety... not super nesessary
			virtual void	execute(Server & s, Client *c = nullptr);
			virtual bool	is_valid() const;
	};

	std::ostream&	operator<<(std::ostream&, const Advance&);
}
#endif

