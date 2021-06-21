#pragma once
#include <D2D1.h>
#include <dwrite_1.h>
#include <D3D11.h>
#include <vector.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3d11.lib")

namespace Renderer {

	extern ID2D1Factory* Interface;
	extern ID2D1RenderTarget* Canvas;
	extern IDWriteFactory1* TextEngine;
	extern IDWriteTextFormat* TextFormat;
	extern ID2D1SolidColorBrush* SolidColor;
	extern bool initialized;

	UINT wcslen(const wchar_t* Str);

	bool Init(IDXGISwapChain* SwapChain);

	bool NewFrame(IDXGISwapChain* SwapChain);

	void ResetCanvas();

	void OutlineRect(const Vector2& pos, const Vector2& size, const D2D1::ColorF& color, const D2D1::ColorF& oColor, float thickness);

	void Rectangle(const Vector2& start, const Vector2& size, const D2D1::ColorF& color, float thickness);

	void FillRectangle(const Vector2& pos, const Vector2& size, const D2D1::ColorF& color);

	void Circle(const Vector2& start, const D2D1::ColorF& color, float radius, float thickness = 1.5f);

	void Line(const Vector2& start, const Vector2& end, const D2D1::ColorF& color, float thickness = 1.5f);

	Vector2 DrawString(const Vector2& pos, const wchar_t* text, bool center = false, const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::White), bool outline = false);

	void EndFrame();
}