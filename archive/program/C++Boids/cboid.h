#ifndef __CBOID_H
#define __CBOID_H

class CBoid
{
  static GLfloat sMaterialBody[4];
  static GLfloat sMaterialFin[4];
  static const double kSight = .9;     // radius of sight
  static const double kFrontCos = -.9; // lower bound of cosine of the 'front'
  static const double kDt = 1.0/30;    // step time
  static const double kGain1 = 1;      // separation gain
  static const double kGain2 = 4;      // alignment gain
  static const double kGain3 = 5;      // cohesion gain
  static const double kGainFv = .5;    // viscous friction coefficient
  static const double kM = 1;          // mass

  int     counter;     // general counter for miscellaneous use
  double  finAngle;    // angle of tail fin
  double  x, y, z;     // position
  double  vx, vy, vz;  // velocity
public:
  CBoid();
  void setPosition(double aX, double aY, double aZ);
  void setVelocity(double aVx, double aVy, double aVz);
  double getX(){ return x; };
  double getY(){ return y; };
  double getZ(){ return z; };
  double getVx(){ return vx; };
  double getVy(){ return vy; };
  double getVz(){ return vz; };
  double distanceFrom(double aX, double aY, double aZ);
  double distanceFrom(CBoid *comrade);
  double cosineTo(double aX, double aY, double aZ);
  double cosineTo(CBoid *comrade);
  void draw();
  void rotate();
  void translate();
  void act(CBoid **comrades);
};
#endif // __CBOID_H
