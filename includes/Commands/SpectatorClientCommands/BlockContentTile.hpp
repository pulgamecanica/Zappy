//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __BLOCKCONTENTTILE_HPP__
# define __BLOCKCONTENTTILE_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
	class BlockContentTile: public SpectatorClientCommand {
		public:
      // CONSTRUCTORS & DESTRUCTORS //
			BlockContentTile(GameEngine *trantor, Spectator& spect, std::vector<std::string>& options);
			BlockContentTile(const BlockContentTile&) = delete;
			BlockContentTile&	operator= (const BlockContentTile&) = delete;
			~BlockContentTile();
      // PUBLIC INHERITED VIRTUAL METHODS //
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			Point * pos_;
	};

	std::ostream&	operator<<(std::ostream&, const BlockContentTile&);
}
#endif

