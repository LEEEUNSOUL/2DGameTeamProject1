#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::Init()
{
	//물리 세계 초기화 
	//b2Vec2 gravity(0.0f, -9.8f);
	//_physicsWorld = new b2World(gravity);
	//_physicsWorld->SetAllowSleeping(true);
	//_physicsWorld->SetContinuousPhysics(true);



	_hdc = GetDC(_hWnd);
	_managerInit = false;


	return S_OK;
}

HRESULT gameNode::Init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	b2Vec2 gravity = b2Vec2{ 0,15.f };
	_physicsWorld = new b2World(gravity);

	PHYSICSMANAGER->SetWorld(_physicsWorld);

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 1.f / 60, NULL);
		IMAGEMANAGER->Init();
		TXTDATA->Init();
		TIMEMANAGER->Init();
		SOUNDMANAGER->Init();
		PHYSICSMANAGER->Init();

	}

	return S_OK;
}

void gameNode::Release()
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->ReleaseSingleton();
		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();
		TXTDATA->Release();
		TXTDATA->ReleaseSingleton();
		TIMEMANAGER->Release();
		TIMEMANAGER->ReleaseSingleton();
		SOUNDMANAGER->Release();
		SOUNDMANAGER->ReleaseSingleton();
		PHYSICSMANAGER->Release();
		PHYSICSMANAGER->ReleaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::Update()
{
	KEYMANAGER->Update();
	PHYSICSMANAGER->Update();
	CAMERAMANAGER->Update();


	Object::Update();
}

void gameNode::Render()
{
	ID2D1RenderTarget* RenderTarget = IMAGEMANAGER->GetRenderTarget();
	RenderTarget->BeginDraw();
	RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	RenderTarget->SetTransform(D2D1::IdentityMatrix());

	//RECT Clip;
	//GetClientRect(_hWnd, &Clip);
	//IMAGEMANAGER->FillRectangle(Clip, DefaultBrush::white);
	//==================================================

	for (auto c : _children)
	{
		c->Render();
	}


	PHYSICSMANAGER->Render();

	//===================================================
	//딱 말했다
	HRESULT hr = RenderTarget->EndDraw();
	//디바이스 로스트 체크
	if (hr == D2DERR_RECREATE_TARGET)
	{
		IMAGEMANAGER->ReloadALL();
	}
}

b2World* gameNode::GetPhysicsWorld()
{
	return _physicsWorld;
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC			hdc;

	switch (iMessage)
	{
	case WM_CREATE:

		break;
		//case WM_TIMER:
		//	this->Update();
		//	break;
		//case WM_PAINT:
		//{
		//	hdc = BeginPaint(hWnd, &ps);

		//	this->Render();

		//	EndPaint(hWnd, &ps);
		//}
		//break;
		//왼쪽클릭하고있으면

	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;

	case WM_ACTIVATE:
		if (!ApplicationManager::GetInstance()->GetIsFullScreen())
			break;
		switch (LOWORD(wParam))
		{
		case WA_ACTIVE:
			ApplicationManager::GetInstance()->UpdateScreen();
			break;
		case WA_INACTIVE:
			ApplicationManager::GetInstance()->ExitFullScreen();
			break;
		}
		break;
	case WM_DESTROY:
		ApplicationManager::GetInstance()->ExitFullScreen();
		PostQuitMessage(0);
		break;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
