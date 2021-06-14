#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"

void Game::Init(const WindowInfo& info)
{
	gEngine->Init(info);
	GET_SINGLETON(SceneManager)->LoadScene(L"TestScene");
	CMD_LIST->Close();
}

void Game::Run()
{
	gEngine->Update();
	gEngine->Render();
}
