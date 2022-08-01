#include "smsgmover.h"

#include <utility>
#include "games.h"

SMsgMover::SMsgMover(std::vector<int> unitsIDs, std::pair<int, int> destination) : unitsIDs(std::move(unitsIDs)),
                                                                                   destination(std::move(destination)) {
}

std::vector<int> &SMsgMover::getUnitsIDs() {
    return unitsIDs;
}

std::pair<int, int> &SMsgMover::getDestination() {
    return destination;
}

void SMsgMover::execute(Game *game) {
    game->mover(this);
}