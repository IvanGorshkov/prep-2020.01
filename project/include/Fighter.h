//
// Created by Ivan Gorshkov on 23.04.2020.
//

#pragma once

class Fighter {
 public:
  explicit Fighter(int hp, unsigned int dmg,  int arm);
  bool takeHit(int dmg);
  int getDamage() const;
  int getHp() const;
  int getArm() const;

 protected:
  int hp;
  unsigned int dmg;
  int point_armor;
};
