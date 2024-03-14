//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Right.hpp"
#include "Player.hpp"

namespace Zappy {


  Right::Right(GameEngine * trantor, Client * c):
    ClientCommand(trantor, c, "right", 7) {  
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
    Player * p = dynamic_cast<Player *>(client_);
    p->move_right();
  };
}
