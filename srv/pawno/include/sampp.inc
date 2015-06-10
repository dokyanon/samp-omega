
#define HUD_COMPONENT_ALL 0
#define HUD_COMPONENT_AMMO 1
#define HUD_COMPONENT_WEAPON 2
#define HUD_COMPONENT_HEALTH 3
#define HUD_COMPONENT_BREATH 4
#define HUD_COMPONENT_ARMOUR 5
#define HUD_COMPONENT_MINIMAP 6
#define HUD_COMPONENT_CROSSHAIR 7
#define HUD_COMPONENT_MONEY 8

#define HUD_COLOUR_MONEY_POSITIVE 0
#define HUD_COLOUR_MONEY_NEGATIVE 1
#define HUD_COLOUR_ARMOUR 2
#define HUD_COLOUR_HEALTH 3
#define HUD_COLOUR_BREATH 4
#define HUD_COLOUR_AMMO 5
#define HUD_COLOUR_WANTED_LEVEL 6
#define HUD_COLOUR_RADIO_TUNED 7
#define HUD_COLOUR_RADIO_UNTUNED 8

#define RADIO_PLAYBACKFM 1
#define RADIO_KROSE 2
#define RADIO_KDST 3
#define RADIO_BOUNCEFM 4
#define RADIO_SFUR 5
#define RADIO_LOSSANTOS 6
#define RADIO_RADIOX 7
#define RADIO_CSR 8
#define RADIO_KJAHWEST 9
#define RADIO_MASTERSOUNDS 10
#define RADIO_WCTR 11
#define RADIO_UTP 12
#define RADIO_OFF 13

#define PAUSE_ID_STATS 0
#define PAUSE_ID_STARTGAME 1
#define PAUSE_ID_BRIEF 2
#define PAUSE_ID_AUDIOSETTINGS 3
#define PAUSE_ID_DISPLAYSETTINGS 4
#define PAUSE_ID_MAP 5
#define PAUSE_ID_DEFAULTSETTINGS 23
#define PAUSE_ID_AUDIODEFAULTSETTINGS 24
#define PAUSE_ID_CONTROLLERDEFAULTSETTINGS 25
#define PAUSE_ID_USERTRACKOPTIONS 26
#define PAUSE_ID_LANGUAGE 28
#define PAUSE_ID_OPTIONS 33
#define PAUSE_ID_QUITGAME 35
#define PAUSE_ID_CONTROLLERSETUP 36
#define PAUSE_ID_REDEFINECONTROLS 37
#define PAUSE_ID_FOOTVEHICLECONTROLS 38
#define PAUSE_ID_MOUSESETTINGS 39
#define PAUSE_ID_JOYPADSETTINGS 40
#define PAUSE_ID_MAIN 41

#define PLAYER_ACTION_ALL 0
#define PLAYER_ACTION_SPRINT 1
#define PLAYER_ACTION_ENTER_CAR 2
#define PLAYER_ACTION_CROUCH 3
#define PLAYER_ACTION_FIRE_WEAPON 4
#define PLAYER_ACTION_UNKNOWN 5
#define PLAYER_ACTION_SWITCH_WEAPON 6
#define PLAYER_ACTION_JUMP 7

#define STUNT_TYPE_TWO_WHEELS 247
#define STUNT_TYPE_INSANE 173
#define STUNT_TYPE_WHEELIE 117
#define STUNT_TYPE_STOPPIE 233

#define DEFAULT_BLUR_INTENSITY 36
#define NO_BLUR_INTENSITY 0

#define DEFAULT_AIRCRAFT_HEIGHT 800
#define DEFAULT_JETPACK_HEIGHT 100

#define MOUSE_LEFT_CLICK 0
#define MOUSE_RIGHT_CLICK 1
#define MOUSE_MIDDLE_CLICK 2

#define DEFAULT_PICKUP_SIZE 1.0

native SetPlayerCheckpointEx(playerid, Float:x, Float:y, Float:z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0, bool:check_z = true);
native SetPlayerCheckpointColour(playerid, colour);

native SetPlayerRaceCheckpointEx(playerid, type, Float:x, Float:y, Float:z, Float:point_x, Float:point_y, Float:point_z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0);
native SetPlayerRaceCheckpointColour(playerid, colour);

native ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle);
native SetRadioStationForPlayer(playerid, stationid);
native SetPlayerGameSpeed(playerid, Float:speed);
native SetWaveHeightForPlayer(playerid, Float:height);
native SetWaveHeightForAll(Float:height);
native TogglePauseMenuAbility(playerid, bool:toggle);
native IsPlayerInPauseMenu(playerid);
native SetPlayerHUDComponentColour(playerid, componentid, colour);
native TogglePlayerAction(playerid, actionid, bool:toggle);
native SetPlayerBlurIntensity(playerid, intensity);
native TogglePlayerDriveOnWater(playerid, bool:toggle);
native TogglePlayerFrozen(playerid, bool:toggle);
native SetPlayerPedAnims(playerid, bool:toggle);
native TogglePlayerSwitchReload(playerid, bool:toggle);
native bool:IsUsingSAMPP(playerid);
native GetPlayerResolution(playerid, &X, &Y);
native SetPlayerNoReload(playerid, bool:toggle);
native TogglePlayerInfiniteRun(playerid, bool:toggle);
native SetPlayerAircraftHeight(playerid, Float:height);
native Float:GetPlayerAircraftHeight(playerid);
native SetPlayerJetpackHeight(playerid, Float:height);
native Float:GetPlayerJetpackHeight(playerid);
native TogglePlayerVehicleBlips(playerid, bool:toggle);
native GetPlayerVehicleBlips(playerid);
native GetPlayerRadioStation(playerid);
native TogglePlayerInfiniteOxygen(playerid, bool:toggle);
native ToggleWaterBuoyancy(playerid, bool:toggle);
native ToggleUnderwaterEffect(playerid, bool:toggle);
native ToggleNightVision(playerid, bool:toggle);
native ToggleThermalVision(playerid, bool:toggle);
native SAMPP_ExecuteCallback(type, {Float,_}:...);

