#include "stdafx.h"
#include "SpriteItem.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

const std::string SpriteItem::TextureIds[2] =
{
	"graphics/ammo_icon.png",
	"graphics/health_pickup.png",
};
//std::fuction<void (Player* player, int amount)>을 배운김에 사용하고 싶었으나 람다함수로 초기화하는게 곧장은 안된다고 해서 using을 사용하여 별도의 별칭을 사용 하여 적용
const SpriteItem::EffectFunction SpriteItem::Effects[2] =
{
	[](Player* player, int amount) {player->AddAmmo(amount); },
	[](Player* player, int amount) {player->AddHealth(amount); },
};
int SpriteItem::Amounts[2] = {120, 20};

SpriteItem::SpriteItem(const std::string& n)
	:SpriteGo("", n),amount(0),itemType(Types::Default)
{
}

SpriteItem::~SpriteItem()
{
}

void SpriteItem::Reset()
{
	int ammo = player->GetAmmo();
	int hp = player->GetHealth();
	std::cout << "아이템 리셋" << std::endl;
	if (ammo < 50)
	{
		SetType(Types::Ammo);
	}
	else if(hp < 20)
	{
		SetType(Types::MediKit);
	}
	else if(ammo < Utils::RandomRange(50, 1000))//탄약의 총 수량이 1000 이 넘으면 더 안생기도록 설정
	{
		SetType(Types::Ammo);
	}
	else
	{
		SetType(Types::MediKit);
	}

	SpriteGo::Reset();
}

void SpriteItem::Update(float dt)
{
	if (sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds()))
	{
		UseItem();
	}
}

void SpriteItem::SetType(Types type)
{
	//std::cout << "아이템 셋 타입" << std::endl;
	itemType = type;
	int index = (int)itemType;
	textureId = TextureIds[index];
	amount = Amounts[index];
}


void SpriteItem::UseItem()
{
	sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/pickup.wav"));
	sound.play();

	Effects[(int)itemType](player, amount);	

	SCENE_MGR.GetCurrScene()->RemoveGo(this);
	pool->Return(this);
}

void SpriteItem::SetPlayer(Player* player)
{
	this->player = player;
}

void SpriteItem::ResetAmount()
{
	SpriteItem::Amounts[0] = 120;
	SpriteItem::Amounts[1] = 20;
}
