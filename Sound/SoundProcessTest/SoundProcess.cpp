#include "SoundProcess.hpp"



/// -------------------------------------------------------------------------------
std::vector<int> SoundProcess::m_SEdata;

std::vector<int> SoundProcess::m_BGMdata;
std::vector<long> SoundProcess::m_BGMtotalTime;
std::vector<long> SoundProcess::m_BGMsampleTime;

float SoundProcess::m_SEVolume;



/// -------------------------------------------------------------------------------
void SoundProcess::Init()
{
	std::vector<int>().swap(m_SEdata);
	std::vector<int>().swap(m_BGMdata);
	std::vector<long>().swap(m_BGMtotalTime);
	std::vector<long>().swap(m_BGMsampleTime);

	m_SEVolume = 1.0f;
}



/// -------------------------------------------------------------------------------
void SoundProcess::Release()
{
	std::vector<int>().swap(m_SEdata);
	std::vector<int>().swap(m_BGMdata);
	std::vector<long>().swap(m_BGMtotalTime);
	std::vector<long>().swap(m_BGMsampleTime);
}



/// -------------------------------------------------------------------------------
bool SoundProcess::LoadSE(const std::string t_seName)
{ 
	m_SEdata.push_back(LoadSoundMem(t_seName.c_str()));
	if (m_SEdata.at(m_SEdata.size() - 1) == -1) return false;

	return true;
}



/// -------------------------------------------------------------------------------
bool SoundProcess::LoadBGM(const std::string t_bgmName)
{
	m_BGMdata.push_back(LoadSoundMem(t_bgmName.c_str()));
	if (m_BGMdata.at(m_BGMdata.size() - 1) == -1) return false;

	m_BGMtotalTime.push_back(GetSoundTotalTime(m_BGMdata.at(m_BGMdata.size() - 1)));
	m_BGMsampleTime.push_back(GetSoundTotalSample(m_BGMdata.at(m_BGMdata.size() - 1)));

	return true;
}



/// -------------------------------------------------------------------------------
void SoundProcess::SetSEVolume(const float t_volume)
{
	m_SEVolume = t_volume;
}



/// -------------------------------------------------------------------------------
const float SoundProcess::GetSEVolume()
{
	return m_SEVolume;
}



/// -------------------------------------------------------------------------------
void SoundProcess::PlaySE(const int t_seData)
{
	PlaySoundMem(t_seData, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(static_cast<int>(255.0f * m_SEVolume), t_seData);
}



/// -------------------------------------------------------------------------------
void SoundProcess::PrintDebug()
{
}
