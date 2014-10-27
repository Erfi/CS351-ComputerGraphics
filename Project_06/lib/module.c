/*
Ryan Brandt & Erfan Azad
Date: 24 Oct 2014
File: module.c
*/
#include <stdlib.h>
#include <stdio.h>
#include "module.h"
#include "drawState.h"
#include "line.h"
#include "point.h"
#include "polyline.h"
#include "polygon.h"
#include "circle.h"
#include "color.h"
#include "Image.h"



ObjectType TYPE;

//Allocate and return an initialized but empty Element.
Element *element_create(){
	Element *e = malloc(sizeof(Element));
	// e->type = ObjNone;
	// e->obj = NULL;
	e->next = NULL;

	return e;
}

//Allocate an Element and store a duplicate of the data pointed to by obj in the Element. Modules do
//not get duplicated. The function needs to handle each type of object separately in a case statement.
Element *element_init(ObjectType type, void *obj){
	Element *e = malloc(sizeof(Element));
	Element *temp = malloc(sizeof(Element));

	e->type = ObjNone;
	switch (type){
		case ObjNone:
			break;
		case ObjLine:
		// 	Line l;
			line_copy(&temp->obj.line,obj);
			e->obj = temp->obj;
			e->type = ObjLine;
			break;
		case ObjPoint:
			// Point p;
			point_copy(&temp->obj.point,obj);
			e->obj = temp->obj;
			e->type = ObjPoint;
			break;
		case ObjPolyline:
			polyline_copy(&temp->obj.polyline,obj);
			e->obj = temp->obj;
			e->type = ObjPolyline;
			break;
		case ObjPolygon:
			polygon_copy(&temp->obj.polygon,obj);
			e->obj = temp->obj;
			e->type = ObjPolygon;
			break;
		case ObjIdentity:
			matrix_copy(&temp->obj.matrix, obj);
			e->obj = temp->obj;
			e->type = ObjIdentity;
			break;
		case ObjMatrix:
			matrix_copy(&temp->obj.matrix, obj);
			e->obj = temp->obj;
			e->type = ObjMatrix;
			break;
		case ObjColor:
			Color_copy(&temp->obj.color, obj);
			e->obj = temp->obj;
			break;
		case ObjBodyColor:
			Color_copy(&temp->obj.color, obj);
			e->obj = temp->obj;
			break;
		case ObjSurfaceColor:
			Color_copy(&temp->obj.color, obj);
			e->obj = temp->obj;
			break;
		case ObjSurfaceCoeff:
			temp->obj.coeff = *(float*)obj;
			e->obj = temp->obj;
			break;
		case ObjLight:
			break;
		case ObjModule:
			e->obj.module = (Module*)obj;
			break;
		default:
			break;
	}
	free(temp);
	return e;
}

//free the element and the object it contains, as appropriate.
void element_delete(Element *e){
	switch (e->type){
		case ObjPolyline:
			polyline_free(&(e->obj.polyline));
			break;
		case ObjPolygon:
			polygon_free(&(e->obj.polygon));
			break;
		case ObjModule:
			free(&(e->obj));
			break;
		default:
			break;
	}
	free(e);
}

//Allocate an empty module
Module* module_create(void){
	Module* mod = malloc(sizeof(Module));
	mod->head = NULL;
	mod->tail = NULL;
	return mod;
}

// clear the module’s list of Elements, freeing memory as appropriate.
void module_clear(Module *md){
	Element temp;
	for(temp = *(md->head); &temp != NULL; temp = *(Element*)temp.next){
		switch (temp.type){
			case ObjPolyline:
				polyline_free(&(temp.obj.polyline));
				// printf("this is working");
				break;
			case ObjPolygon:
				polygon_free(&(temp.obj.polygon));
				// printf("this is working");
				break;
			case ObjModule:
				free(&(temp.obj.module));
				break;
			default:
				// printf("this is working");
				break;
		// }
		}
		temp.type = ObjNone;
	}
}

