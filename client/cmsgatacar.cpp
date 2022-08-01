#include "cmsgatacar.h"

#include <utility>
#include "clientprotocol.h"

CMsgAtacar::CMsgAtacar(std::vector<int> unitsIDs, int atacadoID) : unitsIDs(std::move(unitsIDs)),
                                                                   atacadoID(atacadoID) {
}

std::vector<int> &CMsgAtacar::getUnitsIDs() {
    return unitsIDs;
}

int CMsgAtacar::getAtacadoID() const {
    return atacadoID;
}

void CMsgAtacar::send(ClientProtocol &cProtocol) {
    cProtocol.send(this);
}