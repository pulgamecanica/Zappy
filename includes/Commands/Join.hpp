//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __JOIN_HPP__
# define __JOIN_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "GameEngine.hpp"
#include "Client.hpp"

namespace Zappy {
	class Join: public ClientCommand {
		public:
	    Join(GameEngine *trantor, Client &c, std::string team);
			Join(const Join&) = delete;
			~Join();
			Join&	operator= (const Join&) = delete; // const for safety... not super nesessary
			bool	is_valid() const;
	    void	execute();
      const std::string cmd_error() const;
	  private:
			Client			&client_;
			std::string team_;
			bool team_is_valid_;
	};

	std::ostream&	operator<<(std::ostream&, const Join&);
}
#endif

