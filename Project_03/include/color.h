//
//  color.h
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#ifndef ____color__
#define ____color__

#include <stdio.h>

typedef struct{
    float rgb[3];
} Color;


void Color_copy(Color *to, Color *from);

void Color_set(Color *to, float r, float g, float b);

#endif /* defined(____color__) */
