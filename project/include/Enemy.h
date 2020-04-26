//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <string>
#include <string_view>
#include "Cell.h"
#include "Fighter.h"
#include "eCellType.h"

class Enemy: public Cell, public Fighter {
 public:
  explicit Enemy(std::string_view name, int hp, unsigned int dmg, int arm, bool is_alive);
  eCellTypes getType() const override;
  std::string_view getName() const;
  void setIsAlive(bool value);
  bool getIsAlive() const;

 private:
  const std::string name;
  bool is_alive;
};
