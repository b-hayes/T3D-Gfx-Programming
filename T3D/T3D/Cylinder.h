#pragma once


#ifndef CYLINDER_H
#define CYLINDER_H

#include "mesh.h"

namespace T3D
{
	class Cylinder :
		public Mesh
	{
	public:
		Cylinder(float radius, float height, int density);
		virtual ~Cylinder (void);
	};
}

#endif