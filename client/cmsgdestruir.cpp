#include "cmsgdestruir.h"

CMsgDestruir::CMsgDestruir(int playerID, int buildingID) : playerID(playerID), buildingID(buildingID) {}

int CMsgDestruir::getBuildingId() {
    return buildingID;
}

int CMsgDestruir::getPlayerID() {
    return playerID;
}

void CMsgDestruir::send(ClientProtocol &cProtocol) {
    cProtocol.send(this);
}
