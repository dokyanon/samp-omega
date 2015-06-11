#SA-MP Omega [SA-MP Plus] (https://github.com/KingHual/SA-MP-Plus) Fork
==========

A client modification that uses SA-MP's plugin SDK to interact with the server and add new features

Download
---------
  * [PAWN include.](srv/pawno/include/sampp.inc?raw=true)
  * [Source code.](https://github.com/Debug-/samp-omega/archive/master.zip)
  * [Client] (https://github.com/Debug-/samp-omega/blob/master/srv/client/sampp_client.asi)

Installation (Client)
---------

  * Download and install an [ASI Loader for GTA San Andreas](http://www.gtagarage.com/mods/show.php?id=8321) if you don't have one,
  * Place the [sampp_client.asi] (https://github.com/Debug-/samp-omega/blob/master/srv/client/sampp_client.asi) file in your GTA:SA's folder, along with *gta_sa.exe*.
  

Installation (Server)
---------
  * Download source
  * Compile the server plugin.
  * Place the file in the *plugins* folder of your server.
  * Add the plugin to your server's *server.cfg*.

Functions
---------
  * ToggleHUDComponentForPlayer(playerid, componentid, bool:toggle);
  * SetRadioStationForPlayer(playerid, stationid);
  * SetWaveHeightForPlayer(playerid, Float:height);
  * SetWaveHeightForAll(Float:height);
  * TogglePauseMenuAbility(playerid, bool:toggle);
  * IsPlayerInPauseMenu(playerid);
  * SetPlayerHUDComponentColour(playerid, componentid, colour);
  * TogglePlayerAction(playerid, actionid, bool:toggle);
  * SetPlayerNoReload(playerid, bool:toggle);
  * GetPlayerResolution(playerid, &width, &height);
  * SetPlayerBlurIntensity(playerid, intensity);
  * SetPlayerGameSpeed(playerid, Float:speed);
  * TogglePlayerDriveOnWater(playerid, bool:toggle);
  * TogglePlayerFrozen(playerid, bool:toggle);
  * SetPlayerPedAnims(playerid, bool:toggle);
  * TogglePlayerSwitchReload(playerid, bool:toggle);
  * TogglePlayerInfiniteRun(playerid, bool:toggle);
  * SetPlayerAircraftHeight(playerid, Float:height);
  * Float:GetPlayerAircraftHeight(playerid);
  * SetPlayerJetpackHeight(playerid, Float:height);
  * Float:GetPlayerJetpackHeight(playerid);
  * bool:IsUsingSAMPP(playerid);
  * SetPlayerRaceCheckpointEx(playerid, type, Float:x, Float:y, Float:z, Float:point_x, Float:point_y, Float:point_z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0);
  * SetPlayerCheckpointColour(playerid, colour)
  * SetPlayerRaceCheckpointColour(playerid, colour)
  * TogglePlayerVehicleBlips(playerid, bool:toggle)
  * GetPlayerVehicleBlips(playerid)
  * GetPlayerRadioStation(playerid)
  * TogglePlayerInfiniteOxygen(playerid, bool:toggle)
  * ToggleWaterBuoyancy(playerid, bool:toggle)
  * ToggleUnderwaterEffect(playerid, bool:toggle)
  * ToggleNightVision(playerid, bool:toggle)
  * ToggleThermalVision(playerid, bool:toggle)
  * SetWaterColorForPlayer(playerid, Float:r, Float:g, Float:b, Float:a);
  * SetWaterColorForAll(Float:r, Float:g, Float:b, Float:a);
  * ResetWaterColorForPlayer(playerid);
  * ResetWaterColorForAll();
  * ToggleQuickReloadForPlayer(playerid, bool:toggle); //returned toggle
  * ToggleQuickReloadForAll(bool:toggle); //returned toggle
  * SetSunColorForPlayer(playerid, core_r, core_g, core_b, corona_r, corona_g, corona_b);
  * SetSunColorForAll(core_r, core_g, core_b, corona_r, corona_g, corona_b);
  * ResetSunColorForPlayer(playerid);
  * ResetSunColorForAll();
  * SetGameSpeedForPlayer(playerid, Float:speed); //returned speed
  * SetGameSpeedForAll(Float:speed); //returned speed
  * SetRocketDelay(delay); //returned delay
  * SetPickupSize(playerid, Float:size); //returned size
  * Float:GetPickupSize(playerid);
  * TogglePlayerCursor (playerid, bool:toggle); //returned toggle
  * bool:GetCursorState(playerid);
  * SetPlayerFlameColor(playerid, color_1, color_2);
  * GetPlayerFlameColor(playerid, &color_1, &color_2);
  * SetPlaneRadarColor (playerid, r, g, b, a);
  * GetPlaneRadarColor (playerid, &r, &g, &b, &a);
  * SetClockStringFormat(playerid, format[]); //format len !> 10
  * SetMoneyStringFormat(playerid, format[]); //format len !> 6

####Callbacks:
  * OnPlayerOpenPauseMenu(playerid)
  * OnPlayerClosePauseMenu(playerid)
  * OnPlayerEnterPauseSubmenu(playerid, from, to)
  * OnDriverDriveByShot(playerid)
  * OnPlayerStunt(playerid, stuntid, money, details[])
  * OnPlayerResolutionChange(playerid, X, Y)
  * OnPlayerSAMPPConnect(address[], port)
  * OnPlayerSAMPPJoin(playerid, bool:has_plugin)
  * OnPlayerClick(playerid, type, X, Y)
  * OnPlayerKeyDown(playerid, key)
  * OnPlayerChangeRadioStation(playerid, stationid, vehicleid)
  * OnPlayerDrinkSprunk(playerid)

####Experimental/Unstable:
  * SetPlayerCheckpointEx(playerid, Float:x, Float:y, Float:z, Float:size, colour = 0xFF000020, period = 1024, Float:pulse = 0.1, rotation_rate = 0, bool:check_z = true);
  * CreateD3DText (playerid, Float:x, Float:y, Float:w, Float:h, text[], font[]);
  * SetD3DText (playerid, textid, text[]);
  * ShowD3DText (playerid, id, bool:toggle);
  * DestroyD3DText (playerid, id);
  * CreateD3DBox (playerid, Float:x, Float:y, Float:w, Float:h, res[], a, r, g, b);
  * ShowD3DBox (playerid, id, bool:toggle);
  * DestroyD3DBox (playerid, id);
  * CreateD3DSprite (playerid, Float:x, Float:y, Float:w, Float:h, res[]);
  * DestroyD3DSprite (playerid, id);
  * ResizeD3DSprite (playerid, id, Float:w, Float:h);
  * MoveD3DSprite (playerid, id, Float:x, Float:y);
  * RotateD3DSprite (playerid, id, Float:angle);
  * ShowD3DSprite (playerid, id, bool:toggle); 
  * CreateButton(playerid, canvas);
  * SetPosButton(playerid, id, x, y);
  * SetTextButton(playerid, id, text[]);
  * SetSizeButton(playerid, id, w, h);
  * DestroyButton(playerid, id);
  * CreateCanvas (playerid);
  * SetBackColorCanvas (playerid, id, r, g, b, a);
  * SetCanvasSize (playerid, id, w, h);
  * DestroyCanvas (playerid, id);

Compilation
---------

####Windows:
  * Open the provided solution file (.sln) in Visual Studio.
  * Make sure to change the target to *"Release"* unless you want a build with debug symbols.

####Linux:
  * Open a terminal and use the following commands:
```sh
cd Build
mkdir Temp
cd Temp
cmake ../..
make
```
  * Pass the *-DSAMPP_DEBUG=1* parameter to CMake for generating a build with debug symbols.
