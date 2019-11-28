#include "pch.h"
#include "Coll2D_Lib.h"



/// -----------------------------------------------------------------------------------
bool Coll2D_Lib::CheckColl(const SBox& t_boxA, const SBox& t_boxB)
{
	if ((t_boxA.right > t_boxB.left) &&	(t_boxA.left < t_boxB.right))
	{
		if ((t_boxA.bottom > t_boxB.top) &&	(t_boxA.top < t_boxB.bottom))
		{
			return true;
		}
	}

	return false;
}



/// -----------------------------------------------------------------------------------
bool Coll2D_Lib::CheckColl(const SCircle& t_circleA, const SCircle& t_circleB)
{
	float dx = t_circleA.x - t_circleB.x;
	float dy = t_circleA.y - t_circleB.y;
	float dr = dx * dx + dy * dy;

	float ar = t_circleA.r + t_circleB.r;
	float dl = ar * ar;

	if (dr < dl)
	{
		return true;
	}

	return false;
}



/// -----------------------------------------------------------------------------------
bool Coll2D_Lib::CheckColl(const SBox& t_box, const SCircle& t_circle)
{
	bool nResult = false;

	// 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
	if ((t_circle.x > t_box.left - t_circle.r) && (t_circle.x < t_box.right + t_circle.r) &&
		(t_circle.y > t_box.top - t_circle.r) && (t_circle.y < t_box.bottom + t_circle.r))
	{
		nResult = true;
		float fl = t_circle.r * t_circle.r;


		// 左
		if (t_circle.x < t_box.left)
		{
			// 左上
			if ((t_circle.y < t_box.top))
			{
				float dx = t_circle.x - t_box.left;
				float dy = t_circle.y - t_box.top;

				float distanceSqrf = (dx * dx) + (dy * dy);

				// 重なっていない
				if (distanceSqrf >= fl)
				{
					nResult = false;
				}
			}
			else
			{
				// 左下
				if ((t_circle.y > t_box.bottom))
				{
					float dx = t_circle.x - t_box.left;
					float dy = t_circle.y - t_box.bottom;

					float distanceSqrf = (dx * dx) + (dy * dy);

					// 重なっていない
					if (distanceSqrf >= fl)
					{
						nResult = false;
					}
				}
			}
		}
		else
		{
			// 右
			if (t_circle.x > t_box.right)
			{
				// 右上
				if ((t_circle.y < t_box.top))
				{
					float dx = t_circle.x - t_box.right;
					float dy = t_circle.y - t_box.top;

					float distanceSqrf = (dx * dx) + (dy * dy);

					// 重なっていない
					if (distanceSqrf >= fl)
					{
						nResult = false;
					}
				}
				else
				{
					// 右下
					if ((t_circle.y > t_box.bottom))
					{
						float dx = t_circle.x - t_box.right;
						float dy = t_circle.y - t_box.bottom;

						float distanceSqrf = (dx * dx) + (dy * dy);

						// 重なっていない
						if (distanceSqrf >= fl)
						{
							nResult = false;
						}
					}
				}
			}
		}
	}

	return nResult;
}
