//
// Created by Ivan Gorshkov on 16.04.2020.
//

#pragma once

#include <string_view>
#include <iosfwd>
#include "Map.h"
#include "Player.h"

class Controller {
 public:
  explicit Controller(std::ifstream& is);
  bool printActions() const;
  bool act(std::string_view action);
  bool fight(Fighter& attacker, Fighter& defender);
  bool action_kick();

 private:
  Map map;
  Player player;
};

