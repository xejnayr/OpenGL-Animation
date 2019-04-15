#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "camera.h"
#include "polygon.h"

#ifndef _WIN32
#define __stdcall
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

int drawMode = 0;
float pitch, yaw = 0.0;
float sensitivity = 0.05;
int tick = 0;

bool timestop = false;
bool lights_on = true;
bool clipping = true;
bool window_lights_on = true;
bool world_light_on = true;
bool sunlight_on = true;

int windGen = 0;
bool windOn = false;
int windXDir = 0;
int windZDir = 0;
int snowTick = 0;

int window_width = 720;
int window_height = 720;

Camera camera;
//Cube sun(10,0,150,0,0.98,0.625,0.12,1);
GLfloat sphereRotation = 0.0;
GLfloat minuteHandRotation = 0.0;
GLfloat hourHandRotation = 0.0;

const int maxFlakes = 1500;
float snowLoc[4][maxFlakes] = {};
float snowflakeSize = 0;
float snowAccumulation = 0;

//polygon height, width, depth, x, y, z, r, g, b, a
Polygon clockTower(50,10,10,-80,0,5,1,1,1,1);
Polygon clockFace(8,1,8,-79.7,40,4,0,0,1,1);
Polygon minuteHand(3.8,1,0.8,-79.6,44,0.4,1,1,1,1);
Polygon hourHand(1.9,1,0.64,-79.2,44,0.32,1,0,1,1);

Polygon ground(200,200,200,100,-200,100,0.65,0.65,0.65,1);
Polygon house1(30,30,30,-65,0,-65,1,1,1,1);
Polygon house2(30,30,30,95,0,-65,0.8,0.8,0.8,1);
Polygon house3(30,30,30,-65,0,95,0.45,0.45,0.45,1);
Polygon house4(30,30,30,95,0,95,0.2,0.2,0.2,1);

Polygon h1window1(8,8,8,-64.7,5,-69,0.85,0.85,0.85,0);  //light1
Polygon h1window2(8,8,8,-64.7,5,-83, 0.7,0.7,0.7,0); 
Polygon h1window3(8,8,8,-64.7,17,-69,0.7,0.7,0.7,0);
Polygon h1window4(8,8,8,-64.7,17,-83,0.7,0.7,0.7,0);

Polygon h2window1(8,8,8,-64.7,5,91,0.7,0.7,0.7,0);
Polygon h2window2(8,8,8,-64.7,5,77,0.85,0.85,0.85,0);  //light2
Polygon h2window3(8,8,8,-64.7,17,91,0.7,0.7,0.7,0);
Polygon h2window4(8,8,8,-64.7,17,77,0.7,0.7,0.7,0);

Polygon h3window1(8,8,8,72.7,5,-69,0.7,0.7,0.7,0);
Polygon h3window2(8,8,8,72.7,5,-83,0.7,0.7,0.7,0);
Polygon h3window3(8,8,8,72.7,17,-69,0.85,0.85,0.85,0);  //light3
Polygon h3window4(8,8,8,72.7,17,-83,0.7,0.7,0.7,0);

Polygon h4window1(8,8,8,72.7,5,91,0.7,0.7,0.7,0);
Polygon h4window2(8,8,8,72.7,5,77,0.7,0.7,0.7,0);
Polygon h4window3(8,8,8,72.7,17,91,0.7,0.7,0.7,0);
Polygon h4window4(8,8,8,72.7,17,77,0.85,0.85,0.85,0); //light4


Polygon collision_shapes[] =
{ground, house1, house2, house3, house4,
h1window2, h1window3, h1window4, h2window1,
h2window3, h2window4, h3window1, h3window2,
h3window4, h4window1, h4window2, h4window3,
clockTower, clockFace};
	
Polygon lights[] = 
{h1window1, h2window2, h3window3, h4window4};


double oldx = camera.eyex;
double oldy = camera.eyey;
double oldz = camera.eyez;


//GLfloat light1_diffuse[] = { 0.98,0.625,0.12, 1.0 };

