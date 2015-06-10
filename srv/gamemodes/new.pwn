#include <a_samp>
#include <sampp>
#include <dc_cmd>
#include <sscanf2>

#define VK_KEY_A	0x41
#define VK_KEY_B	0x42
#define VK_KEY_C	0x43
#define VK_KEY_D	0x44
#define VK_KEY_E	0x45
#define VK_KEY_F	0x46
#define VK_KEY_G	0x47
#define VK_KEY_H	0x48
#define VK_KEY_I	0x49
#define VK_KEY_J	0x4A
#define VK_KEY_K	0x4B
#define VK_KEY_L	0x4C
#define VK_KEY_M	0x4D
#define VK_KEY_N	0x4E
#define VK_KEY_O	0x4F
#define VK_KEY_P	0x50
#define VK_KEY_Q	0x51
#define VK_KEY_R	0x52
#define VK_KEY_S	0x53
#define VK_KEY_T	0x54
#define VK_KEY_U	0x55
#define VK_KEY_V	0x56
#define VK_KEY_W	0x57
#define VK_KEY_X	0x58
#define VK_KEY_Y	0x59
#define VK_KEY_Z	0x5A

#define VK_BACKSPACE 0x08
#define VK_SHIFT    0x10
#define VK_CAPITAL  0x14
#define VK_LEFT     0x25
#define VK_RIGHT    0x27

#define VK_KEY0     0x30
#define VK_KEY1     0x31
#define VK_KEY2     0x32
#define VK_KEY3     0x33
#define VK_KEY4     0x34
#define VK_KEY5     0x35
#define VK_KEY6     0x36
#define VK_KEY7     0x37
#define VK_KEY8     0x38
#define VK_KEY9     0x39

new textid, canvas, button;

main() { }

public OnGameModeInit()
{
	SetRocketDelay(50);
	SetGameModeText("Samp+ Pre-Alpha");
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	textid = CreateD3DText
	(
		playerid, //id
		40.0, //x
		40.0, //y
		15.0, //w
		0.0, //h
		"Get my money bitch", //text
		"Arial" //font
	);
	
	canvas = CreateCanvas(playerid);
	SetCanvasSize(playerid, canvas, 400, 300);
    SetBackColorCanvas(playerid, canvas, 150, 170, 170, 255);
    
    button = CreateButton(playerid, canvas);
    SetPosButton(playerid, button, 100, 100);
    SetTextButton(playerid, button, "Test");
    SetSizeButton(playerid, button, 100, 100);
    
 	SetSpawnInfo(playerid, 255, 0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	SpawnPlayer (playerid);
	return 1;
}

public OnPlayerSAMPPJoin(playerid, bool:has_plugin)
{
	if (has_plugin == false)
	{
		SendClientMessage (playerid, -1, "Для игры на сервере, нужно установить дополнение!");
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	DestroyCanvas(playerid, canvas);
	DestroyButton(playerid, button);
    DestroyD3DText(playerid, textid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
    TogglePlayerClock(playerid, 1);
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    return 0;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
	return 0;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}


public OnPlayerKeyDown (playerid, key)
{
	return 1;
}

CMD:pickup(playerid, params[])
{
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    CreatePickup(1242, 23, pos[0], pos[1], pos[2], -1);
    return 1;
}

CMD:settext(playerid, params[])
{
	if (sscanf(params, "s[256]", params[0])) return SendClientMessage (playerid, -1, "params: text[256]");
	SetD3DText(playerid, textid, params);
	return 1;
}

CMD:pickupsize(playerid, params[])
{
	new Float:size;
	if (sscanf(params, "f", size))
	{
		new str[128];
		format (str, sizeof (str), "Current pickups size: %f", GetPickupSize(playerid));
		SendClientMessage(playerid, -1, str);
		return 1;
	}
	SetPickupSize(playerid, size);
	return 1;
}

CMD:flamecolor(playerid, params[])
{
	if (sscanf(params, "ii", params[0], params[1]))
	{
		new str[128];
		new color[2];
		GetPlayerFlameColor(playerid, color[0], color[1]);
		format (str, sizeof (str), "Current flame color: %i | %i", color[0], color[1]);
		SendClientMessage(playerid, -1, str);
		return 1;
	}
	SetPlayerFlameColor(playerid, params[0], params[1]);
	return 1;
}

CMD:cursor(playerid)
{
	TogglePlayerCursor(playerid, !GetCursorState(playerid));
	new str[128];
	format (str, sizeof (str), "New cursor state: %s", GetCursorState(playerid) == true ? ("Enabled") : ("Disabled"));
	SendClientMessage(playerid, -1, str);
	return 1;
}

CMD:clock(playerid, params[])
{
	if (sscanf(params, "s[10]", params[0])) return SendClientMessage(playerid, -1, "params: format[10]");
	SetClockStringFormat(playerid, params);
	return 1;
}

CMD:money(playerid, params[])
{
	if (sscanf(params, "s[6]", params[0])) return SendClientMessage(playerid, -1, "params: format[6]");
	SetMoneyStringFormat(playerid, params);
	return 1;
}

CMD:setmoney(playerid, params[])
{
	if (sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, "params: money");
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, params[0]);
	return 1;
}

CMD:gun(playerid, params[])
{
	GivePlayerWeapon(playerid, 37, 1000);
	return 1;
}


CMD:hydra(playerid, params[])
{
	new Float:pos[3];
    GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
    CreateVehicle(520, pos[0] + 20, pos[1], pos[2], 82.2873, -1, -1, 9999);
	return 1;
}

CMD:plane(playerid, params[])
{
    if (sscanf(params, "iiii", params[0],params[1],params[2],params[3]))
    {
        new str[128];
        new col[4];
		GetPlaneRadarColor(playerid, col[0], col[1], col[2], col[3]);
		format(str, sizeof(str), "Текущий цвет радара: R(%d) G(%d) B(%d) A(%d)", col[0], col[1], col[2], col[3]);
		SendClientMessage(playerid, -1, str);
		return 1;
    }
    SetPlaneRadarColor(playerid, params[0],params[1],params[2],params[3]);
    return 1;
}

CMD:watercolor(playerid, params[])
{
	new Float:col[4];
	if (sscanf(params, "ffff", col[0], col[1], col[2], col[3]))
	{
	    SendClientMessage(playerid, -1, "Цвет воды изменён на на чальное значение!");
	    ResetWaterColorForPlayer(playerid);
	    return 1;
	}
	SetWaterColorForPlayer (playerid, col[0], col[1], col[2], col[3]);
	return 1;
}

CMD:suncolor(playerid, params[])
{
	if (sscanf(params, "iiiiii", params[0], params[1], params[2], params[3], params[4], params[5])) return SendClientMessage(playerid, -1, "params: r g b r g b");
	SetSunColorForPlayer (playerid, params[0], params[1], params[2], params[3], params[4], params[5]);
	return 1;
}

CMD:gamespeed(playerid, params[])
{
	new Float:speed;
	if (sscanf(params, "f", speed)) return SendClientMessage(playerid, -1, "params: Float:speed");
	SetGameSpeedForAll(speed);
	return 1;
}
