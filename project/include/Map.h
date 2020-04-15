//
// Created by Ivan Gorshkov on 11.04.2020.
//

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Enemy.h"

class Map {
 public:
  explicit Map(std::istream& is);
  size_t getRows() const;
  size_t getCols() const;
  Enemy operator()(size_t i, size_t j);
  void setValue(size_t i, size_t j, Enemy& enemy);

 private:
  size_t rows;
  size_t cols;
  std::vector <std::vector <Enemy>> map_enemy;
};
