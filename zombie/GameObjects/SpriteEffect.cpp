#include "stdafx.h"
#include "SpriteEffect.h"
#include "Zombie.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Utils.h"

SpriteEffect::SpriteEffect(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void SpriteEffect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void SpriteEffect::Reset()
{
	SpriteGo::Reset();
	timer = 0.f;
	sprite.setColor(sf::Color::Color(255, 255, 255, 255));
}


void SpriteEffect::Update(float dt)
{
	SpriteGo::Update(dt);

	timer += dt;

	sf::Color a = { 255, 255, 255, 0 };
	sf::Color b = sf::Color::White;
	sf::Color color = Utils::Lerp(a, b, duration - timer);

	sprite.setColor(sf::Color::Color(color));

	if (timer >= duration)
	{
		if (pool != nullptr)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
	}
}
