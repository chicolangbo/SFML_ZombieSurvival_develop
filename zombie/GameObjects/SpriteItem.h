#pragma once
#include "stdafx.h"
#include "SpriteGo.h"
#include "ObjectPool.h"

class Player;

class SpriteItem : public SpriteGo
{
public: 
	using EffectFunction = std::function<void(Player*, int)>;
	enum class Types
	{
		Default = -1,
		Ammo,
		MediKit,
	};
	static const int TotalTypes = 2;
	static const std::string TextureIds[2];
	static const EffectFunction Effects[2];
	static int Amounts[2];
	static void ResetAmount();

protected:
	Types itemType;
	int amount;
	sf::Sound sound;

	Player* player = nullptr;
	ObjectPool<SpriteItem>* pool = nullptr;
public:
	SpriteItem(const std::string& n = "");
	virtual ~SpriteItem() override;

	virtual void Reset() override; 
	virtual void Update(float dt) override;

	void SetType(Types type);
	void AddAmount(Types type, int amount) { SpriteItem::Amounts[(int)type] += amount; }
	void SetPool(ObjectPool<SpriteItem>* pool) { this->pool = pool; }

	void UseItem();
	void SetPlayer(Player* player);
};