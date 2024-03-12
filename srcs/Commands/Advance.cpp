//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Advance.hpp"

namespace Zappy {

	Advance::Advance(GameEngine * trantor): ClientCommand(trantor, "advance", 7) {
		// TODO (default constructor)
	}

	Advance::~Advance() {
		// std::cout << "Advance" << " destroyed" << std::endl;
	}

	void	Advance::execute(Server & s, Client *c) {
		(void)s;
		(void)c;
		std::cout << "Executing Advance" << std::endl;
	}

	bool	Advance::is_valid() const { return (true); }


	std::ostream& operator<<(std::ostream& s, const Advance& param) {
		s << (Command &)param;
		return (s);
	}
}

