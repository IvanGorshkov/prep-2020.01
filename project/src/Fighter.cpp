//
// Created by Ivan Gorshkov on 13.04.2020.
//
#include "Fighter.h"

Fighter::Fighter(int hp, unsigned int dmg)
                : hp(hp)
                , dmg(dmg) {}

int Fighter::getHp() const {
  return hp;
}

bool Fighter::takeHit(int dmg) {
  hp -= dmg;
  return hp > 0 ? false : true;
}

int Fighter::getDamage() {
  return dmg;
}
