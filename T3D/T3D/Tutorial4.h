
#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D {

	class Tutorial4 :
		public WinGLApplication
	{
	public:
		Tutorial4(void);
		~Tutorial4(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}
