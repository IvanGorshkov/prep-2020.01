//
// Created by Ivan Gorshkov on 16.04.2020.
//

#include "Controller.h"
#include <iostream>

Controller::Controller(std::ifstream& is)
                      :map(is)
                      , player(0, 0) {}


bool Controller::printActions() const {
  std::cout << "Supported actions:\n";
  bool in = false;

  if (!player.isFight()) {
    if (player.getPosition().x !=  0) {
      std::cout << " * move left\n";
      in = true;
    }

    if (player.getPosition().x != map.getCols() - 1) {
      std::cout << " * move right\n";
      in = true;
    }

    if (player.getPosition().y != 0) {
      std::cout << " * move down\n";
      in = true;
    }

    if (player.getPosition().y != map.getRows() - 1) {
      std::cout  <<  " * move up\n";
      in = true;
    }

    if (in == false) {
      std::cout << "\n";
    }

    std::cout  << player.getPosition().x << " x " << player.getPosition().y  << ", hp: " <<  player.getHp() << " > ";

    if (map.getRows() == 1 && map.getCols() == 1) {
      return false;
    }

  } else {
    std::cout  << " * kick enemy\n";
    std::cout  << player.getPosition().x << " x " << player.getPosition().y  << ", hp: " <<  player.getHp() << " > ";
  }

  return true;
}

bool Controller::act(std::string_view action) {
  if (action == "move up" || action == "move down" || action == "move left" || action == "move right") {
    player.move(action, map);
  }

  if (action == "kick enemy") {
    return action_kick();
  }

  return true;
}

bool Controller::action_kick() {
  Enemy enemy = map(player.getPosition());

  if (fight(player, enemy)) {
    std::cout << "\nenemy killed\n";
    player.stopFight();
    enemy.setIsAlive(false);
    map(player.getPosition()) = enemy;
    return true;
  }

  if (fight(enemy, player)) {
    std::cout  << "\nplayer died\n";
    return false;
  }

  std::cout << "\nenemy kicked. Enemy hp: " << enemy.getHp() << "\n";
  map(player.getPosition()) = enemy;
  return true;
}

bool Controller::fight(Fighter& attacker, Fighter& defender) {
  return defender.takeHit(attacker.getDamage());
}