GLfloat window_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat window_diffuse[] = { 0.2f,0.08f,0.016f,1.0};
GLfloat window_specular[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat window_light_pos[] = {-64.6,5,-83,1};
GLfloat spot_dir[] = {1.0, -1.0, 0.0 };

GLfloat window_light_pos2[] = {-64.6,5,77,1};
GLfloat spot_dir2[] = {1,-1,0};

GLfloat window_light_pos3[] = {64.6,24,-69,1};
GLfloat spot_dir3[] = {-1,-1,0};

GLfloat window_light_pos4[] = {64.6,24,77,1};
GLfloat spot_dir4[] = {-1.0, -1.0, 0.0 };

GLfloat world_light_pos[] = {1.0f, 1.0f, 1.0f, 0.0f};
GLfloat sphere_light_pos[] = {0,150,0,0};

//Sphere light value
GLfloat sphere_diffuse[] = {0.35,0.35,0.5,1.0};

//GLfloat sky_color[] = {0.0,0.05,0.15};
GLfloat sky_color[] = {0.0,0.2,0.6};

void drawAccumulatedSnow(){
	glPushMatrix();
		glBegin(GL_TRIANGLES);
		glColor4f(1,1,1,1);
			glNormal3f(-1,-1,-1); //bottom of snow layer
			glVertex3f(-100,0.1,-100);
			glNormal3f(-1,-1,1);
			glVertex3f(-100,0.1,100);
			glNormal3f(1,-1,1);
			glVertex3f(100,0.1,100);
			glNormal3f(-1,-1,-1);
			glVertex3f(-100,0.1,-100);
			glNormal3f(1,-1,-1);
			glVertex3f(100,0.1,-100);
			glNormal3f(1,-1,1);
			glVertex3f(100,0.1,100);
			glNormal3f(-1,-1,-1); //left side of snow layer
			glVertex3f(-100,0.1,-100);
			glNormal3f(-1,1,-1);
			glVertex3f(-100,snowAccumulation,-100);
			glNormal3f(-1,-1,1);
			glVertex3f(-100,0.1,100);
			glNormal3f(-1,1,-1);
			glVertex3f(-100,snowAccumulation,-100);
			glNormal3f(-1,-1,1);
			glVertex3f(-100,0.1,100);
			glNormal3f(-1,1,1);
			glVertex3f(-100,snowAccumulation,100);
			glNormal3f(1,-1,-1); //right side of snow layer
			glVertex3f(100,0.1,-100);
			glNormal3f(1,1,-1);
			glVertex3f(100,snowAccumulation,-100);
			glNormal3f(1,-1,1);
			glVertex3f(100,0.1,100);
			glNormal3f(1,1,-1);
			glVertex3f(100,snowAccumulation,-100);
			glNormal3f(1,-1,1);
			glVertex3f(100,0.1,100);
			glNormal3f(1,1,1);
			glVertex3f(100,snowAccumulation,100);
			glNormal3f(1,-1,-1); //front side of snow layer
			glVertex3f(100,0.1,-100);
			glNormal3f(1,1,-1);
			glVertex3f(100,snowAccumulation,-100);
			glNormal3f(-1,-1,-1);
			glVertex3f(-100,0.1,-100);
			glNormal3f(1,1,-1);
			glVertex3f(100,snowAccumulation,-100);
			glNormal3f(-1,1,-1);
			glVertex3f(-100,snowAccumulation,-100);
			glNormal3f(-1,-1,-1);
			glVertex3f(-100,0.1,-100);
			glNormal3f(1,-1,1); //back side of snow layer
			glVertex3f(100,0.1,100);
			glNormal3f(1,1,1);
			glVertex3f(100,snowAccumulation,100);
			glNormal3f(-1,-1,1);
			glVertex3f(-100,0.1,100);
			glNormal3f(1,1,1);
			glVertex3f(100,snowAccumulation,100);
			glNormal3f(-1,1,1);
			glVertex3f(-100,snowAccumulation,100);
			glNormal3f(-1,-1,1);
			glVertex3f(-100,0.1,100);
			glNormal3f(-1,1,-1); //top of snow layer
			glVertex3f(-100,snowAccumulation,-100);
			glNormal3f(-1,1,1);
			glVertex3f(-100,snowAccumulation,100);
			glNormal3f(1,1,1);
			glVertex3f(100,snowAccumulation,100);
			glNormal3f(-1,1,-1);
			glVertex3f(-100,snowAccumulation,-100);
			glNormal3f(1,1,-1);
			glVertex3f(100,snowAccumulation,-100);
			glNormal3f(1,1,1);
			glVertex3f(100,snowAccumulation,100);
		glEnd();
	glPopMatrix();
}

void randomizeSnow(){
	for(int i = 0; i < maxFlakes; i++){
		snowLoc[0][i] = (rand() % 400) - 200;
		snowLoc[1][i] = rand() % 200;
		snowLoc[2][i] = (rand() % 400) - 200;
		snowLoc[3][i] = 0.75 / (rand() % 10 + 1);
	}
}

void drawSnow(){
	
	
	/* Thought about including wind to blow snowflakes around
	 * Having too many flakes lags the program a lot (of course)
	 * And the snowfall immediately after the wind is weird
	 * So probably not going to include it
	windGen = (rand() % 4);
	if(snowTick < 600){
		windOn = false;
	}
	if(snowTick >= 600 && snowTick <= 690){
		std::cout<<"Wind blowing"<<std::endl;
		windOn = true;
		if(windGen = 0){
			windXDir = 1;
			windZDir = 1;
		}
		if(windGen = 1){
			windXDir = -1;
			windZDir = 1;
		}
		if(windGen = 2){
			windXDir = -1;
			windZDir = -1;
		}
		if(windGen = 3){
			windXDir = 1;
			windZDir = -1;
		}
	}
	if(snowTick > 690){
		//std::cout<<"Resetting snowTick"<<std::endl;
		windXDir = 0;
		windZDir = 0;
		snowTick = 0;
	}
	*/
	
	for(int i = 0; i < maxFlakes; i++){
		glPushMatrix();
			glTranslatef(snowLoc[0][i], snowLoc[1][i], snowLoc[2][i]);
			glutSolidSphere(snowLoc[3][i],10,10);
			if(not timestop){
				snowLoc[0][i] -= 0.5 * windXDir;
				snowLoc[1][i] -= 0.5;
				snowLoc[2][i] -= 0.5 * windZDir;
			}
			if(snowLoc[1][i] <= 0){
				snowLoc[0][i] = (rand() % 200) - 100;
				snowLoc[1][i] = 200;
				snowLoc[2][i] = (rand() % 200) - 100;
				snowLoc[3][i] = 0.75 / (rand() % 10 + 1);
				snowAccumulation += 0.001;
			}
		glPopMatrix();
	}
	//snowTick++;
}

void drawSphere(){
	glTranslatef(0,150,0);
	
	//  http://glprogramming.com/red/chapter05.html
	//  Need two sets of Push/PopMatrix to move the light with the sphere
	glPushMatrix();
		
		glPushMatrix();
			glTranslatef(0, -150, 0);
			glRotatef(sphereRotation,1,0,0);
			glTranslatef(0, 150, 0);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, sphere_diffuse);
			glLightfv(GL_LIGHT5, GL_POSITION, sphere_light_pos);
			glColor4f(1,0,0,1);
			glutSolidSphere (10, 40, 40);
		glPopMatrix();
		
	glPopMatrix();
	
	if((sphereRotation >= 90) && (sphereRotation < 270) && not timestop){
		sky_color[1] = sky_color[1] - (0.000416667 * 2);
		sky_color[2] = sky_color[2] - (0.00125 * 2);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		window_lights_on = true;
		//std::cout<<sky_color[1]<<" "<<sky_color[2]<<std::endl;
	} else {
		if(sphereRotation >= 270){
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
		}
		window_lights_on = false;
		if(not timestop){
			sky_color[1] = sky_color[1] + (0.000416667 * 2);
			sky_color[2] = sky_color[2] + (0.00125 * 2);
		}
		//std::cout<<sky_color[1]<<" "<<sky_color[2]<<std::endl;
	}
	
	
	
	glClearColor(sky_color[0],sky_color[1],sky_color[2],1);
	
	if(not timestop){
		sphereRotation += 0.1;
	}
	minuteHandRotation = sphereRotation * 24;
	hourHandRotation = sphereRotation * 2;
	
	if(sphereRotation == 360){
		sphereRotation = 0;
		minuteHandRotation = 0;
		hourHandRotation = 0;
	}
}

