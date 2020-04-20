//
// Created by Ivan Gorshkov on 11.04.2020.
//

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Enemy.h"
#include "Position.h"

class Map {
 public:
  explicit Map(std::istream& is);
  size_t getRows() const;
  size_t getCols() const;
  Enemy operator()(Position position) const;
  Enemy& operator()(Position position);

 private:
  size_t rows;
  size_t cols;
  std::vector <std::vector <Enemy>> map_enemy;
};
