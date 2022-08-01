#include "thread.h"

Thread::Thread() {}

void Thread::start() {
    thread = std::thread(
            &Thread::run,
            this);
}

void Thread::join() {
    thread.join();
}
