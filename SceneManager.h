#pragma once
#include <vector>


class gameNode;
class SceneManager 
{
private:
	vector<gameNode*> scenes;
	SceneManager();
public:
	static SceneManager* GetInstance();

	void ReplaceScene(gameNode* scene);
	void PushScene(gameNode* scene);
	void PopScene();
	 
	gameNode* GetNowScene();  
	vector<gameNode*> GetScenes();
};

