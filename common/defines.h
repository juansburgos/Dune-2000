#ifndef COMMON_DEFINES_H_
#define COMMON_DEFINES_H_

#define HOUSE_HARKONNEN 0
#define HOUSE_ATREIDES 1
#define HOUSE_ORDOS 2

#define COD_ARENA 0
#define COD_CIMA 1
#define COD_DUNA 2
#define COD_PRECIPICIO 3
#define COD_ROCA 4

#define TYPE_REFINERY 4
#define TYPE_COSECHADORA 10
#define TYPE_TRAMPA_AIRE 2
#define TYPE_CENTRO_CONSTRUCCION 0

#define AIR_TRAP 2
#define BARRACKS 6
#define CONSTRUCTION_YARD 0
#define HEAVY_FACTORY 3
#define LIGHT_FACTORY 1
#define PALACE 7
#define REFINERY 4
#define SPICE_SILO 5

#define CAM_UP 1
#define CAM_DOWN 3
#define CAM_RIGHT 2
#define CAM_LEFT 4
#define CAM_UR 5
#define CAM_UL 8
#define CAM_DR 6
#define CAM_DL 7
#define CAM_CENTER 0
#define CAM_MOVEMENT_OFFSET 5

//server
#define TPS_SERVER 20  // Ticks per second
#define FACTOR_MOVE 2  // para ajustar velocidad
#define STEP_MOVE 4    // unidades que avanza por cada move DEBE SER DIVISOR DE CELL_SIZE (32)



//client
#define FPS_CLIENT 20    // Frames per second
#define SCROLL_FACTOR 16
#define CELL_SIZE 32
#define ZOOM 2

#define GUI_MAP_WIDTH 0.8   // % de mapa en window
#define GUI_MENU_WIDTH 0.2  // % de menu en window

#define WINDOW_INIT_WIDTH 1344
#define WINDOW_INIT_HEIGHT 768



//common

#define QUEUE_LEN 200

#define TILETYPE_TYPE {0, 3, 3, 3, 3, 3, 3, 3, 2, 0, 0, 2, 3, 0, 3, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, \
3, 0, 3, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0,\
0, 1, 3, 3, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 3, 3, 1, 0, 0, 3, 3,\
3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 0,\
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 1, 3, 3, 3, 3, 3, 1, 3, 1, 3, 1, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 3, 3, 1, 3,\
3, 1, 3, 1, 3, 0, 0, 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 1, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,\
3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0,\
3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 3, 4, 4, 4, 1, 0, 3,\
3, 0, 0, 0, 3, 0, 0, 3, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 3, 3,\
3, 3, 0, 0, 3, 3, 1, 1, 3, 1, 3, 4, 4, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 3, 1, 3, 4, 4, 3, 3, 3, 0, 0, 3, 3,\
3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,\
3, 3, 1, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3, 0, 3, 3, 0, 1, 3, 3, 3, 3, 1, 3, 3, 3, 0, 3, 3, 3, 0, 3, 3,\
3, 1, 3, 3, 3, 3, 0, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 1, 0, 3, 3, 3, 3, 3, 3, 3,\
3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 0, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3,\
4, 4, 4, 4, 4, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 4, 4, 4, 4, 4, 1, 1, 1, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 3,\
4, 4, 4, 4, 4, 1, 1, 1, 0, 0, 0, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 3, 3, 3, 3, 3, 0, 0, 0, 3, 0,\
0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 0, 0, 0, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1,\
1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3,\
3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,\
3, 3, 3, 3, 3, 3, 3, 3 }

#endif  // COMMON_DEFINES_H_
