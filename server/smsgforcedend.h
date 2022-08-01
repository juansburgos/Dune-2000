#ifndef DUNE_SMSGFORCEDEND_H
#define DUNE_SMSGFORCEDEND_H


#include "smsg.h"

class SMsgForcedEend : public SMsg {
public:
    void execute(Game *game) override;
};


#endif //DUNE_SMSGFORCEDEND_H
