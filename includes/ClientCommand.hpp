//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLIENTCOMMAND_HPP__
# define __CLIENTCOMMAND_HPP__

#include <iostream>
#include <functional>

#include "GameEngine.hpp"
#include "Command.hpp"
#include "Client.hpp"
#include "Spectator.hpp"
#include "Player.hpp"

namespace Zappy {

  class ClientCommand: public Command {// virtual inheritance because I want to also check the middle class (ClientCommand)
    public:
      // TYPE ALIASES DECLARATIONS //
      // STATIC PUBLIC METHODS //
      static ClientCommand* parse_command(GameEngine *trantor, Client *c, const std::string &msg);
      // CONSTRUCTORS & DESTRUCTORS //
      ClientCommand(const ClientCommand&) = default;
      ClientCommand& operator= (const ClientCommand&) = default;
      virtual ~ClientCommand();
      // CONST PUBLIC METHODS //
      int                       get_cost() const;
      bool                      expired() const;
      bool                      was_executed() const;
      // CONST PUBLIC VIRTUAL METHODS //
      virtual void              broadcast() const;
      virtual const std::string cmd_error() const;
      // PUBLIC VIRTUAL METHODS //
      virtual void              execute();
    protected:
      // PROTECTED CONSTRUCTORS (DISABLED PUBLICLY) //
      ClientCommand(GameEngine *trantor, const std::string cmd, int time_cost, Command::Error e = Command::Error::NoError);
      // STATIC CONST PROTECTED MEMBERS //
      static const std::string BAD_PARAMS_MSG;
      static const std::string UNKOWN_CMD_MSG;
      // PROTECTED MEMBERS //
      // GameEngine          *trantor_;
      ssize_t             executed_at_frame_;
    private:
      // CONST PRIVATE MEMBERS //
      bool                executed_;
      const int           frames_cost_;
  };

  std::ostream& operator<<(std::ostream&, const ClientCommand&);
}
#endif
