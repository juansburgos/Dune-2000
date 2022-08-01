#include "cmsgconstruir.h"
#include "clientprotocol.h"

CMsgConstruir::CMsgConstruir(int type, int playerID, std::pair<int, int> position) : type(type),
                                                                                     playerID(playerID),
                                                                                     position(position) {
}

void CMsgConstruir::send(ClientProtocol &cProtocol) {
    cProtocol.send(this);
}