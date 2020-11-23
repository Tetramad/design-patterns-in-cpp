#include <iostream>
#include <cmath>

double const pi = std::acos(-1);

struct Point final {
  struct PointFactory final {
    static auto cartesian(float x, float y) -> Point {
      return { x, y };
    }
    static auto polar(float r, float theta) -> Point {
      return { r * std::cos(theta), r * std::sin(theta) };
    }
  };

  using Factory = PointFactory;

  float x;
  float y;

private:
  Point(float x, float y) : x(x), y(y) {}
};

auto main() -> int {
  auto p = Point::Factory::cartesian(2, 3);

  std::cout << p.x << " " << p.y << std::endl;
}
