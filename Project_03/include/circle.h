//
//  circle.h
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#ifndef ____circle__
#define ____circle__

#include <stdio.h>


void circle_set(Circle *c, Point tc, double tr);
void circle_draw(Circle *c, Image *src, Color p);
void circle_drawFill(Circle *c, Image *src, Color p);

double r;
Point c;

#endif /* defined(____circle__) */
