//***************************//
//*Template by pulgamecanica*//
//***************************//

// #include "Commands/PlayerClientCommands/Advance.hpp"
#include "Commands/PlayerClientCommands/Advance.hpp"
#include "Player.hpp"

namespace Zappy {

  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  Advance::Advance(GameEngine *trantor, Player *p):
    PlayerClientCommand(trantor, "advance", 7), player_(p) {
  }

  Advance::~Advance() {
    ;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////// PUBLIC INHERITED VIRTUAL METHODS //////////////////////////////////
  void  Advance::execute() {
    ClientCommand::execute();
    // Make sure the player was able to advance? Why would it not be possible?
    player_->advance();
    player_->get_client()->broadcast("OK:advance");
  }

  void  Advance::broadcast() const {
    trantor_->broadcast_spectators(player_->get_ppo());
  }

  const std::string Advance::cmd_error() const {
    return ClientCommand::cmd_error();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const Advance& param) {
    s << (Command &)param;
    return (s);
  }
}

