
#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D {

	class Assignment2Test :
		public WinGLApplication
	{
	public:
		Assignment2Test(void);
		~Assignment2Test(void);
		
		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}
