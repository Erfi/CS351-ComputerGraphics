/*
Erfan Azad
Date: 24 Sep 2014
ellipse.h
*/
#ifndef __ELLIPSE_H__
#define __ELLIPSE_H__

typedef struct{
	double ra; //major axis radius
	double rb; //minor axis radius
	Point c;    //center point
	//double a – (optional) angle of major axis relative to the X-axis
}Ellipse;

#endif