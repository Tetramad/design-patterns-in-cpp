#include <string>
#include <utility>

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
  std::string street_address;
  std::string post_code;
  std::string city;

  std::string company_name;
  std::string position;
  int annual_income = 0;

  friend PersonBuilder;
  friend PersonAddressBuilder;
  friend PersonJobBuilder;
  Person() {}

public:
  static auto create() -> PersonBuilder;
};

class PersonBuilderBase {
protected:
  Person &person;
  explicit PersonBuilderBase(Person &person)
    : person{ person } {}
public:
  operator Person() {
    return std::move(person);
  }

  auto lives() const -> PersonAddressBuilder;
  auto works() const -> PersonJobBuilder;
};

class PersonBuilder : public PersonBuilderBase {
  Person p;
public:
  PersonBuilder() : PersonBuilderBase{ p } {}
};

class PersonAddressBuilder : public PersonBuilderBase {
public:
  explicit PersonAddressBuilder(Person &person)
    : PersonBuilderBase{ person } {}

  auto at(std::string street_address) -> PersonAddressBuilder & {
    person.street_address = street_address;
    return *this;
  }

  auto with_postcode(std::string post_code) -> PersonAddressBuilder & {
    person.post_code = post_code;
    return *this;
  }

  auto in(std::string city) -> PersonAddressBuilder & {
    person.city = city;
    return *this;
  }
};

class PersonJobBuilder : public PersonBuilderBase {
public:
  explicit PersonJobBuilder(Person &person)
    : PersonBuilderBase{ person } {}

  auto at(std::string company_name) -> PersonJobBuilder & {
    person.company_name = company_name;
    return *this;
  }

  auto as_a(std::string position) -> PersonJobBuilder & {
    person.position = position;
    return *this;
  }

  auto earning(int annual_income) -> PersonJobBuilder & {
    person.annual_income = annual_income;
    return *this;
  }
};

auto Person::create() -> PersonBuilder {
  return PersonBuilder{};
}

auto PersonBuilderBase::lives() const -> PersonAddressBuilder {
  return PersonAddressBuilder(person);
}

auto PersonBuilderBase::works() const -> PersonJobBuilder {
  return PersonJobBuilder(person);
}

auto main() -> int {
  [[maybe_unused]]
  Person p = Person::create()
    .lives()
      .at("123 London Road")
      .with_postcode("SW1 1GB")
      .in("London")
    .works()
      .at("PragmaSoft")
      .as_a("Consultant")
      .earning(10e6);
}
