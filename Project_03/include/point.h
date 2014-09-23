//
//  point.h
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#ifndef ____point__
#define ____point__

#include <stdio.h>


typedef struct{
    double val[4];
} Point;



void point_set2D(Point *p, double x, double y);
void point_set3D(Point *p, double x, double y, double z);
void point_set(Point *p, double x, double y, double z, double h);

void point_copy(Point *to, Point *from);

void point_draw(Point *p, Image *src, Color c);

void point_drawf(Point *p, Image *src, FPixel c);

#endif /* defined(____point__) */
