//
// Created by Ivan Gorshkov on 12.04.2020.
//

#ifndef PROJECT_INCLUDE_ENEMY_H_
#define PROJECT_INCLUDE_ENEMY_H_
#include <string>
#include <iostream>
#include "interface.h"

class Enemy: public Fighter {
 public:
    explicit Enemy(std::string name, int hp, unsigned int dmg);
    std::string getName() const;
    bool take_hit(int dmg) override;
    int get_damage() override;
    unsigned int getHp() const;
 private:
    std::string name;
    int hp;
    unsigned int dmg;
};


#endif  // PROJECT_INCLUDE_ENEMY_H_
