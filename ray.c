#include "geometry.h"

ray ray_new(vector origin, vector dir){
    ray r = {
        .dir = dir,
        .origin = origin,
    };
    return r;
}