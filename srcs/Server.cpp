//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
  #include <strings.h>
}

#include <algorithm>

#include <toml++/toml.hpp>

#include "Zappy.inc"

#include "Player.hpp"
#include "Spectator.hpp"
#include "Server.hpp"
#include "ServerCommand.hpp"
#include "ClientCommand.hpp"
#include "GameEngine.hpp"
#include "Client.hpp"

namespace Zappy {
  const std::string  Server::VERSION = "42.0";
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  Server::Server(
    GameEngine *trantor,
    std::string toml_file,
    std::string default_lang,
    int players_port,
    int spectators_port,
    int timeout):
      connection_timeout_(timeout), 
      players_port_(players_port), spectators_port_(spectators_port), health_(Booting),
      trantor_(trantor) {
    /* Setup TOML configuration file */
    {
      toml::table tbl = toml::parse_file(toml_file);
      /* Setup configuration for all the languages */
      auto toml_langs = tbl["languages"];
      if (toml::array* arr = toml_langs.as_array())
      {
          /* visitation with for_each() helps deal with heterogeneous data */
          arr->for_each([&](auto&& el)
          {
              if constexpr (toml::is_string<decltype(el)>) {
                if (DEBUG)
                  std::cout << "Loading " << BLUE << *el << ENDC << " configuration" << std::endl;
                configs_.push_back(Config(tbl, *el));
              } else {
                throw std::runtime_error("Error: languages can only contain strings");
              }
          });
      } else {
        throw std::runtime_error("Error: languages is not defined or is not an array");
      }
      /* Check that default language is included */
      std::vector<Config>::iterator it = std::find(configs_.begin(), configs_.end(), default_lang);
      if (it == std::end(configs_))
        throw std::runtime_error("Error: default language is not included in the toml file");
      curr_config_ = &(*it);
    }
    std::cout << YELLOW << "=> Booting Zappy in " << (DEBUG ? "debug" : "development") <<
      " mode" << ENDC << std::endl;
    std::cout << YELLOW << "=> ZappyServer version: " << GREEN << Server::VERSION <<
      ENDC << std::endl;
    std::cout << YELLOW << "=> Run `./Zappy --help` for more startup options" <<
      ENDC << std::endl;
    /* Create players & spectators sockets (IPV4, TCP | man socket) */
    players_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (players_socket_ == -1) {
      throw std::runtime_error(std::string("players socket()") + std::string(strerror(errno)));
    }
    spectators_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (spectators_socket_ == -1) {
      throw std::runtime_error(std::string("spectators socket()") + std::string(strerror(errno)));
    }
    /* Set sockets to reusable (avoid port binding lag) (man 7 setsockopt & man 7 socket) */
    int enable = 1;
    if (setsockopt(players_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
      throw std::runtime_error(std::string("players setsockopt()") + std::string(strerror(errno)));
    }
    if (setsockopt(spectators_socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) {
      throw std::runtime_error(
        std::string("spectators setsockopt()") + std::string(strerror(errno)));
    }
    /* Set socket to non blocking */
    setnonblocking(players_socket_);
    setnonblocking(spectators_socket_);
    /* Bind sockets, to port and 0.0.0.0 (localhost) */
    players_sockaddr_.sin_family = AF_INET;
    players_sockaddr_.sin_port = htons(players_port_);
    players_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(players_socket_, (struct sockaddr *)&players_sockaddr_,
      sizeof(players_sockaddr_)) == -1) {
      throw std::runtime_error(std::string("players bind()") + std::string(strerror(errno)));
    }
    spectators_sockaddr_.sin_family = AF_INET;
    spectators_sockaddr_.sin_port = htons(spectators_port_);
    spectators_sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(spectators_socket_, (struct sockaddr *)&spectators_sockaddr_,
      sizeof(spectators_sockaddr_)) == -1) {
      throw std::runtime_error(std::string("spectators bind()") + std::string(strerror(errno)));
    }
    /* Setup Listen sockets */
    if (listen(players_socket_, Server::BACKLOG) == -1) {
      throw std::runtime_error(std::string("players listen()") + std::string(strerror(errno)));
    }
    if (listen(spectators_socket_, Server::BACKLOG) == -1) {
      throw std::runtime_error(std::string("spectators listen()") + std::string(strerror(errno)));
    }
    std::cout << BLUE << "Zappy listening in single thread mode" << ENDC << std::endl;
    std::cout << BLUE << "* C++ version:\t20" << ENDC << std::endl;
    std::cout << BLUE << "* Server PID:\t" << GREEN << getpid() << ENDC << std::endl;
    /* Epoll setup */
    epoll_fd_ = epoll_create1(0);
    setnonblocking(epoll_fd_);
    /* Add players socket to epoll list */
    {
      struct epoll_event ev;
      ev.events = EPOLLIN | EPOLLET;
      ev.data.fd = players_socket_;
      if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, players_socket_, &ev) == -1) {
        throw std::runtime_error(std::string("epoll_ctl()") + std::string(strerror(errno)));
      }
    }
    /* Add spectators socket to epoll list */
    {
      struct epoll_event ev;
      ev.events = EPOLLIN | EPOLLET;
      ev.data.fd = spectators_socket_;
      if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, spectators_socket_, &ev) == -1) {
        throw std::runtime_error(std::string("epoll_ctl()") + std::string(strerror(errno)));
      }
    }
    /* Add standard input to the epoll list */
    {
      setnonblocking(0);
      struct epoll_event ev;
      ev.events = EPOLLIN | EPOLLET;
      ev.data.fd = 0;
      if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, 0, &ev) == -1) {
        throw std::runtime_error(std::string("epoll_ctl()") + std::string(strerror(errno)));
      }
    }
    /* Setup the timestamp */
    {
      created_at_ms_ = gettimeofday_ms();
    }
    std::cout << BLUE << "* Players:\thttp://host:" << players_port_ << ENDC << std::endl;
    std::cout << BLUE << "* Spectators:\thttp://host:" << spectators_port_<< ENDC << std::endl;
    health_ = Running;
  }

  Server::~Server() {
    close(players_socket_);
    close(spectators_socket_);
    close(epoll_fd_);
    // close all clients and spectators
    // TODO
    for (std::map<int, Client *>::const_iterator i = clients_.begin(); i != clients_.end(); ++i) {
      close(i->first);
      delete i->second;
    }
    clients_.clear();
    configs_.clear();
    health_ = EndOfLife;
    if (DEBUG)
      std::cout << "Server" << " destroyed" << std::endl;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  ssize_t Server::current_timestamp() const {
    return (gettimeofday_ms() - created_at_ms_);
  }

  const std::map<int, Client *> &Server::get_clients() const {
    return (clients_);
  }

  const Config& Server::get_config() const {
    return (*curr_config_);
  } 

  const std::string Server::get_creation_date() const {
    std::string date;

    date = ctime(&created_at_ms_);
    date.pop_back();
    return (date);
  }
  
  const std::vector<std::string> Server::get_list_of_supported_languages() const {
    std::vector<std::string> langs;

    for (std::vector<Config>::const_iterator it = configs_.begin(); it != configs_.end(); ++it) {
      langs.push_back(it->get_language_acronym());
    }
    return (langs);
  }

  int Server::total_players() const {
    int total(0);

    for (std::map<int, Client *>::const_iterator i = clients_.begin(); i != clients_.end(); ++i) {
      if (i->second->check_client_type(Client::ClientType::PlayerT))
        total++;
    }
    return (total);
  }

  int Server::total_spectators() const {
    int total(0);

    for (std::map<int, Client *>::const_iterator i = clients_.begin(); i != clients_.end(); ++i) {
      if (i->second->check_client_type(Client::ClientType::SpectatorT))
        total++;
    }
    return (total);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////// PUBLIC METHODS ///////////////////////////////////////////
  void  Server::broadcast_spectators(const std::string& msg) {
    for (std::map<int, Client *>::iterator i = clients_.begin(); i != clients_.end(); ++i) {
      if (i->second->check_client_type(Client::ClientType::SpectatorT))
        i->second->broadcast(msg);
    }
  }  

  void  Server::set_config(const std::string lang_acronym) {
    std::vector<Config>::iterator it = std::find(configs_.begin(), configs_.end(), lang_acronym);
    if (it == std::end(configs_)) {
      std::cout << RED << "Error" << ENDC << " Couldn't change the configuration '" <<
        lang_acronym << "' is not supported" << std::endl;
    } else {
      curr_config_ = &(*it);
      if (DEBUG) {
        std::cout << YELLOW << "[Server]\t" << GREEN << "Language [" << BLUE << lang_acronym <<
          GREEN << "]" << ENDC << std::endl;
      }
    }
  }

  void  Server::stop_server() {
    health_ = ServerHealth::EndOfLife;
  };
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////// CONST PROTECTED METHODS //////////////////////////////////////
  bool  Server::check_health(enum ServerHealth check) const {
    return (check == health_);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////// PROTECTED METHODS /////////////////////////////////////////
  /**
   * Epoll wait non blocking
   * Check all events (for loop)
   *  If Event
   *   If server socket (some socket waits to be accepted)
   *   If stdin (some command on the server input)
   *   If client (client sent a command or disconnected)
   * Broadcast to all specatators the current state
   **/
  void  Server::update() {
    int nfds;

    nfds = epoll_wait(epoll_fd_, events_, Server::MAX_EPOLL_EVENTS, 0);
    if (nfds == -1)
       throw std::runtime_error(std::string("epoll_wait") + std::string(strerror(errno)));
    for (int n = 0; n < nfds; ++n) {
      if (is_server_socket(events_[n].data.fd)) {
        accept_client(events_[n].data.fd);
      } else { // must be a client (or the server itself: stdin)
        const std::string & client_msg = handle_client_input_or_disconnect(events_[n].data.fd);
        if (client_msg.empty())
          continue ;
        if (is_stdin(events_[n].data.fd))
          handle_stdin(client_msg);
        else if (is_client(events_[n].data.fd))
          handle_client(events_[n].data.fd, client_msg);
      }
    }
    /* Update all clients */
    for (std::map<int, Client *>::iterator i = clients_.begin(); i != clients_.end(); ++i) {
      i->second->update();
      /* Remove innactive players */
      if ((i->second->check_client_type(Client::ClientType::PlayerT) && !i->second->joined()
        && i->second->uptime() >= connection_timeout_)
        || i->second->check_client_type(Client::ClientType::ErrorT))
        remove_client(i->first);
    }
    /* Make sure to remove all players which are in the list of to be removed */
    for (std::vector<int>::const_iterator i = clients_to_remove_.begin();
      i != clients_to_remove_.end(); ++i) {
      remove_client_immediately(*i);
    }
    clients_to_remove_.clear();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////// PRIVATE METHODS //////////////////////////////////////////
  /**
   * Accept a client
   * 
   * Accept a client in either of the sockets 
   * A new socket will be created wit accept
   * Set the client connection to nonblocking
   * Add the client to the server
   **/
  int Server::accept_client(int socket) {
    int                 fd;
    struct epoll_event  ev;
    socklen_t           addrlen;
    sockaddr_in         addr;

    // Check this ... is it really worth it to have two sockaddr_in on the struct... ?
    if (socket == players_socket_)
      addr = players_sockaddr_;
    else if (socket == spectators_socket_)
      addr = spectators_sockaddr_;
    addrlen = sizeof(addr);
    fd = accept(socket, (struct sockaddr *)&addr, &addrlen);
    if (fd == -1)
      throw std::runtime_error(std::string("accept():") + std::string(strerror(errno)));
    if (DEBUG) {
      std::cout << GREEN << "Accepted client (" << BLUE <<
        (socket == players_socket_ ? "Player" : "Spectator") <<  GREEN <<")" << ENDC << std::endl;
    }
    setnonblocking(fd);
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev) == -1) {
      throw std::runtime_error(std::string("epoll_ctl: conn_sock") + std::string(strerror(errno)));
    }
    add_client(socket, fd);
    return fd;
  }

  // This implementation could change depending if the server is launched in single port mode
  void  Server::add_client(int socket, int fd) {
    if (DEBUG)
      std::cout << YELLOW << "[Server]\t" << GREEN << "add\t" << ENDC << fd << std::endl;
    if (players_socket_ == socket) {
      clients_.insert(std::pair<int, Client *>(fd, new Client(fd, Client::ClientType::PlayerT)));
    } else if (spectators_socket_ == socket) {
      clients_.insert(std::pair<int, Client *>(fd, new Spectator(fd)));
    }
  }

  void  Server::handle_client(int fd, const std::string & msg) {
    Client * client;
    ClientCommand *c;

    client = clients_.at(fd);
    c = ClientCommand::parse_command(trantor_, client, msg);
    if (DEBUG) {
      std::cout << YELLOW << "[Server]\t" << BLUE << *c << ENDC << ":" << YELLOW <<
        (c->is_valid() ? "valid" : "invalid") << " | " << GREEN << "recv" << ENDC << ":" << BLUE <<
        msg.length() << ENDC << "bytes" << std::endl;
    }
    if (c->is_valid()) {
      client->queue_cmd(c);
    } else {
      client->broadcast(c->cmd_error());
      delete c;
    }
  }

  const std::string Server::handle_client_input_or_disconnect(int fd) {
    char buf[Server::RECV_BUFFER];
    std::string msg;
    ssize_t read_bytes;

    for (;;) {
      bzero(buf, Server::RECV_BUFFER);
      if (is_stdin(fd))
        read_bytes = read(fd, buf, Server::RECV_BUFFER);
      else
        read_bytes = recv(fd, buf, Server::RECV_BUFFER, MSG_DONTWAIT);
      // Remove client on error
      if (read_bytes == -1) {
        if(errno != EAGAIN && errno != EWOULDBLOCK && fd != 0)
          remove_client(fd);
        break;
      }
      // Remove client on disconnection
      if (read_bytes == 0 && fd != 0) {
        remove_client(fd);
        break;
      }
      // Protect append function from throwing lenght error when -1
      // Return message when the client sends a message
      if (read_bytes > 0)
        msg.append(buf, read_bytes);
    }
    return (msg);
  }

  // Handle standard input from the server [BONUS]
  void  Server::handle_stdin(const std::string & cmd) {
    ServerCommand * c = ServerCommand::parse_command(trantor_, cmd);

    if (DEBUG) {
      std::cout << YELLOW << "[Server]\t" << BLUE << *c << ENDC ":" << YELLOW <<
        (c->is_valid() ? "valid" : "invalid") << ENDC << std::endl;
    }
    if (c->is_valid())
      c->execute();
    else
      write(0, "command not found\n", 18); 
    delete c;
    if (check_health(Running))
      write(1, "$> ", 3);
  }
  
  bool  Server::is_client(int fd) {
    return (clients_.find(fd) != clients_.end());
  }

  bool  Server::is_server_socket(int fd) {
    return (players_socket_ == fd || spectators_socket_ == fd);
  }

  bool  Server::is_stdin(int fd) {
    return (fd == 0);
  }

  void  Server::remove_client(int fd) {
    clients_to_remove_.push_back(fd);
  }

  void  Server::remove_client_immediately(int fd) {
    if (DEBUG)
      std::cout << YELLOW << "[Server]\t" << RED << "remove\t" << ENDC << fd << std::endl;
    if (is_client(fd)) {
      delete clients_.at(fd);
      clients_.erase(fd);
    }
    close(fd);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const Server& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}
