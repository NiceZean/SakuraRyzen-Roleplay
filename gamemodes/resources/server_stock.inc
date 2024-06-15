stock SQL_IsLogged(playerid) {
	return (PlayerData[playerid][pLogged] && PlayerData[playerid][pCharacter] > 0);
}

stock Float:cache_get_field_float(row, const field_name[])
{
	new
	    str[16];

	cache_get_field_content(row, field_name, str, g_iHandle, sizeof(str));
	return floatstr(str);
}

stock ViewFactions(playerid)
{
	new string[1040];
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists]) {
 		format(string, sizeof(string), "%s{FFFFFF}Faction ({FFBF00}%i{FFFFFF}) | %s\n", string, i, FactionData[i][factionName]);
	}
	Dialog_Show(playerid, FactionsList, DIALOG_STYLE_MSGBOX, "Factions List", string, "Close", "");
	return 1;
}

stock SQL_ReturnEscaped(const string[])
{
	new
	    entry[256];

	mysql_real_escape_string(string, entry, g_iHandle);
	return entry;
}

stock LoadServerSettings()
{	
	SendRconCommand("hostname .:: SAKURA RYZEN ROLEPLAY | 2021 - 2024 ::.");
	SendRconCommand("weburl dsc.gg/sakura-ryzen");
	SendRconCommand("language Bahasa Melayu/ English");
	SetGameModeText("Version 3.7.9-1");
    return 1;
}

stock GetInitials(const string[])
{
	new
	    ret[32],
		index = 0;

	for (new i = 0, l = strlen(string); i != l; i ++)
	{
	    if (('A' <= string[i] <= 'Z') && (i == 0 || string[i - 1] == ' '))
			ret[index++] = string[i];
	}
	return ret;
}

stock GetDistance(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return floatround(floatsqroot(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) + ((z1 - z2) * (z1 - z2))));
}

stock Float:DistanceCameraTargetToLocation(Float:fCameraX, Float:fCameraY, Float:fCameraZ, Float:fObjectX, Float:fObjectY, Float:fObjectZ, Float:fVectorX, Float:fVectorY, Float:fVectorZ)
{
	new
		Float:fX,
		Float:fY,
		Float:fZ,
		Float:fDistance;

	fDistance = GetDistance(fCameraX, fCameraY, fCameraZ, fObjectX, fObjectY, fObjectZ);

	fX = fVectorX * fDistance + fCameraX;
	fY = fVectorY * fDistance + fCameraY;
	fZ = fVectorZ * fDistance + fCameraZ;

	return floatsqroot((fX - fObjectX) * (fX - fObjectX) + (fY - fObjectY) * (fY - fObjectY) + (fZ - fObjectZ) * (fZ - fObjectZ));
}

stock PlayerHasTazer(playerid)
{
	return (GetPlayerWeapon(playerid) == 23 && PlayerData[playerid][pTazer]);
}

stock PlayerHasBeanBag(playerid)
{
	return (GetPlayerWeapon(playerid) == 25 && PlayerData[playerid][pBeanBag]);
}


stock SetPlayerToFacePlayer(playerid, targetid)
{
	new
	    Float:x[2],
	    Float:y[2],
	    Float:z[2],
	    Float:angle;

	GetPlayerPos(targetid, x[0], y[0], z[0]);
	GetPlayerPos(playerid, x[1], y[1], z[1]);

	angle = (180.0 - atan2(x[1] - x[0], y[1] - y[0]));
	SetPlayerFacingAngle(playerid, angle + (5.0 * -1));
}

stock DisableWaypoint(playerid)
{
    if (PlayerData[playerid][pWaypoint])
	{
 		PlayerData[playerid][pWaypoint] = 0;

 		DisablePlayerCheckpoint(playerid);
  		PlayerTextDrawHide(playerid, WaypointTD[playerid]);
	}
	return 1;
}

stock TerminateConnection(playerid)
{
	if (BoomboxData[playerid][boomboxPlaced])
		Boombox_Destroy(playerid);
		
	if (PlayerData[playerid][pFirstAid])
	    KillTimer(PlayerData[playerid][pAidTimer]);

	if (PlayerData[playerid][pDrivingTest])
	    DestroyVehicle(PlayerData[playerid][pTestCar]);

	if (PlayerData[playerid][pSweeper])
	    DestroyVehicle(PlayerData[playerid][pSweeperCar]);

	if (PlayerData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID)
	    LeaveTaxi(playerid, PlayerData[playerid][pTaxiPlayer]);

	if (PlayerData[playerid][pDragged])
	    KillTimer(PlayerData[playerid][pDragTimer]);

	if (PlayerData[playerid][pFreeze])
	    KillTimer(PlayerData[playerid][pFreezeTimer]);
	
	foreach (new i : Player)
	{
	    if (PlayerData[i][pLastShot] == playerid) {
	        PlayerData[i][pLastShot] = INVALID_PLAYER_ID;
		}
		if (PlayerData[i][pHouseSeller] == playerid) {
		    PlayerData[i][pHouseSeller] = INVALID_PLAYER_ID;
		    PlayerData[i][pHouseOffered] = -1;
		}
		if (PlayerData[i][pBusinessSeller] == playerid) {
		    PlayerData[i][pBusinessSeller] = INVALID_PLAYER_ID;
		    PlayerData[i][pBusinessOffered] = -1;
		}
		if (PlayerData[i][pCarSeller] == playerid) {
		    PlayerData[i][pCarSeller] = INVALID_PLAYER_ID;
		    PlayerData[i][pCarOffered] = -1;
		}
		if (PlayerData[i][pShakeOffer] == playerid) {
		    PlayerData[i][pShakeOffer] = INVALID_PLAYER_ID;
		    PlayerData[i][pShakeType] = 0;
		}
		if (PlayerData[i][pFriskOffer] == playerid) {
		    PlayerData[i][pFriskOffer] = INVALID_PLAYER_ID;
		}
		if (PlayerData[i][pFoodSeller] == playerid) {
		    PlayerData[i][pFoodSeller] = INVALID_PLAYER_ID;
		    PlayerData[i][pFoodType] = 0;
		}
		if (PlayerData[i][pFactionOffer] == playerid) {
		    PlayerData[i][pFactionOffer] = INVALID_PLAYER_ID;
		    PlayerData[i][pFactionOffered] = -1;
		}
		if (PlayerData[i][pDraggedBy] == playerid) {
		    KillTimer(PlayerData[i][pDragTimer]);

		    PlayerData[i][pDragged] = 0;
            PlayerData[i][pDraggedBy] = INVALID_PLAYER_ID;
		}
		if (PlayerData[i][pMDCPlayer] == playerid) {
		    PlayerData[i][pMDCPlayer] = INVALID_PLAYER_ID;
		    PlayerData[i][pTrackTime] = 0;
		}
		if (PlayerData[i][pGiveItem] == playerid) {
		    PlayerData[i][pGiveItem] = INVALID_PLAYER_ID;
		}
	}
	SQL_SaveCharacter(playerid);
	RemovePlayerCar(playerid);
	Report_Clear(playerid);
	ResetStatistics(playerid);
	DestroyVehicle(PoliceDrone[playerid]);
	return 1;
}

stock GetWeapon(playerid)
{
	new weaponid = GetPlayerWeapon(playerid);

	if (1 <= weaponid <= 46 && PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
 		return weaponid;

	return 0;
}

stock IsBleedableWeapon(weaponid)
{
	switch (weaponid) {
	    case 4, 8, 9, 22..38: return 1;
	}
	return 0;
}

stock CreateBlood(playerid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);
	SetTimerEx("DestroyBlood", 1500, false, "d", CreateDynamicObject(18668, x, y, z - 1.5, 0.0, 0.0, 0.0));

	return 1;
}

stock Graffiti_Refresh(id)
{
	if (id != -1 && GraffitiData[id][graffitiExists])
	{
		if (IsValidDynamicMapIcon(GraffitiData[id][graffitiIcon]))
		    DestroyDynamicMapIcon(GraffitiData[id][graffitiIcon]);

		if (IsValidDynamicObject(GraffitiData[id][graffitiObject]))
			DestroyDynamicObject(GraffitiData[id][graffitiObject]);

        GraffitiData[id][graffitiIcon] = CreateDynamicMapIcon(GraffitiData[id][graffitiPos][0], GraffitiData[id][graffitiPos][1], GraffitiData[id][graffitiPos][2], 23, 0, -1, -1, -1, 100.0, MAPICON_GLOBAL);
		GraffitiData[id][graffitiObject] = CreateDynamicObject(19482, GraffitiData[id][graffitiPos][0], GraffitiData[id][graffitiPos][1], GraffitiData[id][graffitiPos][2], 0.0, 0.0, GraffitiData[id][graffitiPos][3]);

		SetDynamicObjectMaterial(GraffitiData[id][graffitiObject], 0, 0, "none", "none", 0);
		SetDynamicObjectMaterialText(GraffitiData[id][graffitiObject], 0, GraffitiData[id][graffitiText], OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, GraffitiData[id][graffitiColor], 0, 0);
	}
	return 1;
}

stock IsSprayingInProgress(id)
{
	foreach (new i : Player)
	{
	    if (PlayerData[i][pGraffiti] == id && IsPlayerInRangeOfPoint(i, 5.0, GraffitiData[id][graffitiPos][0], GraffitiData[id][graffitiPos][1], GraffitiData[id][graffitiPos][2]))
	        return 1;
	}
	return 0;
}

stock Graffiti_Nearest(playerid)
{
	for (new i = 0; i < MAX_GRAFFITI_POINTS; i ++) if (GraffitiData[i][graffitiExists] && IsPlayerInRangeOfPoint(playerid, 5.0, GraffitiData[i][graffitiPos][0], GraffitiData[i][graffitiPos][1], GraffitiData[i][graffitiPos][2]))
	    return i;

	return -1;
}

stock Graffiti_Delete(id)
{
    if (id != -1 && GraffitiData[id][graffitiExists])
	{
	    new
	        string[64];

		if (IsValidDynamicMapIcon(GraffitiData[id][graffitiIcon]))
		    DestroyDynamicMapIcon(GraffitiData[id][graffitiIcon]);

		if (IsValidDynamicObject(GraffitiData[id][graffitiObject]))
			DestroyDynamicObject(GraffitiData[id][graffitiObject]);

		format(string, sizeof(string), "DELETE FROM `graffiti` WHERE `graffitiID` = '%d'", GraffitiData[id][graffitiID]);
		mysql_tquery(g_iHandle, string);

		GraffitiData[id][graffitiExists] = false;
		GraffitiData[id][graffitiText][0] = 0;
		GraffitiData[id][graffitiID] = 0;
	}
	return 1;
}

stock Graffiti_Save(id)
{
	new
	    query[384];

	format(query, sizeof(query), "UPDATE `graffiti` SET `graffitiX` = '%.4f', `graffitiY` = '%.4f', `graffitiZ` = '%.4f', `graffitiAngle` = '%.4f', `graffitiColor` = '%d', `graffitiText` = '%s' WHERE `graffitiID` = '%d'",
        GraffitiData[id][graffitiPos][0],
        GraffitiData[id][graffitiPos][1],
        GraffitiData[id][graffitiPos][2],
        GraffitiData[id][graffitiPos][3],
		GraffitiData[id][graffitiColor],
		SQL_ReturnEscaped(GraffitiData[id][graffitiText]),
		GraffitiData[id][graffitiID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock Graffiti_Create(Float:x, Float:y, Float:z, Float:angle)
{
	for (new i = 0; i < MAX_GRAFFITI_POINTS; i ++)
	{
	    if (!GraffitiData[i][graffitiExists])
	    {
			GraffitiData[i][graffitiExists] = 1;
			GraffitiData[i][graffitiPos][0] = x;
			GraffitiData[i][graffitiPos][1] = y;
			GraffitiData[i][graffitiPos][2] = z;
			GraffitiData[i][graffitiPos][3] = angle - 90.0;
			GraffitiData[i][graffitiColor] = 0xFFFFFFFF;

			format(GraffitiData[i][graffitiText], 32, "Graffiti");

			Graffiti_Refresh(i);
			mysql_tquery(g_iHandle, "INSERT INTO `graffiti` (`graffitiColor`) VALUES(0)", "OnGraffitiCreated", "d", i);

			return i;
		}
	}
	return -1;
}

stock Speed_Refresh(speedid)
{
	if (speedid != -1 && SpeedData[speedid][speedExists])
	{
	    new
	        string[80];

		if (IsValidDynamicObject(SpeedData[speedid][speedObject]))
		    DestroyDynamicObject(SpeedData[speedid][speedObject]);

		if (IsValidDynamic3DTextLabel(SpeedData[speedid][speedText3D]))
		    DestroyDynamic3DTextLabel(SpeedData[speedid][speedText3D]);

		format(string, sizeof(string), "[SPEEDTRAP]\n{FFFFFF}Speed Limit: "YELLOW_E"%.0f KM/H"WHITE_E"\nStatus: %s", SpeedData[speedid][speedLimit], (SpeedData[speedid][speedStatus] == 1) ? (""GREEN_E"On") : (""RED_E"Off"));

		SpeedData[speedid][speedText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, SpeedData[speedid][speedPos][0], SpeedData[speedid][speedPos][1], SpeedData[speedid][speedPos][2] + 2.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        SpeedData[speedid][speedObject] = CreateDynamicObject(18880, SpeedData[speedid][speedPos][0], SpeedData[speedid][speedPos][1], SpeedData[speedid][speedPos][2], 0.0, 0.0, SpeedData[speedid][speedPos][3]);
	}
	return 1;
}

stock Speed_Save(speedid)
{
	new
	    query[255];

	format(query, sizeof(query), "UPDATE `speedcameras` SET `speedRange` = '%.4f', `speedLimit` = '%.4f', `speedStatus` = '%d', `speedX` = '%.4f', `speedY` = '%.4f', `speedZ` = '%.4f', `speedAngle` = '%.4f' WHERE `speedID` = '%d'",
	    SpeedData[speedid][speedRange],
	    SpeedData[speedid][speedLimit],
		SpeedData[speedid][speedStatus],
	    SpeedData[speedid][speedPos][0],
	    SpeedData[speedid][speedPos][1],
	    SpeedData[speedid][speedPos][2],
	    SpeedData[speedid][speedPos][3],
	    SpeedData[speedid][speedID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock Speed_Nearest(playerid)
{
	for (new i = 0; i < MAX_SPEED_CAMERAS; i ++) if (SpeedData[i][speedExists] && IsPlayerInRangeOfPoint(playerid, SpeedData[i][speedRange], SpeedData[i][speedPos][0], SpeedData[i][speedPos][1], SpeedData[i][speedPos][2]))
	    return i;

	return -1;
}

stock Speed_Delete(speedid)
{
    if (speedid != -1 && SpeedData[speedid][speedExists])
	{
	    new
	        string[64];

		if (IsValidDynamicObject(SpeedData[speedid][speedObject]))
		    DestroyDynamicObject(SpeedData[speedid][speedObject]);

		if (IsValidDynamic3DTextLabel(SpeedData[speedid][speedText3D]))
		    DestroyDynamic3DTextLabel(SpeedData[speedid][speedText3D]);

		format(string, sizeof(string), "DELETE FROM `speedcameras` WHERE `speedID` = '%d'", SpeedData[speedid][speedID]);
		mysql_tquery(g_iHandle, string);

		SpeedData[speedid][speedExists] = false;
		SpeedData[speedid][speedStatus] = false;
		SpeedData[speedid][speedLimit] = 0.0;
		SpeedData[speedid][speedRange] = 0.0;
		SpeedData[speedid][speedID] = 0;
	}
	return 1;
}

stock Speed_Create(playerid, Float:limit, Float:range)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	for (new i = 0; i < MAX_SPEED_CAMERAS; i ++) if (!SpeedData[i][speedExists])
	{
	    SpeedData[i][speedExists] = true;
	    SpeedData[i][speedRange] = range;
        SpeedData[i][speedLimit] = limit;
		SpeedData[i][speedStatus] = true;

		SpeedData[i][speedPos][0] = x + (1.5 * floatsin(-angle, degrees));
	    SpeedData[i][speedPos][1] = y + (1.5 * floatcos(-angle, degrees));
	    SpeedData[i][speedPos][2] = z - 1.2;
	    SpeedData[i][speedPos][3] = angle;

	    Speed_Refresh(i);
	    mysql_tquery(g_iHandle, "INSERT INTO `speedcameras` (`speedRange`) VALUES(0.0)", "OnSpeedCreated", "d", i);
	    return i;
	}
	return -1;
}

stock IsPlayerOnPhone(playerid)
{
	if (PlayerData[playerid][pEmergency] > 0 || PlayerData[playerid][pPlaceAd] > 0 || PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
	    return 1;

	return 0;
}

stock FlipVehicle(vehicleid)
{
	new
	    Float:fAngle;

	GetVehicleZAngle(vehicleid, fAngle);

	SetVehicleZAngle(vehicleid, fAngle);
	SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
}

stock StopVehicleRadio(vehicleid)
{
	if ((IsValidVehicle(vehicleid) && IsEngineVehicle(vehicleid)) && CoreVehicles[vehicleid][vehRadio])
	{
	    CoreVehicles[vehicleid][vehRadio] = 0;

	    foreach (new i : Player)
		{
			if (IsPlayerInVehicle(i, vehicleid))
			{
			    StopAudioStreamForPlayer(i);
			    PlayerData[i][pPlayRadio] = 0;
			}
	    }
	}
	return 1;
}

stock SetVehicleRadio(vehicleid, url[])
{
	if (IsValidVehicle(vehicleid) && IsEngineVehicle(vehicleid))
	{
        CoreVehicles[vehicleid][vehRadio] = 1;
        strpack(CoreVehicles[vehicleid][vehURL], url, 128 char);

        foreach (new i : Player)
		{
			if (IsPlayerInVehicle(i, vehicleid))
			{
			    PlayerData[i][pPlayRadio] = 1;

			    StopAudioStreamForPlayer(i);
				PlayAudioStreamForPlayer(i, url);
            }
        }
	}
	return 1;
}

stock ResetVehicle(vehicleid)
{
	if (1 <= vehicleid <= MAX_VEHICLES)
	{
	    if (CoreVehicles[vehicleid][vehSirenOn] && IsValidDynamicObject(CoreVehicles[vehicleid][vehSirenObject]))
	        DestroyDynamicObject(CoreVehicles[vehicleid][vehSirenObject]);
		
		CoreVehicles[vehicleid][vehWindowsDown] = false;
		CoreVehicles[vehicleid][vehTemporary] = 0;
  		CoreVehicles[vehicleid][vehLoads] = 0;
		CoreVehicles[vehicleid][vehLoadType] = 0;
		CoreVehicles[vehicleid][vehCrate] = INVALID_OBJECT_ID;
		CoreVehicles[vehicleid][vehTrash] = 0;
		CoreVehicles[vehicleid][vehRepairing] = 0;
		CoreVehicles[vehicleid][vehSirenOn] = 0;
		CoreVehicles[vehicleid][vehRadio] = 0;
	}
	return 1;
}

stock RespawnVehicle(vehicleid)
{
	new id = Car_GetID(vehicleid);
	
	Car_Save(vehicleid);

	if(IsValidVehicle(vehicleid))
		DestroyVehicle(vehicleid);

	if (id != -1)
	    Car_Spawn(id);

	else SetVehicleToRespawn(vehicleid);

	ResetVehicle(vehicleid);
	return 1;
}

stock GetWeaponCount(playerid)
{
	new
		count,
	    weapon,
	    ammo;

	for (new i = 0; i < 12; i ++)
	{
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon > 0 && ammo > 0) count++;
	}
	return count;
}

stock Boombox_Place(playerid)
{
	new
	    Float:angle;

	GetPlayerFacingAngle(playerid, angle);

	strpack(BoomboxData[playerid][boomboxURL], "", 128 char);
	GetPlayerPos(playerid, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]);

	BoomboxData[playerid][boomboxPlaced] = true;
	BoomboxData[playerid][boomboxInterior] = GetPlayerInterior(playerid);
	BoomboxData[playerid][boomboxWorld] = GetPlayerVirtualWorld(playerid);

    BoomboxData[playerid][boomboxObject] = CreateDynamicObject(2226, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2] - 0.9, 0.0, 0.0, angle, BoomboxData[playerid][boomboxWorld], BoomboxData[playerid][boomboxInterior]);
    BoomboxData[playerid][boomboxText3D] = CreateDynamic3DTextLabel("[BOOMBOX]\n{FFFFFF}Type "GREEN_E"/boombox"WHITE_E" to use this boombox.", COLOR_DARKBLUE, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2] - 0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BoomboxData[playerid][boomboxWorld], BoomboxData[playerid][boomboxInterior]);

	return 1;
}

stock Boombox_Nearest(playerid)
{
	foreach (new i : Player) if (BoomboxData[i][boomboxPlaced] && GetPlayerInterior(playerid) == BoomboxData[i][boomboxInterior] && GetPlayerVirtualWorld(playerid) == BoomboxData[i][boomboxWorld] && IsPlayerInRangeOfPoint(playerid, 30.0, BoomboxData[i][boomboxPos][0], BoomboxData[i][boomboxPos][1], BoomboxData[i][boomboxPos][2])) {
     	return i;
	}
	return INVALID_PLAYER_ID;
}

stock Boombox_SetURL(playerid, url[])
{
	if (BoomboxData[playerid][boomboxPlaced])
	{
	    strpack(BoomboxData[playerid][boomboxURL], url, 128 char);

	    foreach (new i : Player) if (PlayerData[i][pBoombox] == playerid) {
	        StopAudioStreamForPlayer(i);
	        PlayAudioStreamForPlayer(i, url, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2], 30.0, 1);
		}
	}
	return 1;
}

stock Boombox_Destroy(playerid)
{
	if (BoomboxData[playerid][boomboxPlaced])
	{
		if (IsValidDynamicObject(BoomboxData[playerid][boomboxObject]))
		    DestroyDynamicObject(BoomboxData[playerid][boomboxObject]);

		if (IsValidDynamic3DTextLabel(BoomboxData[playerid][boomboxText3D]))
		    DestroyDynamic3DTextLabel(BoomboxData[playerid][boomboxText3D]);

		foreach (new i : Player) if (PlayerData[i][pBoombox] == playerid) {
		    StopAudioStreamForPlayer(i);
		}
        BoomboxData[playerid][boomboxPlaced] = false;
        BoomboxData[playerid][boomboxInterior] = 0;
        BoomboxData[playerid][boomboxWorld] = 0;
	}
	return 1;
}

stock Taxi_ShowCalls(playerid)
{
    static
	    string[2048];

	string[0] = 0;

	foreach (new i : Player) if (PlayerData[i][pTaxiCalled]) {
	    format(string, sizeof(string), "%s%d: %s (%s)\n", string, i, ReturnName(i, 0), GetPlayerLocation(i));
	}
	if (!strlen(string)) {
	    SendErrorMessage(playerid, "There are no taxi calls to accept.");
	}
	else Dialog_Show(playerid, AcceptTaxi, DIALOG_STYLE_LIST, "Taxi Calls", string, "Accept", "Cancel");
	return 1;
}

stock IsShipmentAccepted(businessid)
{
	foreach (new i : Player) if (PlayerData[i][pJob] == JOB_COURIER && PlayerData[i][pShipment] == businessid) {
	    return 1;
	}
	return 0;
}

stock CancelShipment(playerid)
{
    PlayerData[playerid][pShipment] = -1;

    if (PlayerData[playerid][pDeliverShipment])
    {
		PlayerData[playerid][pDeliverShipment] = 0;
		DisablePlayerCheckpoint(playerid);
	}
	return 1;
}

stock ShowShipments(playerid)
{
    static
	    string[2048],
		type[24];

	string[0] = 0;

	for (new i = 0; i < MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizShipment] && !IsShipmentAccepted(i))
	{
	    switch (BusinessData[i][bizType]) {
	        case 1: type = "Retail Supplies";
	        case 2: type = "Electronic";
	        case 3: type = "Clothing";
	        case 4: type = "Food Supplies";
			case 6: type = "Gasoline/Retail";
			case 7: type = "Furniture";
		}
	    format(string, sizeof(string), "%s%d: %s (%s)\n", string, i, BusinessData[i][bizName], type);
	}
	if (!strlen(string)) {
	    SendErrorMessage(playerid, "There are no shipments to accept.");
	}
	else Dialog_Show(playerid, AcceptShipment, DIALOG_STYLE_LIST, "Shipments", string, "Accept", "Cancel");
	return 1;
}

stock GetWheelName(componentid)
{
	new
		name[12];

	enum g_eWheelData {
	    g_eWheelModel,
	    g_eWheelName[12 char]
	};

	new const g_aWheelData[][g_eWheelData] = {
	    {1025, !"Offroad"},
	    {1073, !"Shadow"},
	    {1074, !"Mega"},
	    {1075, !"Rimshine"},
	    {1076, !"Wires"},
	    {1077, !"Classic"},
	    {1078, !"Twist"},
	    {1079, !"Cutter"},
	    {1080, !"Switch"},
	    {1081, !"Grove"},
	    {1082, !"Import"},
	    {1083, !"Dollar"},
	    {1084, !"Trance"},
	    {1085, !"Atomic"},
	    {1096, !"Ahab"},
	    {1097, !"Virtual"},
	    {1098, !"Access"}
	};
	for (new i = 0; i < sizeof(g_aWheelData); i ++) if (g_aWheelData[i][g_eWheelModel] == componentid) {
	    strunpack(name, g_aWheelData[i][g_eWheelName]);

	    return name;
	}
	strunpack(name, !"Unknown");
	return name;
}

stock SetVehicleColor(vehicleid, color1, color2)
{
    new id = Car_GetID(vehicleid);

	if (id != -1)
	{
	    CarData[id][carColor1] = color1;
	    CarData[id][carColor2] = color2;
	    Car_Save(id);
	}
	return ChangeVehicleColor(vehicleid, color1, color2);
}

stock SetVehiclePaintjob(vehicleid, paintjobid)
{
    new id = Car_GetID(vehicleid);

	if (id != -1)
	{
	    CarData[id][carPaintjob] = paintjobid;
	    Car_Save(id);
	}
	return ChangeVehiclePaintjob(vehicleid, paintjobid);
}

stock RemoveComponent(vehicleid, componentid)
{
	if (!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193))
	    return 0;

	new
		id = Car_GetID(vehicleid);

	if (id != -1)
	{
	    CarData[id][carMods][GetVehicleComponentType(componentid)] = 0;
	    Car_Save(id);
	}
	return RemoveVehicleComponent(vehicleid, componentid);
}

