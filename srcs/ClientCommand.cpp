//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "ClientCommand.hpp"
#include "Advance.hpp"
#include "Right.hpp"
#include "Left.hpp"

namespace Zappy {

  ClientCommand::ClientCommand(GameEngine *trantor, Client * c, const std::string cmd, int frames_cost):
    Command(cmd, trantor), trantor_(trantor), client_(c), executed_at_frame_(-1), executed_(false), frames_cost_(frames_cost) {
  }

  ClientCommand::~ClientCommand() {}

  bool ClientCommand::expired() const {
    if (!was_executed())
      return false ;
    if (executed_at_frame_ == -1)
      throw std::runtime_error("Something went wrong... command was not properly handled/executed");
    return (executed_at_frame_ + frames_cost_ <= trantor_->frame());
  }

  void  ClientCommand::execute() {
    executed_ = true;
    executed_at_frame_ = trantor_->frame();
    client_->broadcast("OK\n");
  }

  bool ClientCommand::is_valid() const { return (false); }

  int ClientCommand::get_cost() const { return (frames_cost_); }

  bool ClientCommand::was_executed() const { return (executed_); }

  std::ostream& operator<<(std::ostream& s, const ClientCommand& cc) {
    s << (Command &)cc;
    return (s);
  }

  ClientCommand* ClientCommand::parse_command(GameEngine *trantor, Client *c, const std::string &msg) {
    const std::string cmd = msg.substr(0, msg.find_first_of(" \n"));
    // std::vector<std::string> options;

    // options = get_options(msg.substr(cmd.length()));
    if (cmd == "advance") {
      return new Advance(trantor, c);
    } else if (cmd == "right") {
     return new Right(trantor, c);
    } else if (cmd == "left") {
     return new Left(trantor, c);
    }
    // } else if (cmd == "clear") {
    //  return new ClientCommand();
    // } else if (cmd == "players") {
    //  return new ClientCommand();
    // } else if (cmd == "lang") {
    //  return new ClientCommand(options);
    // }
    return (new ClientCommand(trantor, c, cmd, 0));
  }
}

// List of commands:
/**
 * advance one square avance 7/t ok
 * turn right 90 degrees droite 7/t ok
 * turn left 90 degrees gauche 7/t ok
 * see voir 7/t {case1, case2, ...}
 * inventory inventaire 1/t {phiras n, sibur n, ...}
 * take an object prend <object> 7/t ok/ko
 * put down an object pose <object> 7/t ok/ko
 * kick the players from the square expulse 7/t ok/ko
 * broadcast broadcast <text> 7/t ok
 * begin the incantation incantation 300/t elevation en cours
 * niveau actuel : K
 * fork a player fork 42/t ok
 * know the number of unused connect_nbr 0/t value
 * connections by the team
 * death of a player - - mort
 **/
