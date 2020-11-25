#include <iostream>

struct Renderer {
  virtual auto render_circle(float x, float y, float radius) -> void = 0;
};

struct VectorRenderer : Renderer {
  auto render_circle(float x, float y, float radius) -> void override {
    std::cout << "Drawing a vector circle of radius " << radius << " at (" << x << ", " << y << ")" << std::endl;
  }
};

struct RasterRenderer : Renderer {
  auto render_circle(float x, float y, float radius) -> void override {
    std::cout << "Rasterizing circle of radius " << radius << " at (" << x << ", " << y << ")" << std::endl;
  }
};

struct Shape {
protected:
  Renderer &renderer;
  Shape(Renderer &renderer) : renderer{ renderer } {}
public:
  virtual auto draw() -> void = 0;
  virtual auto resize(float factor) -> void = 0;
};

struct Circle : Shape {
  float x;
  float y;
  float radius;

  auto draw() -> void override {
    renderer.render_circle(x, y, radius);
  }
  auto resize(float factor) -> void override {
    radius *= factor;
  }

  Circle(Renderer &renderer, float x, float y, float radius)
    : Shape{ renderer }, x{ x }, y{ y }, radius{ radius } {}
};

auto main() -> int {
  RasterRenderer rr;
  Circle raster_circle{ rr, 5, 4, 3 };
  raster_circle.draw();
  raster_circle.resize(2.0f);
  raster_circle.draw();
}
