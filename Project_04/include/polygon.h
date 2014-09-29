/*
Erfan Azad
Date: 29 Sep 2014
file: polygon.h
*/
#ifndef __POLYGON_H__
#define __POLYGON_H__

#include "point.h"
#include "Image.h"
#include "color.h"

typedef struct{
	int numVertex;
	Point *vertex;
	int zBuffer;
}Polygon;

Polygon *polygon_create();
Polygon *polygon_createp(int numV, Point *vlist);
void polygon_free(Polygon *p);
void polygon_init(Polygon *p);
void polygon_set(Polygon *p, int numV, Point *vlist);
void polygon_clear(Polygon *p);
void polygon_zBuffer(Polygon *p, int flag);
void polygon_copy(Polygon *to, Polygon *from);
void polygon_print(Polygon *p, FILE *fp);
void polygon_draw(Polygon *p, Image *src, Color c);
void polygon_drawFill(Polygon *p, Image *src, Color c);
void polygon_drawFillB(Polygon *p, Image *src, Color c);

#endif