#pragma once
#include "gameobject.h"
#include "Renderer.h"

namespace T3D {

	class Xwing : public GameObject
	{
	public:
		
		Xwing(T3DApplication *app);
		~Xwing(void);
		void openWings(float time, float degrees);
		void explode(float time);

		//pass the renderer so the materials can be set automatically for you
		Renderer *renderer;

		//parts
		GameObject *nose;
		GameObject *cockPit;
		GameObject *body;
		GameObject *engineMount;
		GameObject *tlEngine;
		GameObject *blEngine;
		GameObject *trEngine;
		GameObject *brEngine;
		GameObject *tlWing;
		GameObject *blWing;
		GameObject *trWing;
		GameObject *brWing;
		GameObject *bumFoot;

		//joints
		GameObject *tlWingJoint;
		GameObject *blWingJoint;
		GameObject *trWingJoint;
		GameObject *brWingJoint;
		GameObject *cockPitJoint;
	};

}