//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include "Player.h"

Position::Position(size_t x, size_t y)
                  : x(x),
                  y(y) {}

Player::Player(size_t x, size_t y)
              : Fighter(100, 1),
              position(x, y) {}

void Player::move(std::string move, Map map) {
  int i = 0;

  if (move.compare("move left") == 0) {
    ++i;
    if (position.x == 0) {
      return;
    }
    --(this->position.x);
  }

  if (move.compare("move right") == 0) {
    ++i;
    if (position.x == map.getCols() - 1) {
      return;
    }
    ++(this->position.x);
  }

  if (move.compare("move down") == 0) {
    ++i;
    if (position.y == 0) {
      return;
    }
    --(this->position.y);
  }
  if (move.compare("move up") == 0) {
    ++i;
    if (position.y == map.getRows() - 1) {
      return;
    }
    ++(this->position.y);
  }

  if (map(position.y, position.x).getName().compare("") != 0) {
    map(position.y, position.x).findEnemy();
    isFighting = true;
    return;
  }

  if (i != 0) {
    std::cout << std::endl << "moved" << std::endl;
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

void Player::status() {
  std::cout  << getPosition().x << " x " << getPosition().y  << ", hp: " <<  getHp() << " > ";
}
