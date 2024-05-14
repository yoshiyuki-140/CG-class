#include "CFinger.h"

#ifndef CHAND_H
#define CHAND_H

/****************************************************************************
 * Class CHand
 ****************************************************************************/
class CHand {
/* 	the number of vertex of hand model	*/
	static	const int Hand_Points = 9;
/* dimensions for xyz-coordinates	*/
	static	const int Hand_Points_XYZ = 3;
	double	pnt[Hand_Points][Hand_Points_XYZ], thickness;
public:
	CFinger	*finger[5];
	CHand();
	void draw();
};

#endif   // CHAND_H
