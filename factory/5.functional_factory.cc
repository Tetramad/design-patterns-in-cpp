#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <memory>

struct HotDrink {
  virtual void prepare(int volume) = 0;
};


struct Tea final : HotDrink {
  void prepare(int volume) override {
    std::cout << "Take tea bag, boil water, pour " << volume <<
      "ml, add some lemon" << std::endl;
  }
};

struct Coffee final : HotDrink {
  void prepare(int volume) override {
    std::cout << "boil water, pour " << volume << "ml, add some coffee mix" <<
      std::endl;
  }
};

struct DrinkWithVolumeFactory {
  DrinkWithVolumeFactory() {
    factories["tea"] = [] {
      auto tea = std::make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };
    factories["coffee"] = [] {
      auto coffee = std::make_unique<Coffee>();
      coffee->prepare(150);
      return coffee;
    };
  }

  auto make_drink(std::string const &name) -> std::unique_ptr<HotDrink> {
    return factories[name]();
  }

private:
  std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
};

auto main() -> int {
  DrinkWithVolumeFactory().make_drink("coffee");
}
