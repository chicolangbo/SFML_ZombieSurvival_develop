#pragma once
#include "Singleton.h"

class ResourceMgr : public Singleton<ResourceMgr>
{
	friend Singleton<ResourceMgr>;

protected:
	ResourceMgr() = default;
	virtual ~ResourceMgr() override;
	
	std::map<std::string, sf::Texture*> mapTexture;
	std::map<std::string, sf::Font*> mapFont;
	std::map<std::string, sf::SoundBuffer*> mapSoundBuffer;

public:

	void UnLoadAll();

	void Load(ResourceTypes t, const std::string path);
	void Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array);

	void Unload(ResourceTypes t, const std::string path);
	void Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array);


	sf::Texture* GetTexture(const std::string& id);
	sf::Font* GetFont(const std::string& id);
	sf::SoundBuffer* GetSoundBuffer(const std::string& id);

};

#define RESOURCE_MGR (ResourceMgr::Instance())
