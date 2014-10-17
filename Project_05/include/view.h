/*
Erfan Azad & Ryan Brandt
Date: 16 Oct 2014
file: view.h
*/
#ifndef __VIEW_H__
#define __VIEW_H__

#include "matrix.h"
#include "point.h"

typedef struct{
	Point vrp;
	float dx;
	Vector x;
	int screenx;
	int screeny;
}View2D;

typedef struct{
	Point vrp;
	Vector vpn;
	Vector vup;
	double d;
	double du;
	double dv;
	double f;
	double b;
	int screenx;
	int screeny;
}View3D;

void matrix_setView2D(Matrix *vtm, View2D *view);

void matrix_setView3D(Matrix *vtm, View3D *view);


#endif