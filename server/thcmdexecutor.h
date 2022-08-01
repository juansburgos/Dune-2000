#ifndef DUNE_THCMDEXECUTOR_H
#define DUNE_THCMDEXECUTOR_H

#include "thread.h"
#include "model/game.h"
#include "serverqueue.h"

class ThCmdExecutor : public Thread{
    Game *game;
    ServerQueue *queue;
public:
    void run() override;

    ThCmdExecutor(Game *aGame, ServerQueue *aQueue);

    ThCmdExecutor(ThCmdExecutor &&other) = default;

    ThCmdExecutor(ThCmdExecutor &) = delete;

    ThCmdExecutor& operator=(const ThCmdExecutor&) = delete;
};

#endif //DUNE_THCMDEXECUTOR_H
