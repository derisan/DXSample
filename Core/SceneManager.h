#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Update();
	void Render();
	void LoadScene(const std::wstring& sceneName);

	std::shared_ptr<Scene> GetActiveScene() const { return mActiveScene; }

private:
	std::shared_ptr<Scene> LoadTestScene();

private:
	std::shared_ptr<Scene> mActiveScene = nullptr;
};

