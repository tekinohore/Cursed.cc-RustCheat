#pragma once

#include <Windows.h>
#include <D3D11.h>
#include <Minhook.h>
#include <vector>
#include <filesystem>
#include <Renderer.h>
#include <Menu.hpp>
#include <StringObf.h>

#pragma warning(disable: 26495 4005)
#include <D3D11.h>
#pragma warning(default: 26495 4005)
#undef DrawText
#include <sstream>

#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }

typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* D3D11ResizeBuffersHook) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

void Initialize();
void Shutdown();
HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
HRESULT __stdcall ResizeHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
LRESULT __stdcall WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void DrawScene();

extern D3D11PresentHook origPresentHook;
extern D3D11ResizeBuffersHook origResize;
extern bool d3dfirst;
extern bool menuOpen;

extern ID3D11Device* pDevice;
extern ID3D11DeviceContext* pContext;
extern ID3D11RenderTargetView* RenderTargetView;
extern IDXGISwapChain* _pSwapChain;
extern ID3D11Texture2D* RenderTargetTexture;
extern WNDPROC OrigWndProc;
extern HWND window;
extern HRESULT hr;

extern uintptr_t* pSwapChainVtable;
extern uintptr_t* pContextVTable;
extern uintptr_t* pDeviceVTable;

extern UINT vps;
extern D3D11_VIEWPORT viewport;
extern float ScreenCenterX;
extern float ScreenCenterY;