/*
Erfan Azad
Date: 9 Oct 2014
File: matrix.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "point.h"
#include "polyline.h"
#include "polygon.h"
#include "line.h"


// Set the Vector to (x, y, z, 0.0).
void vector_set(Vector *v, double x, double y, double z){
	v->val[0]=x;
    v->val[1]=y;
    v->val[2]=z;
    v->val[3]=0.0;
}

//Print out the Vector to stream fp in a pretty form
void vector_print(Vector *v, FILE *fp){
	if(NULL != v && NULL != fp){
		fprintf(fp, "%f %f %f %f\n",v->val[0], v->val[1], v->val[2], v->val[3]);
	}
}

//Copy the src Vector into the dest Vector.
void vector_copy(Vector *dest, Vector *src){
	if(NULL != dest && NULL != src){
		*dest = *src;
	}
}

/*
Returns the Euclidean length of the vector,
assuming the homogeneous coordinate is 1.0.
*/
double vector_length(Vector *v){
	if(NULL != v){
		return (sqrt((v->val[0]*v->val[0])+(v->val[1]*v->val[1])+(v->val[2]*v->val[2])));
	}
	printf("ERROR: vector_length >> v is NULL");
	exit(-1);
}

//Normalize the Vector to unit length. Do not modify the homogeneous coordinate.
void vector_normalize(Vector *v){
	double len = vector_length(v);
	v->val[0] = v->val[0]/len;
	v->val[1] = v->val[1]/len;
	v->val[2] = v->val[2]/len;
}

// Returns the scalar product of ~a and ~b.
double vector_dot(Vector *a, Vector *b){
	if(NULL != a && NULL != b){
		return (a->val[0]*b->val[0])+(a->val[1]*b->val[1])+(a->val[2]*b->val[2]);
	}
	printf("ERROR: vector_dot >> v is NULL");
	exit(-1);
}

//Calculates the the cross product (vector product) of ~a and ~b and puts the result in ~c.
void vector_cross(Vector *a, Vector *b, Vector *c){
	if(NULL != a && NULL != b && NULL != c){
		c->val[0]= (a->val[1]*b->val[2])-(a->val[2]*b->val[1]);
		c->val[1]= (a->val[2]*b->val[0])-(a->val[0]*b->val[2]);
		c->val[2]= (a->val[0]*b->val[1])-(a->val[1]*b->val[2]);
	}
}

//Print out the matrix in a nice 4x4 arrangement with a blank line below
void matrix_print(Matrix *mat, FILE *fp){
	if(NULL != mat && NULL != fp){
		fprintf(fp, "%f          %f          %f          %f\n",mat->m[0][0], mat->m[0][1], mat->m[0][2], mat->m[0][3]);
		fprintf(fp, "%f          %f          %f          %f\n",mat->m[1][0], mat->m[1][1], mat->m[1][2], mat->m[1][3]);
		fprintf(fp, "%f          %f          %f          %f\n",mat->m[2][0], mat->m[2][1], mat->m[2][2], mat->m[2][3]);
		fprintf(fp, "%f          %f          %f          %f\n",mat->m[3][0], mat->m[3][1], mat->m[3][2], mat->m[3][3]);
	}
}

//Set the matrix to all zeros.
void matrix_clear(Matrix *mat){
	if(NULL != mat){
		int i, j;
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				mat->m[i][j] = 0.0;
			}
		}
	}
}

// Set the matrix to the identity matrix.
void matrix_identity(Matrix *mat){
	if(NULL != mat){
		int i, j;
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				if(i == j){
					mat->m[i][j] = 1.0;
				}else{
					mat->m[i][j] = 0.0;
				}
			}
		}
	}
}

//Return the element of the matrix at row r, column c.
double matrix_get(Matrix *mat, int r, int c){
	if(NULL != mat){
		return mat->m[r][c];
	}
	printf("ERROR: matrix_get >> mat is NULL");
	exit(-1);
}

// Set the element of the matrix at row r, column c to v
void matrix_set(Matrix *mat, int r, int c, double v){
	if(NULL != mat){
		mat->m[r][c] = v;
	}
}

//Copy the src matrix into the dest matrix.
void matrix_copy(Matrix *dest, Matrix *src){
	if(NULL != dest && NULL != src){
		*dest = *src;
	}
}

//Transpose the matrix mat in place
void matrix_transpose(Matrix *mat){
	if(NULL != mat){
		double temp;
		temp = mat->m[0][1];
		mat->m[0][1] = mat->m[1][0];
		mat->m[1][0] = temp;

		temp = mat->m[0][2];
		mat->m[0][2] = mat->m[2][0];
		mat->m[2][0] = temp;

		temp = mat->m[0][3];
		mat->m[0][3] = mat->m[3][0];
		mat->m[3][0] = temp;

		temp = mat->m[1][2];
		mat->m[1][2] = mat->m[2][1];
		mat->m[2][1] = temp;

		temp = mat->m[1][3];
		mat->m[1][3] = mat->m[3][1];
		mat->m[3][1] = temp;

		temp = mat->m[2][3];
		mat->m[2][3] = mat->m[3][2];
		mat->m[3][2] = temp;
	}
}

