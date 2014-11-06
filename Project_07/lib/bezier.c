/*
Erfan & Ryan
Date: 4 November 2014
File: bezier.c
*/

//sets the zbuffer flag to 1 and the curve points to the X-axis between 0 and 1.
void bezierCurve_init(BezierCurve *b){
	if(NULL != b){
		b->flag = 1;
		int i;
		for(i=0; i<4; i++){
			b->ctrl[i].val[0] = 0.5;
		}
	}
}

//sets the zbuffer flag to 1 and the surface to the X-Z plane between (0, 0) and (1, 1).
void bezierSurface_init(BezierSurface *b){
	if(NULL != b){
		b->flag = 1;
		int i;
		for(i=0; i<16; i++){
			b->ctrl[i].val[0] = 0.5;
			b->ctrl[i].val[2] = 0.5;
		}
	}
}

//sets the control points of the BezierCurve to the four points in the vlist array.
void bezierCurve_set(BezierCurve *b, Point *vlist){
	if((NULL != b) && (NULL != vlist)){
		int i;
		for(i=0; i<4; i++){
			point_copy(&b->ctrl[i], &vlist[i]);
		}
	}
}

//sets the control points of the BezierSurface to the 16 points in the vlist array.
void bezierSurface_set(BezierSurface *b, Point *vlist){
	if((NULL != b) && (NULL != vlist)){
		int i;
		for(i=0; i<4; i++){
			point_copy(&b->ctrl[i], &vlist[i]);
		}
	}
}
void bezierCurve_zBuffer(BezierCurve *p, int flag){
	if(NULL != p){
		p->flag = flag;
	}
}

void bezierSurface_zBuffer(BezierCurve *p, int flag){
	if(NULL != p){
		p->flag = flag;
	}
}
void bezierCurve_draw(BezierCurve *b, Image *src, Color c){
	
}

