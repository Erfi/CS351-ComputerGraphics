/*
  This is an example of reading and writing an image using the ppmIO.c
  routines.  To manipulate the image, change the pixel color values.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image1;
  Pixel *image2;
  Pixel *imageMask;
  int rows, cols, colors;
  long imagesize;
  long i;
  //int intensity, avg_r, avg_g, avg_b;
  //int green_deviation;
  float alpha;
  int dx, dy; //offsets

  if(argc < 5) {
    printf("Usage: %s <input file_1><input file_2><input mask><output file>\n", argv[0]);
    exit(-1);
  }

  /* read in the image */
  image1 = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image1) {
    fprintf(stderr, "Unable to read file_1 %s\n", argv[1]);
    exit(-1);
  }else{
    printf("successfully opened image %s\n", argv[1]);
  }

  image2 = readPPM(&rows, &cols, &colors, argv[2]);
  if(!image2) {
    fprintf(stderr, "Unable to read file_2 %s\n", argv[2]);
    exit(-1);
  }else{
    printf("successfully opened image %s\n", argv[2]);
  }

  imageMask = readPPM(&rows, &cols, &colors, argv[3]);
  if(!imageMask) {
    fprintf(stderr, "Unable to read mask %s\n", argv[3]);
    exit(-1);
  }else{
    printf("successfully opened image %s\n", argv[3]);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;
  dx = 100;
  dy = 100;
  /* mess with the image here */
  for(i=0;i<imagesize;i++) {
    int transition = i+dx+dy*cols;
    if (transition > imagesize){
      transition = transition - imagesize;
    }
    alpha = imageMask[transition].g/255.0; /*r,g,b of the mask are the same*/
    image1[i].r = (alpha * image1[i].r) + ((1-alpha) * image2[transition].r);
    image1[i].g = (alpha * image1[i].g) + ((1-alpha) * image2[transition].g);
    image1[i].b = (alpha * image1[i].b) + ((1-alpha) * image2[transition].b);
  }

//   /* write out the resulting image */
  writePPM(image1, rows, cols, colors /* s/b 255 */, argv[4]);

//   /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image1);
  free(image2);
  free(imageMask);
#endif

  return(0);
}

/* code snippets for different tasks that were done in previous steps:
............
    // this little piece of code converts the image to inverse greyscale
    //intensity = ((int)image[i].r + (int)image[i].g + (int)image[i].b) / 3;
    //image[i].r = 255 - intensity;
    //image[i].g = 255 - intensity;
    //image[i].b = 255 - intensity;
............
// this piece of code creates a horizontal blur by averaging 5 adjacent pixels
// if (i < 5) {
    //   avg_r = ((int)image[0].r + (int)image[1].r + (int)image[2].r + (int)image[3].r + (int)image[4].r)/5;
    //   avg_g = ((int)image[0].g + (int)image[1].g + (int)image[2].g + (int)image[3].g + (int)image[4].g)/5;
    //   avg_b = ((int)image[0].b + (int)image[1].b + (int)image[2].b + (int)image[3].b + (int)image[4].b)/5;

    //   image[i].r = avg_r;
    //   image[i].g = avg_g;
    //   image[i].b = avg_b;
    // }
    // else{
    //   avg_r = ((int)image[i-4].r + (int)image[i-3].r + (int)image[i-2].r + (int)image[i-1].r + (int)image[i].r)/5;
    //   avg_g = ((int)image[i-4].g + (int)image[i-3].g + (int)image[i-2].g + (int)image[i-1].g + (int)image[i].g)/5;
    //   avg_b = ((int)image[i-4].b + (int)image[i-3].b + (int)image[i-2].b + (int)image[i-1].b + (int)image[i].b)/5;

    //   image[i].r = avg_r;
    //   image[i].g = avg_g;
    //   image[i].b = avg_b;
    // }
..........
//creates a mask of image. puts 255 on green screen and 0 elsewhere.
  green_deviation = abs((int)image[i].g - 108);
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

*/

