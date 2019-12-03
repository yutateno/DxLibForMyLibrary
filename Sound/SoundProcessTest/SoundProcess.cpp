#include "SoundProcess.hpp"



/// -------------------------------------------------------------------------------
std::vector<std::string> SoundProcess::m_SEdata;

std::vector<std::string> SoundProcess::m_BGMdata;
std::vector<long> SoundProcess::m_BGMtotalTime;
std::vector<long> SoundProcess::m_BGMsampleTime;



/// -------------------------------------------------------------------------------
void SoundProcess::Init()
{
	std::vector<std::string>().swap(m_SEdata);
	std::vector<std::string>().swap(m_BGMdata);
	std::vector<long>().swap(m_BGMtotalTime);
	std::vector<long>().swap(m_BGMsampleTime);
}



/// -------------------------------------------------------------------------------
void SoundProcess::Release()
{
	std::vector<std::string>().swap(m_SEdata);
	std::vector<std::string>().swap(m_BGMdata);
	std::vector<long>().swap(m_BGMtotalTime);
	std::vector<long>().swap(m_BGMsampleTime);
}



/// -------------------------------------------------------------------------------
bool SoundProcess::LoadSE(int& t_seData, const std::string t_seName, const std::string t_intVarName)
{ 
	t_seData = LoadSoundMem(t_seName.c_str());
	if (t_seData == -1) return false;

	m_SEdata.push_back(t_intVarName);

	return true;
}



/// -------------------------------------------------------------------------------
bool SoundProcess::LoadBGM(int& t_bgmData, std::string t_bgmName, const std::string t_intVarName)
{
	t_bgmData = LoadSoundMem(t_bgmName.c_str());
	if (t_bgmData == -1) return false;

	m_BGMdata.push_back(t_intVarName);
	m_BGMtotalTime.push_back(GetSoundTotalTime(t_bgmData));
	m_BGMsampleTime.push_back(GetSoundTotalSample(t_bgmData));

	return true;
}



/// -------------------------------------------------------------------------------
void SoundProcess::PlaySE(const int t_seData)
{
	PlaySoundMem(t_seData, DX_PLAYTYPE_BACK);
}



/// -------------------------------------------------------------------------------
void SoundProcess::PrintDebug()
{
}
