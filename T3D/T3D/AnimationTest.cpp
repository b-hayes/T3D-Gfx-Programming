#include "AnimationTest.h"
#include "Task.h"
#include "Animation.h"
#include "AnimationMove.h"
#include "Cube.h"

namespace T3D {

	AnimationTest::AnimationTest(T3DApplication *app) : Task(app)
	{
		elapsedTime = 0;
		variance = 0.2f;
		music = app->soundManager->createMusic("Resources/Connection.mp3");
		music->setVolume(1);

	}
	AnimationTest::~AnimationTest()
	{
	}

	void AnimationTest::update(float dt) {
		if (time(0))
		{
			music->play();
		}
		elapsedTime += dt;
//		variance = (variance < dt) ? dt : variance;
		Vector3 flyto;
		Vector3 ontop;

		//camera should look at target if there is one
		if(cameraTargetObject != NULL)
		{
			camera->getTransform()->lookAt(cameraTargetObject->getTransform()->getWorldPosition());
		}
		//closing wings as we fly..
		if(elapsedTime >0 && elapsedTime<10)
		{
			xwing->tlWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)), Quaternion(Vector3(0,0,0)),elapsedTime/10));
			xwing->trWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)), Quaternion(Vector3(0,0,0)),elapsedTime/10));
			xwing->blWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)), Quaternion(Vector3(0,0,0)),elapsedTime/10));
			xwing->brWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)), Quaternion(Vector3(0,0,0)),elapsedTime/10));
		}
		
		//xwing flys past
		if(time(0.2))
		{
			cameraTargetObject = xwing;
			flyto = Vector3(-500, 2500, -500);
			xwing->getTransform()->lookAt(flyto);
			move(xwing, 10, Vector3(flyto));
		}
		//crash
		if (time(10))
		{
			camera->getTransform()->setLocalPosition(Vector3(100, 200, -40));
			xwing->getTransform()->setLocalPosition(Vector3(500, 500, 500));
			flyto = Vector3(0, 0, 0);
			xwing->getTransform()->lookAt(flyto);
			move(xwing, 2, Vector3(flyto));
		}
		//eplode
		if (time(12.1))
		{
			cameraTargetObject = xwing->tlEngine;
			moveAndRotate(xwing, 0.2f, Vector3(0, 5, 0), Quaternion(Vector3(0, 0, 0)));
			move(xwing->tlEngine, 0.2f, Vector3(50, 300, 50));
		}
		if(time(12.5))
		{
			move(xwing->tlEngine, 0.5f, Vector3(500, 500, 500));
		}
		if(time(13))
		{
			move(xwing->tlEngine, 1.0f, Vector3(800, 1, 800));
		}
		if(time(13.2))
		{
			move(xwing->tlEngine, 1.0f, Vector3(1000, 1, 1000));
		}
		if (time(15))
		{
			flyto = xwing->getTransform()->getLocalPosition();
			move(camera, 0.5f, Vector3(flyto.x, flyto.y+ 10, flyto.z+140));
			r2d2->getTransform()->setLocalPosition(Vector3(flyto.x, flyto.y+5, flyto.z +75));
			r2d2->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 180, 0)));
			cameraTargetObject = r2d2;
		}
		//R2D2 emerges
		if (time(15.5))
		{
			flyto = r2d2->getTransform()->getLocalPosition();
			ontop = Vector3(flyto.x, flyto.y + 15, flyto.z);
			move(r2d2, 2, ontop);
		}
		if (time(17.7))
		{
			flyto = r2d2->head->getTransform()->getWorldPosition();
			ontop = r2d2->getTransform()->getWorldPosition();
			move(camera, 2, Vector3(flyto.x, flyto.y, flyto.z + 10));
		}
		//Looking around at the wasteland
		if (time(20))
		{
			robot->getTransform()->setLocalPosition(Vector3(500, 5, 500));
			//setup robots arms so they arnt in the start position (insidehis treads)
			flyto = Vector3(Math::DEG2RAD * -40, 0, 0);
			robot->rightArmJoint->getTransform()->setLocalRotation(Quaternion(flyto));
			robot->rightElbowJoint->getTransform()->setLocalRotation(Quaternion(flyto));
			flyto = Vector3(Math::DEG2RAD * 45, 0, 0);
			robot->leftArmJoint->getTransform()->setLocalRotation(Quaternion(flyto));
			robot->leftElbowJoint->getTransform()->setLocalRotation(Quaternion(flyto));
			//PUT the engine in the robots hand
			xwing->tlEngine->getTransform()->setParent(robot->leftWristJoint->getTransform());
			flyto = Vector3(0, -4, 0);
			xwing->tlEngine->getTransform()->setLocalPosition(flyto);
			flyto = Vector3(Math::DEG2RAD * -90, 0, 0);
			xwing->tlEngine->getTransform()->setLocalRotation(flyto);
			cameraTargetObject = NULL;
			flyto = r2d2->head->getTransform()->getWorldPosition();
			camera->getTransform()->setLocalPosition(Vector3(flyto.x, flyto.y + 5, flyto.z));
			camera->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0)));
			rotate(camera, 5, Quaternion(Vector3(0, Math::DEG2RAD * 185, 0)));
		}
		if(time(25))
		{
			camera->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 185, 0)));
			rotate(camera, 5, Quaternion(Vector3(0, Math::DEG2RAD * 0, 0)));
		}
		if(time(30))
		{
			camera->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0)));
			rotate(camera, 2, getLookAt(robot->getTransform()->getWorldPosition(), camera));
		}
		//ROBOT approaches
		if (time(32.2))
		{
			cameraTargetObject = robot;
			flyto = Vector3(70, 8, 130);
			robot->getTransform()->lookAt(flyto);
			move(robot, 10, flyto);
		}
		//robot looks at r2d2
		if(time(43))
		{
			rotate(robot->rightArmJoint, 2, Quaternion(Vector3(Math::DEG2RAD * -70, 0, 0)));
		}
		if(time(45))
		{
			cameraTargetObject = r2d2;
			flyto = robot->getTransform()->getWorldPosition();
			camera->getTransform()->setLocalPosition(Vector3(flyto.x - 10, flyto.y, flyto.z +30));
			r2d2->getTransform()->setLocalPosition(Vector3(flyto.x - 60, flyto.y - 3, flyto.z - 20));
			r2d2->getTransform()->lookAt(flyto);
			//set R2D2 in walking position
			move(r2d2, 3, Vector3(flyto.x-10, flyto.y-3, flyto.z));
			rotate(robot->rightArmJoint, 3, Quaternion(Vector3(Math::DEG2RAD * 0, 0, 0)));
			rotate(robot->rightElbowJoint, 3, Quaternion(Vector3(Math::DEG2RAD * -90, 0, 0)));
			rotate(r2d2->leftArmJoint, 2, Quaternion(Vector3(Math::DEG2RAD * -10, 0, 0)));
			rotate(r2d2->rightArmJoint, 2, Quaternion(Vector3(Math::DEG2RAD * -10, 0, 0)));
			rotate(r2d2->leftFootJoint, 2, Quaternion(Vector3(Math::DEG2RAD * 8, 0, 0)));
			rotate(r2d2->rightFootJoint, 2, Quaternion(Vector3(Math::DEG2RAD * 8, 0, 0)));
		}
		//put the engine back on
		if(time(49))
		{
			
			xwing->tlEngine->getTransform()->setParent(xwing->tlWing->getTransform());
			xwing->tlEngine->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
			xwing->tlEngine->getTransform()->setLocalPosition(Vector3(30, 10, 20));
			xwing->tlEngine->getTransform()->setLocalScale(Vector3(0.7, 0.7, 1));

			cameraTargetObject = xwing->tlEngine;
			flyto = xwing->tlEngine->getTransform()->getWorldPosition();
			camera->getTransform()->setLocalPosition(Vector3(flyto.x + 15, flyto.y + 15, flyto.z + 150));

			robot->getTransform()->setLocalPosition(Vector3(Vector3(flyto.x + 5, flyto.y, flyto.z + 20)));
			robot->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
			robot->leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, 0)));
			robot->leftElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD*-45, 0, 0)));

			rotate(robot->rightElbowJoint, 2, Quaternion(Vector3(Math::DEG2RAD*-45, 0, 0)));

			r2d2->getTransform()->setLocalPosition(Vector3(0,0,0));
			

			move(xwing->tlEngine, 2, Vector3(25, 7, 13));
		}
		if(time(52))
		{
			cameraTargetObject = xwing;
			camera->getTransform()->setLocalPosition(Vector3(0, 20, 300));
			robot->getTransform()->setLocalPosition(Vector3(0, 8, 200));
			robot->getTransform()->setLocalRotation(Vector3(0, 0, 0));
			r2d2->getTransform()->setLocalPosition(Vector3(0, -20, 0));

			move(xwing, 3, Vector3(0, 90, 0));
		}
		//open wings
		float start = 53;
		float end = 58;
		if (elapsedTime > start && elapsedTime < end)
		{
			robot->headJoint->getTransform()->lookAt(xwing->getTransform()->getWorldPosition());
			xwing->tlWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, 0)), Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)), (elapsedTime-start) / (end-start)));
			xwing->trWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, 0)), Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)), (elapsedTime-start) / (end - start)));
			xwing->blWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, 0)), Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)), (elapsedTime-start) / (end - start)));
			xwing->brWingJoint->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, 0)), Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)), (elapsedTime-start) / (end - start)));
		}
		if(time(55))
		{
			move(xwing, 20, Vector3(-2000, 150, 0));
		}
		start = 55;
		end = 60;
		if (elapsedTime > start && elapsedTime < end)
		{
			flyto = Vector3::lerp(Vector3(1, 0, 0), Vector3(0, 0, 0), (elapsedTime - start) / (end - start));
			music->setVolume(flyto.x);
			robot->headJoint->getTransform()->lookAt(xwing->getTransform()->getWorldPosition());
			xwing->getTransform()->setLocalRotation(Quaternion::lerp(Quaternion(Vector3(0, 0, 0)), Quaternion(Vector3(Math::DEG2RAD*10, Math::DEG2RAD * 90, 0)), (elapsedTime - start) / (end - start)));
		}
		if(time(60))
		{
			cameraTargetObject = NULL;
			credits->getTransform()->setParent(camera->getTransform());
			credits->getTransform()->setLocalPosition(Vector3(0, -100, -10));
			credits->getTransform()->setLocalRotation(Quaternion(Vector3(0,0,0)));

			move(credits, 2, Vector3(0, 0, -10));
		}
	}

	void AnimationTest::moveAndRotate(GameObject * object, float time, Vector3 position, Quaternion rotation) {
		
		AnimationMove * move = new AnimationMove(app);
		move->object = object;
		move->startPos = object->getTransform()->getLocalPosition();
		move->endPos = position;
		move->time = time;
		move->startRot = object->getTransform()->getRotationMatrix();
		move->endRot = rotation;
		move->rotate = true;
		move->displace = true;
		app->addTask(move);
	}
	void AnimationTest::move(GameObject * object, float time, Vector3 position) {
		
		AnimationMove * move = new AnimationMove(app);
		move->object = object;
		move->startPos = object->getTransform()->getLocalPosition();
		move->endPos = position;
		move->time = time;
		move->rotate = false;
		move->displace = true;
		app->addTask(move);
	}
	void AnimationTest::rotate(GameObject * object, float time, Quaternion rotation) {
		
		AnimationMove * move = new AnimationMove(app);
		move->object = object;
		move->time = time;
		move->startRot = object->getTransform()->getRotationMatrix();
		move->endRot = rotation;
		move->rotate = true;
		move->displace = false;
		app->addTask(move);
	}

	bool AnimationTest::time(float targetTime)
	{
		if(elapsedTime >= targetTime && elapsedTime < targetTime + variance)
		{
			return true;
		}
		return false;
	}

	Quaternion AnimationTest::getLookAt(Vector3 target, GameObject * object)
	{
		GameObject * temp = new GameObject(app);
		temp->setMesh(new Cube(0.1));
		temp->getTransform()->setLocalPosition(object->getTransform()->getWorldPosition());
		temp->getTransform()->lookAt(target);
		Quaternion rot = temp->getTransform()->getRotationMatrix();
		delete temp;
		return rot;
	}
}

