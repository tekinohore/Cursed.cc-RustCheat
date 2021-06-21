#include <RenderHandler.h>
#include <Globals.hpp>

void DrawScene()
{
	EntityLoop();
	if (impl::crosshair)
	{
		Renderer::Line({ ScreenCenterX,ScreenCenterY - 11 }, { ScreenCenterX,ScreenCenterY + 11 }, D2D1::ColorF::Red, 0.5f);
		Renderer::Line({ ScreenCenterX - 11,ScreenCenterY }, { ScreenCenterX + 11,ScreenCenterY }, D2D1::ColorF::Red, 0.5f);
	}
	if (impl::fovCircle)
	{
		Renderer::Circle({ ScreenCenterX,ScreenCenterY }, D2D1::ColorF::Red, impl::fovSlider, 1.0f);
	}
}