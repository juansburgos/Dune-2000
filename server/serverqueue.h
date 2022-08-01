#ifndef DUNE_SERVERQUEUE_H
#define DUNE_SERVERQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include "smsg.h"
#include "defines.h"

class ServerQueue {
private:
    std::mutex mut;
    std::queue<std::shared_ptr<SMsg>> queue;
    std::condition_variable condNotEmpty;
    std::condition_variable condNotFull;
    int count = 0;
    const int MAX{QUEUE_LEN};
public:
    ServerQueue() = default;

    void push(std::shared_ptr<SMsg> sMsg);

    std::shared_ptr<SMsg> pop();
};

#endif //DUNE_SERVERQUEUE_H
