//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAPCONTENTTILE_HPP__
# define __MAPCONTENTTILE_HPP__

#include <iostream>

#include "Spectator.hpp"
#include "ClientCommand.hpp"

namespace Zappy {
	class MapContentTile: public ClientCommand {
		public:
			MapContentTile(GameEngine *trantor, Spectator& spectator);
			MapContentTile(const MapContentTile&) = default;
			~MapContentTile();
			MapContentTile&	operator= (const MapContentTile&) = default;
			bool  is_valid() const;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const MapContentTile&);
}

#endif