stock AddComponent(vehicleid, componentid)
{
	if (!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193))
	    return 0;

	new
		id = Car_GetID(vehicleid);

	if (id != -1)
	{
	    CarData[id][carMods][GetVehicleComponentType(componentid)] = componentid;
	    Car_Save(id);
	}
	return AddVehicleComponent(vehicleid, componentid);
}

stock ApplyAnimationEx(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync = 0)
{
	ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);

	PlayerData[playerid][pLoopAnim] = true;
	return 1;
}

stock AnimationCheck(playerid)
{
	return (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !PlayerData[playerid][pKilled] && !PlayerData[playerid][pFreeze] && !PlayerData[playerid][pCuffed] && !PlayerData[playerid][pStunned] && !PlayerData[playerid][pFirstAid] && !PlayerData[playerid][pCrafting] && PlayerData[playerid][pGraffiti] == -1);
}

stock PreloadAnimations(playerid)
{
	for (new i = 0; i < sizeof(g_aPreloadLibs); i ++) {
	    ApplyAnimation(playerid, g_aPreloadLibs[i], "null", 4.0, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

stock Vendor_Create(playerid, type)
{
	for (new i = 0; i != MAX_VENDORS; i ++) if (!VendorData[i][vendorExists])
	{
	    VendorData[i][vendorExists] = true;
	    VendorData[i][vendorType] = type;

	    GetPlayerPos(playerid, VendorData[i][vendorPos][0], VendorData[i][vendorPos][1], VendorData[i][vendorPos][2]);
	    GetPlayerFacingAngle(playerid, VendorData[i][vendorPos][3]);

	    VendorData[i][vendorPos][0] = VendorData[i][vendorPos][0] + (1.5 * floatsin(-VendorData[i][vendorPos][3], degrees));
	    VendorData[i][vendorPos][1] = VendorData[i][vendorPos][1] + (1.5 * floatcos(-VendorData[i][vendorPos][3], degrees));

		VendorData[i][vendorInterior] = GetPlayerInterior(playerid);
		VendorData[i][vendorWorld] = GetPlayerVirtualWorld(playerid);

		Vendor_Refresh(i);
		mysql_tquery(g_iHandle, "INSERT INTO `vendors` (`vendorType`) VALUES(0)", "OnVendorCreated", "d", i);
		return i;
	}
	return -1;
}

stock Vendor_Delete(vendorid)
{
	if (vendorid != -1 && VendorData[vendorid][vendorExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `vendors` WHERE `vendorID` = '%d'", VendorData[vendorid][vendorID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(VendorData[vendorid][vendorText3D]))
	        DestroyDynamic3DTextLabel(VendorData[vendorid][vendorText3D]);

		if (IsValidDynamicObject(VendorData[vendorid][vendorObject]))
		    DestroyDynamicObject(VendorData[vendorid][vendorObject]);

	    VendorData[vendorid][vendorExists] = false;
	    VendorData[vendorid][vendorType] = 0;
	    VendorData[vendorid][vendorID] = 0;
	}
	return 1;
}

stock Vendor_Refresh(vendorid)
{
	if (vendorid != -1 && VendorData[vendorid][vendorExists])
	{
	    if (IsValidDynamic3DTextLabel(VendorData[vendorid][vendorText3D]))
	        DestroyDynamic3DTextLabel(VendorData[vendorid][vendorText3D]);

		if (IsValidDynamicObject(VendorData[vendorid][vendorObject]))
		    DestroyDynamicObject(VendorData[vendorid][vendorObject]);

		new
			string[80];

		format(string, sizeof(string), "[VENDOR MACHINE]\n{FFFFFF}Press "GREEN_E"Y"WHITE_E" to use this vendor.");
		VendorData[vendorid][vendorText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, VendorData[vendorid][vendorPos][0], VendorData[vendorid][vendorPos][1], VendorData[vendorid][vendorPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, VendorData[vendorid][vendorWorld], VendorData[vendorid][vendorInterior]);

		switch (VendorData[vendorid][vendorType]) {
		    case 1: VendorData[vendorid][vendorObject] = CreateDynamicObject(1340, VendorData[vendorid][vendorPos][0], VendorData[vendorid][vendorPos][1], VendorData[vendorid][vendorPos][2], 0.0, 0.0, VendorData[vendorid][vendorPos][3] - 90.0, VendorData[vendorid][vendorWorld], VendorData[vendorid][vendorInterior]);
		    case 2: VendorData[vendorid][vendorObject] = CreateDynamicObject(1209, VendorData[vendorid][vendorPos][0], VendorData[vendorid][vendorPos][1], VendorData[vendorid][vendorPos][2] - 1.0, 0.0, 0.0, VendorData[vendorid][vendorPos][3], VendorData[vendorid][vendorWorld], VendorData[vendorid][vendorInterior]);
		}
	}
	return 1;
}

stock Vendor_Save(vendorid)
{
	new
	    query[300];

	format(query, sizeof(query), "UPDATE `vendors` SET `vendorType` = '%d', `vendorX` = '%.4f', `vendorY` = '%.4f', `vendorZ` = '%.4f', `vendorA` = '%.4f', `vendorInterior` = '%d', `vendorWorld` = '%d' WHERE `vendorID` = '%d'",
        VendorData[vendorid][vendorType],
        VendorData[vendorid][vendorPos][0],
        VendorData[vendorid][vendorPos][1],
        VendorData[vendorid][vendorPos][2],
        VendorData[vendorid][vendorPos][3],
        VendorData[vendorid][vendorInterior],
        VendorData[vendorid][vendorWorld],
        VendorData[vendorid][vendorID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock Garbage_Create(playerid, type)
{
	for (new i = 0; i != MAX_GARBAGE_BINS; i ++) if (!GarbageData[i][garbageExists])
	{
	    switch (type) {
	        case 1: GarbageData[i][garbageModel] = 1236;
	        case 2: GarbageData[i][garbageModel] = 1300;
	    }
	    GarbageData[i][garbageExists] = true;
	    GarbageData[i][garbageCapacity] = 0;

	    GetPlayerPos(playerid, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]);
	    GetPlayerFacingAngle(playerid, GarbageData[i][garbagePos][3]);

		switch (type) {
		    case 1: {
		    	GarbageData[i][garbagePos][0] = GarbageData[i][garbagePos][0] + (1.8 * floatsin(-GarbageData[i][garbagePos][3], degrees));
			    GarbageData[i][garbagePos][1] = GarbageData[i][garbagePos][1] + (1.8 * floatcos(-GarbageData[i][garbagePos][3], degrees));
			}
			case 2: {
		    	GarbageData[i][garbagePos][0] = GarbageData[i][garbagePos][0] + (1.0 * floatsin(-GarbageData[i][garbagePos][3], degrees));
			    GarbageData[i][garbagePos][1] = GarbageData[i][garbagePos][1] + (1.0 * floatcos(-GarbageData[i][garbagePos][3], degrees));
			}
		}
		GarbageData[i][garbageInterior] = GetPlayerInterior(playerid);
		GarbageData[i][garbageWorld] = GetPlayerVirtualWorld(playerid);

		Garbage_Refresh(i);
		mysql_tquery(g_iHandle, "INSERT INTO `garbage` (`garbageCapacity`) VALUES(0)", "OnGarbageCreated", "d", i);
		return i;
	}
	return -1;
}

stock Garbage_Delete(garbageid)
{
	if (garbageid != -1 && GarbageData[garbageid][garbageExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `garbage` WHERE `garbageID` = '%d'", GarbageData[garbageid][garbageID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(GarbageData[garbageid][garbageText3D]))
	        DestroyDynamic3DTextLabel(GarbageData[garbageid][garbageText3D]);

		if (IsValidDynamicObject(GarbageData[garbageid][garbageObject]))
		    DestroyDynamicObject(GarbageData[garbageid][garbageObject]);

	    GarbageData[garbageid][garbageExists] = false;
	    GarbageData[garbageid][garbageCapacity] = 0;
	    GarbageData[garbageid][garbageID] = 0;
	}
	return 1;
}

stock Garbage_Refresh(garbageid)
{
	if (garbageid != -1 && GarbageData[garbageid][garbageExists])
	{
	    if (IsValidDynamic3DTextLabel(GarbageData[garbageid][garbageText3D]))
	        DestroyDynamic3DTextLabel(GarbageData[garbageid][garbageText3D]);

		if (IsValidDynamicObject(GarbageData[garbageid][garbageObject]))
		    DestroyDynamicObject(GarbageData[garbageid][garbageObject]);

		new
			string[64];

		format(string, sizeof(string), "[GARBAGE]\n{FFFFFF}Trash Capacity: "YELLOW_E"%d/20", GarbageData[garbageid][garbageCapacity]);

		GarbageData[garbageid][garbageText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, GarbageData[garbageid][garbagePos][0], GarbageData[garbageid][garbagePos][1], GarbageData[garbageid][garbagePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GarbageData[garbageid][garbageWorld], GarbageData[garbageid][garbageInterior]);
		GarbageData[garbageid][garbageObject] = CreateDynamicObject(GarbageData[garbageid][garbageModel], GarbageData[garbageid][garbagePos][0], GarbageData[garbageid][garbagePos][1], (GarbageData[garbageid][garbageModel] == 1236) ? (GarbageData[garbageid][garbagePos][2] - 0.4) : (GarbageData[garbageid][garbagePos][2] - 0.6), 0.0, 0.0, GarbageData[garbageid][garbagePos][3], GarbageData[garbageid][garbageWorld], GarbageData[garbageid][garbageInterior]);
	}
	return 1;
}

stock Garbage_Save(garbageid)
{
	new
	    query[300];

	format(query, sizeof(query), "UPDATE `garbage` SET `garbageModel` = '%d', `garbageCapacity` = '%d', `garbageX` = '%.4f', `garbageY` = '%.4f', `garbageZ` = '%.4f', `garbageA` = '%.4f', `garbageInterior` = '%d', `garbageWorld` = '%d' WHERE `garbageID` = '%d'",
        GarbageData[garbageid][garbageModel],
        GarbageData[garbageid][garbageCapacity],
        GarbageData[garbageid][garbagePos][0],
        GarbageData[garbageid][garbagePos][1],
        GarbageData[garbageid][garbagePos][2],
        GarbageData[garbageid][garbagePos][3],
        GarbageData[garbageid][garbageInterior],
        GarbageData[garbageid][garbageWorld],
        GarbageData[garbageid][garbageID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock UpdateWeapons(playerid)
{
	for (new i = 0; i < 13; i ++) if (PlayerData[playerid][pGuns][i])
    {
		if ((i == 2 && PlayerData[playerid][pTazer]) || (i == 3 && PlayerData[playerid][pBeanBag]))
		    continue;

        GetPlayerWeaponData(playerid, i, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);

        if (PlayerData[playerid][pGuns][i] != 0 && !PlayerData[playerid][pAmmo][i]) {
            PlayerData[playerid][pGuns][i] = 0;
		}
	}
	return 1;
}

stock ATM_Delete(atmid)
{
	if (atmid != -1 && ATMData[atmid][atmExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `atm` WHERE `atmID` = '%d'", ATMData[atmid][atmID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamicObject(ATMData[atmid][atmObject]))
	        DestroyDynamicObject(ATMData[atmid][atmObject]);

	    if (IsValidDynamic3DTextLabel(ATMData[atmid][atmText3D]))
	        DestroyDynamic3DTextLabel(ATMData[atmid][atmText3D]);

	    ATMData[atmid][atmExists] = false;
	    ATMData[atmid][atmID] = 0;
	}
	return 1;
}

stock ATM_Create(playerid)
{
    new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_ATM_MACHINES; i ++) if (!ATMData[i][atmExists])
		{
		    ATMData[i][atmExists] = true;

			x += 1.0 * floatsin(-angle, degrees);
			y += 1.0 * floatcos(-angle, degrees);

            ATMData[i][atmPos][0] = x;
            ATMData[i][atmPos][1] = y;
            ATMData[i][atmPos][2] = z;
            ATMData[i][atmPos][3] = angle;

            ATMData[i][atmInterior] = GetPlayerInterior(playerid);
            ATMData[i][atmWorld] = GetPlayerVirtualWorld(playerid);

			ATM_Refresh(i);
			mysql_tquery(g_iHandle, "INSERT INTO `atm` (`atmInterior`) VALUES(0)", "OnATMCreated", "d", i);

			return i;
		}
	}
	return -1;
}

stock ATM_Refresh(atmid)
{
	if (atmid != -1 && ATMData[atmid][atmExists])
	{
	    if (IsValidDynamicObject(ATMData[atmid][atmObject]))
	        DestroyDynamicObject(ATMData[atmid][atmObject]);

	    if (IsValidDynamic3DTextLabel(ATMData[atmid][atmText3D]))
	        DestroyDynamic3DTextLabel(ATMData[atmid][atmText3D]);

		new
	        string[80];

		format(string, sizeof(string), "[ATM MACHINE]\n{FFFFFF}Press "GREEN_E"Y"WHITE_E" to use this machine.");

        ATMData[atmid][atmText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, ATMData[atmid][atmPos][0], ATMData[atmid][atmPos][1], ATMData[atmid][atmPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, ATMData[atmid][atmWorld], ATMData[atmid][atmInterior]);

		ATMData[atmid][atmObject] = CreateDynamicObject(2942, ATMData[atmid][atmPos][0], ATMData[atmid][atmPos][1], ATMData[atmid][atmPos][2] - 0.4, 0.0, 0.0, ATMData[atmid][atmPos][3], ATMData[atmid][atmWorld], ATMData[atmid][atmInterior]);

		return 1;
	}
	return 0;
}

stock ATM_Save(atmid)
{
	new
	    query[200];

	format(query, sizeof(query), "UPDATE `atm` SET `atmX` = '%.4f', `atmY` = '%.4f', `atmZ` = '%.4f', `atmA` = '%.4f', `atmInterior` = '%d', `atmWorld` = '%d' WHERE `atmID` = '%d'",
	    ATMData[atmid][atmPos][0],
	    ATMData[atmid][atmPos][1],
	    ATMData[atmid][atmPos][2],
	    ATMData[atmid][atmPos][3],
	    ATMData[atmid][atmInterior],
	    ATMData[atmid][atmWorld],
	    ATMData[atmid][atmID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock Backpack_Items(playerid, id)
{
 	if (id != -1 && BackpackData[id][backpackExists])
 	{
 	    new
	        string[MAX_BACKPACK_CAPACITY * 32],
			count = 0;

	    for (new i = 0; i < MAX_BACKPACK_ITEMS; i ++) if (BackpackItems[i][bItemExists] && BackpackItems[i][bItemBackpack] == id)
	    {
	        if (BackpackItems[i][bItemQuantity] == 1)
	            format(string, sizeof(string), "%s%s\n", string, BackpackItems[i][bItemName]);

			else format(string, sizeof(string), "%s%s (%d)\n", string, BackpackItems[i][bItemName], BackpackItems[i][bItemQuantity]);

			BackpackListed[playerid][count++] = i;
		}
		strcat(string, "Take Backpack");

		PlayerData[playerid][pBackpackLoot] = id;
		Dialog_Show(playerid, BackpackLoot, DIALOG_STYLE_LIST, "Backpack", string, "Select", "Cancel");
	}
	return 1;
}

stock Backpack_Open(playerid)
{
	new id = GetPlayerBackpack(playerid);

	if (id != -1)
	{
	    new
	        string[MAX_BACKPACK_CAPACITY * 32],
			count = 0;

		string = "Add Item\n";

	    for (new i = 0; i < MAX_BACKPACK_ITEMS; i ++) if (BackpackItems[i][bItemExists] && BackpackItems[i][bItemBackpack] == id)
	    {
	        if (BackpackItems[i][bItemQuantity] == 1)
	            format(string, sizeof(string), "%s%s\n", string, BackpackItems[i][bItemName]);

			else format(string, sizeof(string), "%s%s (%d)\n", string, BackpackItems[i][bItemName], BackpackItems[i][bItemQuantity]);

			BackpackListed[playerid][count++] = i;
		}
		Dialog_Show(playerid, Backpack, DIALOG_STYLE_LIST, "My Backpack", string, "Select", "Cancel");
	}
	return 1;
}

stock Backpack_GetItems(id)
{
	new count;

	for (new i = 0; i != MAX_BACKPACK_ITEMS; i ++) if (BackpackItems[i][bItemExists] && BackpackItems[i][bItemBackpack] == id) {
	    count++;
	}
	return count;
}

stock Backpack_GetFreeID()
{
	for (new i = 0; i != MAX_BACKPACKS; i ++) if (!BackpackData[i][backpackExists]) {
	    return i;
	}
	return -1;
}

stock Backpack_Refresh(id)
{
	if (id != -1 && BackpackData[id][backpackExists])
	{
	    if (IsValidDynamicObject(BackpackData[id][backpackObject]))
		    DestroyDynamicObject(BackpackData[id][backpackObject]);

		if (IsValidDynamic3DTextLabel(BackpackData[id][backpackText3D]))
		    DestroyDynamic3DTextLabel(BackpackData[id][backpackText3D]);

		if (!BackpackData[id][backpackPlayer]) 
		{
			new string[500];
			format(string, sizeof(string), "[BACKPACK]\n{FFFFFF}Press "GREEN_E"ALT"WHITE_E" to view the items.");
	        BackpackData[id][backpackObject] = CreateDynamicObject(3026, BackpackData[id][backpackPos][0], BackpackData[id][backpackPos][1], BackpackData[id][backpackPos][2] - 0.8, -90.0, 0.0, 0.0, BackpackData[id][backpackWorld], BackpackData[id][backpackInterior]);
    	   	BackpackData[id][backpackText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, BackpackData[id][backpackPos][0], BackpackData[id][backpackPos][1], BackpackData[id][backpackPos][2] - 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BackpackData[id][backpackWorld], BackpackData[id][backpackInterior]);
		}
	}
	return 1;
}

stock Backpack_GetItemID(id, name[])
{
	for (new i = 0; i != MAX_BACKPACK_ITEMS; i ++) if (BackpackItems[i][bItemExists] && BackpackItems[i][bItemBackpack] == id && !strcmp(BackpackItems[i][bItemName], name, true)) {
	    return i;
	}
	return -1;
}

stock Backpack_GetFreeItem()
{
	for (new i = 0; i != MAX_BACKPACK_ITEMS; i ++) if (!BackpackItems[i][bItemExists]) {
	    return i;
	}
	return -1;
}

stock Backpack_HasItem(id, name[])
{
	if (id != -1 && BackpackData[id][backpackExists])
		return Backpack_GetItemID(id, name) != -1;

	return 0;
}

stock Backpack_Count(id, name[])
{
	new itemid;

	if (id != -1 && BackpackData[id][backpackExists])
	{
		itemid = Backpack_GetItemID(id, name);

		if (itemid != -1)
		    return BackpackItems[itemid][bItemQuantity];
	}
	return 0;
}

stock Backpack_Add(id, name[], model, quantity = 1)
{
	new
	    query[128];

	if (id != -1 && BackpackData[id][backpackExists])
	{
	    new itemid = Backpack_GetItemID(id, name);

	    if (itemid != -1)
		{
	        format(query, sizeof(query), "UPDATE `backpackitems` SET `itemQuantity` = `itemQuantity` + %d WHERE `itemID` = '%d'", quantity, BackpackItems[itemid][bItemID]);
	        mysql_tquery(g_iHandle, query);

			return BackpackItems[itemid][bItemQuantity] += quantity;
		}
		else if ((itemid = Backpack_GetFreeItem()) != -1)
		{
		    format(BackpackItems[itemid][bItemName], 32, name);

		    BackpackItems[itemid][bItemBackpack] = id;
		    BackpackItems[itemid][bItemExists] = true;
		    BackpackItems[itemid][bItemModel] = model;
		    BackpackItems[itemid][bItemQuantity] = quantity;

	        format(query, sizeof(query), "INSERT INTO `backpackitems` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", BackpackData[id][backpackID], name, model, quantity);
	        mysql_tquery(g_iHandle, query, "OnBackpackAdd", "dd", id, itemid);

	        return 1;
		}
	}
	return 0;
}

stock Backpack_Remove(id, name[], quantity = 1)
{
	new
	    query[128];

	if (id != -1 && BackpackData[id][backpackExists])
	{
	    new itemid = Backpack_GetItemID(id, name);

	    if (itemid != -1)
		{
			if (BackpackItems[itemid][bItemQuantity] > 0)
			{
				BackpackItems[itemid][bItemQuantity] -= quantity;
			}
			if (BackpackItems[itemid][bItemQuantity] < 1)
			{
		        format(query, sizeof(query), "DELETE FROM `backpackitems` WHERE `itemID` = '%d'", BackpackItems[itemid][bItemID]);
		        mysql_tquery(g_iHandle, query);

			    BackpackItems[itemid][bItemBackpack] = -1;
			    BackpackItems[itemid][bItemExists] = false;
			    BackpackItems[itemid][bItemModel] = 0;
		    	BackpackItems[itemid][bItemQuantity] = 0;
		    }
			else
			{
                format(query, sizeof(query), "UPDATE `backpackitems` SET `itemQuantity` = `itemQuantity` - %d WHERE `itemID` = '%d'", quantity, BackpackItems[itemid][bItemID]);
		        mysql_tquery(g_iHandle, query);
			}
		    return 1;
		}
	}
	return 0;
}

stock GetHouseBackpack(houseid)
{
	for (new i = 0; i != MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && BackpackData[i][backpackHouse] == HouseData[houseid][houseID]) {
	    return i;
	}
	return -1;
}

stock GetVehicleBackpack(carid)
{
	for (new i = 0; i != MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && BackpackData[i][backpackVehicle] == CarData[carid][carID]) {
	    return i;
	}
	return -1;
}

stock GetPlayerBackpack(playerid)
{
	for (new i = 0; i != MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && BackpackData[i][backpackPlayer] == PlayerData[playerid][pID]) {
	    return i;
	}
	return -1;
}

stock Backpack_Create(playerid)
{
	new id = Backpack_GetFreeID();

	if (id != -1)
	{
		BackpackData[id][backpackExists] = true;
		BackpackData[id][backpackPlayer] = PlayerData[playerid][pID];
		BackpackData[id][backpackHouse] = 0;
		BackpackData[id][backpackVehicle] = 0;
		BackpackData[id][backpackPos][0] = 0.0;
		BackpackData[id][backpackPos][1] = 0.0;
		BackpackData[id][backpackPos][2] = 0.0;

		mysql_tquery(g_iHandle, "INSERT INTO `backpacks` (`backpackInterior`) VALUES(0)", "OnBackpackCreated", "d", id);
		return id;
	}
	return -1;
}

stock Backpack_Delete(id)
{
	if (id != -1 && BackpackData[id][backpackExists])
	{
	    new
	        str[64];

		format(str, sizeof(str), "DELETE FROM `backpacks` WHERE `backpackID` = '%d'", BackpackData[id][backpackID]);
		mysql_tquery(g_iHandle, str);

		if (IsValidDynamicObject(BackpackData[id][backpackObject]))
		    DestroyDynamicObject(BackpackData[id][backpackObject]);

		if (IsValidDynamic3DTextLabel(BackpackData[id][backpackText3D]))
		    DestroyDynamic3DTextLabel(BackpackData[id][backpackText3D]);

        BackpackData[id][backpackExists] = false;
        BackpackData[id][backpackID] = 0;
        BackpackData[id][backpackPlayer] = 0;
        BackpackData[id][backpackHouse] = 0;
        BackpackData[id][backpackVehicle] = 0;
	}
	return 1;
}

stock Backpack_Save(id)
{
	new
	    query[256];

    format(query, sizeof(query), "UPDATE `backpacks` SET `backpackPlayer` = '%d', `backpackHouse` = '%d', `backpackVehicle` = '%d', `backpackX` = '%.4f', `backpackY` = '%.4f', `backpackZ` = '%.4f', `backpackInterior` = '%d', `backpackWorld` = '%d' WHERE `backpackID` = '%d'",
        BackpackData[id][backpackPlayer],
        BackpackData[id][backpackHouse],
        BackpackData[id][backpackVehicle],
        BackpackData[id][backpackPos][0],
        BackpackData[id][backpackPos][1],
        BackpackData[id][backpackPos][2],
        BackpackData[id][backpackInterior],
        BackpackData[id][backpackWorld],
        BackpackData[id][backpackID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock IsValidObjectModel(modelid)
{
	if (modelid < 0 || modelid > 20000)
	    return 0;

    switch (modelid)
	{
		case 18632..18645, 18646..18658, 18659..18667, 18668..19299, 19301..19515, 18631, 331, 333..339, 318..321, 325, 326, 341..344, 346..353, 355..370, 372:
			return 1;
	}
    new const g_arrModelData[] =
	{
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -128,
        -515899393, -134217729, -1, -1, 33554431, -1, -1, -1, -14337, -1, -33,
      	127, 0, 0, 0, 0, 0, -8388608, -1, -1, -1, -16385, -1, -1, -1, -1, -1,
       -1, -1, -33, -1, -771751937, -1, -9, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, 33554431, -25, -1, -1, -1, -1, -1, -1,
       -1073676289, -2147483648, 34079999, 2113536, -4825600, -5, -1, -3145729,
       -1, -16777217, -63, -1, -1, -1, -1, -201326593, -1, -1, -1, -1, -1,
       -257, -1, 1073741823, -133122, -1, -1, -65, -1, -1, -1, -1, -1, -1,
       -2146435073, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1073741823, -64, -1,
       -1, -1, -1, -2635777, 134086663, 0, -64, -1, -1, -1, -1, -1, -1, -1,
       -536870927, -131069, -1, -1, -1, -1, -1, -1, -1, -1, -16384, -1,
       -33554433, -1, -1, -1, -1, -1, -1610612737, 524285, -128, -1,
       2080309247, -1, -1, -1114113, -1, -1, -1, 66977343, -524288, -1, -1, -1,
       -1, -2031617, -1, 114687, -256, -1, -4097, -1, -4097, -1, -1,
       1010827263, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -32768, -1, -1, -1, -1, -1,
       2147483647, -33554434, -1, -1, -49153, -1148191169, 2147483647,
       -100781080, -262145, -57, 134217727, -8388608, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1048577, -1, -449, -1017, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1835009, -2049, -1, -1, -1, -1, -1, -1,
       -8193, -1, -536870913, -1, -1, -1, -1, -1, -87041, -1, -1, -1, -1, -1,
       -1, -209860, -1023, -8388609, -2096897, -1, -1048577, -1, -1, -1, -1,
       -1, -1, -897, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1610612737,
       -3073, -28673, -1, -1, -1, -1537, -1, -1, -13, -1, -1, -1, -1, -1985,
       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1056964609, -1, -1, -1,
       -1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -236716037, -1, -1, -1, -1, -1, -1, -1, -536870913, 3, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -2097153, -2109441, -1, 201326591, -4194304, -1, -1,
       -241, -1, -1, -1, -1, -1, -1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, -32768, -1, -1, -1, -2, -671096835, -1, -8388609, -66323585, -13,
       -1793, -32257, -247809, -1, -1, -513, 16252911, 0, 0, 0, -131072,
       33554383, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8356095, 0, 0, 0, 0, 0,
       0, -256, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       -268435449, -1, -1, -2049, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
       92274627, -65536, -2097153, -268435457, 591191935, 1, 0, -16777216, -1,
       -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127
	};
 	return ((modelid >= 0) && ((modelid / 32) < sizeof(g_arrModelData)) && (g_arrModelData[modelid / 32] & (1 << (modelid % 32))));
}

stock Gate_Operate(gateid)
{
	if (gateid != -1 && GateData[gateid][gateExists])
	{
	    new id = -1;

		if (!GateData[gateid][gateOpened])
		{
		    GateData[gateid][gateOpened] = true;
		    MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gateMove][0], GateData[gateid][gateMove][1], GateData[gateid][gateMove][2], GateData[gateid][gateSpeed], GateData[gateid][gateMove][3], GateData[gateid][gateMove][4], GateData[gateid][gateMove][5]);

            if (GateData[gateid][gateTime] > 0) {
				GateData[gateid][gateTimer] = SetTimerEx("CloseGate", GateData[gateid][gateTime], false, "ddfffffff", gateid, GateData[gateid][gateLinkID], GateData[gateid][gatePos][0], GateData[gateid][gatePos][1], GateData[gateid][gatePos][2], GateData[gateid][gateSpeed], GateData[gateid][gatePos][3], GateData[gateid][gatePos][4], GateData[gateid][gatePos][5]);
			}
			if (GateData[gateid][gateLinkID] != -1 && (id = GetGateByID(GateData[gateid][gateLinkID])) != -1)
			{
			    GateData[id][gateOpened] = true;
			    MoveDynamicObject(GateData[id][gateObject], GateData[id][gateMove][0], GateData[id][gateMove][1], GateData[id][gateMove][2], GateData[id][gateSpeed], GateData[id][gateMove][3], GateData[id][gateMove][4], GateData[id][gateMove][5]);
			}
		}
		else if (GateData[gateid][gateOpened])
		{
		    GateData[gateid][gateOpened] = false;
		    MoveDynamicObject(GateData[gateid][gateObject], GateData[gateid][gatePos][0], GateData[gateid][gatePos][1], GateData[gateid][gatePos][2], GateData[gateid][gateSpeed], GateData[gateid][gatePos][3], GateData[gateid][gatePos][4], GateData[gateid][gatePos][5]);

            if (GateData[gateid][gateTime] > 0) {
				KillTimer(GateData[gateid][gateTimer]);
		    }
			if (GateData[gateid][gateLinkID] != -1 && (id = GetGateByID(GateData[gateid][gateLinkID])) != -1)
			{
			    GateData[id][gateOpened] = false;
			    MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gateSpeed], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);
			}
		}
	}
	return 1;
}

stock Gate_Create(playerid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i < MAX_GATES; i ++) if (!GateData[i][gateExists])
		{
		    GateData[i][gateExists] = true;
			GateData[i][gateModel] = 980;
			GateData[i][gateSpeed] = 3.0;
			GateData[i][gateRadius] = 5.0;
			GateData[i][gateOpened] = 0;
			GateData[i][gateTime] = 0;

			GateData[i][gatePos][0] = x + (3.0 * floatsin(-angle, degrees));
			GateData[i][gatePos][1] = y + (3.0 * floatcos(-angle, degrees));
			GateData[i][gatePos][2] = z;
			GateData[i][gatePos][3] = 0.0;
			GateData[i][gatePos][4] = 0.0;
			GateData[i][gatePos][5] = angle;

			GateData[i][gateMove][0] = x + (3.0 * floatsin(-angle, degrees));
			GateData[i][gateMove][1] = y + (3.0 * floatcos(-angle, degrees));
			GateData[i][gateMove][2] = z - 10.0;
			GateData[i][gateMove][3] = -1000.0;
			GateData[i][gateMove][4] = -1000.0;
			GateData[i][gateMove][5] = -1000.0;

            GateData[i][gateInterior] = GetPlayerInterior(playerid);
            GateData[i][gateWorld] = GetPlayerVirtualWorld(playerid);

            GateData[i][gateLinkID] = -1;
            GateData[i][gateFaction] = -1;

            GateData[i][gatePass][0] = '\0';
            GateData[i][gateObject] = CreateDynamicObject(GateData[i][gateModel], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2], GateData[i][gatePos][3], GateData[i][gatePos][4], GateData[i][gatePos][5], GateData[i][gateWorld], GateData[i][gateInterior]);

			mysql_tquery(g_iHandle, "INSERT INTO `gates` (`gateModel`) VALUES(980)", "OnGateCreated", "d", i);
			return i;
		}
	}
	return -1;
}

stock Gate_Delete(gateid)
{
	if (gateid != -1 && GateData[gateid][gateExists])
	{
		new
		    query[64];

		format(query, sizeof(query), "DELETE FROM `gates` WHERE `gateID` = '%d'", GateData[gateid][gateID]);
		mysql_tquery(g_iHandle, query);

		if (IsValidDynamicObject(GateData[gateid][gateObject]))
		    DestroyDynamicObject(GateData[gateid][gateObject]);

		for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && GateData[i][gateLinkID] == GateData[gateid][gateID]) {
		    GateData[i][gateLinkID] = -1;
		    Gate_Save(i);
		}
		if (GateData[gateid][gateOpened] && GateData[gateid][gateTime] > 0) {
		    KillTimer(GateData[gateid][gateTimer]);
		}
	    GateData[gateid][gateExists] = false;
	    GateData[gateid][gateID] = 0;
	    GateData[gateid][gateOpened] = 0;
	}
	return 1;
}

stock Gate_Save(gateid)
{
	new
	    query[768];

	format(query, sizeof(query), "UPDATE `gates` SET `gateModel` = '%d', `gateSpeed` = '%.4f', `gateRadius` = '%.4f', `gateTime` = '%d', `gateX` = '%.4f', `gateY` = '%.4f', `gateZ` = '%.4f', `gateRX` = '%.4f', `gateRY` = '%.4f', `gateRZ` = '%.4f', `gateInterior` = '%d', `gateWorld` = '%d', `gateMoveX` = '%.4f', `gateMoveY` = '%.4f', `gateMoveZ` = '%.4f', `gateMoveRX` = '%.4f', `gateMoveRY` = '%.4f', `gateMoveRZ` = '%.4f', `gateLinkID` = '%d', `gateFaction` = '%d', `gatePass` = '%s' WHERE `gateID` = '%d'",
	    GateData[gateid][gateModel],
	    GateData[gateid][gateSpeed],
	    GateData[gateid][gateRadius],
	    GateData[gateid][gateTime],
	    GateData[gateid][gatePos][0],
	    GateData[gateid][gatePos][1],
	    GateData[gateid][gatePos][2],
	    GateData[gateid][gatePos][3],
	    GateData[gateid][gatePos][4],
	    GateData[gateid][gatePos][5],
	    GateData[gateid][gateInterior],
	    GateData[gateid][gateWorld],
	    GateData[gateid][gateMove][0],
	    GateData[gateid][gateMove][1],
	    GateData[gateid][gateMove][2],
	    GateData[gateid][gateMove][3],
	    GateData[gateid][gateMove][4],
	    GateData[gateid][gateMove][5],
	    GateData[gateid][gateLinkID],
	    GateData[gateid][gateFaction],
	    SQL_ReturnEscaped(GateData[gateid][gatePass]),
	    GateData[gateid][gateID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock ChangeName(playerid, name[], bool:logging = true)
{
	new
	    id = PlayerData[playerid][pCharacter] - 1,
		query[160],
		oldname[24];

	GetPlayerName(playerid, oldname, sizeof(oldname));

	if (logging)
	{
	    format(query, sizeof(query), "INSERT INTO `namechanges` (`OldName`, `NewName`, `Date`) VALUES('%s', '%s', '%s')", oldname, name, ReturnDate());
		mysql_tquery(g_iHandle, query);
	}
    format(PlayerCharacters[playerid][id], MAX_PLAYER_NAME + 1, name);
	SetPlayerName(playerid, name);

	format(query, sizeof(query), "UPDATE `characters` SET `Character` = '%s' WHERE `Character` = '%s'", name, oldname);
	mysql_tquery(g_iHandle, query);

	return 1;
}

stock file_parse_int(File:handle, const field[])
{
	new
	    str[16];

	return (file_parse(handle, field, str), strval(str));
}

stock file_parse(File:handle, const field[], dest[], size = sizeof(dest))
{
	if (!handle)
	    return 0;

	new
	    str[128],
		pos = strlen(field);

	fseek(handle, 0, seek_start);

	while (fread(handle, str)) if (strfind(str, field, true) == 0 && (str[pos] == '=' || str[pos] == ' '))
	{
	    strmid(dest, str, (str[pos] == '=') ? (pos + 1) : (pos + 3), strlen(str), size);

		if ((pos = strfind(dest, "\r")) != -1)
			dest[pos] = '\0';
   		else if ((pos = strfind(dest, "\n")) != -1)
     		dest[pos] = '\0';

		return 1;
	}
	return 0;
}

stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, time = 2000)
{
	if (PlayerData[playerid][pFreeze])
	{
	    KillTimer(PlayerData[playerid][pFreezeTimer]);

	    PlayerData[playerid][pFreeze] = 0;
	    TogglePlayerControllable(playerid, 1);
	}
	SetPlayerPos(playerid, x, y, z + 0.5);
	TogglePlayerControllable(playerid, 0);

	PlayerData[playerid][pFreeze] = 1;
	PlayerData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "dfff", playerid, x, y, z);
	return 1;
}

stock SetPlayerInPrison(playerid)
{
	SetPlayerPosEx(playerid, 1543.1105, 1352.2798, 1510.9160 + 0.3);
	SetPlayerFacingAngle(playerid, 90.9191);

	SetCameraBehindPlayer(playerid);
}

stock ViewCharges(playerid, name[])
{
	new
	    string[128];

	format(string, sizeof(string), "SELECT * FROM `warrants` WHERE `Suspect` = '%s' ORDER BY `ID` DESC", SQL_ReturnEscaped(name));
	mysql_tquery(g_iHandle, string, "OnViewCharges", "ds", playerid, name);
	return 1;
}

stock AddWarrant(targetid, playerid, const description[])
{
	new
	    string[255];

	format(string, sizeof(string), "INSERT INTO `warrants` (`Suspect`, `Username`, `Date`, `Description`) VALUES('%s', '%s', '%s', '%s')", ReturnName(targetid), ReturnName(playerid), ReturnDate(), SQL_ReturnEscaped(description));
	mysql_tquery(g_iHandle, string);
}

stock GetPlayerLocationEx(playerid, &Float:fX, &Float:fY, &Float:fZ)
{
	new
	    id = -1;

    if ((id = House_Inside(playerid)) != -1)
	{
		fX = HouseData[id][housePos][0];
		fY = HouseData[id][housePos][1];
		fZ = HouseData[id][housePos][2];
	}
	else if ((id = Business_Inside(playerid)) != -1)
	{
		fX = BusinessData[id][bizPos][0];
		fY = BusinessData[id][bizPos][1];
		fZ = BusinessData[id][bizPos][2];
	}
	else if ((id = Entrance_Inside(playerid)) != -1)
	{
		fX = EntranceData[id][entrancePos][0];
		fY = EntranceData[id][entrancePos][1];
		fZ = EntranceData[id][entrancePos][2];
	}
	else GetPlayerPos(playerid, fX, fY, fZ);
	return 1;
}

stock GetPlayerLocation(playerid)
{
	new
	    Float:fX,
	    Float:fY,
		Float:fZ,
		string[32],
		id = -1;

	if ((id = House_Inside(playerid)) != -1)
	{
		fX = HouseData[id][housePos][0];
		fY = HouseData[id][housePos][1];
		fZ = HouseData[id][housePos][2];
	}
	else if ((id = Business_Inside(playerid)) != -1)
	{
		fX = BusinessData[id][bizPos][0];
		fY = BusinessData[id][bizPos][1];
		fZ = BusinessData[id][bizPos][2];
	}
	else if ((id = Entrance_Inside(playerid)) != -1)
	{
		fX = EntranceData[id][entrancePos][0];
		fY = EntranceData[id][entrancePos][1];
		fZ = EntranceData[id][entrancePos][2];
	}
	else GetPlayerPos(playerid, fX, fY, fZ);

	format(string, 32, GetLocation(fX, fY, fZ));
	return string;
}

stock GetLocation(Float:fX, Float:fY, Float:fZ)
{
    enum e_ZoneData
	{
     	e_ZoneName[32 char],
     	Float:e_ZoneArea[6]
	};
	new const g_arrZoneData[][e_ZoneData] =
	{
		{!"The Big Ear", 	              {-410.00, 1403.30, -3.00, -137.90, 1681.20, 200.00}},
		{!"Aldea Malvada",                {-1372.10, 2498.50, 0.00, -1277.50, 2615.30, 200.00}},
		{!"Angel Pine",                   {-2324.90, -2584.20, -6.10, -1964.20, -2212.10, 200.00}},
		{!"Arco del Oeste",               {-901.10, 2221.80, 0.00, -592.00, 2571.90, 200.00}},
		{!"Avispa Country Club",          {-2646.40, -355.40, 0.00, -2270.00, -222.50, 200.00}},
		{!"Avispa Country Club",          {-2831.80, -430.20, -6.10, -2646.40, -222.50, 200.00}},
		{!"Avispa Country Club",          {-2361.50, -417.10, 0.00, -2270.00, -355.40, 200.00}},
		{!"Avispa Country Club",          {-2667.80, -302.10, -28.80, -2646.40, -262.30, 71.10}},
		{!"Avispa Country Club",          {-2470.00, -355.40, 0.00, -2270.00, -318.40, 46.10}},
		{!"Avispa Country Club",          {-2550.00, -355.40, 0.00, -2470.00, -318.40, 39.70}},
		{!"Back o Beyond",                {-1166.90, -2641.10, 0.00, -321.70, -1856.00, 200.00}},
		{!"Battery Point",                {-2741.00, 1268.40, -4.50, -2533.00, 1490.40, 200.00}},
		{!"Bayside",                      {-2741.00, 2175.10, 0.00, -2353.10, 2722.70, 200.00}},
		{!"Bayside Marina",               {-2353.10, 2275.70, 0.00, -2153.10, 2475.70, 200.00}},
		{!"Beacon Hill",                  {-399.60, -1075.50, -1.40, -319.00, -977.50, 198.50}},
		{!"Blackfield",                   {964.30, 1203.20, -89.00, 1197.30, 1403.20, 110.90}},
		{!"Blackfield",                   {964.30, 1403.20, -89.00, 1197.30, 1726.20, 110.90}},
		{!"Blackfield Chapel",            {1375.60, 596.30, -89.00, 1558.00, 823.20, 110.90}},
		{!"Blackfield Chapel",            {1325.60, 596.30, -89.00, 1375.60, 795.00, 110.90}},
		{!"Blackfield Intersection",      {1197.30, 1044.60, -89.00, 1277.00, 1163.30, 110.90}},
		{!"Blackfield Intersection",      {1166.50, 795.00, -89.00, 1375.60, 1044.60, 110.90}},
		{!"Blackfield Intersection",      {1277.00, 1044.60, -89.00, 1315.30, 1087.60, 110.90}},
		{!"Blackfield Intersection",      {1375.60, 823.20, -89.00, 1457.30, 919.40, 110.90}},
		{!"Blueberry",                    {104.50, -220.10, 2.30, 349.60, 152.20, 200.00}},
		{!"Blueberry",                    {19.60, -404.10, 3.80, 349.60, -220.10, 200.00}},
		{!"Blueberry Acres",              {-319.60, -220.10, 0.00, 104.50, 293.30, 200.00}},
		{!"Caligula's Palace",            {2087.30, 1543.20, -89.00, 2437.30, 1703.20, 110.90}},
		{!"Caligula's Palace",            {2137.40, 1703.20, -89.00, 2437.30, 1783.20, 110.90}},
		{!"Calton Heights",               {-2274.10, 744.10, -6.10, -1982.30, 1358.90, 200.00}},
		{!"Chinatown",                    {-2274.10, 578.30, -7.60, -2078.60, 744.10, 200.00}},
		{!"City Hall",                    {-2867.80, 277.40, -9.10, -2593.40, 458.40, 200.00}},
		{!"Come-A-Lot",                   {2087.30, 943.20, -89.00, 2623.10, 1203.20, 110.90}},
		{!"Commerce",                     {1323.90, -1842.20, -89.00, 1701.90, -1722.20, 110.90}},
		{!"Commerce",                     {1323.90, -1722.20, -89.00, 1440.90, -1577.50, 110.90}},
		{!"Commerce",                     {1370.80, -1577.50, -89.00, 1463.90, -1384.90, 110.90}},
		{!"Commerce",                     {1463.90, -1577.50, -89.00, 1667.90, -1430.80, 110.90}},
		{!"Commerce",                     {1583.50, -1722.20, -89.00, 1758.90, -1577.50, 110.90}},
		{!"Commerce",                     {1667.90, -1577.50, -89.00, 1812.60, -1430.80, 110.90}},
		{!"Conference Center",            {1046.10, -1804.20, -89.00, 1323.90, -1722.20, 110.90}},
		{!"Conference Center",            {1073.20, -1842.20, -89.00, 1323.90, -1804.20, 110.90}},
		{!"Cranberry Station",            {-2007.80, 56.30, 0.00, -1922.00, 224.70, 100.00}},
		{!"Creek",                        {2749.90, 1937.20, -89.00, 2921.60, 2669.70, 110.90}},
		{!"Dillimore",                    {580.70, -674.80, -9.50, 861.00, -404.70, 200.00}},
		{!"Doherty",                      {-2270.00, -324.10, -0.00, -1794.90, -222.50, 200.00}},
		{!"Doherty",                      {-2173.00, -222.50, -0.00, -1794.90, 265.20, 200.00}},
		{!"Downtown",                     {-1982.30, 744.10, -6.10, -1871.70, 1274.20, 200.00}},
		{!"Downtown",                     {-1871.70, 1176.40, -4.50, -1620.30, 1274.20, 200.00}},
		{!"Downtown",                     {-1700.00, 744.20, -6.10, -1580.00, 1176.50, 200.00}},
		{!"Downtown",                     {-1580.00, 744.20, -6.10, -1499.80, 1025.90, 200.00}},
		{!"Downtown",                     {-2078.60, 578.30, -7.60, -1499.80, 744.20, 200.00}},
		{!"Downtown",                     {-1993.20, 265.20, -9.10, -1794.90, 578.30, 200.00}},
		{!"Downtown Los Santos",          {1463.90, -1430.80, -89.00, 1724.70, -1290.80, 110.90}},
		{!"Downtown Los Santos",          {1724.70, -1430.80, -89.00, 1812.60, -1250.90, 110.90}},
		{!"Downtown Los Santos",          {1463.90, -1290.80, -89.00, 1724.70, -1150.80, 110.90}},
		{!"Downtown Los Santos",          {1370.80, -1384.90, -89.00, 1463.90, -1170.80, 110.90}},
		{!"Downtown Los Santos",          {1724.70, -1250.90, -89.00, 1812.60, -1150.80, 110.90}},
		{!"Downtown Los Santos",          {1370.80, -1170.80, -89.00, 1463.90, -1130.80, 110.90}},
		{!"Downtown Los Santos",          {1378.30, -1130.80, -89.00, 1463.90, -1026.30, 110.90}},
		{!"Downtown Los Santos",          {1391.00, -1026.30, -89.00, 1463.90, -926.90, 110.90}},
		{!"Downtown Los Santos",          {1507.50, -1385.20, 110.90, 1582.50, -1325.30, 335.90}},
		{!"East Beach",                   {2632.80, -1852.80, -89.00, 2959.30, -1668.10, 110.90}},
		{!"East Beach",                   {2632.80, -1668.10, -89.00, 2747.70, -1393.40, 110.90}},
		{!"East Beach",                   {2747.70, -1668.10, -89.00, 2959.30, -1498.60, 110.90}},
		{!"East Beach",                   {2747.70, -1498.60, -89.00, 2959.30, -1120.00, 110.90}},
		{!"East Los Santos",              {2421.00, -1628.50, -89.00, 2632.80, -1454.30, 110.90}},
		{!"East Los Santos",              {2222.50, -1628.50, -89.00, 2421.00, -1494.00, 110.90}},
		{!"East Los Santos",              {2266.20, -1494.00, -89.00, 2381.60, -1372.00, 110.90}},
		{!"East Los Santos",              {2381.60, -1494.00, -89.00, 2421.00, -1454.30, 110.90}},
		{!"East Los Santos",              {2281.40, -1372.00, -89.00, 2381.60, -1135.00, 110.90}},
		{!"East Los Santos",              {2381.60, -1454.30, -89.00, 2462.10, -1135.00, 110.90}},
		{!"East Los Santos",              {2462.10, -1454.30, -89.00, 2581.70, -1135.00, 110.90}},
		{!"Easter Basin",                 {-1794.90, 249.90, -9.10, -1242.90, 578.30, 200.00}},
		{!"Easter Basin",                 {-1794.90, -50.00, -0.00, -1499.80, 249.90, 200.00}},
		{!"Easter Bay Airport",           {-1499.80, -50.00, -0.00, -1242.90, 249.90, 200.00}},
		{!"Easter Bay Airport",           {-1794.90, -730.10, -3.00, -1213.90, -50.00, 200.00}},
		{!"Easter Bay Airport",           {-1213.90, -730.10, 0.00, -1132.80, -50.00, 200.00}},
		{!"Easter Bay Airport",           {-1242.90, -50.00, 0.00, -1213.90, 578.30, 200.00}},
		{!"Easter Bay Airport",           {-1213.90, -50.00, -4.50, -947.90, 578.30, 200.00}},
		{!"Easter Bay Airport",           {-1315.40, -405.30, 15.40, -1264.40, -209.50, 25.40}},
		{!"Easter Bay Airport",           {-1354.30, -287.30, 15.40, -1315.40, -209.50, 25.40}},
		{!"Easter Bay Airport",           {-1490.30, -209.50, 15.40, -1264.40, -148.30, 25.40}},
		{!"Easter Bay Chemicals",         {-1132.80, -768.00, 0.00, -956.40, -578.10, 200.00}},
		{!"Easter Bay Chemicals",         {-1132.80, -787.30, 0.00, -956.40, -768.00, 200.00}},
		{!"El Castillo del Diablo",       {-464.50, 2217.60, 0.00, -208.50, 2580.30, 200.00}},
		{!"El Castillo del Diablo",       {-208.50, 2123.00, -7.60, 114.00, 2337.10, 200.00}},
		{!"El Castillo del Diablo",       {-208.50, 2337.10, 0.00, 8.40, 2487.10, 200.00}},
		{!"El Corona",                    {1812.60, -2179.20, -89.00, 1970.60, -1852.80, 110.90}},
		{!"El Corona",                    {1692.60, -2179.20, -89.00, 1812.60, -1842.20, 110.90}},
		{!"El Quebrados",                 {-1645.20, 2498.50, 0.00, -1372.10, 2777.80, 200.00}},
		{!"Esplanade East",               {-1620.30, 1176.50, -4.50, -1580.00, 1274.20, 200.00}},
		{!"Esplanade East",               {-1580.00, 1025.90, -6.10, -1499.80, 1274.20, 200.00}},
		{!"Esplanade East",               {-1499.80, 578.30, -79.60, -1339.80, 1274.20, 20.30}},
		{!"Esplanade North",              {-2533.00, 1358.90, -4.50, -1996.60, 1501.20, 200.00}},
		{!"Esplanade North",              {-1996.60, 1358.90, -4.50, -1524.20, 1592.50, 200.00}},
		{!"Esplanade North",              {-1982.30, 1274.20, -4.50, -1524.20, 1358.90, 200.00}},
		{!"Fallen Tree",                  {-792.20, -698.50, -5.30, -452.40, -380.00, 200.00}},
		{!"Fallow Bridge",                {434.30, 366.50, 0.00, 603.00, 555.60, 200.00}},
		{!"Fern Ridge",                   {508.10, -139.20, 0.00, 1306.60, 119.50, 200.00}},
		{!"Financial",                    {-1871.70, 744.10, -6.10, -1701.30, 1176.40, 300.00}},
		{!"Fisher's Lagoon",              {1916.90, -233.30, -100.00, 2131.70, 13.80, 200.00}},
		{!"Flint Intersection",           {-187.70, -1596.70, -89.00, 17.00, -1276.60, 110.90}},
		{!"Flint Range",                  {-594.10, -1648.50, 0.00, -187.70, -1276.60, 200.00}},
		{!"Fort Carson",                  {-376.20, 826.30, -3.00, 123.70, 1220.40, 200.00}},
		{!"Foster Valley",                {-2270.00, -430.20, -0.00, -2178.60, -324.10, 200.00}},
		{!"Foster Valley",                {-2178.60, -599.80, -0.00, -1794.90, -324.10, 200.00}},
		{!"Foster Valley",                {-2178.60, -1115.50, 0.00, -1794.90, -599.80, 200.00}},
		{!"Foster Valley",                {-2178.60, -1250.90, 0.00, -1794.90, -1115.50, 200.00}},
		{!"Frederick Bridge",             {2759.20, 296.50, 0.00, 2774.20, 594.70, 200.00}},
		{!"Gant Bridge",                  {-2741.40, 1659.60, -6.10, -2616.40, 2175.10, 200.00}},
		{!"Gant Bridge",                  {-2741.00, 1490.40, -6.10, -2616.40, 1659.60, 200.00}},
		{!"Ganton",                       {2222.50, -1852.80, -89.00, 2632.80, -1722.30, 110.90}},
		{!"Ganton",                       {2222.50, -1722.30, -89.00, 2632.80, -1628.50, 110.90}},
		{!"Garcia",                       {-2411.20, -222.50, -0.00, -2173.00, 265.20, 200.00}},
		{!"Garcia",                       {-2395.10, -222.50, -5.30, -2354.00, -204.70, 200.00}},
		{!"Garver Bridge",                {-1339.80, 828.10, -89.00, -1213.90, 1057.00, 110.90}},
		{!"Garver Bridge",                {-1213.90, 950.00, -89.00, -1087.90, 1178.90, 110.90}},
		{!"Garver Bridge",                {-1499.80, 696.40, -179.60, -1339.80, 925.30, 20.30}},
		{!"Glen Park",                    {1812.60, -1449.60, -89.00, 1996.90, -1350.70, 110.90}},
		{!"Glen Park",                    {1812.60, -1100.80, -89.00, 1994.30, -973.30, 110.90}},
		{!"Glen Park",                    {1812.60, -1350.70, -89.00, 2056.80, -1100.80, 110.90}},
		{!"Green Palms",                  {176.50, 1305.40, -3.00, 338.60, 1520.70, 200.00}},
		{!"Greenglass College",           {964.30, 1044.60, -89.00, 1197.30, 1203.20, 110.90}},
		{!"Greenglass College",           {964.30, 930.80, -89.00, 1166.50, 1044.60, 110.90}},
		{!"Hampton Barns",                {603.00, 264.30, 0.00, 761.90, 366.50, 200.00}},
		{!"Hankypanky Point",             {2576.90, 62.10, 0.00, 2759.20, 385.50, 200.00}},
		{!"Harry Gold Parkway",           {1777.30, 863.20, -89.00, 1817.30, 2342.80, 110.90}},
		{!"Hashbury",                     {-2593.40, -222.50, -0.00, -2411.20, 54.70, 200.00}},
		{!"Hilltop Farm",                 {967.30, -450.30, -3.00, 1176.70, -217.90, 200.00}},
		{!"Hunter Quarry",                {337.20, 710.80, -115.20, 860.50, 1031.70, 203.70}},
		{!"Idlewood",                     {1812.60, -1852.80, -89.00, 1971.60, -1742.30, 110.90}},
		{!"Idlewood",                     {1812.60, -1742.30, -89.00, 1951.60, -1602.30, 110.90}},
		{!"Idlewood",                     {1951.60, -1742.30, -89.00, 2124.60, -1602.30, 110.90}},
		{!"Idlewood",                     {1812.60, -1602.30, -89.00, 2124.60, -1449.60, 110.90}},
		{!"Idlewood",                     {2124.60, -1742.30, -89.00, 2222.50, -1494.00, 110.90}},
		{!"Idlewood",                     {1971.60, -1852.80, -89.00, 2222.50, -1742.30, 110.90}},
		{!"Jefferson",                    {1996.90, -1449.60, -89.00, 2056.80, -1350.70, 110.90}},
		{!"Jefferson",                    {2124.60, -1494.00, -89.00, 2266.20, -1449.60, 110.90}},
		{!"Jefferson",                    {2056.80, -1372.00, -89.00, 2281.40, -1210.70, 110.90}},
		{!"Jefferson",                    {2056.80, -1210.70, -89.00, 2185.30, -1126.30, 110.90}},
		{!"Jefferson",                    {2185.30, -1210.70, -89.00, 2281.40, -1154.50, 110.90}},
		{!"Jefferson",                    {2056.80, -1449.60, -89.00, 2266.20, -1372.00, 110.90}},
		{!"Julius Thruway East",          {2623.10, 943.20, -89.00, 2749.90, 1055.90, 110.90}},
		{!"Julius Thruway East",          {2685.10, 1055.90, -89.00, 2749.90, 2626.50, 110.90}},
		{!"Julius Thruway East",          {2536.40, 2442.50, -89.00, 2685.10, 2542.50, 110.90}},
		{!"Julius Thruway East",          {2625.10, 2202.70, -89.00, 2685.10, 2442.50, 110.90}},
		{!"Julius Thruway North",         {2498.20, 2542.50, -89.00, 2685.10, 2626.50, 110.90}},
		{!"Julius Thruway North",         {2237.40, 2542.50, -89.00, 2498.20, 2663.10, 110.90}},
		{!"Julius Thruway North",         {2121.40, 2508.20, -89.00, 2237.40, 2663.10, 110.90}},
		{!"Julius Thruway North",         {1938.80, 2508.20, -89.00, 2121.40, 2624.20, 110.90}},
		{!"Julius Thruway North",         {1534.50, 2433.20, -89.00, 1848.40, 2583.20, 110.90}},
		{!"Julius Thruway North",         {1848.40, 2478.40, -89.00, 1938.80, 2553.40, 110.90}},
		{!"Julius Thruway North",         {1704.50, 2342.80, -89.00, 1848.40, 2433.20, 110.90}},
		{!"Julius Thruway North",         {1377.30, 2433.20, -89.00, 1534.50, 2507.20, 110.90}},
		{!"Julius Thruway South",         {1457.30, 823.20, -89.00, 2377.30, 863.20, 110.90}},
		{!"Julius Thruway South",         {2377.30, 788.80, -89.00, 2537.30, 897.90, 110.90}},
		{!"Julius Thruway West",          {1197.30, 1163.30, -89.00, 1236.60, 2243.20, 110.90}},
		{!"Julius Thruway West",          {1236.60, 2142.80, -89.00, 1297.40, 2243.20, 110.90}},
		{!"Juniper Hill",                 {-2533.00, 578.30, -7.60, -2274.10, 968.30, 200.00}},
		{!"Juniper Hollow",               {-2533.00, 968.30, -6.10, -2274.10, 1358.90, 200.00}},
		{!"K.A.C.C. Military Fuels",      {2498.20, 2626.50, -89.00, 2749.90, 2861.50, 110.90}},
		{!"Kincaid Bridge",               {-1339.80, 599.20, -89.00, -1213.90, 828.10, 110.90}},
		{!"Kincaid Bridge",               {-1213.90, 721.10, -89.00, -1087.90, 950.00, 110.90}},
		{!"Kincaid Bridge",               {-1087.90, 855.30, -89.00, -961.90, 986.20, 110.90}},
		{!"King's",                       {-2329.30, 458.40, -7.60, -1993.20, 578.30, 200.00}},
		{!"King's",                       {-2411.20, 265.20, -9.10, -1993.20, 373.50, 200.00}},
		{!"King's",                       {-2253.50, 373.50, -9.10, -1993.20, 458.40, 200.00}},
		{!"LVA Freight Depot",            {1457.30, 863.20, -89.00, 1777.40, 1143.20, 110.90}},
		{!"LVA Freight Depot",            {1375.60, 919.40, -89.00, 1457.30, 1203.20, 110.90}},
		{!"LVA Freight Depot",            {1277.00, 1087.60, -89.00, 1375.60, 1203.20, 110.90}},
		{!"LVA Freight Depot",            {1315.30, 1044.60, -89.00, 1375.60, 1087.60, 110.90}},
		{!"LVA Freight Depot",            {1236.60, 1163.40, -89.00, 1277.00, 1203.20, 110.90}},
		{!"Las Barrancas",                {-926.10, 1398.70, -3.00, -719.20, 1634.60, 200.00}},
		{!"Las Brujas",                   {-365.10, 2123.00, -3.00, -208.50, 2217.60, 200.00}},
		{!"Las Colinas",                  {1994.30, -1100.80, -89.00, 2056.80, -920.80, 110.90}},
		{!"Las Colinas",                  {2056.80, -1126.30, -89.00, 2126.80, -920.80, 110.90}},
		{!"Las Colinas",                  {2185.30, -1154.50, -89.00, 2281.40, -934.40, 110.90}},
		{!"Las Colinas",                  {2126.80, -1126.30, -89.00, 2185.30, -934.40, 110.90}},
		{!"Las Colinas",                  {2747.70, -1120.00, -89.00, 2959.30, -945.00, 110.90}},
		{!"Las Colinas",                  {2632.70, -1135.00, -89.00, 2747.70, -945.00, 110.90}},
		{!"Las Colinas",                  {2281.40, -1135.00, -89.00, 2632.70, -945.00, 110.90}},
		{!"Las Payasadas",                {-354.30, 2580.30, 2.00, -133.60, 2816.80, 200.00}},
		{!"Las Venturas Airport",         {1236.60, 1203.20, -89.00, 1457.30, 1883.10, 110.90}},
		{!"Las Venturas Airport",         {1457.30, 1203.20, -89.00, 1777.30, 1883.10, 110.90}},
		{!"Las Venturas Airport",         {1457.30, 1143.20, -89.00, 1777.40, 1203.20, 110.90}},
		{!"Las Venturas Airport",         {1515.80, 1586.40, -12.50, 1729.90, 1714.50, 87.50}},
		{!"Last Dime Motel",              {1823.00, 596.30, -89.00, 1997.20, 823.20, 110.90}},
		{!"Leafy Hollow",                 {-1166.90, -1856.00, 0.00, -815.60, -1602.00, 200.00}},
		{!"Liberty City",                 {-1000.00, 400.00, 1300.00, -700.00, 600.00, 1400.00}},
		{!"Lil' Probe Inn",               {-90.20, 1286.80, -3.00, 153.80, 1554.10, 200.00}},
		{!"Linden Side",                  {2749.90, 943.20, -89.00, 2923.30, 1198.90, 110.90}},
		{!"Linden Station",               {2749.90, 1198.90, -89.00, 2923.30, 1548.90, 110.90}},
		{!"Linden Station",               {2811.20, 1229.50, -39.50, 2861.20, 1407.50, 60.40}},
		{!"Little Mexico",                {1701.90, -1842.20, -89.00, 1812.60, -1722.20, 110.90}},
		{!"Little Mexico",                {1758.90, -1722.20, -89.00, 1812.60, -1577.50, 110.90}},
		{!"Los Flores",                   {2581.70, -1454.30, -89.00, 2632.80, -1393.40, 110.90}},
		{!"Los Flores",                   {2581.70, -1393.40, -89.00, 2747.70, -1135.00, 110.90}},
		{!"Los Santos International",     {1249.60, -2394.30, -89.00, 1852.00, -2179.20, 110.90}},
		{!"Los Santos International",     {1852.00, -2394.30, -89.00, 2089.00, -2179.20, 110.90}},
		{!"Los Santos International",     {1382.70, -2730.80, -89.00, 2201.80, -2394.30, 110.90}},
		{!"Los Santos International",     {1974.60, -2394.30, -39.00, 2089.00, -2256.50, 60.90}},
		{!"Los Santos International",     {1400.90, -2669.20, -39.00, 2189.80, -2597.20, 60.90}},
		{!"Los Santos International",     {2051.60, -2597.20, -39.00, 2152.40, -2394.30, 60.90}},
		{!"Marina",                       {647.70, -1804.20, -89.00, 851.40, -1577.50, 110.90}},
		{!"Marina",                       {647.70, -1577.50, -89.00, 807.90, -1416.20, 110.90}},
		{!"Marina",                       {807.90, -1577.50, -89.00, 926.90, -1416.20, 110.90}},
		{!"Market",                       {787.40, -1416.20, -89.00, 1072.60, -1310.20, 110.90}},
		{!"Market",                       {952.60, -1310.20, -89.00, 1072.60, -1130.80, 110.90}},
		{!"Market",                       {1072.60, -1416.20, -89.00, 1370.80, -1130.80, 110.90}},
		{!"Market",                       {926.90, -1577.50, -89.00, 1370.80, -1416.20, 110.90}},
		{!"Market Station",               {787.40, -1410.90, -34.10, 866.00, -1310.20, 65.80}},
		{!"Martin Bridge",                {-222.10, 293.30, 0.00, -122.10, 476.40, 200.00}},
		{!"Missionary Hill",              {-2994.40, -811.20, 0.00, -2178.60, -430.20, 200.00}},
		{!"Montgomery",                   {1119.50, 119.50, -3.00, 1451.40, 493.30, 200.00}},
		{!"Montgomery",                   {1451.40, 347.40, -6.10, 1582.40, 420.80, 200.00}},
		{!"Montgomery Intersection",      {1546.60, 208.10, 0.00, 1745.80, 347.40, 200.00}},
		{!"Montgomery Intersection",      {1582.40, 347.40, 0.00, 1664.60, 401.70, 200.00}},
		{!"Mulholland",                   {1414.00, -768.00, -89.00, 1667.60, -452.40, 110.90}},
		{!"Mulholland",                   {1281.10, -452.40, -89.00, 1641.10, -290.90, 110.90}},
		{!"Mulholland",                   {1269.10, -768.00, -89.00, 1414.00, -452.40, 110.90}},
		{!"Mulholland",                   {1357.00, -926.90, -89.00, 1463.90, -768.00, 110.90}},
		{!"Mulholland",                   {1318.10, -910.10, -89.00, 1357.00, -768.00, 110.90}},
		{!"Mulholland",                   {1169.10, -910.10, -89.00, 1318.10, -768.00, 110.90}},
		{!"Mulholland",                   {768.60, -954.60, -89.00, 952.60, -860.60, 110.90}},
		{!"Mulholland",                   {687.80, -860.60, -89.00, 911.80, -768.00, 110.90}},
		{!"Mulholland",                   {737.50, -768.00, -89.00, 1142.20, -674.80, 110.90}},
		{!"Mulholland",                   {1096.40, -910.10, -89.00, 1169.10, -768.00, 110.90}},
		{!"Mulholland",                   {952.60, -937.10, -89.00, 1096.40, -860.60, 110.90}},
		{!"Mulholland",                   {911.80, -860.60, -89.00, 1096.40, -768.00, 110.90}},
		{!"Mulholland",                   {861.00, -674.80, -89.00, 1156.50, -600.80, 110.90}},
		{!"Mulholland Intersection",      {1463.90, -1150.80, -89.00, 1812.60, -768.00, 110.90}},
		{!"North Rock",                   {2285.30, -768.00, 0.00, 2770.50, -269.70, 200.00}},
		{!"Ocean Docks",                  {2373.70, -2697.00, -89.00, 2809.20, -2330.40, 110.90}},
		{!"Ocean Docks",                  {2201.80, -2418.30, -89.00, 2324.00, -2095.00, 110.90}},
		{!"Ocean Docks",                  {2324.00, -2302.30, -89.00, 2703.50, -2145.10, 110.90}},
		{!"Ocean Docks",                  {2089.00, -2394.30, -89.00, 2201.80, -2235.80, 110.90}},
		{!"Ocean Docks",                  {2201.80, -2730.80, -89.00, 2324.00, -2418.30, 110.90}},
		{!"Ocean Docks",                  {2703.50, -2302.30, -89.00, 2959.30, -2126.90, 110.90}},
		{!"Ocean Docks",                  {2324.00, -2145.10, -89.00, 2703.50, -2059.20, 110.90}},
		{!"Ocean Flats",                  {-2994.40, 277.40, -9.10, -2867.80, 458.40, 200.00}},
		{!"Ocean Flats",                  {-2994.40, -222.50, -0.00, -2593.40, 277.40, 200.00}},
		{!"Ocean Flats",                  {-2994.40, -430.20, -0.00, -2831.80, -222.50, 200.00}},
		{!"Octane Springs",               {338.60, 1228.50, 0.00, 664.30, 1655.00, 200.00}},
		{!"Old Venturas Strip",           {2162.30, 2012.10, -89.00, 2685.10, 2202.70, 110.90}},
		{!"Palisades",                    {-2994.40, 458.40, -6.10, -2741.00, 1339.60, 200.00}},
		{!"Palomino Creek",               {2160.20, -149.00, 0.00, 2576.90, 228.30, 200.00}},
		{!"Paradiso",                     {-2741.00, 793.40, -6.10, -2533.00, 1268.40, 200.00}},
		{!"Pershing Square",              {1440.90, -1722.20, -89.00, 1583.50, -1577.50, 110.90}},
		{!"Pilgrim",                      {2437.30, 1383.20, -89.00, 2624.40, 1783.20, 110.90}},
		{!"Pilgrim",                      {2624.40, 1383.20, -89.00, 2685.10, 1783.20, 110.90}},
		{!"Pilson Intersection",          {1098.30, 2243.20, -89.00, 1377.30, 2507.20, 110.90}},
		{!"Pirates in Men's Pants",       {1817.30, 1469.20, -89.00, 2027.40, 1703.20, 110.90}},
		{!"Playa del Seville",            {2703.50, -2126.90, -89.00, 2959.30, -1852.80, 110.90}},
		{!"Prickle Pine",                 {1534.50, 2583.20, -89.00, 1848.40, 2863.20, 110.90}},
		{!"Prickle Pine",                 {1117.40, 2507.20, -89.00, 1534.50, 2723.20, 110.90}},
		{!"Prickle Pine",                 {1848.40, 2553.40, -89.00, 1938.80, 2863.20, 110.90}},
		{!"Prickle Pine",                 {1938.80, 2624.20, -89.00, 2121.40, 2861.50, 110.90}},
		{!"Queens",                       {-2533.00, 458.40, 0.00, -2329.30, 578.30, 200.00}},
		{!"Queens",                       {-2593.40, 54.70, 0.00, -2411.20, 458.40, 200.00}},
		{!"Queens",                       {-2411.20, 373.50, 0.00, -2253.50, 458.40, 200.00}},
		{!"Randolph Industrial Estate",   {1558.00, 596.30, -89.00, 1823.00, 823.20, 110.90}},
		{!"Redsands East",                {1817.30, 2011.80, -89.00, 2106.70, 2202.70, 110.90}},
		{!"Redsands East",                {1817.30, 2202.70, -89.00, 2011.90, 2342.80, 110.90}},
		{!"Redsands East",                {1848.40, 2342.80, -89.00, 2011.90, 2478.40, 110.90}},
		{!"Redsands West",                {1236.60, 1883.10, -89.00, 1777.30, 2142.80, 110.90}},
		{!"Redsands West",                {1297.40, 2142.80, -89.00, 1777.30, 2243.20, 110.90}},
		{!"Redsands West",                {1377.30, 2243.20, -89.00, 1704.50, 2433.20, 110.90}},
		{!"Redsands West",                {1704.50, 2243.20, -89.00, 1777.30, 2342.80, 110.90}},
		{!"Regular Tom",                  {-405.70, 1712.80, -3.00, -276.70, 1892.70, 200.00}},
		{!"Richman",                      {647.50, -1118.20, -89.00, 787.40, -954.60, 110.90}},
		{!"Richman",                      {647.50, -954.60, -89.00, 768.60, -860.60, 110.90}},
		{!"Richman",                      {225.10, -1369.60, -89.00, 334.50, -1292.00, 110.90}},
		{!"Richman",                      {225.10, -1292.00, -89.00, 466.20, -1235.00, 110.90}},
		{!"Richman",                      {72.60, -1404.90, -89.00, 225.10, -1235.00, 110.90}},
		{!"Richman",                      {72.60, -1235.00, -89.00, 321.30, -1008.10, 110.90}},
		{!"Richman",                      {321.30, -1235.00, -89.00, 647.50, -1044.00, 110.90}},
		{!"Richman",                      {321.30, -1044.00, -89.00, 647.50, -860.60, 110.90}},
		{!"Richman",                      {321.30, -860.60, -89.00, 687.80, -768.00, 110.90}},
		{!"Richman",                      {321.30, -768.00, -89.00, 700.70, -674.80, 110.90}},
		{!"Robada Intersection",          {-1119.00, 1178.90, -89.00, -862.00, 1351.40, 110.90}},
		{!"Roca Escalante",               {2237.40, 2202.70, -89.00, 2536.40, 2542.50, 110.90}},
		{!"Roca Escalante",               {2536.40, 2202.70, -89.00, 2625.10, 2442.50, 110.90}},
		{!"Rockshore East",               {2537.30, 676.50, -89.00, 2902.30, 943.20, 110.90}},
		{!"Rockshore West",               {1997.20, 596.30, -89.00, 2377.30, 823.20, 110.90}},
		{!"Rockshore West",               {2377.30, 596.30, -89.00, 2537.30, 788.80, 110.90}},
		{!"Rodeo",                        {72.60, -1684.60, -89.00, 225.10, -1544.10, 110.90}},
		{!"Rodeo",                        {72.60, -1544.10, -89.00, 225.10, -1404.90, 110.90}},
		{!"Rodeo",                        {225.10, -1684.60, -89.00, 312.80, -1501.90, 110.90}},
		{!"Rodeo",                        {225.10, -1501.90, -89.00, 334.50, -1369.60, 110.90}},
		{!"Rodeo",                        {334.50, -1501.90, -89.00, 422.60, -1406.00, 110.90}},
		{!"Rodeo",                        {312.80, -1684.60, -89.00, 422.60, -1501.90, 110.90}},
		{!"Rodeo",                        {422.60, -1684.60, -89.00, 558.00, -1570.20, 110.90}},
		{!"Rodeo",                        {558.00, -1684.60, -89.00, 647.50, -1384.90, 110.90}},
		{!"Rodeo",                        {466.20, -1570.20, -89.00, 558.00, -1385.00, 110.90}},
		{!"Rodeo",                        {422.60, -1570.20, -89.00, 466.20, -1406.00, 110.90}},
		{!"Rodeo",                        {466.20, -1385.00, -89.00, 647.50, -1235.00, 110.90}},
		{!"Rodeo",                        {334.50, -1406.00, -89.00, 466.20, -1292.00, 110.90}},
		{!"Royal Casino",                 {2087.30, 1383.20, -89.00, 2437.30, 1543.20, 110.90}},
		{!"San Andreas Sound",            {2450.30, 385.50, -100.00, 2759.20, 562.30, 200.00}},
		{!"Santa Flora",                  {-2741.00, 458.40, -7.60, -2533.00, 793.40, 200.00}},
		{!"Santa Maria Beach",            {342.60, -2173.20, -89.00, 647.70, -1684.60, 110.90}},
		{!"Santa Maria Beach",            {72.60, -2173.20, -89.00, 342.60, -1684.60, 110.90}},
		{!"Shady Cabin",                  {-1632.80, -2263.40, -3.00, -1601.30, -2231.70, 200.00}},
		{!"Shady Creeks",                 {-1820.60, -2643.60, -8.00, -1226.70, -1771.60, 200.00}},
		{!"Shady Creeks",                 {-2030.10, -2174.80, -6.10, -1820.60, -1771.60, 200.00}},
		{!"Sobell Rail Yards",            {2749.90, 1548.90, -89.00, 2923.30, 1937.20, 110.90}},
		{!"Spinybed",                     {2121.40, 2663.10, -89.00, 2498.20, 2861.50, 110.90}},
		{!"Starfish Casino",              {2437.30, 1783.20, -89.00, 2685.10, 2012.10, 110.90}},
		{!"Starfish Casino",              {2437.30, 1858.10, -39.00, 2495.00, 1970.80, 60.90}},
		{!"Starfish Casino",              {2162.30, 1883.20, -89.00, 2437.30, 2012.10, 110.90}},
		{!"Temple",                       {1252.30, -1130.80, -89.00, 1378.30, -1026.30, 110.90}},
		{!"Temple",                       {1252.30, -1026.30, -89.00, 1391.00, -926.90, 110.90}},
		{!"Temple",                       {1252.30, -926.90, -89.00, 1357.00, -910.10, 110.90}},
		{!"Temple",                       {952.60, -1130.80, -89.00, 1096.40, -937.10, 110.90}},
		{!"Temple",                       {1096.40, -1130.80, -89.00, 1252.30, -1026.30, 110.90}},
		{!"Temple",                       {1096.40, -1026.30, -89.00, 1252.30, -910.10, 110.90}},
		{!"The Camel's Toe",              {2087.30, 1203.20, -89.00, 2640.40, 1383.20, 110.90}},
		{!"The Clown's Pocket",           {2162.30, 1783.20, -89.00, 2437.30, 1883.20, 110.90}},
		{!"The Emerald Isle",             {2011.90, 2202.70, -89.00, 2237.40, 2508.20, 110.90}},
		{!"The Farm",                     {-1209.60, -1317.10, 114.90, -908.10, -787.30, 251.90}},
		{!"The Four Dragons Casino",      {1817.30, 863.20, -89.00, 2027.30, 1083.20, 110.90}},
		{!"The High Roller",              {1817.30, 1283.20, -89.00, 2027.30, 1469.20, 110.90}},
		{!"The Mako Span",                {1664.60, 401.70, 0.00, 1785.10, 567.20, 200.00}},
		{!"The Panopticon",               {-947.90, -304.30, -1.10, -319.60, 327.00, 200.00}},
		{!"The Pink Swan",                {1817.30, 1083.20, -89.00, 2027.30, 1283.20, 110.90}},
		{!"The Sherman Dam",              {-968.70, 1929.40, -3.00, -481.10, 2155.20, 200.00}},
		{!"The Strip",                    {2027.40, 863.20, -89.00, 2087.30, 1703.20, 110.90}},
		{!"The Strip",                    {2106.70, 1863.20, -89.00, 2162.30, 2202.70, 110.90}},
		{!"The Strip",                    {2027.40, 1783.20, -89.00, 2162.30, 1863.20, 110.90}},
		{!"The Strip",                    {2027.40, 1703.20, -89.00, 2137.40, 1783.20, 110.90}},
		{!"The Visage",                   {1817.30, 1863.20, -89.00, 2106.70, 2011.80, 110.90}},
		{!"The Visage",                   {1817.30, 1703.20, -89.00, 2027.40, 1863.20, 110.90}},
		{!"Unity Station",                {1692.60, -1971.80, -20.40, 1812.60, -1932.80, 79.50}},
		{!"Valle Ocultado",               {-936.60, 2611.40, 2.00, -715.90, 2847.90, 200.00}},
		{!"Verdant Bluffs",               {930.20, -2488.40, -89.00, 1249.60, -2006.70, 110.90}},
		{!"Verdant Bluffs",               {1073.20, -2006.70, -89.00, 1249.60, -1842.20, 110.90}},
		{!"Verdant Bluffs",               {1249.60, -2179.20, -89.00, 1692.60, -1842.20, 110.90}},
		{!"Verdant Meadows",              {37.00, 2337.10, -3.00, 435.90, 2677.90, 200.00}},
		{!"Verona Beach",                 {647.70, -2173.20, -89.00, 930.20, -1804.20, 110.90}},
		{!"Verona Beach",                 {930.20, -2006.70, -89.00, 1073.20, -1804.20, 110.90}},
		{!"Verona Beach",                 {851.40, -1804.20, -89.00, 1046.10, -1577.50, 110.90}},
		{!"Verona Beach",                 {1161.50, -1722.20, -89.00, 1323.90, -1577.50, 110.90}},
		{!"Verona Beach",                 {1046.10, -1722.20, -89.00, 1161.50, -1577.50, 110.90}},
		{!"Vinewood",                     {787.40, -1310.20, -89.00, 952.60, -1130.80, 110.90}},
		{!"Vinewood",                     {787.40, -1130.80, -89.00, 952.60, -954.60, 110.90}},
		{!"Vinewood",                     {647.50, -1227.20, -89.00, 787.40, -1118.20, 110.90}},
		{!"Vinewood",                     {647.70, -1416.20, -89.00, 787.40, -1227.20, 110.90}},
		{!"Whitewood Estates",            {883.30, 1726.20, -89.00, 1098.30, 2507.20, 110.90}},
		{!"Whitewood Estates",            {1098.30, 1726.20, -89.00, 1197.30, 2243.20, 110.90}},
		{!"Willowfield",                  {1970.60, -2179.20, -89.00, 2089.00, -1852.80, 110.90}},
		{!"Willowfield",                  {2089.00, -2235.80, -89.00, 2201.80, -1989.90, 110.90}},
		{!"Willowfield",                  {2089.00, -1989.90, -89.00, 2324.00, -1852.80, 110.90}},
		{!"Willowfield",                  {2201.80, -2095.00, -89.00, 2324.00, -1989.90, 110.90}},
		{!"Willowfield",                  {2541.70, -1941.40, -89.00, 2703.50, -1852.80, 110.90}},
		{!"Willowfield",                  {2324.00, -2059.20, -89.00, 2541.70, -1852.80, 110.90}},
		{!"Willowfield",                  {2541.70, -2059.20, -89.00, 2703.50, -1941.40, 110.90}},
		{!"Yellow Bell Station",          {1377.40, 2600.40, -21.90, 1492.40, 2687.30, 78.00}},
		{!"Los Santos",                   {44.60, -2892.90, -242.90, 2997.00, -768.00, 900.00}},
		{!"Las Venturas",                 {869.40, 596.30, -242.90, 2997.00, 2993.80, 900.00}},
		{!"Bone County",                  {-480.50, 596.30, -242.90, 869.40, 2993.80, 900.00}},
		{!"Tierra Robada",                {-2997.40, 1659.60, -242.90, -480.50, 2993.80, 900.00}},
		{!"Tierra Robada",                {-1213.90, 596.30, -242.90, -480.50, 1659.60, 900.00}},
		{!"San Fierro",                   {-2997.40, -1115.50, -242.90, -1213.90, 1659.60, 900.00}},
		{!"Red County",                   {-1213.90, -768.00, -242.90, 2997.00, 596.30, 900.00}},
		{!"Flint County",                 {-1213.90, -2892.90, -242.90, 44.60, -768.00, 900.00}},
		{!"Whetstone",                    {-2997.40, -2892.90, -242.90, -1213.90, -1115.50, 900.00}}
	};
	new
	    name[32] = "San Andreas";

	for (new i = 0; i != sizeof(g_arrZoneData); i ++) if ((fX >= g_arrZoneData[i][e_ZoneArea][0] && fX <= g_arrZoneData[i][e_ZoneArea][3]) && (fY >= g_arrZoneData[i][e_ZoneArea][1] && fY <= g_arrZoneData[i][e_ZoneArea][4]) && (fZ >= g_arrZoneData[i][e_ZoneArea][2] && fZ <= g_arrZoneData[i][e_ZoneArea][5])) {
		strunpack(name, g_arrZoneData[i][e_ZoneName]);

		break;
	}
	return name;
}

stock Float:GetPlayerDistanceFromPlayer(playerid, targetid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(targetid, x, y, z);
	return GetPlayerDistanceFromPoint(playerid, x, y, z);
}

stock IsPlayerArmed(playerid)
{
	new
	    weapon,
	    ammo;

	for (new i = 0; i < 13; i ++) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

		if (ammo > 0) {
			switch (weapon) {
			    case 1, 2, 4, 6, 8, 9, 15, 22..38: return 1;
			}
		}
	}
	return 0;
}

stock PlayerPlaySoundEx(playerid, sound)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);

	foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 20.0, x, y, z)) {
	    PlayerPlaySound(i, sound, x, y, z);
	}
	return 1;
}

stock GetNearestPlayerInView(playerid, Float:distance = 2.0)
{
	new
	    Float:fAngle,
		Float:fPosX,
		Float:fPosY,
		Float:fPosZ;

	GetPlayerFacingAngle(playerid, fAngle);
	GetPlayerPos(playerid, fPosX, fPosY, fPosZ);

	fPosX += distance * floatsin(-fAngle, degrees);
	fPosY += distance * floatcos(-fAngle, degrees);

	foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 2.0, fPosX, fPosY, fPosZ)) {
	    return i;
	}
	return INVALID_PLAYER_ID;
}

stock CancelCall(playerid)
{
    if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
	{
 		PlayerData[PlayerData[playerid][pCallLine]][pCallLine] = INVALID_PLAYER_ID;
   		PlayerData[PlayerData[playerid][pCallLine]][pIncomingCall] = 0;

		PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
		PlayerData[playerid][pIncomingCall] = 0;
	}
	return 1;
}

stock PlayReloadAnimation(playerid, weaponid)
{
	switch (weaponid)
	{
	    case 22: ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.0, 0, 0, 0, 0, 0);
		case 23: ApplyAnimation(playerid, "SILENCED", "Silence_reload", 4.0, 0, 0, 0, 0, 0);
		case 24: ApplyAnimation(playerid, "PYTHON", "python_reload", 4.0, 0, 0, 0, 0, 0);
		case 25, 27: ApplyAnimation(playerid, "BUDDY", "buddy_reload", 4.0, 0, 0, 0, 0, 0);
		case 26: ApplyAnimation(playerid, "COLT45", "sawnoff_reload", 4.0, 0, 0, 0, 0, 0);
		case 29..31, 33, 34: ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.0, 0, 0, 0, 0, 0);
		case 28, 32: ApplyAnimation(playerid, "TEC", "tec_reload", 4.0, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock LeaveTaxi(playerid, driverid)
{
	if (driverid != INVALID_PLAYER_ID && IsPlayerConnected(driverid))
	{
	    GiveMoney(playerid, -PlayerData[playerid][pTaxiFee]);

		AddPlayerSalary(driverid, "Taxi", PlayerData[playerid][pTaxiFee]);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s to the taxi driver.", ReturnName(playerid, 0), FormatNumber(PlayerData[playerid][pTaxiFee]));

	    PlayerData[playerid][pTaxiFee] = 0;
	    PlayerData[playerid][pTaxiTime] = 0;
	    PlayerData[playerid][pTaxiPlayer] = INVALID_PLAYER_ID;
	}
	return 1;
}

stock IsFurnitureItem(item[])
{
    for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (!strcmp(g_aFurnitureData[i][e_FurnitureName], item)) {
        return 1;
	}
	return 0;
}

stock GetFurnitureNameByModel(model)
{
	new
	    name[32];

	for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (g_aFurnitureData[i][e_FurnitureModel] == model) {
		strcat(name, g_aFurnitureData[i][e_FurnitureName]);

		break;
	}
	return name;
}

stock PlayerHasWeapon(playerid, weaponid)
{
	new
	    weapon,
	    ammo;

	for (new i = 0; i < 13; i ++) if (PlayerData[playerid][pGuns][i] == weaponid) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon == weaponid && ammo > 0) return 1;
	}
	return 0;
}

stock IsPumpOccupied(pumpid)
{
	foreach (new i : Player) if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID) {
	    if (PlayerData[i][pGasPump] == pumpid) return 1;
	}
	return 0;
}

stock IsWheelModel(modelid)
{
    switch (modelid) {
		case 1025, 1073..1085, 1096..1098: return 1;
	}
    return 0;
}

stock IsNOSCompatible(modelid)
{
	switch (modelid) {
	    case 581, 523, 462, 521, 463, 522, 461, 448, 468, 586, 509, 481, 510, 472, 473, 493, 595, 484, 430, 453, 452, 446, 454, 590, 569, 537, 538, 570, 449: return 0;
	}
    return 1;
}

stock IsLegalComponent(modelid, componentid)
{
    if (IsWheelModel(componentid) || (1086 <= componentid <= 1087) || (componentid >= 1008 && componentid <= 1010))
	{
	    if (!IsNOSCompatible(modelid))
			return 1;
    }
	else
	{
	    for (new i = 0; i < sizeof(g_aLegalMods); i ++)
	    {
	        if (g_aLegalMods[i][0] != modelid)
				continue;

			else for (new l = 1; l < 22; l ++) if (g_aLegalMods[i][l] == componentid) {
			    return 1;
			}
		}
	}
	return 0;
}

stock Car_GetRealID(carid)
{
	if (carid == -1 || !CarData[carid][carExists] || CarData[carid][carVehicle] == INVALID_VEHICLE_ID)
	    return INVALID_VEHICLE_ID;

	return CarData[carid][carVehicle];
}

stock Car_GetID(vehicleid)
{
	for (new i = 0; i != MAX_DYNAMIC_CARS; i ++) if (CarData[i][carExists] && CarData[i][carVehicle] == vehicleid) {
	    return i;
	}
	return -1;
}

stock Car_Spawn(carid)
{
	if (carid != -1 && CarData[carid][carExists])
	{
		if(IsValidVehicle(CarData[carid][carVehicle])) DestroyVehicle(CarData[carid][carVehicle]);

		if (CarData[carid][carColor1] == -1)
		    CarData[carid][carColor1] = random(127);

		if (CarData[carid][carColor2] == -1)
		    CarData[carid][carColor2] = random(127);

		if(CarData[carid][carSiren] == 0)
		{
			CarData[carid][carVehicle] = CreateVehicle(CarData[carid][carModel], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2], CarData[carid][carPos][3], CarData[carid][carColor1], CarData[carid][carColor2], (CarData[carid][carOwner] != 0) ? (-1) : (1200000));
		}
		else
		{
			CarData[carid][carVehicle] = CreateVehicle(CarData[carid][carModel], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2], CarData[carid][carPos][3], CarData[carid][carColor1], CarData[carid][carColor2], (CarData[carid][carOwner] != 0) ? (-1) : (1200000), 1);
		}

		SetVehicleNumberPlate(CarData[carid][carVehicle], CarData[carid][carPlate]);

        if (CarData[carid][carVehicle] != INVALID_VEHICLE_ID)
        {
			if(CarData[carid][carHealth] < 300.0)
			{
				SetVehicleHealth(CarData[carid][carVehicle], 300.0);
			}
			else
			{
				SetVehicleHealth(CarData[carid][carVehicle], CarData[carid][carHealth]);
			}

            if (CarData[carid][carPaintjob] != -1)
            {
                ChangeVehiclePaintjob(CarData[carid][carVehicle], CarData[carid][carPaintjob]);
			}
			if (CarData[carid][carLocked])
			{
			    new
					engine, lights, alarm, doors, bonnet, boot, objective;

				GetVehicleParamsEx(CarData[carid][carVehicle], engine, lights, alarm, doors, bonnet, boot, objective);
			    SetVehicleParamsEx(CarData[carid][carVehicle], engine, lights, alarm, 1, bonnet, boot, objective);
			}
			for (new i = 0; i < 14; i ++)
			{
			    if (CarData[carid][carMods][i]) AddVehicleComponent(CarData[carid][carVehicle], CarData[carid][carMods][i]);
			}
   			ResetVehicle(CarData[carid][carVehicle]);
			return 1;
		}
	}
	return 0;
}

