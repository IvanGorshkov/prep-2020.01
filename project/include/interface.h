//
// Created by Ivan Gorshkov on 11.04.2020.
//

#ifndef PROJECT_INCLUDE_INTERFACE_H_
#define PROJECT_INCLUDE_INTERFACE_H_

class Fighter {
 public:
    virtual bool take_hit(int dmg) = 0;
    virtual int get_damage() = 0;
    virtual ~Fighter() {}
};

#endif  // PROJECT_INCLUDE_INTERFACE_H_
