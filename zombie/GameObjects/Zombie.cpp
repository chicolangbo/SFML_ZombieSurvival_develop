#include "stdafx.h"
#include "Zombie.h"
#include "InputMgr.h"
#include "Player.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "DataTableMgr.h"
#include "ZombieTable.h"

//const std::string Zombie::textureIds[3] = {
//		"graphics/bloater.png",
//		"graphics/chaser.png",
//		"graphics/crawler.png",
//};
//const float Zombie::speedStats[3] = { 40.f, 70.f, 20.f };
//const int Zombie::hpStats[3] = { 100, 75, 50 };
//const int Zombie::damageStats[3] = { 10, 5, 7 };
//const float Zombie::attackRateStats[3] = { 2.f, 0.5, 1.f };

Zombie::Zombie(const std::string& n)
	: SpriteGo("", n)
{

}

Zombie::~Zombie()
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();

	hp = maxHp;
	attackTimer = attackRate;
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);

	if (player == nullptr)
		return;

	float distance = Utils::Distance(player->GetPosition(), position);

	look = direction = Utils::Normalize(player->GetPosition() - position);
	sprite.setRotation(Utils::Angle(look));

	if (distance > 25.f)
	{
		position += direction * speed * dt;
		sprite.setPosition(position);
	}

	attackTimer += dt;
	if (attackTimer > attackRate)
	{
		if (player->isAlive && sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
		{
			attackTimer = 0.f;
			player->OnHitted(damage);
		}
	}

}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::SetType(Types t)
{
	//zombieType = t;
	
	const ZombieInfo& info = DATATABLE_MGR.Get<ZombieTable>(DataTable::Ids::Zombie)->Get(t);

	int index = (int)zombieType;
	textureId = info.textureId;
	speed = info.speed;
	maxHp = info.maxHp;
	damage = info.damage;
	attackRate = info.attackRate;
}

Zombie::Types Zombie::GetType() const
{
	return zombieType;
}

void Zombie::SetPlayer(Player* player)
{
	this->player = player;
}

void Zombie::OnHitBullet(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

		if (sceneDev1 != nullptr)
		{
			sceneDev1->OnDieZombie(this);
		}
	}
}