stock IsVehicleSeatUsed(vehicleid, seat)
{
	foreach (new i : Player) if (IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seat) {
	    return 1;
	}
	return 0;
}

stock RemoveFromVehicle(playerid)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		static
		    Float:fX,
	    	Float:fY,
	    	Float:fZ;

		GetPlayerPos(playerid, fX, fY, fZ);
		SetPlayerPos(playerid, fX, fY, fZ + 1.5);
	}
	return 1;
}

stock GetAvailableSeat(vehicleid, start = 1)
{
	new seats = GetVehicleMaxSeats(vehicleid);

	for (new i = start; i < seats; i ++) if (!IsVehicleSeatUsed(vehicleid, i)) {
	    return i;
	}
	return -1;
}

stock GetVehicleFromBehind(vehicleid)
{
	static
	    Float:fCoords[7];

	GetVehiclePos(vehicleid, fCoords[0], fCoords[1], fCoords[2]);
	GetVehicleZAngle(vehicleid, fCoords[3]);

	for (new i = 1; i != MAX_VEHICLES; i ++) if (i != vehicleid && GetVehiclePos(i, fCoords[4], fCoords[5], fCoords[6]))
	{
		if (floatabs(fCoords[0] - fCoords[4]) < 6 && floatabs(fCoords[1] - fCoords[5]) < 6 && floatabs(fCoords[2] - fCoords[6]) < 6)
			return i;
	}
	return INVALID_VEHICLE_ID;
}

