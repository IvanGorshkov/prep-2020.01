//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, unsigned int dmg, int arm, bool is_alive)
    : Fighter(hp, dmg, arm)
    , name(std::move(name))
    , is_alive(is_alive) {}

eCellTypes Enemy::get_type() const {
  return  eCellTypes::ENEMY;
}

std::string Enemy::getName() const {
  return name;
}

bool Enemy::getIsAlive() {
  return is_alive;
}

void Enemy::setIsAlive(bool value) {
  is_alive = value;
}
