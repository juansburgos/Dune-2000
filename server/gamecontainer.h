#ifndef DUNE_GAMECONTAINER_H
#define DUNE_GAMECONTAINER_H

#include "model/game.h"
#include "thbroadcaster.h"
#include "thgameloop.h"
#include "thcmdexecutor.h"

class GameContainer {
public:
    Game *game;
    ThBroadcaster *broadcaster;
    ThGameloop *gameloop;
    ThCmdExecutor *cmdExecutor;
    ServerQueue *queue;

    GameContainer(const std::string &name, const std::string &mapName, int required, int house,
                  ServerProtocol &sProtocol, ServerQueue *&aQueue);

    GameContainer(GameContainer &&other);

    GameContainer(const GameContainer &) = delete;

    GameContainer &operator=(const GameContainer &) = delete;

    ~GameContainer();

    void stop();

    ServerQueue *getQueue() const;
};


#endif //DUNE_GAMECONTAINER_H
