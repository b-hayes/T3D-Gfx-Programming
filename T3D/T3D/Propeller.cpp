#include "Propeller.h"
#include "Math.h"

namespace T3D
{
	Propeller::Propeller(
		float radius,     // the outer radius of the propeller 
		float hubRadius,   // the radius of the propeller hub 
		float height,     // the z-thickness of the hub and blades 
		float attackAngle, // the twist applied to the top hub vertices 
		int blades,      // the number of blades 
		int density      // the density of the hub (a multiple of blades) 
	)
	{
		// Init vertex and index arrays
		initArrays((density * 2) + (density * 2) + 2,	// total number of points our object has
			density * 2,	// num tris
			density);		// num quads

		for (int i = 0; i < density; i++) {
			float r = hubRadius;
			//change radius if its a blade face
			if (i%(density/blades)==0 || (i-1)% (density / blades) == 0)
			{
				r = radius;
			}

			//sides (each side has a blade based on density)
			//each blade face needs seperate set of verticies for additional faces
			//once done duplicate verticies for sharp shading
			//postivie height vets get twisted
			float theta = i * (Math::TWO_PI / density);
			setVertex(i, r * cos(theta + (Math::DEG2RAD * attackAngle)), height, r * sin(theta + (Math::DEG2RAD * attackAngle))); //chnage radius here for outer blade caps
			setVertex(density + i, r * cos(theta), -height, r * sin(theta));

			//cap
			setVertex(density * 2 + i, r * cos(theta + (Math::DEG2RAD * attackAngle)), height, r * sin(theta + (Math::DEG2RAD * attackAngle)));
			setVertex(density * 3 + i, r * cos(theta), -height, r * sin(theta));
		}

		//bottom centre
		setVertex(density * 4, 0, -height, 0);
		//top
		setVertex(density * 4 + 1, 0, height, 0);

		//set faces
		for (int i = 0; i < density; i++) {
			//side
			setFace(
				i,
				i,
				(i + 1) % density,
				density + (i + 1) % density,
				density + i
			);

			//bottom
			setFace(
				i,
				density * 3 + i,
				density * 3 + (i + 1) % density,
				density * 4

			);


			setFace(
				density + i,
				density * 2 + (i + 1) % density,
				density * 2 + i,
				density * 4 + 1
			);
		}


		checkArrays();
		calcNormals();

	}


	Propeller::~Propeller(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
