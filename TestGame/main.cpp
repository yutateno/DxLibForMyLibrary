#include "InputControl.hpp"

using namespace InputControl;

/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウサイズを決める
	int winWidth = 640;
	int winHeight = 480;
	int bitColor = 32;


#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText("ControllerForDxLib");					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(0, 0, 0);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(winWidth, winHeight, bitColor);			// 画面サイズ設定
	GetDefaultState(&winWidth, &winHeight, &bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(winWidth / 2, winHeight / 2);						// デフォルトウィンドウサイズに合わせてゲームサイズを変更


	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}


	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画

	// キーボードの初期化
	KeyData::UpDate();


	// マウスの初期化
	MouseData::UpDate();
	// マウスホイールの初期化
	MouseWheelData::UpDate();


	// demo 変数名適当
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


	// メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !KeyData::IsCheckEnd())
	{
		KeyData::UpDate();						// キーボードのループ処理
		MouseData::UpDate();				// マウスのループ処理
		MouseWheelData::UpDate();		// マウスホイールのループ処理

		/// demo---------------------------------------------------------------------------------
		/// -------------------------------------------------------------------------------------
		if (KeyData::Get(KEY_INPUT_W) > 0)
		{
			y--;
		}
		if (KeyData::Get(KEY_INPUT_S) > 0)
		{
			y++;
		}
		if (KeyData::Get(KEY_INPUT_A) > 0)
		{
			x--;
		}
		if (KeyData::Get(KEY_INPUT_D) > 0)
		{
			x++;
		}
		DrawBox(x - 20, y - 20, x + 20, y + 20, GetColor(red, green, blue), true);
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%dx%d, GetColor(255, %d, %d)", x, y, green, blue);
		/// -------------------------------------------------------------------------------------

		/// -------------------------------------------------------------------------------------
		if (MouseData::GetClick(MouseData::ECLICK::LEFT) > 0
			&& x3 - 20 < x2 && y3 - 20 < y2 && x3 + 20 > x2&& y3 + 20 > y2)
		{
			if (!click) click = true;
		}
		else if (MouseData::GetClick(MouseData::ECLICK::LEFT) == -1 && click)
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
		if (MouseData::GetClick(MouseData::ECLICK::LEFT) > 0)
		{
			DrawCircle(x2, y2, r, GetColor(0, 255, 0));
		}
		else if (MouseData::GetClick(MouseData::ECLICK::RIGHT) > 0)
		{
			DrawCircle(x2, y2, r, GetColor(255, 0, 0));
		}
		else if (MouseData::GetClick(MouseData::ECLICK::CENTER) > 0)
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
		printfDx("%d\n", x2);
		/// -------------------------------------------------------------------------------------
		/// -------------------------------------------------------------------------------------
	}

	// 削除
	DxLib_End();		// DXライブラリの後始末


	return 0;
}