void drawLights() {
	//Display world lighting
	
	//glLightfv(GL_LIGHT0, GL_POSITION, world_light_pos);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, window_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, window_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, window_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, window_light_pos);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, window_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, window_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, window_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, window_light_pos2);
	
	glLightfv(GL_LIGHT3, GL_AMBIENT, window_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, window_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, window_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, window_light_pos3);
	
	glLightfv(GL_LIGHT4, GL_AMBIENT, window_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, window_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, window_specular);
	glLightfv(GL_LIGHT4, GL_POSITION, window_light_pos4);
}

void generateView(){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	clockTower.drawPolygon();
	drawLights();
	drawSphere();
	glLoadIdentity();
	
	
	
	//gluLookAt - sets camera values
	gluLookAt(camera.eyex, camera.eyey, camera.eyez,
	camera.centerx, camera.centery, camera.centerz,
	camera.upx, camera.upy, camera.upz);
	
	
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		collision_shapes[i].drawPolygon();
	}
	for(int i = 0; i < (sizeof(lights) / sizeof(lights[0])); i++){
		lights[i].drawPolygon();
	}
	
	
	glPushMatrix();
	glTranslatef(hourHand.transX, hourHand.transY, hourHand.transZ);
	glTranslatef(0,0,-0.32);
	glRotatef(hourHandRotation, -1, 0, 0);
	//glTranslatef(hourHand.transX * -1, hourHand.transY * -1, hourHand.transZ * -1);
	glTranslatef(0,0,0.32);
	hourHand.drawHand();
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(minuteHand.transX, minuteHand.transY, minuteHand.transZ);
	glTranslatef(0,0,-0.4);
	glRotatef(minuteHandRotation, -1, 0, 0);
	glTranslatef(0,0,0.4);
	minuteHand.drawHand();
	glPopMatrix();
	
	
	/* Testing things -- can draw multiple instances of same object
	glPushMatrix();
	glTranslatef(10,10,10);
	minuteHand.drawHand();
	glPopMatrix();
	*/
	
	drawSnow();
	drawAccumulatedSnow();
	
	
	glEnd();
	glutSwapBuffers();
}

