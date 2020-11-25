#include <iostream>

#include "1.pimpl.hh"

struct Person::PersonImpl {
  auto greet(Person *p) -> void;
};

Person::Person() : impl(new PersonImpl) {}

Person::Person(std::string name) : name(name), impl(new PersonImpl) {}

Person::~Person() { delete impl; }


auto Person::greet() -> void {
  impl->greet(this);
}

auto Person::PersonImpl::greet(Person *p) -> void {
  std::cout << "Hello " << p->name << std::endl;
}
