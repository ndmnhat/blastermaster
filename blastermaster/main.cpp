/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include ".\Game\Game.h"
#include ".\Object\GameObject.h"
#include ".\Animations\Animations.h"

#include ".\Object\Player\Sophia.h"
#include ".\Object\OutdoorEnemy\OutdoorEnemy.h"

//#include ".\Map\Map.h"
//#include ".\Camera\Camera.h"

#include ".\Scene\CSceneManager.h"

#define ID_TEX_PLAYER 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

CGame *game;
CSophia *sophia;

//COutdoorEnemy* e1, * e2, * e3;
CCamera* cam = CCamera::GetInstance();

//CMap m;

CScene* scenegame = new CSceneGame(1, L"Scene\\scene.txt");
//class CSampleKeyHander: public CKeyEventHandler
//{
//	virtual void KeyState(BYTE *states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander * keyHandler; 
//
//void CSampleKeyHander::OnKeyDown(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		sophia->SetState(SOPHIA_STATE_JUMP);
//		break;
//	case DIK_DOWN:
//		break;
//	}
//}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode)
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//}
//
//void CSampleKeyHander::KeyState(BYTE *states)
//{
//	if (game->IsKeyDown(DIK_RIGHT))
//		sophia->SetState(SOPHIA_STATE_WALKING_RIGHT);
//	else if (game->IsKeyDown(DIK_LEFT))
//		sophia->SetState(SOPHIA_STATE_WALKING_LEFT);
//	else if (game->IsKeyDown(DIK_SPACE))
//		sophia->SetState(SOPHIA_STATE_JUMP);
//	else sophia->SetState(SOPHIA_STATE_IDLE);
//}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_PLAYER, L"textures\\BlasterMasterSheet1.png",D3DCOLOR_ARGB(0, 0, 0,0));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_ARGB(0,0,0,0));
	textures->Add(ID_TEX_MAP, L"textures\\tiles.png", D3DCOLOR_XRGB(0, 0, 0));
	
	//m.ReadMap(L".\\Map\\map2.txt");


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texPlayer = textures->Get(ID_TEX_PLAYER);
	LPDIRECT3DTEXTURE9 textEnemies = textures->Get(ID_TEX_ENEMY);

	sprites->Add(10001, 3, 0, 29, 18, texPlayer);
	sprites->Add(10002, 34, 0, 60, 18, texPlayer);
	sprites->Add(10003, 67, 0, 93, 18, texPlayer);
	sprites->Add(10004, 99, 0, 125, 18, texPlayer);

	sprites->Add(10005, 136, 0, 162, 18, texPlayer);
	sprites->Add(10006, 168, 0, 194, 18, texPlayer);
	sprites->Add(10007, 201, 0, 227, 18, texPlayer);
	sprites->Add(10008, 232, 0, 258, 18, texPlayer);
	////Enemy1
	//sprites->Add(20001, 67, 424, 85, 441, textEnemies);
	//sprites->Add(20002, 87, 424, 105, 441, textEnemies);

	//sprites->Add(20003, 149, 424, 168, 441, textEnemies);
	//sprites->Add(20004, 169, 424, 188, 441, textEnemies);

	////Enemy2
	//sprites->Add(30001, 172, 412, 190, 422, textEnemies);
	//sprites->Add(30002, 191, 412, 209, 422, textEnemies);

	//sprites->Add(30003, 64, 412, 82, 422, textEnemies);
	//sprites->Add(30004, 46, 412, 64, 422, textEnemies);

	////Enemy3
	//sprites->Add(40001, 174, 527, 192, 548, textEnemies);
	//sprites->Add(40002, 194, 530, 212, 548, textEnemies);

	//sprites->Add(40003, 62, 527, 80, 548, textEnemies);
	//sprites->Add(40004, 42, 530, 60, 548, textEnemies);

	LPANIMATION ani;

	ani = new CAnimation(100);	
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10005);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10004);
	ani->Add(10003);
	ani->Add(10002);
	ani->Add(10001);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	animations->Add(501, ani);

	//Enemy1
	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	animations->Add(600, ani);

	ani = new CAnimation(100);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(601, ani);

	//Enemy2
	ani = new CAnimation(100);
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(700, ani);

	ani = new CAnimation(100);
	ani->Add(30003);
	ani->Add(30004);
	animations->Add(701, ani);

	//Enemy3
	ani = new CAnimation(100);
	ani->Add(40001);
	ani->Add(40002);
	animations->Add(800, ani);

	ani = new CAnimation(100);
	ani->Add(40003);
	ani->Add(40004);
	animations->Add(801, ani);


	//sophia = new CSophia();
	//sophia->AddAnimation(400);		// idle left
	//sophia->AddAnimation(401);		// idle right
	//sophia->AddAnimation(500);		// walk left
	//sophia->AddAnimation(501);		// walk right

	/*e1 = new CEnemy1();
	e1->AddAnimation(600);
	e1->AddAnimation(601);

	e2 = new CEnemy2();
	e2->AddAnimation(700);
	e2->AddAnimation(701);

	e3 = new CEnemy3();
	e3->AddAnimation(800);
	e3->AddAnimation(801);*/

	//sophia->SetPosition(1080.0f, 1180.0f);
	/*e1->SetPosition(999.0f, 1215.0f);
	e2->SetPosition(999.0f, 1215.0f);
	e3->SetPosition(999.0f, 1215.0f);*/
	//cam->SetPosition(1024.0f, 1040.0f);
	cam->SetPosition(0.0f, 0.0f);
	//cam->SetFollow(sophia);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	//sophia->Update(dt);
	/*e1->Update(dt);
	e2->Update(dt);
	e3->Update(dt);*/
	//cam->Update(dt);
	//scenegame->Update(dt);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scenegame->Render();

		//sophia->Render();
		/*e1->Render();
		e2->Render();
		e3->Render();*/
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			//game->ProcessKeyboard();
			
			//Update(dt);
			//Render();

			CSceneManager::GetInstance()->Update(dt);
			CSceneManager::GetInstance()->Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);
	//scenegame->Load();
	CSceneManager::GetInstance()->AddScene(scenegame);
	CSceneManager::GetInstance()->SetScene(1);
	//LoadResources();
	Run();


	return 0;
}