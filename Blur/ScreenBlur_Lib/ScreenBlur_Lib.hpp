#pragma once

#ifndef _SCREENBLUR_LIB_HPP
#define _SCREENBLUR_LIB_HPP

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
		int m_offsetX1, m_offsetX2, m_offsetY1, m_offsetY2;
		int m_notBlendDraw;


	public:
		ScreenBlur();
		~ScreenBlur() {}


		void Init(const int t_winWidth, const int t_winHeight, const int t_alpha
			, const int t_offsetX1, const int t_offsetY1, const int t_offsetX2, const int t_offsetY2);
		void ReplayInit();
		void Release();

		void PreRenderBlurScreen();

		void PostRenderBlurScreen();
	};
}

#endif