

#pragma once

#include "../../../Includes.h"

namespace sur
{

	class Renderer 
	{
	private:
		
		HDC dc;
		bool fillBackground;		
		volatile u32 frameCounter = 0;

	public:
		
		Renderer(Color background, bool fillBackground, f32 ambient_light, bool use_light);

		void Clear() const;

		void Render();

		void FPS();

		void DebugConsole(bool show) const;

	};

}