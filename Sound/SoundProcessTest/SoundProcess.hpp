#pragma once
#include "DxLib.h"

#include <vector>
#include <string>

/*
ğŒ
‚PF‘fŞ‚ğƒ[ƒh‚µ‚È‚¢
‚QF‘fŞ‚ğQÆ‚µ‚ÄÄ¶
‚RF‰¹—Ê‚à‚±‚¿‚ç‚Ås‚¤
‚SF‘Šè‘¤‚Íg‚¤‘fŞ‚ğŠÖ”‚ÉŒÄ‚Ño‚·‚¾‚¯‚É‚³‚¹‚é
*/
class SoundProcess
{
private:
	static std::vector<std::string> m_SEdata;

	static std::vector<std::string> m_BGMdata;
	static std::vector<long> m_BGMtotalTime;
	static std::vector<long> m_BGMsampleTime;


public:
	static void Init();

	static void Release();

	static bool LoadSE(int& t_seData, const std::string t_seName, const std::string t_intVarName);

	static bool LoadBGM(int& t_bgmData, std::string t_bgmName, const std::string t_intVarName);

	static void PlaySE(const int t_seData);

	static void PrintDebug();
};

