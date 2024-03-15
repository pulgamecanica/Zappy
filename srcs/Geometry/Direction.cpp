//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Geometry/Direction.hpp"

namespace Zappy {

  Point Direction::get_orientation_vec(enum Orientation o) {
    switch (o) {
      case Orientation::North:
        return Point(1, 0);
      case Orientation::South:
        return Point(-1, 0);
      case Orientation::East:
        return Point(0, 1);
      case Orientation::West:
        return Point(0, -1);
      default:
        return Point(0, 0); 
    }
  }

  Direction Direction::get_random() {
    switch (rand() % 4) {
      case 0:
        return (Direction(Orientation::North));
      case 1:
        return (Direction(Orientation::East));
      case 2:
        return (Direction(Orientation::South));
      case 3:
        return (Direction(Orientation::West));
      default:
        return (Direction(Orientation::North));
    }
  }

  Direction::Direction(enum Orientation o): Point(get_orientation_vec(o)), o_(o) {
  }

  Direction::~Direction() {}


  Direction&  Direction::operator=(const Point& p) {
    x_ =  p.x();
    y_ =  p.y();
    return (*this);
  }

  Direction& Direction::operator++(void) {
    o_ = static_cast<Orientation>((o_ + 1) % 4);
    
    *this = get_orientation_vec(o_);
    return *this;
  }

  Direction Direction::operator++(int) {
    Direction tmp(*this);

    o_ = static_cast<Orientation>((o_ + 1) % 4);
    *this = get_orientation_vec(o_);
    return tmp;
  }

  Direction& Direction::operator--(void) {
    int next;

    next = o_ - 1;
    if (next < 0)
      next = 3;
    o_ = static_cast<Orientation>(next);
    *this = get_orientation_vec(o_);
    return *this;
  }

  Direction Direction::operator--(int) {
    Direction tmp(*this);
    int next;

    next = o_ - 1;
    if (next < 0)
      next = 3;
    o_ = static_cast<Orientation>(next);
    *this = get_orientation_vec(o_);
    return tmp;
  }


  const std::string& Direction::get_name() const {
    return (DIRECTIONS_STR[o_]);
  }

  std::ostream& operator<<(std::ostream& s, const Direction& d) {
    s << "[" << d.get_name() << "]" << (Point)d;
    return (s);
  }
}
