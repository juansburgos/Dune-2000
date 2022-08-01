#include "cmsgmover.h"

#include <utility>
#include "clientprotocol.h"

CMsgMover::CMsgMover(std::vector<int> unitsIDs, std::pair<int, int> destination) : unitsIDs(std::move(unitsIDs)),
                                                                                   destination(std::move(destination)) {
}

std::vector<int> &CMsgMover::getUnitsIDs() {
    return unitsIDs;
}

std::pair<int, int> &CMsgMover::getDestination() {
    return destination;
}

void CMsgMover::send(ClientProtocol &cProtocol) {
    cProtocol.send(this);
}
