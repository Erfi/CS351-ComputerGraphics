/*
Erfan Azad
Date: 29 Sep 2014
file: polygon.h
*/

Polygon *polygon_create(){
	Polygon *p=malloc(sizeof(Polygon));
    if(NULL == p){
        printf("ERROR: polygon_create >> malloc failed!\n");
        exit(-1);
    }
    p->vertex=NULL;
    p->numVertex=0;
    p->zBuffer = 1;
    return p;
}

Polygon *polygon_createp(int numV, Point *vlist);
void polygon_free(Polygon *p);
void polygon_init(Polygon *p);
void polygon_set(Polygon *p, int numV, Point *vlist);
void polygon_clear(Polygon *p);
void polygon_zBuffer(Polygon *p, int flag);
void polygon_copy(Polygon *to, Polygon *from);
void polygon_print(Polygon *p, FILE *fp);
void polygon_draw(Polygon *p, Image *src, Color c);
void polygon_drawFill(Polygon *p, Image *src, Color c);
void polygon_drawFillB(Polygon *p, Image *src, Color c);