/*
 * General collision note - collision is checked before movement.
 * If I would collide with something by making a move, then the move is not made.
 * Check this by performing the move calculations, then seeing whether the
 * result is inside of an object.
 */
bool checkCenterCollision(Polygon cube){
	//Check if the area that the camera is looking at is colliding with anything
	bool colliding = false;
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if((camera.centerx > cube.xmin && camera.centerx < cube.xmax &&
			camera.centery > cube.ymin && camera.centery < cube.ymax &&
			camera.centerz > cube.zmin && camera.centerz < cube.zmax)){
			colliding = true;
		}
	}
	return colliding;
}

bool checkEyeCollision(Polygon cube){
	//Check if the camera itself is colliding with anything
	bool colliding = false;
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if((camera.eyex > cube.xmin && camera.eyex < cube.xmax &&
			camera.eyey > cube.ymin && camera.eyey < cube.ymax &&
			camera.eyez > cube.zmin && camera.eyez < cube.zmax)){
			colliding = true;
		}
	}
	return colliding;
}

bool checkForwardCollision(Polygon cube[]){
	bool colliding = false;
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if((checkCenterCollision(cube[i])) && (checkEyeCollision(cube[i]))){
			colliding = true;
		}
	}
	return colliding;
}

bool checkBackwardCollision(Polygon cube[]){
	bool colliding = false;
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if(
		((2 * camera.eyex - camera.centerx) > (cube[i].xmin)) &&
		((2 * camera.eyex - camera.centerx) < (cube[i].xmax)) &&
		((2 * camera.eyey - camera.centery) > (cube[i].ymin)) &&
		((2 * camera.eyey - camera.centery) < (cube[i].ymax)) &&
		((2 * camera.eyez - camera.centerz) > (cube[i].zmin)) &&
		((2 * camera.eyez - camera.centerz) < (cube[i].zmax))
		){
			colliding = true;
		}
	}
	return colliding;
}

