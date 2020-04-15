//
// Created by Ivan Gorshkov on 12.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, unsigned int dmg)
            : Fighter(hp, dmg)
            , name(name) {}

std::string Enemy::getName() const {
  return name;
}

void Enemy::status() {
  std::cout << std::endl <<  "enemy kicked." << " Enemy hp: " << getHp() << std::endl;
}

void Enemy::findEnemy() {
  std::cout << std::endl << getName() << " found, " << getHp() << " hp" << std::endl;
}
