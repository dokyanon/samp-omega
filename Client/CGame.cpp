#include <SAMP+/CRPC.h>
#include <SAMP+/client/Client.h>
#include <SAMP+/client/CHUD.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/CGraphics.h>
#include <SAMP+/client/CCmdlineParams.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>
#include <SAMP+/client/Network.h>
#include <SAMP+/client/CSystem.h>
#include <Windows.h>


bool CGame::m_bGameLoaded;
bool CGame::InPauseMenu;
bool CGame::PauseMenuEnabled;
bool CGame::Frozen;
bool CGame::PedAnims;
bool CGame::RecreateMarkers = false;
bool CGame::VehicleBlips = true;
float CGame::AircraftMaxHeight;
bool CGame::inWater = false;

int CGame::X, CGame::Y;

int CGame::ClipAmmo[50];


void CGame::OnInitialize(IDirect3D9* pDirect3D, IDirect3DDevice9* pDevice, HWND hWindow)
{
	m_bGameLoaded = false;
	InPauseMenu = false;
	PauseMenuEnabled = true;

	X = 5;
	Y = 5;

//	box.Init(pDevice, 100, 60, 1366/2, 768/2, D3DCOLOR_ARGB(25, 255, 255, 255));

	CGraphics::Initialize(pDirect3D, pDevice);
}


void CGame::OnLoad()
{
	if (!CCmdlineParams::ArgumentExists("d") && CCmdlineParams::ArgumentExists("h"))
	{
		//CSystem::GetLoadedModules();
		CLog::Write("OnLoad success");
		CGame::UnprotectMemory();
		Network::Initialize(CCmdlineParams::GetArgumentValue("h"), atoi(CCmdlineParams::GetArgumentValue("p").c_str()) + 1);
		Network::Connect();
		CHUD::Initialize();
		
		CGame::SetAircraftMaxHeight(800.0f);

		/*for (int i = 0; i < sizeof(50); ++i) {
			CGame::ClipAmmo[i] = 7;
		}*/
	}
}

void CGame::OnUnload()
{
	CGraphics::CleanUp();
}

int CGame::OnCursorMove(int iX, int iY)
{
	return false;
}

void CGame::PreDeviceReset()
{
	CGraphics::OnReset();
}

BYTE CGame::OnPauseMenuChange(BYTE bFromMenuID, BYTE bToMenuID)
{
	RakNet::BitStream bitStream;
	bitStream.Write(bFromMenuID);
	bitStream.Write(bToMenuID);

	Network::SendRPC(eRPC::ON_PAUSE_MENU_CHANGE, &bitStream);

	return bToMenuID;
}

void CGame::PostDeviceReset()
{
	CGraphics::PostDeviceReset();
}

void CGame::PreEndScene()
{
	if(RecreateMarkers)
	{
		for(int i = 0; i < MAX_RACE_CHECKPOINTS; ++i)
		{
			char *thisCheckpoint = (char*) (RACE_CHECKPOINT_ADDR + (i * RACE_CHECKPOINT_OFFSET));

			if(*((unsigned short*) (thisCheckpoint)) != 257)
				*((bool*) (thisCheckpoint + 2)) = true;
		}

		RecreateMarkers = false;
	}

	CGraphics::PreEndScene();
}

void CGame::PostEndScene()
{

}

void CGame::BeginScene()
{
	CGraphics::BeginScene();
}

void CGame::OnWorldCreate()
{
	if (!IsLoaded())
	{
		OnLoad();
		m_bGameLoaded = true;
	}
}

void CGame::OnResolutionChange(UINT16 X, UINT16 Y)
{
	RakNet::BitStream bitStream;
	bitStream.Write(X);
	bitStream.Write(Y);

	Network::SendRPC(eRPC::ON_RESOLUTION_CHANGE, &bitStream);
}

void CGame::OnKeyDown(int key) 
{
	RakNet::BitStream bitStream;
	bitStream.Write(key);
	
	Network::SendRPC(eRPC::ON_KEY_DOWN, &bitStream);
}

void CGame::OnMouseClick(BYTE type, UINT16 X, UINT16 Y)
{
	RakNet::BitStream bitStream;
	bitStream.Write(type);
	bitStream.Write(X);
	bitStream.Write(Y);

	Network::SendRPC(eRPC::ON_MOUSE_CLICK, &bitStream);
}

void CGame::OnPauseMenuToggle(bool toggle)
{
	InPauseMenu = toggle;

	RakNet::BitStream bitStream;
	bitStream.Write(CGame::InPauseMenu);

	Network::SendRPC(eRPC::ON_PAUSE_MENU_TOGGLE, &bitStream);
}

void CGame::ToggleVehicleBlips(bool toggle)
{
	VehicleBlips = toggle;
}

bool CGame::IsLoaded()
{
	return m_bGameLoaded;
}

bool CGame::InMainMenu()
{
	return CMem::Get<bool>(0xBA6831);
}

bool CGame::Paused()
{
	return CMem::Get<bool>(0xB7CB49);
}

