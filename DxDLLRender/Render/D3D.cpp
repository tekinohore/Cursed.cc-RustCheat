#include "D3D.hpp"
#include <random>
#include <thread>
#include <Globals.hpp>


D3D11PresentHook origPresentHook = NULL;
D3D11ResizeBuffersHook origResize = NULL;
bool d3dfirst = true;
bool menuOpen = false;

ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* RenderTargetView = NULL;
IDXGISwapChain* _pSwapChain = NULL;
ID3D11Texture2D* RenderTargetTexture = NULL;
WNDPROC OrigWndProc = NULL;
HWND window;
HRESULT hr;

uintptr_t* pSwapChainVtable = NULL;
uintptr_t* pContextVTable = NULL;
uintptr_t* pDeviceVTable = NULL;

UINT vps = 1;
D3D11_VIEWPORT viewport;
float ScreenCenterX;
float ScreenCenterY;

std::unique_ptr<Menu> menu;
int espTab;
int weaponsTab;
int aimbotTab;
int miscTab;

#define ENG

#ifdef ENG
#define ESPTabName L"[ESP]"

#define PlayerESPName L"Players"
#define SleeperESPName L"Sleepers"
#define ScientistESPName L"Scientists"
#define HeldWeaponESPName L"Held Weapon"
#define TracersESPName L"Tracers"
#define InventoryESPName L"Inventory"
#define SkeletonESPName L"Skeleton"
#define BoxESPName L"Box"
#define HelicopterESPName L"Helicopter"

#define WeaponsTabName L"[Weapons]"

#define NoRecoilName L"No Recoil"
#define NoSpreadName L"No Spread"
//#define FastReloadName L"Fast Reload"
#define InstaEokaName L"100% Eoka"
#define CrosshairName L"Crosshair"
#define AutomaticName L"Automatic"
#define JumpAimName L"Jump Aim"
#define SprintAimName L"Sprint Aim"
#define RapidFireName L"Rapid Fire"

#define AimbotTabName L"[Aimbot]"

#define SilentAimName L"Silent Aim"
#define AimbotName L"Aimbot"
#define PredictionName L"Prediction"
#define FOVCircleName L"FOV Circle"
#define ThicknessName L"Bullet Thickness"
#define HeliSilentName L"Heli Silent"

#define MiscTabName L"[Misc]"

#define SpiderManName L"Spider Man"
#define FakeAdminName L"Fake Admin"
#define NeverSinkName L"Never Sink"

#else

#define ESPTabName L"[ЭСП]"

#define PlayerESPName L"игроки"
#define SleeperESPName L"Спящие"
#define ScientistESPName L"Ученые"
#define HeldWeaponESPName L"Удерживаемое оружие"
#define TracersESPName L"трассирующий снаряд"
#define InventoryESPName L"инвентарь"
#define SkeletonESPName L"остов"
#define BoxESPName L"коробка"
#define HelicopterESPName L"Вертолет"

#define WeaponsTabName L"[Оружие]"

#define NoRecoilName L"Без отдачи"
#define NoSpreadName L"Не разбегайтесь"
#define FastReloadName L"Быстрая перезагрузка"
#define InstaEokaName L"100% Eoka"
#define CrosshairName L"Кроссхаир "
#define AutomaticName L"автоматическая"
#define JumpAimName L"Прыжок цель"
#define SprintAimName L"Спринт цель"
#define RapidFireName L"Rapid Fire"

#define AimbotTabName L"[Аимбот]"

#define SilentAimName L"Тихая цель"
#define AimbotName L"Аимбот"
#define PredictionName L"предвычисление"
#define FOVCircleName L"Поле зрения Круг"
#define ThicknessName L"Толщина пули"
#define HeliSilentName L"Хели Тихая"

#define MiscTabName L"[Разнообразный]"

#define SpiderManName L"человек-паук"
#define FakeAdminName L"Поддельный Админ"
#define NeverSinkName L"Никогда не тонуть"

#endif

HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (d3dfirst)
	{
		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pContext);

		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture))))
		{
			pDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &RenderTargetView);
			RenderTargetTexture->Release();

		}

		menu = std::make_unique<Menu>(L"basement",Vector2(30.f,25.f),Vector2(180.f,490.f));

		int group = menu->addGroup(ESPTabName, &espTab);
		menu->addItem(PlayerESPName, &impl::playerESP, group);
		menu->addItem(SleeperESPName, &impl::sleeperESP, group);
		menu->addItem(ScientistESPName, &impl::scientistESP, group);
		menu->addItem(HeldWeaponESPName, &impl::heldWeapon, group);
		menu->addItem(TracersESPName, &impl::tracers, group);
		menu->addItem(InventoryESPName, &impl::inventoryESP, group);
		menu->addItem(SkeletonESPName, &impl::skeletonESP, group);
		menu->addItem(BoxESPName, &impl::boxESP, group);
		menu->addItem(HelicopterESPName, &impl::helicopterESP, group);
		group = menu->addGroup(WeaponsTabName, &weaponsTab);
		menu->addItem(NoRecoilName, &impl::noRecoil, group);
		menu->addItem(NoSpreadName, &impl::noSpread, group);
		//menu->addItem(FastReloadName, &impl::fastReload, group);
		menu->addItem(InstaEokaName, &impl::instaEoka, group);
		menu->addItem(CrosshairName, &impl::crosshair, group);
		menu->addItem(AutomaticName, &impl::automatic, group);
		menu->addItem(JumpAimName, &impl::jumpAim, group);
		menu->addItem(SprintAimName, &impl::sprintAim, group);
		menu->addItem(RapidFireName, &impl::rapidFire, group);
		group = menu->addGroup(AimbotTabName, &aimbotTab);
		menu->addItem(SilentAimName, &impl::silentAim, group);
		menu->addItem(AimbotName, &impl::aimbot, group);
		menu->addItem(PredictionName, &impl::aimPrediction, group);
		menu->addItem(FOVCircleName, &impl::fovCircle, group);
		menu->addItem(ThicknessName, &impl::bulletThickness, group);
		menu->addItem(HeliSilentName, &impl::heliSilent, group);
		group = menu->addGroup(MiscTabName, &miscTab);
		menu->addItem(SpiderManName, &impl::spiderMan, group);
		menu->addItem(FakeAdminName, &impl::fakeAdmin, group);
		menu->addItem(NeverSinkName, &impl::neverSink, group);

		RenderTargetView->Release();

		d3dfirst = false;
	}

	if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture))))
	{
		pContext->RSGetViewports(&vps, &viewport);
		ScreenCenterX = viewport.Width / 2.0f;
		ScreenCenterY = viewport.Height / 2.0f;
		pDevice->CreateRenderTargetView(RenderTargetTexture, NULL, &RenderTargetView);
		RenderTargetTexture->Release();
	}

	pContext->OMSetRenderTargets(1, &RenderTargetView, NULL);

	if (Renderer::NewFrame(pSwapChain))
	{
		menu->render();
		DrawScene();
	}

	Renderer::EndFrame();

	return origPresentHook(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall ResizeHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{

	Renderer::ResetCanvas();

	if (RenderTargetView != NULL)
		RenderTargetView->Release();


	return origResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

LRESULT CALLBACK WndProcHook(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (menu && menu->handleInput(window, message, wParam, lParam))
		return 0;

	return CallWindowProc(OrigWndProc, window, message, wParam, lParam);
}

void* DetourVTable(void** VTable, int Function, void* Detour)
{
	void* ret = VTable[Function];

	DWORD old;
	VirtualProtect(&(VTable[Function]), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	VTable[Function] = Detour;
	VirtualProtect(&(VTable[Function]), sizeof(void*), old, &old);

	return ret;
}

void Initialize()
{
	window = FindWindowA(NULL, "Rust");
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle("dxgi.dll");
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	} while (!hDXGIDLL);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	IDXGISwapChain* SwapChain;

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DContext = nullptr;

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof SwapChainDesc);
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = window;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.Windowed = TRUE;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createFlags = 0;

	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&SwapChain,
		&D3DDevice,
		&obtainedLevel,
		&D3DContext)))
	{
		MessageBox(window, "Failed to create directX device and swapchain!", "Error", MB_ICONERROR);
		return;
	}

	pSwapChainVtable = (uintptr_t*)((uintptr_t*)SwapChain)[0];

	origPresentHook = (D3D11PresentHook)DetourVTable((void**)pSwapChainVtable, 8, (void*)PresentHook);
	origResize = (D3D11ResizeBuffersHook)DetourVTable((void**)pSwapChainVtable, 13, (void*)ResizeHook);

	D3DDevice->Release();
	D3DContext->Release();
	SwapChain->Release();

	DWORD dwOld;
	VirtualProtect(PresentHook, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	OrigWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProcHook);
}