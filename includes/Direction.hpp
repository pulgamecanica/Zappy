//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __DIRECTION_HPP__
# define __DIRECTION_HPP__

#include <iostream>

#include "Point.hpp"

namespace Zappy {

  enum Orientation {
    North,
    East,
    South,
    West
  };

  class Direction: public Point {
    public:
      static Direction  get_random();
      static Point  get_orientation_vec(enum Orientation o);
      Direction(enum Orientation o);
      Direction(const Direction&) = default;
      ~Direction();
      Direction&          operator= (const Direction&) = default; // const for safety... not super nesessary
      Direction&          operator= (const Point&);
      const std::string&  get_name() const;
      // Direction ++ will change the direction 90deg to the right (clockwize)
      // Direction -- will change the direction 90deg to the left (counter-clockwize)
      Direction&          operator++(void);
      Direction           operator++(int);
      Direction&          operator--(void);
      Direction           operator--(int);
    private:
      static constexpr const std::string DIRECTIONS_STR[4] = {
        "North",
        "East",
        "South",
        "West"
      };
      enum Orientation o_;
  };

  std::ostream& operator<<(std::ostream&, const Direction&);
}
#endif

