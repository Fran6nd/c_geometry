#include "geometry.h"

ray ray_new(vector origin, vector dir, double range){
    ray r = {
        .dir = dir,
        .origin = origin,
        .range = range,
    };
    return r;
}