//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SERVER_HPP__
# define __SERVER_HPP__

extern "C" {
  #include <sys/time.h>
  #include <sys/socket.h>
  #include <sys/epoll.h>
  #include <netinet/in.h>
} 

#include <iostream>
#include <vector>
#include <map>

#include "Config.hpp"

namespace Zappy {
  class GameEngine;
  class Client;

  class Server {
    protected:
      // PROTECTED CONSTRUCTOR //
      Server(GameEngine *trantor, std::string toml_file, std::string default_lang,
        int players_port, int spectators_port, int timeout);
    public:
      static const std::string  VERSION;
      enum ServerHealth
      {
        Booting,
        Running,
        EndOfLife
      };
      // CONSTRUCTORS & DESTRUCTORS //
      Server(const Server&) = delete;
      ~Server();
      Server&                         operator= (const Server&) = delete;
      // CONST PUBLIC METHODS //
      ssize_t                         current_timestamp() const;
      const std::map<int, Client *>   &get_clients() const;
      const Config &                  get_config() const; 
      const std::string               get_creation_date() const;
      const std::vector<std::string>  get_list_of_supported_languages() const;
      int                             total_players() const; 
      int                             total_spectators() const;
      // PUBLIC METHODS //
      void                            broadcast_spectators(const std::string& msg);
      void                            set_config(const std::string lang_acronym);
      void                            stop_server();
    protected:
      // CONST PROTECTED METHODS //
      bool    check_health(enum ServerHealth check) const;
      // PROTECTED METHODS //
      void    update();
      // PROTECTED MEMBERS //
      ssize_t created_at_ms_;
    private:
      // STATIC PRIVATE CONST MEMBERS //
      static constexpr int          MAX_EPOLL_EVENTS = 64;
      static constexpr int          BACKLOG = 10;
      static constexpr int          RECV_BUFFER = 1024;
      // PRIVATE METHODS //
      int               accept_client(int socket);
      void              add_client(int socket, int fd);
      void              handle_client(int fd, const std::string & msg);
      const std::string handle_client_input_or_disconnect(int fd);
      const std::string get_spectator_welcome_msg();
      void              handle_stdin(const std::string & cmd);
      void              add_command_to_history(const std::string cmd);
      bool              is_client(int fd);
      bool              is_server_socket(int fd);
      bool              is_stdin(int fd);
      void              remove_client(int fd);
      void              remove_client_immediately(int fd);
      // PRIVATE CONST MEMBERS //
      const int connection_timeout_; // Players will time out after X miliseconds, spectators never timeout
      const int players_port_;
      const int spectators_port_;
      // PRIVATE MEMBERS //
      std::map<int, Client *>   clients_;
      std::vector<Config>       configs_;
      Config                    *curr_config_;
      int                       epoll_fd_;
      struct epoll_event        events_[MAX_EPOLL_EVENTS];
      enum ServerHealth         health_;
      int                       players_socket_;
      sockaddr_in               players_sockaddr_; // `man 7 ip` to see sockaddr_in struct
      GameEngine                *trantor_;
      sockaddr_in               spectators_sockaddr_; // `man 7 ip` to see sockaddr_in struct
      int                       spectators_socket_;
      std::vector<int>          clients_to_remove_;
      std::vector<std::string>  commands_history_;
      std::string               commands_history_string_;
  };
  std::ostream& operator<<(std::ostream&, const Server&);
}

#endif
