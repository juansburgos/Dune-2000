#ifndef DUNE_SMSGMOVER_H
#define DUNE_SMSGMOVER_H

#include <vector>
#include "smsg.h"

class SMsgMover : public SMsg {
    std::vector<int> unitsIDs;
    std::pair<int, int> destination;
public:
    SMsgMover(std::vector<int> unitsIDs, std::pair<int, int> destination);

    std::vector<int> &getUnitsIDs();

    std::pair<int, int> &getDestination();

    void execute(Game *game) override;
};

#endif //DUNE_SMSGMOVER_H
