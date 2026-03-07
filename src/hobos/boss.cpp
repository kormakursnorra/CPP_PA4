#include "boss.h"


Boss::Boss(const std::string name, std::string zooName)
    : EnemyHobo(name, zooName), enraged(false) {}

// Move* Boss::strongestMove() {
    
//     return ;
// }

// Move* Boss::nextAction() {
    // check if boss is mad
    // if (!enraged && hp < maxHp / 2) {
    //     enraged = true;
    //     std::cout << "\n*** " << getName()
    //             << " is enraged! ***\n";
    // }

    // if (enraged) {
    //     std::cout << getName() << " is overwhelmed with fury!\n";
    //     return strongestMove();
    // }

    // return Enemy::chooseAction();
// }
