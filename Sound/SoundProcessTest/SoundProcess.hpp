#pragma once

#ifndef _SOUNDPROCESS_LIB_HPP
#define _SOUNDPROCESS_LIB_HPP

#include "DxLib.h"

#include <vector>
#include <string>


class SoundProcess
{
private:
	static std::vector<int> m_SEdata;
	static float m_SEVolume;

	static std::vector<int> m_BGMdata;
	static std::vector<long> m_BGMtotalTime;
	static std::vector<long> m_BGMsampleTime;


public:
	static void Init();

	static void Release();

	static bool LoadSE(const std::string t_seName);

	static bool LoadBGM(const std::string t_bgmName);

	static void SetSEVolume(const float t_volume);

	static const float GetSEVolume();

	static void PlaySE(const int t_seData);

	static void PrintDebug();
};


#endif