bool checkLeftCollision(Polygon cube[]){
	bool colliding = false;
	camera.updateDeltas(camera.deltax, camera.deltaz);
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if((fmod(abs(yaw), 360)) >= 0 && (fmod(abs(yaw), 360) <= 180) && yaw >= 0){
			if( //check y values here too
			(camera.eyex + (-1 * camera.deltax * camera.speed) > (cube[i].xmin)) &&
			(camera.eyex + (-1 * camera.deltax * camera.speed) < (cube[i].xmax)) &&
			(camera.eyez + (-1 * camera.deltaz * camera.speed) > (cube[i].zmin)) &&
			(camera.eyez + (-1 * camera.deltaz * camera.speed) < (cube[i].zmax)) &&
			(camera.eyey > cube[i].ymin && camera.eyey < cube[i].ymax)
			){
				colliding = true;
			}
		} else {
			if(
			(camera.eyex - (-1 * camera.deltax * camera.speed) > (cube[i].xmin)) &&
			(camera.eyex - (-1 * camera.deltax * camera.speed) < (cube[i].xmax)) &&
			(camera.eyez - (-1 * camera.deltaz * camera.speed) > (cube[i].zmin)) &&
			(camera.eyez - (-1 * camera.deltaz * camera.speed) < (cube[i].zmax)) &&
			(camera.eyey > cube[i].ymin && camera.eyey < cube[i].ymax)
			){
				colliding = true;
			}
		}
	}
	//std::cout<<"Collision: "<<colliding<<" yaw: "<<yaw<<std::endl;
	return colliding;
}

bool checkRightCollision(Polygon cube[]){
	bool colliding = false;
	camera.updateDeltas(camera.deltax, camera.deltaz);
	for(int i = 0; i < (sizeof(collision_shapes) / sizeof(collision_shapes[0])); i++){
		if((fmod(abs(yaw), 360)) >= 0 && (fmod(abs(yaw), 360) <= 180) && yaw >= 0){
			if(
			(camera.eyex + (camera.deltax * camera.speed) > (cube[i].xmin)) &&
			(camera.eyex + (camera.deltax * camera.speed) < (cube[i].xmax)) &&
			(camera.eyez + (camera.deltaz * camera.speed) > (cube[i].zmin)) &&
			(camera.eyez + (camera.deltaz * camera.speed) < (cube[i].zmax)) &&
			(camera.eyey > cube[i].ymin && camera.eyey < cube[i].ymax)
			){
				colliding = true;
			}
		} else {
			if(
			(camera.eyex - (camera.deltax * camera.speed) > (cube[i].xmin)) &&
			(camera.eyex - (camera.deltax * camera.speed) < (cube[i].xmax)) &&
			(camera.eyez - (camera.deltaz * camera.speed) > (cube[i].zmin)) &&
			(camera.eyez - (camera.deltaz * camera.speed) < (cube[i].zmax)) &&
			(camera.eyey > cube[i].ymin && camera.eyey < cube[i].ymax)
			){
				colliding = true;
			}
		}
	}
	//std::cout<<"Collision: "<<colliding<<" yaw: "<<yaw<<std::endl;
	return colliding;
}

void mouseMove(int x, int y){
	//moving left/right - adjust centerx and centery
	//moving up/down - adjust centerz
	

	double mousex = x - 360;
	double mousey = 360 - y;

	yaw += mousex * sensitivity;
	pitch += mousey * sensitivity;
	
	//make sure yaw is between 0 and 360 at all times
	if(yaw >= 360){
		yaw -= 360;
	}
	if(yaw <= 0){
		yaw += 360;
	}
	
	//Clamp to looking straight up or straight down at most
	if(pitch > 89.0f){
		pitch = 89.0f;
	}
	if(pitch < -89.0f){
		pitch = -89.0f;
	}
	
	//keeps pointer at the center of the screen, as a game would
	//works well with hiding the cursor, also as a game would (usually)
	if(tick % 10 == 0){
		glutWarpPointer(window_width / 2, window_width / 2);
		//for some reason there's a problem here when I set window width higher
	}
	if(tick % 120 == 0){ 
		tick = 0; 
	}
	tick++; 
}

