#pragma once


#ifndef TCylinder_H
#define TCylinder_H

#include "mesh.h"

namespace T3D
{
	class TCylinder :
		public Mesh
	{
	public:
		TCylinder(float radius, float height, int density);
		virtual ~TCylinder (void);
	};
}

#endif