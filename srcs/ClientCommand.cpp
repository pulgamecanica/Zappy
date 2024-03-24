//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "ClientCommand.hpp"
#include "Commands/Advance.hpp"
#include "Commands/Right.hpp"
#include "Commands/Left.hpp"
#include "Commands/MapSize.hpp"
#include "Commands/Join.hpp"
#include "Commands/BlockContentTile.hpp"
#include "Commands/MapContentTile.hpp"
#include "Commands/TeamsNames.hpp"
#include "Commands/PlayerPosition.hpp"

namespace Zappy {
  ///////////////////////////////// STATIC PUBLIC METHODS /////////////////////////////////////////
  ClientCommand* ClientCommand::parse_command(GameEngine *trantor, Client *c,
                                                const std::string &msg) {
    std::vector<std::string> options;
    const std::string cmd(msg.substr(0, msg.find_first_of(" \n")));

    options = Command::get_options(msg.substr(cmd.length()));
    if (c->get_client_type() == Client::ClientType::PlayerT) {
      if (!c->joined()) {
        return new Join(trantor, *c, msg.substr(0, msg.find_first_of("\n")));
      } else { // Joined ... //
        if (cmd == "advance") {
          return new Advance(trantor, c->get_player());
        } else if (cmd == "right") {
          return new Right(trantor, c->get_player());
        } else if (cmd == "left") {
          return new Left(trantor, c->get_player());
        }
      }
    } else if (c->get_client_type() == Client::ClientType::SpectatorT) {
      Spectator & s = *(dynamic_cast<Spectator *>(c));
      if (cmd == "msz") {
        return new MapSize(trantor, s);
      } else if (cmd == "bct") {
        return new BlockContentTile(trantor, s, options);
      } else if (cmd == "mct") {
        return new MapContentTile(trantor, s);
      } else if (cmd == "tna") {
        return new TeamsNames(trantor, s);
      } else if (cmd == "ppo") {
        return new PlayerPosition(trantor, s, options);
      }
    }
    return (new ClientCommand(trantor, cmd, 0));
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  ClientCommand::ClientCommand(GameEngine *trantor, const std::string cmd, int frames_cost):
    Command(cmd, trantor), trantor_(trantor), executed_at_frame_(-1),
    executed_(false), frames_cost_(frames_cost) {
  }

  ClientCommand::~ClientCommand() {
    ;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  const std::string ClientCommand::cmd_error() const {
    std::string msg;

    msg.append(get_cmd());
    msg.append(":is not a valid command");
    return (msg);
  }

  bool ClientCommand::expired() const {
    if (!was_executed())
      return false ;
    if (executed_at_frame_ == -1)
      throw std::runtime_error("Something went wrong command was not properly handled/executed");
    return (executed_at_frame_ + frames_cost_ <= trantor_->frame());
  }

  bool ClientCommand::was_executed() const {
    return (executed_);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////// CONST PUBLIC VIRTUAL METHODS ////////////////////////////////////
  void  ClientCommand::broadcast() const {
    ;
    // throw std::runtime_error("Cannot broadcast a generic ClientCommand!");
  }

  int ClientCommand::get_cost() const {
    return (frames_cost_);
  }

  bool ClientCommand::is_valid() const {
    return (false);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////// PUBLIC VIRTUAL METHODS ///////////////////////////////////////
  void  ClientCommand::execute() {
    executed_ = true;
    executed_at_frame_ = trantor_->frame();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const ClientCommand& cc) {
    s << (Command &)cc;
    return (s);
  }
}

// List of commands:
/**
 * Protocole d’échange Serveur / Moniteur Graphique
 * Projet Zappy
 * - 2 -
 * Tableau des commandes et symboles associés
 * Serveur Moniteur Détails
 * - DONE [ "msz X Y\n", "msz\n", Taille de la carte. ]
 * - DONE [ "bct X Y q q q q q q q\n", "bct X Y\n", Contenu d’une case de la carte. ]
 * - DONE [ "bct X Y q q q q q q q\n" * nbr_cases, "mct\n", Contenu de la carte (toutes les cases). ]
 * - DONE [ "tna N\n" * nbr_equipes, "tna\n", Nom des équipes. ]
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
