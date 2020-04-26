//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include "Armor.h"

Armor::Armor(std::string_view name, int wgt, int arm)
    : name(name)
    , wgt(wgt)
    , arm(arm) {}

int Armor::getWgt() const {
  return wgt;
}

int Armor::getArm() const {
  return arm;
}

std::string_view Armor::getName() const {
  return name;
}

eCellTypes Armor::getType() const {
  return eCellTypes::ARMOR;
}
