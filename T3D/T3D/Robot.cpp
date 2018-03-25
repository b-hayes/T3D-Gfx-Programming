#include "Robot.h"
#include "Math.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Animation.h"


namespace T3D {
	Robot::Robot(T3DApplication *app) :GameObject(app) {

		//Robot's Upper Body
		std::vector<Vector3> torsoProfile;
		torsoProfile.push_back(Vector3(-1, -1, 0.0f));
		torsoProfile.push_back(Vector3(1, -1, 0.0f));
		torsoProfile.push_back(Vector3(1, 1, 0.0f));
		torsoProfile.push_back(Vector3(-1, 1, 0.0f));

		SweepPath torsosp;
		Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 1.5, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		torsosp.addTransform(t);

		t.setLocalScale(Vector3(1.9, 0.5, 1.0));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, 1, 0));
		t.setLocalScale(Vector3(2, 0.6, 1));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalScale(Vector3(2, 0.8, 0));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, -1, 0));
		t.setLocalScale(Vector3(2, 0.6, 0));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, -2, 0));
		t.setLocalScale(Vector3(1, 0.5, 0));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, -2.5, 0));
		t.setLocalScale(Vector3(0.8, 0.4, 0));
		torsosp.addTransform(t);

		t.setLocalPosition(Vector3(0, -3, 0));
		t.setLocalScale(Vector3(0, 0, 0));
		torsosp.addTransform(t);

		//create the object:
		torso = new GameObject(app);
		torso->setMesh(new Sweep(torsoProfile, torsosp, false));
		torso->getTransform()->setParent(getTransform());
		torso->getTransform()->name = "Torso";

		/*setMesh(new Cube(1));
		getTransform()->name = "RobotTorso";*/

		// < NECK >
		neck = new GameObject(app);
		neck->setMesh(new Cylinder(0.3, 1, 16));
		neck->getTransform()->setLocalPosition(Vector3(0, 1.2, 0));
		neck->getTransform()->setLocalScale(Vector3(1, 1, 1));
		neck->getTransform()->setParent(torso->getTransform());
		neck->getTransform()->name = "Neck";

		//	< HEAD >

		headJoint = new GameObject(app);
		headJoint->getTransform()->setParent(neck->getTransform());
		headJoint->getTransform()->setLocalPosition(Vector3(0, 1.5, 0));
		headJoint->getTransform()->name = "HeadJoint";

		head = new GameObject(app);
		head->setMesh(new Sphere(1, 16));
		head->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		head->getTransform()->setLocalScale(Vector3(2, 1, 1));
		head->getTransform()->setParent(headJoint->getTransform());
		head->getTransform()->name = "Head";

		eye1 = new GameObject(app);
		eye1->setMesh(new Sphere(0.3, 16));
		eye1->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		eye1->getTransform()->setLocalPosition(Vector3(0.7, 0.1, 0.7));
		eye1->getTransform()->setLocalScale(Vector3(1, 1, 1));
		eye1->getTransform()->setParent(headJoint->getTransform());
		eye1->getTransform()->name = "Eye1";

		eye2 = new GameObject(app);
		eye2->setMesh(new Sphere(0.3, 16));
		eye2->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		eye2->getTransform()->setLocalPosition(Vector3(-0.7, 0.1, 0.7));
		eye2->getTransform()->setLocalScale(Vector3(1, 1, 1));
		eye2->getTransform()->setParent(headJoint->getTransform());
		eye2->getTransform()->name = "Eye2";

		mouth = new GameObject(app);
		mouth->setMesh(new Cylinder(0.2, 1, 5));
		mouth->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, Math::DEG2RAD * 90, 0)));
		mouth->getTransform()->setLocalPosition(Vector3(0, -0.5, 0.7));
		mouth->getTransform()->setLocalScale(Vector3(1, 1, 1));
		mouth->getTransform()->setParent(headJoint->getTransform());
		mouth->getTransform()->name = "Mouth";

		//	< RIGHT ARM >

		rightArmJoint = new GameObject(app);
		rightArmJoint->setMesh(new Sphere(0.5, 16));
		rightArmJoint->getTransform()->setParent(torso->getTransform());
		rightArmJoint->getTransform()->setLocalPosition(Vector3(2, 1, 0));
		rightArmJoint->getTransform()->name = "RighttArmJoint";

		std::vector<Vector3> shoulderProfile;
		shoulderProfile.push_back(Vector3(0, -4.5, 0.0f));
		shoulderProfile.push_back(Vector3(1.5, -4, 0.0f));
		shoulderProfile.push_back(Vector3(1.5, 0.5, 0.0f));
		shoulderProfile.push_back(Vector3(2.5, 2.5, 0.0f));
		shoulderProfile.push_back(Vector3(-1.5, 1, 0.0f));
		shoulderProfile.push_back(Vector3(-2, -0.5, 0.0f));
		shoulderProfile.push_back(Vector3(-1.5, -4, 0.0f));
		shoulderProfile.push_back(Vector3(-0, -4.5, 0.0f));

		SweepPath shouldersp;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(-1, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		shouldersp.addTransform(t);
		t.setLocalPosition(Vector3(-0.5, 0, 0));
		t.setLocalScale(Vector3(0.8, 1.3, 0.8));
		shouldersp.addTransform(t);
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalScale(Vector3(0.8, 1.1, 0.5));
		shouldersp.addTransform(t);
		t.setLocalPosition(Vector3(0.5, 0, 0));
		t.setLocalScale(Vector3(0.8, 1.3, 0.8));
		shouldersp.addTransform(t);
		t.setLocalPosition(Vector3(1, 0, 0));
		t.setLocalScale(Vector3(0, 0, 0));
		shouldersp.addTransform(t);

		//create the object:
		rightArmShoulder = new GameObject(app);
		rightArmShoulder->setMesh(new Sweep(shoulderProfile, shouldersp, false));
		rightArmShoulder->getTransform()->setLocalScale(Vector3(0.5, 0.5, 0.5));
		rightArmShoulder->getTransform()->setLocalPosition(Vector3(0.6, 0, 0));
		rightArmShoulder->getTransform()->setParent(rightArmJoint->getTransform());
		rightArmShoulder->getTransform()->name = "RightArmShoulder";

		rightElbowJoint = new GameObject(app);
		rightElbowJoint->setMesh(new Sphere(0.5, 16));
		rightElbowJoint->getTransform()->setParent(rightArmShoulder->getTransform());
		rightElbowJoint->getTransform()->setLocalPosition(Vector3(0, -5.5, 0));
		rightElbowJoint->getTransform()->setLocalScale(Vector3(2, 2, 2));
		rightElbowJoint->getTransform()->name = "RightElbowJoint";

		rightForarm = new GameObject(app);
		rightForarm->setMesh(new Cylinder(0.4, 1.2, 5));
		rightForarm->getTransform()->setLocalPosition(Vector3(0, -1.1, 0));
		rightForarm->getTransform()->setLocalScale(Vector3(1, 1, 1.5));
		rightForarm->getTransform()->setParent(rightElbowJoint->getTransform());
		rightForarm->getTransform()->name = "RightForarm";

		rightWristJoint = new GameObject(app);
		rightWristJoint->setMesh(new Sphere(0.5, 16));
		rightWristJoint->getTransform()->setParent(rightForarm->getTransform());
		rightWristJoint->getTransform()->setLocalPosition(Vector3(0, -1.5, 0));
		rightWristJoint->getTransform()->setLocalScale(Vector3(1, 1, 0.725));
		rightWristJoint->getTransform()->name = "RightWristJoint";

		rightHand = new GameObject(app);
		rightHand->setMesh(new Cube(0.5));
		rightHand->getTransform()->setParent(rightWristJoint->getTransform());
		rightHand->getTransform()->setLocalPosition(Vector3(0, -1, 0));
		rightHand->getTransform()->setLocalScale(Vector3(1, 1.5, 0.5));
		rightHand->getTransform()->name = "RightHand";

		//	< LEFT ARM >

		leftArmJoint = new GameObject(app);
		leftArmJoint->setMesh(new Sphere(0.5, 16));
		leftArmJoint->getTransform()->setParent(torso->getTransform());
		leftArmJoint->getTransform()->setLocalPosition(Vector3(-2, 1, 0));
		leftArmJoint->getTransform()->name = "LeftArmJoint";

		//left shoulder:
		leftArmShoulder = new GameObject(app);
		leftArmShoulder->setMesh(new Sweep(shoulderProfile, shouldersp, false));
		leftArmShoulder->getTransform()->setLocalScale(Vector3(0.5, 0.5, 0.5));
		leftArmShoulder->getTransform()->setLocalPosition(Vector3(-0.6, 0, 0));
		leftArmShoulder->getTransform()->setParent(leftArmJoint->getTransform());
		leftArmShoulder->getTransform()->name = "RightArmShoulder";

		leftElbowJoint = new GameObject(app);
		leftElbowJoint->setMesh(new Sphere(0.5, 16));
		leftElbowJoint->getTransform()->setParent(leftArmShoulder->getTransform());
		leftElbowJoint->getTransform()->setLocalPosition(Vector3(0, -5.5, 0));
		leftElbowJoint->getTransform()->setLocalScale(Vector3(2, 2, 2));
		leftElbowJoint->getTransform()->name = "LeftElbowJoint";

		leftForarm = new GameObject(app);
		leftForarm->setMesh(new Cylinder(0.4, 1.2, 5));
		leftForarm->getTransform()->setLocalPosition(Vector3(0, -1.1, 0));
		leftForarm->getTransform()->setLocalScale(Vector3(1, 1, 1.5));
		leftForarm->getTransform()->setParent(leftElbowJoint->getTransform());
		leftForarm->getTransform()->name = "RightForarm";

		leftWristJoint = new GameObject(app);
		leftWristJoint->setMesh(new Sphere(0.5, 16));
		leftWristJoint->getTransform()->setParent(leftForarm->getTransform());
		leftWristJoint->getTransform()->setLocalPosition(Vector3(0, -1.5, 0));
		leftWristJoint->getTransform()->setLocalScale(Vector3(1, 1, 0.725));
		leftWristJoint->getTransform()->name = "LeftWristJoint";

		leftHand = new GameObject(app);
		leftHand->setMesh(new Cube(0.5));
		leftHand->getTransform()->setParent(leftWristJoint->getTransform());
		leftHand->getTransform()->setLocalPosition(Vector3(0, -1, 0));
		leftHand->getTransform()->setLocalScale(Vector3(1, 1.5, 0.5));
		leftHand->getTransform()->name = "LeftHand";

		//< TREADS >

		treadJoint = new GameObject(app);
		treadJoint->setMesh(new Sphere(1, 16));
		treadJoint->getTransform()->setParent(torso->getTransform());
		treadJoint->getTransform()->setLocalPosition(Vector3(0, -3.5, 0));
		treadJoint->getTransform()->setLocalScale(Vector3(1, 1, 1));
		treadJoint->getTransform()->name = "TreadJoint";

		std::vector<Vector3> treadProfile;
		treadProfile.push_back(Vector3(-3, -3, 0.0f));
		treadProfile.push_back(Vector3(3, -3, 0.0f));
		treadProfile.push_back(Vector3(1, 1, 0.0f));
		treadProfile.push_back(Vector3(-1, 1, 0.0f));

		SweepPath treadersp;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(-1, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		treadersp.addTransform(t);
		t.setLocalPosition(Vector3(-1, 0, 0));
		t.setLocalScale(Vector3(1, 1, 1));
		treadersp.addTransform(t);
		t.setLocalPosition(Vector3(1, 0, 0));
		t.setLocalScale(Vector3(1, 1, 1));
		treadersp.addTransform(t);
		t.setLocalPosition(Vector3(1, 0, 0));
		t.setLocalScale(Vector3(0, 0, 1));
		treadersp.addTransform(t);

		//create the object:
		treadBase = new GameObject(app);
		treadBase->setMesh(new Sweep(treadProfile, treadersp, false));
		treadBase->getTransform()->setLocalScale(Vector3(3.5, 0.6, 1));
		treadBase->getTransform()->setLocalPosition(Vector3(0, -1, 0));
		treadBase->getTransform()->setParent(treadJoint->getTransform());
		treadBase->getTransform()->name = "TreadBase";

		//create the object:
		rightTread = new GameObject(app);
		rightTread->setMesh(new Sweep(treadProfile, treadersp, false));
		rightTread->getTransform()->setLocalScale(Vector3(0.2, 1.2, 1.2));
		rightTread->getTransform()->setLocalPosition(Vector3(0.7, 0, 0));
		rightTread->getTransform()->setParent(treadBase->getTransform());
		rightTread->getTransform()->name = "RightTread";

		//create the object:
		leftTread = new GameObject(app);
		leftTread->setMesh(new Sweep(treadProfile, treadersp, false));
		leftTread->getTransform()->setLocalScale(Vector3(0.2, 1.2, 1.2));
		leftTread->getTransform()->setLocalPosition(Vector3(-0.7, 0, 0));
		leftTread->getTransform()->setParent(treadBase->getTransform());
		leftTread->getTransform()->name = "LeftTread";
		
		//ROOT
		torso->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 180, 0)));
		setMesh(new Cube(0.1));
		torso->getTransform()->setParent(getTransform());
		getTransform()->name = "ROBOT";
	}

	Robot::~Robot(void) {

	}

	void Robot::wave(float time, float speed)
	{

//		//rotating the joints
//		getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 10, 0, 0)));
//		headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -40, Math::DEG2RAD * 20, Math::DEG2RAD * -20)));
//		rightArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -70, Math::DEG2RAD * 40, Math::DEG2RAD * 20)));
//		rightElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -70, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
//		rightWristJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -30, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
//		leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 30, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
//		leftElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -75, Math::DEG2RAD * 10, Math::DEG2RAD * 0)));
//		leftWristJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -20, Math::DEG2RAD * 20, Math::DEG2RAD * 0)));
//		treadJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 20, Math::DEG2RAD * 10, Math::DEG2RAD * 0)));
//
//		if (time > 10)
//			time = 10;//max 10 seconds!
//		Animation *anim = new Animation(10.0);
//		addComponent(anim);
//		std::string name;
//		Vector3 pos;
//		Quaternion startRot;
//		Quaternion endRot;
//		float degrees;
//
//		pos = getTransform()->getLocalPosition();
//		name = getTransform()->name;
//		startRot = getTransform()->getRotationMatrix();
//		degrees = -10 * speed;
//		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
//		anim->addKey(name, 10.0, endRot, pos);
//		anim->addKey(name, 0, startRot, pos);
//		anim->addKey(name, time, endRot, pos);
	}

	void Robot::armsUp(float time, float degrees, char side)
	{
		if (time > 10)
			time = 10;//max 10 seconds!
		Animation *anim = new Animation(10.0);
		addComponent(anim);
		std::string name;
		Vector3 pos;
		Quaternion startRot;
		Quaternion endRot;
		if (side=='r' || side=='b')
		{
			pos = rightArmJoint->getTransform()->getLocalPosition();
			name = rightArmJoint->getTransform()->name;
			startRot = rightArmJoint->getTransform()->getRotationMatrix();
			endRot = Quaternion(Vector3(Math::DEG2RAD * -degrees, 0, 0));
			anim->addKey(name, 10.0, endRot, pos);
			anim->addKey(name, 0, startRot, pos);
			anim->addKey(name, time, endRot, pos);
		}

		if (side=='l' || side=='b')
		{
			pos = leftArmJoint->getTransform()->getLocalPosition();
			name = leftArmJoint->getTransform()->name;
			startRot = leftArmJoint->getTransform()->getRotationMatrix();
			endRot = Quaternion(Vector3(Math::DEG2RAD * -degrees, 0, 0));
			anim->addKey(name, 10.0, endRot, pos);
			anim->addKey(name, 0, startRot, pos);
			anim->addKey(name, time, endRot, pos);
		}
		

		anim->play();
	}

	void Robot::bendElbows(float time, float degrees, char side)
	{
		if (time > 10)
			time = 10;//max 10 seconds!
		Animation *anim = new Animation(10.0);
		addComponent(anim);
		std::string name;
		Vector3 pos;
		Quaternion startRot;
		Quaternion endRot;

		if (side=='r' || side=='b')
		{
			pos = rightElbowJoint->getTransform()->getLocalPosition();
			name = rightElbowJoint->getTransform()->name;
			startRot = rightElbowJoint->getTransform()->getRotationMatrix();
			endRot = Quaternion(Vector3(Math::DEG2RAD * -degrees, 0, 0));
			anim->addKey(name, 10.0, endRot, pos);
			anim->addKey(name, 0, startRot, pos);
			anim->addKey(name, time, endRot, pos);
		}

		if (side == 'l' || side=='b')
		{
			pos = leftElbowJoint->getTransform()->getLocalPosition();
			name = leftElbowJoint->getTransform()->name;
			startRot = leftElbowJoint->getTransform()->getRotationMatrix();
			endRot = Quaternion(Vector3(Math::DEG2RAD * -degrees, 0, 0));
			anim->addKey(name, 10.0, endRot, pos);
			anim->addKey(name, 0, startRot, pos);
			anim->addKey(name, time, endRot, pos);
		}

		anim->play();
	}

}


