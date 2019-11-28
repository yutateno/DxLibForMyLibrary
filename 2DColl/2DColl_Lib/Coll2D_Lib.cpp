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

	// �l�p�`�̎l�ӂɑ΂��ĉ~�̔��a�������������Ƃ��~���d�Ȃ��Ă�����
	if ((t_circle.x > t_box.left - t_circle.r) && (t_circle.x < t_box.right + t_circle.r) &&
		(t_circle.y > t_box.top - t_circle.r) && (t_circle.y < t_box.bottom + t_circle.r))
	{
		nResult = true;
		float fl = t_circle.r * t_circle.r;


		// ��
		if (t_circle.x < t_box.left)
		{
			// ����
			if ((t_circle.y < t_box.top))
			{
				float dx = t_circle.x - t_box.left;
				float dy = t_circle.y - t_box.top;

				float distanceSqrf = (dx * dx) + (dy * dy);

				// �d�Ȃ��Ă��Ȃ�
				if (distanceSqrf >= fl)
				{
					nResult = false;
				}
			}
			else
			{
				// ����
				if ((t_circle.y > t_box.bottom))
				{
					float dx = t_circle.x - t_box.left;
					float dy = t_circle.y - t_box.bottom;

					float distanceSqrf = (dx * dx) + (dy * dy);

					// �d�Ȃ��Ă��Ȃ�
					if (distanceSqrf >= fl)
					{
						nResult = false;
					}
				}
			}
		}
		else
		{
			// �E
			if (t_circle.x > t_box.right)
			{
				// �E��
				if ((t_circle.y < t_box.top))
				{
					float dx = t_circle.x - t_box.right;
					float dy = t_circle.y - t_box.top;

					float distanceSqrf = (dx * dx) + (dy * dy);

					// �d�Ȃ��Ă��Ȃ�
					if (distanceSqrf >= fl)
					{
						nResult = false;
					}
				}
				else
				{
					// �E��
					if ((t_circle.y > t_box.bottom))
					{
						float dx = t_circle.x - t_box.right;
						float dy = t_circle.y - t_box.bottom;

						float distanceSqrf = (dx * dx) + (dy * dy);

						// �d�Ȃ��Ă��Ȃ�
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
