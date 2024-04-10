//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SETTIMEUNIT_HPP__
# define __SETTIMEUNIT_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"
#include "GameEngine.hpp"

namespace Zappy {
	class SetTimeUnit: public SpectatorClientCommand {
		public:
			SetTimeUnit(GameEngine * trantor, Spectator & spectator, std::vector<std::string>& options);
			SetTimeUnit(const SetTimeUnit&) = default;
			~SetTimeUnit();
			SetTimeUnit&	operator= (const SetTimeUnit&) = default;
			bool  is_valid() const;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator&	spectator_;
			bool 				bad_params_;
			int					time_unit;
	};

	std::ostream&	operator<<(std::ostream&, const SetTimeUnit&);
}
#endif

