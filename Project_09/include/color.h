//
//  color.h
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdio.h>

typedef struct{
    float rgb[3];
} Color;


void Color_copy(Color *to, Color *from);

void Color_set(Color *to, float r, float g, float b);

void Color_print(Color* colr, FILE *fp);

#endif /* defined(__COLOR_H__) */