stock GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	static
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] - (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] - (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

stock GetVehicleHood(vehicleid, &Float:x, &Float:y, &Float:z)
{
    if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	static
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] + (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

stock IsNearFactionLocker(playerid)
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1)
	    return 0;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2]) && GetPlayerInterior(playerid) == FactionData[factionid][factionLockerInt] && GetPlayerVirtualWorld(playerid) == FactionData[factionid][factionLockerWorld])
	    return 1;

	return 0;
}

stock IsNearFactionLeaderLocker(playerid)
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1)
	    return 0;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, FactionData[factionid][factionLeaderLockerPos][0], FactionData[factionid][factionLeaderLockerPos][1], FactionData[factionid][factionLeaderLockerPos][2]) && GetPlayerInterior(playerid) == FactionData[factionid][factionLockerInt] && GetPlayerVirtualWorld(playerid) == FactionData[factionid][factionLockerWorld])
	    return 1;

	return 0;
}

stock GetFactionByID(sqlid)
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists] && FactionData[i][factionID] == sqlid)
	    return i;

	return -1;
}

stock Faction_SaveRanks(factionid)
{
	static
	    query[768];

	format(query, sizeof(query), "UPDATE `factions` SET `factionRank1` = '%s', `factionRank2` = '%s', `factionRank3` = '%s', `factionRank4` = '%s', `factionRank5` = '%s', `factionRank6` = '%s', `factionRank7` = '%s', `factionRank8` = '%s', `factionRank9` = '%s', `factionRank10` = '%s', `factionRank11` = '%s', `factionRank12` = '%s', `factionRank13` = '%s', `factionRank14` = '%s', `factionRank15` = '%s' WHERE `factionID` = '%d'",
	    FactionRanks[factionid][0],
	    FactionRanks[factionid][1],
	    FactionRanks[factionid][2],
	    FactionRanks[factionid][3],
	    FactionRanks[factionid][4],
	    FactionRanks[factionid][5],
	    FactionRanks[factionid][6],
	    FactionRanks[factionid][7],
	    FactionRanks[factionid][8],
	    FactionRanks[factionid][9],
	    FactionRanks[factionid][10],
	    FactionRanks[factionid][11],
	    FactionRanks[factionid][12],
	    FactionRanks[factionid][13],
	    FactionRanks[factionid][14],
	    FactionData[factionid][factionID]
	);
	return mysql_tquery(g_iHandle, query);
}

