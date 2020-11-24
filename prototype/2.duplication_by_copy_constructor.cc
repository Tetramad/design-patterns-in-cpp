#include <iostream>
#include <string>

struct Address {
  std::string street;
  std::string city;
  int suite;

  Address(std::string const &street, std::string const &city, int suite)
    : street(street), city(city), suite(suite) {}
};

struct Contact {
  std::string name;
  Address *address;

  Contact(std::string const &name, Address *address)
    : name(name), address(address) {}
  Contact(Contact const &other)
    : name(other.name), address(new Address(*other.address)) {}
  ~Contact() noexcept {
    delete address;
  }
  auto operator=(Contact const &other) -> Contact & {
    if (this == &other) {
      return *this;
    }
    name = other.name;
    address = other.address;
    return *this;
  }
};

auto main() -> int {
  auto worker = Contact{ "", new Address{ "123 East Dr", "London", 0 } };
  auto john = Contact{worker};

  john.name = "John Doe";
  john.address->suite = 10;

  std::cout << "worker.address.suite >> " << worker.address->suite << std::endl;
  std::cout << "john.address.suite >> " << john.address->suite << std::endl;
}
