#ifndef DUNE_SMSG_H
#define DUNE_SMSG_H

class Game;

class SMsg {
public:
    virtual void execute(Game *game) = 0;
};

#endif //DUNE_SMSG_H
