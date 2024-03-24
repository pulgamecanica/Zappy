//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>
#include <vector>

#include "Client.hpp"

namespace Zappy {
  
  class Server;

  class Command {
    public:
      // STATIC PUBLIC METHODS //
      static Command* parse_server_command(const std::string & msg, Server * s);      
      // CONSTRUCTORS & DESTRUCTORS //
      Command(const Command&) = default;
      Command& operator=(const Command&) = default; // const for safety... not super nesessary
      virtual ~Command();
      // CONST PUBLIC METHODS //
      const std::string&        get_cmd() const;
      // CONST PUBLIC VIRTUAL METHODS //
      virtual const std::string cmd_error() const;
      virtual void              execute();
      virtual bool              is_valid() const;
    protected:
      // PROTECTED CONSTRUCTORS (DISABLED PUBLICLY) //
      Command(const std::string cmd, Server * s);
      // STATIC PROTECTED METHODS //
      static std::vector<std::string> get_options(const std::string & options_str);
      // PROTECTED METHODS //
      Server* s_;
    private:
      // PRIVATE METHODS //
      const std::string cmd_;
  };

  std::ostream& operator<<(std::ostream&, const Command&);
}
#endif
