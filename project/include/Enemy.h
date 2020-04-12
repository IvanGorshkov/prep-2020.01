//
// Created by Ivan Gorshkov on 12.04.2020.
//

#ifndef PREP_2020_01_ENEMY_H
#define PREP_2020_01_ENEMY_H
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


#endif //PREP_2020_01_ENEMY_H
