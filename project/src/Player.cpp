//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include <iostream>
#include "Player.h"
#include "Map.h"

Player::Player(size_t x, size_t y)
              : Fighter(100, 1),
              position{x, y} {}

void Player::move(std::string_view move, const Map &map) {
  int i = 0;

  if (move == "move left") {
    ++i;
    if (position.x == 0) {
      return;
    }
    --position.x;
  }

  if (move == "move right") {
    ++i;
    if (position.x == map.getCols() - 1) {
      return;
    }
    ++position.x;
  }

  if (move == "move down") {
    ++i;
    if (position.y == 0) {
      return;
    }
    --position.y;
  }
  if (move == "move up") {
    ++i;
    if (position.y == map.getRows() - 1) {
      return;
    }
    ++position.y;
  }

  if (map(position).getIsAlive()) {
    std::cout << "\n" << map(position).getName() << " found, " << map(position).getHp() << " hp\n";
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

