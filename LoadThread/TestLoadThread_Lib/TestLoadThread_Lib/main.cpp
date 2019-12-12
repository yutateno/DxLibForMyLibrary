#include "DxLib.h"
#include <string>

#include "LoadThread_Lib.hpp"

using namespace LoadThread_Lib;

void Update(const int num, const int max)
{
	printfDx("%d\t%d\n", num, max);
}


/// --------------------------------------------------------------------------------------------------
// �E�B���h�E�T�C�Y�����߂�
int winWidth = 0;
int winHeight = 0;
int bitColor = 0;



/// --------------------------------------------------------------------------------------------------
bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	winWidth = t_winWidth;
	winHeight = t_winHeight;
	bitColor = t_bitColor;

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

	SetAlwaysRunFlag(TRUE);				// ����ʂł���ɃA�N�e�B�u�ɕύX


	return true;
}



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (Init(1920, 1080, 32, "Game") == false) return -1;

	std::vector<std::string> m_str;
	std::vector<ELOADFILE> m_type;
	for (int i = 0; i < 50; ++i)
	{
		m_str.push_back("�߂���.wav");
		m_type.push_back(ELOADFILE::backGroundMusic);
	}

	LoadThread* mp_loadThread = new LoadThread();
	mp_loadThread->SetLoadFunc(Update);

	bool start = false;


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		mp_loadThread->Process(m_str.size(), m_str, m_type);

		if (mp_loadThread->GetEnd())
		{
			for (int i = 0; i < mp_loadThread->GetFile().size(); ++i)
			{
				DrawFormatString(1920 / 2, i * 20, GetColor(255, 255, 255), "%d", mp_loadThread->GetFile().at(i));
			}
			if (!start)	PlaySoundMem(mp_loadThread->GetFile().at(0), DX_PLAYTYPE_LOOP);
			start = true;
		}
	}

	delete mp_loadThread;
	WaitKey();

	// �폜
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}