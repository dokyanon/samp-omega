#pragma once

#include <DirectX/d3d9.h>
#include <DirectX/d3dx9.h>
#include <SAMP+/client/CLog.h>
#include <vector>

class Sprite
{
public:
	Sprite();
	~Sprite();

	bool Init(IDirect3DDevice9* device, char* filename, float x, float y, float width, float height);
	bool isInitialized() const;

	void Draw();
	void Resize(float width, float height);
	void Move(float x, float y);
	void Rotate(float angle);
	void Show(bool toggle);

	void Reset();
	void OnLostDevice();
	void OnResetDevice();

private:
	char* m_filename;

	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	bool initialized;
	bool show;

	IDirect3DTexture9 *tex;
	ID3DXSprite *sprite;

	IDirect3DDevice9* m_device;

	D3DXMATRIX mat;

	D3DXVECTOR2 center;

	float rotation;

	void SetTransformation();
};
