#include <GL/glut.h>
#include <cmath>
#include "camera.h"

Camera::Camera(){
	//initial camera values
	eyex = 0;
	eyey = 5;
	eyez = 1;
	centerx = 0;
	centery = 0;
	centerz = 1;
	upx = 0;
	upy = 1;
	upz = 0;
	centerholdx = 0;
	eyeholdx = 0;
	centerholdz = 0;
	eyeholdz = 0;
	xdir = -1;
	zdir = 1;
	deltax = 0.0;
	deltaz = 0.0;
	speed = 0.5;
}

void Camera::moveForward(){
	//make old view point the new camera point
	eyex = centerx;
	centerx = centerx;
	eyey = centery;
	centery = centery;
	eyez = centerz;
	centerz = centerz;
}

void Camera::moveBackward(){
	//2 * point that you're currently at - point that you're looking at
	eyex = 2 * eyex - centerx;
	centerx = 2 * eyex - centerx;
	eyey = 2 * eyey - centery;
	centery = 2 * eyey - centery;
	eyez = 2 * eyez - centerz;
	centerz = 2 * eyez - centerz;
}

void Camera::updateDeltas(double dx, double dz){
	//voodoo math
	deltaz = (centerx - eyex) / (centerz - eyez);
	deltax = -1 / sqrt(1 + deltaz * deltaz);
	deltaz = deltaz / sqrt(1 + deltaz * deltaz);
}

void Camera::strafeLeft(float pitch, float yaw){
	//updateDeltas(deltax, deltaz);
	//std::cout<<"fmod(abs(yaw), 360: "<<fmod(abs(yaw), 360)<<std::endl;
	if((fmod(abs(yaw), 360)) >= 0 && (fmod(abs(yaw), 360) <= 180) && yaw >= 0){
	//if(true){ //I don't think the above is necessary, so testing it with this
		eyex += deltax * -1 * speed;
		eyez += deltaz * -1 * speed;
		centerx += deltax * -1 * speed;
		centerz += deltaz * -1 * speed;
	} else {
		eyex -= deltax * -1 * speed;
		eyez -= deltaz * -1 * speed;
		centerx -= deltax * -1 * speed;
		centerz -= deltaz * -1 * speed;
	}
}

void Camera::strafeRight(float pitch, float yaw){
	//updateDeltas(deltax, deltaz);
	if((fmod(abs(yaw), 360)) >= 0 && (fmod(abs(yaw), 360) <= 180) && yaw >= 0){
	//if(true){
		eyex += deltax * speed;
		eyez += deltaz * speed;
		centerx += deltax * speed;
		centerz += deltaz * speed;
	} else {
		eyex -= deltax * speed;
		eyez -= deltaz * speed;
		centerx -= deltax * speed;
		centerz -= deltaz * speed;
	}
}
