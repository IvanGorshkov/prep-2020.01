//
// Created by Ivan Gorshkov on 12.04.2020.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, unsigned int dmg): name(name), hp(hp), dmg(dmg) {}

bool Enemy::take_hit(int dmg) {
    hp -= dmg;

    if (hp > 0) {
        return false;
    }

    return true;
}

int Enemy::get_damage() {
    return dmg;
}

std::string Enemy::getName() const {
    return name;
}

unsigned int Enemy::getHp() const {
    return hp;
}
