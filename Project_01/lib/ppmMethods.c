/* Erfan Azad
this file includes extra methods to be used in the main 
program as needed
*/
#include "ppmIO.h"
#include "ppmMethods.h"
#include <stdio.h>
#include <stdlib.h>

/*
Creates a mask of the picture with GREEN screen.
Returns a pointer to the masked image.
*/
Pixel* makeMask(Pixel* image, int imageSize){
	int i;
	for (i =0; i<imageSize; i++){
		//creates a mask of image. puts 255 on green screen and 0 elsewhere.
    	if (((int)image[i].g > 2*(int)image[i].r) && ((int)image[i].g > (int)image[i].b)){
      		image[i].r = 255;
      		image[i].g = 255;
      		image[i].b = 255;
    	}
    	else{
      		image[i].r = 0;
      		image[i].g = 0;
      		image[i].b = 0;
    	}
	}
	return image;
}

/* This mathod sets the background image of the input image using the mask created by "makeMask" 
method.
Returns a pointer to the final image
*/
Pixel* setBackground(Pixel* background, Pixel* image, Pixel* imageMask, int imageSize){
	int i;
	for(i=0;i<imageSize;i++) {
    float alpha = imageMask[i].g/255.0; /*r,g,b of the mask are the same*/

    background[i].r = (alpha * background[i].r) + ((1-alpha) * image[i].r);
    background[i].g = (alpha * background[i].g) + ((1-alpha) * image[i].g);
   	background[i].b = (alpha * background[i].b) + ((1-alpha) * image[i].b);
  }
	return background;
}

/* translate the foground image using the mask.
Returns a pointer to the translated image
*/
Pixel* translate(Pixel* background, Pixel* image, Pixel* imageMask, int imageSize, int cols, int dx, int dy){
  int i;
  for(i=0;i<imageSize;i++) {
    int translation = i+dx+dy*cols;
    if (translation > imageSize){
      translation = translation - imageSize;
    }
    float alpha = imageMask[translation].g/255.0; /*r,g,b of the mask are the same*/

    background[i].r = (alpha * background[i].r) + ((1-alpha) * image[translation].r);
    background[i].g = (alpha * background[i].g) + ((1-alpha) * image[translation].g);
   	background[i].b = (alpha * background[i].b) + ((1-alpha) * image[translation].b);
  }
  return background;
}

/*This method turns the given image into its negative
Returns a pointer to the final image
*/
Pixel* toNegative(Pixel* image, int imageSize){
	int i;
	for (i=0; i<imageSize; i++){
	    int intensity = ((int)image[i].r + (int)image[i].g + (int)image[i].b) / 3;
	    image[i].r = 255 - intensity;
	    image[i].g = 255 - intensity;
	    image[i].b = 255 - intensity;
	}
	return image;
}

/*
This method turns the image into greyscale.
Returns a pointer to the greyscale image
*/
Pixel* toGreyscale(Pixel* image, int imageSize){
	int i;
	for (i=0; i<imageSize; i++){
		int intensity = ((int)image[i].r + (int)image[i].g + (int)image[i].b) / 3;
	    image[i].r = intensity;
	    image[i].g = intensity;
	    image[i].b = intensity;
	}
	return image;
}



