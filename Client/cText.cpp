#pragma once

#include "cText.h"
std::vector<Text*> vText(100);

Text::Text()
{
	CLog::Write("Text::Text");
	this->m_bDraw = false;
	this->m_pDevice = nullptr;
	this->m_pFont = nullptr;
	this->m_Text = nullptr;
	this->m_font_name = nullptr;
	this->m_cColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->m_ST = 0;
}

Text::~Text()
{
	if (this->m_pFont)
	{
		this->m_pFont->Release();
		this->m_pFont = nullptr;
	}
}

void Text::SetText(std::shared_ptr<CHAR> text)
{
	this->m_Text = text;
}

bool Text::Create(IDirect3DDevice9* pDevice, float x, float y, float width, float heigth, D3DCOLOR color, std::shared_ptr<CHAR> text, DWORD ST, std::shared_ptr<char> font_name)
{
	HRESULT result;
	if (FAILED(result = D3DXCreateFont(pDevice, heigth, width, FW_BLACK, 0, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font_name.get(), &m_pFont)))
	{
		CLog::Write("[Error 0x%X] Text::Create - Couldn't create the font", result);
		return false;
	}

	this->m_fX = x;
	this->m_fY = y;
	this->m_cColor = color;
	this->m_Text = text;
	this->m_ST = ST;
	this->m_pDevice = pDevice;
	this->m_bDraw = true;

	this->m_heigth = heigth;
	this->m_width = width;
	this->m_font_name = font_name;

	return true;
}

void Text::Draw()
{
	if (m_bDraw && m_pFont && m_Text.get()) 
	{
		RECT rect, rect2;
		SetRect(&rect, m_fX, m_fY, m_fX, m_fY);
		SetRect(&rect2, m_fX - 0.1, m_fY + 0.2, m_fX - 0.1, m_fY + 0.1);

		m_pFont->DrawTextA(NULL, m_Text.get(), -1, &rect2, m_ST, 0xff000000);
		m_pFont->DrawTextA(NULL, m_Text.get(), -1, &rect, m_ST, m_cColor);
	}
}

void Text::Show(bool toggle)
{
	m_bDraw = toggle;
}

void Text::OnLostDevice()
{
	if (m_pFont)
	{
		CLog::Write("Text::OnLostDevice");
		m_pFont->OnLostDevice();
	}
}

void Text::OnResetDevice()
{
	if (m_pFont)
	{
		CLog::Write("Text::OnResetDevice");
		m_pFont->OnResetDevice();
	}
}