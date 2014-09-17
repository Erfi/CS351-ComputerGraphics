/*
  Bruce A. Maxwell
  Fall 2013

  Creates a Mandelbrot set at a selected location
*/
#include "Image.h"
#include "fract.h"

int main(int argc, char *argv[]) {
  Image *src;

  src = image_create(750, 1000);

  mandelbrot( src, -2.0, 1.0, 0.0025);

  image_write( src, "../images/fractal.ppm");

  image_free( src );

  return(0);
}
