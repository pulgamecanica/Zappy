//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "ClientCommand.hpp"
#include "PlayerClientCommand.hpp"
#include "SpectatorClientCommand.hpp"
#include "Commands/PlayerClientCommands/Join.hpp"

namespace Zappy {
  ///////////////////////////////// STATIC PUBLIC METHODS /////////////////////////////////////////
  ClientCommand* ClientCommand::parse_command(GameEngine *trantor, Client *c,
                                                const std::string &msg) {
    ClientCommand* cc(nullptr);
    const std::string cmd(msg.substr(0, msg.find_first_of(" \n")));
    std::vector<std::string> options = Command::get_options(msg.substr(cmd.length()));
    
    if (c->check_client_type(Client::ClientType::SpectatorT)) {
      cc = SpectatorClientCommand::parse_command(trantor, c, cmd, options); //  In the future, use line instead of msg
    } else if (c->check_client_type(Client::ClientType::PlayerT)) {
      if (!c->joined()) {
        return new Join(trantor, *c, msg.substr(0, msg.find_first_of("\n")));
      }
      cc = PlayerClientCommand::parse_command(trantor, c->get_player(), cmd, options);
    }
    if (cc)
      return cc;
    return (new ClientCommand(trantor, cmd, 0, Command::Error::CommandNotFound));
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  ClientCommand::ClientCommand(GameEngine *trantor, const std::string cmd, int frames_cost, Command::Error e):
    Command(cmd, trantor, e), executed_at_frame_(-1),
    executed_(false), frames_cost_(frames_cost) {
    // Check if the command exists
    // if (cmd != "join" && !spectatorsCommandFactoryMap.count(cmd)
    //   && !playersCommandFactoryMap.count(cmd))
    //   error_ = Command::CommandNotFound;
  }

  ClientCommand::~ClientCommand() {
    ;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  const std::string ClientCommand::cmd_error() const {
    std::string msg;
    
    msg.append(UNKOWN_CMD_MSG);
    if (DEBUG) {
      msg.append(" `");
      msg.append(get_cmd());
      msg.append("` (server unkown command)");
    }
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
  /////////////////////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////// PUBLIC VIRTUAL METHODS ///////////////////////////////////////
  void  ClientCommand::execute() {
    executed_ = true;
    executed_at_frame_ = trantor_->frame();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////// PUBLIC VIRTUAL MEMBERS ///////////////////////////////////////
  const std::string ClientCommand::BAD_PARAMS_MSG = "sbp";
  const std::string ClientCommand::UNKOWN_CMD_MSG = "suc";
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
 * 
 * [0  %] - DONE [ "msz X Y\n", "msz\n", Taille de la carte. ]
 * [3  %] - DONE [ "bct X Y q q q q q q q\n", "bct X Y\n", Contenu d’une case de la carte. ]
 * [7  %] - DONE [ "bct X Y q q q q q q q\n" * nbr_cases, "mct\n", Contenu de la carte (toutes les cases). ]
 * [11 %] - DONE [ "tna N\n" * nbr_equipes, "tna\n", Nom des équipes. ]
 * [15 %] - DONE [ "pnw #n X Y O L N",  -,  Connexion d’un nouveau joueur. ]
 * [19 %] - DONE [ "ppo #n X Y O", "ppo #n", Position d’un joueur. ]
 * [23 %] - DONE [ "plv #n L", "plv #n", Niveau d’un joueur. ]
 * [26 %] - DONE [ "sgt T", "sgt", Demande de l’unité de temps courante sur le serveur. ]
 * [30 %] - DONE [ "sgt T", "sst T", Modification de l’unité de temps sur le serveur. ]
 * [34 %] - DONE "suc\n" - Commande inconnue. 
 * [38 %] - DONE "sbp\n" - Mauvais paramètres pour la commande.
 * [42 %] "pin #n X Y q q q q q q q\n" "pin #n\n" Inventaire d’un joueur.
 * [46 %] "pex #n\n" - Un joueur expulse. 
 * [50 %] "pbc #n M\n" - Un joueur fait un broadcast.
 * [53 %] "pic X Y L #n #n …\n" - Premier joueur lance l’incantation pour tous les suivants sur la case.
 * [57 %] "pie X Y R\n" - Fin de l’incantation sur la case donnée avec le résultat R (0 ou 1).
 * [61 %] "pfk #n\n" - Le joueur pond un œuf.
 * [65 %] "pdr #n i\n" - Le joueur jette une ressource.
 * [69 %] "pgt #n i\n" - Le joueur prend une ressource.
 * [73 %] "pdi #n\n" - Le joueur est mort de faim. 
 * [76 %] "enw #e #n X Y\n" - L’œuf a été pondu sur la case par le joueur. 
 * [80 %] "eht #e\n" - L’œuf éclot. 
 * [84 %] "ebo #e\n" - Un joueur s’est connecté pour l’œuf. 
 * [88 %] "edi #e\n" - L’œuf éclos est mort de faim. 
 * [92 %] "seg N\n" - Fin du jeu. L’équipe donnée remporte la partie. 
 * [100%] "smg M\n" - Message du serveur. 
 * 
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
