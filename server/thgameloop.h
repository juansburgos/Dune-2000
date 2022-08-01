#ifndef DUNE_THGAMELOOP_H
#define DUNE_THGAMELOOP_H

#include "thread.h"
#include "model/game.h"

class ThGameloop : public Thread {
    Game *game;
    int count = 0;
public:
    explicit ThGameloop(Game *aGame);

    void run() override;

    ThGameloop(ThGameloop &&other) = default;

    ThGameloop(ThGameloop &) = delete;

    ThGameloop &operator=(const ThGameloop &) = delete;
};

#endif //DUNE_THGAMELOOP_H
