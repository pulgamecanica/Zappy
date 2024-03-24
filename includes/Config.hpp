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
      // CONSTRUCTORS & DESTRUCTORS //
      Config(toml::table & table, const std::string language);
      Config(const Config&) = default;
      Config& operator= (const Config&) = default;
      ~Config();
      // CONST PUBLIC METHODS //
      const std::string&  get(const std::string & directive) const;
      const std::string&  get_language_acronym() const;
      bool                operator==(const std::string&) const;
    private:
      // STATIC PRIVATE METHODS //
      static const std::string  get_value_or_empty(toml::table & table, const std::string language,
                                                    const std::string key);
      // STATIC PRIVATE MEMBERS //
      static const std::vector<std::string> DIRECTIVES;
      // PRIVATE MEMBERS //
      const std::string                     language_acronym_;
      std::map<std::string, std::string>    toml_contents_;
  };

  std::ostream& operator<<(std::ostream&, const Config&);
}

#endif

