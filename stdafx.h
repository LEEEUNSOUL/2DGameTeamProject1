#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#pragma comment (lib,"winmm.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "utils.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "txtData.h"
#include "SoundManager.h"
#include "PhysicsManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "gameNode.h"
#include "ApplicationManager.h"

using namespace SEVENTEEN_UTIL;

//=========================================
// ## 19.10.30 ## - 디파인문 -
//=========================================

#define WINNAME (LPCTSTR)(TEXT("SevenTeen Class"))
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 800
#define WINSIZEY 600
#define WINSTYLE WS_VISIBLE || WS_BORDER || WS_CAPTION

#define RND randomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define PHYSICSMANAGER PhysicsManager::getSingleton()
#define CAMERAMANAGER CameraManager::getSingleton()

#include "Box2D/Box2D.h"
#pragma comment(lib, "lib/x86_64/Debug/Box2D.lib")

#define Deg2Rad PI/180.f
#define Rad2Deg 180.f/PI


#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#define SAFE_Release(p) {if(p) {(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

#define BACKGROUND_SCALE 0.8
#define BACKGROUND_WIDTH 4032 *BACKGROUND_SCALE
#define BACKGROUND_HEIGHT 2000 *BACKGROUND_SCALE

inline Vector2 Hyolim_LeftTop(Vector2 vec, float width, float height)
{
	Vector2 temp;
	temp.x = (vec.x) * BACKGROUND_SCALE + width / 2 - BACKGROUND_WIDTH / 2;
	temp.y = (vec.y) * BACKGROUND_SCALE + height / 2 - BACKGROUND_HEIGHT / 2;
	return temp;
}

inline Vector2 Hyolim_Center(Vector2 vec)
{
	Vector2 temp;
	temp.x = (vec.x)*BACKGROUND_SCALE - BACKGROUND_WIDTH / 2;
	temp.y = (vec.y)*BACKGROUND_SCALE - BACKGROUND_HEIGHT / 2;
	return temp;
}


template <typename T>
inline void SafeRelease(T*&p)
{
	if (NULL != p)
	{
		p->Release();
		p = NULL;
	}
}


//==========================================
// ## 19.10.31 ## Extern
//==========================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

#include "EZ.h"