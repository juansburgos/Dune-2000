#ifndef CLIENT_SDL_SDLBUILDINGS_H_
#define CLIENT_SDL_SDLBUILDINGS_H_

#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include <utility>
#include <vector>

#include "../../common/defines.h"
#include "SDLbuilding.h"
#include "SDLgui.h"
#include "SDLsound.h"
#include "buildings/SDLAirTrap.h"
#include "buildings/SDLBarracks.h"
#include "buildings/SDLConstructionYard.h"
#include "buildings/SDLHeavyFactory.h"
#include "buildings/SDLLightFactory.h"
#include "buildings/SDLPalace.h"
#include "buildings/SDLRefinery.h"
#include "buildings/SDLSpiceSilo.h"
#include "clases/YAMLbuilding.h"
#include "partida.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLbuildings {
    Partida &&partida;
    Renderer &renderer;
    YAML::Node yamlBuildings;
    std::vector<std::shared_ptr<SDLbuilding>> buildings;
    std::map<std::string, Texture *> textures;

   public:
    explicit SDLbuildings(Partida &partida, Renderer &renderer);

    void setBuildings(SDLgui &gui);
    void render(SDLgui &gui);
    int exists(int id);
    void removeDestroyed();
    void update(SDLsound &sounds);
    void createBuilding(StBuilding &building);
    void removeSelected();

    std::vector<std::shared_ptr<SDLbuilding>> getBuildings();

    int getEnemyIdInPosition(std::pair<int, int> position);
    int getAllyIdInPosition(std::pair<int, int> position);

    std::pair<int, int> getBuildingDimension(int type);
    ~SDLbuildings();
};

#endif  // CLIENT_SDL_SDLBUILDINGS_H_
