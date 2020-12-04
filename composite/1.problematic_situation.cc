#include <iostream>
#include <algorithm>

struct Creature {
  auto strength() const -> int {
    return _strength;
  }
  auto strength(int value) -> void {
    _strength = value;
  }
  auto agility() const -> int {
    return _agility;
  }
  auto agility(int value) -> void {
    _agility = value;
  }
  auto intelligence() const -> int {
    return _intelligence;
  }
  auto intelligence(int value) -> void {
    _intelligence = value;
  }

  auto sum() const -> int {
    return _strength + _agility + _intelligence;
  }
  auto average() const -> double {
    return sum() / 3.0;
  }
  auto max() const -> int {
    return std::max(std::max(_strength, _agility), _intelligence);
  }

private:
  int _strength;
  int _agility;
  int _intelligence;
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
