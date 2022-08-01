#ifndef CLIENT_SDL_SDLCAM_H_
#define CLIENT_SDL_SDLCAM_H_

#include <math.h>

#include <iostream>
#include <vector>

#include "../../common/defines.h"
#include "partida.h"

class SDLcam {
    int x = 0;
    int y = 0;
    int counter = 0;

    int maxX;
    int maxY;

    int direccion;

   public:
    SDLcam(int maxX, int maxY, Partida &partida);
    int getX();
    int getY();

    void setDireccion(int dir);
    void turnToViewClick(int &cursorX, int &cursorY);

    float turnToViewSize(float size);
    std::pair<int, int> turnToViewSize(std::pair<int, int> position);
    void setToViewSize(std::pair<int, int> &position);

    void update();
    bool isInside(std::pair<int, int> position);
    bool tileIsInside(std::pair<int, int> position);

    void updateWindow(int windowWidth, int windowHeight);
};

#endif  // CLIENT_SDL_SDLCAM_H_
