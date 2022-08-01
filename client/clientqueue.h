#ifndef DUNE_CLIENTQUEUE_H
#define DUNE_CLIENTQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include "cmsg.h"
#include "defines.h"

class ClientQueue {
private:
    std::mutex mut;
    std::queue<std::shared_ptr<CMsg>> queue;
    std::condition_variable condNotEmpty;
    std::condition_variable condNotFull;
    int count = 0;
    const int MAX{QUEUE_LEN};
public:
    ClientQueue() = default;

    void push(std::shared_ptr<CMsg> cMsg);

    std::shared_ptr<CMsg> pop();
};

#endif //DUNE_CLIENTQUEUE_H
