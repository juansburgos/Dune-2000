#include "thgamestatus.h"
#include <iostream>

ThGameStatus::ThGameStatus(Games& games, std::atomic<bool> &continuar) : games(games), continuar(continuar) {}

void ThGameStatus::run() {
  int count = 0;
  while (continuar) {
    auto start = std::chrono::steady_clock::now();
    games.checkEnding();
    auto end = std::chrono::steady_clock::now();
    int processTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    if (1000 > processTime)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 - processTime));
    else {
        std::cout << "[GameStatus] Process-time: " << processTime << " mayor a 200ms.  Ratio: 1/" << count
                  << std::endl;
        count = 0;
    }
  }
  games.checkEnding();
}
