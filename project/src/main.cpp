#include <iostream>
#include <fstream>
#include "Controller.h"

int main(int argc, const char** argv) {
  if (argc < 3 && argc > 4) {
    return EXIT_FAILURE;
  }
  std::string key {};
  std::string map_path {};
  std::string stage_2 {};
  int stage = 1;
  for (int num = 0; num < argc; ++num) {
    std::string str = argv[num];
    if (str == "--map") {
      key = str;
    }

    if (str == "--view-armor") {
      stage_2 = str;
      stage = 2;
    }

    if (str != "--view-armor" && str != "--map") {
      map_path = str;
    }
  }

  std::ifstream map_file(map_path);

  if (!map_file) {
    return EXIT_FAILURE;
  }

  Controller game(map_file, stage);

  while (true) {
    if (!game.printActions()) {
      break;
    }

    std::string action{};
    std::getline(std::cin, action);

    if (action.empty()) {
      break;
    }

    if (!game.act(action)) {
      break;
    }
  }
  return 0;
}
