//
// Created by Ivan Gorshkov on 11.04.2020.
//
#pragma once

class Fighter {
 public:
  explicit Fighter(int hp, unsigned int dmg);
  bool takeHit(int dmg);
  int getDamage();
  int getHp() const;

 protected:
  int hp;
  unsigned int dmg;
};
