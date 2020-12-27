#include "CSceneManager.h"

CSceneManager* CSceneManager::__instance = NULL;

CSceneManager::CSceneManager()
{

}

CScene* CSceneManager::GetCurrentScene()
{
    return scenes[CurrentSceneID];
}

void CSceneManager::SetScene(int id)
{
    if(CurrentSceneID!=-1)
        scenes[CurrentSceneID]->Unload();
    CurrentSceneID = id;
	CGame::GetInstance()->SetKeyHandler(scenes[CurrentSceneID]->GetKeyEventHandler());
    scenes[CurrentSceneID]->Load();
}

void CSceneManager::AddScene(CScene * scene)
{
    scenes[scene->GetSceneID()] = scene;
}

void CSceneManager::Update(DWORD dt)
{
    scenes[CurrentSceneID]->Update(dt);
}

void CSceneManager::Render()
{
	CGame * game = CGame::GetInstance();
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

		if (d3ddv->BeginScene())
		{
			// Clear back buffer with a color
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

			spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

			//Render scene
			scenes[CurrentSceneID]->Render();

			spriteHandler->End();
			d3ddv->EndScene();
		}
		// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

CSceneManager* CSceneManager::GetInstance()
{
    if (__instance == NULL) __instance = new CSceneManager();
    return __instance;
}
