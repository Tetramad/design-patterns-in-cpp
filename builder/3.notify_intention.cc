#include <string>
#include <iostream>
#include <vector>
#include <sstream>

struct HTMLElement;
struct HTMLBuilder;

struct HTMLElement {
  friend HTMLBuilder;
  std::string name;
  std::string text;
  std::vector<HTMLElement> elements;

  static auto build(std::string const &root_name) -> HTMLBuilder;
  auto str(int indent) const -> std::string;
protected:
  HTMLElement();
  HTMLElement(std::string const & name, std::string const &text);
};

struct HTMLBuilder {
  HTMLElement root;

  HTMLBuilder(std::string root_name);
  auto add_child(std::string child_name, std::string child_text) -> HTMLBuilder &;
  operator HTMLElement() const;
};

auto HTMLElement::build(std::string const &root_name) -> HTMLBuilder {
  return HTMLBuilder(root_name);
}

auto HTMLElement::str([[maybe_unused]] int indent = 0) const -> std::string {
  std::ostringstream oss;
  oss << "<" << name << ">" << text;
  for (auto const &e : elements) {
    oss << e.str();
  }
  oss << "</" << name << ">";
  return oss.str();
}

HTMLElement::HTMLElement() {}
HTMLElement::HTMLElement(std::string const & name, std::string const &text)
  : name(name), text(text) {}

HTMLBuilder::HTMLBuilder(std::string root_name) {
  root.name = root_name;
}

auto HTMLBuilder::add_child(std::string child_name, std::string child_text) -> HTMLBuilder & {
  HTMLElement e{ child_name, child_text };
  root.elements.emplace_back(e);
  return *this;
}

HTMLBuilder::operator HTMLElement() const {
  return root;
}

auto main() -> int {
  using std::cout, std::endl;

  HTMLElement e = HTMLElement::build("ul")
    .add_child("li", "hello")
    .add_child("li", "world");
  cout << e.str() << endl;
}
