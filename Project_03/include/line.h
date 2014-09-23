//
//  line.h
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#ifndef _line_h
#define _line_h

typedef  struct{
    int zBuffer;
    Point a;
    Point b;
}Line;


void line_set2D(Line *l, double x0, double y0, double x1, double y1);

void line_zBuffer(Line *l, int flag);

void line_zBuffer(Line *l, int flag);

void line_copy(Line *to, Line *from);

void line_draw(Line *l, Image *src, Color c);

#endif
