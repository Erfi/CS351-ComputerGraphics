/*
Erfan Azad
Date: Wed 17 Sep 2014
File: fract.c
This file contains two functions for making fractiles.
*/

#include <stdio.h>
#include "fract.h"
#include "Image.h"

void mandelbrot( Image *dst, float x0, float y0, float dx){
	float MinRe = x0;
	float MaxIm = y0;
	float MaxRe = MinRe + (float)((dst->cols - 1) * dx);
	float MinIm = MaxIm - (float)((dst->rows - 1) * dx);
	printf("MaxRe, MinIm: %f, %f\n",MaxRe, MinIm);
	int maxIterations = 500;

	float Re_factor = (float)((MaxRe - MinRe) / (dst->cols -1));
	float Im_factor = (float)((MaxIm - MinIm) / (dst->rows -1));

	int x;
	int y;
	for(y=0; y< dst->rows; y++){
		float c_im = MaxIm - (float)(y)*Im_factor;
		for(x=0; x< dst->cols; x++){
			float c_re = MinRe + (float)(x)*Re_factor;
			
			float z_re = c_re;
			float z_im = c_im;
			int is_inside = 1;
			int n;
			for(n=0; n< maxIterations; n++){
				float z_re2 = z_re * z_re;
				float z_im2 = z_im * z_im;
				if((z_re2 + z_im2) > 4.0){
					is_inside = 0;
					break;
				}
				z_im = 2.0 * z_re * z_im + c_im;
				z_re = z_re2 - z_im2 + c_re;
			}
			if(is_inside==1){ // paint black
				image_setc(dst,y, x, 0, 0.1);
				image_setc(dst,y, x, 1, 0.4);
				image_setc(dst,y, x, 2, 0.7);
			}else{ // paint reddish
				image_setc(dst,y, x, 0, 0.8);
				image_setc(dst,y, x, 1, 0.1);
				image_setc(dst,y, x, 2, 0.1);	
			}
		}
	} 
}


void julia(Image *dst, float x0, float y0, float dx){

}
