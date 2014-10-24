/*
Ryan Brandt & Erfan Azad
Date: 24 Oct 2014
File: module.h
*/

#ifndef __MODULE_H__
#define __MODULE_H__

typedef enum { // example of an enumerated type
	ObjNone,
	ObjLine,
	ObjPoint,
	ObjPolyline,
	ObjPolygon,
	ObjIdentity,
	ObjMatrix,
	ObjColor,
	ObjBodyColor,
	ObjSurfaceColor,
	ObjSurfaceCoeff,
	ObjLight,
	ObjModule
} ObjectType;

typedef union {
	Point point;
	Line line;
	Polyline polyline;
	Polygon polygon;
	Matrix matrix;
	Color color;
	float coeff;
	void *module;
} Object;

typedef struct {
	ObjectType type;
	Object obj;
	void *next;
} Element;

typedef struct {
	Element *head; // pointer to the head of the linked list
	Element *tail; // keep around a pointer to the last object
} Module;


#endif