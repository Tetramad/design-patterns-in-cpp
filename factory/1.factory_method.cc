#include <iostream>
#include <cmath>

double const pi = std::acos(-1);

struct Point {
  float x;
  float y;

  static auto cartesian(float x, float y) -> Point {
    return { x, y };
  }

  static auto polar(float r, float theta) -> Point {
    return { r * std::cos(theta), r * std::sin(theta) };
  }

protected:
  Point(float x, float y)
    : x{ x }, y{ y } {}
};

auto main() -> int {
  auto p = Point::polar(5.0f, pi / 4.0f);

  std::cout << p.x << " " << p.y << std::endl;
}
