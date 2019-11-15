#include "InputControl.hpp"

using namespace InputControl;

/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�T�C�Y�����߂�
	int winWidth = 640;
	int winHeight = 480;
	int bitColor = 32;

#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText("ControllerForDxLib");					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(0, 0, 0);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(winWidth, winHeight, bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(winWidth / 2, winHeight / 2);						// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX


	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}


	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��


	InitAllControl();
	PadData::SetPadNum(GetJoypadNum());
	int mouseX, mouseY;

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


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd() && !PadData::IsCheckEnd())
	{
		GetMousePoint(&mouseX, &mouseY);
		AllUpdate(mouseX, mouseY, GetMouseWheelRotVol());

		/// demo---------------------------------------------------------------------------------
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
		if (PadData::GetStick(PadData::PadStick::RIGHT_STICK_X, 0) > 0)
		{
			if (blue < 255) blue++;
		}
		if (PadData::GetStick(PadData::PadStick::RIGHT_STICK_X, 0) < 0)
		{
			if (blue > 0) blue--;
		}
		DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(red, green, blue), true);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%dx%d, GetColor(255, %d, %d)", x, y, green, blue);
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
	}

	// �폜
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}