stock GetFactionType(playerid)
{
	if (PlayerData[playerid][pFaction] == -1)
	    return 0;

	return (FactionData[PlayerData[playerid][pFaction]][factionType]);
}

stock Business_RemoveCars(bizid)
{
	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizType] == 5)
	{
	    static
	        string[32];

		for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
		{
  			DealershipCars[bizid][i][vehModel] = 0;
    		DealershipCars[bizid][i][vehPrice] = 0;
		}
		format(string, sizeof(string), "DELETE FROM `dealervehicles` WHERE `ID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(g_iHandle, string);
	}
	return 1;
}

stock Business_RemovePumps(bizid)
{
	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizType] == 6)
	{
	    static
	        string[32];

	    foreach (new i : Player) if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID && PlayerData[i][pGasStation] == bizid)
	    {
	        StopRefilling(i);
	    }
		for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && PumpData[i][pumpBusiness] == bizid)
		{
  			DestroyDynamicObject(PumpData[i][pumpObject]);
			DestroyDynamic3DTextLabel(PumpData[i][pumpText3D]);

		    PumpData[i][pumpExists] = 0;
		    PumpData[i][pumpFuel] = 0;
		}
		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `ID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(g_iHandle, string);
	}
	return 1;
}

stock Inventory_Clear(playerid)
{
	static
	    string[64];

	for (new i = 0; i < MAX_INVENTORY; i ++)
	{
	    if (InventoryData[playerid][i][invExists])
	    {
	        InventoryData[playerid][i][invExists] = 0;
	        InventoryData[playerid][i][invModel] = 0;
	        InventoryData[playerid][i][invQuantity] = 0;
		}
	}
	format(string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	return mysql_tquery(g_iHandle, string);
}

stock Inventory_Set(playerid, item[], model, amount)
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid == -1 && amount > 0)
		Inventory_Add(playerid, item, model, amount);

	else if (amount > 0 && itemid != -1)
	    Inventory_SetQuantity(playerid, item, amount);

	else if (amount < 1 && itemid != -1)
	    Inventory_Remove(playerid, item, -1);

	return 1;
}

stock Inventory_GetItemID(playerid, item[])
{
	for (new i = 0; i < MAX_INVENTORY; i ++)
	{
	    if (!InventoryData[playerid][i][invExists])
	        continue;

		if (!strcmp(InventoryData[playerid][i][invItem], item)) return i;
	}
	return -1;
}

stock Inventory_GetFreeID(playerid)
{
	if (Inventory_Items(playerid) >= PlayerData[playerid][pCapacity])
		return -1;

	for (new i = 0; i < MAX_INVENTORY; i ++)
	{
	    if (!InventoryData[playerid][i][invExists])
	        return i;
	}
	return -1;
}

stock Inventory_Items(playerid)
{
    new count;

    for (new i = 0; i != MAX_INVENTORY; i ++) if (InventoryData[playerid][i][invExists]) {
        count++;
	}
	return count;
}

stock Inventory_Count(playerid, item[])
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid != -1)
	    return InventoryData[playerid][itemid][invQuantity];

	return 0;
}

stock Inventory_HasItem(playerid, item[])
{
	return (Inventory_GetItemID(playerid, item) != -1);
}

stock Inventory_SetQuantity(playerid, item[], quantity)
{
	new
	    itemid = Inventory_GetItemID(playerid, item),
	    string[128];

	if (itemid != -1)
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(g_iHandle, string);

	    InventoryData[playerid][itemid][invQuantity] = quantity;
	}
	return 1;
}

stock Inventory_Add(playerid, item[], model, quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = Inventory_GetFreeID(playerid);

	    if (itemid != -1)
	    {
	        InventoryData[playerid][itemid][invExists] = true;
	        InventoryData[playerid][itemid][invModel] = model;
	        InventoryData[playerid][itemid][invQuantity] = quantity;

	        strpack(InventoryData[playerid][itemid][invItem], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `inventory` (`ID`, `invItem`, `invModel`, `invQuantity`) VALUES('%d', '%s', '%d', '%d')", PlayerData[playerid][pID], item, model, quantity);
			mysql_tquery(g_iHandle, string, "OnInventoryAdd", "dd", playerid, itemid);
	        return itemid;
		}
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` + %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(g_iHandle, string);

	    InventoryData[playerid][itemid][invQuantity] += quantity;
	}
	return itemid;
}

