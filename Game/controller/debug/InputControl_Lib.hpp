#pragma once

#include "DxLib.h"


namespace InputControl
{
	// マウス
	class MouseData
	{
	private:
		struct MouseXY
		{
			int x;
			int y;
		};

		static int m_mouse[3];
		static int m_mouseInput;
		static MouseXY m_preMouseArea;
		static MouseXY m_mouseArea;


	public:
		//左クリックか右クリックか
		enum class CLICK
		{
			LEFT,
			RIGHT,
			CENTER
		};


		//マウスのクリックの状態を更新する
		static void UpDate();

		//マウスのクリックの状態を返す
		static const int& GetClick(const CLICK& t_CLICK);

		// 現在のマウスの位置
		static const MouseXY& GetMouseArea();

		// 直前からどれくらい移動したか
		static const MouseXY GetMouseMoveValue();
	};



	// マウスホイール
	class MouseWheelData
	{
	private:
		static int m_mouseWheel;
		static int m_oldMouseWheel;
	

	public:
		//マウスのホイールの状態を更新
		static void UpDate();

		//マウスホイールの状態を返す
		static const int& GetMouseWheel();
	};



	// キーボードの入力状態
	class KeyData
	{
	private:
		static int m_key[256];		// キーの入力状態格納用変数
		static char m_tmpKey[256];	// 現在のキーの入力状態を格納する
	

	public:
		static void UpDate();			// キー入力の状態更新


		static const int& Get(const int& t_keyCode);		// キー入力状態取得
		static const bool IsCheckEnd();					// 強制終了
	};



	// ゲームパッドの入力状態
	class PadData
	{
	private:
		static int m_button[4][16];		// ゲームパッドの入力状態格納用変数
		static int m_stick[4][6];		// ゲームパッドのスティック関連の入力状態収納用変数
		static int m_stickCheck[4][8];	// ゲームパッドのスティックの入力状態収納用変数の最大までの倒しチェック
		static int m_trigger[4][2];		// ゲームパッドのトリガーの入力状態収納用変数


		// ゲームパッドのスティックのデッドゾーン数値を保存
		static short stickLX_DeadZoneMAX;
		static short stickLX_DeadZoneMIN;
		static short stickLY_DeadZoneMAX;
		static short stickLY_DeadZoneMIN;
		static short stickRX_DeadZoneMAX;
		static short stickRX_DeadZoneMIN;
		static short stickRY_DeadZoneMAX;
		static short stickRY_DeadZoneMIN;


		static XINPUT_STATE m_input[4];	// ゲームパッドのナンバー
		static char m_padNum;			// 繋がってるゲームパッドの数


	public:
		enum StickCheck
		{
			LEFT_STICK_LEFT,
			LEFT_STICK_DOWN,
			RIGHT_STICK_LEFT,
			RIGHT_STICK_DOWN,
			LEFT_STICK_RIGHT,
			LEFT_STICK_UP,
			RIGHT_STICK_RIGHT,
			RIGHT_STICK_UP
		};

		enum PadStick
		{
			LEFT_TRIGGER = 0,
			RIGHT_TRIGGER = 1,
			LEFT_STICK_X = 2,
			LEFT_STICK_Y = 3,
			RIGHT_STICK_X = 4,
			RIGHT_STICK_Y = 5,

			STICK_MAX_VALUE = 32767,
			STICK_MIN_VALUE = -32768
		};

		static void UpDate();		// ゲームパッドの入力の状態更新


		static const int& GetButton(const int& t_code, const int& t_padNum);									// ボタンの入力状態取得
		static const int& GetTrigger(const int& t_code, const int& t_padNum);								// トリガーの取得
		static const int& GetStick(const int& t_code, const int& t_padNum);									// スティックの入力状態取得
		static const int& GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue);	// スティックの押し倒し取得


		static const bool IsCheckEnd();																		// 強制終了
		static const char& GetPadNum();																		// 接続されてるゲームパッドの数


		static void SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
			, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN);					// デッドゾーンの設定
		static void SetPadNum();																		// 接続されてるゲームパッドを取得する
	};
	
	void AllUpdate();
}