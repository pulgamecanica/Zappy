//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"
#include "Command.hpp"

#include "Server.hpp"

namespace Zappy {
  ////////////////////////////////// STATIC PUBLIC METHODS ////////////////////////////////////////
  /**
   * Server commands:
   * 
   * help -> Returns list of available commands
   * status -> Returns the current status of the server
   * exit -> exits the server
   * lang <name> -> change the server language
   * 
   **/
  /////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
  Command::Command(const std::string cmd, GameEngine * trantor, Error e):
      error_(e), trantor_(trantor), cmd_(cmd) {
  }

  Command::~Command() {
    ;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
  const std::string& Command::get_cmd() const {
    return (cmd_);
  }

  const std::string& Command::get_error_msg() const {
    return ERROR_MSGS.at(error_);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////// CONST PUBLIC VIRTUAL METHODS ////////////////////////////////////
  const std::string Command::cmd_error() const {
    return ("Command:Error");
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////// PUBLIC METHODS //////////////////////////////////////////
  bool Command::is_valid() const {
    return error_ == NoError;
  }

  void Command::set_error(enum Command::Error error) {
    error_ = error;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// PUBLIC VIRTUAL METHODS //////////////////////////////////////
  void Command::execute() {
    throw std::runtime_error("Cannot execute abstract command");
  }
  //////////////////////////////////// STATIC PROTECTED METHODS ///////////////////////////////////

  //////////////////////////////////// STATIC PROTECTED METHODS ///////////////////////////////////
  std::vector<std::string> Command::get_options(const std::string & options_str) {
    std::vector<std::string> options;

    std::istringstream stream(options_str);
    std::string option;

    while (stream >> option)
      if (!option.empty())
        options.push_back(option);

    if (DEBUG) {
      std::cout << GREEN << "Options: " << ENDC;
      if (options.empty())
        std::cout << "[]";
      for (std::vector<std::string>::iterator i = options.begin(); i != options.end(); ++i)
        std::cout << "[" << BLUE << *i << ENDC << "] ";
      std::cout << std::endl;
    }
    return (options);
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  //////////////////////////////////// STATIC PROTECTED MEMBERS ///////////////////////////////////
  const std::map<enum Command::Error, std::string> Command::ERROR_MSGS = {
    {Command::Error::NoError, ""},
    {Command::Error::BadParams, "was given bad parameters, make sure you are giving the correct type"},
    {Command::Error::MissingParams, "is missing parameters"}
  };
  /////////////////////////////////////////////////////////////////////////////////////////////////
  

  std::ostream& operator<<(std::ostream& s, const Command& param) {
    s << param.get_cmd();
    return (s);
  }
}
