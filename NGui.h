#include <d2d1.h>
#include <dwrite_1.h>
#include <intrin.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class RenderClass
{
private:
	//render context
	ID2D1Factory* Interface;
	ID2D1RenderTarget* Canvas;
	IDWriteFactory1* TextEngine;
	IDWriteTextFormat* TextFormat;
	ID2D1SolidColorBrush* SolidColor;

	//fast get wstring length
	__forceinline UINT wcslen(const wchar_t* Str)
	{
		const wchar_t* TempStr = Str;
		for (; *TempStr; ++TempStr);
		return (UINT)(TempStr - Str);
	}

	__declspec(noinline) bool InitRender(IDXGISwapChain* SwapChain)
	{
		//prep d2d render & text engine
		static bool initialized; if (!initialized) 
		{
			initialized = true; D2D1_FACTORY_OPTIONS CreateOpt = { D2D1_DEBUG_LEVEL_NONE };
			FC(dwrite, DWriteCreateFactory, DWRITE_FACTORY_TYPE_SHARED, __uuidof(TextEngine), (IUnknown**)&TextEngine);
			FC(d2d1, D2D1CreateFactory, D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &CreateOpt, (void**)&Interface);
			TextEngine->CreateTextFormat(StrW(L"Ebrima"), NULL, DWRITE_FONT_WEIGHT_THIN, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_CONDENSED, 12.f, L"", &TextFormat);
			if (!Interface || !TextEngine || !TextFormat) return false;
		}
		//get window flags var
		ID3D11Device* d3d_device;
		if (SwapChain->GetDevice(IID_PPV_ARGS(&d3d_device))) return false;
		WORD flagsOffset = *(WORD*)((*(DWORD64**)d3d_device)[38] + 2); //x64
		int& flags = *(INT*)((DWORD64)d3d_device + flagsOffset);
		d3d_device->Release();
		//get d3d backbuffer
		IDXGISurface* d3d_bbuf;
		if (SwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d_bbuf)))
			return false;
		//create canvas & cleanup
		D2D1_RENDER_TARGET_PROPERTIES d2d_prop = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		flags |= 0x20; HRESULT canvas_state = Interface->CreateDxgiSurfaceRenderTarget(d3d_bbuf, d2d_prop, &Canvas); flags &= ~0x20; d3d_bbuf->Release(); if (canvas_state) return false;
		if (!SolidColor) Canvas->CreateSolidColorBrush({}, &SolidColor); return true;
	}

