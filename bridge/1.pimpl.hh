#pragma once

#include <string>

struct Person {
  std::string name;
  auto greet() -> void;

  Person();
  Person(std::string name);
  ~Person();

  class PersonImpl;
  PersonImpl *impl;
};
