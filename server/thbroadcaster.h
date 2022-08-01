#ifndef DUNE_THBROADCASTER_H
#define DUNE_THBROADCASTER_H

#include <vector>
#include <functional>
#include "serverprotocol.h"
#include "model/game.h"
#include "thread.h"

class ThBroadcaster : public Thread {
    std::vector<std::reference_wrapper<ServerProtocol>> protocols;
    Game *game;
    int count = 0;

public:
    ThBroadcaster(Game *game, ServerProtocol &sProtocol);

    void run() override;

    void add(ServerProtocol &sProtocol);

    void sendSetup();

    void sendUpdate();

    ThBroadcaster(ThBroadcaster &&other) noexcept = default;;

    ThBroadcaster(const ThBroadcaster &) = delete;

    ThBroadcaster &operator=(const ThBroadcaster &) = delete;
};

#endif //DUNE_THBROADCASTER_H
