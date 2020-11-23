#include <iostream>
#include <cmath>

double const pi = std::acos(-1);

struct Point final {
  friend class PointFactory;

  float x;
  float y;

private:
  Point(float x, float y) : x(x), y(y) {}
};

struct PointFactory final {
  static auto cartesian(float x, float y) -> Point {
    return { x, y };
  }

  static auto polar(float r, float theta) -> Point {
    return { r * std::cos(theta), r * std::sin(theta) };
  }
};

auto main() -> int {
  auto p = PointFactory::cartesian(3, 4);

  std::cout << p.x << " " << p.y << std::endl;
}
