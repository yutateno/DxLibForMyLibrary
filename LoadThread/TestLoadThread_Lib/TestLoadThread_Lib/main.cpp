#include "DxLib.h"
#include <string>

#include "LoadThread_Lib.hpp"

using namespace LoadThread_Lib;

void Update(const int num, const int max)
{
	printfDx("%d\t%d\n", num, max);
}


/// --------------------------------------------------------------------------------------------------
// ウィンドウサイズを決める
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
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText(t_projectName.c_str());					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth / 2, winHeight / 2);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	SetAlwaysRunFlag(TRUE);				// 裏画面でも常にアクティブに変更


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
		m_str.push_back("めいん.wav");
		m_type.push_back(ELOADFILE::backGroundMusic);
	}

	LoadThread* mp_loadThread = new LoadThread();
	mp_loadThread->SetLoadFunc(Update);

	bool start = false;


	// メインループ
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

	// 削除
	DxLib_End();		// DXライブラリの後始末


	return 0;
}