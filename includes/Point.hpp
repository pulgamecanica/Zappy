//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __POINT_HPP__
# define __POINT_HPP__

#include <iostream>

namespace Zappy {
  class Point {
    public:
      Point(int x, int y);
      Point(const Point&) = default;
      virtual ~Point();
      Point&  operator=(const Point& p) = default;
      bool    operator==(const Point& p) const;
      bool    operator!=(const Point& p) const;
      Point   operator+(const Point& p) const;
      Point   operator-(const Point& p) const;
      Point   operator*(const Point& p) const;
      Point   operator/(const Point& p) const;
      Point&  operator+=(const Point& p);
      Point&  operator-=(const Point& p);
      Point&  operator*=(const Point& p);
      Point&  operator/=(const Point& p);
      int y() const;
      int x() const;
    protected:
      int x_;
      int y_;
  };

  double distance(const Point & p1, const Point & p2);
  std::ostream& operator<<(std::ostream&, const Point&);
}

#endif

