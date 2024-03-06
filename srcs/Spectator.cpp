//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
	#include <unistd.h>
}

#include "Zappy.inc"
#include "Spectator.hpp"

namespace Zappy {
	Spectator::Spectator(int fd): fd_(fd) {
		// TODO (default constructor)
	}

	// Spectator::Spectator(const Spectator& param) {
	// 	// TODO (copy constructor)
	// 	(void)param;
	// }

	Spectator::~Spectator() {
		if (DEBUG)
			std::cout << "Spectator" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	// Spectator& Spectator::operator= (const Spectator& param) {
	// 	// TODO (Assignment operatior)
	// 	// std::swap()
	// 	(void)param;
	// 	return (*this);
	// }

	std::ostream& operator<<(std::ostream& s, const Spectator& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
