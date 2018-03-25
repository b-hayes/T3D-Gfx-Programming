#include "Lamp.h"
#include "Math.h"
#include "SweepPath.h"
#include "Sweep.h"

namespace T3D {
	Lamp::Lamp(T3DApplication *app) :GameObject(app) {
		setMesh(new Cylinder(.1, .01, 16));
		getTransform()->name = "Lamp";

		//small cylinder that is the arm attachment point.
		base = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
		//Cylinder(float radius, float height, int density)
		base->setMesh(new Cylinder(.02, .01, 16));
		base->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
		base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
		base->getTransform()->name = "Base";

		//sweep profile for the arm of the lamp
		std::vector<Vector3> armProfile;
		armProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
		armProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
		armProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
		armProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
		armProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
		armProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));

		SweepPath armsp;
		Transform t;

		//create the first transform:
		t.setLocalPosition(Vector3(-0.01, 0, 0));
		t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
		t.setLocalScale(Vector3(0, 0, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Adjust the scale for the next path instance:
		t.setLocalScale(Vector3(0.9, 1, 1.0));
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Adjust the position and scale for the next path instance:
		t.setLocalPosition(Vector3(-0.0075, 0, 0));
		t.setLocalScale(Vector3(1, 1, 1.0));
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Adjust the position for the next path instance:
		t.setLocalPosition(Vector3(0.0075, 0, 0));
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Adjust the position for the next path instance:
		t.setLocalPosition(Vector3(0.01, 0, 0));
		t.setLocalScale(Vector3(0.9, 1, 1.0));
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Adjust the scale for the final cap:
		t.setLocalScale(Vector3(0, 0, 1.0));
		armsp.addTransform(t);
		//adding some duplicate transforms to the SweepPath so it has the sharp bevel look
		armsp.addTransform(t);

		//Now use the profile and sweep path to create the first arm:
		arm1 = new GameObject(app);
		arm1->setMesh(new Sweep(armProfile, armsp, false));
		arm1->getTransform()->setLocalPosition(Vector3(0, 0.114, 0)); // not correctly positioned yet
		arm1->getTransform()->setParent(base->getTransform()); // not correct attachment yet
		arm1->getTransform()->name = "Arm1";

		//Create the second arm:
		arm2 = new GameObject(app);
		arm2->setMesh(new Sweep(armProfile, armsp, false));
		arm2->getTransform()->setLocalPosition(Vector3(0, 0.114*3, 0)); // not correctly positioned yet
		arm2->getTransform()->setParent(base->getTransform()); // not correct attachment yet
		arm2->getTransform()->name = "Arm2";
		

		//add two 'empty' game objects for the joints and attach the arms to these joints (with an appropriate offset). Any animation will be performed on the joints, not on the arms directly. 
		//create the joints:
		baseJoint = new GameObject(app);
		baseJoint->getTransform()->setParent(base->getTransform());
		baseJoint->getTransform()->name = "BaseJoint";

		elbowJoint = new GameObject(app);
		elbowJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		elbowJoint->getTransform()->setParent(baseJoint->getTransform());
		elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
		elbowJoint->getTransform()->name = "ElbowJoint";

		shadeJoint = new GameObject(app);
		shadeJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
		shadeJoint->getTransform()->setParent(elbowJoint->getTransform());
		shadeJoint->getTransform()->name = "ShadeJoint";

		//Now arm1 will be attached to baseJoint with a 10cm offset in the y-direction so that when the joint is rotated, the arm will rotate around the correct point.
		arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm1->getTransform()->setParent(baseJoint->getTransform());

		//arm2 goes on the elbow joint
		arm2->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
		arm2->getTransform()->setParent(elbowJoint->getTransform());

		////lamp shade using sweep profile
		//SweepPath shadesp;
		////sweep profile for the Shade
		//std::vector<Vector3> shadeProfile;
		//shadeProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
		//shadeProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
		//shadeProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
		//shadeProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
		//shadeProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
		//shadeProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
		//shadeProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
		//shadeProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
		//shadeProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
		//shadeProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));

		////Now use the profile and sweep path to create the shade object:
		//arm1 = new GameObject(app);
		//arm1->setMesh(new Sweep(armProfile, armsp, false));
		//arm1->getTransform()->setLocalPosition(Vector3(0, 0.114, 0)); // not correctly positioned yet
		//arm1->getTransform()->setParent(base->getTransform()); // not correct attachment yet
		//arm1->getTransform()->name = "Arm1";

		
	}

}


