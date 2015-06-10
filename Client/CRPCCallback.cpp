#include <SAMP+/client/CRPCCallback.h>
#include <SAMP+/client/CHUD.h>
#include <SAMP+/client/CGame.h>
#include <SAMP+/client/CHooks.h>
#include <SAMP+/client/CLocalPlayer.h>
#include <SAMP+/client/Proxy/CJmpProxy.h>
#include <SAMP+/client/CGraphics.h>
#include <memory>

extern std::vector<Text*> vText;
extern std::vector<Sprite*> vSprite;
extern std::vector<Box*> vBox;
extern std::vector<Canvas*> vCanvas;
extern std::vector<Button*> vButton;


void CRPCCallback::Initialize()
{
	CRPC::Add(eRPC::TOGGLE_HUD_COMPONENT, ToggleHUDComponent);
	CRPC::Add(eRPC::SET_RADIO_STATION, SetRadioStation);
	CRPC::Add(eRPC::SET_WAVE_HEIGHT, SetWaveHeight);
	CRPC::Add(eRPC::SET_ROCKET_DELAY, SetRocketDelay);
	CRPC::Add(eRPC::TOGGLE_PAUSE_MENU, TogglePauseMenu);
	CRPC::Add(eRPC::SET_HUD_COMPONENT_COLOUR, SetHUDComponentColour);
	CRPC::Add(eRPC::SET_CHECKPOINT_EX, SetPlayerCheckpointEx);
	CRPC::Add(eRPC::SET_RACE_CHECKPOINT_EX, SetPlayerRaceCheckpointEx);
	CRPC::Add(eRPC::SET_CHECKPOINT_COLOUR, SetCheckpointColour);
	CRPC::Add(eRPC::SET_RACE_CHECKPOINT_COLOUR, SetRaceCheckpointColour);
	CRPC::Add(eRPC::TOGGLE_ACTION, ToggleAction);
	CRPC::Add(eRPC::SET_CLIP_AMMO, SetAmmoInClip);
	CRPC::Add(eRPC::SET_NO_RELOAD, SetNoReload);
	CRPC::Add(eRPC::SET_BLUR_INTENSITY, SetBlur);
	CRPC::Add(eRPC::TOGGLE_DRIVE_ON_WATER, DriveOnWater);
	CRPC::Add(eRPC::SET_GAME_SPEED, SetSpeed);
	CRPC::Add(eRPC::TOGGLE_PLAYER_FROZEN, SetFrozen);
	CRPC::Add(eRPC::SET_PLAYER_ANIMS, SetAnims);
	CRPC::Add(eRPC::TOGGLE_SWITCH_RELOAD, ToggleSwitchReload);
	CRPC::Add(eRPC::TOGGLE_INFINITE_RUN, ToggleInfiniteRun);
	CRPC::Add(eRPC::SET_AIRCRAFT_HEIGHT, SetAircraftHeight);
	CRPC::Add(eRPC::SET_JETPACK_HEIGHT, SetJetpackHeight);
	CRPC::Add(eRPC::TOGGLE_VEHICLE_BLIPS, ToggleVehicleBlips);
	CRPC::Add(eRPC::TOGGLE_INFINITE_OXYGEN, ToggleInfiniteOxygen);
	CRPC::Add(eRPC::TOGGLE_WATER_BUOYANCY, ToggleWaterBuoyancy);
	CRPC::Add(eRPC::TOGGLE_UNDERWATER_EFFECT, ToggleUnderwaterEffect);
	CRPC::Add(eRPC::TOGGLE_NIGHTVISION, ToggleNightVision);
	CRPC::Add(eRPC::SET_PICKUP_SIZE, SetPickupSize);
	CRPC::Add(eRPC::SET_WATER_COLOR, SetWaterColor);
	CRPC::Add(eRPC::SET_FLAME_COLOR, SetFlameColor);
	CRPC::Add(eRPC::SET_CLOCK_STRING_FORMAT, SetClockStringFormat);
	CRPC::Add(eRPC::SET_MONEY_STRING_FORMAT, SetMoneyStringFormat);
	CRPC::Add(eRPC::TOGGLE_THERMALVISION, ToggleThermalVision);

	CRPC::Add(eRPC::SET_SUN_COLOR, SetSunColor);
	CRPC::Add(eRPC::SET_QUICK_RELOAD, SetQuickReload);
	CRPC::Add(eRPC::RESET_WATER_COLOR, ResetWaterColor);
	CRPC::Add(eRPC::SET_PLANE_RADAR_COLOR, SetPlaneRadarColor);
	CRPC::Add(eRPC::TOGGLE_PLAYER_CURSOR, TogglePlayerCursor);
	CRPC::Add(eRPC::CREATE_TEXT, CreateText);
	CRPC::Add(eRPC::SET_TEXT_TEXT, SetTextText);
	CRPC::Add(eRPC::DESTROY_TEXT, DestroyText);
	CRPC::Add(eRPC::SHOW_TEXT, ShowText);
	CRPC::Add(eRPC::SHOW_BOX, ShowBox);

	CRPC::Add(eRPC::CREATE_CANVAS, CreateCanvas);
	CRPC::Add(eRPC::SET_SIZE_CANVAS, SetSizeCanvas);
	CRPC::Add(eRPC::SET_BACK_COLOR_CANVAS, SetBackColorCanvas);
	CRPC::Add(eRPC::DESTROY_CANVAS, DestroyCanvas);

	CRPC::Add(eRPC::CREATE_BUTTON, CreateButton);
	CRPC::Add(eRPC::SET_SIZE_BUTTON, SetSizeButton);
	CRPC::Add(eRPC::SET_TEXT_BUTTON, SetTextButton);
	CRPC::Add(eRPC::SET_POS_BUTTON, SetPosButton);
	CRPC::Add(eRPC::DESTROY_BUTTON, DestroyButton);

	CRPC::Add(eRPC::CREATE_SPRITE, CreateSprite);
	CRPC::Add(eRPC::DESTROY_SPRITE, DestroySprite);
	CRPC::Add(eRPC::RESIZE_SPRITE, ResizeSprite);
	CRPC::Add(eRPC::MOVE_SPRITE, MoveSprite);
	CRPC::Add(eRPC::ROTATE_SPRITE, RotateSprite);
	CRPC::Add(eRPC::SHOW_SPRITE, ShowSprite);

	CRPC::Add(eRPC::CREATE_BOX, CreateBox);
	CRPC::Add(eRPC::DESTROY_BOX, DestroyBox);

	CGame::OnResolutionChange(*(int*)0x0C9C040, *(int*)0x0C9C044);
	CMem::InstallJmp(0x0584770, CJmpProxy::MarkersHook, CJmpProxy::MarkersHookJmpBack, 6);
}

