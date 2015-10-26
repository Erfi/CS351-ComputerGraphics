Erfan Azad
File: README.txt
Date: 26 October 2015
=======================

Description: 
This is a graphics rendering engine for creating 2D and 3D models. The library that is built here is similar to OpenGL library. 

Folder Structure:
/include : contains all the .h files
/lib     : contains all the .c files related to the .h files in /include
/src     : contains all the .c files used to model "demo.gif" 
/bin     : contains the executable files
/images  : contains all the .ppm images and .gif files that are created using this engine. (You will find the "demo.gif" here 				after runing the demo file) 


How to run the demo file:
*NOTE: For simplicity and better orgonization I have used GNU makefile for compiling 

1) Make the library files by navigating into /lib directory and typing "make" (The makefile is set up to compile all the
	library files)
2) Make the executable by navigating to /src directory and typing either "make" (will compile all demo files) or "make demo".
	There is only one demo file in this sample hence both "make" & "make demo" will do the same.
	The executable file can then be found in /bin directory.
3) Navigate to the /bin directory and run the executable file by typing "./demo".
4) After process is finished you will get the message "Finished Successfully :)". 
5) Navigate to /images directory. You will find the "demo.gif" animation file there. You may use your browsers (i.e.
	Firefox, Chrome, ...) to view the file.


About the Demo:
The demo.gif file illustrates some of the capabilities of this engine for creating 3D models. The "GRAPHICS" text shown in the demo
is built from letters that each represent a module and are theselves made from cubes. Each cube is made of 6 square surfaces that 
have only one side (light cannot pass through them!). Each square sides are made of Polygons that themselves are made out of 4 
Points. All such premetives are defined in the library files. This shows the capibility of the engine to 
incorporate modular design. As you can see from the demo different types of light (Ambient, Direct and Spotlight) are present as
well as shading (Phong Shading is used in the demo).

Extra Examples:
There are three more examples that are made with this engine:
"factorial.jpg"   : 2D demo
"tower.gif"       : 3D demo using unfilled polygons
"teapot_poly.gif" : 3D demo using bezier surfaces to create the Utah's teapot

