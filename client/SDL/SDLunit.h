#ifndef CLIENT_SDL_SDLUNIT_H_
#define CLIENT_SDL_SDLUNIT_H_

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "../common/dto.h"
#include "SDLcam.h"
#include "SDLsound.h"
#include "clases/YAMLunit.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLunit {
    Renderer &renderer;

   protected:
    int id;
    std::pair<int, int> position;
    int type;
    int house;
    int heading;
    int health;
    int playerID;
    YAML::Node Yunits;

    bool isSelected;

    std::map<std::pair<int, int>, std::pair<int, int>> offset;

    int xoff = 0;
    int yoff = 0;
    int spriteH = 1;
    int spriteW = 1;

    int interleave = 0;
    int frame = 8;

    int attackX = 0;
    int attackY = 0;

    int attackVal = 1;
    bool avisado = false;

    bool attacking = false;

    void setColorMod(Texture &mask);

   public:
    SDLunit(StUnit &unit, int house, YAML::Node data, Renderer &renderer, SDLsound &sounds);

    std::pair<int, int> getPosition();

    void isClicked(int x, int y, SDLsound &sounds);

    void isClicked(std::pair<int, int> from, std::pair<int, int> to);

    virtual void render(SDLcam &cam,
                        std::map<std::string, Texture *> &textures,
                        std::map<std::pair<int, int>, Texture *> &sprites,
                        std::map<std::pair<int, int>, Texture *> &mask);

    void renderAttack(SDLcam &cam, std::map<std::string, Texture *> &textures);
    void renderHealth(SDLcam &cam);

    void getHeadingAttack();

    void removeSelected();

    bool isInside(int x, int y);
    bool isInsideTile(int x, int y);

    bool getSelected();

    int getId();

    void update(StUnit unit, SDLsound &sounds);

    int getPlayerID();

    virtual ~SDLunit();
};

#endif  // CLIENT_SDL_SDLUNIT_H_
