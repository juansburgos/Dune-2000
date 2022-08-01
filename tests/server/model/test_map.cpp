#include "gtest/gtest.h"
#include "../../../server/model/map.h" //TODO hacer con cmake

class MapaFixture : public ::testing::TestWithParam<int> {
public:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

    MapaFixture() : TestWithParam<int>() {
        std::string mapName("Mapa 1");
        auto config = Config(mapName);
        map = new Map(mapName, config);
    }

    virtual ~MapaFixture() {
        delete map;
    }

    Map *map;
};

TEST_F(MapaFixture, position_valid) {
    bool v = map->positionIsValid({1, 1});
    EXPECT_EQ(v, true);
}

TEST_F(MapaFixture, position_not_valid) {
    bool v;
    v = map->positionIsValid({-1, 1});
    EXPECT_EQ(v, false);
    v = map->positionIsValid({1, -1});
    EXPECT_EQ(v, false);
    v = map->positionIsValid({100, 1});
    EXPECT_EQ(v, false);
    v = map->positionIsValid({1, 100});
    EXPECT_EQ(v, false);
}

//TEST_F(MapaFixture, one_trap_check) {
//    std::vector<coordenada> ocupados;
//    map->add(3, 0, 0, ocupados);
//    std::string s = map->getStrMap();
//    EXPECT_EQ(s[0], 'S');
//}
//
//TEST_F(MapaFixture, xxx_check) {
//std::vector<coordenada> ocupados;
//map->add(3, 0, 0, ocupados);
//map->add(3, 0, 0, ocupados);
//std::string s = map->getStrMap();
//EXPECT_EQ(ocupados.size(), 1);
//}
//
//TEST_F(MapaFixture, yyy_check) {
//std::vector<coordenada> ocupados;
//map->add(3, 30, 30, ocupados);
//std::string s = map->getStrMap();
//EXPECT_EQ(ocupados.size(), 1);
//}
