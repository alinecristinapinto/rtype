#include "colors.h"

Colors getColors(){
    Colors colors = {
            .WHITE = al_map_rgb(255, 255, 255),
            .BLACK = al_map_rgb(0, 0, 0),
            .CYAN = al_map_rgb(0, 255, 255),
            .GREEN = al_map_rgb(0, 255, 0),
            .RED = al_map_rgb(255, 0, 0),
            .YELLOW = al_map_rgb(255, 255, 0),
            .ORANGE = al_map_rgb(255, 165, 0),
            .MEDIUM_VIOLET_RED = al_map_rgb(199,21,133)
    };

    return colors;
}