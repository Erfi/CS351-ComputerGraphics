//
//  line.c
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#include "line.h"
#include "point.h"
#include "image.h"
#include "color.h"
void line_set2D(Line *l, double x0, double y0, double x1, double y1){
    /*– initialize a 2D line.*/
    if (l==NULL) {
        return;
    }
    l->a->vals[0]=x0;
    l->a->vals[1]=y0;
    l->b->vals[0]=x1;
    l->b->vals[1]=y1;
}

void line_set(Line *l, Point ta, Point tb){
    /*initialize a line to ta and tb.*/
    if (l==NULL) {
        return;
    }
    l->a=ta;
    l->b=tb;

}

void line_zBuffer(Line *l, int flag){
/*set the z-buffer flag to the given value.*/
    if (l==NULL) {
        return;
    }
    l->zBuffer=flag;
}


void line_copy(Line *to, Line *from){
/*copy the line data structure.*/
    if (to==NULL || from == NULL) {
        return;
    }
    to=from;
}


void line_draw(Line *l, Image *src, Color c){
/*draw the line into src using color c.*/
    if (l==NULL) {
        printf("lineDraw");
        return;
    }
    int x0=l->a.vals[0];
    int y0=l->a.vals[1];
    int x1=l->b.vals[0];
    int x1=l->b.vals[1];
    
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        Point *p;
        point_set2d(p,x0,y0);
        point_draw(p,src,c);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
    
}