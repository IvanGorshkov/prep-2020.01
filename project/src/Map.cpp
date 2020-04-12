//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include "Map.h"

Map::Map(std::istream& is) {
    rows = 0;
    cols = 0;
    is >> cols >> rows;
    map_enemy.resize(rows, std::vector<Enemy>(cols, Enemy("", 0, 0)));
    size_t x = 0;
    size_t y = 0;

    while (is) {
        std::string enemy = "";
        is >> x >> y >> enemy;

        if (enemy.compare("wolf") == 0) {
            Enemy wolf(enemy, 6, 11);
            map_enemy[y][x] = wolf;
        }

        if (enemy.compare("dog") == 0) {
            Enemy dog(enemy, 3, 6);
            map_enemy[y][x] = dog;
        }

        if (enemy.compare("rat") == 0) {
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
Enemy Map::operator()(size_t i, size_t j) {
    return map_enemy[i][j];
}

void Map::setValue(size_t i, size_t j, Enemy& enemy) {
    map_enemy[i][j] = enemy;
}
