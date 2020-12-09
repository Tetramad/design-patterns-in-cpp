#include <iostream>
#include <string>
#include <sstream>
#include <memory>

struct Shape {
  virtual auto str() const -> std::string = 0;
};

struct Circle : Shape {
  float radius;

  explicit Circle(float const radius)
    : radius(radius) {}

  auto resize(float factor) -> void {
    radius *= factor;
  }

  auto str() const -> std::string override {
    std::ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

auto main() -> int {
  std::unique_ptr<Shape> shape = std::make_unique<Circle>(10.0f);

  std::cout << shape->str() << std::endl;
}
