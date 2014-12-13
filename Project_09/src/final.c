/*
Erfan Azad
Date: Dec 13 2014
File: final.C
Description: This file will create an animation of letters "GRAPHICS" on a ground and circles arouns them.
*/
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "matrix.h"
#include "polygon.h"
#include "Image.h"
#include "module.h"
#include "drawState.h"
#include "view.h"
#include "light.h"

//Creating unit letters
void module_2cube(Module* md);
void module_2cube(Module* md){
	module_scale(md, 2.0, 1, 1);
	module_cube(md);
}

void module_3cube(Module* md);
void module_3cube(Module* md){
	module_scale(md, 3.0, 1, 1);
	module_cube(md);
}

void module_4cube(Module* md);
void module_4cube(Module* md){
	module_scale(md, 4.0, 1, 1);
	module_cube(md);
}

void module_alphabet_G(Module *md);
void module_alphabet_G(Module *md){
	module_3cube(md);
}


int main(int argc, char* argv[]){
	Image* src;
	Module *scene;
	Module* GRAPHICS;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Lighting *light;
	Color Red;
	Color Green;
	Color Grey;
	Color White;

	//setting colors
	Color_set(&Red, 1.0, 0.2, 0.1 );
	Color_set(&Grey, 0.6, 0.65, 0.67 );
	Color_set(&Green, 0.1, 1, 0.1 );
	Color_set(&White, 1, 1, 1 );

	// setting the view
	point_set3D( &(view.vrp), 10, 0, 10 );
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 1;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 200;
	view.screenx = 1280;
	view.screeny = 720;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	//creating GRAPHICS module
	GRAPHICS = module_create();
	module_alphabet_G(GRAPHICS);


	//creating scene module
	scene = module_create();
	module_module(scene, GRAPHICS);

	// setting the light
	light = lighting_create();
	lighting_add( light, LightAmbient, &White, NULL, NULL, 0, 0);

	// image
	src = image_create( view.screeny, view.screenx );

	//setting drawstate
	ds = drawstate_create();
	point_copy(&(ds->viewer), &(view.vrp) );
	// ds->shade = ShadePhong;
	ds->shade = ShadeDepth;

	//Drawing
	module_draw( scene, &vtm, &gtm, ds, light, src );
	image_write( src, "final.ppm" );

	return(0);
}
