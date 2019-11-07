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
	class MouseData
	{
	private:
		static int m_mouse[3];
		static int m_mouseInput;
		struct MouseXY
		{
			int x;
			int y;
		};
		static MouseXY m_preMouseArea;
		static MouseXY m_mouseArea;


	public:
		//左クリックか右クリックか
		INPUTCONTROL_API enum class ECLICK { LEFT, RIGHT, CENTER };


		//マウスのクリックの状態を更新する
		static INPUTCONTROL_API void UpDate();

		//マウスのクリックの状態を返す
		static INPUTCONTROL_API const int& GetClick(const ECLICK& t_mouseCode);

		// 現在のマウスの位置
		static INPUTCONTROL_API const MouseXY& GetMouseArea();

		// 直前からどれくらい移動したか
		static INPUTCONTROL_API const MouseXY GetMouseMoveValue();
	};



	// マウスホイール
	class MouseWheelData
	{
	private:
		static int m_mouseWheel;
		static int m_oldMouseWheel;


	public:
		//マウスのホイールの状態を更新
		static INPUTCONTROL_API void UpDate();

		//マウスホイールの状態を返す
		static INPUTCONTROL_API const int& GetMouseWheel();
	};



	// キーボードの入力状態
	class KeyData
	{
	private:
		static int m_key[256];		// キーの入力状態格納用変数
		static char m_tmpKey[256];	// 現在のキーの入力状態を格納する

	public:
		static INPUTCONTROL_API void UpDate();			// キー入力の状態更新


		static INPUTCONTROL_API const int& Get(const int& t_keyCode);		// キー入力状態取得
		static INPUTCONTROL_API const bool IsCheckEnd();					// 強制終了
	};



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


		enum class EStickCheck
		{
			LEFT_STICK_LEFT, LEFT_STICK_DOWN, RIGHT_STICK_LEFT, RIGHT_STICK_DOWN
			, LEFT_STICK_RIGHT, LEFT_STICK_UP, RIGHT_STICK_RIGHT, RIGHT_STICK_UP
		};



	public:
		static void UpDate();		// ゲームパッドの入力の状態更新


		static INPUTCONTROL_API const int& GetButton(const int& t_code, const int& t_padNum);									// ボタンの入力状態取得
		static INPUTCONTROL_API const int& GetTrigger(const int& t_code, const int& t_padNum);								// トリガーの取得
		static INPUTCONTROL_API const int& GetStick(const int& t_code, const int& t_padNum);									// スティックの入力状態取得
		static INPUTCONTROL_API const int& GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue);	// スティックの押し倒し取得


		static INPUTCONTROL_API const bool IsCheckEnd();																		// 強制終了
		static INPUTCONTROL_API const char& GetPadNum();																		// 接続されてるゲームパッドの数


		static INPUTCONTROL_API inline void SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
			, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN);					// デッドゾーンの設定
		static INPUTCONTROL_API inline void SetPadNum();																		// 接続されてるゲームパッドを取得する
	};



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	inline void PadData::SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
		, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN)
	{
		stickLX_DeadZoneMAX = t_stickLX_MAX;
		stickLX_DeadZoneMIN = t_stickLX_MIN;
		stickLY_DeadZoneMAX = t_stickLY_MAX;
		stickLY_DeadZoneMIN = t_stickLY_MIN;
		stickRX_DeadZoneMAX = t_stickRX_MAX;
		stickRX_DeadZoneMIN = t_stickRX_MIN;
		stickRY_DeadZoneMAX = t_stickRY_MAX;
		stickRY_DeadZoneMIN = t_stickRY_MIN;
	}



	/// ------------------------------------------------------------------------------------------------------------
	inline void PadData::SetPadNum()
	{
		if (GetJoypadNum() > 0)
		{
			m_padNum = static_cast<char>(GetJoypadNum());
		}
		else
		{
			m_padNum = -1;
		}
	}
}