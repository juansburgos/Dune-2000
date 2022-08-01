#ifndef DUNE_SMSGATACAR_H
#define DUNE_SMSGATACAR_H

#include <vector>

#include "smsg.h"
class SMsgAtacar : public SMsg {
    std::vector<int> unitsIDs;
    int atacadoID;

   public:
    SMsgAtacar(std::vector<int> unitsIDs, int atacadoID);

    std::vector<int> &getUnitsIDs();

    int getTargetID();

    void execute(Game *game) override;
};

#endif  // DUNE_SMSGATACAR_H
