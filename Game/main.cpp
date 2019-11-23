#pragma once

#include "InputControl_Lib.hpp"
#include "ScreenBlur_Lib.hpp"
#include "FileReadWrite_Lib.hpp"
#include "DxLib.h"
#include <string>

using namespace InputControl;
using namespace ScreenBlur_Lib;
using namespace FileReadWrite_Lib;


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


	/// �R���g���[���[���C�u����
	PadData::SetPadNum();

	// demo �ϐ����K��
	int x = 100;
	int y = 100;
	int red = 255;
	int green = 0;
	int blue = 0;
	int x2 = 0;
	int y2 = 0;
	int r = 5;
	int x3 = 400;
	int y3 = 400;
	bool click = false;


	/// �u���[���C�u����
	ScreenBlur m_screenBlur = ScreenBlur();
	bool m_blur = false;
	bool m_firstBlur = false;


	/// �t�@�C�����C�u����
	FileReaderWrite::Init();
	if (!FileReaderWrite::FileCSVRead("test.csv")) return -1;
	//std::vector<std::vector<std::string>> map = FileReaderWrite::GetMapData();


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd())
	{
		/// �t�@�C��-----------------------------------------------------------------------------
		/*for (int i = 0; i != map.size(); ++i)
		{
			for (int j = 0; j != map[i].size(); ++j)
			{
				DrawFormatString(i * 5, j * 5, GetColor(255, 255, 255), "%s", map[i][j]);
			}
		}*/
		

		/*
		/// �u���[-------------------------------------------------------------------------------
		if (KeyData::Get(KEY_INPUT_W) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_Y, 0, false) > 0)
		{
			y--;
		}
		if (KeyData::Get(KEY_INPUT_S) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_Y, 0, true) > 0)
		{
			y++;
		}
		if (KeyData::Get(KEY_INPUT_A) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_X, 0, true) > 0)
		{
			x--;
			m_blur = true;
		}
		if (KeyData::Get(KEY_INPUT_A) == -1)
		{
			m_blur = false;
		}
		if (KeyData::Get(KEY_INPUT_D) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_X, 0, false) > 0)
		{
			x++;
		}
		if (m_blur)
		{
			if (!m_firstBlur)
			{
				m_firstBlur = true;
				m_screenBlur.Init(640, 480, 200, 10, 0, 0, 0);
			}
			m_screenBlur.PreRenderBlurScreen();
			DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(255, 0, 0), true);
			m_screenBlur.PostRenderBlurScreen();
		}
		else
		{
			m_firstBlur = false;
			m_screenBlur.Release();
			DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(255, 0, 0), true);
		}*/


		/*
		/// �R���g���[���[-----------------------------------------------------------------------
		InputControl::AllUpdate();
		/// -------------------------------------------------------------------------------------
		if (KeyData::Get(KEY_INPUT_W) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_Y, 0, false) > 0)
		{
			y--;
		}
		if (KeyData::Get(KEY_INPUT_S) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_Y, 0, true) > 0)
		{
			y++;
		}
		if (KeyData::Get(KEY_INPUT_A) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_X, 0, true) > 0)
		{
			x--;
		}
		if (KeyData::Get(KEY_INPUT_D) > 0 || PadData::GetStickCheck(PadData::PadStick::LEFT_STICK_X, 0, false) > 0)
		{
			x++;
		}
		if (PadData::GetTrigger(PadData::PadStick::LEFT_TRIGGER, 0) == 255)
		{
			if (green < 255) green++;
		}
		if (PadData::GetTrigger(PadData::PadStick::RIGHT_TRIGGER, 0) == 255)
		{
			if (green > 0) green--;
		}
		if (PadData::GetStick(PadData::PadStick::RIGHT_STICK_Y, 0) > 0)
		{
			if (blue < 255) blue++;
		}
		if (PadData::GetStick(PadData::PadStick::RIGHT_STICK_Y, 0) < 0)
		{
			if (blue > 0) blue--;
		}
		DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(red, green, blue), true);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%dx%d, GetColor(255, %d, %d)", x, y, green, blue);
		printfDx("%d\n", PadData::GetPadNum());
		/// -------------------------------------------------------------------------------------

		/// -------------------------------------------------------------------------------------
		if (MouseData::GetClick(MouseData::CLICK::LEFT) > 0
			&& x3 - 20 < x2 && y3 - 20 < y2 && x3 + 20 > x2&& y3 + 20 > y2)
		{
			if (!click) click = true;
		}
		else if (MouseData::GetClick(MouseData::CLICK::LEFT) == -1 && click)
		{
			click = false;
		}
		if (click)
		{
			x3 += MouseData::GetMouseMoveValue().x;
			y3 += MouseData::GetMouseMoveValue().y;
		}
		DrawBox(x3 - 20, y3 - 20, x3 + 20, y3 + 20, GetColor(red, green, blue), true);
		/// -------------------------------------------------------------------------------------

		/// -------------------------------------------------------------------------------------
		x2 = MouseData::GetMouseArea().x;
		y2 = MouseData::GetMouseArea().y;
		if (MouseData::GetClick(MouseData::CLICK::LEFT) > 0)
		{
			DrawCircle(x2, y2, r, GetColor(0, 255, 0));
		}
		else if (MouseData::GetClick(MouseData::CLICK::RIGHT) > 0)
		{
			DrawCircle(x2, y2, r, GetColor(255, 0, 0));
		}
		else if (MouseData::GetClick(MouseData::CLICK::CENTER) > 0)
		{
			DrawCircle(x2, y2, r, GetColor(0, 0, 255));
		}
		else
		{
			DrawCircle(x2, y2, r, GetColor(255, 255, 255));
		}
		if (MouseWheelData::GetMouseWheel() > 0)
		{
			if (r > 1)
			{
				r--;
			}
		}
		else if (MouseWheelData::GetMouseWheel() < 0)
		{
			if (r < 20)
			{
				r++;
			}
		}
		/// -------------------------------------------------------------------------------------
		/// -------------------------------------------------------------------------------------
		*/
	}

	// �폜
	DxLib::DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}