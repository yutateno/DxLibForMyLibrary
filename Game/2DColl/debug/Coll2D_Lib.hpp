#pragma once

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

	bool CheckColl(const SBox& t_boxA, const SBox& t_boxB);

	bool CheckColl(const SCircle& t_circleA, const SCircle& t_circleB);

	bool CheckColl(const SBox& t_box, const SCircle& t_circle);
}