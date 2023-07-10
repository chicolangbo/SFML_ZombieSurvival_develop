#pragma once
#include "Scene.h"
class SceneTitle :
    public Scene
{
protected:
	sf::View titleView;

public:
	SceneTitle(SceneId id = SceneId::Title);
	virtual ~SceneTitle() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

