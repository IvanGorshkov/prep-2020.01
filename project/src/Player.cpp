//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include <iostream>
#include <memory>
#include <algorithm>
#include "Player.h"
#include "Map.h"
#include "Enemy.h"

Player::Player(size_t x, size_t y)
    : Fighter(100, 1, 0)
    , position{x, y}
    , wgt(0) {}

void Player::move(std::string_view move, Map &map) {
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

  if (map(position) != nullptr) {
    if (map(position)->getType() == eCellTypes::ENEMY) {
      std::shared_ptr<Enemy> enemy = std::static_pointer_cast<Enemy>(map(position));
      if (enemy->getIsAlive()) {
        std::cout << "\n" << enemy->getName() << " found, " << enemy->getHp() << " hp\n";
        isFighting = true;
        return;
      }
    }

    if (map(position)->getType() == eCellTypes::ARMOR) {
      std::shared_ptr<Armor> armor = std::static_pointer_cast<Armor>(map(position));
      std::cout << "\n" << armor->getName() << " found\n";
      return;
    }
  }

  if (i != 0) {
    std::cout << "\nmoved\n";
  }
}

Position& Player::getPosition() {
  return position;
}

bool Player::isFight() const {
  return isFighting;
}

void Player::stopFight() {
  isFighting = false;
}

static bool compareInterval(std::shared_ptr<Armor> ar1, std::shared_ptr<Armor> ar2) {
  return (ar1->getName() < ar2->getName());
}

bool Player::addArmor(Map &map) {
  if (map(getPosition()) != nullptr) {
    if (map(getPosition())->getType() == eCellTypes::ARMOR) {
      std::shared_ptr<Armor> armor = std::static_pointer_cast<Armor>(map(getPosition()));
      if (wgt <= 20) {
        armors.push_back(armor);
        std::sort(armors.begin(), armors.end(), compareInterval);
        std::cout << "\nclothes worn\n";
        point_armor += armor->getArm();
        wgt += armor->getWgt();
        return true;
      }
    }
  }
  return false;
}

void Player::printArmor() const {
  for (const auto& armor : armors) {
    std::cout << " * throw " << armor->getName() << "\n";
  }
}

void Player::dropArmor(std::string_view armor_drop) {
  int i = 0;
  bool is_found = false;
  for (const auto& armor : armors) {
    if (armor->getName() == armor_drop) {
      is_found = true;
      break;
    }
    i++;
  }

  if (is_found) {
    point_armor -= armors[i]->getArm();
    wgt -= armors[i]->getWgt();
    armors.erase(armors.begin() + i);
    std::cout << "\nthe " << armor_drop <<" is thrown out\n";
  }
}

bool Player::notExist(std::string_view check_armor) {
  for (const auto& armor : armors) {
    if (armor->getName() == check_armor) {
      return false;
    }
  }
  return true;
}
