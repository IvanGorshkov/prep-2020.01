//
// Created by Ivan Gorshkov on 12.04.2020.
//

#pragma once

#include <iosfwd>
#include <string>
#include "Fighter.h"

class Enemy: public Fighter {
 public:
  explicit Enemy(std::string name, int hp, unsigned int dmg, bool is_alive);
  std::string getName() const;
  void status() const;
  void findEnemy() const;
  void setIsAlive(bool value);
  bool getIsAlive();
 private:
  std::string name;
  bool is_alive;
};
