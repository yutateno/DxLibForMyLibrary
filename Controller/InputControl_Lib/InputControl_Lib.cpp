#include "pch.h"
#include "InputControl_Lib.hpp"


namespace InputControl
{
	/// ------------------------------------------------------------------------------------------------------------

	int MouseData::m_mouse[3];
	int MouseData::m_mouseInput;
	MouseData::MouseXY MouseData::m_preMouseArea;
	MouseData::MouseXY MouseData::m_mouseArea;



	/// ------------------------------------------------------------------------------------------------------------
	void MouseData::UpDate()
	{
		// PCゲーである以上、マウスのない状態が想定できないのでエラー処理は省く
		m_mouseInput = GetMouseInput();

		m_preMouseArea.x = m_mouseArea.x;
		m_preMouseArea.y = m_mouseArea.y;
		GetMousePoint(&m_mouseArea.x, &m_mouseArea.y);


		for (int i = 0; i != 3; ++i)
		{
			// 押されていなかったら
			if ((m_mouseInput & 1 << i)/* 左は1 / 右は2 / 真ん中は4 */ == 0)
			{
				if (m_mouse[i] < 0)
				{
					m_mouse[i] = 0;
				}
				else if (m_mouse[i] > 0)
				{
					m_mouse[i] = -1;
				}
			}
			// 押されていたら
			else
			{
				m_mouse[i]++;
			}
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	const int& MouseData::GetClick(const CLICK& t_CLICK)
	{
		return m_mouse[static_cast<int>(t_CLICK)];
	}



	/// ------------------------------------------------------------------------------------------------------------
	const MouseData::MouseXY& MouseData::GetMouseArea()
	{
		return m_mouseArea;
	}



	/// ------------------------------------------------------------------------------------------------------------
	const MouseData::MouseXY MouseData::GetMouseMoveValue()
	{
		return { m_mouseArea.x - m_preMouseArea.x, m_mouseArea.y - m_preMouseArea.y };
	}



	/// ------------------------------------------------------------------------------------------------------------
	
	int MouseWheelData::m_mouseWheel;
	int MouseWheelData::m_oldMouseWheel;



	/// ------------------------------------------------------------------------------------------------------------
	void MouseWheelData::UpDate()
	{
		m_mouseWheel += GetMouseWheelRotVol();


		if (m_oldMouseWheel == m_mouseWheel)
		{
			if (m_mouseWheel != 0) m_mouseWheel = 0;
			return;
		}
		else
		{
			m_oldMouseWheel = m_mouseWheel;
		}


		if (m_oldMouseWheel - m_mouseWheel > 0)
		{
			m_mouseWheel++;
		}
		else if (m_oldMouseWheel - m_mouseWheel < 0)
		{
			m_mouseWheel--;
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	const int& MouseWheelData::GetMouseWheel()
	{
		return m_mouseWheel;
	}



	/// ------------------------------------------------------------------------------------------------------------

	int KeyData::m_key[256];		// キーの入力状態格納用変数
	char KeyData::m_tmpKey[256];	// 現在のキーの入力状態を格納する



	/// ------------------------------------------------------------------------------------------------------------
	void KeyData::UpDate()
	{
		// 全てのキーの入力状態を得る（押されたら１を出力し、押されていなかったら０を返す
		if (GetHitKeyStateAll(m_tmpKey) == -1) return;


		// 全キー入力処理
		for (int i = 0; i < 256; ++i)
		{
			// 押されていなかったら
			if (m_tmpKey[i] == 0)
			{
				if (m_key[i] < 0)
				{
					m_key[i] = 0;
				}
				else if (m_key[i] > 0)
				{
					m_key[i] = -1;
				}
			}
			// i番のキーコードに対応するキーが押されていたら
			else if (m_tmpKey[i] == 1)
			{
				m_key[i]++;
			}
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	const int& KeyData::Get(const int& t_keyCode)
	{
		return m_key[t_keyCode];
	}



	/// ------------------------------------------------------------------------------------------------------------
	const bool KeyData::IsCheckEnd()
	{
		return m_key[KEY_INPUT_ESCAPE] > 0;
	}




	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------

	int PadData::m_button[4][16];
	int PadData::m_stick[4][6];
	int PadData::m_stickCheck[4][8];
	int PadData::m_trigger[4][2];

	short PadData::stickLX_DeadZoneMAX = 1000;
	short PadData::stickLX_DeadZoneMIN = -1000;
	short PadData::stickLY_DeadZoneMAX = 1000;
	short PadData::stickLY_DeadZoneMIN = -1000;
	short PadData::stickRX_DeadZoneMAX = 1000;
	short PadData::stickRX_DeadZoneMIN = -1000;
	short PadData::stickRY_DeadZoneMAX = 1000;
	short PadData::stickRY_DeadZoneMIN = -1000;

	XINPUT_STATE PadData::m_input[4];
	char PadData::m_padNum;



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	void PadData::UpDate()
	{
		// ゲームパッドの取得出来ているか
		if (m_padNum == -1) return;


		// ゲームパッドの個数だけ処理
		for (int padNumber = 0; padNumber < static_cast<int>(m_padNum); ++padNumber)
		{
			// 入力状態を取得
			GetJoypadXInputState(padNumber + 1, &m_input[padNumber]);



			/// ボタン関係-----------------------------------------------------------
			{
				// 全ボタン入力処理
				for (int j = 0; j < 16; ++j)
				{
					// 押されていなかったら
					if (m_input[padNumber].Buttons[j] == 0)
					{
						if (m_button[padNumber][j] < 0)
						{
							m_button[padNumber][j] = 0;
						}
						else if (m_button[padNumber][j] > 0)
						{
							m_button[padNumber][j] = -1;
						}
					}
					// i番のキーコードに対応するボタンが押されていたら
					else if (m_input[padNumber].Buttons[j] == 1)
					{
						m_button[padNumber][j]++;
					}
				}
			}
			/// ---------------------------------------------------------------------



			/// トリガー関係---------------------------------------------------------
			{
				// トリガーの入力数値を渡す
				m_trigger[padNumber][LEFT_TRIGGER] = m_input[padNumber].LeftTrigger;
				m_trigger[padNumber][RIGHT_TRIGGER] = m_input[padNumber].RightTrigger;
			}
			/// ---------------------------------------------------------------------



			/// スティック入力関係---------------------------------------------------
			{
				/// スティックのデッドゾーンを考慮した入力数値を取得（デッドゾーンは受け付けない値

				// 左スティック左右
				if (m_input[padNumber].ThumbLX > stickLX_DeadZoneMAX || m_input[padNumber].ThumbLX < stickLX_DeadZoneMIN)
				{
					m_stick[padNumber][LEFT_STICK_X] = m_input[padNumber].ThumbLX;
				}
				else
				{
					if (m_stick[padNumber][LEFT_STICK_X] != 0) m_stick[padNumber][LEFT_STICK_X] = 0;
				}

				// 左スティック上下
				if (m_input[padNumber].ThumbLY > stickLY_DeadZoneMAX || m_input[padNumber].ThumbLY < stickLY_DeadZoneMIN)
				{
					m_stick[padNumber][LEFT_STICK_Y] = m_input[padNumber].ThumbLY;
				}
				else
				{
					if (m_stick[padNumber][LEFT_STICK_Y] != 0) m_stick[padNumber][LEFT_STICK_Y] = 0;
				}

				// 右スティック左右
				if (m_input[padNumber].ThumbRX > stickRX_DeadZoneMAX || m_input[padNumber].ThumbRX < stickRX_DeadZoneMIN)
				{
					m_stick[padNumber][RIGHT_STICK_X] = m_input[padNumber].ThumbRX;
				}
				else
				{
					if (m_stick[padNumber][RIGHT_STICK_X] != 0) m_stick[padNumber][RIGHT_STICK_X] = 0;
				}

				// 右スティック上下
				if (m_input[padNumber].ThumbRY > stickRY_DeadZoneMAX || m_input[padNumber].ThumbRY < stickRY_DeadZoneMIN)
				{
					m_stick[padNumber][RIGHT_STICK_Y] = m_input[padNumber].ThumbRY;
				}
				else
				{
					if (m_stick[padNumber][RIGHT_STICK_Y] != 0) m_stick[padNumber][RIGHT_STICK_Y] = 0;
				}
			}
			/// ---------------------------------------------------------------------



			/// スティック押し倒し関係-----------------------------------------------
			{
				// 左スティックを右に押し倒していたら
				if (m_input[padNumber].ThumbLX == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_RIGHT]++;
				}
				// 左スティックを左に押し倒していたら
				else if (m_input[padNumber].ThumbLX == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_LEFT]++;
				}
				// 左スティックが押し倒されていなかったら
				else
				{
					if (m_stickCheck[padNumber][LEFT_STICK_RIGHT] < 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_RIGHT] = 0;
					}
					else if (m_stickCheck[padNumber][LEFT_STICK_RIGHT] > 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_RIGHT] = -1;
					}


					if (m_stickCheck[padNumber][LEFT_STICK_LEFT] < 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_LEFT] = 0;
					}
					else if (m_stickCheck[padNumber][LEFT_STICK_LEFT] > 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_LEFT] = -1;
					}
				}


				// 左スティックを上に押し倒していたら
				if (m_input[padNumber].ThumbLY == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_UP]++;
				}
				// 左スティックを下に押し倒していたら
				else if (m_input[padNumber].ThumbLY == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_DOWN]++;
				}
				// 左スティックが押し倒されていなかったら
				else
				{
					if (m_stickCheck[padNumber][LEFT_STICK_UP] < 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_UP] = 0;
					}
					else if (m_stickCheck[padNumber][LEFT_STICK_UP] > 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_UP] = -1;
					}


