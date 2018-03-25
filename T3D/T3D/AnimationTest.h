#pragma once
#include "Task.h"
#include "R2D2.h"
#include "Robot.h"
#include "Xwing.h"
#include "SoundTestTask.h"
#include "Billboard.h"


namespace T3D {

	class AnimationTest :
		public Task
	{
	public:
		float variance = 0.2f;
		float elapsedTime = 0;
		R2D2 * r2d2;
		Robot * robot;
		Xwing * xwing;
		Music * music;
		GameObject * credits;
		SoundTestTask * sounds;
		GameObject * camera;
		GameObject * cameraTargetObject = NULL;
		AnimationTest(T3DApplication * app);
		~AnimationTest();
		
		void update(float dt);
		void moveAndRotate(GameObject * object, float time, Vector3 position, Quaternion rotation);
		bool time(float target);
		Quaternion getLookAt(Vector3 target, GameObject* object);
		void AnimationTest::move(GameObject * object, float time, Vector3 position);
		void rotate(GameObject * object, float time, Quaternion rotation);
	};
}
