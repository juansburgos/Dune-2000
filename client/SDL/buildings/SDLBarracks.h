#ifndef CLIENT_SDL_BUILDINGS_SDLBARRACKS_H_
#define CLIENT_SDL_BUILDINGS_SDLBARRACKS_H_

#include <SDL2pp/SDL2pp.hh>
#include <utility>
#include <vector>

#include "../common/defines.h"
#include "SDLbuilding.h"

using namespace SDL2pp;

class SDLBarracks : public SDLbuilding {
   public:
    SDLBarracks(StBuilding building, int house, YAML::Node data) : SDLbuilding(building, house, data){};

    virtual void render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) override;
};

#endif  // CLIENT_SDL_BUILDINGS_SDLBARRACKS_H_
