#include "Player.h"
#include <memory>

bool fight(Fighter& attacker, Fighter& defender) {
    return defender.take_hit(attacker.get_damage());
}


int main(int argc, const char** argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    const std::string key = argv[1];
    const std::string map_path = argv[2];

    if (key.compare("--map") != 0) {
        return EXIT_FAILURE;
    }

    std::ifstream map_file(map_path);
    Map map(map_file);
    Player player(0, 0);

    while (true) {
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

            std::cout  << player.getPosition().x << " x " << player.getPosition().y  << ", hp: " <<  player.getHp() << " > ";

            if (map.getRows() == 1 && map.getCols() == 1) {
                break;
            }

            std::getline(std::cin, action);

            if (action.compare("\0") == 0) {
                break;
            }

            player.move(action, map);
        } else {
            std::cout  << " * kick enemy" << std::endl;
            std::cout << player.getPosition().x << " x " << player.getPosition().y   << ", hp: " <<  player.getHp() << " > ";
            std::getline(std::cin, action);

            if ((action.compare("kick enemy") == 0)) {
                Enemy enemy = map(player.getPosition().y, player.getPosition().x);

                if (fight(player, enemy)) {
                    std::cout << std::endl << "enemy killed" << std::endl;
                    player.stopFight();
                    Enemy enemy_killed = Enemy("", 0, 0);
                    map.setValue(player.getPosition().y, player.getPosition().x, enemy_killed);
                    continue;
                }

                if (fight(enemy, player)) {
                    std::cout << std::endl <<  "player died" << std::endl;
                    break;
                }

                std::cout << std::endl <<  "enemy kicked." << " Enemy hp: " << enemy.getHp() << std::endl;
                map.setValue(player.getPosition().y, player.getPosition().x, enemy);
            }
        }
    }

    return 0;
}
