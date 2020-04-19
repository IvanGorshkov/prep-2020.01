//
// Created by Ivan Gorshkov on 11.04.2020.
//

#pragma once

#include <utility>
#include <string>
#include "Map.h"
#include "Fighter.h"


class Player: public Fighter {
 public:
  explicit Player(size_t x, size_t y);
  void move(std::string_view move, const Map &map);
  Position getPosition() const;
  bool isFight() const;
  void stopFight();
  void status() const;

 private:
  Position position;
  bool isFighting = false;
};
