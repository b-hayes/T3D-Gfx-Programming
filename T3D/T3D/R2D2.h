#pragma once
#include "gameobject.h"
#include "SweepPath.h"
#include "Cylinder.h"
#include "Renderer.h"

namespace T3D {

	class R2D2 : public GameObject
	{
	public:
		
		R2D2(T3DApplication *app);
		~R2D2(void);
		void walkingPos(float time, float speed);

		//pass the renderer so the materials can be set automatically for you
		Renderer *renderer;

		//parts
		GameObject *head;
		GameObject *eye;
		GameObject *body;
		GameObject *leftArm;
		GameObject *leftArmLong;
		GameObject *leftArmStub;
		GameObject *rightArm;
		GameObject *rightArmLong;
		GameObject *rightArmStub;
		GameObject *leftFoot;
		GameObject *rightFoot;
		GameObject *bum;
		GameObject *bumFoot;

		//joints
		GameObject *headJoint;
		GameObject *leftArmJoint;
		GameObject *rightArmJoint;
		GameObject *leftFootJoint;
		GameObject *rightFootJoint;
		GameObject *bumFootJoint;
	};

}