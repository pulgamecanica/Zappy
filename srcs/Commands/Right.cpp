//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Player.hpp"
#include "Commands/Right.hpp"

namespace Zappy {


  Right::Right(GameEngine * trantor, Player &p):
    ClientCommand(trantor, "right", 7), player_(p) {  
  }

  Right::~Right() {
  }

  std::ostream& operator<<(std::ostream& s, const Right& param) {
    (void)param;
    return (s);
  }

  bool  Right::is_valid() const { return (true); };

  void  Right::execute() {
    ClientCommand::execute();
    player_.move_right();
    player_.broadcast("OK:right");
  };
}
