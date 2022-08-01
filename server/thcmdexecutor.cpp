#include "thcmdexecutor.h"

void ThCmdExecutor::run() {
    while (!game->checkGameEnd()) {
        std::shared_ptr<SMsg> sMsg = queue->pop();
        sMsg->execute(game);
    }
}

ThCmdExecutor::ThCmdExecutor(Game *aGame, ServerQueue *aQueue) {
    game = aGame;
    queue = aQueue;
}
