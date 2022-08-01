#ifndef PLAYER_INFO__H_
#define PLAYER_INFO__H_

class PlayerInfo {
    int playerID, house, requiredEnergy, currentEnergy, money, capacity;
    bool playing;
    bool game_running;
public:
    PlayerInfo(int house, int playerID);

    int getPlayerID() { return playerID; }

    int &getMoney() { return money; }

    int &getRequiredEnergy() { return requiredEnergy; }

    int &getCurrentEnergy() { return currentEnergy; }

    int &getHouse() { return house; }

    int &getCapacity() { return capacity; }

    void addMoney(int quant) { money += quant; }

    void subtractMoney(int quant) { money -= quant; }

    void addCapacity(int quant) { capacity += quant; }

    void subtractCapacity(int quant) { capacity -= quant; }

    void addCurrentEnergy(int quant) { currentEnergy += quant; }

    void subtractCurrentEnergy(int quant) { currentEnergy -= quant; }

    void addRequiredEnergy(int quant) { requiredEnergy += quant; }

    void subtractRequiredEnergy(int quant) { requiredEnergy -= quant; }

    void playerLost() { playing = false; }

    bool isPlaying() { return playing; }

    bool isGameRunning() { return game_running; }

    void setGameEnd() { game_running = false; }

    int getEnergyPercentage() { return (static_cast<float>(currentEnergy) / static_cast<float>(requiredEnergy)*100); }
};

#endif
