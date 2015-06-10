#include "cButton.h"
std::vector<Button*> vButton(100);

Button::Button()
{
	CLog::Write("Button::Button");
	m_pButton = nullptr;
}

bool Button::Init(Gwen::Controls::Canvas* canvas)
{
	m_pButton = new Gwen::Controls::Button(canvas);
	return true;
}

void Button::SetPos(int x, int y)
{
	m_pButton->SetPos(x, y);
}

void Button::SetSize(int w, int h)
{
	m_pButton->SetSize(w, h);
}

void Button::SetText(char* text)
{
	m_pText = text;
	m_pButton->SetText(text);
}

Button::~Button()
{
	CLog::Write("Button::~Button");
	if (m_pButton)
	{
		delete m_pButton;
		m_pButton = nullptr;
	}

	if (m_pText)
	{
		delete[] m_pText;
		m_pText = nullptr;
	}
}