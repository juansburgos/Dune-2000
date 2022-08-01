#ifndef GAMES_H
#define GAMES_H

#include <mutex>
#include <map>
#include <string>
#include <vector>
#include "model/game.h"
#include "thbroadcaster.h"
#include "gamecontainer.h"

class Games {
    std::mutex mut;
    std::vector<GameContainer> gameContontainers;
public:
    Games() = default;

    bool crear(const std::string &name, const std::string &mapa, int required, int house, ServerProtocol &sProtocol,
               ServerQueue *&queue);

    bool unirse(const std::string &name, int house, ServerProtocol &sProtocol, ServerQueue *&queue);

    void checkStarting();

    std::vector<StGame> getStGames();

    Games(const Games &) = delete;

    Games &operator=(const Games &) = delete;

    std::vector<std::pair<std::string, int>> getMapas();

    void checkEnding();

    void stop();
};

#endif //GAMES_H
