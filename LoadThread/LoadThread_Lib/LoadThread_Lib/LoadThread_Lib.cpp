#include "pch.h"
#include "LoadThread_Lib.hpp"


namespace LoadThread_Lib
{
	using namespace std;
	mutex mtx;


	/// ---------------------------------------------------------------------------------------
	void LoadThread::MyNextLoad(const std::string path, int& file, const ELOADFILE type)
	{
		lock_guard<mutex> lock(mtx);

		MyLoad(path, file, type);

		ClearDrawScreen();
		m_function(num++, maxNum);
		ScreenFlip();
	}



	/// ---------------------------------------------------------------------------------------
	void LoadThread::MyLoad(const string path, int& file, const ELOADFILE type)
	{
		// ロードする
		switch (type)
		{
			// UI関係の画像のとき
		case ELOADFILE::graph:
			file = LoadGraph(path.c_str());
			break;


			// 2D系SEのとき
		case ELOADFILE::soundEffect:
			file = LoadSoundMem(path.c_str());
			break;


			// モデルデータのとき
		case ELOADFILE::model:
			file = MV1LoadModel(path.c_str());
			break;


			// BGMのとき
		case ELOADFILE::backGroundMusic:
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			file = LoadSoundMem(path.c_str());
			SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
			break;


			// 3Dサウンドのとき
		case ELOADFILE::sound3DEffect:
			SetCreate3DSoundFlag(TRUE);
			file = LoadSoundMem(path.c_str());
			SetCreate3DSoundFlag(FALSE);
			break;


		default:
			break;
		}
	}



	/// ---------------------------------------------------------------------------------------
	LoadThread::LoadThread()
	{
		num = 0;
		maxNum = 0;
		end = false;

		std::vector<int>().swap(loadData);
		std::vector<ELOADFILE>().swap(loadType);
	}



	/// ---------------------------------------------------------------------------------------
	LoadThread::~LoadThread()
	{
		for (int i = 0; i < loadType.size(); ++i)
		{
			switch (loadType.at(i))
			{
				// UI関係の画像のとき
			case ELOADFILE::graph:
				DeleteGraph(loadData.at(i));
				break;


				// 2D系SEのとき
			case ELOADFILE::soundEffect:
				DeleteSoundMem(loadData.at(i));
				break;


				// モデルデータのとき
			case ELOADFILE::model:
				MV1DeleteModel(loadData.at(i));
				break;


				// BGMのとき
			case ELOADFILE::backGroundMusic:
				DeleteSoundMem(loadData.at(i));
				break;


				// 3Dサウンドのとき
			case ELOADFILE::sound3DEffect:
				DeleteSoundMem(loadData.at(i));
				break;


			default:
				break;
			}
		}
		std::vector<int>().swap(loadData);
		std::vector<ELOADFILE>().swap(loadType);
	}



	/// ---------------------------------------------------------------------------------------
	void LoadThread::Process(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type)
	{
		if (end) return;

		maxNum = max;
		loadData.resize(max);

		for (int i = 0; i < max; ++i)
		{
			ths.push_back(thread(&LoadThread::MyNextLoad, this, path.at(i), ref(loadData.at(i)), type.at(i)));
			ths.at(i).join();
		}

		loadType = type;

		end = true;
	}



	/// ---------------------------------------------------------------------------------------
	void LoadThread::SetLoadFunc(std::function<void(const int, const int)> t_loadFunc)
	{
		m_function = t_loadFunc;
	}
}