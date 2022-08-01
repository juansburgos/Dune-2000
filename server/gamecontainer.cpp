#include "gamecontainer.h"
#include "smsgforcedend.h"

GameContainer::GameContainer(const std::string &name, const std::string &mapName, int required, int house,
                             ServerProtocol &sProtocol, ServerQueue *&aQueue) {
    game = new Game(name, mapName, required, house);
    broadcaster = new ThBroadcaster(game, sProtocol);
    gameloop = new ThGameloop(game);
    queue = new ServerQueue();
    aQueue = queue;
    cmdExecutor = new ThCmdExecutor(game, queue);
}

GameContainer::GameContainer(GameContainer &&other) {
    this->game = other.game;
    other.game = nullptr;
    this->broadcaster = other.broadcaster;
    other.broadcaster = nullptr;
    this->gameloop = other.gameloop;
    other.gameloop = nullptr;
    this->cmdExecutor = other.cmdExecutor;
    other.cmdExecutor = nullptr;
    this->queue = other.queue;
    other.queue = nullptr;
}

GameContainer::~GameContainer() {
    delete cmdExecutor;
    delete queue;
    delete gameloop;
    delete broadcaster;
    delete game;
}

void GameContainer::stop() {
    game->stop();
    auto sMsgForcedEnd = std::make_shared<SMsgForcedEend>();
    queue->push(sMsgForcedEnd);
}

ServerQueue *GameContainer::getQueue() const {
    return queue;
}
