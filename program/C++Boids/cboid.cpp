#include <GL/glut.h>
#include <iostream>
#include "cboid.h"

extern const double kRoomW;
extern const double kRoomH;
extern const double kRoomD;

using namespace std;

GLfloat CBoid::sMaterialBody[] = {0, 1, .3, 1};
GLfloat CBoid::sMaterialFin[] = {.5, 0, .5, 1};

CBoid::CBoid()
	:x(0), y(0), z(0), vx(0), vy(0), vz(0), finAngle(0), counter(0)
{
}

void CBoid::setPosition(double aX, double aY, double aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

void CBoid::setVelocity(double aVx, double aVy, double aVz)
{
	vx = aVx;
	vy = aVy;
	vz = aVz;
}

/* drawing itself on the origin */
void CBoid::draw()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sMaterialBody);
	glScalef(.5, 1, 1);
/* torso */
	glRotatef(180,1,0,0);
	glutSolidCone(.1, .01, 10, 10);
	glRotatef(180,1,0,0);
	glutSolidCone(.1, .1, 10, 10);
/* tail fin */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sMaterialFin);
	glRotatef(finAngle, 0, 1, 0);  // move the fin
	glTranslatef(0, 0, -.06);
	glScalef(.25, 1, 1);
	glutSolidCone(.04, .1, 10, 10);
}

/* 
 * heading toward the same direction as velocity.
 * (should be called prior to draw().)
 */
void CBoid::rotate(){
	double p = atan2(vy, sqrt(vx*vx + vz*vz));
	double q = atan2(vx, vz);
	glRotatef( q * 180 / M_PI, 0, 1, 0);
	glRotatef(-p * 180 / M_PI, 1, 0, 0);
}

/*
 * move itself to the position (x, y, z).
 * (sould be called prior to rotate().
 */
void CBoid::translate()
{
	glTranslatef(x, y, z);
}

/* 
 * making the next action.
 * The argument is an array of pointers to boids, which ends with 'null'.
 */
void CBoid::act(CBoid **comrades)
{
	int    numBoids = 0;      				// # of boids in its sight
	double fx = 0, fy = 0, fz = 0;
	double gx = 0, gy = 0, gz = 0;			// C.O.G. of boids in its sight

	for(CBoid **theComrade = comrades; *theComrade; theComrade++){
		double d = distanceFrom(*theComrade);
		double c = cosineTo(*theComrade);
		if(*theComrade == this) continue;  // Is this me?  Then, ignore.
		if(d > kSight) continue;           // out of sight?
		if(c < kFrontCos) continue;        // behind me?
		fx -= kGain1 * ((*theComrade)->getX() - x) / d / d;
		fy -= kGain1 * ((*theComrade)->getY() - y) / d / d;
		fz -= kGain1 * ((*theComrade)->getZ() - z) / d / d;
		fx += kGain2 * ((*theComrade)->getVx() - vx);
		fy += kGain2 * ((*theComrade)->getVy() - vy);
		fz += kGain2 * ((*theComrade)->getVz() - vz);
		gx += (*theComrade)->getX();
		gy += (*theComrade)->getY();
		gz += (*theComrade)->getZ();
		numBoids++;
	}
	if(numBoids){      					// Is there any comrade in my sight?
		double dgx = gx / numBoids - x;
		double dgy = gy / numBoids - y;
		double dgz = gz / numBoids - z;
		double dg = sqrt(dgx * dgx + dgy * dgy + dgz * dgz);
		fx += kGain3 * dgx / dg;
		fy += kGain3 * dgy / dg;
		fz += kGain3 * dgz / dg;
	}
	// viscous friction
	fx -= kGainFv * vx;
	fy -= kGainFv * vy;
	fz -= kGainFv * vz;
/* speed up if too slow */
	if(vx*vx + vy*vy + vz*vz < .1){
		fx += vx;
		fy += vy;
		fz += vz;
	}
	x += vx * kDt;
	y += vy * kDt;
	z += vz * kDt;
	vx += fx / kM * kDt;
	vy += fy / kM * kDt;
	vz += fz / kM * kDt;
/* The Universe is closed! */
	if(x > kRoomW/2) x -= kRoomW;
	if(y > kRoomH/2) y -= kRoomH;
	if(z > kRoomD/2) z -= kRoomD;
	if(x < -kRoomW/2) x += kRoomW;
	if(y < -kRoomH/2) y += kRoomH;
	if(z < -kRoomD/2) z += kRoomD;

	counter += (int)(200*sqrt(vx * vx + vy * vy + vz * vz) * kDt);
	finAngle = sin(counter*.1)*50;
}

double CBoid::distanceFrom(double aX, double aY, double aZ)
{
	double dx = x - aX;
	double dy = y - aY;
	double dz = z - aZ;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double CBoid::distanceFrom(CBoid *comrade)
{
	return distanceFrom(comrade->getX(), comrade->getY(), comrade->getZ());
}

double CBoid::cosineTo(double aX, double aY, double aZ)
{
	double v = sqrt(vx*vx + vy*vy + vz*vz);
	double d = distanceFrom(aX, aY, aZ);
	return ((x-aX)*vx + (y-aY)*vy + (z-aZ)*vz) / v / d;
}

double CBoid::cosineTo(CBoid *comrade)
{
	return cosineTo(comrade->getX(), comrade->getY(), comrade->getZ());
}
