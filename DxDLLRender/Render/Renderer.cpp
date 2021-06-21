#include "Renderer.h"

namespace Renderer {

	ID2D1Factory* Interface;
	ID2D1RenderTarget* Canvas;
	IDWriteFactory1* TextEngine;
	IDWriteTextFormat* TextFormat;
	ID2D1SolidColorBrush* SolidColor;
	bool initialized = false;

	__forceinline UINT wcslen(const wchar_t* Str) {
		const wchar_t* TempStr = Str;
		for (; *TempStr; ++TempStr);
		return (UINT)(TempStr - Str);
	}

	bool Init(IDXGISwapChain* SwapChain)
	{
		if (!initialized)
		{
			initialized = true;
			D2D1_FACTORY_OPTIONS CreateOpt = { D2D1_DEBUG_LEVEL_NONE };
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(TextEngine), (IUnknown**)&TextEngine);
			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &CreateOpt, (void**)&Interface);
			TextEngine->CreateTextFormat(L"Tahoma", NULL, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED, 12.f, L"", &TextFormat);
			if (!Interface || !TextEngine || !TextFormat) return false;
		}

		ID3D11Device* d3d_device;
		if (SwapChain->GetDevice(IID_PPV_ARGS(&d3d_device))) return false;
		WORD flagsOffset = *(WORD*)((*(uintptr_t**)d3d_device)[38] + 2);
		int& flags = *(INT*)((uintptr_t)d3d_device + flagsOffset);
		d3d_device->Release();

		IDXGISurface* d3d_bbuf;
		if (SwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d_bbuf)))
			return false;

		D2D1_RENDER_TARGET_PROPERTIES d2d_prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		flags |= 0x20;
		HRESULT canvas_state = Interface->CreateDxgiSurfaceRenderTarget(d3d_bbuf, d2d_prop, &Canvas); flags &= ~0x20;
		d3d_bbuf->Release();

		if (canvas_state)
			return false;
		if (!SolidColor)
			Canvas->CreateSolidColorBrush({}, &SolidColor);

		return true;
	}

	bool NewFrame(IDXGISwapChain* SwapChain)
	{
		if (!Canvas && !Init(SwapChain))
			return false;

		Canvas->BeginDraw();
		return true;
	}

	void ResetCanvas()
	{
		if (Canvas) {
			Canvas->Release();
			Canvas = nullptr;
		}
	}

	void FillRectangle(const Vector2& pos, const Vector2& size, const D2D1::ColorF& color)
	{
		SolidColor->SetColor(color);
		Canvas->FillRectangle({ pos.x, pos.y, pos.x + size.x, pos.y + size.y }, SolidColor);
	}

	void Circle(const Vector2& start, const D2D1::ColorF& color, float radius, float thickness)
	{
		SolidColor->SetColor(color);
		Canvas->DrawEllipse({ { start.x, start.y }, radius, radius }, SolidColor, thickness);
	}

	void Line(const Vector2& start, const Vector2& end, const D2D1::ColorF& color, float thickness)
	{
		SolidColor->SetColor(color);
		Canvas->DrawLine({ start.x, start.y }, { end.x, end.y }, SolidColor, thickness);
	}

	void OutlineRect(const Vector2& pos, const Vector2& size, const D2D1::ColorF& color, const D2D1::ColorF& oColor, float thickness)
	{
		SolidColor->SetColor(color);
		Canvas->FillRectangle({ pos.x, pos.y, pos.x + size.x, pos.y + size.y }, SolidColor);
		SolidColor->SetColor(oColor);
		Canvas->DrawRectangle({ pos.x, pos.y, pos.x + size.x, pos.y + size.y }, SolidColor, thickness);
	}

	void Rectangle(const Vector2& start, const Vector2& size, const D2D1::ColorF& color, float thickness)
	{
		SolidColor->SetColor(color);
		Canvas->DrawRectangle({ start.x, start.y, start.x + size.x, start.y + size.y }, SolidColor, thickness);
	}

	Vector2 DrawString(const Vector2& pos, const wchar_t* text, bool center, const D2D1::ColorF& color,bool outline)
	{
		if (center)
		{
			SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			IDWriteTextLayout* TextLayout;
			TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
			DWRITE_TEXT_METRICS TextInfo;
			TextLayout->GetMetrics(&TextInfo);
			Vector2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
			if (outline)
			{
				const auto x = pos.x - TextSize.x;
				const auto y = pos.y - TextSize.y;
				Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
				Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
			}

			SolidColor->SetColor(color);

			Canvas->DrawTextLayout({ pos.x - TextSize.x, pos.y - TextSize.y }, TextLayout, SolidColor);
			TextLayout->Release();
			return TextSize;
		}


		IDWriteTextLayout* TextLayout;
		TextEngine->CreateTextLayout(text, wcslen(text), TextFormat, 200.f, 100.f, &TextLayout);
		SolidColor->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

		if (outline)
		{
			const auto x = pos.x;
			const auto y = pos.y;

			Canvas->DrawTextLayout(D2D1::Point2F(x - 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x + 1, y), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y - 1), TextLayout, SolidColor);
			Canvas->DrawTextLayout(D2D1::Point2F(x, y + 1), TextLayout, SolidColor);
		}

		SolidColor->SetColor(color);
		Canvas->DrawTextA(text, wcslen(text), TextFormat, { pos.x, pos.y, FLT_MAX, FLT_MAX }, SolidColor);

		TextLayout->Release();

		return { 0,0 };
	}

	void EndFrame()
	{
		HRESULT state = Canvas->EndDraw();
		if (state == D2DERR_RECREATE_TARGET)
			ResetCanvas();
	}

}