RPC_CALLBACK CRPCCallback::ToggleHUDComponent(RPC_ARGS)
{
	unsigned char ucComponent;
	bool bToggle;

	if (bsData.Read(ucComponent) && bsData.Read(bToggle))
		CHUD::ToggleComponent(ucComponent, bToggle);

}

RPC_CALLBACK CRPCCallback::SetHUDComponentColour(RPC_ARGS)
{
	unsigned char ucComponent;
	DWORD dwColour;

	if (bsData.Read(ucComponent) && bsData.Read(dwColour))
	{
		RakNet::BitStream::ReverseBytesInPlace((unsigned char*)&dwColour, sizeof(DWORD));

		CHUD::SetComponentColour(ucComponent, dwColour);
	}
}

RPC_CALLBACK CRPCCallback::SetRadioStation(RPC_ARGS)
{
	unsigned char ucStation;

	if (bsData.Read(ucStation))
		CGame::SetRadioStation(ucStation);
}

RPC_CALLBACK CRPCCallback::SetWaveHeight(RPC_ARGS)
{
	float fHeight;

	if (bsData.Read(fHeight))
		CGame::SetWaveHeight(fHeight);

}

RPC_CALLBACK CRPCCallback::SetRocketDelay(RPC_ARGS)
{
	int delay;

	if (bsData.Read(delay))
		CGame::SetRocketDelay(delay);

}

RPC_CALLBACK CRPCCallback::TogglePauseMenu(RPC_ARGS)
{
	bool ucToggle;

	if (bsData.Read(ucToggle))
		CGame::PauseMenuEnabled = ucToggle;

}

