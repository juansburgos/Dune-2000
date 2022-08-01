#ifndef DUNE_POSITONABLE_H
#define DUNE_POSITONABLE_H

#include <utility>

class Positionable {
protected:
    std::pair<int, int> position;
    std::pair<int, int> dimension;
public:
    Positionable() = default;

    Positionable(Positionable &&other) noexcept = default;

    Positionable(const Positionable &) = delete;

    Positionable &operator=(const Positionable &) = delete;

    std::pair<int, int> getPosition() {return position;}

    void setPosition(std::pair<int, int> pos) { position = pos; }

    std::pair<int, int> getDimension() const { return dimension; }
};

#endif //DUNE_POSITONABLE_H
