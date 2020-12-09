#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

struct Shape {
  virtual auto str() const -> std::string = 0;
};

struct ColoredShape : Shape {
  Shape &shape;
  std::string color;

  ColoredShape(Shape &shape, std::string const& color)
    : shape(shape), color(color) {}

  auto str() const -> std::string override {
    std::ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

struct TransparentShape : Shape {
  Shape &shape;
  std::uint8_t transparency;

  TransparentShape(Shape &shape, std::uint8_t transparency)
    : shape(shape), transparency(transparency) {}

  auto str() const -> std::string override {
    std::ostringstream oss;
    oss << shape.str() << " has "
      << static_cast<float>(transparency) / 255.0f * 100.0f << "% transparency";
    return oss.str();
  }
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
  auto circle = Circle{ 0.5f };
  auto red_circle = ColoredShape{ circle, "red" };
  auto transparent_circle = TransparentShape{ circle, 127u };

  std::cout << red_circle.str() << std::endl;
  std::cout << transparent_circle.str() << std::endl;
}
