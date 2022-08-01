#include "clientqueue.h"

void ClientQueue::push(std::shared_ptr<CMsg> cMsg) {

    std::unique_lock<std::mutex> lk(mut);
    condNotFull.wait(lk, [this] { return count != MAX; });
    queue.push(cMsg);
    count++;
    condNotEmpty.notify_all();
}

std::shared_ptr<CMsg> ClientQueue::pop() {
    std::unique_lock<std::mutex> lk(mut);
    condNotEmpty.wait(lk, [this] { return !queue.empty(); });
    std::shared_ptr<CMsg> cMsg = queue.front();
    queue.pop();
    count--;
    condNotFull.notify_all();
    return cMsg;
}
