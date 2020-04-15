//
// Created by Ivan Gorshkov on 16.04.2020.
//

#include "Controller.h"

Controller::Controller(std::istream& is)
                      :map(is)
                      , player(0, 0) {}


bool Controller::printActions() {
  std::cout << "Supported actions:" << std::endl;
  std::string action = "";
  bool in = false;
  if (!player.isFight()) {
    if (player.getPosition().x !=  0) {
      std::cout << " * move left" << std::endl;
      in = true;
    }

    if (player.getPosition().x != map.getCols() - 1) {
      std::cout << " * move right" << std::endl;
      in = true;
    }

    if (player.getPosition().y != 0) {
      std::cout << " * move down" << std::endl;
      in = true;
    }

    if (player.getPosition().y != map.getRows() - 1) {
      std::cout  <<  " * move up" << std::endl;
      in = true;
    }

    if (in == false) {
      std::cout << std::endl;
    }

    player.status();

    if (map.getRows() == 1 && map.getCols() == 1) {
      return false;
    }

  } else {
    std::cout  << " * kick enemy" << std::endl;
    player.status();
  }

  return true;
}

bool Controller::action(std::string action) {
  if ((action.compare(0, 4, "move")) == 0) {
    player.move(action, map);
  }

  if ((action.compare("kick enemy")) == 0) {
    return action_kick();
  }

  return true;
}
bool Controller::action_kick() {
  Enemy enemy = map(player.getPosition().y, player.getPosition().x);

  if (fight(player, enemy)) {
    std::cout << std::endl << "enemy killed" << std::endl;
    player.stopFight();
    Enemy enemy_killed = Enemy("", 0, 0);
    map.setValue(player.getPosition().y, player.getPosition().x, enemy_killed);
    return true;
  }

  if (fight(enemy, player)) {
    std::cout << std::endl <<  "player died" << std::endl;
    return false;
  }

  enemy.status();
  map.setValue(player.getPosition().y, player.getPosition().x, enemy);
  return true;
}

bool Controller::fight(Fighter& attacker, Fighter& defender) {
  return defender.take_hit(attacker.get_damage());
}
