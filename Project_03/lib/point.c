//
//  point.c
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#include "point.h"
#include "Image.h"

void point_set2D(Point *p, double x, double y){
/*set the first two values of the vector to x and y. Set the third value to 0 and the fourth value to 1 .*/
    if (p==NULL) {
        printf("ERROR: point_set2D >> pointer parameter is NULL\n");
        exit(-1);
    }
    p->val[0]=x;
    p->val[1]=y;
    p->val[2]=0;
    p->val[3]=1;
}

void point_set3D(Point *p, double x, double y, double z){
    /*set the point’s values to x and y and z. Set the homogeneous coordinate to 1 .*/
    if (p==NULL) {
        printf("ERROR: point_set3D >> pointer parameter is NULL\n");
        exit(-1);
    }
    p->val[0]=x;
    p->val[1]=y;
    p->val[2]=z;
    p->val[3]=1;
}

void point_set(Point *p, double x, double y, double z, double h){
/*set the four values of the vector to x, y, z, and h, respectively.*/
    if (p==NULL) {
        printf("ERROR: point_set >> pointer parameter is NULL\n");
        exit(-1);
    }
    p->val[0]=x;
    p->val[1]=y;
    p->val[2]=z;
    p->val[3]=h;
}


void point_copy(Point *to, Point *from){
/*copy the point data structure.*/
    if (to==NULL||from ==NULL) {
        printf("ERROR: point_copy >> pointer parameter is NULL\n");
        exit(-1);
    }
    to->val[0] = from->val[0];
    to->val[1] = from->val[1];
    to->val[2] = from->val[2];
    to->val[3] = from->val[3];
}


void point_draw(Point *p, Image *src, Color c){
/*draw the point into src using color c.*/
    if (p==NULL||src ==NULL|| c==NULL) {
        printf("pointer is null");
        return;
    }
    double x=p->val[0];
    double y=p->val[1];
    src->data[x][y].rgb=c;
    src->data[x][y].z=p->val[2];
}


void point_drawf(Point *p, Image *src, FPixel c){
/*draw the p into src using FPixel c.*/
    if (p==NULL||src ==NULL|| c==NULL) {
        printf("pointer is null");
        return;
    }
    double x=p->val[0];
    double y=p->val[1];
    src->data[x][y].rgb=c->rgb;
    src->data[x][y].z=p->val[2];

}











