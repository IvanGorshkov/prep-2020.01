//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include "eCellType.h"

class Cell {
 public:
  Cell() = default;
  virtual ~Cell() {}
  virtual eCellTypes getType() const;
};
