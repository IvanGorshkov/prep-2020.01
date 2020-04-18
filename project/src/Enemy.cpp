//
// Created by Ivan Gorshkov on 12.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, unsigned int dmg)
            : Fighter(hp, dmg)
            , name(std::move(name)) {}

std::string Enemy::getName() const {
  return name;
}

void Enemy::status() {
  std::cout << "\nenemy kicked. Enemy hp: " << getHp() << "\n";
}

void Enemy::findEnemy() {
  std::cout << "\n" << getName() << " found, " << getHp() << " hp\n";
}
