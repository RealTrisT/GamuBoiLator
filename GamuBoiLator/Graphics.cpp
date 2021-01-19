#include "Graphics.h"
#include <thread>
#include <d3dcompiler.h>
#include <DirectXMath.h>
//#include "../GBDefines.hpp"
#pragma comment(lib, "d3dcompiler.lib")

LRESULT CALLBACK GFX::WindowHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Log( "MSG: %X", msg );
	switch (msg)
	{
	case WM_NCDESTROY:
		PostQuitMessage(0); // let our thread know we're dead.
		break;
	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

ID3D11VertexShader *pVS;    // the vertex shader
ID3D11PixelShader *pPS;     // the pixel shader
ID3D11Buffer * pConstantBuffer = 0; // constant buffer ( where the projection matrix is placed )
ID3D11InputLayout *pLayout = 0;
bool GFX::InitializeDirectX(int width, int height)
{
	DXGI_SWAP_CHAIN_DESC desc = { 0 };
	desc.OutputWindow = this->hWindow;
	desc.BufferCount = 2; // D O U B L E  B U F F E R D
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // should only need an alpha i guess, GB has no color, right?
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1; // SIXTY HERTZ BOIS

	desc.SampleDesc.Quality = 0, desc.SampleDesc.Count = 1;

	desc.Windowed = true; // dont set this to false unless you want DX to hijack the fuck out of your monitor
	int createFlags = 0;
	createFlags |= D3D11_CREATE_DEVICE_DEBUG; // for debugging, duh.
	auto success = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, 0,
		createFlags, 0, 0, D3D11_SDK_VERSION, &desc, &this->pSwapchain, &this->pDevice, 0, &this->pCtx);

	if (success != S_OK)
	{
		puts("God help us, its failed.");
		return false;
	}

	if (!this->pDesc)
	{
		this->pDesc = new DXGI_SWAP_CHAIN_DESC();
		this->pSwapchain->GetDesc(this->pDesc);
	}

	ID3D10Blob *VS, *PS;
	// have to compile shaders here.
#pragma region Shaders
	// so i want to be able to transform 0,0 to be the top left
	auto shader = R"(
	cbuffer VS_CONSTANT_BUFFER : register( b0 )
	{
		matrix mMat;
	};

	struct VOut
	{
		float4 position : SV_POSITION;
		float4 color : COLOR;
	};

	VOut VShader( float4 position : POSITION, float4 color : COLOR )
	{
		VOut output;
		output.position = mul( mMat, position );
		output.color = color;
		return output;
	}

	float4 PShader( float4 position : SV_POSITION, float4 color : COLOR ) : SV_TARGET
	{
		return float4( color[0], color[1], color[2], color[3] );
	})";

#pragma endregion

	HRESULT hr = D3DCompile(shader, strlen(shader) + 1, "VS", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, 0);
	if (FAILED(hr))
		__debugbreak();
	hr = D3DCompile(shader, strlen(shader) + 1, "PS", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);
	if (FAILED(hr))
		__debugbreak();

	pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	pCtx->PSSetShader(pPS, 0, 0);
	pCtx->VSSetShader(pVS, 0, 0);

	DirectX::XMMATRIX mat = DirectX::XMMatrixOrthographicOffCenterLH(0, width, height, 0, 0.f, 1.f);
	//D3DXMatrixOrthoOffCenterLH( &mat, 0, width, height, 0, 0.f, .1f ); // was 0 where the 1 is, for some reason it dicks my lines sometimes.

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(mat);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &mat;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer.
	hr = pDevice->CreateBuffer(&cbDesc, &InitData, &pConstantBuffer);
	if (FAILED(hr))
		__debugbreak();

	pCtx->VSSetConstantBuffers(0, 1, &pConstantBuffer);

	hr = pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	if (FAILED(hr))
		__debugbreak();

	pCtx->IASetInputLayout(pLayout);

	return true;
}

// TODO: Could use a constant buffer, though resizing may be confusing

void GFX::CompileImage(float** buf)
{
	if (buf[0] == nullptr)
		return;// not initializd yet
	if (!this->initialized)
		return;

	struct PIXEL_VERTEX {
		float x, y, z;
		float col[4];
	};

	HRESULT hr = 0;
	ID3D11RenderTargetView * pRenderView = 0;
	ID3D11Texture2D * pBackBuffer = 0;
	hr = this->pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		__debugbreak();

	hr = pDevice->CreateRenderTargetView(pBackBuffer, 0, &pRenderView);
	if (FAILED(hr))
		__debugbreak();

	pBackBuffer->Release();
	D3DCOLORVALUE val = { 0 ,0 ,0, 255 }; // RGBA
	pCtx->ClearRenderTargetView(pRenderView, (float*)&val); // clear view so shit doesnt pile up
															//std::vector<PIXEL_VERTEX> testVertex;
	auto size = this->gb_w * this->gb_h + 1;

	PIXEL_VERTEX * pPix = new PIXEL_VERTEX[size];

	int i = 0;

	for (int y = 0; y < this->gb_h; y++)
	{
		for (int x = 0; x < this->gb_w; x++)
		{

			pPix[i] = {x+1, y+1, 0, buf[i][0], buf[i][1], buf[i][2], buf[i][3]};
			auto pCol = buf[i];
			PIXEL_VERTEX vert = { 0 };
			vert.x = x + 1;
			vert.y = y + 1;
			vert.z = 0;
			memcpy(vert.col, pCol, sizeof(float[4]));
			pPix[i] = vert;
			//testVertex.push_back( vert );
			i++;
		}
	}
	// clean screen
	// draw pixels (possibly use a POINTLIST and just set them via XY
	ID3D11Buffer * pVertexBuffer = nullptr;
	D3D11_BUFFER_DESC bd = { 0 };
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = size * sizeof(PIXEL_VERTEX);
	//bd.ByteWidth = testVertex.size( ) * sizeof( PIXEL_VERTEX );
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	hr = pDevice->CreateBuffer(&bd, NULL, &pVertexBuffer);       // create the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	hr = pCtx->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);   // map the buffer
	memcpy(ms.pData, pPix, size * sizeof(PIXEL_VERTEX));                // copy the data
	pCtx->Unmap(pVertexBuffer, NULL);

	unsigned int stride = sizeof(PIXEL_VERTEX);
	unsigned int offset = 0;
	pCtx->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	pCtx->Draw(size, 0);
	pVertexBuffer->Release();

	delete[] pPix;

	this->pCtx->OMSetRenderTargets(1, &pRenderView, 0);

	this->RenderD3D();
}

