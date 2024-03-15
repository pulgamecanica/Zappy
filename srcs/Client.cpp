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

namespace Zappy {
  Client::Client(int fd, ClientType type): fd_(fd), client_type_(type) {
    created_at_ms_ = gettimeofday_ms();
  }

  Client::~Client() {
    cmd_queue_.clear();
    if (DEBUG)
      std::cout << *this << " destroyed" << std::endl;
    // TODO (destructor)
  }

  ssize_t Client::uptime() const {
    return (gettimeofday_ms() - created_at_ms_);
  }

  void Client::broadcast(std::string msg) {
    msg.append("\n");
    if (send(fd_, msg.c_str(), msg.length(), MSG_DONTWAIT | MSG_NOSIGNAL) == -1) {
      if (errno == EPIPE) {
        if (DEBUG)
          std::cout << YELLOW << "[Server]\t" << RED << "Error" << ENDC << " would send SIGPIPE, problems with socket" << std::endl;
        // remove_client(*it);
        // Client is dead
        client_type_ = ClientType::Error;
      }
    }
  }

  void  Client::queue_cmd(ClientCommand * cmd) {
    if (cmd_queue_.size() < Client::QUEUE_SIZE) {
      cmd_queue_.push_back(cmd);
    }
    if (DEBUG)
      std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " enqueue" << ENDC << ":" << BLUE << *cmd << ENDC << std::endl;
  }

  // Update Client
  // Check cmd queue
  // Execute commands
  // Remove expired commands
  void Client::update() {
    if (cmd_queue_.empty())
      return ;
    if (!cmd_queue_.front()->was_executed()) {
      if (DEBUG)
        std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " exec" << ENDC << ":" << BLUE << *cmd_queue_.front() << ENDC << std::endl;
      cmd_queue_.front()->execute();
    } else if (cmd_queue_.front()->expired()) {
      if (DEBUG)
        std::cout << YELLOW << "[Server]" << BLUE << "(" << *this << ")" << GREEN << " finished exec" << ENDC << ":" << BLUE << *cmd_queue_.front() << ENDC << std::endl; 
      delete cmd_queue_.front();
      cmd_queue_.erase(cmd_queue_.begin());
    }
  }

  int Client::get_fd() const { return (fd_); }

  enum Client::ClientType Client::get_client_type() const { return (client_type_); }

  std::ostream& operator<<(std::ostream& s, const Client& p) {
    s << Client::CLIENT_TYPES_STR[p.get_client_type()] << " [" << p. get_fd() << "]";
    return (s);
  }
}
