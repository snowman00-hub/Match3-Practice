#include "stdafx.h"
#include "Button.h"

Button::Button(const std::string& name)
	: GameObject(name)
{
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
	text.setPosition(pos - sf::Vector2f(0.f, 10.f));
}

void Button::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
	text.setRotation(rot);
}

void Button::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
	text.setScale(s);
}

void Button::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
	text.setOrigin(o);
}

void Button::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
		Utils::SetOrigin(text, preset);
	}
}

void Button::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	SetOrigin(Origins::MC);
	text.setPosition(sprite.getPosition() - sf::Vector2f(0.f,10.f));
}

void Button::Release()
{
}

void Button::Reset()
{
}

void Button::Update(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) &&
		sprite.getGlobalBounds().contains((sf::Vector2f)InputMgr::GetMousePosition()))
	{
		if (event)
			event();
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(text);
}