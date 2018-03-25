#include "Assignment1Test.h"
#include "Camera.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "KeyboardController.h"
#include "R2D2.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Propeller.h"
#include "Robot.h"

namespace T3D {

	Assignment1Test::Assignment1Test(void)
	{
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	Assignment1Test::~Assignment1Test(void)
	{
	}

	bool Assignment1Test::init() {
		WinGLApplication::init();

		Light *light = new Light(Light::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);

		GameObject *lightObj = new GameObject(this);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
		camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController());
		
		//materials
		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8, 0.8, 0.9, 1);
		Material *blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0, 0, 0.9, 1);
		Material *white = renderer->createMaterial(Renderer::PR_OPAQUE);
		white->setDiffuse(1, 1, 1, 1);
		Material *black = renderer->createMaterial(Renderer::PR_OPAQUE);
		black->setDiffuse(0.0, 0.0, 0.0, 1);
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0.0, 1, 0.0, 1);
		Material *orange = renderer->createMaterial(Renderer::PR_OPAQUE);
		orange->setDiffuse(1, 0.5, 0.0, 1);



		//R2D2 <TASK 1 & 2>
		/*
		NOTE: The head (dome shape) of R2D2 addreses TASK 1
		It was made with 16 points and 8 transforms instead of using a Sphear.
		*/
		R2D2 * r2d2 = new R2D2(this);

		r2d2->getTransform()->setLocalScale(Vector3(5, 5, 5));// size
		r2d2->setMaterial(white); //should be white
		r2d2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		r2d2->getTransform()->setParent(root);

		//You need to set the materials of sub-objects separately
		r2d2->head->setMaterial(grey); //TODO: should be silver
		r2d2->eye->setMaterial(black);
		r2d2->rightArm->setMaterial(white);
		r2d2->rightArmLong->setMaterial(blue);
		r2d2->rightArmStub->setMaterial(white);
		r2d2->rightFoot->setMaterial(white);
		r2d2->leftArm->setMaterial(white);
		r2d2->leftArmLong->setMaterial(blue);
		r2d2->leftArmStub->setMaterial(white);
		r2d2->leftFoot->setMaterial(white);
		r2d2->bum->setMaterial(white);
		r2d2->bumFoot->setMaterial(white);
		

		//rotating the joints
		r2d2->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *-10, 0, 0)));
		r2d2->headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::DEG2RAD * 30, 0)));
		r2d2->rightArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *20, 0, 0)));
		r2d2->rightFootJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *-8, 0, 0)));
		r2d2->leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 20, 0, 0)));
		r2d2->leftFootJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *8, 0, 0)));//should alwasy be the negertive of the other foot to keep on same level (because entire arm has been rotated180deg to go on the other side)
		r2d2->bumFootJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *20, 0, 0)));



		//PROPELLA < TASK 3>
		GameObject *prop = new GameObject(this);
		//propeller(radius, hubRadius, height, attackAngle, blades, density)
		prop->setMesh(new Propeller(30, 10, 5, 10, 5, 30));
		prop->getTransform()->setLocalPosition(Vector3(0, 50, 0));
		prop->setMaterial(green);
		prop->getTransform()->setParent(root);



		//ROBOT <TASK 5>
		Robot * robot = new Robot(this);

		robot->getTransform()->setLocalScale(Vector3(5, 5, 5));// size
		robot->setMaterial(orange);
		robot->getTransform()->setLocalPosition(Vector3(100, 0, 0));
		robot->getTransform()->setParent(root);

		//You need to set the materials of sub-objects separately
		robot->head->setMaterial(orange);
		robot->neck->setMaterial(orange);
		robot->eye1->setMaterial(white);
		robot->eye2->setMaterial(white);
		robot->mouth->setMaterial(white);
		robot->rightArmJoint->setMaterial(orange);
		robot->rightArmShoulder->setMaterial(orange);
		robot->rightElbowJoint->setMaterial(orange);
		robot->rightForarm->setMaterial(orange);
		robot->rightWristJoint->setMaterial(orange);
		robot->rightHand->setMaterial(orange);
		robot->leftArmJoint->setMaterial(orange);
		robot->leftArmShoulder->setMaterial(orange);
		robot->leftElbowJoint->setMaterial(orange);
		robot->leftForarm->setMaterial(orange);
		robot->leftWristJoint->setMaterial(orange);
		robot->leftHand->setMaterial(orange);
		robot->treadJoint->setMaterial(orange);
		robot->treadBase->setMaterial(orange);
		robot->rightTread->setMaterial(black);
		robot->leftTread->setMaterial(black);
		


		//rotating the joints
		robot->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD *10, 0, 0)));
		robot->headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -40, Math::DEG2RAD * 20, Math::DEG2RAD * -20)));
		robot->rightArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -70, Math::DEG2RAD * 40, Math::DEG2RAD * 20)));
		robot->rightElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -70, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
		robot->rightWristJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -30, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
		robot->leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 30, Math::DEG2RAD * 0, Math::DEG2RAD * 0)));
		robot->leftElbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -75, Math::DEG2RAD * 10, Math::DEG2RAD * 0)));
		robot->leftWristJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * -20, Math::DEG2RAD * 20, Math::DEG2RAD * 0)));
		robot->treadJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::DEG2RAD * 20, Math::DEG2RAD * 10, Math::DEG2RAD * 0)));
		
		return true;
	}

}
