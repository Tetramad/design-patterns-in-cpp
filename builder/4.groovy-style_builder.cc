#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <initializer_list>

struct Tag {
  std::string name;
  std::string text;
  std::vector<Tag> children;
  std::vector<std::pair<std::string, std::string>> attributes;

  friend auto operator<<(std::ostream &os, [[maybe_unused]] Tag const &tag) -> std::ostream & {
    std::cout << "<" << tag.name;
    for (auto const &a : tag.attributes) {
      std::cout << " " << a.first << "=" << a.second;
    }
    std::cout << ">";
    std::cout << tag.text;
    for (auto const &c : tag.children) {
      std::cout << c;
    }
    std::cout << "</" << tag.name << ">";
    return os;
  }

protected:
  Tag(std::string const &name, std::string const &text)
    : name{name}, text{text} {}
  Tag(std::string const &name, std::vector<Tag> const &children)
    : name{name}, children{children} {}
};

struct P final : Tag {
  explicit P(std::string const &text)
    : Tag{"p", text} {}
  P(std::initializer_list<Tag> children)
    : Tag{"p", children} {}
};

struct IMG final : Tag {
  explicit IMG(std::string const &url)
    : Tag{"img", ""} {
      attributes.emplace_back("src", url);
    }
};

auto main() -> int {
  std::cout <<
    P {
      IMG { "http://pokemon.com/pikachu.png" }
    }
  << std::endl;
}
