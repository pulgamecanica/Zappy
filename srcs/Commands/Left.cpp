//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Player.hpp"
#include "Commands/Left.hpp"

namespace Zappy {

  Left::Left(GameEngine * trantor, Player &p): 
      ClientCommand(trantor, "left", 7), player_(p) {
  }

  Left::~Left() {
  }

  bool  Left::is_valid() const { return (true); }

  void  Left::execute() {
    ClientCommand::execute();
    player_.move_left();
    player_.broadcast("OK:left");
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

