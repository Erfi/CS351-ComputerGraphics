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




//Allocate and return an initialized but empty Element.
Element *element_create(){
	Element *e = malloc(sizeof(Element));
	e->next = NULL;
	return e;
}

//Allocate an Element and store a duplicate of the data pointed to by obj in the Element. Modules do
//not get duplicated. The function needs to handle each type of object separately in a case statement.
Element *element_init(ObjectType type, void *obj){
	Element *e = malloc(sizeof(Element));
	e->type = type;
	e->next = NULL;
	switch (type){
		case ObjNone:
			break;
		case ObjLine:
			line_copy(&e->obj.line,(Line *)obj);
			break;
		case ObjPoint:
			point_copy(&e->obj.point,(Point *)obj);
			break;
		case ObjPolyline:
			polyline_init(&e->obj.polyline);
			polyline_copy(&e->obj.polyline, (Polyline *)obj);
			break;
		case ObjPolygon:
			polygon_init(&e->obj.polygon);
			polygon_copy(&e->obj.polygon,(Polygon *)obj);
			break;
		case ObjIdentity:
			break;
		case ObjMatrix:
			matrix_copy(&e->obj.matrix, (Matrix *)obj);
			break;
		case ObjColor:
		case ObjBodyColor:
		case ObjSurfaceColor:
			Color_copy(&e->obj.color, (Color *)obj);
			break;
		case ObjSurfaceCoeff:
			e->obj.coeff = *(float*)obj;
			break;
		case ObjLight:
			break;
		case ObjModule:
			e->obj.module = (Module *) obj;
			break;
		default:
			e->type = ObjNone;
			break;
	}
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
	Module* mod = (Module *)malloc(sizeof(Module));
	mod->head = NULL;
	mod->tail = NULL;
	return mod;
}

// clear the module’s list of Elements, freeing memory as appropriate.
void module_clear(Module *md){
	Element *iterator;
	for(iterator = (md->head); iterator != NULL; iterator = (Element*)iterator->next){
		switch (iterator->type){
			case ObjPolyline:
				polyline_free(&(iterator->obj.polyline));
				// printf("this is working");
				break;
			case ObjPolygon:
				polygon_free(&(iterator->obj.polygon));
				// printf("this is working");
				break;
			case ObjModule:
				free(&(iterator->obj.module));
				break;
			default:
				// printf("this is working");
				break;
		}
	}
}

// Free all of the memory associated with a module, including the memory pointed to by md
void module_delete(Module *md){
	Element *iterator;
	for(iterator = (md->head); iterator != NULL; iterator = (Element*)iterator->next){
		switch (iterator->type){
			case ObjPolyline:
				polyline_free(&(iterator->obj.polyline));
				break;
			case ObjPolygon:
				polygon_free(&(iterator->obj.polygon));
				break;
			default:
				break;
		}
	}
	free(md);
}

