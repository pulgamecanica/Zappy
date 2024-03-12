//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLIENTCOMMAND_HPP__
# define __CLIENTCOMMAND_HPP__

#include <iostream>

#include "GameEngine.hpp"
#include "Command.hpp"

namespace Zappy {

	class ClientCommand: public Command {
		public:
			static ClientCommand* parse_command(GameEngine *trantor, const std::string &msg);
			ClientCommand(const ClientCommand&) = default;
			~ClientCommand();
			ClientCommand&	operator= (const ClientCommand&) = default;
			int 						get_cost() const;
			bool 						was_executed() const;
			bool 						expired() const;
			virtual bool		is_valid() const;
		protected:
			ClientCommand(GameEngine *trantor, const std::string cmd, int time_cost);
		private:
			GameEngine 					*trantor_;
			const int						frames_cost_;
			ssize_t							executed_at_frame_;
			bool								executed_;
	};

	std::ostream&	operator<<(std::ostream&, const ClientCommand&);
}
#endif

