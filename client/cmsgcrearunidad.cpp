#include "cmsgcrearunidad.h"
#include "clientprotocol.h"

CMsgCrearUnidad::CMsgCrearUnidad(int type, int playerID, std::pair<int, int> position) : type(type),
                                                                                         playerID(playerID),
                                                                                         position(position) {
}

void CMsgCrearUnidad::send(ClientProtocol &cProtocol) {
    cProtocol.send(this);
}