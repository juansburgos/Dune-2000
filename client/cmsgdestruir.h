#ifndef CLIENT_CMSGDESTRUIR_H_
#define CLIENT_CMSGDESTRUIR_H_

#include <vector>

#include "clientprotocol.h"
#include "cmsg.h"

class CMsgDestruir : public CMsg {
    int buildingID;
    int playerID;

   public:
    explicit CMsgDestruir(int playerID, int buildingID);

    int getBuildingId();

    int getPlayerID();

    void send(ClientProtocol &cProtocol) override;
};

#endif  // CLIENT_CMSGDESTRUIR_H_
