#pragma once

#ifndef __WATER__
#define __WATER__

#include "../Utilities/Math.h"

struct Water
{				
	int		ID;
	Vector3 color;
	float	fresnel_power;
	float	depth_ajust;
};

#endif