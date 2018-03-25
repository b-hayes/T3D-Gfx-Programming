#include "AnimationMove.h"
#include "Task.h"
#include "Animation.h"

namespace T3D {

	AnimationMove::AnimationMove(T3DApplication *app) : Task(app)
	{
		elapsedTime = 0;
		variance = 0.2f;
		rotate = false;
		displace = false;
	}
	AnimationMove::~AnimationMove()
	{
	}
	void AnimationMove::update(float dt) {
		elapsedTime += dt;
		if(elapsedTime < time)
		{
			if(rotate)
			{
				object->getTransform()->setLocalRotation(Quaternion::lerp(startRot, endRot, elapsedTime / time));
			}
			if(displace)
			{
				object->getTransform()->setLocalPosition(Vector3::lerp(startPos, endPos, elapsedTime / time));
			}
		}
		else { setFinsihed(true); }
	}
	
}

