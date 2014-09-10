/*
  This is an example of reading and writing an image using the ppmIO.c
  routines.  To manipulate the image, change the pixel color values.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;
  long i;
  int intensity, avg_r, avg_g, avg_b;

  if(argc < 3) {
    printf("Usage: ppmtest <input file> <output file>\n");
    exit(-1);
  }

  /* read in the image */
  image = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  /* mess with the image here
   * In this case it it making a horizontal blur by averaging each 5 pixel */
  for(i=0;i<imagesize;i++) {
    if (i < 5) {
      avg_r = ((int)image[0].r + (int)image[1].r + (int)image[2].r + (int)image[3].r + (int)image[4].r)/5;
      avg_g = ((int)image[0].g + (int)image[1].g + (int)image[2].g + (int)image[3].g + (int)image[4].g)/5;
      avg_b = ((int)image[0].b + (int)image[1].b + (int)image[2].b + (int)image[3].b + (int)image[4].b)/5;

      image[i].r = avg_r;
      image[i].g = avg_g;
      image[i].b = avg_b;
    }
    else{
      avg_r = ((int)image[i-4].r + (int)image[i-3].r + (int)image[i-2].r + (int)image[i-1].r + (int)image[i].r)/5;
      avg_g = ((int)image[i-4].g + (int)image[i-3].g + (int)image[i-2].g + (int)image[i-1].g + (int)image[i].g)/5;
      avg_b = ((int)image[i-4].b + (int)image[i-3].b + (int)image[i-2].b + (int)image[i-1].b + (int)image[i].b)/5;

      image[i].r = avg_r;
      image[i].g = avg_g;
      image[i].b = avg_b;
    }
    // this little piece of code converts the image to inverse greyscale
    //intensity = ((int)image[i].r + (int)image[i].g + (int)image[i].b) / 3;
    //image[i].r = 255 - intensity;
    //image[i].g = 255 - intensity;
    //image[i].b = 255 - intensity;
  }

  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
