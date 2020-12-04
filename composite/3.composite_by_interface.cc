#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct GraphicObject {
  virtual auto draw() const -> void = 0;
};

struct Circle : GraphicObject {
  auto draw() const -> void override {
    std::cout << "Circle" << std::endl;
  }
};

struct Group : GraphicObject {
  std::string name;
  std::vector<std::unique_ptr<GraphicObject>> objects;

  explicit Group(std::string const &name) 
    : name(name) {}

  auto draw() const -> void override {
    std::cout << "Group" << name << " contains:" << std::endl;
    for (auto const &o : objects) {
      o->draw();
    }
  }
};

auto main() -> int {
  auto group1 = Group{"Group1"};
  group1.objects.push_back(std::make_unique<Circle>());
  auto group2 = std::make_unique<Group>("Group2");
  group2->objects.push_back(std::make_unique<Circle>());
  group1.objects.push_back(std::move(group2));
  group1.objects.push_back(std::make_unique<Circle>());
  group1.draw();
}
