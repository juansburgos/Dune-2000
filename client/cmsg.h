#ifndef DUNE_CMSG_H
#define DUNE_CMSG_H

class ClientProtocol;

class CMsg {

public:
    virtual void send(ClientProtocol &cProtocol) = 0;
};

#endif //DUNE_CMSG_H
