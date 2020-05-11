//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <string>
#include <string_view>
#include "Cell.h"
#include "eCellType.h"

class Armor: public Cell {
 public:
  explicit Armor(std::string_view name, int wgt, int arm);
  int getWgt() const;
  int getArm() const;
  std::string_view getName() const;
  eCellTypes getType() const override;

 private:
  const std::string name;
  int wgt;
  int arm;
};
