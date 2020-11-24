#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>

class Database {
public:
  std::unordered_map<std::string, std::string> data;
  static auto get() -> Database & {
    static Database database;
    return database;
  }
  Database(Database const &) = delete;
  Database(Database &&) = delete;
  auto operator=(Database const &) = delete;
  auto operator=(Database &&) = delete;
protected:
  Database() {}
};

auto main() -> int {
  Database::get().data["greeting"] = "Hello, world!";

  std::cout << Database::get().data["greeting"] << std::endl;
}
