//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/PlayerClientCommands/Left.hpp"
#include "Player.hpp"

namespace Zappy {

  Left::Left(GameEngine *trantor, Player *p): 
      PlayerClientCommand(trantor, "left", 7), player_(p) {
  }

  Left::~Left() {
  }

  bool  Left::is_valid() const { return (true); }

  void  Left::execute() {
    ClientCommand::execute();
    player_->move_left();
    player_->get_client()->broadcast("OK:left");
  }

  void  Left::broadcast() const {
    trantor_->broadcast_spectators(player_->get_ppo());
  }

  const std::string Left::cmd_error() const {
    return ("Error");
  }

  std::ostream& operator<<(std::ostream& s, const Left& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }

}

