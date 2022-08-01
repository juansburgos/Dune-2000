#include <utility>
#include "smsgconstruir.h"
#include "games.h"

SMsgConstruir::SMsgConstruir(int type, int playerID, std::pair<int, int> position) : type(type),
                                                                                     playerID(playerID),
                                                                                     position(position) {
}

void SMsgConstruir::execute(Game *game) {
    game->construir(this);
}