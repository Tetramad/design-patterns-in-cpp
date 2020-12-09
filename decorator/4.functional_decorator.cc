#include <iostream>
#include <string>
#include <functional>

template <typename R, typename ...Args>
struct Logger {
  std::function<R (Args...)> function;
  std::string name;

  Logger(std::function<R(Args...)> const &function, std::string const &name)
    : function(function), name(name) {}

  auto operator()(Args ...args) const -> R {
    std::cout << "Entering " << name << std::endl;
    auto result = function(args...);
    std::cout << "Exiting " << name << std::endl;
    return result;
  }
};

auto add(double a, double b) -> double {
  std::cout << a << "+" << b << "=" << (a + b) << std::endl;
  return a + b;
}

template <typename R, typename ...Args>
auto log(R (*function)(Args...), std::string const &name) {
  return Logger<R, Args...>(std::function<R (Args...)>(function), name);
}

auto main() -> int {
  log(&add, "Add")(3.5, 4.2);
}
