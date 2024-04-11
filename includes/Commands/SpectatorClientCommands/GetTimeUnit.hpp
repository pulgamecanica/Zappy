//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __GETTIMEUNIT_HPP__
# define __GETTIMEUNIT_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"
#include "GameEngine.hpp"

namespace Zappy {
	class GetTimeUnit: public SpectatorClientCommand {
		public:
			GetTimeUnit(GameEngine * trantor, Spectator & spectator);
			GetTimeUnit(const GetTimeUnit&) = default;
			~GetTimeUnit();
			GetTimeUnit&	operator= (const GetTimeUnit&) = default;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const GetTimeUnit&);
}
#endif

