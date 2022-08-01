#include <iostream>
#include "thgameloop.h"

void ThGameloop::run() {
    int count = 0;
    while (!game->checkGameEnd()) {
        count++;
        auto start = std::chrono::steady_clock::now();
        game->advance();
        auto end = std::chrono::steady_clock::now();
        int processTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (1000 / TPS_SERVER > processTime)
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / TPS_SERVER - processTime));
        else {
            std::cout << "[Gameloop]  TPS Muy Elevado.  Process-time: " << processTime << "  Ratio: 1/" << count
                      << std::endl;
            count = 0;
        }
    }
}

ThGameloop::ThGameloop(Game *aGame) {
    game = aGame;
}
