#include "Pyramid.h"

namespace T3D
{
	Pyramid::Pyramid(float size)
	{
		// Init vertex and index arrays
		initArrays(4 * 3 + 1 * 4,	// num vertices
			4,		// num tris
			1);		// num quads

		// Set vertices

		int pos = 0;

		//front
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, 0, size, 0);

		//back
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, 0, size, 0);

		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, 0, size, 0);

		//right
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, 0, size, 0);

		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);

		// Build tris
		pos = 0;

		//front
		setFace(pos++, 2, 1, 0);

		//back
		setFace(pos++, 3, 4, 5);

		//left
		setFace(pos++, 6, 7, 8);

		//right
		setFace(pos++, 9, 10, 11);

		//set quads
		//bottom
		pos = 0;//were on quads now so starting in the other array
		setFace(pos++, 12, 13, 14, 15);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
		
	}


	Pyramid::~Pyramid(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
