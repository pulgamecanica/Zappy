//***************************//
//*Template by pulgamecanica*//
//***************************//

/**
 * Clients can send commands to the server, any commands
 * The server is in charge of validating the client commands
 * A command might or might not have a reply
 * Clients can receive messages from the server without warning
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
      static constexpr const char * CLIENT_TYPES_STR[4] = {"Player", "Spectator", "Graphic", "Error"};
      enum ClientType {
        PlayerT,
        SpectatorT,
        ErrorT
      };
      // CONSTRUCTORS & DESTRUCTORS
      Client(int fd, ClientType type);
      Client(const Client&) = default;
      virtual ~Client();
      Client&         operator= (const Client&) = default; // const for safety... not super nesessary
      // CONST PUBLIC METHODS
      enum ClientType get_client_type() const;
      bool            check_client_type(enum ClientType) const;
      int             get_fd() const;
      bool            joined() const;
      ssize_t         uptime() const; // In miliseconds (ms)
      // PUBLIC METHODS
      void            broadcast(std::string msg);
      void            update();
      void            queue_cmd(ClientCommand * cmd);
      void            assign_player(Player * player);
      void            dismiss_player();
      Player          *player_; // I don't like this, spectators should not inherit this...
    protected:
      // STATIC PROTECTED CONST MEMBERS
      static const int QUEUE_SIZE = 8;
      // CONST PROTECTED MEMBERS
      const int                     fd_;
      // PROTECTED MEMBERS
      enum ClientType               client_type_;
      ssize_t                       created_at_ms_;
      std::vector<ClientCommand *>  cmd_queue_;
    private:
      // PRIVATE MEMBERS
    // Will concider having this separated...
  };

  std::ostream& operator<<(std::ostream&, const Client&);
}
#endif

