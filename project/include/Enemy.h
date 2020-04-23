//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <string>
#include "Cell.h"
#include "Fighter.h"
#include "eCellType.h"

class Enemy: public Cell, public Fighter {
 public:
  explicit Enemy(std::string name, int hp, unsigned int dmg, int arm, bool is_alive);
  eCellTypes get_type() const override;
  std::string getName() const;
  void setIsAlive(bool value);
  bool getIsAlive();

 private:
  std::string name;
  bool is_alive;
};
