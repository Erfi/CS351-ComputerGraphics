#include <stdio.h>
#include <stdlib.h>
#include "light.h"
#include "color.h"
#include "matrix.h"
#include "point.h"

int main(int argc, char *argv[]) {

	Vector N;
	Vector V;
	Point p;
	Color Cb = {{0.4, 0.5, 0.6}};
	Color Cs = {{0.2, 0.2, 0.2}};
	float s = 10;
	Lighting *l;
	Color c;
	Color amb = {{0.3, 0.3, 0.3}};
	Color pt = {{1.0, 1.0, 1.0}};
	Point loc;

	point_set3D(&p, 0, 0, 0); // origin
	point_set3D(&N, 0, 1, 0); // up
	vector_set(&V, 1, 2, 3);
	

	l = lighting_create();
	lighting_add( l, LightAmbient, &amb, NULL, NULL, 0, 0);

	point_set3D( &loc, 3, 2, 1 );
	lighting_add( l, LightPoint, &pt, NULL, &loc, 0, 0 );

	lighting_shading( l, &N, &V, &p, &Cb, &Cs, s, 1, &c );

	printf("c: %.2f %.2f %.2f\n", c.rgb[0], c.rgb[1], c.rgb[2] );

	return(0);
}