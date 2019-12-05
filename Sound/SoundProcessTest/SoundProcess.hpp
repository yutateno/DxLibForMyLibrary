#pragma once
#include "DxLib.h"

#include <vector>
#include <string>

/*
条件
１：素材をロードしない
２：素材を参照して再生
３：音量もこちらで行う
４：相手側は使う素材を関数に呼び出すだけにさせる
*/
class SoundProcess
{
private:
	static std::vector<std::string> m_SEdata;
	static float m_SEVolume;

	static std::vector<std::string> m_BGMdata;
	static std::vector<long> m_BGMtotalTime;
	static std::vector<long> m_BGMsampleTime;


public:
	static void Init();

	static void Release();

	static bool LoadSE(int& t_seData, const std::string t_seName, const std::string t_intVarName);

	static bool LoadBGM(int& t_bgmData, std::string t_bgmName, const std::string t_intVarName);

	static void SetSEVolume(const float t_volume);

	static const float GetSEVolume();

	static void PlaySE(const int t_seData);

	static void PrintDebug();
};

