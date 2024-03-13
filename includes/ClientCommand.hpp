//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLIENTCOMMAND_HPP__
# define __CLIENTCOMMAND_HPP__

#include <iostream>

#include "GameEngine.hpp"
#include "Command.hpp"
#include "Client.hpp"

namespace Zappy {

  class ClientCommand: public Command {
    public:
      static ClientCommand* parse_command(GameEngine *trantor, Client * c, const std::string &msg);
      
      // CONSTRUCTORS
      ClientCommand(const ClientCommand&) = default;
      virtual ~ClientCommand();

      // MEMBER FUNCTIONS
      ClientCommand&  operator= (const ClientCommand&) = default;
      int             get_cost() const;
      bool            was_executed() const;
      bool            expired() const;
      
      // VIRTUAL MEMBER FUNCTIONS(Inherited will prioritize)
      bool            is_valid() const;
      void            execute();
    protected:
      ClientCommand(GameEngine *trantor, Client *c, const std::string cmd, int time_cost);
      GameEngine          *trantor_;
      Client              *client_;
      ssize_t             executed_at_frame_;
    private:
      bool                executed_;
      const int           frames_cost_;
  };

  std::ostream& operator<<(std::ostream&, const ClientCommand&);
}
#endif

