#include "playerinfo.h"

PlayerInfo::PlayerInfo(int house, int playerID) : house(house), playerID(playerID), requiredEnergy(0),
                                      currentEnergy(0), money(3500), capacity(0), playing(true), game_running(true) {}
