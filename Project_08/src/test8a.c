/*
  Bruce A. Maxwell
  Fall 2014

  Example code for drawing a single cube

  C Version
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "module.h"
#include "drawState.h"
#include "line.h"
#include "point.h"
#include "polyline.h"
#include "polygon.h"
#include "circle.h"
#include "color.h"
#include "Image.h"
#include "matrix.h"
#include "view.h"


int main(int argc, char *argv[]) {
  Image *src;
  Matrix VTM;
  Matrix GTM;
  Module *cube;
  int rows = 360;
  int cols = 640;

  Color Grey = {{1, 1, 1}};

  DrawState *ds;
  View3D view;

  // initialize the image
  src = image_create(rows, cols);

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 5, 5, -7.0);
  vector_set(&(view.vpn), -5, -5, 7);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 2.0;
  view.du = 1.6;
  view.dv = .9;
  view.f = 0.0;
  view.b = 15;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple cube module
  cube = module_create();
  module_scale( cube, 3, 1, 2 );
  module_color( cube, &Grey );
  module_cube( cube, 1);


  ds = drawstate_create();
  ds->shade = ShadeDepth;

  matrix_identity(&GTM);
  module_draw(cube, &VTM, &GTM, ds, /*NULL,*/ src);

  // write out the image
  image_write(src, "test8a.ppm");

  // free stuff here
  module_delete( cube );
  image_free( src );
  

  return(0);
}
