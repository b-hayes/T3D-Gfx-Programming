#pragma once
#include "Task.h"
#include "R2D2.h"
#include "Robot.h"
#include "Xwing.h"


namespace T3D {

	class AnimationMove :
		public Task
	{
	public:
		float variance = 0.2f;
		float elapsedTime = 0;
		float time;
		bool rotate = false;
		bool displace = false;
		Vector3 startPos;
		Vector3 endPos;
		Quaternion startRot;
		Quaternion endRot;
		GameObject * object = NULL;
		AnimationMove(T3DApplication * app);
		~AnimationMove();
		
		void update(float dt);
	};
}
