#ifndef GLOBAL_H
#define GLOBAL_H

extern "C" {
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
}

/*	Create checkerboard image	*/
#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];

extern void makeCheckImage();

#endif // GLOBAL_H
