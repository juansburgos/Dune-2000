#ifndef CLIENT_SDL_SDLBUILDING_H_
#define CLIENT_SDL_SDLBUILDING_H_

#include <SDL2pp/SDL2pp.hh>
#include <utility>
#include <vector>

#include "../common/dto.h"
#include "SDLcam.h"
#include "SDLsound.h"
#include "clases/YAMLbuilding.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLbuilding {
   protected:
    int id;
    std::pair<int, int> position;
    int type;
    int house;
    int health;
    int playerID;
    YAML::Node node;

    bool avisado = false;

    bool isSelected;

    int buildingStage = 0;
    int destroyedStage = 42;
    bool sDestruction = false;

   public:
    SDLbuilding(StBuilding &building, int house, YAML::Node data);

    std::pair<int, int> getPosition();

    virtual void render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures);

    void renderSelected(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures);
    void renderHealth(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures);
    void renderBuild(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures);
    void renderDestroyed(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures);

    int getId();
    int getHealthImageID();

    void isClicked(int x, int y);
    int isClicked(int fromx, int fromy, int tox, int toy);

    void removeSelected();

    void update(StBuilding building, SDLsound &sounds);
    bool isInside(int x, int y);

    int getPlayerID();

    void startDestruction();

    bool getSDestruction();

    virtual ~SDLbuilding();
};

#endif  // CLIENT_SDL_SDLBUILDING_H_
