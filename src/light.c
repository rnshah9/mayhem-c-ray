//
//  light.c
//  C-Ray
//
//  Created by Valtteri Koskivuori on 11/10/15.
//  Copyright © 2015 Valtteri Koskivuori. All rights reserved.
//

#include "light.h"

/*light newLight(vector pos, float radius, color intensity) {
    light newLight;
    newLight.pos = pos;
    newLight.radius = radius;
    newLight.intensity = intensity;
    return newLight;
}*/

light newLight(vector pos, float radius, color intensity) {
    return (light){pos, radius, intensity};
}
