#include <string>

struct Address {
  std::string street;
  std::string city;
  int suite;
};

struct Contact {
  std::string name;
  Address address;
};

auto main() -> int {
  Contact worker{ "", Address{ "123 East Dr", "London", 0 } };

  Contact john = worker;
  john.name = "John Doe";
  john.address.suite = 10;
}
