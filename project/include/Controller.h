//
// Created by Ivan Gorshkov on 16.04.2020.
//

#pragma once

#include <string>
#include "Map.h"
#include "Player.h"

class Controller {
 public:
  explicit Controller(std::istream& is);
  bool printActions();
  bool action(std::string action);
  bool fight(Fighter& attacker, Fighter& defender);
  bool action_kick();
 private:
  Map map;
  Player player;
};