public:
	//canvas mgr
	__forceinline bool NewFrame(IDXGISwapChain* SwapChain)
	{
		//need prep d2d canvas
		if (!Canvas && !InitRender(SwapChain))
		return false;
		//draw start
		Canvas->BeginDraw();
		return true;
	}

	__forceinline Vector2 CanvasSize() 
	{
		D2D1_SIZE_F Size = Canvas->GetSize();
		return Vector2{ Size.width, Size.height };
	}

	__forceinline void ResetCanvas() 
	{
		if (Canvas) {
			Canvas->Release();
			Canvas = nullptr;
		}
	}

	__forceinline void EndFrame() 
	{
		HRESULT state = Canvas->EndDraw();
		if (state == D2DERR_RECREATE_TARGET)
			ResetCanvas();
	}

	//line
	__forceinline void Line(const Vector2& Start, const Vector2& End, const D2D1::ColorF& Clr, float Thick = 1.5f) 
	{
		SolidColor->SetColor(Clr); Canvas->DrawLine({ Start.x, Start.y }, { End.x, End.y }, SolidColor, Thick);
	}

	//circle
	__forceinline void Ñircle(const Vector2& Start, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) 
	{
		SolidColor->SetColor(Clr); Canvas->DrawEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor, Thick);
	}

	__forceinline void FillCircle(const Vector2& Start, const D2D1::ColorF& Clr, float Rad) 
	{
		SolidColor->SetColor(Clr); Canvas->FillEllipse({ { Start.x, Start.y }, Rad, Rad }, SolidColor);
	}

	__forceinline void FillRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr) {
		SolidColor->SetColor(Clr); Canvas->FillRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor);
	}

	//rectangle
	__forceinline void Rectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Thick = 1.5f) 
	{
		SolidColor->SetColor(Clr); Canvas->DrawRectangle({ Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, SolidColor, Thick);
	}

	__forceinline void RoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad, float Thick = 1.5f) 
	{
		SolidColor->SetColor(Clr); Canvas->DrawRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y }, Rad, Rad }, SolidColor, Thick);
	}

	__forceinline void FillRoundedRectangle(const Vector2& Start, const Vector2& Sz, const D2D1::ColorF& Clr, float Rad) 
	{
		SolidColor->SetColor(Clr); Canvas->FillRoundedRectangle({ {Start.x, Start.y, Start.x + Sz.x, Start.y + Sz.y}, Rad, Rad }, SolidColor);
	}

	//text
	__forceinline Vector2 StringCenter(const Vector2& Start, const wchar_t* Str, const D2D1::ColorF& Clr = D2D1::ColorF(D2D1::ColorF::White)) 
	{
		SolidColor->SetColor(Clr); IDWriteTextLayout* TextLayout; TextEngine->CreateTextLayout(Str, this->wcslen(Str), TextFormat, 200.f, 100.f, &TextLayout);
		DWRITE_TEXT_METRICS TextInfo; TextLayout->GetMetrics(&TextInfo); Vector2 TextSize = { TextInfo.width / 2.f, TextInfo.height / 2.f };
		Canvas->DrawTextLayout({ Start.x - TextSize.x, Start.y - TextSize.y }, TextLayout, SolidColor); TextLayout->Release();
		return TextSize; //return half text size
	}

	Vector2 RenderString(const Vector2& pos, const wchar_t* text, bool center = false, const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::White), bool outline = false, bool Big = false)
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
		Canvas->DrawTextW(text, wcslen(text), TextFormat, { pos.x, pos.y, FLT_MAX, FLT_MAX }, SolidColor);

		TextLayout->Release();

		return { 0,0 };
	}

	__forceinline void String(const Vector2& Start, const wchar_t* Str, const D2D1::ColorF& Clr = D2D1::ColorF(D2D1::ColorF::White))
	{
		SolidColor->SetColor(Clr); Canvas->DrawTextW(Str, this->wcslen(Str), TextFormat, { Start.x, Start.y, FLT_MAX, FLT_MAX }, SolidColor);
	}
};

namespace GUI
{
	RenderClass Render;
	WNDPROC NextWndProc;
	enum Button {
		NoPress,
		Clicked,
		Pressed
	};
	struct IO {
		Button LKM;
		Vector2 MousePos;
		Vector2 MouseDelta;
		Vector2 OldMousePos;
		USHORT CurElement;
	} IO;
	struct WndData {
		Vector2 WndPos;
		Vector2 Size;
		Vector2 Pos;
		Vector2 Togele;
	} CurWnd;

	//str hash
	unsigned short __forceinline HashStr(const wchar_t* Str)
	{
		unsigned char i;
		unsigned short crc = 0xFFFF;
		while (wchar_t DChar = *Str++) {
			unsigned char Char = (unsigned char)DChar;
			crc ^= Char << 8;
			for (i = 0; i < 8; i++)
				crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
			Char = (unsigned char)(DChar >> 8);
			crc ^= Char << 8;
			for (i = 0; i < 8; i++)
				crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
		} return crc;
	}

	Vector2 __forceinline CenterLine(const Vector2& Pos)
	{
		return { (Pos.x + (CurWnd.Size.x / 2)), Pos.y };
	}

	bool __forceinline InRect(Vector2 Rect, Vector2 Size, Vector2 Dot)
	{
		return (Dot.x > Rect.x && Dot.x < Rect.x + Size.x && Dot.y > Rect.y && Dot.y < Rect.y + Size.y);
	}

