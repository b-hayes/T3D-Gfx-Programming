#include "Xwing.h"
#include "Math.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Renderer.h"
#include "Animation.h"
#include "Cube.h"


namespace T3D {
	Xwing::Xwing(T3DApplication *app) :GameObject(app) {
		
		//	<	BODY	> (uses same profile as nose)

		//sweep profile for the NOSE and Body of the Xwing
		std::vector<Vector3> mainProfile;
		mainProfile.push_back(Vector3(-0.5f, 1, 0.0f));
		mainProfile.push_back(Vector3(0.5f, 1, 0.0f));
		mainProfile.push_back(Vector3(1.5f, -0.5f, 0.0f));
		mainProfile.push_back(Vector3(1.0f, -1.0f, 0.0f));
		mainProfile.push_back(Vector3(-1.0f, -1.0f, 0.0f));
		mainProfile.push_back(Vector3(-1.5f, -0.5f, 0.0f));

		Transform t;
		SweepPath bodysp;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0.5, -10));
		t.setLocalRotation(Quaternion(Vector3(0, 0, 0)));
		t.setLocalScale(Vector3(5.1, 3, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		bodysp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -100));
		t.setLocalScale(Vector3(10, 11, 1.0));
		bodysp.addTransform(t);

		//close off the back
		t.setLocalPosition(Vector3(0, 0, -100));
		t.setLocalScale(Vector3(0, 0, 1.0));
		bodysp.addTransform(t);

		body = new GameObject(app);
		body->setMesh(new Sweep(mainProfile, bodysp, false));
		body->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		body->getTransform()->setParent(getTransform());
		body->getTransform()->name = "xBody";


		//	<	NOSE	>

		SweepPath nosesp;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		nosesp.addTransform(t);

		//start from the nose
		t.setLocalPosition(Vector3(0, 0, -1));
		t.setLocalScale(Vector3(2, 1, 1.0));
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, -2));
		t.setLocalScale(Vector3(3, 1.5, 1.0));
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0.2, -5));
		t.setLocalScale(Vector3(5, 2.5, 1.0));
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0.5, -10));
		t.setLocalScale(Vector3(6, 4, 1.0));
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, -1, -15));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 30, 0, 0)));
		t.setLocalScale(Vector3(6.5, 3, 1.0));
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, -15));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -30, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0));
		nosesp.addTransform(t);
		nosesp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, -10));
		t.setLocalScale(Vector3(5.5, 2, 1.0));
		nosesp.addTransform(t);
		
		//close off the back
		t.setLocalScale(Vector3(0, 0, 1.0));
		nosesp.addTransform(t);

		nose = new GameObject(app);
		nose->setMesh(new Sweep(mainProfile, nosesp, false));
		nose->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		nose->getTransform()->setParent(getTransform());
		nose->getTransform()->name = "xNose";


		//	<	COCKPIT	>

		std::vector<Vector3> cpProfile;
		cpProfile.push_back(Vector3(-0.5f, 1, 0.0f));
		cpProfile.push_back(Vector3(0.5f, 1, 0.0f));
		cpProfile.push_back(Vector3(1.0f, 0.0f, 0.0f));
		cpProfile.push_back(Vector3(-1.0f, 0.0f, 0.0f));
		SweepPath cockpitsp;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 5, -85));
		t.setLocalRotation(Quaternion(Vector3(0, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0));
		cockpitsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 7.6, -85));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 65, 0, 0)));
		t.setLocalScale(Vector3(11, 13, 1.0));
		cockpitsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 6, -100));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 0, 0, 0)));
		t.setLocalScale(Vector3(12, 11, 1.0));
		cockpitsp.addTransform(t);

		//close off the back
		t.setLocalPosition(Vector3(0, 0, -100));
		t.setLocalScale(Vector3(0, 0, 1.0));
		cockpitsp.addTransform(t);

		cockPit = new GameObject(app);
		cockPit->setMesh(new Sweep(cpProfile, cockpitsp, false));
		cockPit->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		cockPit->getTransform()->setParent(getTransform());			//add to a joint later!
		cockPit->getTransform()->name = "xCockPit";
		
		//	<	ENGINE MOUNT	> (well its the wing mount really)

		SweepPath eMountsp;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 1, -100));
		t.setLocalRotation(Quaternion(Vector3(0, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -100));
		t.setLocalScale(Vector3(10, 11, 1.0));
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -150));
		t.setLocalScale(Vector3(10, 11, 1.0));
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -150));
		t.setLocalScale(Vector3(9, 10, 1.0));
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -146));
		t.setLocalScale(Vector3(9, 10, 1.0));
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -148));
		t.setLocalScale(Vector3(6, 7, 1.0));
		eMountsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 5.5, -148));
		t.setLocalScale(Vector3(0, 0, 1.0));
		eMountsp.addTransform(t);

		//now create the object
		engineMount = new GameObject(app);
		engineMount->setMesh(new Sweep(mainProfile, eMountsp, false));
		engineMount->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		engineMount->getTransform()->setParent(getTransform());
		engineMount->getTransform()->name = "xEngineMount";


		//engines
		std::vector<Vector3> engineProfile;
		engineProfile.push_back(Vector3(-1.75f, -1.75f, 0.0f));
		engineProfile.push_back(Vector3(-2.25f, -0.95f, 0.0f));
		engineProfile.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		engineProfile.push_back(Vector3(-2.25f, 0.95f, 0.0f));
		engineProfile.push_back(Vector3(-1.75f, 1.75f, 0.0f));
		engineProfile.push_back(Vector3(-0.95f, 2.25f, 0.0f));
		engineProfile.push_back(Vector3(0.0f, 2.5f, 0.0f));
		engineProfile.push_back(Vector3(0.95f, 2.25f, 0.0f));
		engineProfile.push_back(Vector3(1.75f, 1.75f, 0.0f));
		engineProfile.push_back(Vector3(2.25f, 0.95f, 0.0f));
		engineProfile.push_back(Vector3(2.5f, 0.0f, 0.0f));
		engineProfile.push_back(Vector3(2.25f, -0.95f, 0.0f));
		engineProfile.push_back(Vector3(1.75f, -1.75f, 0.0f));
		engineProfile.push_back(Vector3(0.95f, -2.25f, 0.0f));
		engineProfile.push_back(Vector3(0.0f, -2.5f, 0.0f));
		engineProfile.push_back(Vector3(-0.95, -2.25f, 0.0f));

		SweepPath enginesp;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 2));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		enginesp.addTransform(t);
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(2, 2, 1.0));
		t.setLocalPosition(Vector3(0,0,-2));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(3.6, 3.6, 1.0));
		t.setLocalPosition(Vector3(0,0,-5));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(3.6, 3.6, 1.0));
		t.setLocalPosition(Vector3(0,0,0));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(4, 4, 1.0));
		t.setLocalPosition(Vector3(0,0,0));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(4, 4, 1.0));
		t.setLocalPosition(Vector3(0,0,-25));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(3, 3, 1.0));
		t.setLocalPosition(Vector3(0,0,-30));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(3, 3, 1.0));
		t.setLocalPosition(Vector3(0,0,-55));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(2.8, 2.8, 1.0));
		t.setLocalPosition(Vector3(0,0,-55));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(2.8, 2.8, 1.0));
		t.setLocalPosition(Vector3(0,0,-50));
		enginesp.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 1.0));
		t.setLocalPosition(Vector3(0,0,-56));
		enginesp.addTransform(t);
		//create the engines later when wings are ready...
		
		//	<	WINGS	>
		std::vector<Vector3> wingProfile;
		wingProfile.push_back(Vector3(-20.1f, -1.0f, 0.0f));
		wingProfile.push_back(Vector3(20.1f, -1.0f, 0.0f));
		wingProfile.push_back(Vector3(20.1f, 1.0f, 0.0f));
		wingProfile.push_back(Vector3(-20.1f, 1.0f, 0.0f));
		
		
		//	<	TOP LEFT WING	>
		SweepPath wingsp;
		//create the first transform:
		t.setLocalPosition(Vector3(5, 1.5, 0));
		t.setLocalScale(Vector3(0, 0, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(5, 1.5, 0));
		t.setLocalScale(Vector3(0.7, 3, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 1.5, 25));
		t.setLocalScale(Vector3(1, 3, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, 30));
		t.setLocalScale(Vector3(1, 1, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(15, 0, 100));
		t.setLocalScale(Vector3(0.5, 1, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 100));
		t.setLocalScale(Vector3(2.5, 1, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 102));
		t.setLocalScale(Vector3(2.5, 1, 1.0));
		wingsp.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 102));
		t.setLocalScale(Vector3(0, 0, 1.0));
		wingsp.addTransform(t);

		//create an empty object for wing joint
		tlWingJoint = new GameObject(app);
		tlWingJoint->getTransform()->setParent(getTransform());
		tlWingJoint->getTransform()->setLocalPosition(Vector3(-10, 1, -125));
		tlWingJoint->getTransform()->name = "tlWingJoint";
		tlWingJoint->getTransform()->setParent(engineMount->getTransform());
