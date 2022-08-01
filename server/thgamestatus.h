#ifndef DUNE_THGAMESTATUS_H
#define DUNE_THGAMESTATUS_H

// #include <functional>
#include <atomic>
#include "thread.h"
#include "games.h"

class ThGameStatus : public Thread {
    Games &games;
    std::atomic<bool> &continuar;

public:
    ThGameStatus(Games &games, std::atomic<bool> &continuar);

    void run() override;

    ThGameStatus(ThGameStatus &&other) noexcept = default;;

    ThGameStatus(const ThGameStatus &) = delete;

    ThGameStatus &operator=(const ThGameStatus &) = delete;
};

#endif //DUNE_THGAMESTATUS_H
