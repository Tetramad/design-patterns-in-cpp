#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

struct Shape {
  virtual auto str() const -> std::string = 0;
};

template <typename T>
struct ColoredShape : T {
  static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a Shape");

  std::string color;

  template <typename ...Args>
  ColoredShape(std::string color, Args ...args)
    : T(std::forward<Args>(args)...), color(color) {}

  auto str() const -> std::string override {
    std::ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T>
struct TransparentShape : T {
  static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a Shape");

  std::uint8_t transparency;

  template <typename ...Args>
  TransparentShape(std::uint8_t transparency, Args ...args)
    : T(std::forward<Args>(args)...), transparency(transparency) {}

  auto str() const -> std::string override {
    std::ostringstream oss;
    oss << T::str() << " has "
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
  auto circle = ColoredShape<TransparentShape<Circle>>{ "blue", 20, 0.5f };

  std::cout << circle.str() << std::endl;
}
