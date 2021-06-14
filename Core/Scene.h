#pragma once

#include "Light.h"

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddGameObject(std::shared_ptr<GameObject> obj);
	void RemoveGameObject(std::shared_ptr<GameObject> obj);

	const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() const { return mGameObjects; }

private:
	void setLightData();

private:
	std::vector<std::shared_ptr<GameObject>> mGameObjects;

	UploadBuffer<LightParams> mLightCb;
};

