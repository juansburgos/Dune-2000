#ifndef DUNE_SMSGCREARUNIDAD_H
#define DUNE_SMSGCREARUNIDAD_H

#include "smsg.h"
#include <utility>

class SMsgCrearUnidad : public SMsg {
  int type;
  int playerID;
  std::pair<int, int> position;
public:
  SMsgCrearUnidad(int type, int playerID, std::pair<int, int> position);

  void execute(Game *game) override;

  int getType() const { return type; }

  int getPlayerID() const { return playerID; }

  std::pair<int, int> getPosition() { return position; }
};

#endif //DUNE_SMSGCREARUNIDAD_H
