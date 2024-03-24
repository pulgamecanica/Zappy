//***************************//
//*Template by pulgamecanica*//
//***************************//

/**
 * Clients 
 *  - Can send commands to the server, any commands
 *  - The server is in charge of validating the client commands
 *  - A command might or might not have a reply
 *  - Clients can receive messages from the server without warning
 *  - Clients can join through 2 different ports
 *  - One port allows Clients to spectate
 *  - Another port allow Players to join a Team and controll a Player
 **/
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

extern "C" {
  #include <sys/time.h>
}

#include <vector>
#include <iostream>

namespace Zappy {
  class ClientCommand;
  class Player;

  class Client {
    public:
      // STATIC PUBLIC CONST MEMBERS //
      static constexpr const char * CLIENT_TYPES_STR[4] = {
        "Player",
        "Spectator",
        "Graphic",
        "Error"
      };
      // NESTED ENUM MEMBER //
      enum ClientType {
        PlayerT,
        SpectatorT,
        ErrorT
      };
      // CONSTRUCTORS & DESTRUCTORS //
      Client(int fd, ClientType type);
      Client(const Client&) = default;
      Client& operator=(const Client&) = default;
      virtual ~Client();
      // CONST PUBLIC METHODS //
      bool            check_client_type(enum ClientType) const;
      enum ClientType get_client_type() const;
      int             get_fd() const;
      Player*         get_player() const;
      bool            joined() const;
      ssize_t         uptime() const; // In miliseconds (ms)
      // PUBLIC METHODS //
      void            assign_player(Player * player);
      void            broadcast(std::string msg, bool new_line = true);
      void            dismiss_player();
      void            queue_cmd(ClientCommand * cmd);
      void            update();
    protected:
      Player                        *player_;
      // STATIC PROTECTED CONST MEMBERS //
      static const int              QUEUE_SIZE = 8;
      // CONST PROTECTED MEMBERS //
      const int                     fd_;
      // PROTECTED MEMBERS //
      enum ClientType               client_type_;
      ssize_t                       created_at_ms_;
      std::vector<ClientCommand *>  cmd_queue_;
  };

  std::ostream& operator<<(std::ostream&, const Client&);
}
#endif

