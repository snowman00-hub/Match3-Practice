#pragma once

class SoundMgr : public Singleton<SoundMgr>
{
	friend Singleton<SoundMgr>;

protected:
	SoundMgr() = default;
	virtual ~SoundMgr() = default;

	SoundMgr(const SoundMgr& other) = delete;
	SoundMgr& operator=(const SoundMgr& other) = delete;

	sf::Sound bgm;

	std::list<sf::Sound*> playing;
	std::list<sf::Sound*> waiting;

	float bgmVolume = 30.f;
	float sfxVolume = 40.f;

public:
	const float DEFAULT_BGM_VOLUME = 30.f;
	const float DEFAULT_SFX_VOLUME = 40.f;
	bool GetIsBgmOn() { return bgmVolume != 0.f; }
	bool GetIsSfxOn() { return sfxVolume != 0.f; }

	void SetBgmVolume(float v)
	{
		bgmVolume = v;
		bgm.setVolume(bgmVolume);
	}

	void SetSfxVolume(float v);

	void Init(int totalChannels = 64);
	void Release();
	void Update(float dt);

	void PlayBgm(std::string id, bool loop = true);
	void PlayBgm(sf::SoundBuffer& buffer, bool loop = true);
	void StopBgm();

	void PlaySfx(std::string id, bool loop = false);
	void PlaySfx(sf::SoundBuffer& buffer, bool loop = false);

	void StopAllSfx();
};

#define SOUND_MGR (SoundMgr::Instance())