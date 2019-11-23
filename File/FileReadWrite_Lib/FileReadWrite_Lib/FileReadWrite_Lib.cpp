#include "pch.h"
#include "FileReadWrite_Lib.hpp"




/// ----------------------------------------------------------------------------------------------
namespace FileReadWrite_Lib
{
	/// ----------------------------------------------------------------------------------------------
	std::vector<std::vector<std::string>> FileReaderWrite::m_mapdata;



	/// ----------------------------------------------------------------------------------------------
	void FileReaderWrite::Init()
	{
		std::vector<std::vector<std::string>>().swap(m_mapdata);
	}



	/// ----------------------------------------------------------------------------------------------
	bool FileReaderWrite::FileCSVRead(const std::string t_file)
	{
		std::ifstream writeFile(t_file);

		// マップデータ読み込み失敗
		if (writeFile.fail())
		{
			std::cerr << "LoadError" << std::endl;
			return false;
		}


		// 仮置き
		std::string str;
		int count = 0;
		int arrayCount = 0;

		while (getline(writeFile, str))
		{
			// 仮置き
			std::string token;
			std::istringstream stream(str);

			// メモリ確保
			m_mapdata.resize(++count);
			arrayCount = count - 1;

			while (getline(stream, token, ','))
			{
				m_mapdata[arrayCount].push_back(token);
			}
		}


		// ファイルを閉じる
		writeFile.close();


		return true;
	}



	/// ----------------------------------------------------------------------------------------------
	std::vector<std::vector<std::string>> FileReaderWrite::GetMapData()
	{
		return m_mapdata;
	}



	/// ----------------------------------------------------------------------------------------------
	bool FileReaderWrite::FileCSVWrite(const std::string t_file, const std::vector<std::vector<std::string>> t_data)
	{
		// ファイルを読み込む
		std::ofstream saveFile(t_file);

		// ファイル読み込み失敗
		if (saveFile.fail())
		{
			std::cerr << "LoadError" << std::endl;
			return false;
		}


		for (int i = 0; i != t_data.size(); ++i)
		{
			for (int j = 0; j != t_data[i].size(); ++j)
			{
				if (j == t_data[i].size() - 1)
				{
					saveFile << t_data[i][j] << std::endl;
				}
				else
				{
					saveFile << t_data[i][j] << ",";
				}
			}
		}


		// ファイルを閉じる
		saveFile.close();


		return true;
	}
}