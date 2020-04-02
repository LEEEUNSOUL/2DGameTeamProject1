#include "stdafx.h"
#include "gameNode.h"
#include "SceneManager.h"
#include "playGround.h"

SceneManager::SceneManager() 
{
	scenes.push_back(new playGround());
}

SceneManager* SceneManager::GetInstance() 
{
	static SceneManager* instance = new SceneManager();
	return instance;
}

vector<gameNode*> SceneManager::GetScenes()
{ 
	return scenes;
}

void SceneManager::ReplaceScene(gameNode* scene)
{
	for (gameNode* s : scenes) 
		s->Release(); 
	scenes.clear(); 

	scenes.push_back(scene); 
	scene->Init();
}

void SceneManager::PushScene(gameNode* scene) 
{
	scenes.push_back(scene);
	scene->Init();
}

void SceneManager::PopScene()
{
	scenes[scenes.size() - 1]->Release(); 
	scenes.pop_back();
}

gameNode* SceneManager::GetNowScene() 
{
	return scenes[scenes.size() - 1];
}