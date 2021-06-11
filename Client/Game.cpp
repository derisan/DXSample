#include "pch.h"
#include "Game.h"
#include "Engine.h"

void Game::Init(const WindowInfo& info)
{
	gEngine->Init(info);
}

void Game::Run()
{
	gEngine->Render();
}
