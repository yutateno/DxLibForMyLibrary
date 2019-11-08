#include "pch.h"
#include "InputControl.hpp"


namespace InputControl
{
	/// ------------------------------------------------------------------------------------------------------------
	using namespace MouseDataInternal;
	/// ------------------------------------------------------------------------------------------------------------
	void MouseData::UpDate(const int& GetMousePointX, const int& GetMousePointY)
	{
		// PC�Q�[�ł���ȏ�A�}�E�X�̂Ȃ���Ԃ��z��ł��Ȃ��̂ŃG���[�����͏Ȃ�
		m_mouseInput = GetMouseInput();

		m_preMouseArea.x = m_mouseArea.x;
		m_preMouseArea.y = m_mouseArea.y;
		m_mouseArea.x = GetMousePointX;
		m_mouseArea.y = GetMousePointY;


		for (int i = 0; i != 3; ++i)
		{
			// ������Ă��Ȃ�������
			if ((m_mouseInput & 1 << i)/* ����1 / �E��2 / �^�񒆂�4 */ == 0)
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
			// ������Ă�����
			else
			{
				m_mouse[i]++;
			}
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	const int& MouseData::GetClick(const short& t_CLICK)
	{
		return m_mouse[t_CLICK];
	}



	/// ------------------------------------------------------------------------------------------------------------
	const MouseXY& MouseData::GetMouseArea()
	{
		return m_mouseArea;
	}



	/// ------------------------------------------------------------------------------------------------------------
	const MouseXY MouseData::GetMouseMoveValue()
	{
		return { m_mouseArea.x - m_preMouseArea.x, m_mouseArea.y - m_preMouseArea.y };
	}



	/// ------------------------------------------------------------------------------------------------------------
	using namespace MouseWheelDataInternal;
	/// ------------------------------------------------------------------------------------------------------------
	void MouseWheelData::UpDate(const int t_GetMouseWheelRotVol)
	{
		m_mouseWheel += t_GetMouseWheelRotVol;


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
	using namespace KeyDataInternal;
	/// ------------------------------------------------------------------------------------------------------------
	void KeyData::UpDate()
	{
		// �S�ẴL�[�̓��͏�Ԃ𓾂�i�����ꂽ��P���o�͂��A������Ă��Ȃ�������O��Ԃ�
		if (GetHitKeyStateAll(m_tmpKey) == -1) return;


		// �S�L�[���͏���
		for (int i = 0; i < 256; ++i)
		{
			// ������Ă��Ȃ�������
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
			// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
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
	using namespace PadDataInternal;
	using namespace PadData::PadStick;
	using namespace PadData::StickCheck;
	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------



	/// ---------------------------------------------------------------------------------------------------------------------------------------------------------
	void PadData::UpDate()
	{
		// �Q�[���p�b�h�̎擾�o���Ă��邩
		if (m_padNum == -1) return;


		// �Q�[���p�b�h�̌���������
		for (int padNumber = 0; padNumber < static_cast<int>(m_padNum); ++padNumber)
		{
			// ���͏�Ԃ��擾
			GetJoypadXInputState(padNumber + 1, &m_input[padNumber]);



			/// �{�^���֌W-----------------------------------------------------------
			{
				// �S�{�^�����͏���
				for (int j = 0; j < 16; ++j)
				{
					// ������Ă��Ȃ�������
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
					// i�Ԃ̃L�[�R�[�h�ɑΉ�����{�^����������Ă�����
					else if (m_input[padNumber].Buttons[j] == 1)
					{
						m_button[padNumber][j]++;
					}
				}
			}
			/// ---------------------------------------------------------------------



			/// �g���K�[�֌W---------------------------------------------------------
			{
				// �g���K�[�̓��͐��l��n��
				m_trigger[padNumber][LEFT_TRIGGER] = m_input[padNumber].LeftTrigger;
				m_trigger[padNumber][RIGHT_TRIGGER] = m_input[padNumber].RightTrigger;
			}
			/// ---------------------------------------------------------------------



			/// �X�e�B�b�N���͊֌W---------------------------------------------------
			{
				/// �X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾�i�f�b�h�]�[���͎󂯕t���Ȃ��l

				// ���X�e�B�b�N���E
				if (m_input[padNumber].ThumbLX > stickLX_DeadZoneMAX || m_input[padNumber].ThumbLX < stickLX_DeadZoneMIN)
				{
					m_stick[padNumber][LEFT_STICK_X] = m_input[padNumber].ThumbLX;
				}
				else
				{
					if (m_stick[padNumber][LEFT_STICK_X] != 0) m_stick[padNumber][LEFT_STICK_X] = 0;
				}

				// ���X�e�B�b�N�㉺
				if (m_input[padNumber].ThumbLY > stickLY_DeadZoneMAX || m_input[padNumber].ThumbLY < stickLY_DeadZoneMIN)
				{
					m_stick[padNumber][LEFT_STICK_Y] = m_input[padNumber].ThumbLY;
				}
				else
				{
					if (m_stick[padNumber][LEFT_STICK_Y] != 0) m_stick[padNumber][LEFT_STICK_Y] = 0;
				}

				// �E�X�e�B�b�N���E
				if (m_input[padNumber].ThumbRX > stickRX_DeadZoneMAX || m_input[padNumber].ThumbRX < stickRX_DeadZoneMIN)
				{
					m_stick[padNumber][RIGHT_STICK_X] = m_input[padNumber].ThumbRX;
				}
				else
				{
					if (m_stick[padNumber][RIGHT_STICK_X] != 0) m_stick[padNumber][RIGHT_STICK_X] = 0;
				}

				// �E�X�e�B�b�N�㉺
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



			/// �X�e�B�b�N�����|���֌W-----------------------------------------------
			{
				// ���X�e�B�b�N���E�ɉ����|���Ă�����
				if (m_input[padNumber].ThumbLX == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_RIGHT]++;
				}
				// ���X�e�B�b�N�����ɉ����|���Ă�����
				else if (m_input[padNumber].ThumbLX == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_LEFT]++;
				}
				// ���X�e�B�b�N�������|����Ă��Ȃ�������
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


				// ���X�e�B�b�N����ɉ����|���Ă�����
				if (m_input[padNumber].ThumbLY == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_UP]++;
				}
				// ���X�e�B�b�N�����ɉ����|���Ă�����
				else if (m_input[padNumber].ThumbLY == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][LEFT_STICK_DOWN]++;
				}
				// ���X�e�B�b�N�������|����Ă��Ȃ�������
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


				// �E�X�e�B�b�N���E�ɉ����|���Ă�����
				if (m_input[padNumber].ThumbRX == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_RIGHT]++;
				}
				// �E�X�e�B�b�N�����ɉ����|���Ă�����
				else if (m_input[padNumber].ThumbRX == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_LEFT]++;
				}
				// �E�X�e�B�b�N�������|����Ă��Ȃ�������
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


				// �E�X�e�B�b�N����ɉ����|���Ă�����
				if (m_input[padNumber].ThumbRY == STICK_MAX_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_UP]++;
				}
				// �E�X�e�B�b�N�����ɉ����|���Ă�����
				else if (m_input[padNumber].ThumbRY == STICK_MIN_VALUE)
				{
					m_stickCheck[padNumber][RIGHT_STICK_DOWN]++;
				}
				// �E�X�e�B�b�N�������|����Ă��Ȃ�������
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
	void InitAllControl()
	{
		{
			for (int i = 0; i != 3; ++i)
			{
				m_mouse[i] = 0;
			}
			m_mouseInput = 0;
			m_preMouseArea.x = 0;
			m_preMouseArea.y = 0;
			m_mouseArea.x = 0;
			m_mouseArea.y = 0;

			m_mouseWheel = 0;
			m_oldMouseWheel = 0;
		}

		{
			for (int i = 0; i != 256; ++i)
			{
				m_key[i];
				m_tmpKey[i];
			}
		}

		{
			for (int i = 0; i != 4; ++i)
			{
				for (int j = 0; j != 16; ++j)
				{
					m_button[i][j] = 0;
				}

				for (int j = 0; j != 6; ++j)
				{
					m_stick[i][j] = 0;
				}

				for (int j = 0; j != 8; ++j)
				{
					m_stickCheck[i][j] = 0;
				}

				for (int j = 0; j != 2; ++j)
				{
					m_trigger[i][j] = 0;
				}
			}

			stickLX_DeadZoneMAX = 0;
			stickLX_DeadZoneMIN = 0;
			stickLY_DeadZoneMAX = 0;
			stickLY_DeadZoneMIN = 0;
			stickRX_DeadZoneMAX = 0;
			stickRX_DeadZoneMIN = 0;
			stickRY_DeadZoneMAX = 0;
			stickRY_DeadZoneMIN = 0;

			ZeroMemory(m_input, sizeof(XINPUT_STATE));

			m_padNum = 0;
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	void InitMouse()
	{
		for (int i = 0; i != 3; ++i)
		{
			m_mouse[i] = 0;
		}
		m_mouseInput = 0;
		m_preMouseArea.x = 0;
		m_preMouseArea.y = 0;
		m_mouseArea.x = 0;
		m_mouseArea.y = 0;

		m_mouseWheel = 0;
		m_oldMouseWheel = 0;
	}



	/// ------------------------------------------------------------------------------------------------------------
	void InitKey()
	{
		for (int i = 0; i != 256; ++i)
		{
			m_key[i];
			m_tmpKey[i];
		}
	}



	/// ------------------------------------------------------------------------------------------------------------
	void InitPad()
	{
		for (int i = 0; i != 4; ++i)
		{
			for (int j = 0; j != 16; ++j)
			{
				m_button[i][j] = 0;
			}

			for (int j = 0; j != 6; ++j)
			{
				m_stick[i][j] = 0;
			}

			for (int j = 0; j != 8; ++j)
			{
				m_stickCheck[i][j] = 0;
			}

			for (int j = 0; j != 2; ++j)
			{
				m_trigger[i][j] = 0;
			}
		}

		stickLX_DeadZoneMAX = 0;
		stickLX_DeadZoneMIN = 0;
		stickLY_DeadZoneMAX = 0;
		stickLY_DeadZoneMIN = 0;
		stickRX_DeadZoneMAX = 0;
		stickRX_DeadZoneMIN = 0;
		stickRY_DeadZoneMAX = 0;
		stickRY_DeadZoneMIN = 0;

		ZeroMemory(m_input, sizeof(XINPUT_STATE));

		m_padNum = 0;
	}



	/// ------------------------------------------------------------------------------------------------------------
	void AllUpdate(const int& t_GetMousePointX, const int& t_GetMousePointY, const int t_GetMouseWheelRotVol)
	{
		KeyData::UpDate();						// �L�[�{�[�h�̃��[�v����
		PadData::UpDate();						// �Q�[���p�b�h�̃��[�v����
		MouseData::UpDate(t_GetMousePointX, t_GetMousePointY);				// �}�E�X�̃��[�v����
		MouseWheelData::UpDate(t_GetMouseWheelRotVol);		// �}�E�X�z�C�[���̃��[�v����
	}
}