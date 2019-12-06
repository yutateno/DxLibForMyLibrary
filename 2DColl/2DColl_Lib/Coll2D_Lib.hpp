#pragma once

#ifndef _COLL2D_LIB_HPP
#define _COLL2D_LIB_HPP

#include "DxLib.h"

namespace Coll2D_Lib
{
	struct SBox
	{
		float left, top, right, bottom;
	};

	struct SCircle
	{
		float x, y, r;
	};

	bool CheckColl(const SBox t_boxA, const SBox t_boxB);

	bool CheckColl(const SCircle t_circleA, const SCircle t_circleB);

	bool CheckColl(const SBox t_box, const SCircle t_circle);

	void DebugDraw(const SBox t_box, const unsigned int t_GetColor);

	void DebugDraw(const SCircle t_circle, const unsigned int t_GetColor);
}

#endif