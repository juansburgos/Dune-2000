
#include "smsgdestruir.h"

SMsgDestruir::SMsgDestruir(int playerID, int buildingID) : playerID(playerID), buildingID(buildingID) {}

void SMsgDestruir::execute(Game *game) {
    game->destruir(this);
}
