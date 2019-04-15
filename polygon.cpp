#include <GL/glut.h>
#include <cmath>
#include "polygon.h"

Polygon::Polygon(GLdouble height, GLdouble width, GLdouble depth, GLdouble tx, GLdouble ty, GLdouble tz, GLdouble ir, GLdouble ig, GLdouble ib, GLdouble ia){
	//use size to determine position of points in vector space
	//working in modelview, so points are relative
	//this is a cube so all edges will be the same length (hopefully)
	
	//tx, ty, tz, ir, ig, and ib are input values for class variables
	
	points[0][0] = 0;
	points[0][1] = 0;
	points[0][2] = 0;
	
	points[1][0] = -1 * width;
	points[1][1] = 0;
	points[1][2] = 0;
	
	points[2][0] = -1 * width;
	points[2][1] = 0;
	points[2][2] = -1 * depth;
	
	points[3][0] = 0;
	points[3][1] = 0;
	points[3][2] = -1 * depth;
	
	points[4][0] = 0;
	points[4][1] = height;
	points[4][2] = 0;
	
	points[5][0] = -1 * width;
	points[5][1] = height;
	points[5][2] = 0;
	
	points[6][0] = -1 * width;
	points[6][1] = height;
	points[6][2] = -1 * depth;
	
	points[7][0] = 0;
	points[7][1] = height;
	points[7][2] = -1 * depth;
	
	transX = tx;
	transY = ty;
	transZ = tz;
	
	r = ir;
	g = ig;
	b = ib;
	a = ia;
	
	xmin = (points[1][0] + transX) - 1;
	ymin = transY - 1;
	zmin = (points[7][2] + transZ) - 1; 
	xmax = transX + 1; 
	ymax = (points[4][1] + transY) + 1; 
	zmax = transZ + 1; 
}

void Polygon::drawPolygon(){
	glPushMatrix();
	glTranslatef(transX, transY, transZ);
	
	
	//Draw the polygon here
	//Begins at forward upper right corner
	glBegin(GL_TRIANGLES); 
		glColor4f(r, g, b, 1.0); //top
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
		glColor4f(r, g, b, 1.0); //right
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
		glColor4f(r, g, b, 1.0); //front
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
		glColor4f(r, g, b, 1.0); //bottom
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
		glColor4f(r, g, b, 1.0); //left
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
		glColor4f(r, g, b, 1.0); //back
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
	glEnd();
	glPopMatrix();
}

void Polygon::drawHand(){
	//Draw the polygon here
	//Begins at forward upper right corner
	glBegin(GL_TRIANGLES); 
		glColor4f(r, g, b, 1.0); //top
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
		glColor4f(r, g, b, 1.0); //right
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
		glColor4f(r, g, b, 1.0); //front
			glNormal3f(1,1,-1);
			glVertex3f(points[7][0], points[7][1], points[7][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
		glColor4f(r, g, b, 1.0); //bottom
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(1,-1,-1);
			glVertex3f(points[3][0], points[3][1], points[3][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
		glColor4f(r, g, b, 1.0); //left
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,-1);
			glVertex3f(points[6][0], points[6][1], points[6][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,-1,-1);
			glVertex3f(points[2][0], points[2][1], points[2][2]);
		glColor4f(r, g, b, 1.0); //back
			glNormal3f(-1,1,1);
			glVertex3f(points[5][0], points[5][1], points[5][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
			glNormal3f(1,-1,1);
			glVertex3f(points[0][0], points[0][1], points[0][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[1][0], points[1][1], points[1][2]);
			glNormal3f(-1,1,1);
			glVertex3f(points[4][0], points[4][1], points[4][2]);
	glEnd();
}
