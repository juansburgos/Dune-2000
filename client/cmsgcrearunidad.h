#ifndef DUNE_CMSGCREARUNIDAD_H
#define DUNE_CMSGCREARUNIDAD_H

#include <utility>
#include "cmsg.h"

class CMsgCrearUnidad : public CMsg {
    int type;
    int playerID;
    std::pair<int, int> position;
public:
    CMsgCrearUnidad(int type, int playerID, std::pair<int, int> position);

    void send(ClientProtocol &cProtocol) override;

    int getType() { return type; }

    int getPlayerID() { return playerID; }

    std::pair<int, int> getPosition() { return position; }
};

#endif //DUNE_CMSGCREARUNIDAD_H
