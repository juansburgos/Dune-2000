#ifndef DUNE_SMSGCONSTRUIR_H
#define DUNE_SMSGCONSTRUIR_H

#include "smsg.h"

class SMsgConstruir : public SMsg {
    int type;
    int playerID;
    std::pair<int, int> position;
public:
    SMsgConstruir(int type, int playerID, std::pair<int, int> position);

    void execute(Game *game) override;

    int getType() const { return type; }

    int getPlayerID() { return playerID; }

    std::pair<int, int> getPosition() { return position; }
};

#endif //DUNE_SMSGCONSTRUIR_H