// Free all of the memory associated with a module, including the memory pointed to by md
void module_delete(Module *md){
	Element temp;
	for(temp = *(md->head); &temp != NULL; temp = *(Element*)temp.next){
		switch (temp.type){
			case ObjPolyline:
				polyline_free(&(temp.obj.polyline));
				break;
			case ObjPolygon:
				polygon_free(&(temp.obj.polygon));
				break;
			case ObjModule:
				free(&(temp.obj));
				break;
			default:
				break;
		}
		temp.type = ObjNone;
	}
	free(md);
}

// Generic insert of an element into the module at the tail of the list.
void module_insert(Module *md, Element *e){
	if(NULL != md || NULL != e){
		e->next = NULL;//just to make sure
		md->tail->next = e;
		md->tail = e;
	}
}

// Adds a pointer to the Module sub to the tail of the module’s list.
void module_module(Module *md, Module *sub){
	if(NULL != md || NULL != sub){
		Element* e = element_init(ObjModule, sub);
		md->tail->next = e;
		md->tail = e;
	}
}

// Adds p to the tail of the module’s list.
void module_point(Module *md, Point *p){
	if(NULL != md || NULL != p){
		Element* e = element_init(ObjPoint, p);
		md->tail->next = e;
		md->tail = e;
	}
}

// Adds p to the tail of the module’s list.
void module_line(Module *md, Line *p){
	if(NULL != md || NULL != p){
		Element* e = element_init(ObjLine, p);
		md->tail->next = e;
		md->tail = e;
	}	
}

// Adds p to the tail of the module’s list.
void module_polyline(Module *md, Polyline *p){
	if(NULL != md || NULL != p){
		Element* e = element_init(ObjPolyline, p);
		md->tail->next = e;
		md->tail = e;
	}
}

// Adds p to the tail of the module’s list.
void module_polygon(Module *md, Polygon *p){
	if(NULL != md || NULL != p){
		Element* e = element_init(ObjPolygon, p);
		md->tail->next = e;
		md->tail = e;
	}
}

// Object that sets the current transform to the identity, placed at the tail of the module’s list.
void module_identity(Module *md){
	if(NULL != md){
		matrix_identity(&md->tail->obj.matrix);
	}
}

// Matrix operand to add a translation matrix to the tail of the module’s list.
void module_translate2D(Module *md, double tx, double ty){
	if(NULL != md){
		Matrix mat;
		matrix_clear(&mat);
		matrix_translate2D(&mat, tx, ty);
		Element* e = element_init(ObjMatrix, &mat);
		md->tail->next = e;
		md->tail = e;
	}
}

// Matrix operand to add a scale matrix to the tail of the module’s list.
void module_scale2D(Module *md, double sx, double sy){
	if(NULL != md){
		Matrix mat;
		matrix_clear(&mat);
		matrix_scale2D(&mat, sx, sy);
		Element* e = element_init(ObjMatrix, &mat);
		md->tail->next = e;
		md->tail = e;
	}
}

// Matrix operand to add a rotation about the Z axis to the tail of the module’s list.
void module_rotateZ(Module *md, double cth, double sth){
	if(NULL != md){
		Matrix mat;
		matrix_clear(&mat);
		matrix_rotateZ(&mat, cth, sth);
		Element* e = element_init(ObjMatrix, &mat);
		md->tail->next = e;
		md->tail = e;
	}
}

// Matrix operand to add a 2D shear matrix to the tail of the module’s list.
void module_shear2D(Module *md, double shx, double shy){
	if(NULL != md){
		Matrix mat;
		matrix_clear(&mat);
		matrix_shear2D(&mat, shx, shy);
		Element* e = element_init(ObjMatrix, &mat);
		md->tail->next = e;
		md->tail = e;
	}
}

