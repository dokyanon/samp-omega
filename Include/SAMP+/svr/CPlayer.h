#pragma once

#include <SAMP+/svr/CClientSocketInfo.h>

class CPlayer
{
public:
	CPlayer(CClientSocketInfo* socketInfo);
	~CPlayer();

	CClientSocketInfo* GetConnectionInfo();
	void SetInPauseMenu(bool bInPauseMenu);
	bool IsInPauseMenu();
	void SetCurrentMenuId(unsigned char ucMenuId);
	unsigned char GetCurrentMenuId();
	int GetResolutionX();
	int GetResolutionY();
	void SetResolution(int X, int Y);
	float GetAircraftHeight();
	float GetJetpackHeight();
	void SetAircraftHeight(float height);
	void SetJetpackHeight(float height);
	void ToggleVehicleBlips(bool toggle);
	bool GetVehicleBlips();
	void SetRadio(int id);
	int GetRadio();

	float GetPickupSize();
	void SetPickupSize(float);

	void SetPlaneRadarColor(int, int, int, int);
	int GetPlaneRadarColor_R();
	int GetPlaneRadarColor_G();
	int GetPlaneRadarColor_B();
	int GetPlaneRadarColor_A();

	bool IsCursorEnabled();
	void ToggleCursor(bool);
	void SetFlameColor(int, int);
	int GetFlameColor_1();
	int GetFlameColor_2();

private:
	CClientSocketInfo* m_pSockInfo;
	bool m_bInPauseMenu;
	unsigned char m_ucMenuId;
	int m_iResolutionX;
	int m_iResolutionY;
	float m_fAircraftHeight;
	float m_fJetpackHeight;
	bool m_bVehicleBlips;
	int m_iRadioStation;
	float m_fPickupSize;
	bool m_bCursorEnabled;
	int m_iFlameColor[2];
	int m_iPlaneRadarColor[4];
};