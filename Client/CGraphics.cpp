#include <SAMP+/client/CGraphics.h>
#include "cCanvas.h"

CPoint2D CGraphics::m_pResolution;
IDirect3D9* CGraphics::m_pDirect3D;
IDirect3DDevice9* CGraphics::m_pDevice;
bool CGraphics::m_bCursorEnabled;
extern std::vector<Text*> vText;
extern std::vector<Sprite*> vSprite;
extern std::vector<Box*> vBox;
extern std::vector<Canvas*> vCanvas;
extern std::vector<Button*> vButton;

Gwen::Renderer::DirectX9* CGraphics::pRenderer;

VOID CGraphics::SetScreenResolution(UINT uiWidth, UINT uiHeight)
{
	m_pResolution.X() = uiWidth;
	m_pResolution.Y() = uiHeight;
}

CPoint2D& CGraphics::GetScreenResolution()
{
	return m_pResolution;
}


void CGraphics::Initialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice)
{
	m_pDevice = pDevice;
	m_pDirect3D = pDirect3D;
	m_bCursorEnabled = false;
	UpdateScreenResolution();

	pRenderer = new Gwen::Renderer::DirectX9(m_pDevice);
	
	CLog::Write("CGraphics::Initialize");
}

void CGraphics::UpdateScreenResolution()
{
	D3DDISPLAYMODE dm;
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	SetScreenResolution(dm.Width, dm.Height);
}

HRESULT CGraphics::ToggleCursor(bool toggle)
{
	m_bCursorEnabled = toggle;
	return m_pDevice->ShowCursor(toggle);
}

bool CGraphics::IsCursorEnabled()
{
	return m_bCursorEnabled;
}

void CGraphics::OnReset()
{
	CLog::Write("CGraphics::OnReset");
	for (int I = 0; I < vText.size(); I++)
	{
		if (vText[I])
		{
			vText[I]->OnLostDevice();
		}
	}

	for (int I = 0; I < vSprite.size(); I++)
	{
		if (vSprite[I] && vSprite[I]->isInitialized())
		{
			vSprite[I]->OnLostDevice();
		}
	}

	for (int I = 0; I < vBox.size(); I++)
	{
		if (vBox[I])
		{
			vBox[I]->OnLostDevice();
		}
	}
}

void CGraphics::PostDeviceReset()
{
	CLog::Write("CGraphics::PostDeviceReset");
	for (int I = 0; I < vText.size(); I++)
	{
		if (vText[I])
		{
			vText[I]->OnResetDevice();
		}
	}
	for (int I = 0; I < vSprite.size(); I++)
	{
		if (vSprite[I] && vSprite[I]->isInitialized())
		{
			vSprite[I]->OnResetDevice();
		}
	}
	for (int I = 0; I < vBox.size(); I++)
	{
		if (vBox[I])
		{
			vBox[I]->OnResetDevice();
		}
	}
}

void CGraphics::PreEndScene()
{
	if (!CGame::IsLoaded())
	{

	}
	else
	{
		if (CGame::Playing())
		{
			for (int I = 0; I < vCanvas.size(); I++)
			{
				if (vCanvas[I])
				{
					vCanvas[I]->GetThis()->RenderCanvas();
					vCanvas[I]->GetThis()->Show();
				}		
			}

			for (int I = 0; I < vText.size(); I++)
			{
				if (vText[I])
				{
					vText[I]->Draw();
				}
			}
			for (int I = 0; I < vSprite.size(); I++)
			{
				if (vSprite[I] && vSprite[I]->isInitialized())
				{
					vSprite[I]->Draw();
				}
			}
			for (int I = 0; I < vBox.size(); I++)
			{
				if (vBox[I])
				{
					vBox[I]->Draw();
				}
			}
			for (int I = 0; I < vButton.size(); I++)
			{
				if (vButton[I])
				{
					vButton[I]->GetThis()->Show();
				}
			}
		}
		else //!Playing
		{
			for (int I = 0; I < vCanvas.size(); I++)
			{
				if (vCanvas[I])
				{
					vCanvas[I]->GetThis()->Hide();
				}
			}
			for (int I = 0; I < vButton.size(); I++)
			{
				if (vButton[I])
				{
					vButton[I]->GetThis()->Hide();
				}
			}
		}
	}
}

void CGraphics::BeginScene()
{
	
}

void CGraphics::CleanUp()
{
	CLog::Write("CGraphics::CleanUp");
	for (int I = 0; I < vText.size(); I++)
	{
		if (vText[I])
		{
			delete vText[I];
			vText[I] = nullptr;
		}
	}

	for (int I = 0; I < vSprite.size(); I++)
	{
		if (vSprite[I] && vSprite[I]->isInitialized())
		{
			delete vSprite[I];
			vSprite[I] = nullptr;
		}
	}
	for (int I = 0; I < vBox.size(); I++)
	{
		if (vBox[I])
		{
			delete vBox[I];
			vBox[I] = nullptr;
		}
	}
	for (int I = 0; I < vCanvas.size(); I++)
	{
		if (vCanvas[I])
		{
			delete vCanvas[I];
			vCanvas[I] = nullptr;
		}
	}
	for (int I = 0; I < vButton.size(); I++)
	{
		if (vButton[I])
		{
			delete vButton[I];
			vButton[I] = nullptr;
		}
	}
	if (pRenderer)
	{
		delete pRenderer;
		pRenderer = nullptr;
	}
}