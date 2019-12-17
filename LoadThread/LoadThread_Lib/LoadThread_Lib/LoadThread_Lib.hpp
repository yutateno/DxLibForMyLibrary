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
	非同期でロードを行うクラス
	*/
	class LoadThread
	{
	private:
		// ロードした個数
		int num;

		// 最大ロード個数
		int maxNum;

		// ロードしたもの
		std::vector<int> loadData;

		// ロードしたもののタイプ
		std::vector<ELOADFILE> loadType;

		// 終了したかどうか
		bool end;

		// ロード画面
		std::function<void(const int, const int, const int)> m_function;

		// ロードの時間
		int time;


	public:
		// コンストラクタ
		LoadThread(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type, std::function<void(const int, const int, const int)> t_loadFunc);

		// デストラクタ
		~LoadThread();


		// プロセス
		void Process();


		// ロードしたものを渡す
		const std::vector<int> GetFile() const;

		// ロード終えたかどうか
		const bool GetEnd() const;
	};
}

#endif