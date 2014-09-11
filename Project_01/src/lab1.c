/*
  This is an example of reading and writing an image using the ppmIO.c
  routines.  To manipulate the image, change the pixel color values.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppmIO.h"
#include "ppmMethods.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image1;
  Pixel *image2;
  Pixel *image3;
  int rows, cols, colors;
  long imagesize;
  // //int intensity, avg_r, avg_g, avg_b;


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

  image3 = readPPM(&rows, &cols, &colors, argv[3]);
  if(!image3) {
    fprintf(stderr, "Unable to read mask %s\n", argv[3]);
    exit(-1);
  }else{
    printf("successfully opened image %s\n", argv[3]);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  //image1 = makeMask(image, imagesize);
  image1 = setBackground(image1, image2, image3, imagesize);
  //image1 = translate(image1, image2, image3, imagesize, cols, 100, 100);
  //image1 = toGreyscale(image1, imagesize);
  image1 = toNegative(image1, imagesize);
  //image1 = horizontalBlur(image1, imagesize);



//   /* write out the resulting image */
  writePPM(image1, rows, cols, colors /* s/b 255 */, argv[4]);

//   /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image1);
  free(image2);
  free(image3);
#endif

  return(0);
}

/* code snippets for different tasks that were done in previous steps:

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
*/

