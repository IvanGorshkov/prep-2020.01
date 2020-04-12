//
// Created by Ivan Gorshkov on 13.04.2020.
//
#include "Fighter.h"

Fighter::Fighter(int hp, unsigned int dmg): hp(hp), dmg(dmg) {}

int Fighter::getHp() const {
  return hp;
}

bool Fighter::take_hit(int dmg) {
  hp -= dmg;

  if (hp > 0) {
    return false;
  }

  return true;
}

int Fighter::get_damage() {
  return dmg;
}