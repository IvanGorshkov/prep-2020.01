//
// Created by Ivan Gorshkov on 16.04.2020.
//

#pragma once

#include <iostream>
#include "Map.h"
#include "Player.h"

class Controller {
 public:
  explicit Controller(std::istream& is);
  bool printActions();
  bool action(std::string_view action);
  bool fight(Fighter& attacker, Fighter& defender);
  bool action_kick();

 private:
  Map map;
  Player player;
};
