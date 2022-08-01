#ifndef DUNE_CMSGCONSTRUIR_H
#define DUNE_CMSGCONSTRUIR_H

#include <utility>
#include "cmsg.h"

class CMsgConstruir : public CMsg {
    int type;
    int playerID;
    std::pair<int, int> position;
public:
    CMsgConstruir(int type, int playerID, std::pair<int, int> position);

    void send(ClientProtocol &cProtocol) override;

    int getType() { return type; }

    int getPlayerID() { return playerID; }

    std::pair<int, int> getPosition() { return position; }
};

#endif //DUNE_CMSGCONSTRUIR_H
