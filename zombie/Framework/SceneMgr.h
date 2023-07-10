#pragma once
#include "Singleton.h"
#include "Scene.h"

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	virtual ~SceneMgr() override = default;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene = nullptr;

	SceneId startSceneId = SceneId::Title;

public:
	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void ChangeScene(SceneId id);
	Scene* GetCurrScene() const;
	// 김민지, 230709, hiscore 세팅을 위한 함수 추가
	Scene* GetGameScene() const;
	////////////////////////////////////////////
};

#define SCENE_MGR (SceneMgr::Instance())
