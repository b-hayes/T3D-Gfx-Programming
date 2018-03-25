#include "TCylinder.h"
#include "Math.h"

namespace T3D
{
	TCylinder::TCylinder(float radius, float height, int density)
	{
		// Init vertex and index arrays
		initArrays((density * 2) + (density * 2) + 2 + density,	// total number of points our object has
			density * 2,	// num tris
			density);		// num quads

		for (int i = 0; i < density; i++) {

			//sides
//			float theta = i * (Math::TWO_PI / density);
//			setVertex(i, radius * cos(theta), height, radius * sin(theta));
//			setVertex(density + i, radius * cos(theta), -height, radius * sin(theta));

//			float theta = float(i) / density * Math::TWO_PI;
//			setVertex(i, radius*cos(theta), height, radius*sin(theta));
//			setVertex((density + 1) + i, radius*cos(theta), -height, radius*sin(theta));

			float theta = float(i) / density * Math::TWO_PI;
			setVertex(i, radius*cos(theta), height, radius*sin(theta));
			float top = radius;
			setUV(i, float(i) / density, top);
			setVertex(density + 1 + i, radius*cos(theta), -height, radius*sin(theta));
			float bottom = radius;
			setUV(density + 1 + i, float(i) / density, bottom);

			//cap
			setVertex(density * 2 + i, radius * cos(theta), height, radius * sin(theta));
			setVertex(density * 3 + i, radius * cos(theta), -height, radius * sin(theta));
		}

		//bottom centre
		setVertex(density * 4, 0, -height, 0);
		//top
		setVertex(density * 4 + 1, 0, height, 0);

		//set faces
		for (int i = 0; i < density +1; i++) {
			//side
			setFace(
				i,
				i,
				(i + 1),// % density,
				density + (i + 1),// % density,
				density + i
			);

			//bottom
			setFace(
				i,
				density * 3 + i,
				density * 3 + (i + 1) % density,
				density * 4

			);

			//top
			setFace(
				density + i,
				density * 2 + (i + 2) % density,
				density * 2 + i,
				density * 4 + 1
			);
		}

		checkArrays();
		calcNormals();

	}


	TCylinder::~TCylinder(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
