//
// Created by Ivan Gorshkov on 11.04.2020.
//

#ifndef PROJECT_INCLUDE_FIGHTER_H_
#define PROJECT_INCLUDE_FIGHTER_H_

class Fighter {
 public:
  explicit Fighter(int hp, unsigned int dmg);
  bool take_hit(int dmg);
  int get_damage();
  int getHp() const;
 protected:
  int hp;
  unsigned int dmg;
};

#endif  // PROJECT_INCLUDE_FIGHTER_H_
