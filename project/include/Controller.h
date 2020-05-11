//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <string_view>
#include <iosfwd>
#include <memory>
#include "Map.h"
#include "Player.h"

class Controller {
 public:
  explicit Controller(std::ifstream& is, int stage);
  bool printActions() const;
  bool act(std::string_view action);

 private:
  bool fight(std::shared_ptr<Fighter> attacker, std::shared_ptr<Fighter> defender);
  bool actionKick();
  Map map;
  std::shared_ptr<Player> player;
  int stage;
};