bool CGame::InMenu()
{
	return CMem::Get<bool>(0xBA67A4);
}

bool CGame::Playing()
{
	return IsLoaded() && !InMainMenu() && !Paused() && !InMenu();
}

bool CGame::HUDVisible()
{
	return CMem::Get<bool>(0xA444A0);
}

void CGame::SetHUDVisible(bool iVisible)
{
	CMem::PutSingle<bool>(0xA444A0, iVisible);
}

void CGame::SetClockStringFormat(char* format)
{
	CMem::Put<char*>(0x859A6C, format, 10);
}

void CGame::SetMoneyStringFormat(char* format)
{
	if (CMem::Get<int>(0xB7CE50) < 0)
		CMem::Put<char*>(0x866C8C, format, 6);
	else
		CMem::Put<char*>(0x866C94, format, 5);
}

void CGame::SetPlaneRadarColor(int r, int g, int b, int a)
{
	CMem::PutSingle<int>(0x58A514, r);
	CMem::PutSingle<int>(0x58A50D, g);
	CMem::PutSingle<int>(0x58A506, b);
	CMem::PutSingle<int>(0x58A4FF, a);
}

void CGame::SetRadioStation(unsigned long ulStation)
{
	((int(__thiscall*)(int, int, char, int, int))0x4EB3C0)(0x8CB6F8, ulStation, 0, 0, 0);
}

void CGame::SetWaveHeight(float fHeight)
{
	unsigned short ulOpcodes = 0xD8DD;
	CMem::Set(0x0072C667, 0x90, 0x04);
	CMem::Put<unsigned char>(0x72C665, &ulOpcodes, 2);
	CMem::Set(0x0072C659, 0x90, 0x0A);
	CMem::PutSingle<float>(0x00C812E8, fHeight);
}

void CGame::SetRocketDelay(int delay)
{
	CMem::PutSingle<int>(0x6D462E, delay);
	CMem::PutSingle<int>(0x6D4634, delay);
}

void CGame::UnprotectMemory()
{
	CMem::Unprotect(0x72C659, 0x12);
	CMem::Unprotect(0xC812E8, sizeof(float));
	//CMem::Unprotect(0x00C7F158, 38 * NUM_CHECKPOINTS);
}

void CGame::SetBlurIntensity(int intensity) 
{
	CMem::PutSingle<BYTE>(0x0704E8A, 0xE8); // call
	CMem::PutSingle<BYTE>(0x0704E8B, 0x11);
	CMem::PutSingle<BYTE>(0x0704E8C, 0xE2);
	CMem::PutSingle<BYTE>(0x0704E8D, 0xFF);
	CMem::PutSingle<BYTE>(0x0704E8E, 0xFF);

	CMem::PutSingle<int>(0x8D5104, intensity);
}

void CGame::SetGameSpeed(float speed) 
{
	CMem::PutSingle<float>(0xB7CB64, speed);
}

void CGame::ToggleDriveOnWater(bool toggle) 
{
	CMem::PutSingle<BYTE>(0x969152, (BYTE)toggle);
}

void CGame::ToggleFrozen(bool toggle) 
{
	Frozen = toggle;
}

void CGame::SetPedAnims(bool toggle)
{
	PedAnims = toggle;
}

unsigned int CGame::IsFrozen() 
{
	return (unsigned int)Frozen;
}

unsigned int CGame::UsePedAnims()
{
	return (unsigned int)PedAnims;
}


void CGame::ToggleSwitchReload(bool toggle)
{
	if (!toggle)
	{
		memcpy((void*)0x060B4FA, "\x90\x90\x90\x90\x90\x90", 6);
	}
	else
	{
		memcpy((void*)0x060B4FA, "\x89\x88\xA8\x05\x00\x00", 6); // mov [eax+000005A8],ecx
	}
}

BYTE CGame::GetVersion()
{
	unsigned char ucA = CMem::Get<BYTE>(0x748ADD);
	unsigned char ucB = CMem::Get<BYTE>(0x748ADE);
	if (ucA == 0xFF && ucB == 0x53)
		return 1; // usa
	else if (ucA == 0x0F && ucB == 0x84)
		return 2; // eu
	else if (ucA == 0xFE && ucB == 0x10)
		return 3;

	return 0;
}

void CGame::SetAircraftMaxHeight(float height)
{
	AircraftMaxHeight = height;
}

void CGame::SetJetpackMaxHeight(float height)
{
	CMem::PutSingle<float>(0x8703D8, height);
}

void CGame::OnRadioChange(BYTE id)
{
	RakNet::BitStream bitStream;
	
	bitStream.Write(id);

	Network::SendRPC(eRPC::ON_RADIO_CHANGE, &bitStream);
}

void CGame::OnDrinkSprunk()
{
	Network::SendRPC(eRPC::ON_DRINK_SPRUNK);
}

void CGame::ToggleInfiniteOxygen(bool toggle)
{
	CMem::PutSingle<BYTE>(0x96916E, (BYTE)toggle);
}