void keyPressed(unsigned char key, int x, int y){
	switch(key){
		case 27:
			glutDestroyWindow(glutGetWindow());
			break;
		case 'w':
			oldx = camera.eyex;
			oldy = camera.eyey;
			oldz = camera.eyez;
			if(not checkForwardCollision(collision_shapes) || not clipping){
				camera.moveForward();
			}
			break;
		case 's':
			if(not checkBackwardCollision(collision_shapes) || not clipping){
				camera.moveBackward();
			}
			break;
		case 'd':
			if
			(not checkRightCollision(collision_shapes) || not clipping){
				camera.updateDeltas(camera.deltax, camera.deltaz);
				camera.strafeRight(pitch, yaw);
			}
			break;
		case 'a':
			if
			(not checkLeftCollision(collision_shapes) || not clipping){
				camera.updateDeltas(camera.deltax, camera.deltaz);
				camera.strafeLeft(pitch, yaw);
			}
			break;
		case ' ':
			//Defaults to a normal view. 
			//Pressing space switches to wireframe mode.
			//Pressing space again breaks everything for some reason.
			drawMode = ++drawMode % 3;
			if(drawMode == 0) { // fill mode
			
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_CULL_FACE);
			}
			else if(drawMode == 1) { // wireframe mode
			
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_CULL_FACE);
			}
			else if(drawMode == 2) { // point mode
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_CULL_FACE);
			}
			//std::cout<<drawMode<<std::endl;
			break;
		case 't':
			//Printing camera coordinates and yaw for debug purposes
			std::cout<<"centerx: "<<camera.centerx<<" centery: "<<camera.centery<<" centerz: "<<camera.centerz<<std::endl;
			std::cout<<"eyex: "<<camera.eyex<<" eyey: "<<camera.eyey<<" eyez: "<<camera.eyez<<std::endl;
			std::cout<<"yaw: "<<yaw<<std::endl;
			break;
		case '+':
			if(camera.speed < 2){
				camera.speed += 0.05;
			}
			break;
		case '-':
			if(camera.speed > 0.5){
				camera.speed -= 0.05;
			}
			break;
		case 'l':
			//Turns off lighting altogether
			if(lights_on){
				lights_on = false;
				glDisable(GL_LIGHTING);
			}
			else{
				lights_on = true;
				glEnable(GL_LIGHTING);
			}
			std::cout<<lights_on<<std::endl;
			break;
		case 'c':
			//Switches clipping state, allow user to phase through buildings
			if(clipping){
				clipping = false;
			} else {
				clipping = true;
			}
			//std::cout<<"Clipping: "<<clipping<<std::endl;
			break;
		case '1':
			//Pressing 1 disables the overworld lighting (Sun/Moonlight)
			if(world_light_on){
				glDisable(GL_LIGHT5);
				world_light_on = false;
			} else {
				glEnable(GL_LIGHT5);
				world_light_on = true;
			}
			std::cout<<"World light: "<<world_light_on<<" "<<"Window lights: "<<window_lights_on<<std::endl;
			break;
		case '2':
			//Pressing 2 disables window lights
			if(window_lights_on){
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHT4);
				window_lights_on = false;
			} else {
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
				glEnable(GL_LIGHT4);
				window_lights_on = true;
			}
			std::cout<<"World light: "<<world_light_on<<" "<<"Window lights: "<<window_lights_on<<std::endl;
			break;
		case 'f':
			timestop = not timestop;
			break;
	}
	
	
}

void reshape(GLsizei width, GLsizei height){
	if(height == 0){
		height = 1;
	}
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	std::cout<<"Reshape function called. Width: "<<width<<" "<<"Height: "<<height<<std::endl;
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, aspect, 0.1f, 500.0f);
}

void idleFunction(){
	
	//std::cout<<"Yaw: "<<yaw<<std::endl;
	
	//dir variables say whether left is positive or negative
	if(camera.centerx - camera.eyex <= 0){
		camera.zdir = 1;
	} else {
		camera.zdir = -1;
	}
	if(camera.centerz - camera.eyez <= 0){
		camera.xdir = 1;
	} else {
		camera.xdir = -1;
	}
	
	//2I - P = B
	//I = initial point, P = looking at, B = backwards
	
	camera.centerx = cos(yaw * M_PI / 180) * cos(pitch * M_PI / 180) + camera.eyex;
	camera.centery = sin(pitch * M_PI / 180) + camera.eyey;
	camera.centerz = sin(yaw * M_PI / 180) * cos(pitch * M_PI / 180) + camera.eyez;


	generateView();
}

void initLighting(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5); //sun
    
    
	//enabling blending for good effects
	glEnable(GL_BLEND); //need these for blending and shading
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA); //maybe change src to color
	glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL); //not sure why this
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {
	randomizeSnow();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Animation");
	glutSetCursor(GLUT_CURSOR_NONE);
	glutKeyboardFunc(keyPressed);
	glutPassiveMotionFunc(mouseMove);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutDisplayFunc(generateView);
	
	initLighting();
	glutReshapeFunc(reshape);
	glutIdleFunc(idleFunction);
	glutMainLoop();
	return 0;
}
