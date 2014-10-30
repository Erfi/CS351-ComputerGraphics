/*
Erfan Azad & Ryan Brandt
Date: 16 Oct 2014
file: view.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "view.h"


void matrix_setView2D(Matrix *vtm, View2D *view){
	if(NULL != vtm && NULL != view){
		float dv = (view->dx*view->screeny)/view->screenx;
		matrix_identity(vtm);
 		 matrix_print(vtm, stdout);
		matrix_translate2D(vtm, -view->vrp.val[0], -view->vrp.val[1]);
		matrix_rotateZ(vtm, view->x.val[0], -view->x.val[1]);
		matrix_scale2D(vtm, view->screenx/view->dx, -view->screeny/dv);
		matrix_translate2D(vtm, view->screenx/2, view->screeny/2);
	}
}

void matrix_setView3D(Matrix *vtm, View3D *view){
	if(NULL != vtm && NULL != view){
		Vector u;
		Vector vup = view->vup;
		Vector vpn = view->vpn;
		Matrix project;
		double bPrime = view->d +view->b;
		double dPrime = view->d/bPrime;

		matrix_identity(vtm);
		printf("before everything:\n");
 		matrix_print(vtm, stdout);

		vector_cross(&vup,&vpn,&u);
		vector_cross(&vpn,&u,&vup);
		printf("vrp:\n");
		vector_print(&view->vrp,stdout);

		matrix_translate(vtm, -view->vrp.val[0], -view->vrp.val[1],-view->vrp.val[2]);
		printf("After VRP translation:\n");
 		matrix_print(vtm, stdout);

		vector_normalize(&u);
		vector_normalize(&vpn);
		vector_normalize(&vup);
		matrix_rotateXYZ(vtm, &u, &vup, &vpn );
		printf("After Rxyz :\n");
  		matrix_print(vtm, stdout);

		matrix_translate(vtm, 0, 0,view->d);
		printf("After translating COP to origin:\n");
  		matrix_print(vtm, stdout);
  		
		
		matrix_scale(vtm, (2*view->d)/(bPrime*view->du), (2*view->d)/(bPrime*view->dv), 1/bPrime);
		printf("After scaling to CVV:\n");
 		matrix_print(vtm, stdout);

		matrix_identity(&project);
		project.m[3][3]=0;
		project.m[3][2]=1/dPrime;
		printf("projection:\n");
		matrix_print(&project, stdout);
		matrix_multiply(&project,vtm,vtm);
		printf("After perspective:\n");
 		matrix_print(vtm, stdout);

		matrix_scale2D(vtm, -view->screenx/(2*dPrime), -view->screeny/(2*dPrime));
		printf("After scale to image coords:\n");
  		matrix_print(vtm, stdout);

		matrix_translate2D(vtm, view->screenx/2, view->screeny/2);
		printf("After final translation to image coords:\n");
  		matrix_print(vtm, stdout);
	}

}


/*
Tells you if a surface of a polygon is visible or not for drawing.
returns 1 if visible, 0 otherwise
*/
int is_surface_visible(Vector* vpn, Vector* surfaceNormal){
	double result = vector_dot(vpn, surfaceNormal);
	if( result > 0){
		return 1; //visible
	}
	else{
		return 0; // not visible
	}
}



