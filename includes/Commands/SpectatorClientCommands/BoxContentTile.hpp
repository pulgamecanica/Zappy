//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __BOXCONTENTTILE_HPP__
# define __BOXCONTENTTILE_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
	class BoxContentTile: public SpectatorClientCommand {
		public:
      // CONSTRUCTORS & DESTRUCTORS //
			BoxContentTile(GameEngine *trantor, Spectator& spect, std::vector<std::string>& options);
			BoxContentTile(const BoxContentTile&) = delete;
			BoxContentTile&	operator= (const BoxContentTile&) = delete;
			~BoxContentTile();
      // PUBLIC INHERITED VIRTUAL METHODS //
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			Point * pos_;
	};

	std::ostream&	operator<<(std::ostream&, const BoxContentTile&);
}
#endif

