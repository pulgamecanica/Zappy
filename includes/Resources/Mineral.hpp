//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MINERAL_HPP__
# define __MINERAL_HPP__

#include <iostream>
#include <map>

namespace Zappy {
  class Mineral {
  	public:
      static std::map<int, std::string> TRANTORIAN_MINERALS;
  		Mineral(int index);
  		Mineral(const Mineral&) = default;
  		Mineral&	operator= (const Mineral&) = default;
  		~Mineral();
      bool  operator==(int) const;
      bool  operator== (const Mineral&) const;
      bool  operator< (const Mineral&) const;
      const std::string & get_name() const;
    private:
      const int index_;
      const std::string name_;
  };

  std::ostream&	operator<<(std::ostream&, const Mineral&);
}
#endif

