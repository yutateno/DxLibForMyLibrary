#pragma once

#ifdef INPUTCONTROL_EXPORTS
#define INPUTCONTROL_API __declspec(dllexport)
#else
#define INPUTCONTROL_API __declspec(dllimport)
#endif

#include "DxLib.h"


namespace InputControl
{
	// �}�E�X
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
		//���N���b�N���E�N���b�N��
		namespace CLICK
		{
			const short LEFT = 0;
			const short RIGHT = 1;
			const short CENTER = 2;
		}


		//�}�E�X�̃N���b�N�̏�Ԃ��X�V����
		INPUTCONTROL_API void UpDate(const int& GetMousePointX, const int& GetMousePointY);

		//�}�E�X�̃N���b�N�̏�Ԃ�Ԃ�
		INPUTCONTROL_API const int& GetClick(const short& t_CLICK);

		// ���݂̃}�E�X�̈ʒu
		INPUTCONTROL_API const MouseDataInternal::MouseXY& GetMouseArea();

		// ���O����ǂꂭ�炢�ړ�������
		INPUTCONTROL_API const MouseDataInternal::MouseXY GetMouseMoveValue();
	};



	// �}�E�X�z�C�[��
	namespace MouseWheelDataInternal
	{
		int m_mouseWheel;
		int m_oldMouseWheel;
	}
	namespace MouseWheelData
	{
		//�}�E�X�̃z�C�[���̏�Ԃ��X�V
		INPUTCONTROL_API void UpDate(const int t_GetMouseWheelRotVol);

		//�}�E�X�z�C�[���̏�Ԃ�Ԃ�
		INPUTCONTROL_API const int& GetMouseWheel();
	};



	// �L�[�{�[�h�̓��͏��
	namespace KeyDataInternal
	{
		int m_key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
		char m_tmpKey[256];	// ���݂̃L�[�̓��͏�Ԃ��i�[����
	}
	namespace KeyData
	{
		INPUTCONTROL_API void UpDate();			// �L�[���͂̏�ԍX�V


		INPUTCONTROL_API const int& Get(const int& t_keyCode);		// �L�[���͏�Ԏ擾
		INPUTCONTROL_API const bool IsCheckEnd();					// �����I��
	};



	// �Q�[���p�b�h�̓��͏��
	namespace PadDataInternal
	{
		int m_button[4][16];		// �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
		int m_stick[4][6];		// �Q�[���p�b�h�̃X�e�B�b�N�֘A�̓��͏�Ԏ��[�p�ϐ�
		int m_stickCheck[4][8];	// �Q�[���p�b�h�̃X�e�B�b�N�̓��͏�Ԏ��[�p�ϐ��̍ő�܂ł̓|���`�F�b�N
		int m_trigger[4][2];		// �Q�[���p�b�h�̃g���K�[�̓��͏�Ԏ��[�p�ϐ�


		// �Q�[���p�b�h�̃X�e�B�b�N�̃f�b�h�]�[�����l��ۑ�
		short stickLX_DeadZoneMAX;
		short stickLX_DeadZoneMIN;
		short stickLY_DeadZoneMAX;
		short stickLY_DeadZoneMIN;
		short stickRX_DeadZoneMAX;
		short stickRX_DeadZoneMIN;
		short stickRY_DeadZoneMAX;
		short stickRY_DeadZoneMIN;


		XINPUT_STATE m_input[4];	// �Q�[���p�b�h�̃i���o�[
		char m_padNum;			// �q�����Ă�Q�[���p�b�h�̐�
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

		INPUTCONTROL_API void UpDate();		// �Q�[���p�b�h�̓��͂̏�ԍX�V


		INPUTCONTROL_API const int& GetButton(const int& t_code, const int& t_padNum);									// �{�^���̓��͏�Ԏ擾
		INPUTCONTROL_API const int& GetTrigger(const int& t_code, const int& t_padNum);								// �g���K�[�̎擾
		INPUTCONTROL_API const int& GetStick(const int& t_code, const int& t_padNum);									// �X�e�B�b�N�̓��͏�Ԏ擾
		INPUTCONTROL_API const int& GetStickCheck(const int& t_code, const int& t_padNum, const bool& t_leftAndDownIsTrue);	// �X�e�B�b�N�̉����|���擾


		INPUTCONTROL_API const bool IsCheckEnd();																		// �����I��
		INPUTCONTROL_API const char& GetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h�̐�


		INPUTCONTROL_API void SetDedZone(const short& t_stickLX_MAX, const short& t_stickLX_MIN, const short& t_stickLY_MAX, const short& t_stickLY_MIN
			, const short& t_stickRX_MAX, const short& t_stickRX_MIN, const short& t_stickRY_MAX, const short& t_stickRY_MIN);					// �f�b�h�]�[���̐ݒ�
		INPUTCONTROL_API void SetPadNum();																		// �ڑ�����Ă�Q�[���p�b�h���擾����
	}

	INPUTCONTROL_API void InitAllControl();
	INPUTCONTROL_API void InitMouse();
	INPUTCONTROL_API void InitKey();
	INPUTCONTROL_API void InitPad();

	INPUTCONTROL_API void AllUpdate(const int& GetMousePointX, const int& GetMousePointY, const int t_GetMouseWheelRotVol);
}