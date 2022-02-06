#include "colors.h"

Colors getColors(){
    Colors colors = {
            .WHITE = al_map_rgb(255, 255, 255),
            .BLACK = al_map_rgb(0, 0, 0)
    };

    return colors;
}