bool GFX::SpawnWindow()
{
	WNDCLASSA wc = { 0 };
	wc.lpfnWndProc = GFX::WindowHandler;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = "GaymeBoy";
	wc.hbrBackground = GetSysColorBrush(COLOR_BTNSHADOW);
	auto classerino = RegisterClassA(&wc);
	if (!classerino)
	{
		printf("Error registering class %d", GetLastError());
		return false;
	}

	RECT desired_size = { 0, 0, this->wnd_w, this->wnd_h };
	AdjustWindowRect(&desired_size, WS_VISIBLE | WS_OVERLAPPEDWINDOW, FALSE);

	this->hWindow = CreateWindowA((LPCSTR)classerino, "GaymeBoy", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, desired_size.right - desired_size.left, desired_size.bottom - desired_size.top, 0, 0, 0, 0);
	if (!hWindow)
	{
		printf("Error creating window %d", GetLastError());
		return false;
	}

	// before we infinite loop, setup DX.
	if (!GFX::InitializeDirectX(this->gb_w, this->gb_h)) // using gb dimensions so that it scales to our window size!
	{
		DestroyWindow(hWindow);
		UnregisterClassA((LPCSTR)classerino, 0);
		return false;
	}

	this->ClearScreen();

	this->initialized = true;
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, 0))
		{
			if (!GetMessage(&msg, 0, 0, 0))
				break; // got a WM_QUIT

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//this->RenderD3D( ); // possible thread timing issues here lmao
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	puts("Window closed");
	return true;
}

void GFX::ClearScreen()
{
	ID3D11RenderTargetView * pRenderView = 0;
	ID3D11Texture2D *pBackBuffer = 0;

	this->pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);	//get the fucking buffer						------------------------\ 
	this->pDevice->CreateRenderTargetView(pBackBuffer, 0, &pRenderView);				//make a "view" out of it so we can actually use it					-	 | basically say "hey the back buffer is a view",
	pBackBuffer->Release();																//release not the buffer, but the object we're using to access it	-	/  but then also telling the context that this "view"
	//																																						-  /   is supposed to represent the back buffer??
	this->pCtx->OMSetRenderTargets(1, &pRenderView, 0);									//associate this fucking "view" with the back buffer??	--------------/
	D3DCOLORVALUE val = { 0 ,0 ,0, 1 }; // RGBA
	this->pCtx->ClearRenderTargetView(pRenderView, (float*)&val);						//clear the "view" which is the back buffer

	D3D11_VIEWPORT viewPort = { 0 };							//I actually
	viewPort.Width = this->pDesc->BufferDesc.Width;				//have no 
	viewPort.Height = this->pDesc->BufferDesc.Height;			//fucking idea
	viewPort.MaxDepth = 1.0f;									//of what any of this
	this->pCtx->RSSetViewports(1, &viewPort);					//means or does
	this->pSwapchain->Present(1, 0);							//--I assume this switches the buffers so then the back buffer is presented
}

void GFX::RenderD3D()
{
	//ID3D11Texture2D *pBackBuffer = 0;
	//this->pSwapchain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	//ID3D11RenderTargetView * pRenderView = 0;
	//this->pDevice->CreateRenderTargetView( pBackBuffer, 0, &pRenderView );

	//pBackBuffer->Release( );
	//this->pCtx->OMSetRenderTargets( 1, &pRenderView, 0 );
	//D3DCOLORVALUE val = { 0 ,0 ,0, 1 }; // RGBA
	//this->pCtx->ClearRenderTargetView( pRenderView, ( float* )&val );
	// assume render target set???? BELIEVE.

	D3D11_VIEWPORT viewPort = { 0 };
	viewPort.Width = this->pDesc->BufferDesc.Width;
	viewPort.Height = this->pDesc->BufferDesc.Height;
	viewPort.MaxDepth = 1.0f;
	this->pCtx->RSSetViewports(1, &viewPort);
	this->pSwapchain->Present(1, 0);
}

void GFX::DrawGPUBuffer(float** buf)
{
	this->CompileImage(buf);
}

GFX::GFX(int gb_w, int gb_h, int window_w, int window_h)
{
	this->gb_h = gb_h, this->gb_w = gb_w;
	if (!window_h)
		this->wnd_h = gb_h;
	else
		this->wnd_h = window_h;

	if (!window_w)
		this->wnd_w = gb_w;
	else
		this->wnd_w = window_w;

	// Create a window, setup pDevice, etc etc
	// Luckily for you, I know a decent amount of dx11
	// Then one must begin the message loop.
}