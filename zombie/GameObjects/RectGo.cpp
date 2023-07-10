#include "stdafx.h"
#include "RectGo.h"
#include "Utils.h"

RectGo::RectGo(const std::string& n)
    : GameObject(n)
{
}

RectGo::~RectGo()
{
}

sf::RectangleShape& RectGo::GetRect()
{
    return rect;
}

void RectGo::SetPosition(const sf::Vector2f& p)
{
    rect.setPosition(p);
}

void RectGo::SetPosition(float x, float y)
{
    rect.setPosition(x, y);
}

void RectGo::SetOrigin(Origins origin)
{
    Utils::SetOrigin(rect, origin);

    if (this->origin != Origins::CUSTOM)
    {
        Utils::SetOrigin(rect, origin);
    }
}

void RectGo::SetOrigin(float x, float y)
{
    GameObject::SetOrigin(x, y);
    rect.setOrigin(x, y);
}

void RectGo::Init()
{
}

void RectGo::Release()
{
}

void RectGo::Reset()
{
}

void RectGo::Update(float dt)
{
}

void RectGo::Draw(sf::RenderWindow& window)
{
    window.draw(rect);
}
