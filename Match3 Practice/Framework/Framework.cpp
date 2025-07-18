#include "stdafx.h"
#include "Framework.h"
#include "Animator.h"

void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);

    // texIds, fontIds, soundIds
    texIds.push_back("graphics/cursor.png");
    texIds.push_back("graphics/blocks.png");
    texIds.push_back("graphics/tiles.png");
    texIds.push_back("graphics/sparkles.png");
    texIds.push_back("graphics/bg_sky.png");
    texIds.push_back("graphics/backgroundPanel.png");
    texIds.push_back("graphics/swapCountPanel.png"); 
    texIds.push_back("graphics/targetCountPanel.png");
    texIds.push_back("graphics/stageLevelPanel.png");
    texIds.push_back("graphics/button.png");
    texIds.push_back("graphics/optionPanel.png");
    texIds.push_back("graphics/option.png");
    texIds.push_back("graphics/bgmOn.png");
    texIds.push_back("graphics/bgmOff.png");
    texIds.push_back("graphics/sfxOn.png");
    texIds.push_back("graphics/sfxOff.png");

    fontIds.push_back("fonts/Maplestory Light.ttf");

    soundIds.push_back("sound/backgroundBgm.mp3");
    soundIds.push_back("sound/click.mp3");
    soundIds.push_back("sound/swapSound.mp3");
    soundIds.push_back("sound/pop.mp3");
    soundIds.push_back("sound/clear.mp3");
    soundIds.push_back("sound/defeat.mp3");

	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);
    ANI_CLIP_MGR.Load("animations/sparkle.csv");

    Utils::Init();
	InputMgr::Init();
    SOUND_MGR.Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        time += deltaTime;
        realTime = realDeltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateEvent(event);
        }

        InputMgr::Update(deltaTime);

        // Update
        SOUND_MGR.Update(deltaTime);
        SCENE_MGR.Update(deltaTime);

        // Draw
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SOUND_MGR.Release();
	SCENE_MGR.Release();

	SOUNDBUFFER_MGR.Unload(soundIds);
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
    ANI_CLIP_MGR.Unload("animations/sparkle.csv");
}