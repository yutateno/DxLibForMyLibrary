#pragma once

#ifdef INPUTCONTROL_EXPORTS
#define INPUTCONTROL_API __declspec(dllexport)
#else
#define INPUTCONTROL_API __declspec(dllimport)
#endif

#include "DxLib.h"


namespace InputControl
{
	// マウス
	namespace MouseDataInternal
	{
		struct MouseXY
		{
			int x;
			int y;
		};

		int m_mouse[3];
		int m_mouseInput;
		MouseXY m_preMouseArea;
		MouseXY m_mouseArea;
	}
	namespace MouseData
	{
		//左クリックか右クリックか
		namespace CLICK
		{
			const short LEFT = 0;
			const short RIGHT = 1;
			const short CENTER = 2;
		}


		//マウスのクリックの状態を更新する
		INPUTCONTROL_API void UpDate(const int& GetMousePointX, const int& GetMousePointY);

		//マウスのクリックの状態を返す
		INPUTCONTROL_API const int& GetClick(const short& t_CLICK);

		// 現在のマウスの位置
		INPUTCONTROL_API const MouseDataInternal::MouseXY& GetMouseArea();

		// 直前からどれくらい移動したか
		INPUTCONTROL_API const MouseDataInternal::MouseXY GetMouseMoveValue();
	};



	// マウスホイール
	namespace MouseWheelDataInternal
	{
		int m_mouseWheel;
		int m_oldMouseWheel;
	}
	namespace MouseWheelData
	{
		//マウスのホイールの状態を更新
		INPUTCONTROL_API void UpDate(const int t_GetMouseWheelRotVol);

		//マウスホイールの状態を返す
		INPUTCONTROL_API const int& GetMouseWheel();
	};



	// キーボードの入力状態
	namespace KeyDataInternal
	{
		int m_key[256];		// キーの入力状態格納用変数
		char m_tmpKey[256];	// 現在のキーの入力状態を格納する
	}
	namespace KeyData
	{
		INPUTCONTROL_API void UpDate();			// キー入力の状態更新


		INPUTCONTROL_API const int& Get(const int& t_keyCode);		// キー入力状態取得
		INPUTCONTROL_API const bool IsCheckEnd();					// 強制終了
	};



	// ゲームパッドの入力状態
	namespace PadDataInternal
	{
		int m_button[4][16];		// ゲームパッドの入力状態格納用変数
		int m_stick[4][6];		// ゲームパッドのスティック関連の入力状態収納用変数
		int m_stickCheck[4][8];	// ゲームパッドのスティックの入力状態収納用変数の最大までの倒しチェック
		int m_trigger[4][2];		// ゲームパッドのトリガーの入力状態収納用変数


		// ゲームパッドのスティックのデッドゾーン数値を保存
		short stickLX_DeadZoneMAX;
		short stickLX_DeadZoneMIN;
		short stickLY_DeadZoneMAX;
		short stickLY_DeadZoneMIN;
		short stickRX_DeadZoneMAX;
		short stickRX_DeadZoneMIN;
		short stickRY_DeadZoneMAX;
		short stickRY_DeadZoneMIN;


		XINPUT_STATE m_input[4];	// ゲームパッドのナンバー
		char m_padNum;			// 繋がってるゲームパッドの数
	}
	namespace PadData
	{
		namespace StickCheck
		{
			const short LEFT_STICK_LEFT		= 0;
			const short LEFT_STICK_DOWN	   	= 1;
			const short RIGHT_STICK_LEFT	 = 2;
			const short RIGHT_STICK_DOWN	 = 3;
			const short LEFT_STICK_RIGHT	 = 4;
			const short LEFT_STICK_UP		 = 5;
			const short RIGHT_STICK_RIGHT	 = 6;
			const short RIGHT_STICK_UP		 = 7;
		}

		namespace PadStick
		{
			const int LEFT_TRIGGER = 0;
			const int RIGHT_TRIGGER = 1;
			const int LEFT_STICK_X = 2;
			const int LEFT_STICK_Y = 3;
			const int RIGHT_STICK_X = 4;
			const int RIGHT_STICK_Y = 5;

			const int STICK_MAX_VALUE = 32767;
			const int STICK_MIN_VALUE = -32768;
		}

		INPUTCONTROL_API void UpDate();		// ゲームパッドの入力の状態更新


		INPUTCONTROL_API const int& GetButton(const int& t_code, const int& t_padNum);									// ボタンの入力状態取得
		INPUTCONTROL_API const int& GetTrigger(const int& t_code, const int& t_padNum);								// トリガーの取得
		INPUTCONTROL_API const int& GetStick(const int& t_code, const int& t_padNum);									// スティックの入力状態取得
		INPUTCONTROL_API const int& GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue);	// スティックの押し倒し取得


		INPUTCONTROL_API const bool IsCheckEnd();																		// 強制終了
		INPUTCONTROL_API const char& GetPadNum();																		// 接続されてるゲームパッドの数


		INPUTCONTROL_API void SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
			, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN);					// デッドゾーンの設定
		INPUTCONTROL_API void SetPadNum();																		// 接続されてるゲームパッドを取得する
	}

	INPUTCONTROL_API void InitAllControl();
	INPUTCONTROL_API void InitMouse();
	INPUTCONTROL_API void InitKey();
	INPUTCONTROL_API void InitPad();

	INPUTCONTROL_API void AllUpdate(const int& GetMousePointX, const int& GetMousePointY, const int t_GetMouseWheelRotVol);
}