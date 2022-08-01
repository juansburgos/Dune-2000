#include "gtest/gtest.h"
#include "../../../server/model/game.h"

class GameFixture : public ::testing::TestWithParam<int> {
public:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    GameFixture() : TestWithParam<int>() {
        std::string gameName("Test Game");
        std::string mapName("Mapa 1");
        int requeridos = 2;
        int house = 0;
        game = new Game(gameName, mapName, requeridos, house);
    }

    virtual ~GameFixture() {
        delete game;
    }

    Game *game;
};

TEST_F(GameFixture, start_with_one_player) {
    int players = game->getPlayers();
    EXPECT_EQ(players, 1);
}

TEST_F(GameFixture, unirse_second_player) {
    int house = 1;
    bool ret = game->unirse(house);
    EXPECT_EQ(ret, true);
    int players = game->getPlayers();
    EXPECT_EQ(players, 2);
}

TEST_F(GameFixture, unirse_third_player) {
    int house = 1;

    bool ret = game->unirse(house);
    EXPECT_EQ(ret, true);
    int players = game->getPlayers();
    EXPECT_EQ(players, 2);

    ret = game->unirse(house);
    EXPECT_EQ(players, 2);
    EXPECT_EQ(ret, false);
    players = game->getPlayers();
    EXPECT_EQ(players, 2);
}