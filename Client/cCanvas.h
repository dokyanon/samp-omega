#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>

#include <Gwen/Gwen.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/Renderers/DirectX9.h>

#include <SAMP+/client/CLog.h>
#include <SAMP+/client/CGraphics.h>
#include <vector>

class Canvas
{
public:
	Canvas();
	~Canvas();

	bool Init();

	bool SetShow(bool toggle)
	{
		return show = toggle;
	};

	bool IsHide() const
	{
		return !show;
	};

	void SetSize(int, int);
	bool SetDrawBackground(bool);
	void SetBackgroundColor(int, int, int, int);

	Gwen::Controls::Canvas* GetThis() const
	{
		return m_pCanvas;
	};
private:
	bool show;
	Gwen::Controls::Canvas* m_pCanvas;
	Gwen::Skin::TexturedBase* m_pSkin;
};