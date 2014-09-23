//
//  color.c
//  
//
//  Created by Ryan Brandt on 9/22/14.
//
//

#include "color.h"
//– copies the Color data.
void Color_copy(Color *to, Color *from){
    if (to==NULL||from ==NULL) {
        printf("pointer is null");
        return;
    }
    to->rgb[0]=from->rgb[0];
    to->rgb[1]=from->rgb[1];
    to->rgb[2]=from->rgb[2];

    
}
//– sets the Color data.
void Color_set(Color *to, float r, float g, float b){
    if (to==NULL) {
        printf("pointer is null");
        return;
    }
    to->rgb[0]=r;
    to->rgb[1]=g;
    to->rgb[2]=b;
    
}
