/* 
Erfan Azad
Date: Mon 15 Sep 2014
This file contains the definitions of all the method declarations in
image.c which deals with Constructors & Destructors, I/O functions, Access, Utility
*/
#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
/* constructors & destructors */

/*
Allocates an Image structure and initializesthe top level fields to appropriate values.
Allocates space for an image of the specified size, unless
either rows or cols is 0.
Returns a pointer to the allocated Image structure. Returns a NULL pointer if
the operation fails.
*/
Image* image_create(int rows, int cols){
	if((rows == 0) || (cols == 0)){
		printf("ERROR: Cannot create image >> rows or cols is Zero\n");
		return NULL;
	}else{
		Image* image = malloc(sizeof(Image));
		image->data = NULL;
		image->rows = rows;
		image->cols = cols;
		return image;
	}
}

/*
De-allocates image data and frees the Image structure
*/
void image_free(Image* src){
	if(NULL != src){
		int i;
		int j;
		for (i=0; i<src->rows; i++){
			for (j=0; j<src->cols; j++){
				free(src[i][j]);
			}
		}
		src->data = NULL;
		free(src);
		src->NULL;
	}else{
		printf("ERROR: cannot free image >> image pointer is NULL\n");
	}
}

/*
Given an uninitialized Image structure, sets the rows and cols
fields to zero and the data field to NULL.
*/
void image_init(Image* src){
	if(NULL != src){
		src->data = NULL;
		src->rows = 0;
		src->cols = 0;
	}else{
		printf("ERROR: cannot initialize image >> image pointer is NULL\n");
	}
}

/*
Allocates space for the image data given rows and columns and initializes the image data to appropriate values,
such as 0.0 for RGBA and 1.0 for Z.
Returns 0 if the operation is successful. Returns a non-zero value if the operation fails.
(?)This function should probably free existing memory if rows and cols are both non-zero.(?)
*/
int image_alloc(Image* src, int rows, int cols){
	if(NULL != src){
		if(rows==0 || cols==0)
			printf("WARNING: rows or cols is Zero\n");

		src->data = malloc(sizeof(FPixel*)*rows); // creating "rows". an Array of FPixel pointers
		
		int k;
		for(k=0; k<rows; k++){
			src[i] = malloc(sizeof(FPixel)*cols); // creating "cols". an array of FPixels.
		}

		int i;
		int j;
		for(i=0; i<rows; i++){ // initializing image data
			for(j=0; j<cols; j++){
				src->data[i][j].rgb[0]=0.0; //r
				src->data[i][j].rgb[1]=0.0; //g
				src->data[i][j].rgb[2]=0.0; //b
				src->data[i][j].a = 0.0; // a
				src->data[i][j].z = 1.0; // z
			}
		}
		return 0;
	}else{
		printf("ERROR: could not allocate data >> image pointer in NULL\n");
		return -1;
	}
}

/*
De-allocates image data and resets the Image structure
fields. The function does not free the Image structure.
*/
void image_dealloc(Image* src){
	if(NULL != src){
		int i;
		int j;
		for (i=0; i<src->rows; i++){
			for (j=0; j<src->cols; j++){
				free(src[i][j]);
			}
		}
		src->data = NULL;
		src->rows = 0;
		src->cols = 0;
	}else{
		printf("ERROR: cannot deallocate image >> image pointer is NULL\n");
	}
}

/*I/O functions */

Image* image_read(char* filename);
int image_write(Image* src, char* filename);

/* Acces functions */
FPixel image_getf(Image* src, int r, int c);
float image_getc(Image* src, int r, int c, int b);
float image_geta(Image* src, int r, int c);
float image_getz(Image* src, int r, int c);
void image_setf(Image* src, int r, int c, FPixel val);
void image_setc(Image* src, int r, int c, int b, float val);
void image_seta(Image* src, int r, int c, float val);
void image_setz(Image* src, int r, int c, float val);

/* Utility functions */
void image_reset(Image* src);
void image_fill(Image* src, FPixel val);
void image_fillrgb(Image* src, float r, float g, float b);
void image_filla(Image* src, float a);
void image_fillz(Image *src, float z);