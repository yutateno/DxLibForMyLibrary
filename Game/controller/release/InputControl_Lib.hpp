#pragma once

#include "DxLib.h"


namespace InputControl
{
	// �}�E�X
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
		//���N���b�N���E�N���b�N��
		enum class CLICK
		{
			LEFT,
			RIGHT,
			CENTER
		};


		//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
		static void UpDate();

		//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
		static const int& GetClick(const CLICK& t_CLICK);

		// ���݂̃}�E�X�̈ʒu
		static const MouseXY& GetMouseArea();

		// ���O����ǂꂭ�炢�ړ�������
		static const MouseXY GetMouseMoveValue();
	};



	// �}�E�X�z�C�[��
	class MouseWheelData
	{
	private:
		static int m_mouseWheel;
		static int m_oldMouseWheel;
	

	public:
		//�}�E�X�̃z�C�[���̏�Ԃ��X�V
		static void UpDate();

		//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
		static const int& GetMouseWheel();
	};



	// �L�[�{�[�h�̓��͏��
	class KeyData
	{
	private:
		static int m_key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
		static char m_tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����
	

	public:
		static void UpDate();			// �L�[���͂̏�ԍX�V


		static const int& Get(const int& t_keyCode);		// �L�[���͏�Ԏ擾
		static const bool IsCheckEnd();					// �����I��
	};



	// �Q�[���p�b�h�̓��͏��
	class PadData
	{
	private:
		static int m_button[4][16];		// �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
		static int m_stick[4][6];		// �Q�[���p�b�h�̃X�e�B�b�N�֘A�̓��͏�Ԏ��[�p�ϐ�
		static int m_stickCheck[4][8];	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ��[�p�ϐ��̍ő�܂ł̓|���`�F�b�N
		static int m_trigger[4][2];		// �Q�[���p�b�h�̃g���K�[�̓��͏�Ԏ��[�p�ϐ�


		// �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
		static short stickLX_DeadZoneMAX;
		static short stickLX_DeadZoneMIN;
		static short stickLY_DeadZoneMAX;
		static short stickLY_DeadZoneMIN;
		static short stickRX_DeadZoneMAX;
		static short stickRX_DeadZoneMIN;
		static short stickRY_DeadZoneMAX;
		static short stickRY_DeadZoneMIN;


		static XINPUT_STATE m_input[4];	// �Q�[���p�b�h�̃i���o�[
		static char m_padNum;			// �q�����Ă�Q�[���p�b�h�̐�


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

		static void UpDate();		// �Q�[���p�b�h�̓��͂̏�ԍX�V


		static const int& GetButton(const int& t_code, const int& t_padNum);									// �{�^���̓��͏�Ԏ擾
		static const int& GetTrigger(const int& t_code, const int& t_padNum);								// �g���K�[�̎擾
		static const int& GetStick(const int& t_code, const int& t_padNum);									// �X�e�B�b�N�̓��͏�Ԏ擾
		static const int& GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue);	// �X�e�B�b�N�̉����|���擾


		static const bool IsCheckEnd();																		// �����I��
		static const char& GetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h�̐�


		static void SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
			, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN);					// �f�b�h�]�[���̐ݒ�
		static void SetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h���擾����
	};
	
	void AllUpdate();
}