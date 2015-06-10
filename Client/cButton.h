#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>

#include <Gwen/Gwen.h>
#include <Gwen/Controls/Button.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/Renderers/DirectX9.h>

#include <SAMP+/client/CLog.h>
#include <vector>

class Button
{
public:
	Button();
	~Button();

	bool Init(Gwen::Controls::Canvas* canvas);
	void SetText(char*);
	void SetPos(int, int);
	void SetSize(int, int);

	Gwen::Controls::Button* GetThis() const
	{
		return m_pButton;
	};
private:
	char* m_pText;
	Gwen::Controls::Button* m_pButton;
};