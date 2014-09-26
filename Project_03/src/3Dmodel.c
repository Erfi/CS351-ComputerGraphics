/*
Erfan Azad
25 Sep 2014
3Dmodel.c
This file creates 3d shapes using the files in the library, mostly lines, circles and ellipses.
*/

#include <stdio.h>
#include <stdlib.h>
#include "polyline.h"
#include "point.h"
#include "color.h"
#include "Image.h"
#include "line.h"
#include "circle.h"
#include "ellipse.h"

int main(int argc, char *argv[]) {
	int rows = 500;
	int cols = 500;
	int numPoints = 8;
	double x_coord[numPoints] = {50, 100, 100, 50, 80, 80, 130, 130};
	double y_coord[numPoints] = {50, 50, 100, 100, 40, 90, 90, 40};
	Image* src;
	Polyline* cube1;
	Point 
	
	Color White;
	Color Yellow;
	Color Red;
	Color Blue;

	Color_set(&White, 1.0, 1.0, 1.0);
	Color_set(&Yellow, 1.0, 1.0, 0.0);
	Color_set(&Red, 1.0, 0.0, 0.0);
	Color_set(&Blue, 0.0, 0.0, 1.0);

	printf("Making point lists\n");
	int i;
	for(i=0; i< 8; i++){
		point_set2D(&p[i], x_coord[i], y_coord[i]);
	}

	






}
