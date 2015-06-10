#include <RakNet/BitStream.h>

#include <SAMP+/Utility.h>
#include <SAMP+/CRPC.h>
#include <SAMP+/svr/Plugin.h>
#include <SAMP+/svr/Callback.h>

#include <sampgdk.h>
#include <queue>

std::deque<int> boxPool;
std::deque<int> buttonPool;
std::deque<int> spritePool;
std::deque<int> textPool;
std::deque<int> canvasPool;

cell AMX_NATIVE_CALL CallbackProc(AMX* pAmx, cell* pParams)
{
	return Callback::Process(pAmx, (Callback::eCallbackType)pParams[1], &pParams[2]);
}

cell AMX_NATIVE_CALL ToggleHUDComponentForPlayerProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // component
	bitStream.Write(!!pParams[3]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_HUD_COMPONENT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerCursor(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	Network::GetPlayerFromPlayerid(pParams[1])->ToggleCursor(!!pParams[2]);
	Network::PlayerSendRPC(eRPC::TOGGLE_PLAYER_CURSOR, pParams[1], &bitStream);
	return !!pParams[2];
}

cell AMX_NATIVE_CALL GetCursorState(AMX* pAmx, cell* pParams)
{
	return Network::GetPlayerFromPlayerid(pParams[1])->IsCursorEnabled();
}

cell AMX_NATIVE_CALL SetPlayerHUDComponentColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // colour component
	bitStream.WriteCasted<unsigned int, cell>(pParams[3]); // colour

	return Network::PlayerSendRPC(eRPC::SET_HUD_COMPONENT_COLOUR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetRadioStationForPlayerProc(AMX* pAmx, cell* pParams)
{
	if (IsPlayerInAnyVehicle(pParams[1]))
	{
		RakNet::BitStream bitStream;
		bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // radio station id

		return Network::PlayerSendRPC(eRPC::SET_RADIO_STATION, pParams[1], &bitStream);
	}

	return 1;
}

cell AMX_NATIVE_CALL GetRadioStation(AMX* pAmx, cell* pParams)
{
	if (IsPlayerInAnyVehicle(pParams[1]))
	{
		return Network::GetPlayerFromPlayerid(pParams[1])->GetRadio();
	}
	return 0;
}

cell AMX_NATIVE_CALL SetWaveHeightForPlayerProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2])); // wave height

	return Network::PlayerSendRPC(eRPC::SET_WAVE_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePauseMenuAbilityProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_PAUSE_MENU, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL ToggleInfiniteOxygen(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_INFINITE_OXYGEN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerWaterBuoyancy(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_WATER_BUOYANCY, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL ToggleUnderwaterEffect(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_UNDERWATER_EFFECT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL ToggleNightVision(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_NIGHTVISION, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPickupSize(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2])); // size

	Network::GetPlayerFromPlayerid(pParams[1])->SetPickupSize(amx_ctof(pParams[2]));
	Network::PlayerSendRPC(eRPC::SET_PICKUP_SIZE, pParams[1], &bitStream);
	return pParams[2];
}

cell AMX_NATIVE_CALL GetPickupSize(AMX* pAmx, cell* pParams)
{
	float f = Network::GetPlayerFromPlayerid(pParams[1])->GetPickupSize();
	return amx_ftoc(f);
}

cell AMX_NATIVE_CALL SetPlayerFlameColor(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[2]); // color_1
	bitStream.Write(pParams[3]); // color_2

	Network::GetPlayerFromPlayerid(pParams[1])->SetFlameColor(pParams[2], pParams[3]);
	return Network::PlayerSendRPC(eRPC::SET_FLAME_COLOR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerFlameColor(AMX* pAmx, cell* pParams)
{
	cell *cellptr;
	amx_GetAddr(pAmx, pParams[2], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetFlameColor_1();

	amx_GetAddr(pAmx, pParams[3], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetFlameColor_2();

	return 1;
}

cell AMX_NATIVE_CALL ToggleThermalVision(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_THERMALVISION, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL IsPlayerInPauseMenuProc(AMX* pAmx, cell* pParams)
{
	return Network::GetPlayerFromPlayerid(pParams[1])->IsInPauseMenu();
}

cell AMX_NATIVE_CALL GetPlayerResolutionProc(AMX* pAmx, cell* pParams)
{	
	cell *cellptr;
	amx_GetAddr(pAmx, pParams[2], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetResolutionX(); 

	amx_GetAddr(pAmx, pParams[3], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetResolutionY();

	return 1;
}

cell AMX_NATIVE_CALL SetWaveHeightForAllProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[1])); // wave height

	Network::BroadcastRPC(eRPC::SET_WAVE_HEIGHT, &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetRocketDelayProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[1]);

	Network::BroadcastRPC(eRPC::SET_ROCKET_DELAY, &bitStream);
	return pParams[1];
}

cell AMX_NATIVE_CALL SetClockStringFormat(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	char *format;
	amx_StrParam(pAmx, pParams[2], format); // format

	bitStream.Write(format);

	return Network::PlayerSendRPC(eRPC::SET_CLOCK_STRING_FORMAT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetMoneyStringFormat(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	char *format;
	amx_StrParam(pAmx, pParams[2], format); // format

	bitStream.Write(format);

	return Network::PlayerSendRPC(eRPC::SET_MONEY_STRING_FORMAT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlaneRadarColor(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[2]); // r
	bitStream.Write(pParams[3]); // g
	bitStream.Write(pParams[4]); // b
	bitStream.Write(pParams[5]); // a

	Network::GetPlayerFromPlayerid(pParams[1])->SetPlaneRadarColor(pParams[2], pParams[3], pParams[4], pParams[5]);
	return Network::PlayerSendRPC(eRPC::SET_PLANE_RADAR_COLOR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlaneRadarColor(AMX* pAmx, cell* pParams)
{
	cell *cellptr;
	amx_GetAddr(pAmx, pParams[2], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetPlaneRadarColor_R();

	amx_GetAddr(pAmx, pParams[3], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetPlaneRadarColor_G();

	amx_GetAddr(pAmx, pParams[4], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetPlaneRadarColor_B();

	amx_GetAddr(pAmx, pParams[5], &cellptr);
	*cellptr = Network::GetPlayerFromPlayerid(pParams[1])->GetPlaneRadarColor_A();

	return 1;
}

cell AMX_NATIVE_CALL SetPlayerCheckpointExProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write<float>(amx_ctof(pParams[2])); //pos x
	bitStream.Write<float>(amx_ctof(pParams[3])); //pos y
	bitStream.Write<float>(amx_ctof(pParams[4])); //pos z
	bitStream.Write<float>(amx_ctof(pParams[5])); //size
	bitStream.WriteCasted<unsigned int, cell>(pParams[6]); //colour
	bitStream.WriteCasted<unsigned short, cell>(pParams[7]); //period
	bitStream.Write<float>(amx_ctof(pParams[8])); //pulse
	bitStream.WriteCasted<short, cell>(pParams[9]); //rot_rate
	bitStream.Write(!!pParams[10]); //check_z

	DisablePlayerCheckpoint(pParams[1]);

	Network::PlayerSendRPC(eRPC::SET_CHECKPOINT_EX, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerRaceCheckpointExProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); //type
	bitStream.Write<float>(amx_ctof(pParams[3])); //pos x
	bitStream.Write<float>(amx_ctof(pParams[4])); //pos y
	bitStream.Write<float>(amx_ctof(pParams[5])); //pos z
	bitStream.Write<float>(amx_ctof(pParams[6])); //point x
	bitStream.Write<float>(amx_ctof(pParams[7])); //point y
	bitStream.Write<float>(amx_ctof(pParams[8])); //point z
	bitStream.Write<float>(amx_ctof(pParams[9])); //size
	bitStream.WriteCasted<unsigned int, cell>(pParams[10]); //colour
	bitStream.WriteCasted<unsigned short, cell>(pParams[11]); //period
	bitStream.Write<float>(amx_ctof(pParams[12])); //pulse
	bitStream.WriteCasted<short, cell>(pParams[13]); //rot_rate

	DisablePlayerRaceCheckpoint(pParams[1]);

	Network::PlayerSendRPC(eRPC::SET_RACE_CHECKPOINT_EX, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned long, cell>(pParams[2]); // checkpoint colours
	/*bitStream.WriteCasted<unsigned long, cell>(pParams[3]);
	bitStream.WriteCasted<unsigned long, cell>(pParams[4]);*/

	Network::PlayerSendRPC(eRPC::SET_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetPlayerRaceCheckpointColourProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned int, cell>(pParams[2]); // checkpoint colour

	Network::PlayerSendRPC(eRPC::SET_RACE_CHECKPOINT_COLOUR, pParams[1], &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL TogglePlayerActionProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // action
	bitStream.Write(!!pParams[3]); // toggle

	return Network::PlayerSendRPC(eRPC::TOGGLE_ACTION, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerClipAmmoProc(AMX* pAmx, cell* pParams) // tips off SA-MP's anti-cheat, wouldn't recomend using... yet...
{
	RakNet::BitStream bitStream;
	bitStream.WriteCasted<unsigned char, cell>(pParams[2]); // bSlotId
	bitStream.WriteCasted<DWORD, cell>(pParams[3]); // dwNewAmmo

	return Network::PlayerSendRPC(eRPC::SET_CLIP_AMMO, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerNoReloadProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); // bToggle
	
	return Network::PlayerSendRPC(eRPC::SET_NO_RELOAD, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL CreateBox(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	int nId = boxPool.front();
	bitStream.Write(nId);//id
	if (boxPool.size() == 1)
	for (int i = nId; i < nId + 100; i++) boxPool.push_back(i);
	boxPool.pop_front();

	bitStream.Write(amx_ctof(params[2]));//x
	bitStream.Write(amx_ctof(params[3]));//y
	bitStream.Write(amx_ctof(params[4]));//w
	bitStream.Write(amx_ctof(params[5]));//h
	char* res;
	amx_StrParam(amx, params[6], res);//res
	bitStream.Write(res);
	bitStream.Write(params[7]);//a
	bitStream.Write(params[8]);//r
	bitStream.Write(params[9]);//g
	bitStream.Write(params[10]);//b
	if (Network::isConnected(params[1]))
		Network::PlayerSendRPC(eRPC::CREATE_BOX, params[1], &bitStream);
	return nId;
}

cell AMX_NATIVE_CALL DestroyBox(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < boxPool.size(); i++)
	{
		if (boxPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	boxPool.push_front(params[2]);
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::DESTROY_BOX, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL CreateSprite(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	int nId = spritePool.front();
	bitStream.Write(nId);//id
	if (spritePool.size() == 1)
	for (int i = nId; i < nId + 100; i++) spritePool.push_back(i);
	spritePool.pop_front();

	bitStream.Write(amx_ctof(params[2]));//x
	bitStream.Write(amx_ctof(params[3]));//y
	bitStream.Write(amx_ctof(params[4]));//w
	bitStream.Write(amx_ctof(params[5]));//h
	char* res;
	amx_StrParam(amx, params[6], res);//res
	bitStream.Write(res);
	if (Network::isConnected(params[1]))
		Network::PlayerSendRPC(eRPC::CREATE_SPRITE, params[1], &bitStream);
	return nId;
}

cell AMX_NATIVE_CALL DestroySprite(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < spritePool.size(); i++)
	{
		if (spritePool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	spritePool.push_front(params[2]);
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::DESTROY_SPRITE, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL ResizeSprite(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < spritePool.size(); i++)
	{
		if (spritePool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	bitStream.Write(amx_ctof(params[3]));//w
	bitStream.Write(amx_ctof(params[4]));//h
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::RESIZE_SPRITE, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL RotateSprite(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < spritePool.size(); i++)
	{
		if (spritePool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	bitStream.Write(amx_ctof(params[3]));//angle
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::ROTATE_SPRITE, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL MoveSprite(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < spritePool.size(); i++)
	{
		if (spritePool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	bitStream.Write(amx_ctof(params[3]));//x
	bitStream.Write(amx_ctof(params[4]));//y
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::MOVE_SPRITE, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL ShowSprite(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[3]); // bToggle
	for (int i = 0; i < spritePool.size(); i++)
	{
		if (spritePool[i] == pParams[2]) return 0;
	}
	if (Network::isConnected(pParams[1]))
		return Network::PlayerSendRPC(eRPC::SHOW_SPRITE, pParams[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL CreateText(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	int nId = textPool.front();
	bitStream.Write(nId);//id
	if (textPool.size() == 1)
		for (int i = nId; i < nId + 100; i++) textPool.push_back(i);
	textPool.pop_front();
	
	bitStream.Write(amx_ctof(params[2]));//x
	bitStream.Write(amx_ctof(params[3]));//y
	bitStream.Write(amx_ctof(params[4]));//w
	bitStream.Write(amx_ctof(params[5]));//h
	char* text;
	char* font_name;
	amx_StrParam(amx, params[6], text);//text
	amx_StrParam(amx, params[7], font_name);//font
	bitStream.Write(text);
	bitStream.Write(font_name);
	if(Network::isConnected(params[1]))
		Network::PlayerSendRPC(eRPC::CREATE_TEXT, params[1], &bitStream);
	return nId;
}

cell AMX_NATIVE_CALL SetTextText(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < textPool.size(); i++)
	{
		if (textPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id

	if (Network::isConnected(params[1]))
	{
		int len;
		cell *addr = NULL;

		amx_GetAddr(amx, params[3], &addr);
		amx_StrLen(addr, &len);
		LPSTR text = new CHAR[++len];
		amx_GetString(text, addr, 0, len);
		bitStream.Write(text);
		delete[] text;

		return Network::PlayerSendRPC(eRPC::SET_TEXT_TEXT, params[1], &bitStream);
	}

	return false;
}

cell AMX_NATIVE_CALL CreateButton(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	int nId = buttonPool.front();
	bitStream.Write(nId); //id
	if (buttonPool.size() == 1)
		for (int i = nId; i < nId + 100; i++) buttonPool.push_back(i);

	buttonPool.pop_front();
	bitStream.Write(params[2]);

	if (Network::isConnected(params[1]))
		Network::PlayerSendRPC(eRPC::CREATE_BUTTON, params[1], &bitStream);
	return nId;
}

cell AMX_NATIVE_CALL SetSizeButton(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < buttonPool.size(); i++)
	{
		if (buttonPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id
	bitStream.Write(params[3]); //w
	bitStream.Write(params[4]); //h

	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::SET_SIZE_BUTTON, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL SetPosButton(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < buttonPool.size(); i++)
	{
		if (buttonPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id
	bitStream.Write(params[3]); //x
	bitStream.Write(params[4]); //y

	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::SET_POS_BUTTON, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL SetTextButton(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < buttonPool.size(); i++)
	{
		if (buttonPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id

	char* text;
	amx_StrParam(amx, params[3], text); //text
	bitStream.Write(text);

	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::SET_TEXT_BUTTON, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL DestroyButton(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < buttonPool.size(); i++)
	{
		if (buttonPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id

	buttonPool.push_front(params[2]);

	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::DESTROY_BUTTON, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL CreateCanvas(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	int nId = canvasPool.front();
	bitStream.Write(nId); //id
	if (canvasPool.size() == 1)
		for (int i = nId; i < nId + 100; i++) canvasPool.push_back(i);

	canvasPool.pop_front();

	if (Network::isConnected(params[1]))
		Network::PlayerSendRPC(eRPC::CREATE_CANVAS, params[1], &bitStream);

	return nId;
}

cell AMX_NATIVE_CALL SetCanvasSize(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < canvasPool.size(); i++)
	{
		if (canvasPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id
	bitStream.Write(params[3]); //x
	bitStream.Write(params[4]); //w

	if (Network::isConnected(params[1]))
	{
		return Network::PlayerSendRPC(eRPC::SET_SIZE_CANVAS, params[1], &bitStream);
	}
	return false;
}

cell AMX_NATIVE_CALL SetBackColorCanvas(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < canvasPool.size(); i++)
	{
		if (canvasPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id
	bitStream.Write(params[3]); //r
	bitStream.Write(params[4]); //g
	bitStream.Write(params[5]); //b
	bitStream.Write(params[6]); //a

	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::SET_BACK_COLOR_CANVAS, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL DestroyCanvas(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < canvasPool.size(); i++)
	{
		if (canvasPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]); //id
	canvasPool.push_front(params[2]);
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::DESTROY_CANVAS, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL DestroyText(AMX *amx, cell* params)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < textPool.size(); i++)
	{
		if (textPool[i] == params[2]) return 0;
	}
	bitStream.Write(params[2]);//id
	textPool.push_front(params[2]);
	if (Network::isConnected(params[1]))
		return Network::PlayerSendRPC(eRPC::DESTROY_TEXT, params[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL ShowText(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < textPool.size(); i++)
	{
		if (textPool[i] == pParams[2]) return 0;
	}
	bitStream.Write(pParams[2]); // id
	bitStream.Write(!!pParams[3]); // bToggle
	if (Network::isConnected(pParams[1]))
		return Network::PlayerSendRPC(eRPC::SHOW_TEXT, pParams[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL ShowBox(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	for (int i = 0; i < textPool.size(); i++)
	{
		if (textPool[i] == pParams[2]) return 0;
	}
	bitStream.Write(pParams[2]); // id
	bitStream.Write(!!pParams[3]); // bToggle
	if (Network::isConnected(pParams[1]))
		return Network::PlayerSendRPC(eRPC::SHOW_BOX, pParams[1], &bitStream);
	return false;
}

cell AMX_NATIVE_CALL SetPlayerBlurIntensityProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_BLUR_INTENSITY, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerDriveOnWaterProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_DRIVE_ON_WATER, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetGameSpeedProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::BroadcastRPC(eRPC::SET_GAME_SPEED, &bitStream);
	return pParams[2];
}

cell AMX_NATIVE_CALL SetPlayerGameSpeedProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::PlayerSendRPC(eRPC::SET_GAME_SPEED, pParams[1], &bitStream);
	return pParams[2];
}

cell AMX_NATIVE_CALL ToggleQuickReloadForPlayer(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); //toggle

	Network::PlayerSendRPC(eRPC::SET_QUICK_RELOAD, pParams[1], &bitStream);
	return !!pParams[2];
}

cell AMX_NATIVE_CALL ToggleQuickReloadForAll(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]); //toggle

	Network::BroadcastRPC(eRPC::SET_QUICK_RELOAD, &bitStream);
	return !!pParams[2];
}

cell AMX_NATIVE_CALL SetSunColorForPlayer(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[2]); //core_r
	bitStream.Write(pParams[3]); //core_g
	bitStream.Write(pParams[4]); //core_b

	bitStream.Write(pParams[5]); //corona_r
	bitStream.Write(pParams[6]); //corona_g
	bitStream.Write(pParams[7]); //corona_b

	return Network::PlayerSendRPC(eRPC::SET_SUN_COLOR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL ResetSunColorForPlayer(AMX* pAmx, cell* pParams)
{
	return Network::PlayerSendRPC(eRPC::RESET_SUN_COLOR, pParams[1], NULL);
}

cell AMX_NATIVE_CALL ResetSunColorForAll(AMX* pAmx, cell* pParams)
{
	Network::BroadcastRPC(eRPC::RESET_SUN_COLOR, 0);
	return 1;
}


cell AMX_NATIVE_CALL SetSunColorForAll(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(pParams[1]); //core_r
	bitStream.Write(pParams[2]); //core_g
	bitStream.Write(pParams[3]); //core_b

	bitStream.Write(pParams[4]); //corona_r
	bitStream.Write(pParams[5]); //corona_g
	bitStream.Write(pParams[6]); //corona_b

	Network::BroadcastRPC(eRPC::SET_SUN_COLOR, &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL SetWaterColorForPlayer(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2])); //r
	bitStream.Write(amx_ctof(pParams[3])); //g
	bitStream.Write(amx_ctof(pParams[4])); //b
	bitStream.Write(amx_ctof(pParams[5])); //a

	return Network::PlayerSendRPC(eRPC::SET_WATER_COLOR, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL ResetWaterColorForPlayer(AMX* pAmx, cell* pParams)
{
	return Network::PlayerSendRPC(eRPC::RESET_WATER_COLOR, pParams[1], 0);
}

cell AMX_NATIVE_CALL SetWaterColorForAll(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[1])); //r
	bitStream.Write(amx_ctof(pParams[2])); //g
	bitStream.Write(amx_ctof(pParams[3])); //b
	bitStream.Write(amx_ctof(pParams[4])); //a

	Network::BroadcastRPC(eRPC::SET_WATER_COLOR, &bitStream);
	return 1;
}

cell AMX_NATIVE_CALL ResetWaterColorForAll(AMX* pAmx, cell* pParams)
{
	Network::BroadcastRPC(eRPC::RESET_WATER_COLOR, 0);
	return 1;
}

cell AMX_NATIVE_CALL TogglePlayerFrozenProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_PLAYER_FROZEN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPedAnimsProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::SET_PLAYER_ANIMS, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerSwitchReloadProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_SWITCH_RELOAD, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL TogglePlayerInfiniteRunProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	return Network::PlayerSendRPC(eRPC::TOGGLE_INFINITE_RUN, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL SetPlayerAircraftHeightProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::GetPlayerFromPlayerid(pParams[1])->SetAircraftHeight(amx_ctof(pParams[2]));
	return Network::PlayerSendRPC(eRPC::SET_AIRCRAFT_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerAircraftHeightProc(AMX* pAmx, cell* pParams)
{
	float f = Network::GetPlayerFromPlayerid(pParams[1])->GetAircraftHeight();
	return amx_ftoc(f);
}

cell AMX_NATIVE_CALL SetPlayerJetpackHeightProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(amx_ctof(pParams[2]));

	Network::GetPlayerFromPlayerid(pParams[1])->SetJetpackHeight(amx_ctof(pParams[2]));
	return Network::PlayerSendRPC(eRPC::SET_JETPACK_HEIGHT, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerJetpackHeightProc(AMX* pAmx, cell* pParams)
{
	float f = Network::GetPlayerFromPlayerid(pParams[1])->GetJetpackHeight();
	return amx_ftoc(f);
}

cell AMX_NATIVE_CALL TogglePlayerVehicleBlipsProc(AMX* pAmx, cell* pParams)
{
	RakNet::BitStream bitStream;
	bitStream.Write(!!pParams[2]);

	Network::GetPlayerFromPlayerid(pParams[1])->ToggleVehicleBlips(!!pParams[2]);
	return Network::PlayerSendRPC(eRPC::TOGGLE_VEHICLE_BLIPS, pParams[1], &bitStream);
}

cell AMX_NATIVE_CALL GetPlayerVehicleBlipsProc(AMX* pAmx, cell* pParams)
{
	return Network::GetPlayerFromPlayerid(pParams[1])->GetVehicleBlips();
}

cell AMX_NATIVE_CALL IsUsingSAMPPProc(AMX* pAmx, cell* pParams)
{
	return Network::isConnected(pParams[1]);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	Network::Process();
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	Utility::Initialize(ppData);
	Utility::Printf("Loaded");
	for (int i = 0; i < 100; i++)
	{
		boxPool.push_back(i);
		buttonPool.push_back(i);
		textPool.push_back(i);
		spritePool.push_back(i);
		canvasPool.push_back(i);
	}
	SAMPServer::Initialize("server.cfg");
	Network::Initialize(SAMPServer::GetListeningAddress(), SAMPServer::GetListeningPort() + 1, SAMPServer::getMaxPlayers());
	return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	Utility::Printf("Unloaded");
	return sampgdk::Unload();
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SAMPP_ExecuteCallback", CallbackProc },
	{ "ToggleHUDComponentForPlayer", ToggleHUDComponentForPlayerProc },
	{ "SetRadioStationForPlayer", SetRadioStationForPlayerProc },
	{ "SetWaveHeightForPlayer", SetWaveHeightForPlayerProc },
	{ "SetWaveHeightForAll", SetWaveHeightForAllProc },
	{ "TogglePauseMenuAbility", TogglePauseMenuAbilityProc },
	{ "IsPlayerInPauseMenu", IsPlayerInPauseMenuProc },
	{ "SetPlayerHUDComponentColour", SetPlayerHUDComponentColourProc },
	{ "SetPlayerCheckpointEx", SetPlayerCheckpointExProc },
	{ "SetPlayerRaceCheckpointEx", SetPlayerRaceCheckpointExProc },
	{ "SetPlayerCheckpointColour", SetPlayerCheckpointColourProc },
	{ "SetPlayerRaceCheckpointColour", SetPlayerRaceCheckpointColourProc },
	{ "TogglePlayerAction", TogglePlayerActionProc },
	//{ "SetPlayerAmmoInClip", SetPlayerClipAmmoProc }, // tips off SA-MP's anti-cheat, wouldn't recomend using... yet...
	{ "SetPlayerNoReload", SetPlayerNoReloadProc },
	{ "GetPlayerResolution", GetPlayerResolutionProc },
	{ "IsUsingSAMPP", IsUsingSAMPPProc },
	{ "SetPlayerBlurIntensity", SetPlayerBlurIntensityProc },
	{ "TogglePlayerDriveOnWater", TogglePlayerDriveOnWaterProc },
	{ "SetGameSpeedForPlayer", SetPlayerGameSpeedProc },
	{ "SetGameSpeedForAll", SetGameSpeedProc },
	{ "TogglePlayerFrozen", TogglePlayerFrozenProc },
	{ "SetPlayerPedAnims", SetPedAnimsProc },
	{ "TogglePlayerSwitchReload", TogglePlayerSwitchReloadProc },
	{ "TogglePlayerInfiniteRun", TogglePlayerInfiniteRunProc },
	{ "SetPlayerAircraftHeight", SetPlayerAircraftHeightProc },
	{ "GetPlayerAircraftHeight", GetPlayerAircraftHeightProc },
	{ "SetPlayerJetpackHeight", SetPlayerJetpackHeightProc },
	{ "GetPlayerJetpackHeight", GetPlayerJetpackHeightProc },
	{ "TogglePlayerVehicleBlips", TogglePlayerVehicleBlipsProc },
	{ "GetPlayerVehicleBlips", GetPlayerVehicleBlipsProc },
	{ "GetPlayerRadioStation", GetRadioStation },
	{ "TogglePlayerInfiniteOxygen", ToggleInfiniteOxygen },
	{ "ToggleWaterBuoyancy", TogglePlayerWaterBuoyancy },
	{ "ToggleUnderwaterEffect", ToggleUnderwaterEffect },
	{ "ToggleNightVision", ToggleNightVision },
	{ "ToggleThermalVision", ToggleThermalVision },

	{ "SetSunColorForPlayer", SetSunColorForPlayer },
	{ "SetSunColorForAll", SetSunColorForAll },
	{ "ResetSunColorForPlayer", ResetSunColorForPlayer },
	{ "ResetSunColorForAll", ResetSunColorForAll },
	{ "ToggleQuickReloadForPlayer", ToggleQuickReloadForPlayer },
	{ "ToggleQuickReloadForAll", ToggleQuickReloadForAll },
	{ "SetWaterColorForPlayer", SetWaterColorForPlayer },
	{ "SetWaterColorForAll", SetWaterColorForAll },
	{ "ResetWaterColorForPlayer", ResetWaterColorForPlayer },
	{ "ResetWaterColorForAll", ResetWaterColorForAll },
	{ "SetRocketDelay", SetRocketDelayProc },
	{ "SetPickupSize", SetPickupSize },
	{ "GetPickupSize", GetPickupSize },
	{ "TogglePlayerCursor", TogglePlayerCursor },
	{ "GetCursorState", GetCursorState },
	{ "SetPlayerFlameColor", SetPlayerFlameColor },
	{ "GetPlayerFlameColor", GetPlayerFlameColor },
	{ "SetPlaneRadarColor", SetPlaneRadarColor },
	{ "GetPlaneRadarColor", GetPlaneRadarColor },
	{ "SetClockStringFormat", SetClockStringFormat },
	{ "SetMoneyStringFormat", SetMoneyStringFormat },

	{ "CreateCanvas", CreateCanvas },
	{ "SetCanvasSize", SetCanvasSize },
	{ "SetBackColorCanvas", SetBackColorCanvas },
	{ "DestroyCanvas", DestroyCanvas },

	{ "CreateButton", CreateButton },
	{ "SetPosButton", SetPosButton },
	{ "SetTextButton", SetTextButton },
	{ "SetSizeButton", SetSizeButton },
	{ "DestroyButton", DestroyButton },

	{ "CreateD3DText", CreateText },
	{ "SetD3DText", SetTextText },
	{ "DestroyD3DText", DestroyText },
	{ "ShowD3DText", ShowText },

	{ "CreateD3DSprite", CreateSprite },
	{ "DestroyD3DSprite", DestroySprite },
	{ "ShowD3DSprite", ShowSprite },
	{ "ResizeD3DSprite", ResizeSprite },
	{ "MoveD3DSprite", MoveSprite },
	{ "RotateD3DSprite", RotateSprite },

	{ "CreateD3DBox", CreateBox },
	{ "ShowD3DBox", ShowBox },
	{ "DestroyD3DBox", DestroyBox },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *pAmx)
{
	Callback::GetAMXList().push_back(pAmx);
	return amx_Register(pAmx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *pAmx)
{
	Callback::GetAMXList().remove(pAmx);
	return AMX_ERR_NONE;
}
