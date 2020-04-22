//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include <fstream>
#include <iostream>
#include "Exeptions.h"
#include "Map.h"
#include <istream>

Map::Map(std::ifstream& is) {
  is >> cols >> rows;
  if(!is) {
    throw InvalidFileStream();
  }

  map_enemy.resize(rows, std::vector<Enemy>(cols, Enemy("", 0, 0, false)));

  while (!is.eof()) {
    size_t x = 0;
    size_t y = 0;
    std::string enemy{};

    is >> x >> y >> enemy;

    if(!is && !is.eof()) {
      throw InvalidFileStream();
    }

    if (enemy == "wolf") {
      Enemy wolf(enemy, 6, 11, true);
      map_enemy[y][x] = wolf;
      continue;
    }

    if (enemy == "dog") {
      Enemy dog(enemy, 3, 6, true);
      map_enemy[y][x] = dog;
      continue;
    }

    if (enemy == "rat") {
      Enemy rat(enemy, 2, 4, true);
      map_enemy[y][x] = rat;
    }
  }
}

size_t Map::getRows() const {
  return rows;
}

size_t Map::getCols() const {
  return cols;
}
Enemy Map::operator()(Position position) const {
  return map_enemy[position.y][position.x];
}

Enemy& Map::operator()(Position position) {
  return map_enemy[position.y][position.x];
}
