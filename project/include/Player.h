//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <utility>
#include <string_view>
#include <vector>
#include <memory>
#include "Fighter.h"
#include "Position.h"
#include "Armor.h"
class Map;

class Player: public Fighter  {
 public:
  explicit Player(size_t x, size_t y);
  void move(std::string_view move, Map &map);
  Position getPosition() const;
  bool isFight() const;
  void stopFight();
  void addArmor(Map &map);
  void printArmor();
  void dropArmor(std::string_view armor_drop);
  bool notExist(std::string_view check_armor);

 private:
  Position position;
  std::vector <std::shared_ptr<Armor>> armors;
  bool isFighting = false;
  int wgt;
};
