//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <sys/socket.h>
  #include <sys/time.h>
}

#include "Zappy.inc"

#include "Client.hpp"
#include "ClientCommand.hpp"
#include "Player.hpp"

namespace Zappy {
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  Client::Client(int fd, ClientType type): player_(nullptr), fd_(fd), client_type_(type) {
    created_at_ms_ = gettimeofday_ms();
  }

  Client::~Client() {
    cmd_queue_.clear();
    if (DEBUG)
      std::cout << *this << " destroyed" << std::endl;
    // TODO (destructor)
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  bool Client::check_client_type(enum Client::ClientType ct) const {
    return (client_type_ == ct);
  }

  enum Client::ClientType Client::get_client_type() const {
    return (client_type_);
  }
  
  int Client::get_fd() const {
    return (fd_);
  }

  Player* Client::get_player() const {
    return (player_);
  }

  bool Client::joined() const {
    return (player_ != nullptr);
  }

  ssize_t Client::uptime() const {
    return (gettimeofday_ms() - created_at_ms_);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////// PUBLIC METHODS ///////////////////////////////////////////
  void Client::assign_player(Player * player) {
    if (player)
      if (client_type_ == ClientType::PlayerT)
        player_ = player;
  }

  void Client::broadcast(std::string msg, bool new_line) {
    if (new_line)
      msg.append("\n");
    if (send(fd_, msg.c_str(), msg.length(), MSG_DONTWAIT | MSG_NOSIGNAL) == -1) {
      if (errno == EPIPE) {
        if (DEBUG)
          std::cout << YELLOW << "[Server]\t" << RED << "Error" << ENDC << " would send SIGPIPE, problems with socket" << std::endl;
        client_type_ = ClientType::ErrorT;
      }
    }
  }

  void Client::dismiss_player() {
    player_ = nullptr;
  }

  void Client::queue_cmd(ClientCommand * cmd) {
    if (cmd_queue_.size() < Client::QUEUE_SIZE)
      cmd_queue_.push_back(cmd);
    if (DEBUG)
      std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " enqueue" << ENDC << ":" << BLUE << *cmd << ENDC << std::endl;
  }

  // Check Command Queue (are there commands to be executed?)
  // IF NOT EXECUTED => Execute the first command if it wasn't executed
  // IF EXECUTED => Wait until command expires and remove it
  void Client::update() {
    if (cmd_queue_.empty())
      return ;
    if (!cmd_queue_.front()->was_executed()) {
      if (DEBUG)
        std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " exec" << ENDC << ":" << BLUE << *cmd_queue_.front() << ENDC << std::endl;
      try {
        cmd_queue_.front()->execute();
        cmd_queue_.front()->broadcast();
      } catch( std::exception & e) {
        this->broadcast(e.what());
      }
    } else if (cmd_queue_.front()->expired()) {
      if (DEBUG)
        std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " finished exec" << ENDC << ":" << BLUE << *cmd_queue_.front() << ENDC << std::endl; 
      delete cmd_queue_.front();
      cmd_queue_.erase(cmd_queue_.begin());
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  std::ostream& operator<<(std::ostream& s, const Client& p) {
    s << Client::CLIENT_TYPES_STR[p.get_client_type()] << " [" << p. get_fd() << "]";
    return (s);
  }
}
