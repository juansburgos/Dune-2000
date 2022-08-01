#include <iostream>
#include <algorithm>
#include <filesystem>
#include "smsgforcedend.h"
#include "games.h"

bool Games::crear(const std::string &name, const std::string &mapa, int required, int house, ServerProtocol &sProtocol,
                  ServerQueue *&queue) {
    std::lock_guard<std::mutex> lock(mut);
    for (auto &gameContainer: gameContontainers) {
        if (gameContainer.game->getName() == name)
            return EXIT_FAILURE;
    }
    auto gameContainer = GameContainer(name, mapa, required, house, sProtocol, queue);
    gameContontainers.push_back(std::move(gameContainer));
    return EXIT_SUCCESS;
}

bool Games::unirse(const std::string &name, int house, ServerProtocol &sProtocol, ServerQueue *&queue) {
    std::lock_guard<std::mutex> lock(mut);
    for (auto &gameContainer: gameContontainers) {
        if (gameContainer.game->getName() == name) {
            gameContainer.game->unirse(house);
            gameContainer.broadcaster->add(sProtocol);
            queue = gameContainer.getQueue();
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

std::vector<StGame> Games::getStGames() {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<StGame> listado;
    for (auto &gameContainer: gameContontainers)
        listado.push_back({gameContainer.game->getName(),
                           gameContainer.game->getPlayers(),
                           gameContainer.game->getRequired()});
    return listado;
}

void Games::checkStarting() {
    for (auto &gameContainer: gameContontainers)
        if (gameContainer.game->checkStarting()) {
            gameContainer.broadcaster->sendSetup();
            gameContainer.gameloop->start();
            gameContainer.broadcaster->start();
            gameContainer.cmdExecutor->start();
        }
}

std::vector<std::pair<std::string, int>> Games::getMapas() {
    std::vector<std::pair<std::string, int>> mapas;
    std::string path = "../maps";
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        std::string s = entry.path().string().substr(8);
        YAML::Node node = YAML::LoadFile(path + "/" + s);
        int maxPlayers = node["players"].size();
        s = s.substr(0, s.find(".yaml"));
        mapas.push_back(std::make_pair(s, maxPlayers));
    }
    return mapas;
}

void Games::checkEnding() {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<GameContainer> aux;
    for (auto &gameContainer: gameContontainers) {
        if (gameContainer.game->checkGameEnd()) {
            gameContainer.gameloop->join();
            gameContainer.broadcaster->join();
            auto sMsgForcedEnd = std::make_shared<SMsgForcedEend>();
            gameContainer.queue->push(sMsgForcedEnd);
            gameContainer.cmdExecutor->join();
        } else {
            aux.push_back(std::move(gameContainer));
        }
    }
    gameContontainers = std::move(aux);
}

void Games::stop() {
    std::lock_guard<std::mutex> lock(mut);
    for (auto &gameContainer: gameContontainers)
        gameContainer.stop();
}
