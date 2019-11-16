#include "pch.h"
#include "ScreenBlur_Lib.hpp"


namespace ScreenBlur_Lib
{
	/// ------------------------------------------------------------------------------------------------------------
	ScreenBlur::ScreenBlur()
	{
		m_screen[0] = 0;
		m_screen[1] = 0;
		m_current = 0;
		m_alpha = 0;
		m_screenWidth = 0;
		m_screenHeight = 0;
		m_offsetX1 = 0;
		m_offsetX2 = 0;
		m_offsetY1 = 0;
		m_offsetY2 = 0;
		m_notBlendDraw = 0;
	}



	/// ------------------------------------------------------------------------------------------------------------
	void ScreenBlur::Init(const int t_winWidth, const int t_winHeight, const int t_alpha, const int t_offsetX1, const int t_offsetY1, const int t_offsetX2, const int t_offsetY2)
	{
		m_screenWidth = t_winWidth;
		m_screenHeight = t_winHeight;
		for (int i = 0; i < 2; ++i)
		{
			m_screen[i] = -1;
			m_screen[i] = MakeScreen(m_screenWidth, m_screenHeight);
		}
		m_current = 0;
		m_alpha = t_alpha;
		m_offsetX1 = t_offsetX1;
		m_offsetX2 = t_offsetX2;
		m_offsetY1 = t_offsetY1;
		m_offsetY2 = t_offsetY2;

		m_notBlendDraw = 0;
	}



	/// ------------------------------------------------------------------------------------------------------------
	void ScreenBlur::ReplayInit()
	{
		for (int i = 0; i < 2; ++i)
		{
			if (m_screen[i] != -1) DeleteGraph(m_screen[i]);
			m_screen[i] = MakeScreen(m_screenWidth, m_screenHeight);
		}
		m_current = 0;

		m_notBlendDraw = 0;
	}



	/// ------------------------------------------------------------------------------------------------------------
	void ScreenBlur::Release()
	{
		for (int i = 0; i < 2; ++i)
		{
			if (m_screen[i] != -1) DeleteGraph(m_screen[i]);
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	void ScreenBlur::PreRenderBlurScreen()
	{
		SetDrawScreen(m_screen[m_current]);
		ClearDrawScreen();
	}



	/// ------------------------------------------------------------------------------------------------------------
	void ScreenBlur::PostRenderBlurScreen()
	{
		int drawMode = GetDrawMode();
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		int blendMode, param;
		GetDrawBlendMode(&blendMode, &param);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);

		if (m_notBlendDraw++ > 2)
		{
			DrawExtendGraph(m_offsetX1, m_offsetY1, m_screenWidth + m_offsetX2, m_screenHeight + m_offsetY2, m_screen[1 - m_current], false);
		}
		SetDrawBlendMode(blendMode, param);
		SetDrawMode(drawMode);

		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(0, 0, m_screen[m_current], false);
		m_current = 1 - m_current;
	}
}