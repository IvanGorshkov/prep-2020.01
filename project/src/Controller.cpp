//
// Created by Ivan Gorshkov on 23.04.2020.
//

#include <iostream>
#include "Controller.h"
#include "Enemy.h"
#include "Armor.h"

Controller::Controller(std::ifstream& is, int stage)
    : map(is)
    , player(std::make_shared<Player>(0, 0))
    , stage(stage) {}

bool Controller::printActions() const {
  std::cout << "Supported actions:\n";
  bool in = false;

  if (!player->isFight()) {
    if (player->getPosition().x !=  0) {
      std::cout << " * move left\n";
      in = true;
    }

    if (player->getPosition().x != map.getCols() - 1) {
      std::cout << " * move right\n";
      in = true;
    }

    if (player->getPosition().y != 0) {
      std::cout << " * move down\n";
      in = true;
    }

    if (player->getPosition().y != map.getRows() - 1) {
      std::cout  <<  " * move up\n";
      in = true;
    }

    if (map(player->getPosition()) != nullptr) {
      if (map(player->getPosition())->get_type() == eCellTypes::ARMOR) {
        std::shared_ptr<Armor> armor = std::static_pointer_cast<Armor>(map(player->getPosition()));
        if (player->notExist(armor->getName())) {
          std::cout << " * pick " << armor->getName() << "\n";
        }
        player->printArmor();
      }
    }

    if (in == false) {
      std::cout << "\n";
    }

    if (stage == 1) {
      std::cout  << player->getPosition().x << " x " << player->getPosition().y  << ", hp: "
                 <<  player->getHp() << " > ";
    } else {
      std::cout  << player->getPosition().x << " x " << player->getPosition().y  << ", hp: "
                 <<  player->getHp() << ", armor: " << player->getArm() << " > ";
    }

    if (map.getRows() == 1 && map.getCols() == 1) {
      return false;
    }
  } else {
    std::cout  << " * kick enemy\n";
    if (stage == 1) {
      std::cout  << player->getPosition().x << " x " << player->getPosition().y  << ", hp: "
                 <<  player->getHp() << " > ";
    } else {
      std::cout  << player->getPosition().x << " x " << player->getPosition().y  << ", hp: "
                 <<  player->getHp() << ", armor: " << player->getArm() << " > ";
    }
  }
  return true;
}

bool Controller::act(std::string_view action) {
  if (action == "move up" || action == "move down" || action == "move left" || action == "move right") {
    player->move(action, map);
  }

  if (action == "kick enemy") {
    return actionKick();
  }

  if (action == "pick pants" || action == "pick armor" || action == "pick helmet"
      || action == "pick shield" || action == "pick T-Shirt") {
    player->addArmor(map);
  }

  if (action == "throw pants" || action == "throw armor" || action == "throw helmet"
      || action == "throw shield" || action == "throw T-Shirt") {
    player->dropArmor(action.substr(6, action.length()));
  }

  return true;
}

bool Controller::actionKick() {
  if (map(player->getPosition())->get_type() == eCellTypes::ENEMY) {
    std::shared_ptr<Enemy> enemy = std::static_pointer_cast<Enemy>(map(player->getPosition()));
    if (fight(player, enemy)) {
      std::cout << "\nenemy killed\n";
      player->stopFight();
      enemy->setIsAlive(false);
      return true;
    }

    if (fight(enemy, player)) {
      std::cout << "\nplayer died\n";
      return false;
    }

    std::cout << "\nenemy kicked. Enemy hp: " << enemy->getHp() << "\n";
  }
  return true;
}

bool Controller::fight(std::shared_ptr<Fighter> attacker, std::shared_ptr<Fighter> defender) {
  if (defender->getArm() >= attacker->getDamage()) {
    return defender->takeHit(1);
  }

  return defender->takeHit(attacker->getDamage() - defender->getArm());
}
