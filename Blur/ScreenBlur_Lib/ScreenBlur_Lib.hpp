#pragma once

#include "DxLib.h"


namespace ScreenBlur_Lib
{
	class ScreenBlur
	{
	private:
		int m_screen[2];
		int m_current;
		int m_alpha;
		int m_screenWidth, m_screenHeight;
		int m_offsetX1, m_offsetX2, m_offsetY1, offsetY2;
		int m_notBlendDraw;


	public:
		ScreenBlur();
		~ScreenBlur() {}


		void Init(int alpha, int offsetX1, int offsetY1, int offsetX2, int offsetY2);
		void ReplayInit();
		void Release();

		void PreRenderBlurScreen();

		void PostRenderBlurScreen();
	};
}