#include "stdafx.h"
#include "OptionUI.h"
#include <SceneGame.h>

OptionUI::OptionUI(const std::string& name)
	: GameObject(name)
{
}

void OptionUI::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UI.optionPanel.setPosition(pos);
	UI.bgmButton.sprite.setPosition(UI.optionPanel.getPosition() + sf::Vector2f(30.f, 30.f));
	UI.sfxButton.sprite.setPosition(UI.optionPanel.getPosition() + sf::Vector2f(130.f, 30.f));
}

void OptionUI::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UI.optionPanel.setRotation(rot);
	UI.bgmButton.sprite.setRotation(rot);
	UI.sfxButton.sprite.setRotation(rot);
}

void OptionUI::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UI.optionPanel.setScale(s);
	UI.bgmButton.sprite.setScale(s);
	UI.sfxButton.sprite.setScale(s);
}

void OptionUI::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UI.optionPanel.setOrigin(o);
	UI.bgmButton.sprite.setOrigin(o);
	UI.sfxButton.sprite.setOrigin(o);
}

void OptionUI::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(UI.optionPanel, preset);
		Utils::SetOrigin(UI.bgmButton.sprite, preset);
		Utils::SetOrigin(UI.sfxButton.sprite, preset);
	}
}

void OptionUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	UI.optionPanel.setTexture(TEXTURE_MGR.Get("graphics/optionPanel.png"));
	UI.bgmButton.buttonOnTexId = "graphics/bgmOn.png";
	UI.bgmButton.buttonOffTexId = "graphics/bgmOff.png";
	UI.bgmButton.sprite.setTexture(TEXTURE_MGR.Get(UI.bgmButton.buttonOnTexId));
	UI.sfxButton.buttonOnTexId = "graphics/sfxOn.png";
	UI.sfxButton.buttonOffTexId = "graphics/sfxOff.png";
	UI.sfxButton.sprite.setTexture(TEXTURE_MGR.Get(UI.sfxButton.buttonOnTexId));

	UI.restartButton.sprite.setTexture(TEXTURE_MGR.Get("graphics/textButton.png"));
	UI.restartButton.text.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	UI.restartButton.text.setString(L"다시하기");
	UI.restartButton.Init();
	UI.restartButton.text.setFillColor(sf::Color::Black);
	UI.exitButton.sprite.setTexture(TEXTURE_MGR.Get("graphics/textButton.png"));
	UI.exitButton.text.setFont(FONT_MGR.Get("fonts/Maplestory Light.ttf"));
	UI.exitButton.text.setString(L"나가기");
	UI.exitButton.Init();
	UI.exitButton.text.setFillColor(sf::Color::Black);

	UI.bgmButton.SetPosition(UI.optionPanel.getPosition() + sf::Vector2f(30.f, 30.f));
	UI.sfxButton.SetPosition(UI.optionPanel.getPosition() + sf::Vector2f(130.f, 30.f));
	UI.restartButton.SetPosition(UI.optionPanel.getPosition() + sf::Vector2f(115.f, 170.f));
	UI.exitButton.SetPosition(UI.optionPanel.getPosition() + sf::Vector2f(115.f, 270.f));

	UI.bgmButton.SetCallBack([&]()
		{
			if (UI.bgmButton.isOn)
			{
				UI.bgmButton.isOn = false;
				UI.bgmButton.sprite.setTexture(TEXTURE_MGR.Get(UI.bgmButton.buttonOffTexId));
				SOUND_MGR.PlaySfx("sound/click.mp3");
				SOUND_MGR.SetBgmVolume(0.f);
			}
			else
			{
				UI.bgmButton.isOn = true;
				UI.bgmButton.sprite.setTexture(TEXTURE_MGR.Get(UI.bgmButton.buttonOnTexId));
				SOUND_MGR.PlaySfx("sound/click.mp3");
				SOUND_MGR.SetBgmVolume(SOUND_MGR.DEFAULT_BGM_VOLUME);
			}
		}
	);

	UI.sfxButton.SetCallBack([&]()
		{
			if (UI.sfxButton.isOn)
			{
				UI.sfxButton.isOn = false;
				UI.sfxButton.sprite.setTexture(TEXTURE_MGR.Get(UI.sfxButton.buttonOffTexId));
				SOUND_MGR.PlaySfx("sound/click.mp3");
				SOUND_MGR.SetSfxVolume(0.f);
			}
			else
			{
				UI.sfxButton.isOn = true;
				UI.sfxButton.sprite.setTexture(TEXTURE_MGR.Get(UI.sfxButton.buttonOnTexId));
				SOUND_MGR.SetSfxVolume(SOUND_MGR.DEFAULT_SFX_VOLUME);
				SOUND_MGR.PlaySfx("sound/click.mp3");
			}
		}
	);

	UI.restartButton.SetCallBack([this]()
		{
			((SceneGame*)SCENE_MGR.GetCurrentScene())->isPlaying = true;
			SCENE_MGR.ChangeScene(SCENE_MGR.GetCurrentSceneId());
			SOUND_MGR.PlaySfx("sound/click.mp3");
			active = false;
		}
	);

	UI.exitButton.SetCallBack([this]()
		{
			SCENE_MGR.ChangeScene(SceneIds::Lobby);
			SOUND_MGR.PlaySfx("sound/click.mp3");
			active = false;
		}
	);
}

void OptionUI::Release()
{
}

void OptionUI::Reset()
{
	if (SOUND_MGR.GetIsBgmOn())
	{
		UI.bgmButton.isOn = true;
		UI.bgmButton.sprite.setTexture(TEXTURE_MGR.Get(UI.bgmButton.buttonOnTexId));
	}
	else
	{
		UI.bgmButton.isOn = false;
		UI.bgmButton.sprite.setTexture(TEXTURE_MGR.Get(UI.bgmButton.buttonOffTexId));
	}

	if (SOUND_MGR.GetIsSfxOn())
	{
		UI.sfxButton.isOn = true;
		UI.sfxButton.sprite.setTexture(TEXTURE_MGR.Get(UI.sfxButton.buttonOnTexId));
	}
	else
	{
		UI.sfxButton.isOn = false;
		UI.sfxButton.sprite.setTexture(TEXTURE_MGR.Get(UI.sfxButton.buttonOffTexId));
	}
}

void OptionUI::Update(float dt)
{
	UI.bgmButton.Update(dt);
	UI.sfxButton.Update(dt);
	UI.restartButton.Update(dt);
	UI.exitButton.Update(dt);
}

void OptionUI::Draw(sf::RenderWindow& window)
{
	window.draw(UI.optionPanel);
	UI.bgmButton.Draw(window);
	UI.sfxButton.Draw(window);
	UI.restartButton.Draw(window);
	UI.exitButton.Draw(window);
}