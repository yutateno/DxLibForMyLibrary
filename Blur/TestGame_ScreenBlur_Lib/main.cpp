#include "ScreenBlur_Lib.hpp"
#include "DxLib.h"
#include <string>



bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	// ウィンドウサイズを決める
	int winWidth = t_winWidth;
	int winHeight = t_winHeight;
	int bitColor = t_bitColor;

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
	m_screenBlur[0].Init(200, 6, -2, 0, 0);
	m_screenBlur[1].Init(200, 0, 10, 0, 0);

	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen())
	{
		DrawBox(0, 0, 640, 480, GetColor(125, 125, 125), true);

		m_screenBlur[1].PreRenderBlurScreen();
		DrawBox(50, 50, 80, 80, GetColor(255, 0, 0), true);
		m_screenBlur[1].PostRenderBlurScreen();
	}

	// 削除
	DxLib_End();		// DXライブラリの後始末


	return 0;
}