//		tlWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -10)));

		//Now use the profile and sweep path:
		tlWing = new GameObject(app);
		tlWing->setMesh(new Sweep(wingProfile, wingsp, false));
		tlWing->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * -90, 0)));
		tlWing->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		tlWing->getTransform()->setLocalScale(Vector3(1, 1, 1));
		tlWing->getTransform()->setParent(tlWingJoint->getTransform());
		tlWing->getTransform()->name = "tlWing";

		//put the engine on..
		tlEngine = new GameObject(app);
		tlEngine->setMesh(new Sweep(engineProfile, enginesp, false));
		tlEngine->getTransform()->setParent( tlWing->getTransform());
		tlEngine->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		tlEngine->getTransform()->setLocalPosition(Vector3(25, 7, 13));
		tlEngine->getTransform()->setLocalScale(Vector3(0.7, 0.7, 1));
		tlEngine->getTransform()->name = "tlEngine";

		//	<	BOT LEFT WING	>
		SweepPath wingsp2;
		//have to recreate the wings because of the shape it cant be reused & rotated...
		//create the first transform:
		t.setLocalPosition(Vector3(5, -1.5, 0));
		t.setLocalScale(Vector3(0, 0, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(5, -1.5, 0));
		t.setLocalScale(Vector3(0.7, 3, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(0, -1.5, 25));
		t.setLocalScale(Vector3(1, 3, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(0, 0, 30));
		t.setLocalScale(Vector3(1, 1, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(15, 0, 100));
		t.setLocalScale(Vector3(0.5, 1, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 100));
		t.setLocalScale(Vector3(2.5, 1, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 102));
		t.setLocalScale(Vector3(2.5, 1, 1.0));
		wingsp2.addTransform(t);

		t.setLocalPosition(Vector3(30, 0, 102));
		t.setLocalScale(Vector3(0, 0, 1.0));
		wingsp2.addTransform(t);

		//create an empty object for wing joint
		blWingJoint = new GameObject(app);
		blWingJoint->getTransform()->setParent(getTransform());
		blWingJoint->getTransform()->setLocalPosition(Vector3(-10, -1, -125));
		blWingJoint->getTransform()->name = "blWingJoint";
		blWingJoint->getTransform()->setParent(engineMount->getTransform());
//		tlWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -10)));

		//Now use the profile and sweep path:
		blWing = new GameObject(app);
		blWing->setMesh(new Sweep(wingProfile, wingsp2, false));
		blWing->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * -90, 0)));
		blWing->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		blWing->getTransform()->setLocalScale(Vector3(1, 1, 1));
		blWing->getTransform()->setParent(blWingJoint->getTransform());
		blWing->getTransform()->name = "blWing";

		//put the engine on..
		blEngine = new GameObject(app);
		blEngine->setMesh(new Sweep(engineProfile, enginesp, false));
		blEngine->getTransform()->setParent( blWing->getTransform());
		blEngine->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		blEngine->getTransform()->setLocalPosition(Vector3(25, -7, 13));
		blEngine->getTransform()->setLocalScale(Vector3(0.7, 0.7, 1));
		blEngine->getTransform()->name = "blEngine";


		//	<	TOP RIGHT WING	>
		
		//create an empty object for wing joint
		trWingJoint = new GameObject(app);
		trWingJoint->getTransform()->setParent(getTransform());
		trWingJoint->getTransform()->setLocalPosition(Vector3(10, -1, -125));
		trWingJoint->getTransform()->name = "trWingJoint";
		trWingJoint->getTransform()->setParent(engineMount->getTransform());
		//		tlWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -10)));

		//Now use the profile and sweep path:
		trWing = new GameObject(app);
		trWing->setMesh(new Sweep(wingProfile, wingsp, false));
		trWing->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 180, Math::DEG2RAD * -90, 0)));
		trWing->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		trWing->getTransform()->setLocalScale(Vector3(1, 1, 1));
		trWing->getTransform()->setParent(trWingJoint->getTransform());
		trWing->getTransform()->name = "trWing";

		//put the engine on..
		trEngine = new GameObject(app);
		trEngine->setMesh(new Sweep(engineProfile, enginesp, false));
		trEngine->getTransform()->setParent(trWing->getTransform());
		trEngine->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		trEngine->getTransform()->setLocalPosition(Vector3(25, 7, 13));
		trEngine->getTransform()->setLocalScale(Vector3(0.7, 0.7, 1));
		trEngine->getTransform()->name = "trEngine";

		//	<	BOT RIGHT WING	>
		
		//create an empty object for wing joint
		brWingJoint = new GameObject(app);
		brWingJoint->getTransform()->setParent(getTransform());
		brWingJoint->getTransform()->setLocalPosition(Vector3(10, 1, -125));
		brWingJoint->getTransform()->name = "brWingJoint";
		brWingJoint->getTransform()->setParent(engineMount->getTransform());
		//		tlWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -10)));

		//Now use the profile and sweep path:
		brWing = new GameObject(app);
		brWing->setMesh(new Sweep(wingProfile, wingsp2, false));
		brWing->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 180, Math::DEG2RAD * -90, 0)));
		brWing->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		brWing->getTransform()->setLocalScale(Vector3(1, 1, 1));
		brWing->getTransform()->setParent(brWingJoint->getTransform());
		brWing->getTransform()->name = "brWing";

		//put the engine on..
		brEngine = new GameObject(app);
		brEngine->setMesh(new Sweep(engineProfile, enginesp, false));
		brEngine->getTransform()->setParent(brWing->getTransform());
		brEngine->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		brEngine->getTransform()->setLocalPosition(Vector3(25, -7, 13));
		brEngine->getTransform()->setLocalScale(Vector3(0.7, 0.7, 1));
		brEngine->getTransform()->name = "brEngine";

		//ROOT
		nose->getTransform()->setParent(body->getTransform());
		engineMount->getTransform()->setParent(body->getTransform());
		cockPit->getTransform()->setParent(body->getTransform());
		body->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 180, 0)));
		setMesh(new Cube(0.1));
		body->getTransform()->setParent(getTransform());
		body->getTransform()->setLocalPosition(Vector3(0, 0, -50));//centre the object more when camera looks at it
		getTransform()->name = "Xwing";

	}

	Xwing::~Xwing(void) {

	}

	void Xwing::openWings(float time, float degrees)
	{
		Animation *anim = new Animation(time);
		addComponent(anim);
		std::string name;
		Vector3 pos;
		Quaternion startRot;
		Quaternion endRot;

		pos = tlWingJoint->getTransform()->getLocalPosition();
		name = tlWingJoint->getTransform()->name;
		startRot = tlWingJoint->getTransform()->getRotationMatrix();
		endRot = Quaternion(Vector3(0, 0, Math::DEG2RAD * -degrees));
		anim->addKey(name, 0.0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = blWingJoint->getTransform()->getLocalPosition();
		name = blWingJoint->getTransform()->name;
		startRot = blWingJoint->getTransform()->getRotationMatrix();
		endRot = Quaternion(Vector3(0, 0, Math::DEG2RAD * degrees));
		anim->addKey(name, 0.0, startRot, pos);
		anim->addKey(name, time, endRot, pos);
		
		pos = trWingJoint->getTransform()->getLocalPosition();
		name = trWingJoint->getTransform()->name;
		startRot = trWingJoint->getTransform()->getRotationMatrix();
		endRot = Quaternion(Vector3(0, 0, Math::DEG2RAD * -degrees));
		anim->addKey(name, 0.0, startRot, pos);
		anim->addKey(name, time, endRot, pos);
		
		pos = brWingJoint->getTransform()->getLocalPosition();
		name = brWingJoint->getTransform()->name;
		startRot = brWingJoint->getTransform()->getRotationMatrix();
		endRot = Quaternion(Vector3(0, 0, Math::DEG2RAD * degrees));
		anim->addKey(name, 0.0, startRot, pos);
		anim->addKey(name, time, endRot, pos);
		
		anim->play();
		//how do i know if the animation is finished???
	}

	void Xwing::explode(float time)
	{
		Animation *anim = new Animation(time);
		addComponent(anim);
		std::string name;
		Vector3 startPos;
		Vector3 endPos;
		Quaternion startRot;
		Quaternion endRot;

		startPos = tlEngine->getTransform()->getLocalPosition();
		endPos = Vector3(50, 50, 50);
		name = tlEngine->getTransform()->name;
		startRot = tlEngine->getTransform()->getRotationMatrix();
		anim->addKey(name, 0, startRot, startPos);
		anim->addKey(name, time, endRot, endPos);
		anim->play();
	}
}


