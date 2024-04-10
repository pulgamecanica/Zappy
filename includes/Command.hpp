//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

#include <iostream>
#include <vector>
#include <map>

#include "Client.hpp"
#include "GameEngine.hpp"

namespace Zappy {
  
  class Server;

  class Command {
    protected:
      enum Error {
        NoError,
        BadParams,
        MissingParams,
        CommandNotFound
      };
    public:  
      // CONSTRUCTORS & DESTRUCTORS //
      Command(const Command&) = default;
      Command& operator=(const Command&) = default; // const for safety... not super nesessary
      virtual ~Command();
      // CONST PUBLIC METHODS //
      const std::string&        get_cmd() const;
      const std::string&        get_error_msg() const;
      // CONST PUBLIC VIRTUAL METHODS //
      virtual const std::string cmd_error() const;
      // PUBLIC METHODS //
      bool                      is_valid() const;
      void                      set_error(enum Command::Error error);
      // PUBLIC VIRTUAL METHODS //
      virtual void              execute();
    protected:
      // PROTECTED CONSTRUCTORS (DISABLED PUBLICLY) //
      Command(const std::string cmd, GameEngine * trantor, Error e = NoError);
      // STATIC PROTECTED METHODS //
      static std::vector<std::string> get_options(const std::string & options_str);
      // PROTECTED METHODS //
      enum Error  error_;
      GameEngine  *trantor_;
    private:
      // STATIC PRIVATE MEMBERS //
      static const std::map<enum Error, std::string> ERROR_MSGS;
      // PRIVATE METHODS //
      const std::string cmd_;
  };

  std::ostream& operator<<(std::ostream&, const Command&);
}
#endif
