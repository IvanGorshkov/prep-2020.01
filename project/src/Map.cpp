//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include "Map.h"


Map::Map(std::istream& is) {
  is >> cols >> rows;
  map_enemy.resize(rows, std::vector<Enemy>(cols, Enemy("", 0, 0)));

  while (is) {
    size_t x = 0;
    size_t y = 0;
    std::string enemy = "";
    is >> x >> y >> enemy;

    if (enemy == "wolf") {
      Enemy wolf(enemy, 6, 11);
      map_enemy[y][x] = wolf;
      continue;
    }

    if (enemy == "dog") {
      Enemy dog(enemy, 3, 6);
      map_enemy[y][x] = dog;
      continue;
    }

    if (enemy == "rat") {
      Enemy rat(enemy, 2, 4);
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
