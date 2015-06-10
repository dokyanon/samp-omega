#pragma once

#include "CSprite.h"
std::vector<Sprite*> vSprite(100);

Sprite::Sprite()
{
	CLog::Write("Sprite::Sprite");
	pos.x = 0;
	pos.y = 0;
	m_filename = nullptr;
	show = false;

	D3DXMatrixIdentity(&mat);

	initialized = false;
}

Sprite::~Sprite()
{
	CLog::Write("Sprite::~Sprite");
	if (sprite)
	{
		sprite->Release();
		sprite = nullptr;
	}

	if (tex)
	{
		tex->Release();
		tex = nullptr;
	}

	if (m_filename)
	{
		delete[] m_filename;
		m_filename = nullptr;
	}

	this->initialized = false;
}

bool Sprite::Init(LPDIRECT3DDEVICE9 device, char* filename, float x, float y, float width, float height)
{
	m_device = device;

	center = D3DXVECTOR2(width / 2, height / 2);
	scale = D3DXVECTOR2(width, height);

	this->m_filename = filename;

	pos.x = x;
	pos.y = y;

	std::string path = "samp-plus/";
	path.append(m_filename);

	HRESULT result;
	
	if (FAILED(result = D3DXCreateTextureFromFileEx(m_device, (LPCSTR)path.c_str(), width, height, D3DX_DEFAULT, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))

	//if (FAILED(result = D3DXCreateTextureFromFile(device, path.c_str(), &tex)))
	{
		CLog::Write("[Error 0x%X] Sprite::Init - Couldn't create the texture from file %s.", result, path);
		return false;
	}

	if (FAILED(result = D3DXCreateSprite(device, &sprite)))
	{
		CLog::Write("[Error 0x%X] Sprite::Init - Couldn't create the sprite.", result);
		return false;
	}

	SetTransformation();

	initialized = true;
	show = true;

	return true;
}

bool Sprite::isInitialized() const
{
	return initialized;
}

void Sprite::Draw()
{
	if (sprite && tex && show)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(tex, NULL, NULL, &D3DXVECTOR3(pos.x, pos.y, 0), D3DCOLOR_XRGB(255, 255, 255));
		sprite->End();
	}
}

void Sprite::Show(bool toggle)
{
	show = toggle;
}

void Sprite::Reset()
{
	CLog::Write("Sprite::Reset");
	HRESULT r = m_device->TestCooperativeLevel();

	if (r == D3DERR_DEVICELOST)
		OnLostDevice();

	else if (r == D3DERR_DEVICENOTRESET)
		OnResetDevice();
}

void Sprite::OnLostDevice()
{
	if (sprite)
	{
		CLog::Write("Sprite::OnLostDevice");
		sprite->OnLostDevice();
	}
}

void Sprite::OnResetDevice()
{
	if (sprite)
	{
		CLog::Write("Sprite::OnResetDevice");
		sprite->OnResetDevice();
	}
}

void Sprite::Resize(float width, float height)
{
	scale = D3DXVECTOR2(width, height);
}

void Sprite::Move(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Sprite::Rotate(float angle)
{
	rotation = angle;
}

void Sprite::SetTransformation()
{
	D3DXVECTOR2 spriteCenter = center;
	D3DXVECTOR2 trans = pos;
	D3DXVECTOR2 scaling = scale;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCenter, rotation, &trans);
}