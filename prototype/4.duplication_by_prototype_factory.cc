#include <iostream>
#include <string>
#include <memory>

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

  Contact(std::string const &name = "", Address *address = nullptr)
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

struct EmployeeFactory {
  static Contact main;
  static Contact aux;

  static auto MainOfficeEmployee(std::string name, int suite) -> std::unique_ptr<Contact> {
    return Employee(name, suite, main);
  }
  static auto AuxOfficeEmployee(std::string name, int suite) -> std::unique_ptr<Contact> {
    return Employee(name, suite, aux);
  }

private:
  static auto Employee(std::string name, int suite, Contact const &proto) -> std::unique_ptr<Contact> {
    auto result = std::make_unique<Contact>(proto);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

Contact EmployeeFactory::main{ "", new Address{ "123 East Dr", "London", 0 } };
Contact EmployeeFactory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

auto main() -> int {
  auto john = EmployeeFactory::AuxOfficeEmployee("John Doe", 123);
  auto jane = EmployeeFactory::MainOfficeEmployee("Jane Doe", 125);

  std::cout << john->name << std::endl;
  std::cout << "  " << john->address->street << std::endl;
  std::cout << "  " << john->address->city << std::endl;
  std::cout << "  " << john->address->suite << std::endl;
  std::cout << jane->name << std::endl;
  std::cout << "  " << jane->address->street << std::endl;
  std::cout << "  " << jane->address->city << std::endl;
  std::cout << "  " << jane->address->suite << std::endl;
}
