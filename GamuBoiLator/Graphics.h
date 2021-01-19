#pragma once
//#include "../GenericHeader.h"
#include <d3d11.h> // d3d9 is old news dont even think about it
#pragma comment(lib, "d3d11.lib")
#include <vector>

class GFX {

	ATOM wClass;
	HWND hWindow;
	ID3D11DeviceContext *pCtx;
	ID3D11Device		*pDevice;
	IDXGISwapChain		*pSwapchain;
	DXGI_SWAP_CHAIN_DESC *pDesc = nullptr;

	static LRESULT CALLBACK WindowHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool InitializeDirectX(int width, int height); // doesnt really need to be here, but i like them here.
												   // take given buffer from GPU and compile it into a DX Texture
	void CompileImage(float** buf);

	int gb_w = 0, gb_h = 0;
	int wnd_w = 0, wnd_h = 0;
	void ClearScreen();
	bool initialized = false;
public:
	void RenderD3D();
	void DrawGPUBuffer(float** buf);
	bool SpawnWindow();

	GFX(int gb_w, int gb_h, int window_w = 0, int window_h = 0);
};