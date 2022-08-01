#ifndef DUNE_CMSGFORCEDEND_H
#define DUNE_CMSGFORCEDEND_H

#include "cmsg.h"

class CMsgForcedEnd : public CMsg {
public:
    void send(ClientProtocol &cProtocol) override;
};

#endif //DUNE_CMSGFORCEDEND_H