/*by Пельмень*/
native SetWaterColorForPlayer(playerid, Float:r, Float:g, Float:b, Float:a);
native SetWaterColorForAll(Float:r, Float:g, Float:b, Float:a);
native ResetWaterColorForPlayer(playerid);
native ResetWaterColorForAll();
native ToggleQuickReloadForPlayer(playerid, bool:toggle); //returned toggle
native ToggleQuickReloadForAll(bool:toggle); //returned toggle
native SetSunColorForPlayer(playerid, core_r, core_g, core_b, corona_r, corona_g, corona_b);
native SetSunColorForAll(core_r, core_g, core_b, corona_r, corona_g, corona_b);
native ResetSunColorForPlayer(playerid);
native ResetSunColorForAll();
native SetGameSpeedForPlayer(playerid, Float:speed); //returned speed
native SetGameSpeedForAll(Float:speed); //returned speed
native SetRocketDelay(delay); //returned delay
native SetPickupSize(playerid, Float:size); //returned size
native Float:GetPickupSize(playerid);
native TogglePlayerCursor (playerid, bool:toggle); //returned toggle
native bool:GetCursorState(playerid);
native SetPlayerFlameColor(playerid, color_1, color_2);
native GetPlayerFlameColor(playerid, &color_1, &color_2);
native SetPlaneRadarColor (playerid, r, g, b, a);
native GetPlaneRadarColor (playerid, &r, &g, &b, &a);
native SetClockStringFormat(playerid, format[]); //format len !> 10
/*
	Default: %02d:%02d
	Prints like: 14:39 or 09:04

	Changed To: %02d-%02i
	Prints like: 14-39 or 09-04

	Changed To: %2i:%02d
	Prints like: 14:39 or 9:04

	Changed To: %2i:%2i
	Prints like: 14:39 or 9:4
*/

native SetMoneyStringFormat(playerid, format[]); //format len !> 6
/*
	if money < 0
	{
		-$%07d
	}
	
	Default: $%08d
	Prints like: $00000000

	Changed To: R%08d
	Prints like: R00000000
*/

//native GetPlayerFPS(playerid);

native CreateD3DText (playerid, Float:x, Float:y, Float:w, Float:h, text[], font[]);
native SetD3DText (playerid, textid, text[]);
native ShowD3DText (playerid, id, bool:toggle);
native DestroyD3DText (playerid, id);

native CreateD3DBox (playerid, Float:x, Float:y, Float:w, Float:h, res[32], a, r, g, b);
native ShowD3DBox (playerid, id, bool:toggle);
native DestroyD3DBox (playerid, id);

native CreateD3DSprite (playerid, Float:x, Float:y, Float:w, Float:h, res[32]);
native DestroyD3DSprite (playerid, id);
native ResizeD3DSprite (playerid, id, Float:w, Float:h);
native MoveD3DSprite (playerid, id, Float:x, Float:y);
native RotateD3DSprite (playerid, id, Float:angle);
native ShowD3DSprite (playerid, id, bool:toggle);

/*Unstable*/
native CreateButton(playerid, canvas);
native SetPosButton(playerid, id, x, y);
native SetTextButton(playerid, id, text[]);
native SetSizeButton(playerid, id, w, h);
native DestroyButton(playerid, id);

native CreateCanvas (playerid);
native SetBackColorCanvas (playerid, id, r, g, b, a);
native SetCanvasSize (playerid, id, w, h);
native DestroyCanvas (playerid, id);
/*end*/

forward OnPlayerOpenPauseMenu(playerid);
forward OnPlayerClosePauseMenu(playerid);
forward OnPlayerEnterPauseSubmenu(playerid, from, to);
forward OnDriverDriveByShot(playerid);
forward OnPlayerStunt(playerid, stuntid, money, details[]);
forward OnPlayerResolutionChange(playerid, X, Y);
forward OnPlayerSAMPPConnect(address[], port);
forward OnPlayerSAMPPJoin(playerid, bool:has_plugin);
forward OnPlayerClick(playerid, type, X, Y);
forward OnPlayerKeyDown(playerid, key);
forward OnPlayerChangeRadioStation(playerid, stationid, vehicleid);
forward OnPlayerDrinkSprunk(playerid);

public OnPlayerConnect(playerid)
{
	SAMPP_ExecuteCallback(0, playerid);

#if defined SAMPP_OnPlayerConnect
	return SAMPP_OnPlayerConnect(playerid);
#else
	return 1;
#endif
}

#if defined SAMPP_OnPlayerConnect
	forward SAMPP_OnPlayerConnect(playerid);
#endif
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAMPP_OnPlayerConnect

public OnPlayerDisconnect(playerid, reason)
{
	SAMPP_ExecuteCallback(1, playerid, reason);

#if defined SAMPP_OnPlayerDisconnect
	return SAMPP_OnPlayerDisconnect(playerid, reason);
#else
	return 1;
#endif
}

#if defined SAMPP_OnPlayerDisconnect
	forward SAMPP_OnPlayerDisconnect(playerid, reason);
#endif
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SAMPP_OnPlayerDisconnect
