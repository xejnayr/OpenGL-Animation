//Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <cmath>

//camera class - controls the camera position and view point
class Camera {
	public: 
		double eyex, eyey, eyez;
		double centerx, centery, centerz;
		double upx, upy, upz;
		double centerholdx,eyeholdx,centerholdz,eyeholdz;
		double deltax, deltaz;
		double speed;
		int xdir, zdir;
		//double pitch, yaw;
		
		Camera();
		void moveForward();
		void moveBackward();
		void updateDeltas(double, double);
		void strafeLeft(float, float);
		void strafeRight(float, float);
};
#endif
