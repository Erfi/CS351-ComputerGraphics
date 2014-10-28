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
	// e->type = ObjNone;
	// e->obj = NULL;
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
			printf("init\n");
			point_print(&e->obj.point, stdout);
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
			e->obj.module = (Module*)obj;
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
	Module* mod = malloc(sizeof(Module));
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
		// }
		}
		iterator->type = ObjNone;
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
			case ObjModule:
				free(&(iterator->obj));
				break;
			default:
				break;
		}
		iterator->type = ObjNone;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
	}
}

// Adds a pointer to the Module sub to the tail of the module’s list.
void module_module(Module *md, Module *sub){
	if(NULL != md && NULL != sub){
		Element* e = element_init(ObjModule, sub);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
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
		matrix_identity(&mat);
		matrix_translate2D(&mat, tx, ty);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
			return;
		}
		md->tail->next = e;
		md->tail = e;
	}
}

// Matrix operand to add a scale matrix to the tail of the module’s list.
void module_scale2D(Module *md, double sx, double sy){
	if(NULL != md){
		Matrix mat;
		matrix_identity(&mat);
		matrix_scale2D(&mat, sx, sy);
		printf("scale sx %f  sy %f \n",sx,sy);
				matrix_print(&mat, stdout);
		Element* e = element_init(ObjMatrix, &mat);
		if (md->head == NULL)
		{
			md->head = e;
			md->tail = e;
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
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
			return;
		}
		md->tail->next = e;
		md->tail = e;
	}
}

//Draw the module into the image using the given view transformation matrix [VTM], Lighting and
//DrawState by traversing the list of Elements. (For now, Lighting can be an empty structure.)
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Image *src){
	// printf("moduleDAWPIOJAPIDJ");
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
	printf("LTM _ begining\n");
	matrix_print(&LTM, stdout);

		printf("GTM _ begining\n");
	matrix_print(GTM, stdout);

	printf("VTM \n");
	matrix_print(VTM, stdout);



	for(iterator = (md->head); iterator != NULL; iterator = (Element*)iterator->next){

		//printf("enumprint: %d\n", iterator-> type);
		// printf("temp val: %d\n", tempPoint.val[0]);
		// printf("iterator val: %d\n", iterator->obj.point.val[0]);

		// if (iterator-> type == ObjMatrix)
		// {
		// 	printf("true!");
		// }

		switch(iterator->type){
			case ObjColor:
				ds->color = iterator->obj.color ;
				break;
			case ObjPoint:
				printf("before\n");
				point_print(&iterator->obj.point,stdout);
				point_copy(&tempPoint,&iterator->obj.point);
				matrix_xformPoint(&LTM,&tempPoint,&tempPoint);
				// printf("LTM _ onjPoint\n");
				// matrix_print(&LTM, stdout);
				// printf("after\n");
				// point_print(&tempPoint,stdout);
				matrix_xformPoint(GTM,&tempPoint,&tempPoint);
				matrix_xformPoint(VTM,&tempPoint,&tempPoint);
				printf("after VTM\n");
				point_print(&iterator->obj.point,stdout);
				point_normalize(&tempPoint);
				// printf("VTM point \n");
				// matrix_print(VTM, stdout);

				// point_draw(&tempPoint,src,ds->color);
				break;
	 		case ObjLine:
				// printf("objline\n");
				line_copy(&tempLine,&iterator->obj.line);
				matrix_xformLine(&LTM,&tempLine);
				matrix_xformLine(GTM,&tempLine);
				matrix_xformLine(VTM,&tempLine);
				line_normalize(&tempLine);
					// printf("VTM line \n");
					// matrix_print(VTM, stdout);
				// line_draw(&tempLine,src,ds->color);
				break;
			case ObjPolyline:
				// printf("objPolyline\n");
				polyline_copy(&tempPolyline,&iterator->obj.polyline);
				matrix_xformPolyline(&LTM,&tempPolyline);
				matrix_xformPolyline(GTM,&tempPolyline);
				matrix_xformPolyline(VTM,&tempPolyline);
				polyline_normalize(&tempPolyline);
				// printf("VTM polyline\n");
				// matrix_print(VTM, stdout);
				// polyline_draw(&tempPolyline,src,ds->color);
				break;
			case ObjPolygon:
				// printf("objPolygon\n");
				polygon_copy(&tempPolygon,&iterator->obj.polygon);
				matrix_xformPolygon(&LTM,&tempPolygon);
				matrix_xformPolygon(GTM,&tempPolygon);
				matrix_xformPolygon(VTM,&tempPolygon);
				polygon_normalize(&tempPolygon);
				// printf("VTM polygon\n");
				// matrix_print(VTM, stdout);
				if (ds->shade == ShadeFrame)
				{
					// polygon_draw(&tempPolygon,src,ds->color);
				}
				else if(ds->shade == ShadeConstant ){
					// polygon_drawFill(&tempPolygon,src,ds->color);
				}
				break;
			case ObjMatrix:
				// printf("LTM _ objMatrix before\n");
				// matrix_print(&LTM, stdout);
				matrix_multiply(&(iterator->obj.matrix), &LTM, &LTM);
				// 	printf("VTM matrix\n");
				// matrix_print(VTM, stdout);
				// printf("iterator->obj.matrix\n");
				// matrix_print(&iterator->obj.matrix, stdout);
				// printf("LTM _ objMatrix after\n");
				// matrix_print(&LTM, stdout);
				break;
			case ObjIdentity:
				// printf("objIdentity\n");
				matrix_identity(&LTM);
				// printf("VTM identify\n");
				// matrix_print(VTM, stdout);
				// printf("LTM _ objIdentity\n");
				// matrix_print(&LTM, stdout);
				break;
			case ObjLight:
				break;
			case ObjModule:
				printf("objModule\n");
				matrix_multiply(GTM, &LTM, &tempGTM);
				tempDraw = *ds;
				// printf("VTM module\n");
				// matrix_print(VTM, stdout);
				// module_draw(iterator->obj.module, VTM, &tempGTM, &tempDraw, /* light, */ src); 
				break;
			default:
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