	//input
	LRESULT WINAPI WndProc(HWND Wnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_LBUTTONDOWN:
			IO.LKM = Pressed;
			break;

		case WM_LBUTTONUP:
			IO.LKM = Clicked;
			IO.CurElement = 0;
			break;

		case WM_KEYUP:
			if (wParam == VK_INSERT)
			{
				Vars::Global::MenuVisible = !Vars::Global::MenuVisible;

			}
			break;

		case WM_MOUSEMOVE:
			IO.MousePos.x = (signed short)(lParam);
			IO.MousePos.y = (signed short)(lParam >> 16);
			break;
		}

		if (Vars::Global::MenuVisible && !ImGui_ImplWin32_WndProcHandler(Wnd, Msg, wParam, lParam))
			return TRUE;
		if (ImGui_ImplWin32_WndProcHandler(Wnd, Msg, wParam, lParam))
			return TRUE;

		return CallWindowProcW(NextWndProc, Wnd, Msg, wParam, lParam);
	}

	void ProcessInput(bool End = false)
	{
		if (!End)
		{
			//calc mouse delta
			IO.MouseDelta = IO.MousePos - IO.OldMousePos;
			IO.OldMousePos = IO.MousePos;
		}

		else
		{
			//update LKM button
			if (IO.LKM == Clicked)
				IO.LKM = NoPress;
		}
	}

	bool InputMgr(const wchar_t* Name, bool Reg = false)
	{
		unsigned short StrHash = HashStr(Name);
		if (Reg && !IO.CurElement) 
		{
			IO.CurElement = StrHash;
			return true;
		}
		else if (!Reg)
		return (IO.CurElement == StrHash);
		return false;
	}

	//main
	static int page;
	static int TabPage;
	static int ColorPage;

	void SliderInt(const wchar_t* Name, float* Switch, float Min, float Max)
	{
		wchar_t Result[64];
		_swprintf(Result, L"%s [%d m]", Name, (int)*Switch);
		Render.RenderString({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + 103.f }, Result, false, ConverToRGB(81, 77, 118), false);
		bool result;
		const float Pos_X = 185.f;
		const float Pos_Y = 105.f;
		const float Height = 320.f;

		if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X + 10.f, CurWnd.Togele.y + Pos_Y }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
		{
			float Val = ((((IO.MousePos.x - (Pos_X + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (Max - Min)) + Min);
			*Switch = ((Val > Max) ? Max : ((Val < Min) ? Min : Val)); InputMgr(Name, true);

		}

		float CurOff = (*Switch - Min) / (Max - Min);
		Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X + 10.f, CurWnd.Togele.y + Pos_Y }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
		Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X + 10.f, CurWnd.Togele.y + Pos_Y }, { (CurWnd.Size.x - Height - 20.f) * CurOff, 11.f }, ConverToRGB(84, 11, 61), 4.f);
		Render.FillCircle({ CurWnd.Togele.x + Pos_X + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOff), CurWnd.Togele.y + Pos_Y + 6 }, D2D1::ColorF::White, 8.f);
		CurWnd.Togele.y += 25.f;
	}

	void ColorPiker(const wchar_t* Name, D2D1::ColorF* Color, float Page, bool RGBA = false)
	{
		bool result;
		const float Pos_x = 385;
		const float Pos_Y = 100.f;
		const float Pos_Color_Pik = 15.f;
		Render.RenderString({ CurWnd.Togele.x + 55.f, CurWnd.Togele.y + Pos_Y }, const_cast<wchar_t*>(Name), false, ConverToRGB(81, 77, 118));
		if (IO.LKM == Clicked && InRect({ CurWnd.Togele.x + Pos_Color_Pik, CurWnd.Togele.y + Pos_Y }, { 35.f, 15.f }, IO.MousePos) && InputMgr(Name, true))
		{
			if (ColorPage == Page)
				ColorPage = 0;
			else
				ColorPage = Page;
		}
		Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_Color_Pik, CurWnd.Togele.y + Pos_Y }, { 35.f, 15.f }, *Color, 4.f);

		if (ColorPage == Page)
		{
			const float Height = 450.f;

			Render.FillRoundedRectangle({ CurWnd.Togele.x + 610, CurWnd.Togele.y + Pos_Y }, { (350),  RGBA ? 90.f : 70.f }, ConverToRGB(20, 15, 52), 6.f);
			//*** Slider Red ***//
			wchar_t ResultRed[64];
			int ColorRedValue = Color->r * 255.f;
			_swprintf(ResultRed, L"Red [%d]", ColorRedValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 103.f }, ResultRed, false, ConverToRGB(81, 77, 118));

			const float Pos_X1 = 675.f;
			const float Pos_Y1 = 105.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X1 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->r = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffRed = (Color->r * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { (CurWnd.Size.x - Height - 20.f) * CurOffRed, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X1 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffRed), CurWnd.Togele.y + Pos_Y1 + 6 }, D2D1::ColorF::White, 8.f);

			//*** Slider Gren ***//
			wchar_t ResultGreen[64];
			int ColorGreenValue = Color->g * 255.f;
			_swprintf(ResultGreen, L"Green [%d]", ColorGreenValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 126.f }, ResultGreen, false, ConverToRGB(81, 77, 118));

			const float Pos_X2 = 675.f;
			const float Pos_Y2 = 128.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X2 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->g = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffGreen = (Color->g * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { (CurWnd.Size.x - Height - 20.f) * CurOffGreen, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X2 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffGreen), CurWnd.Togele.y + Pos_Y2 + 6 }, D2D1::ColorF::White, 8.f);

			//*** Slider Blue ***//
			wchar_t ResultBlue[64];
			int ColorBlueValue = Color->b * 255.f;
			_swprintf(ResultBlue, L"Blue [%d]", ColorBlueValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 149.f }, ResultBlue, false, ConverToRGB(81, 77, 118));

			const float Pos_X3 = 675.f;
			const float Pos_Y3 = 151.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X3 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->b = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffBlue = (Color->b * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { (CurWnd.Size.x - Height - 20.f) * CurOffBlue, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X3 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffBlue), CurWnd.Togele.y + Pos_Y3 + 6 }, D2D1::ColorF::White, 8.f);

			if (RGBA)
			{
				wchar_t ResultApha[64];
				int ColorAlphaValue = Color->a * 255.f;
				_swprintf(ResultBlue, L"Alpha [%d]", ColorAlphaValue);
				Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 172.f }, ResultBlue, false, ConverToRGB(81, 77, 118));

				const float Pos_X4 = 675.f;
				const float Pos_Y4 = 174.f;

				if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
				{
					float Val = ((((IO.MousePos.x - (Pos_X4 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
					Color->a = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
					InputMgr(Name, true);
				}
				float CurOffAlpha = (Color->a * 255.f - 0) / (255 - 0);
				Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
				Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { (CurWnd.Size.x - Height - 20.f) * CurOffAlpha, 11.f }, ConverToRGB(84, 11, 61), 4.f);
				Render.FillCircle({ CurWnd.Togele.x + Pos_X4 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffAlpha), CurWnd.Togele.y + Pos_Y4 + 6 }, D2D1::ColorF::White, 8.f);
			}
		}
		CurWnd.Togele.y += 20.f;

	}

	void TogleAndColorBottton(const wchar_t* Name, bool* Switch, D2D1::ColorF* Color, float Page, bool RGBA = false)
	{
		bool result;
		bool SW = *Switch;
		const float Pos_x = 385;
		const float Pos_Y = 100.f;
		const float Pos_Color_Pik = 250.f;
		Render.RenderString({ CurWnd.Togele.x + 35.f, CurWnd.Togele.y + Pos_Y }, (wchar_t*)Name, false, ConverToRGB(81, 77, 118));
		if (IO.LKM == Clicked && InRect({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, IO.MousePos) && InputMgr(Name, true)) *Switch = SW = !SW;
		Render.RoundedRectangle({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, ConverToRGB(223, 3, 80), 2.f);
		if (SW)
			Render.FillRoundedRectangle({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, ConverToRGB(84, 11, 61), 2.f);
		if (IO.LKM == Clicked && InRect({ CurWnd.Togele.x + Pos_Color_Pik, CurWnd.Togele.y + Pos_Y }, { 35.f, 15.f }, IO.MousePos) && InputMgr(Name, true))
		{
			if (ColorPage == Page)
				ColorPage = 0;
			else
				ColorPage = Page;
		}
		Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_Color_Pik, CurWnd.Togele.y + Pos_Y }, { 35.f, 15.f }, *Color, 4.f);

		if (ColorPage == Page)
		{
			const float Height = 450.f;

			Render.FillRoundedRectangle({ CurWnd.Togele.x + 610, CurWnd.Togele.y + Pos_Y }, { (350),  RGBA ? 90.f : 70.f }, ConverToRGB(20, 15, 52), 6.f);
			//*** Slider Red ***//
			wchar_t ResultRed[64];
			int ColorRedValue = Color->r * 255.f;
			_swprintf(ResultRed, L"Red [%d]", ColorRedValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 103.f }, ResultRed, false, ConverToRGB(81, 77, 118));

			const float Pos_X1 = 675.f;
			const float Pos_Y1 = 105.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X1 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->r = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffRed = (Color->r * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X1 + 10.f, CurWnd.Togele.y + Pos_Y1 }, { (CurWnd.Size.x - Height - 20.f) * CurOffRed, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X1 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffRed), CurWnd.Togele.y + Pos_Y1 + 6 }, D2D1::ColorF::White, 8.f);

			//*** Slider Gren ***//
			wchar_t ResultGreen[64];
			int ColorGreenValue = Color->g * 255.f;
			_swprintf(ResultGreen, L"Green [%d]", ColorGreenValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 126.f }, ResultGreen, false, ConverToRGB(81, 77, 118));

			const float Pos_X2 = 675.f;
			const float Pos_Y2 = 128.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X2 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->g = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffGreen = (Color->g * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X2 + 10.f, CurWnd.Togele.y + Pos_Y2 }, { (CurWnd.Size.x - Height - 20.f) * CurOffGreen, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X2 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffGreen), CurWnd.Togele.y + Pos_Y2 + 6 }, D2D1::ColorF::White, 8.f);

			//*** Slider Blue ***//
			wchar_t ResultBlue[64];
			int ColorBlueValue = Color->b * 255.f;
			_swprintf(ResultBlue, L"Blue [%d]", ColorBlueValue);
			Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 149.f }, ResultBlue, false, ConverToRGB(81, 77, 118));

			const float Pos_X3 = 675.f;
			const float Pos_Y3 = 151.f;

			if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
			{
				float Val = ((((IO.MousePos.x - (Pos_X3 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
				Color->b = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
				InputMgr(Name, true);
			}
			float CurOffBlue = (Color->b * 255.f - 0) / (255 - 0);
			Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
			Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X3 + 10.f, CurWnd.Togele.y + Pos_Y3 }, { (CurWnd.Size.x - Height - 20.f) * CurOffBlue, 11.f }, ConverToRGB(84, 11, 61), 4.f);
			Render.FillCircle({ CurWnd.Togele.x + Pos_X3 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffBlue), CurWnd.Togele.y + Pos_Y3 + 6 }, D2D1::ColorF::White, 8.f);

			if (RGBA)
			{
				wchar_t ResultApha[64];
				int ColorAlphaValue = Color->a * 255.f;
				_swprintf(ResultBlue, L"Alpha [%d]", ColorAlphaValue);
				Render.RenderString({ CurWnd.Togele.x + 620.f, CurWnd.Togele.y + 172.f }, ResultBlue, false, ConverToRGB(81, 77, 118));

				const float Pos_X4 = 675.f;
				const float Pos_Y4 = 174.f;

				if (IO.LKM == Pressed && InRect({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { CurWnd.Size.x - Height - 20.f, 14.f }, IO.MousePos))
				{
					float Val = ((((IO.MousePos.x - (Pos_X4 + 15.f) - CurWnd.Togele.x) / (CurWnd.Size.x - Height - 36.f)) * (255 - 0)) + 0);
					Color->a = ((Val > 250) ? 250 : ((Val < 0) ? 0 : Val)) / 255.f;
					InputMgr(Name, true);
				}
				float CurOffAlpha = (Color->a * 255.f - 0) / (255 - 0);
				Render.RoundedRectangle({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { CurWnd.Size.x - Height - 20.f, 11.f }, ConverToRGB(223, 3, 80), 4.f);
				Render.FillRoundedRectangle({ CurWnd.Togele.x + Pos_X4 + 10.f, CurWnd.Togele.y + Pos_Y4 }, { (CurWnd.Size.x - Height - 20.f) * CurOffAlpha, 11.f }, ConverToRGB(84, 11, 61), 4.f);
				Render.FillCircle({ CurWnd.Togele.x + Pos_X4 + 18.f + ((CurWnd.Size.x - Height - 36.f) * CurOffAlpha), CurWnd.Togele.y + Pos_Y4 + 6 }, D2D1::ColorF::White, 8.f);
			}
		}
		CurWnd.Togele.y += 20.f;
	}

	void ToggleBotton(const wchar_t* Name, bool* Switch)
	{
		bool SW = *Switch;
		const float Pos_x = 385;
		const float Pos_Y = 100.f;
		bool result;
		Render.RenderString({ CurWnd.Togele.x + 35.f, CurWnd.Togele.y + Pos_Y }, (wchar_t*)Name, false, ConverToRGB(81, 77, 118));
		if (IO.LKM == Clicked && InRect({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, IO.MousePos) && InputMgr(Name, true))
		{
			*Switch = SW = !SW;
		}
		Render.RoundedRectangle({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, ConverToRGB(223, 3, 80), 2.f);
		if (SW)
			Render.FillRoundedRectangle({ CurWnd.Togele.x + 15.f, CurWnd.Togele.y + Pos_Y }, { 15.f, 15.f }, ConverToRGB(84, 11, 61), 2.f);

		CurWnd.Togele.y += 20.f;
	}

	void PanelButton(const wchar_t* Name, int tabnum)
	{
		bool result;
		if (IO.LKM == Clicked && InRect({ CurWnd.Pos.x + 100.f, CurWnd.Pos.y }, { 75.f, 25.f }, IO.MousePos) && InputMgr(Name, true))
		{
			if (page == tabnum)
			{
				page = 0;
				TabPage = 0;
				ColorPage = 0;
			}
			else
			{
				ColorPage = 0;
				TabPage = 0;
				page = tabnum;
			}
		}
		if (page == tabnum)
		{
			Render.FillRoundedRectangle({ CurWnd.Pos.x + 100.f, CurWnd.Pos.y }, { 75.f, 25.f }, ConverToRGB(45, 35, 114), 9);
		}

		Render.RenderString({ CurWnd.Pos.x + 100.f + 75.f / 2, CurWnd.Pos.y + 12 }, Name, true, D2D1::ColorF::White);
		CurWnd.Pos.x += 80.f;
	}

	void OtherButton(const wchar_t* Name, int Result)
	{
		const float Pos_X = 395.f;
		const float Pos_Y = 55.f;
		bool result;
		if (IO.LKM == Clicked && InRect({ CurWnd.Pos.x - Pos_X, CurWnd.Pos.y + Pos_Y }, { 100.f, 25.f }, IO.MousePos) && InputMgr(Name, true))
		{
			{
				if (TabPage == Result)
				{
					TabPage = 0;
					ColorPage = 0;
				}
				else
					TabPage = Result;
			}
		}
		Render.FillRoundedRectangle({ CurWnd.Pos.x - Pos_X, CurWnd.Pos.y + Pos_Y }, { 100.f, 30.f }, ConverToRGB(20, 15, 52), 0);
		Render.RoundedRectangle({ CurWnd.Pos.x - Pos_X, CurWnd.Pos.y + Pos_Y }, { 100.f, 30.f }, ConverToRGB(84, 11, 61), 4);
		Render.RenderString({ CurWnd.Pos.x - Pos_X + 50.f, CurWnd.Pos.y + Pos_Y + 12 }, Name, true, D2D1::ColorF::White);
		if (TabPage == Result)
			Render.Line({ CurWnd.Pos.x - Pos_X, CurWnd.Pos.y + Pos_Y + 26.f }, { CurWnd.Pos.x - Pos_X + 100, CurWnd.Pos.y + Pos_Y + 26.f }, ConverToRGB(223, 155, 78), 5);
		CurWnd.Pos.x += 105.f;
	}

	void RenderMenu(Vector2& Pos, const Vector2& Size)
	{
		//base menu
		ProcessInput();
		if (!CurWnd.WndPos.Zero()) Pos = CurWnd.WndPos;

		const int MenuHeight = 600;

		const wchar_t* cheat_name = L"Sense.vip";


		Render.FillRoundedRectangle(Pos, Vector2( MenuHeight, 50 ), ConverToRGB(20, 15, 52), 0);
		{
			Render.FillRectangle(Pos, Vector2( MenuHeight, 6 ), ConverToRGB(223, 155, 78));
			Render.RenderString(Vector2( Pos.x + 10, Pos.y + 15 ), cheat_name, false, D2D1::ColorF::White, false, true);
			Render.Line(Vector2( Pos.x + 90, Pos.y + 15 ), Vector2( Pos.x + 90, Pos.y + 40 ), ConverToRGB(40, 40, 64), 2);
		}

		if (page != NULL)
		{
			Render.FillRoundedRectangle(Vector2( Pos.x, Pos.y + 65 ), Vector2( MenuHeight,  500 ), ConverToRGB(20, 15, 52), 0);
			Render.FillRoundedRectangle(Vector2( Pos.x, Pos.y + 105 ), Vector2( MenuHeight, 460 ), ConverToRGB(20, 15, 52), 0);
		}

		CurWnd.WndPos = Vector2( Pos.x, Pos.y ); CurWnd.Size = Size;
		CurWnd.Pos = Vector2( Pos.x, Pos.y + 15.f );
		CurWnd.Togele = Vector2( Pos.x, Pos.y + 15.f );
	}

	void EndRenderMenu()
	{
		//drag window
		ProcessInput(true);
		if (InputMgr(L"##Drag") || (IO.LKM == Pressed && InRect(CurWnd.WndPos, CurWnd.Size, IO.MousePos) && InputMgr(L"##Drag", true)))
			CurWnd.WndPos = CurWnd.WndPos + IO.MouseDelta;
	}

	void Begin(Vector2& Pos, const Vector2& Size, const D2D1::ColorF& Clr)
	{
		//base menu
		ProcessInput();
		if (!CurWnd.WndPos.Zero()) Pos = CurWnd.WndPos;
		Render.FillRoundedRectangle(Pos, Size, Clr, 8.f);
		CurWnd.WndPos = Vector2( Pos.x, Pos.y ); CurWnd.Size = Size;
		CurWnd.Pos = Vector2( Pos.x, Pos.y + 25.f );
	}
}

namespace Render {
	RenderClass Object;
}