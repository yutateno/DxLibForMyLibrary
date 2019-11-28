#pragma once

#include "Coll2D_Lib.h"
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

	Coll2D_Lib::SBox box;
	Coll2D_Lib::SCircle circle;

	circle.x = 100.0f;
	circle.y = 100.0f;
	circle.r = 80.0f;

	box.left = 200.0f;
	box.top = 150.0f;
	box.right = 500.0f;
	box.bottom = 350.0f;

	// メインループ
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

	// 削除
	DxLib::DxLib_End();		// DXライブラリの後始末


	return 0;
}