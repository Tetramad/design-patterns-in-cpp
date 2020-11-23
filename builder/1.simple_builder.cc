#include <string>
#include <iostream>
#include <vector>
#include <sstream>

struct HTMLElement {
  std::string name;
  std::string text;
  std::vector<HTMLElement> elements;

  HTMLElement() {}
  HTMLElement(std::string const & name, std::string const &text)
    : name(name), text(text) {}

  auto str([[maybe_unused]] int indent = 0) const -> std::string {
    std::ostringstream oss;
    oss << "<" << name << ">" << text;
    for (auto const &e : elements) {
      oss << e.str();
    }
    oss << "</" << name << ">";
    return oss.str();
  }
};

struct HTMLBuilder {
  HTMLElement root;

  HTMLBuilder(std::string root_name) {
    root.name = root_name;
  }

  auto add_child(std::string child_name, std::string child_text) -> void {
    HTMLElement e{ child_name, child_text };
    root.elements.emplace_back(e);
  }

  auto str() -> std::string {
    return root.str();
  }
};

auto main() -> int {
  using std::cout, std::endl;

  HTMLBuilder builder{ "ul" };
  builder.add_child("li", "hello");
  builder.add_child("li", "world");
  cout << builder.str() << endl;
}
