//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Left.hpp"
#include "Player.hpp"

namespace Zappy {

  Left::Left(GameEngine * trantor, Client * c): 
      ClientCommand(trantor, c, "left", 7) {
  }

  Left::~Left() {
  }

  bool  Left::is_valid() const { return (true); }

  void  Left::execute() {
    ClientCommand::execute();
    Player * p = dynamic_cast<Player *>(client_);
    p->move_left();
  }


  std::ostream& operator<<(std::ostream& s, const Left& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }

}

