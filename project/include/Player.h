//
// Created by Ivan Gorshkov on 11.04.2020.
//

#ifndef PREP_2020_01_PLAYER_H
#define PREP_2020_01_PLAYER_H
#include "Map.h"
#include "interface.h"

typedef struct Position{
    Position(size_t x, size_t y);
    size_t x;
    size_t y;
} Position;

class Player: public Fighter {
public:
    explicit Player(size_t x, size_t y);
    void move(std::string move, Map map);
    Position getPosition() const;
    int getHp() const;
    bool isFight() const;
    bool take_hit(int dmg) override;
    int get_damage() override;
    void stopFight();
private:
    int hp;
    unsigned int dmg;
    Position position;
    bool isFighting = false;
};



#endif //PREP_2020_01_PLAYER_H
