#include <memory>
#include <iostream>
#include <vector>

struct Painter {
  Painter(int width, int height) : width(width), height(height) {
    screen.resize(width * height);
  }
  auto SetPixel(int x, int y, int color_code) -> void {
    screen[x + y * width] = color_code;
    Redraw();
  }
private:
  int width;
  int height;
  std::vector<int> screen;
  auto Redraw() -> void {
    std::cout << "\033[2J\033[1;1H";
    for (auto y = 0; y < height; ++y) {
      for (auto x = 0; x < width; ++x) {
        if (screen[x + y * width] != 0) {
          std::cout << "\033[" << screen[x + y * width] << "m";
          std::cout << "  ";
          std::cout << "\033[49m";
        } else {
          std::cout << "  ";
        }
      }
      std::cout << '\n';
    }
    std::cout << std::flush;
  }
};

struct Point {
  int x;
  int y;
};

struct Line {
  Point start;
  Point end;
  Line(Point start, Point end) : start(start), end(end) {}
};

struct VectorObject {
  virtual auto begin() -> std::vector<Line>::iterator = 0;
  virtual auto end() -> std::vector<Line>::iterator = 0;
};

struct VectorRectangle : VectorObject {
  VectorRectangle(int x, int y, int width, int height) {
    lines.emplace_back(Point{ x, y }, Point{ x + width, y });
    lines.emplace_back(Point{ x + width, y }, Point{ x + width, y + height });
    lines.emplace_back(Point{ x, y }, Point{ x, y + height });
    lines.emplace_back(Point{ x, y + height }, Point{ x + width, y + height });
  }

  auto begin() -> std::vector<Line>::iterator override {
    return lines.begin();
  }
  auto end() -> std::vector<Line>::iterator override {
    return lines.end();
  }
private:
  std::vector<Line> lines;
};

auto DrawPoints(Painter &painter, std::vector<Point>::iterator first, std::vector<Point>::iterator last) -> void {
  while (first != last) {
    painter.SetPixel(first->x, first->y, 41);
    ++first;
  }
}

struct LineToPointAdapter {
  using Points = std::vector<Point>;

  LineToPointAdapter(Line &line) {
    int left = std::min(line.start.x, line.end.x);
    int right = std::max(line.start.x, line.end.x);
    int top = std::min(line.start.y, line.end.y);
    int bottom = std::max(line.start.y, line.end.y);
    int dx = right - left;
    int dy = bottom - top;

    if (dx == 0) {
      for (int y = top; y <= bottom; ++y) {
        points.emplace_back(Point{ left, y });
      }
    } else if (dy == 0) {
      for (int x = left; x <= right; ++x) {
        points.emplace_back(Point{ x, top });
      }
    }
  }

  virtual auto begin() -> Points::iterator {
    return points.begin();
  }
  virtual auto end() -> Points::iterator {
    return points.end();
  }
private:
  Points points;
};

auto main() -> int {
  auto painter = Painter{20, 20};
  std::vector<std::shared_ptr<VectorObject>> vector_objects {
    std::make_shared<VectorRectangle>(1, 1, 10, 10),
    std::make_shared<VectorRectangle>(5, 5, 10, 10),
    std::make_shared<VectorRectangle>(3, 3, 6, 6) };

  for (auto &obj : vector_objects) {
    for (auto &line : *obj) {
      auto lpo = LineToPointAdapter{ line };
      DrawPoints(painter, lpo.begin(), lpo.end());
    }
  }
}
