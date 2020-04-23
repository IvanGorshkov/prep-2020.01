//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

#include <memory>
#include <vector>
#include <iosfwd>
#include "Cell.h"
#include "Position.h"

class Map {
 public:
  explicit Map(std::ifstream& is);
  size_t getRows() const;
  size_t getCols() const;
  std::shared_ptr<Cell> operator()(Position position) const;
  void skipArmor(Position position);

 private:
  size_t rows;
  size_t cols;
  std::vector <std::vector <std::shared_ptr <Cell>>> map;
};
