#include "Tutorial4.h"
#include "Camera.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "KeyboardController.h"
#include "R2D2.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Propeller.h"
#include "AnimationTest.h"
#include "Animation.h"

namespace T3D {

	Tutorial4::Tutorial4(void)
	{
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	Tutorial4::~Tutorial4(void)
	{
	}

	bool Tutorial4::init() {
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
		
		//R2D2 <TASK 1 & 2>
		/*
		NOTE: The head (dome shape) of R2D2 addreses TASK 1
		It was made with 16 points and 8 transforms instead of using a Sphear.
		*/
		R2D2 * r2d2 = new R2D2(this);

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

		r2d2->getTransform()->setLocalScale(Vector3(1, 1, 1));// size
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
		
//		AnimationTest *animTask = new AnimationTest(this);
//		animTask->R2D2 = r2d2->getTransform();
//		addTask(animTask);
		
		Animation *anim = new Animation(10.0);
		r2d2->addComponent(anim);
		Vector3 pos = r2d2->rightArmJoint->getTransform()->getLocalPosition();
		anim->addKey(r2d2->rightArmJoint->getTransform()->name, 10.0, Quaternion(Vector3(0, 0, 0)), pos);
		anim->addKey(r2d2->rightArmJoint->getTransform()->name, 0, Quaternion(Vector3(0, 0, 0)), pos);
		anim->addKey(r2d2->rightArmJoint->getTransform()->name, 7.0, Quaternion(Vector3(Math::HALF_PI, 0, 0)),pos);
		anim->addKey(r2d2->rightArmJoint->getTransform()->name, 5.0, Quaternion(Vector3(-Math::HALF_PI, 0, 0)), pos);
		pos = r2d2->leftArmJoint->getTransform()->getLocalPosition();
		anim->addKey(r2d2->leftArmJoint->getTransform()->name, 10.0, Quaternion(Vector3(0, 0, 0)), pos);
		anim->addKey(r2d2->leftArmJoint->getTransform()->name, 0, Quaternion(Vector3(0, 0, 0)), pos);
		anim->addKey(r2d2->leftArmJoint->getTransform()->name, 7.0, Quaternion(Vector3(0, 0, Math::HALF_PI)), pos);
		anim->addKey(r2d2->leftArmJoint->getTransform()->name, 5.0, Quaternion(Vector3(0, 0, -Math::HALF_PI)), pos);
		anim->loop(true);
		anim->play();

		return true;
	}

}
