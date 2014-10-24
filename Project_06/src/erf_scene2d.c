/*
Erfan Azad
Date: 23 Oct 2014
File: erf_scene2d.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "point.h"
#include "polyline.h"
#include "polygon.h"
#include "line.h"
#include "view.h"
#include "color.h"
#include "circle.h"

int main(int argc, char* argv[]){
	const int rows = 1000;
	const int cols = 1000;
	View2D view;
	Matrix vtm;
	Matrix ltm;
	Line line[5];
	Line tLine;
	Circle head;
	double R_head;
	Point p[7];
	Color color[4];
	int t;
	char filename[256];
	Image *src;

	//setting the colors for the scene
	Color_set(&color[0], 0.56, 0.93, 0.56);//green
	Color_set(&color[1], 0.80, 0.52, 0.24);//brown
	Color_set(&color[2], 1.0, 1.0, 1.0);//white
	Color_set(&color[3], 0.0, 0.0, 0.0);//black

	src = image_create( rows, cols );

	//setting the points
	point_set2D(&p[0], 0, 5);//head center

	//setting the circle
	R_head = 10;
	circle_set(&head, p[0], R_head);
	//setting the line using points
	// line_set(Line *l, Point ta, Point tb);
	// line_set(Line *l, Point ta, Point tb);
	// line_set(Line *l, Point ta, Point tb);
	// line_set(Line *l, Point ta, Point tb);
	// line_set(Line *l, Point ta, Point tb);

	



	//cleanup
	image_free(src);

}