#include "cCanvas.h"
std::vector<Canvas*> vCanvas(100);

Canvas::Canvas()
{
	CLog::Write("Canvas::Canvas");
	m_pCanvas = nullptr;
}

Canvas::~Canvas()
{
	if (m_pCanvas)
	{
		delete m_pCanvas;
		m_pCanvas = nullptr;
	}
	if (m_pSkin)
	{
		delete m_pSkin;
		m_pSkin = nullptr;
	}
	CLog::Write("Canvas::~Canvas");
}

bool Canvas::Init()
{
	m_pSkin = new Gwen::Skin::TexturedBase(CGraphics::GetRenderer());
	m_pSkin->Init("DefaultSkin.png");
	m_pCanvas = new Gwen::Controls::Canvas(m_pSkin);
	SetDrawBackground(true);
	return true;
}

void Canvas::SetBackgroundColor(int r, int g, int b, int a)
{
	CLog::Write("Canvas::SetBackgroundColor (%d,%d,%d,%d)", r, g, b, a);
	m_pCanvas->SetBackgroundColor(Gwen::Color(r, g, b, a));
}

void Canvas::SetSize(int w, int h)
{
	CLog::Write("Canvas::SetSize (%d,%d)", w, h);
	m_pCanvas->SetSize(w, h);
}

bool Canvas::SetDrawBackground(bool toggle)
{
	m_pCanvas->SetDrawBackground(toggle);
	return toggle;
}