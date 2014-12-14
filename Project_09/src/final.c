/*
Erfan Azad
Date: Dec 13 2014
File: final.C
Description: This file will create an animation of letters "GRAPHICS" on a ground and circles arouns them.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "point.h"
#include "matrix.h"
#include "polygon.h"
#include "Image.h"
#include "module.h"
#include "drawState.h"
#include "view.h"
#include "light.h"



//creating unit letters
void module_alphabet_G(Module *md);
void module_alphabet_G(Module *md){
	//3
	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	module_cube(md); 
	module_translate(md, 2, 0 ,0);

	//4
	module_cube(md);
	module_translate(md, 0, 0 ,-2);
	module_cube(md); 

	module_translate(md, 0, 0 ,-2);
	module_cube(md);

	module_translate(md, 0, 0 ,-2);
	module_cube(md);

	//5
	module_translate(md, -2, 0, 0);
	module_cube(md);

	//2
	module_identity(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0,0,-2);
		module_cube(md);
	}

	//1
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0 ,0);
		module_cube(md);
	}	
}

void module_alphabet_R(Module *md);
void module_alphabet_R(Module *md){

	//4
	for(int i=0; i<6; i++){
		module_cube(md);
		module_translate(md, 0,0,-2);
	}

	//1
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	for(int i=0; i<2; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 2);
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}

	//5
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 2);
		module_cube(md);
	}
}


void module_alphabet_A(Module *md);
void module_alphabet_A(Module *md){
	//1
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}	

	//2
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//3
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}	

	//4
	module_translate(md, 0, 0, -6);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_P(Module *md);
void module_alphabet_P(Module *md){
		//4
	for(int i=0; i<6; i++){
		module_cube(md);
		module_translate(md, 0,0,-2);
	}

	//1
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	for(int i=0; i<2; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 2);
	module_cube(md);
	for(int i=0; i<3; i++){
		module_translate(md, -2, 0, 0);
		module_cube(md);
	}
}

void module_alphabet_H(Module *md);
void module_alphabet_H(Module *md){
	//1
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, -2);
		module_cube(md);
	}

	//3
	module_translate(md, 0, 0, 6);
	for(int i=0; i<3; i++){
		module_translate(md, 2, 0, 0);
		module_cube(md);
	}

	//2
	module_translate(md, 0, 0, -6);
	module_cube(md);
	for(int i=0; i<6; i++){
		module_translate(md, 0, 0, 2);
		module_cube(md);
	}
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
	point_set3D( &(view.vrp), 20, 60, 30 );
	vector_set( &(view.vpn), -view.vrp.val[0]+20, -view.vrp.val[1], -view.vrp.val[2]);
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

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 10, 0, 0);
	module_alphabet_R(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 20, 0, 0);
	module_alphabet_A(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 30, 0, 0);
	module_alphabet_P(GRAPHICS);

	module_identity(GRAPHICS);
	module_translate(GRAPHICS, 40, 0, 0);
	module_alphabet_H(GRAPHICS);








	//creating scene module
	scene = module_create();
	module_module(scene, GRAPHICS);

	// setting the light
	light = lighting_create();
	// lighting_add( light, LightAmbient, &Grey, NULL, NULL, 0, 0);
	lighting_add(light, LightPoint, &White , NULL, &view.vrp, 0, 0);

	// image
	src = image_create( view.screeny, view.screenx );

	//setting drawstate
	ds = drawstate_create();
	point_copy(&(ds->viewer), &(view.vrp) );
	ds->shade = ShadePhong;
	// ds->shade = ShadeDepth;

	//Drawing
	module_draw( scene, &vtm, &gtm, ds, light, src );
	image_write( src, "final.ppm" );

	return(0);
}
