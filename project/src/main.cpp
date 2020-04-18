#include "Player.h"
#include "Controller.h"

int main(int argc, const char** argv) {
  if (argc != 3) {
    return EXIT_FAILURE;
  }

  const std::string key = argv[1];
  const std::string map_path = argv[2];

  if (key != "--map") {
    return EXIT_FAILURE;
  }

  std::ifstream map_file(map_path);

  if (!map_file) {
    return EXIT_FAILURE;
  }

  Controller game(map_file);

  while (true) {
    if (!game.printActions()) {
      break;
    }

    std::string action = "";
    std::getline(std::cin, action);

    if (action.empty()) {
      break;
    }

    if (!game.action(action)) {
      break;
    }
  }

  return 0;
}
