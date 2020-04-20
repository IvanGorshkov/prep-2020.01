//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include "Player.h"
#include "Map.h"

Player::Player(size_t x, size_t y)
              : Fighter(100, 1),
              position{x, y} {}

void Player::move(std::string_view move, const Map &map) {
  int i = 0;

  if (move.compare("move left") == 0) {
    ++i;
    if (position.x == 0) {
      return;
    }
    --position.x;
  }

  if (move.compare("move right") == 0) {
    ++i;
    if (position.x == map.getCols() - 1) {
      return;
    }
    ++position.x;
  }

  if (move.compare("move down") == 0) {
    ++i;
    if (position.y == 0) {
      return;
    }
    --position.y;
  }
  if (move.compare("move up") == 0) {
    ++i;
    if (position.y == map.getRows() - 1) {
      return;
    }
    ++position.y;
  }

  if (map(position).getIsAlive()) {
    map(position).findEnemy();
    isFighting = true;
    return;
  }

  if (i != 0) {
    std::cout << "\nmoved\n";
  }
}

Position Player::getPosition() const {
  return position;
}

bool Player::isFight() const {
  return isFighting;
}

void Player::stopFight() {
  isFighting = false;
}

void Player::status() const {
  std::cout  << getPosition().x << " x " << getPosition().y  << ", hp: " <<  getHp() << " > ";
}
