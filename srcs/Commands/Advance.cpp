//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Player.hpp"
#include "Commands/Advance.hpp"

namespace Zappy {

  Advance::Advance(GameEngine *trantor, Player *p):
    ClientCommand(trantor, "advance", 7), player_(p) {
    // TODO (default constructor)
  }

  Advance::~Advance() {
    // std::cout << "Advance" << " destroyed" << std::endl;
  }

  void  Advance::execute() {
    ClientCommand::execute();
    player_->advance();
    player_->get_client()->broadcast("OK:advance");
  }

  void  Advance::broadcast() const {
    trantor_->broadcast_spectators(player_->get_ppo());
  }

  bool  Advance::is_valid() const { return (true); }

  const std::string Advance::cmd_error() const {
    return ClientCommand::cmd_error();
  }


  std::ostream& operator<<(std::ostream& s, const Advance& param) {
    s << (Command &)param;
    return (s);
  }
}