// Generic insert of an element into the module at the tail of the list.
void module_insert(Module *md, Element *e){
	if(NULL != md && NULL != e){
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Adds a pointer to the Module sub to the tail of the module’s list.
void module_module(Module* md, Module* sub){
	if(NULL != md && NULL != sub){
		Element* e = element_init(ObjModule, sub);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Adds p to the tail of the module’s list.
void module_point(Module *md, Point *p){
	if(NULL != md && NULL != p){
		Element* e = element_init(ObjPoint, p);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Adds p to the tail of the module’s list.
void module_line(Module *md, Line *p){
	if(NULL != md && NULL != p){

		Element* e = element_init(ObjLine, p);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{	
			md->tail->next = e;
			md->tail = e;
		}
	}	
}

// Adds p to the tail of the module’s list.
void module_polyline(Module *md, Polyline *p){
	if(NULL != md && NULL != p){
		Element* e = element_init(ObjPolyline, p);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{	
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Adds p to the tail of the module’s list.
void module_polygon(Module *md, Polygon *p){
	if(NULL != md && NULL != p){
		Element* e = element_init(ObjPolygon, p);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Object that sets the current transform to the identity, placed at the tail of the module’s list.
void module_identity(Module *md){
	Element* e  = element_create();
	e->type = ObjIdentity;
	if (md->head == NULL)
	{
		md->head = e;
		md->tail = e;
	}
	else{
		md->tail->next = e;
		md->tail = e;
	}
}

// Matrix operand to add a translation matrix to the tail of the module’s list.
void module_translate2D(Module *md, double tx, double ty){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_translate2D(&mat, tx, ty);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}
		else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Matrix operand to add a scale matrix to the tail of the module’s list.
void module_scale2D(Module *md, double sx, double sy){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_scale2D(&mat, sx, sy);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}
		else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Matrix operand to add a rotation about the Z axis to the tail of the module’s list.
void module_rotateZ(Module *md, double cth, double sth){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_rotateZ(&mat, cth, sth);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// Matrix operand to add a 2D shear matrix to the tail of the module’s list.
void module_shear2D(Module *md, double shx, double shy){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_shear2D(&mat, shx, shy);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

//Draw the module into the image using the given view transformation matrix [VTM], Lighting and
//DrawState by traversing the list of Elements. (For now, Lighting can be an empty structure.)
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Image *src){
	Matrix LTM;
	Matrix tempGTM;
	DrawState tempDraw;
	Element *iterator;
	Point tempPoint;
	Line tempLine;
	Polygon tempPolygon;
	Polyline tempPolyline;

	matrix_identity(&LTM);
	polygon_init(&tempPolygon);
	polyline_init(&tempPolyline);
	// printf("LTM _ begining\n");
	// matrix_print(&LTM, stdout);

	for(iterator = md->head; iterator != NULL; iterator = (Element*)iterator->next){
		switch(iterator->type){
			case ObjColor:
				ds->color = iterator->obj.color ;
				break;
			case ObjPoint:
				printf("objPoint\n");
				point_copy(&tempPoint,&iterator->obj.point);
				matrix_xformPoint(&LTM,&tempPoint,&tempPoint);
				matrix_xformPoint(GTM,&tempPoint,&tempPoint);
				matrix_xformPoint(VTM,&tempPoint,&tempPoint);
				point_normalize(&tempPoint);
				printf("src (rows, cols): (%d, %d)\n",src->rows, src->cols);
				point_print(&tempPoint, stdout);
				point_draw(&tempPoint,src,ds->color);
				break;
	 		case ObjLine:
				printf("objline\n");
				line_copy(&tempLine,&iterator->obj.line);
				matrix_xformLine(&LTM,&tempLine);
				matrix_xformLine(GTM,&tempLine);
				matrix_xformLine(VTM,&tempLine);
				line_normalize(&tempLine);
				line_draw(&tempLine,src,ds->color);
				break;
			case ObjPolyline:
				printf("objPolyline\n");
				polyline_copy(&tempPolyline,&iterator->obj.polyline);
				matrix_xformPolyline(&LTM,&tempPolyline);
				matrix_xformPolyline(GTM,&tempPolyline);
				matrix_xformPolyline(VTM,&tempPolyline);
				polyline_normalize(&tempPolyline);
				polyline_draw(&tempPolyline,src,ds->color);
				break;
			case ObjPolygon:
				printf("objPolygon\n");
				polygon_copy(&tempPolygon,&iterator->obj.polygon);
				matrix_xformPolygon(&LTM,&tempPolygon);
				matrix_xformPolygon(GTM,&tempPolygon);
				matrix_xformPolygon(VTM,&tempPolygon);
				polygon_normalize(&tempPolygon);
				if (ds->shade == ShadeFrame)
				{
					polygon_draw(&tempPolygon,src,ds->color);
				}
				else if(ds->shade == ShadeConstant ){
					polygon_drawFill(&tempPolygon,src,ds->color);
				}
				break;
			case ObjMatrix:
				printf("objMatrix\n");
				matrix_multiply(&(iterator->obj.matrix), &LTM, &LTM);
				break;
			case ObjIdentity:
				printf("objIdentity\n");
				matrix_identity(&LTM);
				break;
			case ObjLight:
				break;
			case ObjModule:
				printf("objModule\n");
				matrix_multiply(GTM, &LTM, &tempGTM);
				tempDraw = *ds;
				// printf("VTM\n");
				// matrix_print(VTM, stdout);
				// printf("tempGTM\n");
				// matrix_print(&tempGTM, stdout);
				// printf("addr iterator->obj.module\n");
				// printf("%p\n",iterator->obj.module);
				// printf("addr tempDraw\n");
				// printf("%p\n",&tempDraw);
				module_draw(iterator->obj.module, VTM, &tempGTM, &tempDraw, /* light, */ src); 
				break;
			default:
				break;
		}
	}
}


// //3D functions

// // Matrix operand to add a 3D translation to the Module.
void module_translate(Module *md, double tx, double ty, double tz){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_translate(&mat, tx, ty, tz);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}
		else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// // Matrix operand to add a 3D scale to the Module.
void module_scale(Module *md, double sx, double sy, double sz){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_scale(&mat, sx, sy, sz);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}
		else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// // Matrix operand to add a rotation about the X-axis to the Module.
void module_rotateX(Module *md, double cth, double sth){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_rotateX(&mat, cth, sth);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// // Matrix operand to add a rotation about the Y-axis to the Module.
void module_rotateY(Module *md, double cth, double sth){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_rotateY(&mat, cth, sth);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// //Matrix operand to add a rotation that orients to the orthonormal axes ~u, ~v, w~
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){
	if((NULL != md) && (NULL != u) && (NULL != v) && (NULL != w)){
		Matrix mat;
		matrix_identity(&mat);
		matrix_rotateXYZ(&mat, u,v,w);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
		}else{
			md->tail->next = e;
			md->tail = e;
		}
	}
}

// //Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines.
// //If solid is non-zero, use polygons. Make sure each polygon has surface normals defined for it.
void module_cube(Module *md, int solid){
	if(NULL != md){
		Point p[8];
		point_set3D( &p[0], -1, -1, -1 );
  		point_set3D( &p[1],  1, -1, -1 );
  		point_set3D( &p[2],  1,  1, -1 );
		point_set3D( &p[3], -1,  1, -1 );
		point_set3D( &p[4], -1, -1,  1 );
		point_set3D( &p[5],  1, -1,  1 );
		point_set3D( &p[6],  1,  1,  1 );
		point_set3D( &p[7], -1,  1,  1 );
		if(solid == 0){//use lines
			Line l[12];
			line_set(&l[0], p[0], p[1]);
			line_set(&l[1], p[1], p[2]);
			line_set(&l[2], p[2], p[3]);
			line_set(&l[3], p[3], p[0]);
			line_set(&l[4], p[0], p[4]);
			line_set(&l[5], p[4], p[7]);
			line_set(&l[6], p[7], p[3]);
			line_set(&l[7], p[5], p[1]);
			line_set(&l[8], p[2], p[6]);
			line_set(&l[9], p[6], p[7]);
			line_set(&l[10], p[6], p[5]);
			line_set(&l[11], p[4], p[5]);
			int i;
			for (i = 0; i < 12; i++)
			{
				module_line(md,&l[i]);
			}			
		}else{//use polygons
			Polygon pol[6];
			int i;
			Point temp[4];
			for (i = 0; i < 6; i++)
			{
				polygon_init(&pol[i]);
			}
			point_copy(&temp[0],&p[0]);
			point_copy(&temp[1],&p[1]);
			point_copy(&temp[2],&p[2]);
			point_copy(&temp[3],&p[3]);

			polygon_set(&pol[0],4,&temp[0]);

			point_copy(&temp[0],&p[1]);
			point_copy(&temp[1],&p[2]);
			point_copy(&temp[2],&p[6]);
			point_copy(&temp[3],&p[5]);

			polygon_set(&pol[1],4,&temp[0]);


			point_copy(&temp[0],&p[5]);
			point_copy(&temp[1],&p[6]);
			point_copy(&temp[2],&p[7]);
			point_copy(&temp[3],&p[4]);

			polygon_set(&pol[2],4,&temp[0]);


			point_copy(&temp[0],&p[4]);
			point_copy(&temp[1],&p[0]);
			point_copy(&temp[2],&p[3]);
			point_copy(&temp[3],&p[7]);

			polygon_set(&pol[3],4,&temp[0]);


			point_copy(&temp[0],&p[4]);
			point_copy(&temp[1],&p[5]);
			point_copy(&temp[2],&p[1]);
			point_copy(&temp[3],&p[0]);

			polygon_set(&pol[4],4,&temp[0]);


			point_copy(&temp[0],&p[7]);
			point_copy(&temp[1],&p[6]);
			point_copy(&temp[2],&p[2]);
			point_copy(&temp[3],&p[3]);

			polygon_set(&pol[5],4,&temp[0]);

			for (i = 0; i < 6; i++)
			{
				module_polygon(md,&pol[i]);
			}	
		}
	}

}


// //shading/color module functions

// // Adds the foreground color value to the tail of the module’s list.
// void module_color(Module *md, Color *c);


