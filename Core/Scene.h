#pragma once

class GameObject;

class Scene
{
public:
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
	std::vector<std::shared_ptr<GameObject>> mGameObjects;
};

