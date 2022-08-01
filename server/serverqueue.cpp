#include "serverqueue.h"

void ServerQueue::push(std::shared_ptr<SMsg> sMsg) {
    std::unique_lock<std::mutex> lk(mut);
    condNotFull.wait(lk, [this] { return count != MAX; });
    queue.push(sMsg);
    count++;
    condNotEmpty.notify_all();
}

std::shared_ptr<SMsg> ServerQueue::pop() {
    std::unique_lock<std::mutex> lk(mut);
    condNotEmpty.wait(lk, [this] { return !queue.empty(); });
    std::shared_ptr<SMsg> sMsg = queue.front();
    queue.pop();
    count--;
    condNotFull.notify_all();
    return sMsg;
}
