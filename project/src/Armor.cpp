//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include "Armor.h"

Armor::Armor(std::string name, int wgt, int arm)
    : name(name)
    , wgt(wgt)
    , arm(arm) {}

int Armor::getWgt() const {
  return wgt;
}

int Armor::getArm() const {
  return arm;
}

std::string Armor::getName() const {
  return name;
}

eCellTypes Armor::get_type() const {
  return eCellTypes::ARMOR;
}
