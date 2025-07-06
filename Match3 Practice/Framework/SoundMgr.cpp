#include "stdafx.h"
#include "SoundMgr.h"

sf::Sound SoundMgr::soundBackground;
sf::Sound SoundMgr::soundCoin;

void SoundMgr::Init()
{
	soundBackground.setBuffer(SOUNDBUFFER_MGR.Get("sound/backgroundBgm.wav"));
	soundCoin.setBuffer(SOUNDBUFFER_MGR.Get("sound/coin.wav"));
}