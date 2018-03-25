// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Tutorial1.cpp
//
// Base application for tutorial 1.  Used in conjunction with DrawTask, a task for drawing onto a 2D texture.

#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D{

	class Tutorial1 :
		public WinGLApplication
	{
	public:
		Tutorial1(void);
		~Tutorial1(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}

