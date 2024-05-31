#ifndef CFINGER_H
#define CFINGER_H

/*****************************************************************************
 * Class CFinger
 *****************************************************************************/
class CFinger{
	double	x,y,z;
	double	zangle;
	double	length[3];
	double	radius[3];
	int		angle[3];
	float 	ambient[4], diffuse[4], specular[4], shininess;

public:
	CFinger();
	void	set(double x, double y, double z, double zangle,
							double length[], double radius[], int angle[]);
	void	rotateAngle(int mode, int fingerNo, int ang);
	void	draw();
};

#endif
