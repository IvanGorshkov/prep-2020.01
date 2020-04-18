//
// Created by Ivan Gorshkov on 12.04.2020.
//

#pragma once

#include <iostream>
#include <string>
#include "Fighter.h"

class Enemy: public Fighter {
 public:
  explicit Enemy(std::string name, int hp, unsigned int dmg);
  std::string getName() const;
  void status();
  void findEnemy();

 private:
  std::string name;
};