//Draw the module into the image using the given view transformation matrix [VTM], Lighting and
//DrawState by traversing the list of Elements. (For now, Lighting can be an empty structure.)
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, /*Lighting *lighting,*/ Image *src){
	Matrix LTM;
	Matrix tempMatrix;
	DrawState tempDraw;
	matrix_identity(&LTM);
	Element iterator;
	Element * temp = malloc(sizeof(Element));
	for(iterator = *(md->head); &iterator != NULL; iterator = *(Element*)iterator.next){
		switch(iterator.type){
			case ObjColor:
				ds->color = iterator.obj.color;
				break;
			case ObjPoint:
				point_copy(&temp->obj.point,&iterator.obj.point);
				matrix_xformPoint(&LTM,&temp->obj.point,&temp->obj.point);
				matrix_xformPoint(GTM,&temp->obj.point,&temp->obj.point);
				matrix_xformPoint(VTM,&temp->obj.point,&temp->obj.point);
				point_normalize(&temp->obj.point);
				point_draw(&temp->obj.point,src,ds->color);
				break;
			case ObjLine:
				line_copy(&temp->obj.line,&iterator.obj.line);
				matrix_xformLine(&LTM,&temp->obj.line);
				matrix_xformLine(GTM,&temp->obj.line);
				matrix_xformLine(VTM,&temp->obj.line);
				line_normalize(&temp->obj.line);
				line_draw(&temp->obj.line,src,ds->color);
				break;
			case ObjPolyline:
				polyline_copy(&temp->obj.polyline,&iterator.obj.polyline);
				matrix_xformPolyline(&LTM,&temp->obj.polyline);
				matrix_xformPolyline(GTM,&temp->obj.polyline);
				matrix_xformPolyline(VTM,&temp->obj.polyline);
				polyline_normalize(&temp->obj.polyline);
				polyline_draw(&temp->obj.polyline,src,ds->color);
				break;
			case ObjPolygon:
				polygon_copy(&temp->obj.polygon,&iterator.obj.polygon);
				matrix_xformPolygon(&LTM,&temp->obj.polygon);
				matrix_xformPolygon(GTM,&temp->obj.polygon);
				matrix_xformPolygon(VTM,&temp->obj.polygon);
				polygon_normalize(&temp->obj.polygon);
				if (ds->shade == ShadeFrame)
				{
					polygon_draw(&temp->obj.polygon,src,ds->color);
				}
				else if(ds->shade == ShadeConstant ){
					polygon_drawFill(&temp->obj.polygon,src,ds->color);
				}
				break;
			case ObjMatrix:
				matrix_multiply(&(iterator.obj.matrix), &LTM, &LTM);
			case ObjIdentity:
				matrix_identity(&LTM);
			case ObjModule:
				matrix_multiply(GTM, &LTM, &tempMatrix);
				tempDraw = *ds;
				module_draw(iterator.obj.module, VTM, &tempMatrix, &tempDraw, /* light, */ src); 
			default:
				//bla
				break;
		}
	}
}


// //3D functions

// // Matrix operand to add a 3D translation to the Module.
// void module_translate(Module *md, double tx, double ty, double tz);

// // Matrix operand to add a 3D scale to the Module.
// void module_scale(Module *md, double sx, double sy, double sz);

// // Matrix operand to add a rotation about the X-axis to the Module.
// void module_rotateX(Module *md, double cth, double sth);

// // Matrix operand to add a rotation about the Y-axis to the Module.
// void module_rotateY(Module *md, double cth, double sth);

// //Matrix operand to add a rotation that orients to the orthonormal axes ~u, ~v, w~
// void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w);

// //Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines.
// //If solid is non-zero, use polygons. Make sure each polygon has surface normals defined for it.
// void module_cube(Module *md, int solid);


// //shading/color module functions

// // Adds the foreground color value to the tail of the module’s list.
// void module_color(Module *md, Color *c);


