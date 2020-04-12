//
// Created by Ivan Gorshkov on 11.04.2020.
//

#include "Player.h"

Position::Position(size_t x, size_t y) {
    this->x = x;
    this->y = y;
}

Player::Player(size_t x, size_t y): hp(100), dmg(1), position(x,y) {}
void Player::move(std::string move, Map map) {
    int i = 0;
    if (move.compare("move left") == 0) {
        i++;
        if (position.x == 0) {
            return;
        }
        this->position.x--;
    }
    if (move.compare("move right") == 0) {
        i++;
        if (position.x == map.getCols() - 1) {
            return;
        }
        this->position.x++;
    }
    if (move.compare("move down") == 0) {
        i++;
        if (position.y == 0) {
            return;
        }
        this->position.y--;
    }
    if (move.compare("move up") == 0) {
        i++;
        if (position.y == map.getRows() - 1) {
            return;
        }
        this->position.y++;
    }

    if (map(position.y, position.x).getName().compare("") != 0 ) {
        std::cout << std::endl << map(position.y, position.x).getName() << " found, " << map(position.y, position.x).getHp() << " hp" << std::endl;
        isFighting = true;
        return;
    }

    if (i != 0) {
        std::cout << std::endl << "moved" << std::endl;
    }
}

Position Player::getPosition() const{
    return position;
}

int Player::getHp() const{
    return hp;
}

bool Player::isFight() const{
    return isFighting;
}

bool Player::take_hit(int dmg) {
    hp -= dmg;
    if (hp > 0) {
        return false;
    } else {
        return true;
    }
}

int Player::get_damage() {
    return dmg;
}
void Player::stopFight() {
    isFighting = false;
}