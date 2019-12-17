#pragma once

#ifndef _LOADTHREAD_LIB_HPP
#define _LOADTHREAD_LIB_HPP

#include <vector>
#include <string>
#include <functional>
#include "DxLib.h"



namespace LoadThread_Lib
{
	enum class ELOADFILE { graph, soundEffect, model, backGroundMusic, sound3DEffect };

	/*
	�񓯊��Ń��[�h���s���N���X
	*/
	class LoadThread
	{
	private:
		// ���[�h������
		int num;

		// �ő働�[�h��
		int maxNum;

		// ���[�h��������
		std::vector<int> loadData;

		// ���[�h�������̂̃^�C�v
		std::vector<ELOADFILE> loadType;

		// �I���������ǂ���
		bool end;

		// ���[�h���
		std::function<void(const int, const int, const int)> m_function;

		// ���[�h�̎���
		int time;


	public:
		// �R���X�g���N�^
		LoadThread(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type, std::function<void(const int, const int, const int)> t_loadFunc);

		// �f�X�g���N�^
		~LoadThread();


		// �v���Z�X
		void Process();


		// ���[�h�������̂�n��
		const std::vector<int> GetFile() const;

		// ���[�h�I�������ǂ���
		const bool GetEnd() const;
	};
}

#endif