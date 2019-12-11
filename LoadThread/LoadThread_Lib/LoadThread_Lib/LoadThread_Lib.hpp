#pragma once

#ifndef _LOADTHREAD_LIB_HPP
#define _LOADTHREAD_LIB_HPP

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <functional>

#include "DxLib.h"



namespace LoadThread_Lib
{
	// �ǂݍ��ރt�@�C���̎��
	enum class ELOADFILE { graph, soundEffect, model, backGroundMusic, sound3DEffect };

	

	class LoadThread
	{
	private:
		// �񓯊����s��
		std::vector<std::thread> ths;

		// ���[�h������
		int num;

		// �ő働�[�h��
		int maxNum;

		// ���[�h��������
		std::vector<int> loadData;

		// ���[�h�������̂̃^�C�v
		std::vector<ELOADFILE> loadType;

		// �񓯊����s�����\�b�h
		void MyNextLoad(const std::string path, int& file, const ELOADFILE type);

		// �I���������ǂ���
		bool end;

		// ���[�h���
		std::function<void(const int, const int)> m_function;

		// ���f�B�A�̃��[�h���s��
		void MyLoad(const std::string path, int& file, const ELOADFILE type);


	public:
		// �R���X�g���N�^
		LoadThread();

		// �f�X�g���N�^
		~LoadThread();


		// �v���Z�X
		void Process(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type);


		// ���[�h�������̂�n��
		const std::vector<int> GetFile() const { return loadData; }

		// ���[�h�I�������ǂ���
		const bool GetEnd() const { return end; }

		// ���[�h��ʂ�Ⴄ(��₱���������̂ŃX�^�e�B�b�N�֐��|�C���^���D�܂���)
		void SetLoadFunc(std::function<void(const int, const int)> t_loadFunc);
	};
}

#endif