RPC_CALLBACK CRPCCallback::SetCheckpointColour(RPC_ARGS)
{
	int dwColour;
	if (bsData.Read(dwColour))
	{
		int colR = (dwColour & 0xFF000000) >> 24;
		int colG = (dwColour & 0x00FF0000) >> 16;
		int colB = (dwColour & 0x0000FF00) >> 8;
		int colA = (dwColour & 0x000000FF);
		
		for(int i = 0; i < MAX_CHECKPOINTS; ++i)
		{
			unsigned char *thisCheckpoint = (unsigned char*) (CHECKPOINT_ADDR + (i * CHECKPOINT_OFFSET));

			if(*((unsigned short*) (thisCheckpoint + 80)) == 1)
			{
				*((unsigned long*) (thisCheckpoint + 88)) = ((colA << 24) | (colB << 16) | (colG << 8) | colR);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::SetRaceCheckpointColour(RPC_ARGS)
{
	int dwColour;
	if (bsData.Read(dwColour))
	{
		int colR = (dwColour & 0xFF000000) >> 24;
		int colG = (dwColour & 0x00FF0000) >> 16;
		int colB = (dwColour & 0x0000FF00) >> 8;
		int colA = (dwColour & 0x000000FF);

		for(int i = 0; i < MAX_RACE_CHECKPOINTS; ++i)
		{
			unsigned char *thisCheckpoint = (unsigned char*) (RACE_CHECKPOINT_ADDR + (i * RACE_CHECKPOINT_OFFSET));

			if(*((bool*) (thisCheckpoint + 2)))
			{
				*((bool*) (thisCheckpoint + 2)) = false;
				*((unsigned long*) (thisCheckpoint + 8)) = ((colA << 24) | (colB << 16) | (colG << 8) | colR);
			}
		}

		CGame::RecreateMarkers = true;
	}
}

RPC_CALLBACK CRPCCallback::SetPlayerCheckpointEx(RPC_ARGS)
{
	CVector pos;
	float size;
	unsigned int col;
	unsigned short period;
	float pulse;
	short rot_rate;
	bool checkZ;

	if(bsData.Read(pos.x) && bsData.Read(pos.y) && bsData.Read(pos.z) && bsData.Read(size) && bsData.Read(col) && bsData.Read(period) && bsData.Read(pulse) && bsData.Read(rot_rate) && bsData.Read(checkZ))
	{
		// Crash
		//((PlaceCheckpoint_t) CHECKPOINT_PLACE)(1, 5, &pos, size, (col & 0xFF000000) >> 24, (col & 0x00FF0000) >> 16, (col & 0x0000FF00) >> 8, col & 0x000000FF, period, pulse, rot_rate, 0.0f, 0.0f, 0.0f, checkZ);
	}
}

RPC_CALLBACK CRPCCallback::SetPlayerRaceCheckpointEx(RPC_ARGS)
{
	unsigned char type;
	float pos[3];
	float next[3];
	float size;
	unsigned int col;
	unsigned short period;
	float pulse;
	short rot_rate;

	if(bsData.Read(type) && bsData.Read(pos[0]) && bsData.Read(pos[1]) && bsData.Read(pos[2]) && bsData.Read(next[0]) && bsData.Read(next[1]) && bsData.Read(next[2]) && bsData.Read(size) && bsData.Read(col) && bsData.Read(period) && bsData.Read(pulse) && bsData.Read(rot_rate))
	{
		char *thisCheckpoint = (char*) (RACE_CHECKPOINT_ADDR);

		float length = sqrtf(powf((pos[0]-next[0]), 2) + powf((pos[1]-next[1]), 2) + powf((pos[2]-next[2]), 2) );

		*((unsigned short*) (thisCheckpoint)) = type;
		*((bool*) (thisCheckpoint + 2)) = true;
		*((bool*) (thisCheckpoint + 3)) = true;
		*((unsigned long*) (thisCheckpoint + 4)) = 1;
		*((unsigned long*) (thisCheckpoint + 8)) = ((col & 0x000000FF) << 24) | ((col & 0x0000FF00) << 8) | ((col & 0x00FF0000) >> 8) | ((col & 0xFF000000) >> 24);
		*((unsigned short*) (thisCheckpoint + 12)) = period;
		*((short*) (thisCheckpoint + 14)) = rot_rate;
		((CVector*) (thisCheckpoint + 16))->x = pos[0];
		((CVector*) (thisCheckpoint + 16))->y = pos[1];
		((CVector*) (thisCheckpoint + 16))->z = pos[2];
		((CVector*) (thisCheckpoint + 28))->x = (next[0]-pos[0]) / length;
		((CVector*) (thisCheckpoint + 28))->y = (next[1]-pos[1]) / length;
		((CVector*) (thisCheckpoint + 28))->z = (next[2]-pos[2]) / length;
		*((float*) (thisCheckpoint + 40)) = pulse;
		*((float*) (thisCheckpoint + 44)) = size;
		*((float*) (thisCheckpoint + 48)) = 43.84f;
		*((float*) (thisCheckpoint + 52)) = 0.0;
	}
}

RPC_CALLBACK CRPCCallback::ToggleAction(RPC_ARGS)
{
	BYTE action;
	bool bToggle;

	if (bsData.Read(action) && bsData.Read(bToggle))
	{
		CLog::Write("ToggleAction %i %i", action, bToggle);
		CLocalPlayer::SetActionEnabled(action, bToggle);
	}
}

RPC_CALLBACK CRPCCallback::SetPlaneRadarColor(RPC_ARGS)
{
	int r, g, b, a;

	if (bsData.Read(r) && bsData.Read(g) && bsData.Read(b) && bsData.Read(a))
	{
		CGame::SetPlaneRadarColor(r, g, b, a);
	}
}

RPC_CALLBACK CRPCCallback::TogglePlayerCursor(RPC_ARGS)
{
	bool bToggle;

	if (bsData.Read(bToggle))
	{
		CGraphics::ToggleCursor(bToggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAmmoInClip(RPC_ARGS)
{
	DWORD dwNewAmmo;
	BYTE bSlotId;

	if (bsData.Read(bSlotId) && bsData.Read(dwNewAmmo))
	{
		CLocalPlayer::SetClipAmmo(bSlotId, dwNewAmmo);
	}
}

RPC_CALLBACK CRPCCallback::SetNoReload(RPC_ARGS)
{

	bool toggle;

	if (bsData.Read(toggle))
	{
		CLocalPlayer::SetNoReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleInfiniteRun(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CLocalPlayer::ToggleInfiniteRun(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetSpeed(RPC_ARGS)
{

	float speed;

	if (bsData.Read(speed))
	{
		CGame::SetGameSpeed(speed);
	}
}

RPC_CALLBACK CRPCCallback::DriveOnWater(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle)) 
	{
		CGame::ToggleDriveOnWater(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetBlur(RPC_ARGS)
{
	int intensity;
	if (bsData.Read(intensity))
	{
		CGame::SetBlurIntensity(intensity);
	}
}

RPC_CALLBACK CRPCCallback::SetFrozen(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleFrozen(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAnims(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::SetPedAnims(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleSwitchReload(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleSwitchReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetAircraftHeight(RPC_ARGS)
{
	float height;
	if (bsData.Read(height))
	{
		CGame::SetAircraftMaxHeight(height);
	}
}

RPC_CALLBACK CRPCCallback::SetJetpackHeight(RPC_ARGS)
{
	float height;
	if (bsData.Read(height))
	{
		CGame::SetJetpackMaxHeight(height);
	}
}

RPC_CALLBACK CRPCCallback::ToggleVehicleBlips(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleVehicleBlips(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleInfiniteOxygen(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleInfiniteOxygen(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleWaterBuoyancy(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleWaterBuoyancy(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleUnderwaterEffect(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleUnderwaterEffect(toggle);
	}
}


RPC_CALLBACK CRPCCallback::SetPickupSize(RPC_ARGS)
{
	float size;
	if (bsData.Read(size))
	{
		CGame::SetPickupSize(size);
	}
}

RPC_CALLBACK CRPCCallback::SetQuickReload(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::SetQuickReload(toggle);
	}
}

RPC_CALLBACK CRPCCallback::SetWaterColor(RPC_ARGS)
{
	float r, g, b, a;
	if (bsData.Read(r) && bsData.Read(g) && bsData.Read(b) && bsData.Read(a))
	{
		CGame::SetWaterColor(r, g, b, a);
	}
}

RPC_CALLBACK CRPCCallback::SetSunColor(RPC_ARGS)
{
	unsigned int core_r, core_g, core_b, corona_r, corona_g, corona_b;
	if (bsData.Read(core_r) && bsData.Read(core_g) && bsData.Read(core_b) 
		&& bsData.Read(corona_r) && bsData.Read(corona_g) && bsData.Read(corona_b))
	{
		CGame::SetSunColor(core_r, core_g, core_b, corona_r, corona_g, corona_b);
	}
}

RPC_CALLBACK CRPCCallback::ResetSunColor(RPC_ARGS)
{
	CGame::ResetSunColor();
}

RPC_CALLBACK CRPCCallback::ResetWaterColor(RPC_ARGS)
{
	CGame::ResetWaterColor();
}


RPC_CALLBACK CRPCCallback::SetFlameColor(RPC_ARGS)
{
	int color[2];
	if (bsData.Read(color[0]) && bsData.Read(color[1]))
	{
		CGame::SetFlameColor(color[0], color[1]);
	}
}

RPC_CALLBACK CRPCCallback::ToggleNightVision(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleNightVision(toggle);
	}
}

RPC_CALLBACK CRPCCallback::ToggleThermalVision(RPC_ARGS)
{
	bool toggle;
	if (bsData.Read(toggle))
	{
		CGame::ToggleThermalVision(toggle);
	}
}

RPC_CALLBACK CRPCCallback::CreateButton(RPC_ARGS)
{
	int id, canvas;
	if (bsData.Read(id) && bsData.Read(canvas))
	{
		if (vCanvas[canvas])
		{
			Button* gwen_button = new Button;
			if (gwen_button->Init(vCanvas[canvas]->GetThis()))
			{
				if (id > vButton.size()) vButton.resize(id + 100);
				vButton[id] = gwen_button;
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::SetPosButton(RPC_ARGS)
{
	int id, x, y;
	if (bsData.Read(id) && bsData.Read(x) && bsData.Read(y))
	{
		if (vButton[id])
		{
			vButton[id]->SetPos(x, y);
		}
	}
}

RPC_CALLBACK CRPCCallback::SetSizeButton(RPC_ARGS)
{
	int id, w, h;
	if (bsData.Read(id) && bsData.Read(w) && bsData.Read(h))
	{
		if (vButton[id])
		{
			vButton[id]->SetSize(w, h);
		}
		else
		{
			CLog::Write("Button %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::SetTextButton(RPC_ARGS)
{
	int id;
	char* text = new char[32];
	if (bsData.Read(id) && bsData.Read(text))
	{
		if (vButton[id])
		{
			vButton[id]->SetText(text);
		}
		else
		{
			CLog::Write("Button %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::DestroyButton(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		if (vButton[id])
		{
			delete vButton[id];
			vButton[id] = nullptr;
		}
		else
		{
			CLog::Write("Button %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::CreateCanvas(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		Canvas* gwen_canvas = new Canvas;
		if (gwen_canvas->Init())
		{
			if (id > vCanvas.size()) vCanvas.resize(id + 100);
			vCanvas[id] = gwen_canvas;
		}
	}
}

RPC_CALLBACK CRPCCallback::SetSizeCanvas(RPC_ARGS)
{
	int id, w, h;
	if (bsData.Read(id) && bsData.Read(w) && bsData.Read(h))
	{
		if (vCanvas[id])
		{
			vCanvas[id]->SetSize(w, h);
		}
		else
		{
			CLog::Write("Canvas %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::SetBackColorCanvas(RPC_ARGS)
{
	int id, r, g, b, a;
	if (bsData.Read(id) && bsData.Read(r) && bsData.Read(g) && bsData.Read(b) && bsData.Read(a))
	{
		if (vCanvas[id])
		{
			vCanvas[id]->SetBackgroundColor(r, g, b, a);
		}
		else
		{
			CLog::Write("Canvas %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::DestroyCanvas(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		if (vCanvas[id])
		{
			delete vCanvas[id];
			vCanvas[id] = nullptr;
		}
		else
		{
			CLog::Write("Canvas %d not found!", id);
		}
	}
}

RPC_CALLBACK CRPCCallback::CreateSprite(RPC_ARGS)
{
	int id;
	float	x, y,
			w, h
	;
	char* res = new char[32];

	if (
		bsData.Read(id) &&

		bsData.Read(x) &&
		bsData.Read(y) &&

		bsData.Read(w) &&
		bsData.Read(h) &&

		bsData.Read(res)
		)
	{
		Sprite* d3dSprite = new Sprite;
		if	(d3dSprite->Init(CGraphics::GetDevice(),
			res, x, y, w, h)
			)
		{
			if (id > vSprite.size()) vSprite.resize(id + 100);
			vSprite[id] = d3dSprite;
		}
	}
}

RPC_CALLBACK CRPCCallback::CreateBox(RPC_ARGS)
{
	int id;
	unsigned int a, r, g, b;
	float	
		x, y,
		w, h
	;
	char* res = new char[32];

	if (
		bsData.Read(id) &&

		bsData.Read(x) &&
		bsData.Read(y) &&

		bsData.Read(w) &&
		bsData.Read(h) &&

		bsData.Read(res) &&
		bsData.Read(a) && bsData.Read(r) && bsData.Read(g) && bsData.Read(b)
		)
	{
		Box* d3dBox = new Box;

		if (d3dBox->Init(CGraphics::GetDevice(),
			res, w, h, x, y, D3DCOLOR_ARGB(a, r, g, b))
			)
		{
			if (id > vBox.size()) vBox.resize(id + 100);
			vBox[id] = d3dBox;
		}
	}
}

RPC_CALLBACK CRPCCallback::ShowBox(RPC_ARGS)
{
	int id;
	bool toggle;
	if (bsData.Read(id) && bsData.Read(toggle))
	{
		if (vBox[id])
			vBox[id]->Show(toggle);
	}
}

RPC_CALLBACK CRPCCallback::DestroyBox(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		if (vBox[id])
		{	
			delete vBox[id];
			vBox[id] = nullptr;
		}
	}
}

RPC_CALLBACK CRPCCallback::DestroySprite(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		if (vSprite[id])
		{
			if (vSprite[id]->isInitialized())
			{
				delete vSprite[id];
				vSprite[id] = nullptr;
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::ResizeSprite(RPC_ARGS)
{
	int id;
	float w, h;
	if	(
		bsData.Read(id) && 
		bsData.Read(w) && 
		bsData.Read(h)
		)
	{
		if (vSprite[id])
		{
			if (vSprite[id]->isInitialized())
			{
				vSprite[id]->Resize(w, h);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::MoveSprite(RPC_ARGS)
{
	int id;
	float x, y;
	if (
		bsData.Read(id) &&
		bsData.Read(x) &&
		bsData.Read(y)
		)
	{
		if (vSprite[id])
		{
			if (vSprite[id]->isInitialized())
			{
				vSprite[id]->Move(x, y);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::RotateSprite(RPC_ARGS)
{
	int id;
	float angle;
	if (
		bsData.Read(id) &&
		bsData.Read(angle)
		)
	{
		if (vSprite[id])
		{
			if (vSprite[id]->isInitialized())
			{
				vSprite[id]->Rotate(angle);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::ShowSprite(RPC_ARGS)
{
	int id;
	bool toggle;
	if (bsData.Read(id) && bsData.Read(toggle))
	{
		if (vSprite[id])
		{
			if (vSprite[id]->isInitialized())
			{
				vSprite[id]->Show(toggle);
			}
		}
	}
}

RPC_CALLBACK CRPCCallback::SetClockStringFormat(RPC_ARGS)
{
	auto text = std::make_shared<char>(10);

	if (bsData.Read(text.get()))
	{
		std::replace(text.get(), text.get() + strlen(text.get()), '#', '%');
		CGame::SetClockStringFormat(text.get());
	}
}

RPC_CALLBACK CRPCCallback::SetMoneyStringFormat(RPC_ARGS)
{
	auto text = std::make_shared<char>(6);

	if (bsData.Read(text.get()))
	{
		std::replace(text.get(), text.get() + strlen(text.get()), '#', '%');
		CGame::SetMoneyStringFormat(text.get());
	}
}

RPC_CALLBACK CRPCCallback::CreateText(RPC_ARGS)
{
	int id;
	float
		x, y,
		w, h
		;
	auto text = std::make_shared<CHAR>(256);
	auto font = std::make_shared<char>(16);

	if (
		bsData.Read(id) &&
		bsData.Read(x) &&
		bsData.Read(y) &&
		bsData.Read(w) &&
		bsData.Read(h) &&
		bsData.Read(text.get()) &&
		bsData.Read(font.get())
		)
	{
		Text* d3dText = new Text;
		d3dText->Create(CGraphics::GetDevice(),
			x, y, h, w, D3DCOLOR_ARGB(255, 000, 255, 000), text, DT_LEFT | DT_NOCLIP, font);
		if (id > vText.size()) vText.resize(id + 100);
		vText[id] = d3dText;
	}
}

RPC_CALLBACK CRPCCallback::SetTextText(RPC_ARGS)
{
	int id;
	auto text = std::make_shared<CHAR>(256);
	if (bsData.Read(id) && bsData.Read(text.get()))
	{
		if (vText[id])
		{
			vText[id]->SetText(text);
		}
	}
}

RPC_CALLBACK CRPCCallback::DestroyText(RPC_ARGS)
{
	int id;
	if (bsData.Read(id))
	{
		if (vText[id])
		{
			delete vText[id];
			vText[id] = nullptr;
		}
	}
	//SHA PRIDU KOROCH
}

RPC_CALLBACK CRPCCallback::ShowText(RPC_ARGS)
{
	int id;
	bool toggle;
	if (bsData.Read(id) && bsData.Read(toggle))
	{
		if (vText[id])
			vText[id]->Show(toggle);
	}
}