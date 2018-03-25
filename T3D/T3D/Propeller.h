#pragma once
#include "mesh.h"

namespace T3D
{
	class Propeller :
		public Mesh
	{
	public:
		Propeller(
			float radius,     // the outer radius of the propeller 
			float hubRadius,   // the radius of the propeller hub 
			float height,     // the z-thickness of the hub and blades 
			float attackAngle, // the twist applied to the top hub vertices 
			int blades,      // the number of blades 
			int density      // the density of the hub (a multiple of blades) 
		);
		virtual ~Propeller(void);
	};
}

