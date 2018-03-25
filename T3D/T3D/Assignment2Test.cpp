#include "Assignment2Test.h"
#include "Camera.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "KeyboardController.h"
#include "R2D2.h"
#include "SweepPath.h"
#include "Sweep.h"
#include "Propeller.h"
#include "Robot.h"
#include "Animation.h"
#include "Cube.h"
#include "Terrain.h"
#include "Xwing.h"
#include "AnimationTest.h"
#include "TCylinder.h"
#include "Billboard.h"

namespace T3D {
	class Xwing;

	Assignment2Test::Assignment2Test(void)
	{
		drawArea = new Texture(1024, 640, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}


	Assignment2Test::~Assignment2Test(void)
	{
	}

	bool Assignment2Test::init() {
		WinGLApplication::init();

		//movie timeline..
		AnimationTest *movie = new AnimationTest(this);
		addTask(movie);

		//Create a skybox and add some fog
		renderer->loadSkybox("Resources/mandaris");
		renderer->setFog(0.002f, 0.2f, 0.0f, 0.1f, 0.5f);
		renderer->toggleFog();

		Light *light = new Light(Light::DIRECTIONAL);
		light->setAmbient(1, 1, 1);
		light->setDiffuse(1, 1, 1);
		light->setSpecular(1, 1, 1);

		GameObject *lightObj = new GameObject(this);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
		lightObj->getTransform()->setParent(root);

		//CAMERA
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 1500.0, 70.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
		camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		
		//materials
		Material *grey = renderer->createMaterial(Renderer::PR_OPAQUE);
		grey->setDiffuse(0.8, 0.8, 0.9, 1);
		Material *blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0, 0, 0.9, 1);
		Material *white = renderer->createMaterial(Renderer::PR_OPAQUE);
		white->setDiffuse(1, 1, 1, 1);
		Material *black = renderer->createMaterial(Renderer::PR_OPAQUE);
		black->setDiffuse(0.2, 0.2, 0.2, 1);
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0.0, 1, 0.0, 1);
		Material *orange = renderer->createMaterial(Renderer::PR_OPAQUE);
		orange->setDiffuse(1, 0.5, 0.0, 1);
		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1, 0.0, 0.0, 1);

		//Create a material with a procedurally generated texture
		Texture *proctex = new Texture(512, 512);
		proctex->createFractal(Colour(102, 51, 0, 255), Colour(204, 51, 0, 255), 25.0f, false);
		renderer->loadTexture(proctex, true);
		Material *procmat = renderer->createMaterial(Renderer::PR_TERRAIN);
		procmat->setTexture(proctex, 50);
		procmat->setSpecular(0, 0, 0, 0);

		//Add some terrain
		GameObject *terrain = new GameObject(this);
		Terrain *terrainComponent = new Terrain();
		terrain->addComponent(terrainComponent);
		terrainComponent->createFractalTerrain(512, 10000, 0, 0); // procedurally generate terrain
		terrain->setMaterial(procmat);
		terrain->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		terrain->getTransform()->setParent(root);
		terrain->getTransform()->name = "Terrain";
		

		//R2D2 
		R2D2 * r2d2 = new R2D2(this);

		r2d2->getTransform()->setLocalScale(Vector3(1, 1, 1));// size
		r2d2->setMaterial(white); //should be white
		r2d2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		r2d2->getTransform()->setParent(root);

		//You need to set the materials of sub-objects separately
		r2d2->body->setMaterial(white);
		r2d2->head->setMaterial(grey);
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

		//ROBOT
		Robot * robot = new Robot(this);

		robot->getTransform()->setLocalScale(Vector3(1, 1, 1));// size
		robot->setMaterial(orange);
		robot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
		robot->getTransform()->setParent(root);

		//You need to set the materials of sub-objects separately
		robot->torso->setMaterial(orange);
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

		//XWING
		Xwing * xwing = new Xwing(this);

		xwing->getTransform()->setLocalScale(Vector3(1, 1, 1));// size
		xwing->getTransform()->setLocalPosition(Vector3(0, 30, 0));
		xwing->getTransform()->setParent(root);

		//set materials
		xwing->setMaterial(grey);
		xwing->nose->setMaterial(grey);
		xwing->body->setMaterial(red);
		xwing->cockPit->setMaterial(black);
		xwing->engineMount->setMaterial(grey);
		xwing->tlEngine->setMaterial(black);
		xwing->blEngine->setMaterial(black);
		xwing->trEngine->setMaterial(black);
		xwing->brEngine->setMaterial(black);
		xwing->tlWing->setMaterial(red);
		xwing->blWing->setMaterial(red);
		xwing->trWing->setMaterial(red);
		xwing->brWing->setMaterial(red);



		//Text texture
		Texture *texttex = new Texture(128, 32);
		texttex->clear(Colour(255, 255, 255, 255));
		font *f = getFont("resources/FreeSans.ttf", 24);
		if (f != NULL) {
			texttex->writeText(2, 0, "The", Colour(255, 0, 0, 255), f->getFont());
			texttex->writeText(64, 0, "End", Colour(255, 0, 0, 0), f->getFont());
		}
		renderer->loadTexture(texttex, true);
		Material *textmat = renderer->createMaterial(Renderer::PR_OPAQUE);
		textmat->setTexture(texttex, 1);
		textmat->setEmissive(1, 1, 1, 1);

		//For the end
		GameObject *billboard = new GameObject(this);
		Billboard *billboardComponent = new Billboard(renderer->camera->gameObject->getTransform(), true);
		billboard->addComponent(billboardComponent);
		billboard->setMaterial(textmat);			// hello world
		billboard->getTransform()->setLocalPosition(Vector3(0,-20, 0));
		billboard->getTransform()->setLocalScale(Vector3(6, 1.5, 1));
		billboard->getTransform()->setParent(root);
		billboard->getTransform()->name = "Billboard";


		//animation tests...
//		xwing->openWings(10, 20);
//		r2d2->walkingPos(10, 2);
//		robot->armsUp(10, 90, 'r');
//		robot->bendElbows(10, 45, 'r');

		//set starting positions
		camObj->getTransform()->setLocalPosition(Vector3(100, 3000, -20));
		xwing->getTransform()->setLocalPosition(Vector3(500, 3500, 500));
		xwing->tlWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)));
		xwing->trWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * -20)));
		xwing->blWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)));
		xwing->brWingJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::DEG2RAD * 20)));
		robot->getTransform()->setLocalPosition(Vector3(0, -20, 0));
		r2d2->getTransform()->setLocalPosition(Vector3(0, -20, 0));

		//keyboard control for testing
//		camObj->addComponent(new KeyboardController());

		//add the 'actors' to the movie
		movie->camera = camObj;
		movie->r2d2 = r2d2;
		movie->xwing = xwing;
		movie->robot = robot;
		movie->credits = billboard;
		return true;
		//X:\_UTAS\BICT_3rd_year\KIT307 Graphics Programming\Assignment 2 - Copy
	}

}
