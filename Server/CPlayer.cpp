#include <SAMP+/svr/CPlayer.h>

CPlayer::CPlayer(CClientSocketInfo* socketInfo)
{
	m_pSockInfo = socketInfo;
	m_bInPauseMenu = false;
	m_ucMenuId = 42;
	m_fAircraftHeight = 800.0f;
	m_fJetpackHeight = 100.0f;
	m_fPickupSize = 1.0f;
	m_bCursorEnabled = false;
	m_iFlameColor[0] = 0;
	m_iFlameColor[1] = 0;
}

CPlayer::~CPlayer()
{
	delete m_pSockInfo;
}

CClientSocketInfo* CPlayer::GetConnectionInfo()
{
	return m_pSockInfo;
}

void CPlayer::SetInPauseMenu(bool bInPauseMenu)
{
	m_bInPauseMenu = bInPauseMenu;
}

bool CPlayer::IsInPauseMenu()
{
	return m_bInPauseMenu;
}

int CPlayer::GetResolutionX()
{
	return m_iResolutionX;
}

int CPlayer::GetResolutionY()
{
	return m_iResolutionY;
}

int CPlayer::GetFlameColor_1()
{
	return m_iFlameColor[0];
}

int CPlayer::GetFlameColor_2()
{
	return m_iFlameColor[1];
}

void CPlayer::SetFlameColor(int col1, int col2)
{
	m_iFlameColor[0] = col1;
	m_iFlameColor[1] = col2;
}

void CPlayer::SetResolution(int X, int Y)
{
	m_iResolutionX = X;
	m_iResolutionY = Y;
}

float CPlayer::GetPickupSize()
{
	return m_fPickupSize;
}

void CPlayer::SetPickupSize(float size)
{
	m_fPickupSize = size;
}

void CPlayer::SetPlaneRadarColor(int r, int g, int b, int a)
{
	m_iPlaneRadarColor[0] = r;
	m_iPlaneRadarColor[1] = g;
	m_iPlaneRadarColor[2] = b;
	m_iPlaneRadarColor[3] = b;
}

int CPlayer::GetPlaneRadarColor_R()
{
	return m_iPlaneRadarColor[0];
}

int CPlayer::GetPlaneRadarColor_G()
{
	return m_iPlaneRadarColor[1];
}

int CPlayer::GetPlaneRadarColor_B()
{
	return m_iPlaneRadarColor[2];
}

int CPlayer::GetPlaneRadarColor_A()
{
	return m_iPlaneRadarColor[3];
}

void CPlayer::ToggleCursor(bool toggle)
{
	m_bCursorEnabled = toggle;
}

bool CPlayer::IsCursorEnabled()
{
	return m_bCursorEnabled;
}

float CPlayer::GetAircraftHeight()
{
	return m_fAircraftHeight;
}

float CPlayer::GetJetpackHeight()
{
	return m_fJetpackHeight;
}

void CPlayer::SetAircraftHeight(float height)
{
	m_fAircraftHeight = height;
}

void CPlayer::SetJetpackHeight(float height)
{
	m_fJetpackHeight = height;
}

void CPlayer::SetCurrentMenuId(unsigned char ucMenuId)
{
	m_ucMenuId = ucMenuId;
}

void CPlayer::ToggleVehicleBlips(bool toggle)
{
	m_bVehicleBlips = toggle;
}

bool CPlayer::GetVehicleBlips()
{
	return m_bVehicleBlips;
}

unsigned char CPlayer::GetCurrentMenuId()
{
	return m_ucMenuId;
}

void CPlayer::SetRadio(int id)
{
	m_iRadioStation = id;
}

int CPlayer::GetRadio()
{
	return m_iRadioStation;
}