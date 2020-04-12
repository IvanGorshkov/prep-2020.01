//
// Created by Ivan Gorshkov on 11.04.2020.
//

#ifndef PREP_2020_01_INTERFACE_H
#define PREP_2020_01_INTERFACE_H

class Fighter {
public:
    virtual bool take_hit(int dmg) = 0;
    virtual int get_damage() = 0;
    virtual ~Fighter() {};
};

#endif //PREP_2020_01_INTERFACE_H
