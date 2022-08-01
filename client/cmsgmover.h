#ifndef DUNE_CMSGMOVER_H
#define DUNE_CMSGMOVER_H

#include <vector>
#include "cmsg.h"

class CMsgMover : public CMsg {
    std::vector<int> unitsIDs;
    std::pair<int, int> destination;
public:
    CMsgMover(std::vector<int> unitsIDs, std::pair<int, int> destination);

    std::vector<int> &getUnitsIDs();

    std::pair<int, int> &getDestination();

    void send(ClientProtocol &cProtocol) override;
};

#endif //DUNE_CMSGMOVER_H