stock Inventory_Remove(playerid, item[], quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

	if (itemid != -1)
	{
	    if (InventoryData[playerid][itemid][invQuantity] > 0)
	    {
	        InventoryData[playerid][itemid][invQuantity] -= quantity;
		}
		if (quantity == -1 || InventoryData[playerid][itemid][invQuantity] < 1)
		{
		    InventoryData[playerid][itemid][invExists] = false;
		    InventoryData[playerid][itemid][invModel] = 0;
		    InventoryData[playerid][itemid][invQuantity] = 0;

		    format(string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d' AND `invID` = '%d'", PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	        mysql_tquery(g_iHandle, string);
		}
		else if (quantity != -1 && InventoryData[playerid][itemid][invQuantity] > 0)
		{
			format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` - %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
            mysql_tquery(g_iHandle, string);
		}
		return 1;
	}
	return 0;
}

stock RemoveAlpha(color) {
    return (color & ~0xFF);
}

stock CancelDrivingTest(playerid)
{
	if (PlayerData[playerid][pDrivingTest])
	{
 		SetPlayerPosEx(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
 		SetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

  		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
  		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);

		DisablePlayerCheckpoint(playerid);
  		SetCameraBehindPlayer(playerid);

		DestroyVehicle(PlayerData[playerid][pTestCar]);

  		PlayerData[playerid][pDrivingTest] = false;
	}
	return 1;
}

stock House_WeaponStorage(playerid, houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[320];

	string[0] = 0;

	for (new i = 0; i < 10; i ++)
	{
	    if (!HouseData[houseid][houseWeapons][i])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
			format(string, sizeof(string), "%s%s (Ammo: %d)\n", string, ReturnWeaponName(HouseData[houseid][houseWeapons][i]), HouseData[houseid][houseAmmo][i]);
	}
	Dialog_Show(playerid, HouseWeapons, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
	return 1;
}

stock House_ShowItems(playerid, houseid)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[MAX_HOUSE_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else {
			strunpack(name, HouseStorage[houseid][i][hItemName]);

			if (HouseStorage[houseid][i][hItemQuantity] == 1) {
			    format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, HouseStorage[houseid][i][hItemQuantity]);
		}
	}
	Dialog_Show(playerid, HouseItems, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
	return 1;
}

stock House_OpenStorage(playerid, houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		items[2],
		string[MAX_HOUSE_STORAGE * 32];

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++) if (HouseStorage[houseid][i][hItemExists]) {
	    items[0]++;
	}
	for (new i = 0; i < 10; i ++) if (HouseData[houseid][houseWeapons][i]) {
	    items[1]++;
	}
	format(string, sizeof(string), "Item Storage (%d/%d)\nWeapon Storage (%d/10)\nMoney Safe (%s)", items[0], MAX_HOUSE_STORAGE, items[1], FormatNumber(HouseData[houseid][houseMoney]));
	Dialog_Show(playerid, HouseStorage, DIALOG_STYLE_LIST, "House Storage", string, "Select", "Cancel");
	return 1;
}

stock House_GetItemID(houseid, item[])
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        continue;

		if (!strcmp(HouseStorage[houseid][i][hItemName], item)) return i;
	}
	return -1;
}

stock House_GetFreeID(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        return i;
	}
	return -1;
}

stock House_AddItem(houseid, item[], model, quantity = 1, slotid = -1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = House_GetFreeID(houseid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        HouseStorage[houseid][itemid][hItemExists] = true;
	        HouseStorage[houseid][itemid][hItemModel] = model;
	        HouseStorage[houseid][itemid][hItemQuantity] = quantity;

	        strpack(HouseStorage[houseid][itemid][hItemName], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `housestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", HouseData[houseid][houseID], item, model, quantity);
			mysql_tquery(g_iHandle, string, "OnStorageAdd", "dd", houseid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	    mysql_tquery(g_iHandle, string);

	    HouseStorage[houseid][itemid][hItemQuantity] += quantity;
	}
	return itemid;
}

stock House_RemoveItem(houseid, item[], quantity = 1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid != -1)
	{
	    if (HouseStorage[houseid][itemid][hItemQuantity] > 0)
	    {
	        HouseStorage[houseid][itemid][hItemQuantity] -= quantity;
		}
		if (quantity == -1 || HouseStorage[houseid][itemid][hItemQuantity] < 1)
		{
		    HouseStorage[houseid][itemid][hItemExists] = false;
		    HouseStorage[houseid][itemid][hItemModel] = 0;
		    HouseStorage[houseid][itemid][hItemQuantity] = 0;

		    format(string, sizeof(string), "DELETE FROM `housestorage` WHERE `ID` = '%d' AND `itemID` = '%d'", HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	        mysql_tquery(g_iHandle, string);
		}
		else if (quantity != -1 && HouseStorage[houseid][itemid][hItemQuantity] > 0)
		{
			format(string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
            mysql_tquery(g_iHandle, string);
		}
		return 1;
	}
	return 0;
}

stock Car_GetItemID(carid, item[])
{
	if (carid == -1 || !CarData[carid][carExists])
	    return 0;

	for (new i = 0; i < MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[carid][i][cItemExists])
	        continue;

		if (!strcmp(CarStorage[carid][i][cItemName], item)) return i;
	}
	return -1;
}

stock Car_GetFreeID(carid)
{
	if (carid == -1 || !CarData[carid][carExists])
	    return 0;

	for (new i = 0; i < MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[carid][i][cItemExists])
	        return i;
	}
	return -1;
}

stock Car_AddItem(carid, item[], model, quantity = 1, slotid = -1)
{
    if (carid == -1 || !CarData[carid][carExists])
	    return 0;

	new
		itemid = Car_GetItemID(carid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = Car_GetFreeID(carid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        CarStorage[carid][itemid][cItemExists] = true;
	        CarStorage[carid][itemid][cItemModel] = model;
	        CarStorage[carid][itemid][cItemQuantity] = quantity;

	        strpack(CarStorage[carid][itemid][cItemName], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `carstorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", CarData[carid][carID], item, model, quantity);
			mysql_tquery(g_iHandle, string, "OnCarStorageAdd", "dd", carid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `carstorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, CarData[carid][carID], CarStorage[carid][itemid][cItemID]);
	    mysql_tquery(g_iHandle, string);

	    CarStorage[carid][itemid][cItemQuantity] += quantity;
	}
	return itemid;
}

stock Car_RemoveItem(carid, item[], quantity = 1)
{
    if (carid == -1 || !CarData[carid][carExists])
	    return 0;

	new
		itemid = Car_GetItemID(carid, item),
		string[128];

	if (itemid != -1)
	{
	    if (CarStorage[carid][itemid][cItemQuantity] > 0)
	    {
	        CarStorage[carid][itemid][cItemQuantity] -= quantity;
		}
		if (quantity == -1 || CarStorage[carid][itemid][cItemQuantity] < 1)
		{
		    CarStorage[carid][itemid][cItemExists] = false;
		    CarStorage[carid][itemid][cItemModel] = 0;
		    CarStorage[carid][itemid][cItemQuantity] = 0;

		    format(string, sizeof(string), "DELETE FROM `carstorage` WHERE `ID` = '%d' AND `itemID` = '%d'", CarData[carid][carID], CarStorage[carid][itemid][cItemID]);
	        mysql_tquery(g_iHandle, string);
		}
		else if (quantity != -1 && CarStorage[carid][itemid][cItemQuantity] > 0)
		{
			format(string, sizeof(string), "UPDATE `carstorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, CarData[carid][carID], CarStorage[carid][itemid][cItemID]);
            mysql_tquery(g_iHandle, string);
		}
		return 1;
	}
	return 0;
}

stock SetDefaultSpawn(playerid)
{
    SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	if(PlayerData[playerid][pSpawnPoint] == 0) // Airport
	{
	    SetPlayerPos(playerid,1445.1062,-2287.3020,13.5469);
	    SetPlayerFacingAngle(playerid, 0.0);
	}
	if(PlayerData[playerid][pSpawnPoint] == 1) // Faction
	{
	    new faction = PlayerData[playerid][pFactionID];
	    if(PlayerData[playerid][pFactionID] == -1)
	    {
	        SendErrorMessage(playerid, "You've been set to civilian spawn.");
	        SetPlayerPos(playerid,1445.1062,-2287.3020,13.5469);
	    	SetPlayerFacingAngle(playerid, 0.0);
		}
		SetPlayerPos(playerid,FactionData[faction][SpawnX],FactionData[faction][SpawnY],FactionData[faction][SpawnZ]);
		SetPlayerInterior(playerid,FactionData[faction][SpawnInterior]);
		SetPlayerVirtualWorld(playerid, FactionData[faction][SpawnVW]);
	}
	if(PlayerData[playerid][pSpawnPoint] == 2)
	{
	    SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
	    SetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);
	    SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
	}

	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, 1);
	return 1;
}

stock RespawnPlayer(playerid)
{
	if (IsPlayerInAnyVehicle(playerid))
	{
        new
		    Float:x,
		    Float:y,
	    	Float:z;

	    GetPlayerPos(playerid, x, y, z);
	    SetPlayerPos(playerid, x, y, z + 1);
	}
	SpawnPlayer(playerid);
	SetDefaultSpawn(playerid);
	return 1;
}

stock IsPlayerIdle(playerid) {
	new
	    index = GetPlayerAnimationIndex(playerid);

	return ((index == 1275) || (1181 <= index <= 1192));
}

stock IsPlayerNearDynamicObject(playerid, objectid, Float:range = 5.0) {

	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	GetDynamicObjectPos(objectid, fX, fY, fZ);

	return (IsPlayerInRangeOfPoint(playerid, range, fX, fY, fZ));
}

stock IsPlayerSpawned(playerid)
{
	if (playerid < 0 || playerid >= MAX_PLAYERS)
	    return 0;

	return (!PlayerData[playerid][pKilled]) && (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && GetPlayerState(playerid) != PLAYER_STATE_NONE && GetPlayerState(playerid) != PLAYER_STATE_WASTED);
}

stock GetVehicleMaxSeats(vehicleid)
{
    static const g_arrMaxSeats[] = {
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
		1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4, 4,
		2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2,
		4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
		4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 4,
		4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0, 4,
		0, 0
	};
	new
	    model = GetVehicleModel(vehicleid);

	if (400 <= model <= 611)
	    return g_arrMaxSeats[model - 400];

	return 0;
}

stock GetNearestVehicle(playerid)
{
	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && GetVehiclePos(i, fX, fY, fZ))
	{
	    if (IsPlayerInRangeOfPoint(playerid, 3.5, fX, fY, fZ)) return i;
	}
	return INVALID_VEHICLE_ID;
}

stock IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetPlayerPos(targetid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock IsPlayerNearBoot(playerid, vehicleid)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleBoot(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.5, fX, fY, fZ);
}

stock IsPlayerNearHood(playerid, vehicleid)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleHood(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.0, fX, fY, fZ);
}

