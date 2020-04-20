//
// Created by Ivan Gorshkov on 12.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, unsigned int dmg, bool is_alive)
            : Fighter(hp, dmg)
            , name(std::move(name))
            , is_alive(is_alive) {}

std::string Enemy::getName() const {
  return name;
}

void Enemy::status() const {
  std::cout << "\nenemy kicked. Enemy hp: " << getHp() << "\n";
}

void Enemy::findEnemy() const {
  std::cout << "\n" << getName() << " found, " << getHp() << " hp\n";
}

void Enemy::setIsAlive(bool value) {
  is_alive = value;
}

bool Enemy::getIsAlive() {
  return is_alive;
}
