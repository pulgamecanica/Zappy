//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <math.h>
}

#include "Point.hpp"

namespace Zappy {

  Point::Point(int x, int y): x_(x), y_(y) {
    // TODO (default constructor)
  }

  Point::~Point() {}

  int Point::x() const { return (x_); }

  int Point::y() const { return (y_); }

  bool    Point::operator==(const Point &p) const {
    return (y_ == p.y() && x_ == p.x());
  }
  
  bool    Point::operator!=(const Point &p) const {
    return (y_ != p.y() || x_ != p.x());
  }
  
  Point   Point::operator+(const Point &p) const {
    return (Point(y_ + p.y(), x_ + p.x()));
  }
  
  Point   Point::operator-(const Point &p) const {
    return (Point(y_ - p.y(), x_ - p.x()));
  }
  
  Point   Point::operator*(const Point &p) const {
    return (Point(y_ * p.y(), x_ * p.x()));
  }

  Point   Point::operator/(const Point &p) const {
    return (Point(y_ / p.y(), x_ / p.x()));
  }

  Point&  Point::operator+=(const Point& p) {
    x_ += p.x();
    y_ += p.y();
    return (*this);
  }
  
  Point&  Point::operator-=(const Point& p) {
    x_ -= p.x();
    y_ -= p.y();
    return (*this);
  }
  
  Point&  Point::operator*=(const Point& p) {
    x_ *= p.x();
    y_ *= p.y();
    return (*this);
  }

  Point&  Point::operator/=(const Point& p) {
    x_ /= p.x();
    y_ /= p.y();
    return (*this);
  }


  // Formula: d=√((x2 – x1)² + (y2 – y1)²).
  double distance(const Point & p1, const Point & p2) {
    return (sqrt(
      pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2)));
  }

  std::ostream& operator<<(std::ostream& s, const Point &p) {
    s << "(" << p.x() << ", " << p.y() << ")";
    return (s);
  }
}
