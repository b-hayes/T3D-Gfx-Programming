#pragma once
#include "gameobject.h"

namespace T3D {

	class Robot : public GameObject
	{
	public:
		Robot(T3DApplication *app);
		~Robot(void);

		void wave(float time, float speed);

		void armsUp(float time, float degrees, char side);

		void bendElbows(float time, float degrees, char side);

		void blink(float time);

		//parts
		GameObject *torso;
		GameObject *head;
		GameObject *neck;
		GameObject *eye1;
		GameObject *eye2;
		GameObject *mouth;
		GameObject *rightArmShoulder;
		GameObject *rightElbowJoint;
		GameObject *rightForarm;
		GameObject *rightWristJoint;
		GameObject *rightHand;
		GameObject *leftArmShoulder;
		GameObject *leftElbowJoint;
		GameObject *leftForarm;
		GameObject *leftWristJoint;
		GameObject *leftHand;
		GameObject *treadJoint;
		GameObject *treadBase;
		GameObject *rightTread;
		GameObject *leftTread;

		//joints
		GameObject *headJoint;
		GameObject *leftArmJoint;
		GameObject *rightArmJoint;
	};

}