					if (m_stickCheck[padNumber][LEFT_STICK_DOWN] < 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_DOWN] = 0;
					}
					else if (m_stickCheck[padNumber][LEFT_STICK_DOWN] > 0)
					{
						m_stickCheck[padNumber][LEFT_STICK_DOWN] = -1;
					}
				}


				// 右スティックを右に押し倒していたら
				if (m_input[padNumber].ThumbRX == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_RIGHT]++;
				}
				// 右スティックを左に押し倒していたら
				else if (m_input[padNumber].ThumbRX == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_LEFT]++;
				}
				// 右スティックが押し倒されていなかったら
				else
				{
					if (m_stickCheck[padNumber][RIGHT_STICK_RIGHT] < 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_RIGHT] = 0;
					}
					else if (m_stickCheck[padNumber][RIGHT_STICK_RIGHT] > 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_RIGHT] = -1;
					}


					if (m_stickCheck[padNumber][RIGHT_STICK_LEFT] < 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_LEFT] = 0;
					}
					else if (m_stickCheck[padNumber][RIGHT_STICK_LEFT] > 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_LEFT] = -1;
					}
				}


				// 右スティックを上に押し倒していたら
				if (m_input[padNumber].ThumbRY == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_UP]++;
				}
				// 右スティックを下に押し倒していたら
				else if (m_input[padNumber].ThumbRY == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_DOWN]++;
				}
				// 右スティックが押し倒されていなかったら
				else
				{
					if (m_stickCheck[padNumber][RIGHT_STICK_UP] < 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_UP] = 0;
					}
					else if (m_stickCheck[padNumber][RIGHT_STICK_UP] > 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_UP] = -1;
					}


					if (m_stickCheck[padNumber][RIGHT_STICK_DOWN] < 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_DOWN] = 0;
					}
					else if (m_stickCheck[padNumber][RIGHT_STICK_DOWN] > 0)
					{
						m_stickCheck[padNumber][RIGHT_STICK_DOWN] = -1;
					}
				}
			}
			/// ---------------------------------------------------------------------
		}
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const int& PadData::GetButton(const int& t_code, const int& t_padNum)
	{
		return m_button[t_padNum][t_code];
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const int& PadData::GetTrigger(const int& t_code, const int& t_padNum)
	{
		return m_trigger[t_padNum][t_code];
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const int& PadData::GetStick(const int& t_code, const int& t_padNum)
	{
		return m_stick[t_padNum][t_code];
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const int& PadData::GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue)
	{
		if (t_leftAndDownIsTrue)
		{
			return m_stickCheck[t_padNum][t_code - 2];
		}
		else
		{
			return m_stickCheck[t_padNum][t_code - 2 + 4];
		}
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const bool PadData::IsCheckEnd()
	{
		return
		{
			(m_button[0][XINPUT_BUTTON_START] > 1 && m_button[0][XINPUT_BUTTON_BACK] > 1) ||
			(m_button[1][XINPUT_BUTTON_START] > 1 && m_button[1][XINPUT_BUTTON_BACK] > 1) ||
			(m_button[2][XINPUT_BUTTON_START] > 1 && m_button[2][XINPUT_BUTTON_BACK] > 1) ||
			(m_button[3][XINPUT_BUTTON_START] > 1 && m_button[3][XINPUT_BUTTON_BACK] > 1)
		};
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	const char& PadData::GetPadNum()
	{
		return m_padNum;
	}



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	void PadData::SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
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
	void PadData::SetPadNum()
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



	/// ------------------------------------------------------------------------------------------------------------
	void AllUpdate()
	{
		KeyData::UpDate();						// キーボードのループ処理
		PadData::UpDate();						// ゲームパッドのループ処理
		MouseData::UpDate();				// マウスのループ処理
		MouseWheelData::UpDate();		// マウスホイールのループ処理
	}
}