stock SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius)) {
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius)) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendAdminAlert(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAdminDuty] == 1) {
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (PlayerData[i][pAdmin] >= 1 && PlayerData[i][pAdminDuty] == 1) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendFactionAlert(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (PlayerData[i][pAdmin] >= 1 || PlayerData[i][pFactionMod] > 0) {
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (PlayerData[i][pAdmin] >= 1 || PlayerData[i][pFactionMod] > 0) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendFactionMessageEx(type, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (PlayerData[i][pFaction] != -1 && GetFactionType(i) == type) {
			if (GetFactionType(i) != FACTION_GANG)
			{
				if(PlayerData[i][pOnDuty] == 0) return 1;
				SendClientMessage(i, color, string);
			}
			else SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pFaction] != -1 && GetFactionType(i) == type && PlayerData[i][pOnDuty]) {
 		if (GetFactionType(i) != FACTION_GANG)
		{
			if(PlayerData[i][pOnDuty] == 0) return 1;
			SendClientMessage(i, color, string);
		}
		else SendClientMessage(i, color, string);
	}
	return 1;
}

stock SendFactionMessage(factionid, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (PlayerData[i][pFaction] == factionid) {
			if (GetFactionType(i) != FACTION_GANG)
			{
				if(PlayerData[i][pOnDuty] == 0) return 1;
				SendClientMessage(i, color, string);
			}
			else SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pFaction] == factionid && PlayerData[i][pOnDuty]) {
 		if (GetFactionType(i) != FACTION_GANG)
		{
			if(PlayerData[i][pOnDuty] == 0) return 1;
			SendClientMessage(i, color, string);
		}
		else SendClientMessage(i, color, string);
	}
	return 1;
}
 
stock SendJobMessage(jobid, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (PlayerData[i][pJob] == jobid) {
		    SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pJob] == jobid) {
 		SendClientMessage(i, color, str);
	}
	return 1;
}

