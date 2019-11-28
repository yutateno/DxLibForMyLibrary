#pragma once

#include "Coll2D_Lib.h"
#include "DxLib.h"
#include <string>




bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = t_winWidth;
	int winHeight = t_winHeight;
	int bitColor = t_bitColor;

#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText(t_projectName.c_str());					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth / 2, winHeight / 2);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��


	return true;
}


/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (Init(640, 480, 32, "Game") == false) return -1;

	Coll2D_Lib::SBox box;
	Coll2D_Lib::SCircle circle;

	circle.x = 100.0f;
	circle.y = 100.0f;
	circle.r = 80.0f;

	box.left = 200.0f;
	box.top = 150.0f;
	box.right = 500.0f;
	box.bottom = 350.0f;

	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		if (Coll2D_Lib::CheckColl(box, circle))
		{
			DrawBox(box.left, box.top, box.right, box.bottom, GetColor(255, 255, 255), true);
			DrawCircle(circle.x, circle.y, circle.r, GetColor(125, 125, 125));
		}
		else
		{
			DrawBox(box.left, box.top, box.right, box.bottom, GetColor(125, 125, 125), true);
			DrawCircle(circle.x, circle.y, circle.r, GetColor(125, 125, 125));
		}

		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			box.left -= 5.0f;
			box.right -= 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			box.left += 5.0f;
			box.right += 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			box.top -= 5.0f;
			box.bottom -= 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			box.top += 5.0f;
			box.bottom += 5.0f;
		}
	}

	// �폜
	DxLib::DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}