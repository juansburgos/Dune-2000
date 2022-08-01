#ifndef SERVER_SMSGDESTRUIR_H_
#define SERVER_SMSGDESTRUIR_H_

#include <utility>

#include "games.h"
#include "smsg.h"

class SMsgDestruir : public SMsg {
    int buildingID;
    int playerID;

public:
    explicit SMsgDestruir(int playerID, int buildingID);

    void execute(Game *game) override;

    int getPlayerID() const { return playerID; }

    int getBuildingID() const { return buildingID; }
};

#endif  // SERVER_SMSGDESTRUIR_H_
