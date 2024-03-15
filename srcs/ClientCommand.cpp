//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "ClientCommand.hpp"
#include "Commands/Advance.hpp"
#include "Commands/Right.hpp"
#include "Commands/Left.hpp"
#include "Commands/MapSize.hpp"

namespace Zappy {

  ClientCommand::ClientCommand(GameEngine *trantor, const std::string cmd, int frames_cost):
    Command(cmd, trantor), trantor_(trantor), executed_at_frame_(-1), executed_(false), frames_cost_(frames_cost) {
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
    if (c->get_client_type() == Client::ClientType::Player) {
      Player & p = *(dynamic_cast<Player *>(c));
      if (cmd == "advance") {
        return new Advance(trantor, p);
      } else if (cmd == "right") {
        return new Right(trantor, p);
      } else if (cmd == "left") {
        return new Left(trantor, p);
      }
      // } else if (cmd == "clear") {
      //  return new ClientCommand();
      // } else if (cmd == "players") {
      //  return new ClientCommand();
      // } else if (cmd == "lang") {
      //  return new ClientCommand(options);
      // }
    } else if (c->get_client_type() == Client::ClientType::Spectator) {
      Spectator & s = *(dynamic_cast<Spectator *>(c));
      if (cmd == "msz") {
        return new MapSize(trantor, s);
      }
    }
    return (new ClientCommand(trantor, cmd, 0));
  }
}




// List of commands:
/**
 * Protocole d’échange Serveur / Moniteur Graphique
 * Projet Zappy
 * - 2 -
 * Tableau des commandes et symboles associés
 * Serveur Moniteur Détails
 * "msz X Y\n" "msz\n" Taille de la carte.
 * "bct X Y q q q q q q q\n" "bct X Y\n" Contenu d’une case de la carte.
 * "bct X Y q q q q q q q\n" *
 * nbr_cases "mct\n" Contenu de la carte (toutes les cases).
 * "tna N\n" * nbr_equipes "tna\n" Nom des équipes.
 * "pnw #n X Y O L N\n" - Connexion d’un nouveau joueur.
 * "ppo #n X Y O\n" "ppo #n\n" Position d’un joueur.
 * "plv #n L\n" "plv #n\n" Niveau d’un joueur.
 * "pin #n X Y q q q q q q q\n" "pin #n\n" Inventaire d’un joueur.
 **/

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
