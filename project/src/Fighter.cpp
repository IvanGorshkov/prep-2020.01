//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include "Fighter.h"

Fighter::Fighter(int hp, unsigned int dmg,  int arm)
    : hp(hp)
    , dmg(dmg)
    , point_armor(arm) {}

int Fighter::getHp() const {
  return hp;
}

bool Fighter::takeHit(int dmg) {
  hp -= dmg;
  return hp > 0 ? false : true;
}

int Fighter::getDamage() const {
  return dmg;
}

int Fighter::getArm() const {
  return point_armor;
}
