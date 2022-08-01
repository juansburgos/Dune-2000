#ifndef DUNE_CMSGATACAR_H
#define DUNE_CMSGATACAR_H

#include "cmsg.h"
#include <vector>

class CMsgAtacar : public CMsg {
    std::vector<int> unitsIDs;
    int atacadoID;
public:
    CMsgAtacar(std::vector<int> unitsIDs, int atacadoID);

    std::vector<int> &getUnitsIDs();

    int getAtacadoID() const;

    void send(ClientProtocol &cProtocol) override;
};

#endif //DUNE_CMSGATACAR_H
