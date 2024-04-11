//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Resources/Mineral.hpp"

namespace Zappy {

  std::map<int, std::string> Mineral::TRANTORIAN_MINERALS = {
    { 0, "linemate" },
    { 1, "deraumere" },
    { 2, "sibur" },
    { 3, "mendiane" },
    { 4, "phiras" },
    { 5, "thystame" },
  };

  Mineral::Mineral(int index): index_(index), name_(TRANTORIAN_MINERALS[index]) {
    ;
  }

  Mineral::~Mineral() {
    ;
  }

  const std::string & Mineral::get_name() const {
    return name_;
  }

  bool  Mineral::operator==(int mineral_rhs) const {
    return index_ == mineral_rhs;
  }

  bool  Mineral::operator== (const Mineral& mineral_rhs) const {
    return index_ == mineral_rhs.index_;
  }

  bool  Mineral::operator< (const Mineral& mineral_rhs) const {
    return index_ < mineral_rhs.index_;
  }

  std::ostream& operator<<(std::ostream& s, const Mineral& param) {
  	(void)param;
  	return (s);
  }
}
