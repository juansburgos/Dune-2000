#include "smsgcrearunidad.h"
#include "games.h"
#include <utility>

SMsgCrearUnidad::SMsgCrearUnidad(int type, int playerID, std::pair<int, int> position) : type(type),
                                                                                         playerID(playerID),
                                                                                         position(position) {
}

void SMsgCrearUnidad::execute(Game *game) {
    game->crearUnidad(this);
}
