#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>
#include <SAMP+/client/CLog.h>
#include <vector>
#include <memory>


class Text
{
public:
	Text();
	~Text();

	bool Create(IDirect3DDevice9* pDevice, float x, float y, float width, float height, D3DCOLOR color, std::shared_ptr<CHAR>, DWORD ST, std::shared_ptr<char>);

	void OnLostDevice();
	void OnResetDevice();

	void Draw();
	void SetText(std::shared_ptr<CHAR>);
	void Show(bool);

private:
	bool m_bDraw;

	IDirect3DDevice9* m_pDevice;
	ID3DXFont* m_pFont;

	std::shared_ptr<CHAR> m_Text;
	DWORD m_ST;

	float m_fX;
	float m_fY;

	float m_heigth;
	float m_width;

	std::shared_ptr<char> m_font_name;

	D3DCOLOR m_cColor;
};