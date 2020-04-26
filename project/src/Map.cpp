//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include <fstream>
#include "Map.h"
#include "Enemy.h"
#include "Armor.h"
#include "Exeptions.h"

Map::Map(std::ifstream& is) {
  is >> cols >> rows;
  if (!is) {
    throw InvalidFileStream();
  }

  map.resize(rows, std::vector<std::shared_ptr <Cell>>(cols));
  while (!is.eof()) {
    size_t x = 0;
    size_t y = 0;
    std::string value{};

    is >> x >> y >> value;

    if (!is && !is.eof()) {
      throw InvalidFileStream();
    }

    if (value == "wolf") {
      map[y][x] = std::make_shared<Enemy>(Enemy(value, 6, 11, 0, true));
      continue;
    }

    if (value == "dog") {
      map[y][x] = std::make_shared<Enemy>(Enemy(value, 3, 6, 0, true));
      continue;
    }

    if (value == "rat") {
      map[y][x] = std::make_shared<Enemy>(Enemy(value, 2, 4, 0, true));
      continue;
    }

    if (value == "armor") {
      map[y][x] =  std::make_shared<Armor>(Armor(value, 3, 3));
    }

    if (value == "helmet") {
      map[y][x] =  std::make_shared<Armor>(Armor(value, 2, 3));
    }

    if (value == "shield") {
      map[y][x] =  std::make_shared<Armor>(Armor(value, 7, 5));
    }

    if (value == "pants") {
      map[y][x] =  std::make_shared<Armor>(Armor(value, 1, 1));
    }

    if (value == "T-Shirt") {
      map[y][x] =  std::make_shared<Armor>(Armor(value, 1, 1));
    }
  }
}

size_t Map::getRows() const {
  return rows;
}

size_t Map::getCols() const {
  return cols;
}

std::shared_ptr <Cell> Map::operator()(Position &position) const {
  return map[position.y][position.x];
}

void Map::skipArmor(Position &position) {
  map[position.y][position.x] = nullptr;
}
