/* 
Erfan Azad
Date: Mon 15 Sep 2014
This file contains the definitions of all the method declarations in
image.c which deals with Constructors & Destructors, I/O functions, Access, Utility
*/

/* constructors & destructors */
Image* image_create(int rows, int cols);
void image_free(Image* src);
void image_init(Image* src);
int image_alloc(Image* src, int rows, int cols);
void image_dealloc(Image* src);

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