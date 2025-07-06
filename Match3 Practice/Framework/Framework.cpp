#include "stdafx.h"
#include "Framework.h"

void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);

    // texIds, fontIds, soundIds
    texIds.push_back("graphics/greenJem.png");
    texIds.push_back("graphics/redJem.png");
    texIds.push_back("graphics/yellowJem.png");
    texIds.push_back("graphics/blueJem.png");
    texIds.push_back("graphics/tileDefault.png");
    texIds.push_back("graphics/sparkles.png");
    texIds.push_back("graphics/diamond.png");
    texIds.push_back("graphics/emerald.png");
    texIds.push_back("graphics/boxObstacle.png");
    texIds.push_back("graphics/bg_sky.png");
    texIds.push_back("graphics/bg_day.jpg");
    texIds.push_back("graphics/Blocks.png");

    fontIds.push_back("fonts/Maplestory Light.ttf");

    soundIds.push_back("sound/backgroundBgm.wav");
    soundIds.push_back("sound/coin.wav");

	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

    Utils::Init();
	InputMgr::Init();
    SoundMgr::Init();
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
        SCENE_MGR.Update(deltaTime);

        // Draw
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
	SCENE_MGR.Release();

	SOUNDBUFFER_MGR.Unload(soundIds);
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
}