//Multiply left and right and put the result in mat
void matrix_multiply(Matrix *left, Matrix *right, Matrix *mat){
	if(NULL != left && NULL != right && NULL != mat){
		int i, j;
		for(i=0; i<4; i++){
			for(j=0; j<4; j++){
				mat->m[i][j] = left->m[i][0]*right->m[0][j];
				mat->m[i][j] += left->m[i][1]*right->m[1][j];
				mat->m[i][j] += left->m[i][2]*right->m[2][j];
				mat->m[i][j] += left->m[i][3]*right->m[3][j];
			}
		}
	}
}

/*
Transform the point p by the matrix mat and put the result in q. 
For this function, p and q need to be different variables.
*/
void matrix_xformPoint(Matrix *mat, Point *p, Point *q){
	if(NULL != mat && NULL != p && NULL != q){
		int i;
		for (i = 0; i < 4; i++)
		{
			q->val[i] = mat->m[i][0]*p->val[0];
			q->val[i] += mat->m[i][1]*p->val[1];
			q->val[i] += mat->m[i][2]*p->val[2];
			q->val[i] += mat->m[i][3]*p->val[3];
		}
	}
}

void matrix_xformVector(Matrix *mat, Vector *p, Vector *q){
	if(NULL != mat && NULL != p && NULL != q){
		int i;
		for (i = 0; i < 4; i++)
		{
			q->val[i] = mat->m[i][0]*p->val[0];
			q->val[i] += mat->m[i][1]*p->val[1];
			q->val[i] += mat->m[i][2]*p->val[2];
			q->val[i] += mat->m[i][3]*p->val[3];
		}
	}
}


//Transform the points and surface normals (if they exist) in the Polygon p by the matrix mat
void matrix_xformPolygon(Matrix *mat, Polygon *p){
	if(NULL != mat && NULL != p){
		int i,j;
		for (i = 0; i < p->numVertex; i++)
		{
			for (j = 0; j < 4; j++)
			{
				p->vertex[i].val[j] = mat->m[j][0]*p
				->vertex[i].val[0];
				p->vertex[i].val[j] += mat->m[j][1]*p->vertex[i].val[1];
				p->vertex[i].val[j] += mat->m[j][2]*p->vertex[i].val[2];
				p->vertex[i].val[j] += mat->m[j][3]*p->vertex[i].val[3];
			}
		}
	}	
}

// – Transform the points in the Polyline p by the matrix m.
void matrix_xformPolyline(Matrix *mat, Polyline *p){
	if(NULL != mat && NULL != p){
		int i,j;
		for (i = 0; i < p->numVertex; i++)
		{
			for (j = 0; j < 4; j++)
			{
				p->vertex[i].val[j] = mat->m[j][0]*p->vertex[i].val[0];
				p->vertex[i].val[j] += mat->m[j][1]*p->vertex[i].val[1];
				p->vertex[i].val[j] += mat->m[j][2]*p->vertex[i].val[2];
				p->vertex[i].val[j] += mat->m[j][3]*p->vertex[i].val[3];
			}
		}
	}
}

// – Transform the points in line by the matrix m.
void matrix_xformLine(Matrix *mat, Line *line){
	if(NULL != mat && NULL != &line->a && &line->b != NULL){
		int j;
		for (j = 0; j < 4; j++)
		{
			line->a.val[j] = mat->m[j][0]*line->a.val[0];
			line->a.val[j] += mat->m[j][1]*line->a.val[1];
			line->a.val[j] += mat->m[j][2]*line->a.val[2];
			line->a.val[j] += mat->m[j][3]*line->a.val[3];
		}
		for (j = 0; j < 4; j++)
		{
			line->b.val[j] = mat->m[j][0]*line->b.val[0];
			line->b.val[j] += mat->m[j][1]*line->b.val[1];
			line->b.val[j] += mat->m[j][2]*line->b.val[2];
			line->b.val[j] += mat->m[j][3]*line->b.val[3];
		}
	}
}

//– Premultiply the matrix by a scale matrix parameterized by sx and sy.
void matrix_scale2D(Matrix *mat, double sx, double sy){
	if(NULL != mat){
		int i;
		for(i=0; i<4; i++){
			mat->m[0][i]=mat->m[0][i]*sx;
			mat->m[1][i]=mat->m[1][i]*sy;
		}
	}
}
void matrix_rotateZ(Matrix *m, double cth, double sth);
void matrix_translate2D(Matrix *m, double tx, double ty);
void matrix_shear2D(Matrix *m, double shx, double shy);
void matrix_translate(Matrix *m, double tx, double ty, double tz);
void matrix_scale(Matrix *m, double sx, double sy, double sz);
void matrix_rotateX(Matrix *m, double cth, double sth);
void matrix_rotateY(Matrix *m, double cth, double sth);
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w);
void matrix_shearZ(Matrix *m, double shx, double shy);
void matrix_perspective(Matrix *m, double d);








