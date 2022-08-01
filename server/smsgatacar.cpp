#include <utility>
#include <vector>
#include "smsgatacar.h"
#include "games.h"

SMsgAtacar::SMsgAtacar(std::vector<int> unitsIDs, int atacadoID) : unitsIDs(std::move(unitsIDs)),
                                                                   atacadoID(atacadoID) {
}

std::vector<int> &SMsgAtacar::getUnitsIDs() {
    return unitsIDs;
}

int SMsgAtacar::getTargetID() {
    return atacadoID;
}

void SMsgAtacar::execute(Game *game) {
    game->atacar(this);
}
