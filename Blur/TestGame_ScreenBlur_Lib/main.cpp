#include "ScreenBlur_Lib.hpp"
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

	ScreenBlur_Lib::ScreenBlur m_screenBlur[2];
	for (int i = 0; i != 2; ++i)
	{
		m_screenBlur[i] = ScreenBlur_Lib::ScreenBlur();
	}
	m_screenBlur[0].Init(640, 480, 200, 6, -2, 0, 0);
	m_screenBlur[1].Init(640, 480, 200, 0, 10, 0, 0);

	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		m_screenBlur[1].PreRenderBlurScreen();
		DrawBox(0, 0, 640, 480, GetColor(125, 125, 125), true);
		DrawBox(50, 50, 80, 80, GetColor(255, 0, 0), true);
		m_screenBlur[1].PostRenderBlurScreen();
	}

	// �폜
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}