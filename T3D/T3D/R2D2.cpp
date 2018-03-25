#include "R2D2.h"
#include "Math.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Renderer.h"
#include "Animation.h"
#include "TCylinder.h"
#include "Cube.h"


namespace T3D {
	R2D2::R2D2(T3DApplication *app) :GameObject(app) {
		
		//r2d2's body
		body = new GameObject(app);
		body->setMesh(new Cylinder(2.5, 2.5, 16));
		body->getTransform()->name = "BODY";

		//	< HEAD >

		//////sweep profile for the HEAD of the R2D2
		std::vector<Vector3> headProfile;
		headProfile.push_back(Vector3(-1.75f, -1.75f, 0.0f));
		headProfile.push_back(Vector3(-2.25f, -0.95f, 0.0f));
		headProfile.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		headProfile.push_back(Vector3(-2.25f, 0.95f, 0.0f));
		headProfile.push_back(Vector3(-1.75f, 1.75f, 0.0f));
		headProfile.push_back(Vector3(-0.95f, 2.25f, 0.0f));
		headProfile.push_back(Vector3(0.0f, 2.5f, 0.0f));
		headProfile.push_back(Vector3(0.95f, 2.25f, 0.0f));
		headProfile.push_back(Vector3(1.75f, 1.75f, 0.0f));
		headProfile.push_back(Vector3(2.25f, 0.95f, 0.0f));
		headProfile.push_back(Vector3(2.5f, 0.0f, 0.0f));
		headProfile.push_back(Vector3(2.25f, -0.95f, 0.0f));
		headProfile.push_back(Vector3(1.75f, -1.75f, 0.0f));
		headProfile.push_back(Vector3(0.95f, -2.25f, 0.0f));
		headProfile.push_back(Vector3(0.0f, -2.5f, 0.0f));
		headProfile.push_back(Vector3(-0.95, -2.25f, 0.0f));

		SweepPath headsp;
		Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		headsp.addTransform(t);

		//2nd transform: (begin the rim where head joins to body)
		t.setLocalScale(Vector3(1.03, 1.03, 1.0)); // Rim width
		headsp.addTransform(t);
		headsp.addTransform(t);

		//3rd transform:
		t.setLocalPosition(Vector3(0, 0.3, 0)); //rim height
		headsp.addTransform(t);
		headsp.addTransform(t);

		//4th transform: (finish the rim)
		t.setLocalScale(Vector3(1.0, 1.0, 1.0)); // Rim width
		headsp.addTransform(t);
		headsp.addTransform(t);

		//5th transfrom: (begin recessing to build rest of head shape)
		t.setLocalPosition(Vector3(0, 1.25, 0));
		t.setLocalScale(Vector3(0.9, 0.9, 1.0));
		headsp.addTransform(t);

		//6th transfrom:
		t.setLocalPosition(Vector3(0, 2.05, 0));
		t.setLocalScale(Vector3(0.7, 0.7, 1.0));
		headsp.addTransform(t);

		//7th transfrom:
		t.setLocalPosition(Vector3(0, 2.55, 0));
		t.setLocalScale(Vector3(0.38, 0.38, 1.0));
		headsp.addTransform(t);
		
		//8th & final transform:
		t.setLocalPosition(Vector3(0, 2.8, 0));
		t.setLocalScale(Vector3(0, 0, 1.0));
		headsp.addTransform(t);

		////Now use the profile and sweep path to create the head:
		head = new GameObject(app);
		head->setMesh(new Sweep(headProfile, headsp, false));
		head->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		head->getTransform()->setParent(body->getTransform());			//add to a joint later!
		head->getTransform()->name = "Head";

		//		<< RIGHT ARM >>

		//	< ARM - Shoulder >


		std::vector<Vector3> armProfile_shoulder;
		//curve at the top
		armProfile_shoulder.push_back(Vector3(2.5f, 0.0f, 0.0f));
		armProfile_shoulder.push_back(Vector3(2.25f, 0.95f, 0.0f));
		armProfile_shoulder.push_back(Vector3(1.75f, 1.75f, 0.0f));
		armProfile_shoulder.push_back(Vector3(0.95f, 2.25f, 0.0f));
		armProfile_shoulder.push_back(Vector3(0.0f, 2.5f, 0.0f));
		armProfile_shoulder.push_back(Vector3(-0.95f, 2.25f, 0.0f));
		armProfile_shoulder.push_back(Vector3(-1.75f, 1.75f, 0.0f));
		armProfile_shoulder.push_back(Vector3(-2.25f, 0.95f, 0.0f));
		armProfile_shoulder.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		//square part of shoulder
		armProfile_shoulder.push_back(Vector3(-2.5f, -4.0f, 0.0f));
		armProfile_shoulder.push_back(Vector3(-1.75f, -5.75f, 0.0f));
		armProfile_shoulder.push_back(Vector3(1.75f, -5.75f, 0.0f));
		armProfile_shoulder.push_back(Vector3(2.5f, -4.0f, 0.0f));



		SweepPath armsp_shoulder;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_shoulder.addTransform(t);

		//2nd transform:
		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_shoulder.addTransform(t);
		armsp_shoulder.addTransform(t);

		//3rd transform:
		t.setLocalPosition(Vector3(2, 0, 0));
		armsp_shoulder.addTransform(t);
		armsp_shoulder.addTransform(t);

		//4th transform:
		t.setLocalScale(Vector3(0.8, 0.8, 1.0));
		armsp_shoulder.addTransform(t);
		armsp_shoulder.addTransform(t);

		//5th transfrom:
		t.setLocalPosition(Vector3(2.5, 0, 0));
		t.setLocalScale(Vector3(0.6, 0.6, 1.0));
		armsp_shoulder.addTransform(t);

		//6th transfrom:
		t.setLocalScale(Vector3(0, 0, 1.0));
		armsp_shoulder.addTransform(t);


		//create the object:
		rightArm = new GameObject(app);
		rightArm->setMesh(new Sweep(armProfile_shoulder, armsp_shoulder, false));
		rightArm->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		rightArm->getTransform()->setLocalScale(Vector3(0.3, 0.3, 0.3));
		rightArm->getTransform()->setParent(body->getTransform());			//add to a joint later! (this probably will become the joint actually)
		rightArm->getTransform()->name = "RightArm";



		//	< ARM - Long Part >


		std::vector<Vector3> armProfile_long;
		//curve at the top
		armProfile_long.push_back(Vector3(-1.75f, 0.0f, 0.0f));
		armProfile_long.push_back(Vector3(-1.75f, -10.0f, 0.0f));
		armProfile_long.push_back(Vector3(1.75f, -10.0f, 0.0f));
		armProfile_long.push_back(Vector3(1.75f, 0.0f, 0.0f));


		SweepPath armsp_long;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_long.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_long.addTransform(t);
		armsp_long.addTransform(t);

		t.setLocalPosition(Vector3(2, 0, 0));
		armsp_long.addTransform(t);
		armsp_long.addTransform(t);

		t.setLocalScale(Vector3(0.8, 1, 1));
		armsp_long.addTransform(t);
		armsp_long.addTransform(t);

		t.setLocalPosition(Vector3(2.5f, 0.0f, 0));
		armsp_long.addTransform(t);
		armsp_long.addTransform(t);

		t.setLocalScale(Vector3(0.7, 1, 1));
		t.setLocalPosition(Vector3(2.5, 0, 0));
		armsp_long.addTransform(t);

		t.setLocalScale(Vector3(0.6, 0, 1));
		t.setLocalPosition(Vector3(3, 0, 0));
		armsp_long.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 1));
		armsp_long.addTransform(t);


		//create the object:
		rightArmLong = new GameObject(app);
		rightArmLong->setMesh(new Sweep(armProfile_long, armsp_long, false));
		rightArmLong->getTransform()->setLocalPosition(Vector3(0, -1, 0));
		rightArmLong->getTransform()->setLocalScale(Vector3(1, 1, 1));
		rightArmLong->getTransform()->setParent(rightArm->getTransform());			//attatched to shoulder
		rightArmLong->getTransform()->name = "RightArmLong";
		

		//	< ARM - Stub >

		std::vector<Vector3> armProfile_stub;
		//curve at the top
		armProfile_stub.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		armProfile_stub.push_back(Vector3(-2.5f, -0.2f, 0.0f));
		armProfile_stub.push_back(Vector3(-2.4f, -0.2f, 0.0f));
		armProfile_stub.push_back(Vector3(-2.4f, -4.0f, 0.0f));
		armProfile_stub.push_back(Vector3(0.0f, -6.0f, 0.0f));//triangle point
		armProfile_stub.push_back(Vector3(2.4f, -4.0f, 0.0f));
		armProfile_stub.push_back(Vector3(2.4f, -0.2f, 0.0f));
		armProfile_stub.push_back(Vector3(2.5f, -0.2f, 0.0f));
		armProfile_stub.push_back(Vector3(2.5f, 0.0f, 0.0f));

		SweepPath armsp_stub;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_stub.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_stub.addTransform(t);
		armsp_stub.addTransform(t);

		t.setLocalPosition(Vector3(2.4, 0, 0));
		armsp_stub.addTransform(t);
		armsp_stub.addTransform(t);

		t.setLocalPosition(Vector3(2.5, 0, 0));
		t.setLocalScale(Vector3(0.8, 1, 1));
		armsp_stub.addTransform(t);

		t.setLocalPosition(Vector3(3.0f, 0.0f, 0));
		t.setLocalScale(Vector3(0, 0.5, 1));
		armsp_stub.addTransform(t);

		//create the object:
		rightArmStub = new GameObject(app);
		rightArmStub->setMesh(new Sweep(armProfile_stub, armsp_stub, false));
		rightArmStub->getTransform()->setLocalPosition(Vector3(0, -10, 0));
		rightArmStub->getTransform()->setLocalScale(Vector3(1, 1, 1));
		rightArmStub->getTransform()->setParent(rightArmLong->getTransform());			//attatched to long part
		rightArmStub->getTransform()->name = "RightArmStub";

		//	< RIGHT FOOT >

		std::vector<Vector3> footProfile;
		//curve at the top
		footProfile.push_back(Vector3(-2.0f, -3.0f, 0.0f));
		footProfile.push_back(Vector3(2.0f, -3.0f, 0.0f));
		footProfile.push_back(Vector3(2.0f, 3.0f, 0.0f));
		footProfile.push_back(Vector3(-2.0f, 3.0f, 0.0f));


		SweepPath footsp;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0.3, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90,0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		footsp.addTransform(t);
		footsp.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		footsp.addTransform(t);
		footsp.addTransform(t);

		t.setLocalPosition(Vector3(0, -4, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp.addTransform(t);
		footsp.addTransform(t);

		t.setLocalPosition(Vector3(0, -4.5, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp.addTransform(t);
		footsp.addTransform(t);

		t.setLocalPosition(Vector3(0, -5, 0));
		t.setLocalScale(Vector3(1.5, 1.8, 1.0));
		footsp.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 0));
		footsp.addTransform(t);

		//create the object:
		rightFoot = new GameObject(app);
		rightFoot->setMesh(new Sweep(footProfile, footsp, false));
		rightFoot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		rightFoot->getTransform()->setLocalScale(Vector3(1, 1, 1));
		rightFoot->getTransform()->setParent(rightArmStub->getTransform());			//attatched to stub
		rightFoot->getTransform()->name = "RightFoot";

		//duplicate the arm..




		//		<< LEFT ARM >>

		//	< ARM - Shoulder >


		std::vector<Vector3> armProfile_shoulder2;
		//curve at the top
		armProfile_shoulder2.push_back(Vector3(2.5f, 0.0f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(2.25f, 0.95f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(1.75f, 1.75f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(0.95f, 2.25f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(0.0f, 2.5f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(-0.95f, 2.25f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(-1.75f, 1.75f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(-2.25f, 0.95f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		//square part of shoulder
		armProfile_shoulder2.push_back(Vector3(-2.5f, -4.0f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(-1.75f, -5.75f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(1.75f, -5.75f, 0.0f));
		armProfile_shoulder2.push_back(Vector3(2.5f, -4.0f, 0.0f));



		SweepPath armsp_shoulder2;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_shoulder2.addTransform(t);

		//2nd transform:
		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_shoulder2.addTransform(t);
		armsp_shoulder2.addTransform(t);

		//3rd transform:
		t.setLocalPosition(Vector3(2, 0, 0));
		armsp_shoulder2.addTransform(t);
		armsp_shoulder2.addTransform(t);

		//4th transform:
		t.setLocalScale(Vector3(0.8, 0.8, 1.0));
		armsp_shoulder2.addTransform(t);
		armsp_shoulder2.addTransform(t);

		//5th transfrom:
		t.setLocalPosition(Vector3(2.5, 0, 0));
		t.setLocalScale(Vector3(0.6, 0.6, 1.0));
		armsp_shoulder2.addTransform(t);

		//6th transfrom:
		t.setLocalScale(Vector3(0, 0, 1.0));
		armsp_shoulder2.addTransform(t);


		//create the object:
		leftArm = new GameObject(app);
		leftArm->setMesh(new Sweep(armProfile_shoulder2, armsp_shoulder2, false));
		leftArm->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		leftArm->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 180, 0)));
		leftArm->getTransform()->setLocalScale(Vector3(0.3, 0.3, 0.3));
		leftArm->getTransform()->setParent(body->getTransform());			//add to a joint later! (this probably will become the joint actually)
		leftArm->getTransform()->name = "LeftArm";



		//	< ARM - Long Part >


		std::vector<Vector3> armProfile_long2;
		//curve at the top
		armProfile_long2.push_back(Vector3(-1.75f, 0.0f, 0.0f));
		armProfile_long2.push_back(Vector3(-1.75f, -10.0f, 0.0f));
		armProfile_long2.push_back(Vector3(1.75f, -10.0f, 0.0f));
		armProfile_long2.push_back(Vector3(1.75f, 0.0f, 0.0f));


		SweepPath armsp_long2;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_long2.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_long2.addTransform(t);
		armsp_long2.addTransform(t);

		t.setLocalPosition(Vector3(2, 0, 0));
		armsp_long2.addTransform(t);
		armsp_long2.addTransform(t);

		t.setLocalScale(Vector3(0.8, 1, 1));
		armsp_long2.addTransform(t);
		armsp_long2.addTransform(t);

		t.setLocalPosition(Vector3(2.5f, 0.0f, 0));
		armsp_long2.addTransform(t);
		armsp_long2.addTransform(t);

		t.setLocalScale(Vector3(0.7, 1, 1));
		t.setLocalPosition(Vector3(2.5, 0, 0));
		armsp_long2.addTransform(t);

		t.setLocalScale(Vector3(0.6, 0, 1));
		t.setLocalPosition(Vector3(3, 0, 0));
		armsp_long2.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 1));
		armsp_long2.addTransform(t);


		//create the object:
		leftArmLong = new GameObject(app);
		leftArmLong->setMesh(new Sweep(armProfile_long2, armsp_long2, false));
		leftArmLong->getTransform()->setLocalPosition(Vector3(0, -1, 0));
		leftArmLong->getTransform()->setLocalScale(Vector3(1, 1, 1));
		leftArmLong->getTransform()->setParent(leftArm->getTransform());			//attatched to shoulder
		leftArmLong->getTransform()->name = "LeftArmLong";


		//	< ARM - Stub >

		std::vector<Vector3> armProfile_stub2;
		//curve at the top
		armProfile_stub2.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		armProfile_stub2.push_back(Vector3(-2.5f, -0.2f, 0.0f));
		armProfile_stub2.push_back(Vector3(-2.4f, -0.2f, 0.0f));
		armProfile_stub2.push_back(Vector3(-2.4f, -4.0f, 0.0f));
		armProfile_stub2.push_back(Vector3(0.0f, -6.0f, 0.0f));//triangle point
		armProfile_stub2.push_back(Vector3(2.4f, -4.0f, 0.0f));
		armProfile_stub2.push_back(Vector3(2.4f, -0.2f, 0.0f));
		armProfile_stub2.push_back(Vector3(2.5f, -0.2f, 0.0f));
		armProfile_stub2.push_back(Vector3(2.5f, 0.0f, 0.0f));

		SweepPath armsp_stub2;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 90, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp_stub2.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		armsp_stub2.addTransform(t);
		armsp_stub2.addTransform(t);

		t.setLocalPosition(Vector3(2.4, 0, 0));
		armsp_stub2.addTransform(t);
		armsp_stub2.addTransform(t);

		t.setLocalPosition(Vector3(2.5, 0, 0));
		t.setLocalScale(Vector3(0.8, 1, 1));
		armsp_stub2.addTransform(t);

		t.setLocalPosition(Vector3(3.0f, 0.0f, 0));
		t.setLocalScale(Vector3(0, 0.5, 1));
		armsp_stub2.addTransform(t);

		//create the object:
		leftArmStub = new GameObject(app);
		leftArmStub->setMesh(new Sweep(armProfile_stub2, armsp_stub2, false));
		leftArmStub->getTransform()->setLocalPosition(Vector3(0, -10, 0));
		leftArmStub->getTransform()->setLocalScale(Vector3(1, 1, 1));
		leftArmStub->getTransform()->setParent(leftArmLong->getTransform());			//attatched to long part
		leftArmStub->getTransform()->name = "LeftArmStub";

		//	< LEFT FOOT >

		std::vector<Vector3> footProfile2;
		//curve at the top
		footProfile2.push_back(Vector3(-2.0f, -3.0f, 0.0f));
		footProfile2.push_back(Vector3(2.0f, -3.0f, 0.0f));
		footProfile2.push_back(Vector3(2.0f, 3.0f, 0.0f));
		footProfile2.push_back(Vector3(-2.0f, 3.0f, 0.0f));


		SweepPath footsp2;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0.3, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		footsp2.addTransform(t);
		footsp2.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		footsp2.addTransform(t);
		footsp2.addTransform(t);

		t.setLocalPosition(Vector3(0, -4, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp2.addTransform(t);
		footsp2.addTransform(t);

		t.setLocalPosition(Vector3(0, -4.5, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp2.addTransform(t);
		footsp2.addTransform(t);

		t.setLocalPosition(Vector3(0, -5, 0));
		t.setLocalScale(Vector3(1.5, 1.8, 1.0));
		footsp2.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 0));
		footsp2.addTransform(t);

		//create the object:
		leftFoot = new GameObject(app);
		leftFoot->setMesh(new Sweep(footProfile2, footsp2, false));
		leftFoot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		leftFoot->getTransform()->setLocalScale(Vector3(1, 1, 1));
		leftFoot->getTransform()->setParent(leftArmStub->getTransform());			//attatched to stub
		leftFoot->getTransform()->name = "LeftFoot";

		//	< BUM >

		//////sweep profile for the BUM of the R2D2
		std::vector<Vector3> bumProfile;
		bumProfile.push_back(Vector3(-1.75f, -1.75f, 0.0f));
		bumProfile.push_back(Vector3(-2.25f, -0.95f, 0.0f));
		bumProfile.push_back(Vector3(-2.5f, 0.0f, 0.0f));
		bumProfile.push_back(Vector3(-2.25f, 0.95f, 0.0f));
		bumProfile.push_back(Vector3(-1.75f, 1.75f, 0.0f));
		bumProfile.push_back(Vector3(-0.95f, 2.25f, 0.0f));
		bumProfile.push_back(Vector3(0.0f, 2.5f, 0.0f));
		bumProfile.push_back(Vector3(0.95f, 2.25f, 0.0f));
		bumProfile.push_back(Vector3(1.75f, 1.75f, 0.0f));
		bumProfile.push_back(Vector3(2.25f, 0.95f, 0.0f));
		bumProfile.push_back(Vector3(2.5f, 0.0f, 0.0f));
		bumProfile.push_back(Vector3(2.25f, -0.95f, 0.0f));
		bumProfile.push_back(Vector3(1.75f, -1.75f, 0.0f));
		bumProfile.push_back(Vector3(0.95f, -2.25f, 0.0f));
		bumProfile.push_back(Vector3(0.0f, -2.5f, 0.0f));
		bumProfile.push_back(Vector3(-0.95, -2.25f, 0.0f));

		SweepPath bumsp;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		bumsp.addTransform(t);

		//2nd transform: (begin the rim where bum joins to body)
		t.setLocalScale(Vector3(1.03, 1.03, 1.0)); // Rim width
		bumsp.addTransform(t);
		bumsp.addTransform(t);

		//3rd transform:
		t.setLocalPosition(Vector3(0, 0.3, 0)); //rim height
		bumsp.addTransform(t);
		bumsp.addTransform(t);

		//4th transform: (finish the rim)
		t.setLocalScale(Vector3(1.0, 1.0, 1.0)); // Rim width
		bumsp.addTransform(t);
		bumsp.addTransform(t);

		//5th transfrom: (begin recessing to build rest of bum shape)
		t.setLocalPosition(Vector3(0, 1.25, 0));
		t.setLocalScale(Vector3(0.9, 0.9, 1.0));
		bumsp.addTransform(t);

		//6th transfrom:
		t.setLocalPosition(Vector3(0, 2.05, 0));
		t.setLocalScale(Vector3(0.7, 0.7, 1.0));
		bumsp.addTransform(t);

		//7th transfrom:
		t.setLocalPosition(Vector3(0, 2.55, 0));
		t.setLocalScale(Vector3(0.38, 0.38, 1.0));
		bumsp.addTransform(t);

		//8th & final transform:
		t.setLocalPosition(Vector3(0, 2.8, 0));
		t.setLocalScale(Vector3(0, 0, 1.0));
		bumsp.addTransform(t);

		////Now use the profile and sweep path to create the bum:
		bum = new GameObject(app);
		bum->setMesh(new Sweep(bumProfile, bumsp, false));
		bum->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 180, 0, 0)));
		bum->getTransform()->setLocalPosition(Vector3(0, -2.5, 0));
		bum->getTransform()->setLocalScale(Vector3(1, 0.5, 1));
		bum->getTransform()->setParent(body->getTransform());			//add to a joint later!
		bum->getTransform()->name = "Bum";

		//	< BUM FOOT - for the midle (bum)>

		std::vector<Vector3> footProfile3;
		//curve at the top
		footProfile3.push_back(Vector3(-2.0f, -3.0f, 0.0f));
		footProfile3.push_back(Vector3(2.0f, -3.0f, 0.0f));
		footProfile3.push_back(Vector3(2.0f, 3.0f, 0.0f));
		footProfile3.push_back(Vector3(-2.0f, 3.0f, 0.0f));


		SweepPath footsp3;
		//Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(0, 0.3, 0));
		t.setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 90, 0, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		footsp3.addTransform(t);
		footsp3.addTransform(t);

		t.setLocalScale(Vector3(1.0, 1.0, 1.0));
		footsp3.addTransform(t);
		footsp3.addTransform(t);

		t.setLocalPosition(Vector3(0, -4, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp3.addTransform(t);
		footsp3.addTransform(t);

		t.setLocalPosition(Vector3(0, -4.5, 0));
		t.setLocalScale(Vector3(1.5, 2.0, 1.0));
		footsp3.addTransform(t);
		footsp3.addTransform(t);

		t.setLocalPosition(Vector3(0, -5, 0));
		t.setLocalScale(Vector3(1.5, 1.8, 1.0));
		footsp3.addTransform(t);

		t.setLocalScale(Vector3(0, 0, 0));
		footsp3.addTransform(t);

		//create the object:
		bumFoot = new GameObject(app);
		bumFoot->setMesh(new Sweep(footProfile3, footsp3, false));
		bumFoot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		bumFoot->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 180, 0, 0)));
		bumFoot->getTransform()->setLocalScale(Vector3(0.4, 0.5, 0.3));
		bumFoot->getTransform()->setParent(bum->getTransform());			//attatched to stub
		bumFoot->getTransform()->name = "BumFoot";

		//	< EYE >
		eye = new GameObject(app);
		eye->setMesh(new Cylinder(0.5, 0.5, 16));
		eye->getTransform()->setLocalPosition(Vector3(0, 1.3, 1.8));
		eye->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 70, 0, 0)));
		eye->getTransform()->setLocalScale(Vector3(1, 1, 1.0));
		eye->getTransform()->name = "Eye";
		eye->getTransform()->setParent(head->getTransform());

		//	< JOINTS >

		headJoint = new GameObject(app);
		headJoint->getTransform()->setParent(body->getTransform());
		headJoint->getTransform()->setLocalPosition(Vector3(0, 2.5, 0));
		headJoint->getTransform()->name = "HeadJoint";
		head->getTransform()->setParent(headJoint->getTransform());

		rightArmJoint = new GameObject(app);
		rightArmJoint->getTransform()->setParent(getTransform());
		rightArmJoint->getTransform()->setLocalPosition(Vector3(2.5, 1.75, 0));
		rightArmJoint->getTransform()->name = "RightArmJoint";
		rightArm->getTransform()->setParent(rightArmJoint->getTransform());

		rightFootJoint = new GameObject(app);
		rightFootJoint->getTransform()->setParent(rightArmStub->getTransform());
		rightFootJoint->getTransform()->setLocalPosition(Vector3(1, -5, 0));
		rightFootJoint->getTransform()->name = "RightFootJoint";
		rightFoot->getTransform()->setParent(rightFootJoint->getTransform());

		leftArmJoint = new GameObject(app);
		leftArmJoint->getTransform()->setParent(getTransform());
		leftArmJoint->getTransform()->setLocalPosition(Vector3(-2.5, 1.75, 0));
		leftArmJoint->getTransform()->name = "LeftArmJoint";
		leftArm->getTransform()->setParent(leftArmJoint->getTransform());

		leftFootJoint = new GameObject(app);
		leftFootJoint->getTransform()->setParent(leftArmStub->getTransform());
		leftFootJoint->getTransform()->setLocalPosition(Vector3(1, -5, 0));
		leftFootJoint->getTransform()->name = "LeftFootJoint";
		leftFoot->getTransform()->setParent(leftFootJoint->getTransform());

		bumFootJoint = new GameObject(app);
		bumFootJoint->getTransform()->setParent(bum->getTransform());
		bumFootJoint->getTransform()->setLocalPosition(Vector3(0, 1.8, 0));
		bumFootJoint->getTransform()->name = "BumFootJoint";
		bumFoot->getTransform()->setParent(bumFootJoint->getTransform());

		//ROOT
		body->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 180, 0)));
		setMesh(new Cube(0.1));
		body->getTransform()->setParent(getTransform());
		getTransform()->name = "R2D2";

	}

	R2D2::~R2D2(void) {

	}

	void R2D2::walkingPos(float time, float speed)
	{
		if (time > 10)
			time = 10;//max 10 seconds!
		Animation *anim = new Animation(10.0);
		addComponent(anim);
		std::string name;
		Vector3 pos;
		Quaternion startRot;
		Quaternion endRot;
		float degrees;

		pos = getTransform()->getLocalPosition();
		name = getTransform()->name;
		startRot = getTransform()->getRotationMatrix();
		degrees = -10 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = rightArmJoint->getTransform()->getLocalPosition();
		name = rightArmJoint->getTransform()->name;
		startRot = rightArmJoint->getTransform()->getRotationMatrix();
		degrees = 20 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = rightFootJoint->getTransform()->getLocalPosition();
		name = rightFootJoint->getTransform()->name;
		startRot = rightFootJoint->getTransform()->getRotationMatrix();
		degrees = -8 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = leftArmJoint->getTransform()->getLocalPosition();
		name = leftArmJoint->getTransform()->name;
		startRot = leftArmJoint->getTransform()->getRotationMatrix();
		degrees = 20 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = leftFootJoint->getTransform()->getLocalPosition();
		name = leftFootJoint->getTransform()->name;
		startRot = leftFootJoint->getTransform()->getRotationMatrix();
		degrees = 8 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		pos = bumFootJoint->getTransform()->getLocalPosition();
		name = bumFootJoint->getTransform()->name;
		startRot = bumFootJoint->getTransform()->getRotationMatrix();
		degrees = 20 * speed;
		endRot = Quaternion(Vector3(Math::DEG2RAD * degrees, 0, 0));
		anim->addKey(name, 10.0, endRot, pos);
		anim->addKey(name, 0, startRot, pos);
		anim->addKey(name, time, endRot, pos);

		anim->play();
	}
}