stock SendVehicleMessage(vehicleid, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (GetPlayerVehicleID(i) == vehicleid) {
		    SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (GetPlayerVehicleID(i) == vehicleid) {
 		SendClientMessage(i, color, string);
	}
	return 1;
}

stock SendRadioMessage(frequency, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (Inventory_HasItem(i, "Portable Radio") && PlayerData[i][pChannel] == frequency) {
		    SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (Inventory_HasItem(i, "Portable Radio") && PlayerData[i][pChannel] == frequency) {
 		SendClientMessage(i, color, str);
	}
	return 1;
}

stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
	static
	    args,
	    str[144];

	/*
     *  Custom function that uses #emit to format variables into a string.
     *  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 3)
	{
	    SendClientMessage(playerid, color, text);
	}
	else
	{
		while (--args >= 3)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		SendClientMessage(playerid, color, str);

		#emit RETN
	}
	return 1;
}

stock SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
	static
	    args,
	    str[144];

	/*
     *  Custom function that uses #emit to format variables into a string.
     *  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 2)
	{
	    SendClientMessageToAll(color, text);
	}
	else
	{
		while (--args >= 2)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		SendClientMessageToAll(color, str);

		#emit RETN
	}
	return 1;
}

stock Log_Write(const path[], const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    File:file,
	    string[1024]
	;
	if ((start = strfind(path, "/")) != -1) {
	    strmid(string, path, 0, start + 1);

	    if (!fexist(string))
	        return printf("** Warning: Directory \"%s\" doesn't exist.", string);
	}
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	file = fopen(path, io_append);

	if (!file)
	    return 0;

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 1024
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		fwrite(file, string);
		fwrite(file, "\r\n");
		fclose(file);

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN
	}
	fwrite(file, str);
	fwrite(file, "\r\n");
	fclose(file);

	return 1;
}

stock ReturnVehicleName(vehicleid)
{
	new
		model = GetVehicleModel(vehicleid),
		name[32] = "None";

    if (model < 400 || model > 611)
	    return name;

	format(name, sizeof(name), g_arrVehicleNames[model - 400]);
	return name;
}

stock IsWindowedVehicle(vehicleid)
{
	static const g_aWindowStatus[] = {
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1,
	    1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
	};
	new modelid = GetVehicleModel(vehicleid);

    if (modelid < 400 || modelid > 611)
        return 0;

    return (g_aWindowStatus[modelid - 400]);
}

stock IsNewsVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
	    case 488, 582: return 1;
	}
	return 0;
}

stock IsACruiser(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
	    case 523, 427, 490, 528, 596..599, 601: return 1;
	}
	return 0;
}

stock IsDoorVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 400..424, 426..429, 431..440, 442..445, 451, 455, 456, 458, 459, 466, 467, 470, 474, 475:
		    return 1;

		case 477..480, 482, 483, 486, 489, 490..492, 494..496, 498..500, 502..508, 514..518, 524..529, 533..536:
		    return 1;

		case 540..547, 549..552, 554..562, 565..568, 573, 575, 576, 578..580, 582, 585, 587..589, 596..605, 609:
			return 1;
	}
	return 0;
}

stock IsSpeedoVehicle(vehicleid)
{
	if (GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 510 || GetVehicleModel(vehicleid) == 481 || !IsEngineVehicle(vehicleid)) {
	    return 0;
	}
	return 1;
}

stock IsLoadableVehicle(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if (GetVehicleTrailer(vehicleid))
	    modelid = GetVehicleModel(GetVehicleTrailer(vehicleid));

	switch (modelid) {
	    case 609, 403, 414, 456, 498, 499, 514, 515, 435, 591: return 1;
	}
	return 0;
}

stock GetMaxCrates(vehicleid)
{
	new crates;

	switch (GetVehicleModel(vehicleid)) {
	    case 498, 609: crates = 10;
	    case 414: crates = 8;
	    case 456, 499: crates = 6;
	    case 435, 591: crates = 15;
	}
	return crates;
}

stock IsCrateInUse(crateid)
{
	if (CrateData[crateid][crateVehicle] != INVALID_VEHICLE_ID && IsValidVehicle(CrateData[crateid][crateVehicle])) {
	    return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pCarryCrate] == crateid && GetPlayerSpecialAction(i) == SPECIAL_ACTION_CARRY) {
	    return 1;
	}
	return 0;
}

stock GetVehicleCrates(vehicleid)
{
	if (!IsValidVehicle(vehicleid) || !IsLoadableVehicle(vehicleid))
		return 0;

	new crates;

	for (new i = 0; i != MAX_CRATES; i ++) if (CrateData[i][crateExists] && CrateData[i][crateVehicle] == vehicleid) {
	    crates++;
	}
 	return crates;
}

stock IsABoat(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return 1;
	}
	return 0;
}

stock IsABike(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 448, 461..463, 468, 521..523, 581, 586, 481, 509, 510: return 1;
	}
	return 0;
}

stock IsAPlane(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 460, 464, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return 1;
	}
	return 0;
}

stock IsAHelicopter(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: return 1;
	}
	return 0;
}

stock IsEngineVehicle(vehicleid)
{
	static const g_aEngineStatus[] = {
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
	};
    new modelid = GetVehicleModel(vehicleid);

    if (modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

stock Float:GetPlayerSpeed(playerid)
{
	static Float:velocity[3];

	if (IsPlayerInAnyVehicle(playerid))
	    GetVehicleVelocity(GetPlayerVehicleID(playerid), velocity[0], velocity[1], velocity[2]);
	else
	    GetPlayerVelocity(GetPlayerVehicleID(playerid), velocity[0], velocity[1], velocity[2]);

	return floatsqroot((velocity[0] * velocity[0]) + (velocity[1] * velocity[1]) + (velocity[2] * velocity[2])) * 100.0;
}

stock GetGateByID(sqlid)
{
	for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && GateData[i][gateID] == sqlid)
	    return i;

	return -1;
}

stock GetHouseByID(sqlid)
{
	for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && HouseData[i][houseID] == sqlid)
	    return i;

	return -1;
}

stock GetBusinessByID(sqlid)
{
	for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizID] == sqlid)
	    return i;

	return -1;
}

stock GetEntranceByID(sqlid)
{
	for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceID] == sqlid)
	    return i;

	return -1;
}

stock GetElapsedTime(time, &hours, &minutes, &seconds)
{
	hours = 0;
	minutes = 0;
	seconds = 0;

	if (time >= 3600)
	{
		hours = (time / 3600);
		time -= (hours * 3600);
	}
	while (time >= 60)
	{
	    minutes++;
	    time -= 60;
	}
	return (seconds = time);
}

stock GetDuration(time)
{
	new
	    str[32];

	if (time < 0 || time == gettime()) {
	    format(str, sizeof(str), "Never");
	    return str;
	}
	else if (time < 60)
		format(str, sizeof(str), "%d seconds", time);

	else if (time >= 0 && time < 60)
		format(str, sizeof(str), "%d seconds", time);

	else if (time >= 60 && time < 3600)
		format(str, sizeof(str), (time >= 120) ? ("%d minutes") : ("%d minute"), time / 60);

	else if (time >= 3600 && time < 86400)
		format(str, sizeof(str), (time >= 7200) ? ("%d hours") : ("%d hour"), time / 3600);

	else if (time >= 86400 && time < 2592000)
 		format(str, sizeof(str), (time >= 172800) ? ("%d days") : ("%d day"), time / 86400);

	else if (time >= 2592000 && time < 31536000)
 		format(str, sizeof(str), (time >= 5184000) ? ("%d months") : ("%d month"), time / 2592000);

	else if (time >= 31536000)
		format(str, sizeof(str), (time >= 63072000) ? ("%d years") : ("%d year"), time / 31536000);

	strcat(str, " ago");

	return str;
}

stock GetEngineStatus(vehicleid)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (engine != 1)
		return 0;

	return 1;
}

stock GetHoodStatus(vehicleid)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (bonnet != 1)
		return 0;

	return 1;
}

stock GetTrunkStatus(vehicleid)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (boot != 1)
		return 0;

	return 1;
}

stock GetLightStatus(vehicleid)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (lights != 1)
		return 0;

	return 1;
}

stock SetEngineStatus(vehicleid, status)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, status, lights, alarm, doors, bonnet, boot, objective);
}

stock SetLightStatus(vehicleid, status)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, status, alarm, doors, bonnet, boot, objective);
}

stock SetTrunkStatus(vehicleid, status)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, status, objective);
}

stock SetHoodStatus(vehicleid, status)
{
	static
	    engine,
	    lights,
	    alarm,
	    doors,
	    bonnet,
	    boot,
	    objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, status, boot, objective);
}

stock FlashTextDraw(playerid, PlayerText:textid, delay = 500)
{
	PlayerTextDrawHide(playerid, textid);

	SetTimerEx("FlashShowTextDraw", delay, false, "dd", playerid, _:textid);

	return 1;
}

stock FlashTextDrawEx(playerid, PlayerText:textid, amount = 1)
{
	PlayerTextDrawHide(playerid, textid);

	SetTimerEx("FlashShowTextDrawEx", 500, false, "ddd", playerid, _:textid, amount);

	return 1;
}

stock TotalledCheck()
{
	static
	    Float:fHealth;

	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && GetVehicleHealth(i, fHealth) && fHealth < 300.0) {
	    SetVehicleHealth(i, 300.0);
	    SetEngineStatus(i, false);
	}
	return 1;
}

stock ShowContacts(playerid)
{
	new
	    string[32 * MAX_CONTACTS],
		count = 0;

	string = "Add Contact\n";

	for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]) {
	    format(string, sizeof(string), "%s%s - #%d\n", string, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber]);

		ListedContacts[playerid][count++] = i;
	}
	Dialog_Show(playerid, Contacts, DIALOG_STYLE_LIST, "My Contacts", string, "Select", "Back");
	return 1;
}

stock GetPlayerID(name[], underscore = 1)
{
	foreach (new i : Player) if (!strcmp(ReturnName(i, underscore), name, true)) {
	    return i;
	}
	return INVALID_PLAYER_ID;
}

stock PlaySoundForPlayersInRange(soundid, Float:range, Float:x, Float:y, Float:z)
{
	for(new i=0; i<MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i,range,x,y,z))
	    {
		    PlayerPlaySound(i, soundid, x, y, z);
	    }
	}
}

stock SetCameraData(playerid)
{ 
	InterpolateCameraPos(playerid, 1697.194091, 582.047485, 65.091819, 1865.236816, 997.897460, 57.145011, 40000);
	InterpolateCameraLookAt(playerid, 1699.372436, 586.514343, 64.542152, 1867.001342, 1002.574584, 57.250473, 40000);
	return 1;
}


stock GetWeaponModelEx(weaponid)
{
    switch(weaponid)
    {
        case 1:
            return 331;
 
        case 2..8:
            return weaponid+331;
 
        case 9:
            return 341;
 
        case 10..15:
            return weaponid+311;
 
        case 16..18:
            return weaponid+326;
 
        case 22..29:
            return weaponid+324;
 
        case 30,31:
            return weaponid+325;
 
        case 32:
            return 372;
 
        case 33..45:
            return weaponid+324;
 
        case 46:
            return 371;
    }
    return 0;
}


stock IsVehicleEmpty(vehicleid)
{
	for(new i = 0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerInVehicle(i, vehicleid)) return 0;
	}
	return 1;
}

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc)){
		if(strsrc[i]==delimiter || i==strlen(strsrc)){
			len = strmid(strdest[aNum], strsrc, li, i, 128);
			strdest[aNum][len] = 0;
			li = i+1;
			aNum++;
		}
		i++;
	}
	return 1;
}

// --------------------------------- End Stocks