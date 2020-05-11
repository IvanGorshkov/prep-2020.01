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

using armor_vector = std::vector <std::shared_ptr<Armor>>;

class Player: public Fighter  {
 public:
  explicit Player(size_t x, size_t y);
  void move(std::string_view move, Map &map);
  Position& getPosition();
  bool isFight() const;
  void stopFight();
  bool addArmor(Map &map);
  void printArmor() const;
  void dropArmor(std::string_view armor_drop);
  bool notExist(std::string_view check_armor);

 private:
  Position position;
  armor_vector armors;
  bool isFighting = false;
  int wgt;
};
