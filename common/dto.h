#ifndef COMMONDTO_H
#define COMMONDTO_H

struct StBuilding {
    int id;
    int type;
    std::pair<int, int> position;
    int hp;
    int playerID;
};

struct StUnit {
    int id;
    int type;
    std::pair<int, int> position;
    int heading;
    int hp;
    int playerID;
    bool attacking;
};

struct StOnHold {
    int type;
    int playerID;
    int percentage;
};

struct StPlayerInfo {
    int playerID;
    int currentEnergy;
    int requiredEnergy;
    int money;
    bool isPlaying;
    bool gameRunnig;
    int house;
};

struct StWorm {
    std::pair<int, int> position;
    bool attacking;
};

#endif  // COMMONDTO_H
