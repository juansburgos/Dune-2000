#ifndef CLIENT_SDL_SDLUNITS_H_
#define CLIENT_SDL_SDLUNITS_H_

#include <SDL2pp/SDL2pp.hh>

#include "../../common/defines.h"
#include "SDLgui.h"
#include "SDLunit.h"
#include "partida.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLunits {
    Partida &&partida;
    Renderer &renderer;
    YAML::Node yamlUnits;
    std::vector<std::shared_ptr<SDLunit>> units;
    std::map<std::pair<int, int>, Texture *> sprites;
    std::map<std::pair<int, int>, Texture *> mask;
    std::map<std::string, Texture *> textures;

   public:
    explicit SDLunits(Partida &partida, Renderer &renderer);

    void setUnits(SDLgui &gui);

    void render(SDLgui &gui);

    void update(SDLsound &sounds);

    int exists(int id);

    void createUnit(StUnit &unit, SDLsound &sounds);

    int getEnemyIdInPosition(std::pair<int, int> position);
    int getAllyIdInPosition(std::pair<int, int> position);

    void removeSelected();

    void removeDead();

    std::vector<int> getSelectedUnits();

    std::vector<std::shared_ptr<SDLunit>> getUnits();

    ~SDLunits();
};

#endif  // CLIENT_SDL_SDLUNITS_H_
