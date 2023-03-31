#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy() {}

PlayerStrategy::PlayerStrategy(Player* player) {
    p = player;
}

PlayerStrategy::~PlayerStrategy() {
    delete p;
    p = nullptr;
}

Human::Human() {}

Human::Human(Player* player) : PlayerStrategy(player) {}

Human::~Human() {

}

bool Human::issueOrder() {
    return 0;
}

vector<Territory* >* Human::toAttack() {
    return p->getPlayerTerritories();
}

vector<Territory* >* Human::toDefend() {
    return p->getPlayerTerritories();
}