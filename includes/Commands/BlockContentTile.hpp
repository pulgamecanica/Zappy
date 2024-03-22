//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __BLOCKCONTENTTILE_HPP__
# define __BLOCKCONTENTTILE_HPP__

#include <iostream>

#include "Spectator.hpp"
#include "ClientCommand.hpp"
#include "Geometry/Point.hpp"

namespace Zappy {
	class BlockContentTile: public ClientCommand {
		public:
			BlockContentTile(GameEngine *trantor, Spectator& spectator, std::vector<std::string>& options);
			BlockContentTile(const BlockContentTile&) = default;
			~BlockContentTile();
			BlockContentTile&	operator= (const BlockContentTile&) = default; // const for safety... not super nesessary
			bool  is_valid() const;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
			bool bad_params_;
			Point * pos_;
	};

	std::ostream&	operator<<(std::ostream&, const BlockContentTile&);
}
#endif

