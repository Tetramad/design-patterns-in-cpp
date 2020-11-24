#include <iostream>
#include <sstream>
#include <string>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

struct Address {
  std::string street;
  std::string city;
  int suite;

  Address(std::string const &street = "", std::string const &city = "", int suite = 0)
    : street(street), city(city), suite(suite) {}

private:
  friend class boost::serialization::access;
  template <typename Ar>
  auto serialize(Ar &ar, [[maybe_unused]] unsigned int version) -> void {
    ar & street;
    ar & city;
    ar & suite;
  }
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

private:
  friend class boost::serialization::access;
  template <typename Ar>
  auto serialize(Ar &ar, [[maybe_unused]] unsigned int version) -> void {
    ar & name;
    ar & address;
  }
};

auto main() -> int {
  auto clone = [](Contact const &c) {
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << c;
    std::string s = oss.str();

    std::istringstream iss(oss.str());
    boost::archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;
    return result;
  };

  auto john = Contact{ "John Doe", new Address{"123 East Dr", "London", 10 } };
  auto jane = clone(john);
  jane.name = "Jane Doe";
  jane.address->suite = 11;
  std::cout << john.name << std::endl;
  std::cout << "  " << john.address->street << std::endl;
  std::cout << "  " << john.address->city << std::endl;
  std::cout << "  " << john.address->suite << std::endl;
  std::cout << jane.name << std::endl;
  std::cout << "  " << jane.address->street << std::endl;
  std::cout << "  " << jane.address->city << std::endl;
  std::cout << "  " << jane.address->suite << std::endl;
}
