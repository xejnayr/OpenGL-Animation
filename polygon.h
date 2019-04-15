//polygon.h
#ifndef POLYGON_H
#define POLYGON_H

#include <GL/glut.h>

//polygon class, so I can have shapes that aren't cubes
class Polygon {
	public:
		GLdouble points[8][3];
		GLdouble xmax;
		GLdouble ymax;
		GLdouble zmax;
		GLdouble xmin;
		GLdouble ymin;
		GLdouble zmin;
		GLdouble transX;
		GLdouble transY;
		GLdouble transZ;
		GLdouble r;
		GLdouble g;
		GLdouble b;
		GLdouble a;
		
		Polygon(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
		void drawPolygon();
		void drawHand();
};
#endif

