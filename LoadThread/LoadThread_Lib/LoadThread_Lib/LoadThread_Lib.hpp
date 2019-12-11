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
	// 読み込むファイルの種類
	enum class ELOADFILE { graph, soundEffect, model, backGroundMusic, sound3DEffect };

	

	class LoadThread
	{
	private:
		// 非同期を行う
		std::vector<std::thread> ths;

		// ロードした個数
		int num;

		// 最大ロード個数
		int maxNum;

		// ロードしたもの
		std::vector<int> loadData;

		// ロードしたもののタイプ
		std::vector<ELOADFILE> loadType;

		// 非同期を行うメソッド
		void MyNextLoad(const std::string path, int& file, const ELOADFILE type);

		// 終了したかどうか
		bool end;

		// ロード画面
		std::function<void(const int, const int)> m_function;

		// メディアのロードを行う
		void MyLoad(const std::string path, int& file, const ELOADFILE type);


	public:
		// コンストラクタ
		LoadThread();

		// デストラクタ
		~LoadThread();


		// プロセス
		void Process(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type);


		// ロードしたものを渡す
		const std::vector<int> GetFile() const { return loadData; }

		// ロード終えたかどうか
		const bool GetEnd() const { return end; }

		// ロード画面を貰う(ややこしかったのでスタティック関数ポインタが好ましい)
		void SetLoadFunc(std::function<void(const int, const int)> t_loadFunc);
	};
}

#endif