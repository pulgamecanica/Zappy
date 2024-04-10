//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAPSIZE_HPP__
# define __MAPSIZE_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"

namespace Zappy {

	class MapSize: public SpectatorClientCommand {
		public:
		  MapSize(GameEngine * trantor, Spectator & spectator);
			MapSize(const MapSize&) = default;
			~MapSize();
			MapSize&	operator= (const MapSize&) = default; // const for safety... not super nesessary
			bool  is_valid() const;
      void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const MapSize&);
}
#endif

