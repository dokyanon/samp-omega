#pragma once

#include <SAMP+/CRPC.h>
#include <SAMP+/client/Client.h>

class CRPCCallback
{
public:
	static void Initialize();

	static RPC_CALLBACK ToggleHUDComponent(RPC_ARGS);
	static RPC_CALLBACK SetRadioStation(RPC_ARGS);
	static RPC_CALLBACK SetWaveHeight(RPC_ARGS);
	static RPC_CALLBACK TogglePauseMenu(RPC_ARGS);
	static RPC_CALLBACK SetHUDComponentColour(RPC_ARGS);
	static RPC_CALLBACK SetPlayerCheckpointEx(RPC_ARGS);
	static RPC_CALLBACK SetPlayerRaceCheckpointEx(RPC_ARGS);
	static RPC_CALLBACK SetCheckpointColour(RPC_ARGS);
	static RPC_CALLBACK SetRaceCheckpointColour(RPC_ARGS);
	static RPC_CALLBACK ToggleAction(RPC_ARGS);
	static RPC_CALLBACK SetAmmoInClip(RPC_ARGS);
	static RPC_CALLBACK SetNoReload(RPC_ARGS);
	static RPC_CALLBACK ToggleInfiniteRun(RPC_ARGS);
	static RPC_CALLBACK DriveOnWater(RPC_ARGS);
	static RPC_CALLBACK SetBlur(RPC_ARGS);
	static RPC_CALLBACK SetSpeed(RPC_ARGS);
	static RPC_CALLBACK SetFrozen(RPC_ARGS);
	static RPC_CALLBACK SetAnims(RPC_ARGS);
	static RPC_CALLBACK ToggleSwitchReload(RPC_ARGS);
	static RPC_CALLBACK SetJetpackHeight(RPC_ARGS);
	static RPC_CALLBACK SetAircraftHeight(RPC_ARGS);
	static RPC_CALLBACK ToggleVehicleBlips(RPC_ARGS);
	static RPC_CALLBACK ToggleInfiniteOxygen(RPC_ARGS);
	static RPC_CALLBACK ToggleWaterBuoyancy(RPC_ARGS);
	static RPC_CALLBACK ToggleUnderwaterEffect(RPC_ARGS);
	static RPC_CALLBACK ToggleNightVision(RPC_ARGS);
	static RPC_CALLBACK ToggleThermalVision(RPC_ARGS);

	static RPC_CALLBACK SetQuickReload(RPC_ARGS);
	static RPC_CALLBACK SetWaterColor(RPC_ARGS);
	static RPC_CALLBACK SetSunColor(RPC_ARGS);
	static RPC_CALLBACK ResetSunColor(RPC_ARGS);
	static RPC_CALLBACK ResetWaterColor(RPC_ARGS);
	static RPC_CALLBACK SetClockStringFormat(RPC_ARGS);
	static RPC_CALLBACK SetMoneyStringFormat(RPC_ARGS);
	static RPC_CALLBACK SetPlaneRadarColor(RPC_ARGS);
	static RPC_CALLBACK SetPickupSize(RPC_ARGS);
	static RPC_CALLBACK SetFlameColor(RPC_ARGS);
	static RPC_CALLBACK SetRocketDelay(RPC_ARGS);

	static RPC_CALLBACK CreateText(RPC_ARGS);
	static RPC_CALLBACK SetTextText(RPC_ARGS);
	static RPC_CALLBACK DestroyText(RPC_ARGS);
	static RPC_CALLBACK ShowText(RPC_ARGS);

	static RPC_CALLBACK CreateSprite(RPC_ARGS);
	static RPC_CALLBACK DestroySprite(RPC_ARGS);
	static RPC_CALLBACK ResizeSprite(RPC_ARGS);
	static RPC_CALLBACK MoveSprite(RPC_ARGS);
	static RPC_CALLBACK RotateSprite(RPC_ARGS);
	static RPC_CALLBACK ShowSprite(RPC_ARGS);

	static RPC_CALLBACK CreateBox(RPC_ARGS);
	static RPC_CALLBACK ShowBox(RPC_ARGS);
	static RPC_CALLBACK DestroyBox(RPC_ARGS);

	static RPC_CALLBACK CreateButton(RPC_ARGS);
	static RPC_CALLBACK SetSizeButton(RPC_ARGS);
	static RPC_CALLBACK SetPosButton(RPC_ARGS);
	static RPC_CALLBACK SetTextButton(RPC_ARGS);
	static RPC_CALLBACK DestroyButton(RPC_ARGS);

	static RPC_CALLBACK TogglePlayerCursor(RPC_ARGS);

	static RPC_CALLBACK CreateCanvas(RPC_ARGS);
	static RPC_CALLBACK SetSizeCanvas(RPC_ARGS);
	static RPC_CALLBACK SetBackColorCanvas(RPC_ARGS);
	static RPC_CALLBACK DestroyCanvas(RPC_ARGS);

private:

};