//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Advance.hpp"
#include "Player.hpp"

namespace Zappy {

  Advance::Advance(GameEngine * trantor, Client * c):
    ClientCommand(trantor, c, "advance", 7) {
    // TODO (default constructor)
  }

  Advance::~Advance() {
    // std::cout << "Advance" << " destroyed" << std::endl;
  }

  void  Advance::execute() {
    ClientCommand::execute();
    Player * p = dynamic_cast<Player *>(client_);
    p->advance();
  }

  bool  Advance::is_valid() const { return (true); }


  std::ostream& operator<<(std::ostream& s, const Advance& param) {
    s << (Command &)param;
    return (s);
  }
}

