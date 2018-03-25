#pragma once
#include "gameobject.h"
#include "SweepPath.h"

// don't forget to include theses, either here or in lamp.cpp
#include "Cylinder.h"
#include "DrawTask.h"

namespace T3D {

	class Lamp : public GameObject
	{
	public:
		Lamp(T3DApplication *app);
		~Lamp(void);

		GameObject *base;
		GameObject *arm1;
		GameObject *arm2;
		GameObject *baseJoint;
		GameObject *elbowJoint;
		GameObject *shadeJoint;
	};

}