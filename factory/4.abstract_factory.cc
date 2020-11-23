#include <iostream>
#include <map>
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

struct HotDrinkFactory {
  virtual auto make() const -> std::unique_ptr<HotDrink> = 0;
};

struct TeaFactory final : HotDrinkFactory {
  auto make() const -> std::unique_ptr<HotDrink> override {
    return std::make_unique<Tea>();
  }
};

struct CoffeeFactory final : HotDrinkFactory {
  auto make() const -> std::unique_ptr<HotDrink> override {
    return std::make_unique<Coffee>();
  }
};

struct DrinkFactory {
  DrinkFactory() {
    hotdrink_factories["tea"] = std::make_unique<TeaFactory>();
    hotdrink_factories["coffee"] = std::make_unique<CoffeeFactory>();
  }

  auto make_drink(std::string const &name) -> std::unique_ptr<HotDrink> {
    auto drink = hotdrink_factories[name]->make();
    return drink;
  }

private:
  std::map<std::string, std::unique_ptr<HotDrinkFactory>> hotdrink_factories;
};

auto main() -> int {
  DrinkFactory().make_drink("tea")->prepare(100);
}
