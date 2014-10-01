/*
Erfan Azad
Date: 29 Sep 2014
file: polygon.h
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "polygon.h"
#include "line.h"
#include "point.h"
#include "Image.h"
#include "color.h"

// returns an allocated Polygon pointer initialized so that numVertex is 0 and vertex is NULL.
Polygon *polygon_create(){
	Polygon *p=malloc(sizeof(Polygon));
    if(NULL == p){
        printf("ERROR: polygon_create >> malloc failed!\n");
        exit(-1);
    }
    p->vertex=NULL;
    p->numVertex=0;
    p->zBuffer = 1;
    return p;
}

// returns an allocated Polygon pointer with the vertex list
//initialized to a copy of the points in vlist.
Polygon *polygon_createp(int numV, Point *vlist){
	Polygon *p=malloc(sizeof(Polygon));
    if(NULL == p){
        printf("ERROR: polygon_createp >> malloc failed!\n");
        exit(-1);
    }
    p->vertex=malloc(sizeof(Point)*numV);
    for (int i = 0; i < numV; i++){
        point_copy(&(p->vertex[i]),&vlist[i]);
    }
    p->numVertex=numV;
    p->zBuffer = 1;
    return p;
}

// frees the internal data for a Polygon and the Polygon pointer
void polygon_free(Polygon *p){
	if (p!=NULL) {
        if (p->vertex!=NULL) {
            free(p->vertex);
        }
        free(p);
    }
}

//initializes the existing Polygon to an empty Polygon.
void polygon_init(Polygon *p){
	p->vertex=NULL;
    p->numVertex=0;
    p->zBuffer = 1;
}

// initializes the vertex array to the points in vlist
void polygon_set(Polygon *p, int numV, Point *vlist){
	if (p->vertex!=NULL) {
        free(p->vertex);
    }
        p->vertex=malloc(sizeof(Point)*numV);
    for (int i = 0; i < numV; i++)
    {
        point_copy(&(p->vertex[i]),&vlist[i]);
    }
    p->numVertex = numV;
    p->zBuffer = 1;
}

// frees the internal data and resets the fields.
void polygon_clear(Polygon *p){
	if(p->vertex != NULL){
        free(p->vertex);
    }
    p->vertex = NULL;
    p->numVertex = 0;
    p->zBuffer = 1;
}

//sets the z-buffer flag to the given value
void polygon_zBuffer(Polygon *p, int flag){
	if(NULL != p){
        p->zBuffer = flag;
    }
}

//De-allocates/allocates space and copies the 
//vertex and color data from one polygon to the other
void polygon_copy(Polygon *to, Polygon *from){
	if(NULL != to && NULL != from){
        polygon_clear(to);
        *to = *from;
    }
}

// prints polygon data to the stream designated by the FILE pointer
void polygon_print(Polygon *p, FILE *fp){
	if(NULL != p && NULL != fp){
        int i;
        fprintf(fp, "%d\n",p->numVertex);//writes number of vertecies
        fprintf(fp, "%d\n",p->zBuffer);//writes the zBuffer value
        for(i=0; i<p->numVertex; i++){
            fprintf(fp, "%f %f %f %f\n",p->vertex[i].val[0], p->vertex[i].val[1], p->vertex[i].val[2], p->vertex[i].val[3]);
        }
    }
}

// draw the outline of the polygon using color c.
void polygon_draw(Polygon *p, Image *src, Color colr){
	Line l;
    int i;
    for (i=0; i< p->numVertex-1; i++){
        line_set2D(&l,p->vertex[i].val[0], p->vertex[i].val[1], p->vertex[i+1].val[0], p->vertex[i+1].val[1]);
        line_draw(&l, src, colr);
    }
    line_set2D(&l, p->vertex[i].val[0], p->vertex[i].val[1], p->vertex[0].val[0], p->vertex[0].val[1]);
    line_draw(&l, src, colr);
}

//draw the filled polygon using color c with the
//scanline rendering algorithm.
void polygon_drawFill(Polygon *p, Image *src, Color c){

}

/*
Auxilary function to be used with qsort
*/
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

//draw the filled polygon using color c with the
//Barycentric coordinates algorithm.
void polygon_drawFillB(Polygon *p, Image *src, Color c){
	float alpha, beta, gamma;
	float xlist[3] = {p->vertex[0].val[0], p->vertex[1].val[0], p->vertex[2].val[0]};
	float ylist[3] = {p->vertex[0].val[1], p->vertex[1].val[1], p->vertex[2].val[1]};
	qsort(xlist, 3, sizeof(float), compare);
	qsort(ylist, 3, sizeof(float), compare);
	int Xmin = (int)(xlist[0]+0.5);
	int Ymin = (int)(ylist[0]+0.5);
	int Xmax = (int)(ylist[2]+0.5);
	int Ymax = (int)(ylist[2]+0.5);


	for (int i = Ymin; i < Ymax; i++)
	{
		for (int j = Xmin; j < Xmax; j++)
		{
			beta = Aux_implicit_line(p->vertex[0], p->vertex[2], j,i)/ Aux_implicit_line(p->vertex[0], p->vertex[2],p->vertex[1].val[0], p->vertex[1].val[1]);
			gamma = Aux_implicit_line(p->vertex[0], p->vertex[1], j,i)/ Aux_implicit_line(p->vertex[0], p->vertex[1],p->vertex[2].val[0], p->vertex[2].val[1]);
			alpha = 1- beta - gamma; 


			if (beta<0 || gamma <0 || alpha<0)
			{
				continue;
			}
			else{
				image_setColor(src,i,j,c);
			}

		}

	}


}

/*
Auxilary function to calculate the distance of point p_in from
the line segment p1p2
*/

float Aux_implicit_line(Point p1, Point p2, float x,float y){
	float x0=p1.val[0];
	float y0=p1.val[1];

	float x1=p2.val[0];
	float y1=p2.val[1];
	x += 0.5;
	y += 0.5;
	return (y0-y1)*x + (x1-x0)*y + x0*y1 - x1*y0;
}