void CGame::ToggleWaterBuoyancy(bool toggle)
{
	CMem::PutSingle <BYTE>(0x6C3F80, (BYTE) toggle);
	if (toggle)
	{
		memcpy((void*) 0x6C3F80, "\x90\x90\x90\x90\x90\x90\x90", 7); //NOP
	}
	else
	{
		memcpy((void*) 0x6C3F80, "\xC6\x87\x98\x00\x00\x00\x01", 7); //MOV BYTE PTR DS:[EDI+98],1
	}
}

void CGame::ToggleUnderwaterEffect(bool toggle)
{
	CMem::PutSingle<BYTE>(0x00C402D3, (BYTE) toggle);
}

void CGame::ToggleNightVision(bool toggle)
{
	CMem::PutSingle<BYTE>(0xC402B8, (BYTE) toggle);
}

void CGame::SetPickupSize(float size)
{
	CMem::PutSingle<float>(0x858CC8, size);
}

void CGame::SetQuickReload(bool toggle)
{
	CMem::MemPut<WORD>(0x60B4F6, (toggle) ? 0x027C : 0x08EB);
}

void CGame::SetSunColor(unsigned int core_r, unsigned int core_g, unsigned int core_b,
	unsigned int corona_r, unsigned int corona_g, unsigned int corona_b)
{
	CMem::Set((LPVOID)0x55F9B2, 0x90, 4);
	CMem::Set((LPVOID)0x55F9DD, 0x90, 4);
	CMem::Set((LPVOID)0x55FA08, 0x90, 4);
	CMem::Set((LPVOID)0x55FA33, 0x90, 4);
	CMem::Set((LPVOID)0x55FA5E, 0x90, 4);
	CMem::Set((LPVOID)0x55FA8D, 0x90, 4);

	CMem::PutSingle<BYTE>(0xB7C4D0, core_r);
	CMem::PutSingle<BYTE>(0xB7C4D2, core_g);
	CMem::PutSingle<BYTE>(0xB7C4D4, core_b);

	CMem::PutSingle<BYTE>(0xB7C4D6, corona_r);
	CMem::PutSingle<BYTE>(0xB7C4D8, corona_g);
	CMem::PutSingle<BYTE>(0xB7C4DA, corona_b);
}

void CGame::ResetSunColor()
{
	BYTE originalMov[3] = { 0x66, 0x89, 0x46 };
	CMem::Cpy((LPVOID)0x55F9B2, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55F9B5, 0x30);
	CMem::Cpy((LPVOID)0x55F9DD, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55F9E0, 0x32);
	CMem::Cpy((LPVOID)0x55FA08, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55FA0B, 0x34);
	CMem::Cpy((LPVOID)0x55FA33, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55FA36, 0x36);
	CMem::Cpy((LPVOID)0x55FA5E, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55FA61, 0x38);
	CMem::Cpy((LPVOID)0x55FA8D, &originalMov, 3);
	CMem::MemPut<BYTE>(0x55FA90, 0x3A);
}

void CGame::SetWaterColor(float r, float g, float b, float a)
{
	CMem::PutSingle<BYTE>(0x8D5140, (BYTE)r);
	CMem::PutSingle<BYTE>(0x8D5141, (BYTE)g);
	CMem::PutSingle<BYTE>(0x8D5142, (BYTE)b);
	CMem::PutSingle<BYTE>(0x8D5143, (BYTE)a);

	CMem::MemPut<BYTE>(0x7051A7, 255 - (BYTE)a);
	CMem::MemPut<float>(0x872660, 255 - a);
	CMem::MemPut<BYTE>(0x7051D7, 255 - (BYTE)a);
}

void CGame::ResetWaterColor()
{
	CMem::PutSingle<DWORD>(0x8D5140, 0x40404040);
	CMem::MemPut<BYTE>(0x7051A7, 184);
	CMem::MemPut<float>(0x872660, 184.0f);
	CMem::MemPut<BYTE>(0x7051D7, 184);
}

void CGame::SetFlameColor(int color1, int color2)
{
	CMem::PutSingle<int>(0x4A394E, color1);
	CMem::PutSingle<int>(0x4A3967, color2);
}

void CGame::ToggleThermalVision(bool toggle)
{
	CMem::PutSingle<BYTE>(0xC402B9, (BYTE) toggle);
}

void CGame::OnEnterWater()
{
	inWater = true;

	//Network::SendRPC(eRPC::ON_ENTER_WATER);
}

void CGame::OnLeaveWater()
{
	inWater = false;

	//Network::SendRPC(eRPC::ON_LEAVE_WATER);
}

void CGame::Present()
{
	//CGraphics::DrawString("Running SA-MP+ Pre-Alpha Release", 15, X, Y, D3DCOLOR_ARGB(255, 255, 255, 255));

	//CGraphics::DrawBox(50, 50, 100, 90, D3DCOLOR_ARGB(255, 255, 255, 255));
}