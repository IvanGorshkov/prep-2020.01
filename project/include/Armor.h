//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <string>
#include "Cell.h"
#include "eCellType.h"

class Armor: public Cell {
 public:
  explicit Armor(std::string name, int wgt, int arm);
  int getWgt() const;
  int getArm() const;
  std::string getName() const;
  eCellTypes get_type() const override;

 private:
  std::string name;
  int wgt;
  int arm;
};
