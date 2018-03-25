
#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D {

	class Assignment1Test :
		public WinGLApplication
	{
	public:
		Assignment1Test(void);
		~Assignment1Test(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}
