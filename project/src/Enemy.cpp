//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string_view name, int hp, unsigned int dmg, int arm, bool is_alive)
    : Fighter(hp, dmg, arm)
    , name(std::move(name))
    , is_alive(is_alive) {}

eCellTypes Enemy::getType() const {
  return  eCellTypes::ENEMY;
}

std::string_view Enemy::getName() const {
  return name;
}

bool Enemy::getIsAlive() const {
  return is_alive;
}

void Enemy::setIsAlive(bool value) {
  is_alive = value;
}
