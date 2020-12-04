#include <iostream>
#include <algorithm>
#include <numeric>

struct Creature {
  auto strength() const -> int {
    return abilities[str];
  }
  auto strength(int value) -> void {
    abilities[str] = value;
  }
  auto agility() const -> int {
    return abilities[agl];
  }
  auto agility(int value) -> void {
    abilities[agl] = value;
  }
  auto intelligence() const -> int {
    return abilities[intl];
  }
  auto intelligence(int value) -> void {
    abilities[intl] = value;
  }

  auto sum() const -> int {
    return std::accumulate(abilities.cbegin(), abilities.cend(), 0);
  }
  auto average() const -> double {
    return sum() / (double)count;
  }
  auto max() const -> int {
    return *std::max_element(abilities.cbegin(), abilities.cend());
  }

private:
  enum Abilities : int {
    str,
    agl,
    intl,
    count
  };
  std::array<int, count> abilities;
};

auto main() -> int {
  auto creature = Creature{};
  creature.strength(10);
  creature.agility(5);
  creature.intelligence(12);

  std::cout << "Creature Status" << std::endl;
  std::cout << "Sum     : " << creature.sum() << std::endl;
  std::cout << "Average : " << creature.average() << std::endl;
  std::cout << "Maximum : " << creature.max() << std::endl;
}
