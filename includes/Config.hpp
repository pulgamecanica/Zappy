//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CONFIG_HPP__
# define __CONFIG_HPP__

#include <iostream>
#include <vector>
#include <map>

#include <toml++/toml.hpp>

namespace Zappy {
  class Config {
    public:
      Config(toml::table & table, const std::string language);
      Config(const Config&) = default;
      ~Config();
      Config&             operator= (const Config&) = default;
      bool                operator==(const std::string&) const; // Needed in order to use find with a string
      const std::string & get_language_acronym() const;
      const std::string & get(const std::string & directive) const;
    private:
      // CLASS FUNCTION MEMBERS
      static const std::vector<std::string> DIRECTIVES;
      static const std::string get_value_or_empty(toml::table & table, const std::string language, const std::string key);
      // CLASS PARAMS MEMBERS
      const std::string language_acronym_;
      std::map<std::string, std::string> toml_contents_;
  };

  std::ostream& operator<<(std::ostream&, const Config&);
}

#endif

