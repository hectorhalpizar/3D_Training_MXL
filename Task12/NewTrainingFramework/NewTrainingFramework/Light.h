#pragma once
#ifndef __LIGHT__
#define __LIGHT__


#include "../Utilities/Math.h"
struct LightConst
{
	Vector3 ambientColor;
	float	ambientWeight;
};

struct Light
{				
	int		ID;
	int		light_type;
	int		move_type;
	float	radius;
	float	speed;
	Vector3 pos_dir;
	Vector3 color;
	float	specularPower;
};
#endif