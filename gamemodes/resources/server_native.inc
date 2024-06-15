native IsValidVehicle(vehicleid);

LoadMySQLSettings()
{
    g_iHandle = mysql_connect("localhost", "root", "SakuraRyzen_Roleplay", ""); 

	if (mysql_errno(g_iHandle) != 0) {
	    printf("[SQL] Connection to database failed! Please check the connection settings.\a");
	}
	else {
		printf("[SQL] Connection to database passed!");
	}

    return 1;
}

SQL_SaveCharacter(playerid)
{
	if (!PlayerData[playerid][pLogged] && !PlayerData[playerid][pCharacter])
		return 0;

	new
	    query[2048];

	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && !PlayerData[playerid][pDrivingTest])
	{
	    PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
	    PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

	    GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
	    GetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

	    GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	    GetPlayerArmour(playerid, PlayerData[playerid][pArmorStatus]);

	    if (!PlayerData[playerid][pKilled] && PlayerData[playerid][pHealth] == 0.0) {
	        PlayerData[playerid][pHealth] = 100.0;
		}
		UpdateWeapons(playerid);
	}
	format(query, sizeof(query), "UPDATE `characters` SET `Created` = '%d', `Gender` = '%d', `Birthdate` = '%s', `Origin` = '%s', `Skin` = '%d', `OnDuty` = '%d', `FacSkin` = '%d', `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f', `PosA` = '%.4f', `Health` = '%.4f', `Interior` = '%d', `World` = '%d', `Money` = '%d', `BankMoney` = '%d',  `Savings` = '%d', `Admin` = '%d', `JailTime` = '%d', `Muted` = '%d', `Staterpack` = '%d'",
		PlayerData[playerid][pCreated],
		PlayerData[playerid][pGender],
		PlayerData[playerid][pBirthdate],
		PlayerData[playerid][pOrigin],
		PlayerData[playerid][pSkin],
		PlayerData[playerid][pOnDuty],
		PlayerData[playerid][pFacSkin], 
		PlayerData[playerid][pPos][0],
		PlayerData[playerid][pPos][1],
		PlayerData[playerid][pPos][2], 
		PlayerData[playerid][pPos][3],
		PlayerData[playerid][pHealth],
		PlayerData[playerid][pInterior],
		PlayerData[playerid][pWorld],
		PlayerData[playerid][pMoney],
		PlayerData[playerid][pBankMoney],
		PlayerData[playerid][pSavings],
		PlayerData[playerid][pAdmin],
		PlayerData[playerid][pJailTime],
		PlayerData[playerid][pMuted],
		PlayerData[playerid][pStaterpack]
	);
	for (new i = 0; i < 13; i ++) {
		format(query, sizeof(query), "%s, `Gun%d` = '%d', `Ammo%d` = '%d'", query, i + 1, PlayerData[playerid][pGuns][i], i + 1, PlayerData[playerid][pAmmo][i]);
	}
	format(query, sizeof(query), "%s, `House` = '%d', `Business` = '%d', `Entrance` = '%d', `Phone` = '%d', `Lottery` = '%d', `LotteryB` = '%d', `BodyInsurance` = '%d', `Uraine` = '%d', `Stress` = '%d', `Hunger` = '%d', `Thirst` = '%d', `Score` = '%d', `Minutes` = '%d', `ArmorStatus` = '%.4f', `Job` = '%d', `Faction` = '%d', `FactionRank` = '%d', `Prisoned` = '%d', `Injured` = '%d', `InjuredTime` = '%d', `Warrants` = '%d', `Channel` = '%d', `AdminHide` = '%d', `SpawnPoint` = '%d'",
		query,
		PlayerData[playerid][pHouse],
		PlayerData[playerid][pBusiness],
		PlayerData[playerid][pEntrance],
		PlayerData[playerid][pPhone],
		PlayerData[playerid][pLottery],
		PlayerData[playerid][pLotteryB], 
		PlayerData[playerid][pBodyInsurance], 
		PlayerData[playerid][pUraine],
		PlayerData[playerid][pStress],
		PlayerData[playerid][pHunger],
		PlayerData[playerid][pThirst],
		PlayerData[playerid][pScore],
		PlayerData[playerid][pMinutes],
		PlayerData[playerid][pArmorStatus],
		PlayerData[playerid][pJob],
		PlayerData[playerid][pFactionID],
		PlayerData[playerid][pFactionRank],
		PlayerData[playerid][pPrisoned],
		PlayerData[playerid][pInjured],
		PlayerData[playerid][pInjuredTime],
		PlayerData[playerid][pWarrants],
		PlayerData[playerid][pChannel],
		PlayerData[playerid][pAdminHide],
		PlayerData[playerid][pSpawnPoint]
	);
	format(query, sizeof(query), "%s, `Warnings` = '%d', `Warn1` = '%s', `Warn2` = '%s', `MaskID` = '%d', `FactionMod` = '%d', `Capacity` = '%d' WHERE `ID` = '%d'",
	    query,
	    PlayerData[playerid][pWarnings],
	    SQL_ReturnEscaped(PlayerData[playerid][pWarn1]),
	    SQL_ReturnEscaped(PlayerData[playerid][pWarn2]),
	    PlayerData[playerid][pMaskID],
	    PlayerData[playerid][pFactionMod],
	    PlayerData[playerid][pCapacity],
		PlayerData[playerid][pID]
	);
	mysql_tquery(g_iHandle, query);

	SQL_SaveAccessories(playerid);
	return 1;
}

SQL_SaveAccessories(playerid)
{
    if (!PlayerData[playerid][pLogged])
		return 0;

	new
	    query[768];

    format(query, sizeof(query), "UPDATE `characters` SET `Glasses` = '%d', `Hat` = '%d', `Bandana` = '%d', `GlassesPos` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f'",
	    PlayerData[playerid][pGlasses],
	    PlayerData[playerid][pHat],
	    PlayerData[playerid][pBandana],
		AccessoryData[playerid][0][0],
        AccessoryData[playerid][0][1],
        AccessoryData[playerid][0][2],
        AccessoryData[playerid][0][3],
        AccessoryData[playerid][0][4],
        AccessoryData[playerid][0][5],
        AccessoryData[playerid][0][6],
        AccessoryData[playerid][0][7],
        AccessoryData[playerid][0][8]
	);
    format(query, sizeof(query), "%s, `HatPos` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f'",
        query,
		AccessoryData[playerid][1][0],
        AccessoryData[playerid][1][1],
        AccessoryData[playerid][1][2],
        AccessoryData[playerid][1][3],
        AccessoryData[playerid][1][4],
        AccessoryData[playerid][1][5],
        AccessoryData[playerid][1][6],
        AccessoryData[playerid][1][7],
        AccessoryData[playerid][1][8]
	);
	format(query, sizeof(query), "%s, `BandanaPos` = '%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f|%.4f' WHERE `ID` = '%d'",
	    query,
		AccessoryData[playerid][2][0],
        AccessoryData[playerid][2][1],
        AccessoryData[playerid][2][2],
        AccessoryData[playerid][2][3],
        AccessoryData[playerid][2][4],
        AccessoryData[playerid][2][5],
        AccessoryData[playerid][2][6],
        AccessoryData[playerid][2][7],
        AccessoryData[playerid][2][8],
        PlayerData[playerid][pID]
	);
	mysql_tquery(g_iHandle, query);
	return 1;
}

Vendor_Nearest(playerid)
{
    for (new i = 0; i != MAX_VENDORS; i ++) if (VendorData[i][vendorExists] && IsPlayerInRangeOfPoint(playerid, 2.0, VendorData[i][vendorPos][0], VendorData[i][vendorPos][1], VendorData[i][vendorPos][2]))
	{
		if (GetPlayerInterior(playerid) == VendorData[i][vendorInterior] && GetPlayerVirtualWorld(playerid) == VendorData[i][vendorWorld])
			return i;
	}
	return -1;
}

Garbage_Nearest(playerid)
{
    for (new i = 0; i != MAX_GARBAGE_BINS; i ++) if (GarbageData[i][garbageExists] && IsPlayerInRangeOfPoint(playerid, 3.0, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]))
	{
		if (GetPlayerInterior(playerid) == GarbageData[i][garbageInterior] && GetPlayerVirtualWorld(playerid) == GarbageData[i][garbageWorld])
			return i;
	}
	return -1;
}

ATM_Nearest(playerid)
{
    for (new i = 0; i != MAX_ATM_MACHINES; i ++) if (ATMData[i][atmExists] && IsPlayerInRangeOfPoint(playerid, 2.5, ATMData[i][atmPos][0], ATMData[i][atmPos][1], ATMData[i][atmPos][2]))
	{
		if (GetPlayerInterior(playerid) == ATMData[i][atmInterior] && GetPlayerVirtualWorld(playerid) == ATMData[i][atmWorld])
			return i;
	}
	return -1;
}

cache_get_field_int(row, const field_name[])
{
	new
	    str[12];

	cache_get_field_content(row, field_name, str, g_iHandle, sizeof(str));
	return strval(str);
}

Mechanic_Nearest(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(IsPlayerInRangeOfPoint(playerid, 4.0, 1865.4161,788.2553,12.0493) ||
			IsPlayerInRangeOfPoint(playerid, 4.0, 1875.4205,789.7808,11.2445) ||
			IsPlayerInRangeOfPoint(playerid, 4.0, 1885.0736,789.2410,11.1434) ||
			IsPlayerInRangeOfPoint(playerid, 4.0, 1853.9557,796.0042,11.7484) ||
			IsPlayerInRangeOfPoint(playerid, 4.0, 1857.9434,809.4344,11.0212) ||
			IsPlayerInRangeOfPoint(playerid, 4.0, 1884.4518,809.4943,11.0436))

		{
			return 1;
		}
	}
	return 0;
}

Ticket_Add(suspectid, price, factionid, reason[])
{
	new
	    string[160];

	for (new i = 0; i != MAX_PLAYER_TICKETS; i ++) if (!TicketData[suspectid][i][ticketExists])
	{
	    TicketData[suspectid][i][ticketExists] = true;
	    TicketData[suspectid][i][ticketFee] = price;
		TicketData[suspectid][i][ticketFaction] = factionid;

	    format(TicketData[suspectid][i][ticketDate], 36, ReturnDate());
	    format(TicketData[suspectid][i][ticketReason], 64, reason);

		format(string, sizeof(string), "INSERT INTO `tickets` (`ID`, `ticketFee`, `ticketDate`, `ticketFaction`, `ticketReason`) VALUES('%d', '%d', '%s', '%d', '%s')", PlayerData[suspectid][pID], price, TicketData[suspectid][i][ticketDate], factionid, SQL_ReturnEscaped(reason));
		mysql_tquery(g_iHandle, string, "OnTicketCreated", "dd", suspectid, i);

		return i;
	}
	return -1;
}

Ticket_Remove(playerid, ticketid)
{
	if (ticketid != -1 && TicketData[playerid][ticketid][ticketExists])
	{
	    new
	        string[90];

		format(string, sizeof(string), "DELETE FROM `tickets` WHERE `ID` = '%d' AND `ticketID` = '%d'", PlayerData[playerid][pID], TicketData[playerid][ticketid][ticketID]);
		mysql_tquery(g_iHandle, string);

	    TicketData[playerid][ticketid][ticketExists] = false;
	    TicketData[playerid][ticketid][ticketID] = 0;
	    TicketData[playerid][ticketid][ticketFee] = 0;
		TicketData[playerid][ticketid][ticketFaction] = -1;
	}
	return 1;
}

Waypoint_Set(playerid, name[], Float:x, Float:y, Float:z)
{
    format(PlayerData[playerid][pLocation], 32, name);

    PlayerData[playerid][pWaypoint] = 1;
   	PlayerData[playerid][pWaypointPos][0] = x;
    PlayerData[playerid][pWaypointPos][1] = y;
   	PlayerData[playerid][pWaypointPos][2] = z;

	SetPlayerCheckpoint(playerid, x, y, z, 3.0);
	PlayerTextDrawShow(playerid, WaypointTD[playerid]);

	return 1;
}

Location_Add(playerid, name[], Float:x, Float:y, Float:z)
{
	new
	    query[192];

	for (new i = 0; i != MAX_GPS_LOCATIONS; i ++) if (!LocationData[playerid][i][locationExists])
	{
	    LocationData[playerid][i][locationExists] = true;
	    format(LocationData[playerid][i][locationName], 32, name);

	    LocationData[playerid][i][locationPos][0] = x;
	    LocationData[playerid][i][locationPos][1] = y;
	    LocationData[playerid][i][locationPos][2] = z;

		format(query, sizeof(query), "INSERT INTO `gps` (`ID`, `locationName`, `locationX`, `locationY`, `locationZ`) VALUES('%d', '%s', '%.4f', '%.4f', '%.4f')", PlayerData[playerid][pID], SQL_ReturnEscaped(name), x, y, z);
		mysql_tquery(g_iHandle, query, "OnLocationCreated", "dd", playerid, i);

		return i;
	}
	return -1;
}

Location_GetID(playerid, name[])
{
    for (new i = 0; i != MAX_GPS_LOCATIONS; i ++) if (LocationData[playerid][i][locationExists] && !strcmp(LocationData[playerid][i][locationName], name, true)) {
        return i;
	}
	return -1;
}

Location_Delete(playerid, name[])
{
	new
		query[96];

    for (new i = 0; i != MAX_GPS_LOCATIONS; i ++) if (LocationData[playerid][i][locationExists] && !strcmp(LocationData[playerid][i][locationName], name))
	{
	    LocationData[playerid][i][locationExists] = false;

	    LocationData[playerid][i][locationPos][0] = 0.0;
	    LocationData[playerid][i][locationPos][1] = 0.0;
	    LocationData[playerid][i][locationPos][2] = 0.0;

	    format(query, sizeof(query), "DELETE FROM `gps` WHERE `ID` = '%d' AND `locationID` = '%d'", PlayerData[playerid][pID], LocationData[playerid][i][locationID]);
	    mysql_tquery(g_iHandle, query);
		return 1;
	}
	return 0;
}

ShowHungerTextdraw(playerid, enable)
{
	if (!enable) 
	{
		for (new i = 0; i < 4; i ++) {
			TextDrawHideForPlayer(playerid, PLAYERONLINE[playerid][i]);
		}
		for (new i = 0; i < 9; i ++) {
			TextDrawHideForPlayer(playerid, LAPARHAUS[playerid][i]);
		}
		for (new i = 0; i < 3; i ++) {
			HidePlayerProgressBar(playerid, LAPARHAUSBAR[playerid][i]);
		}

	}
	else if (PlayerData[playerid][pHUD] && PlayerData[playerid][pJailTime] < 1) 
	{
		for (new i = 0; i < 4; i ++) {
			TextDrawShowForPlayer(playerid, PLAYERONLINE[playerid][i]);
		}
		for (new i = 0; i < 9; i ++) {
			TextDrawShowForPlayer(playerid, LAPARHAUS[playerid][i]);
		}
		for (new i = 0; i < 3; i ++) {
			ShowPlayerProgressBar(playerid, LAPARHAUSBAR[playerid][i]);
		}

		UpdatePlayerHudData(playerid);
	}
	return 1;
}

SendPlayerToPlayer(playerid, targetid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(targetid, x, y, z);

	if (IsPlayerInAnyVehicle(playerid))
	{
	    SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
	}
	else
		SetPlayerPos(playerid, x + 1, y, z);

	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

	PlayerData[playerid][pHouse] = PlayerData[targetid][pHouse];
	PlayerData[playerid][pBusiness] = PlayerData[targetid][pBusiness];
	PlayerData[playerid][pEntrance] = PlayerData[targetid][pEntrance];
}

StopRefilling(playerid)
{
    PlayerData[playerid][pGasPump] = -1;
    PlayerData[playerid][pGasStation] = -1;
   	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
}

SetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	for (new i = 0; i < 13; i ++) if (PlayerData[playerid][pGuns][i] > 0 && PlayerData[playerid][pAmmo][i] > 0) {
	    GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);
	}
	return 1;
}

SetAccessories(playerid)
{
    for (new i = 0; i != MAX_PLAYER_ATTACHED_OBJECTS; i ++) {
	    RemovePlayerAttachedObject(playerid, i);
	}
	if (PlayerData[playerid][pToggleGlasses]) RemovePlayerAttachedObject(playerid, 0);
	else if (PlayerData[playerid][pGlasses] != 0) SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pGlasses], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);

	if (PlayerData[playerid][pToggleHat]) RemovePlayerAttachedObject(playerid, 1);
	else if (PlayerData[playerid][pHat] != 0) SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pHat], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);

    if (PlayerData[playerid][pToggleBandana]) RemovePlayerAttachedObject(playerid, 2);
	else if (PlayerData[playerid][pBandana] != 0) SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pBandana], 2, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);

	if (Inventory_HasItem(playerid, "Backpack")) SetPlayerAttachedObject(playerid, 5, 3026, 1, -0.134207, -0.093048, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
	else RemovePlayerAttachedObject(playerid, 5);
}

SQL_LoadCharacter(playerid, characterid)
{
	if (characterid < 1 || characterid > 3)
		return 0;

	new
		query[160];

	format(query, sizeof(query), "UPDATE `characters` SET `LastLogin` = '%d' WHERE `Username` = '%s' AND `Character` = '%s'", gettime(), PlayerData[playerid][pUsername], PlayerCharacters[playerid][characterid - 1]);
	mysql_tquery(g_iHandle, query);

	format(query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%s' AND `Character` = '%s'", PlayerData[playerid][pUsername], PlayerCharacters[playerid][characterid - 1]);
	mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", playerid, THREAD_LOAD_CHARACTER);

	return 1;
}

ShowCharacterMenu(playerid)
{
	new str[230];
	format(str, sizeof(str), ""WHITE_E"%s\n%s\nSlot 3 - Soon", (!PlayerCharacters[playerid][0][0]) ? ("Tiada") : (PlayerCharacters[playerid][0]), (!PlayerCharacters[playerid][1][0]) ? ("Tiada") : (PlayerCharacters[playerid][1]), (!PlayerCharacters[playerid][2][0]) ? ("Tiada") : (PlayerCharacters[playerid][2]));
	return Dialog_Show(playerid, SelectChar, DIALOG_STYLE_LIST, ""WHITE_E"Senarai Watak", str, "Pilih", "Batal");
}

GetClosestGarbage(playerid)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_GARBAGE_BINS; i ++) if (GarbageData[i][garbageExists] && GarbageData[i][garbageCapacity] > 0 && GetPlayerInterior(playerid) == GarbageData[i][garbageInterior] && GetPlayerVirtualWorld(playerid) == GarbageData[i][garbageWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestBusiness(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizType] == type && GetPlayerInterior(playerid) == BusinessData[i][bizExterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][bizExteriorVW] && BusinessData[i][bizLocked] == 1 && BusinessData[i][bizSita] == 1)
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestJobPoint(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == type && GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, JobData[i][jobPoint][0], JobData[i][jobPoint][1], JobData[i][jobPoint][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

IsWeaponModel(model) {
    new const g_aWeaponModels[] = {
		0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324,
		325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352,
		353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366,
		367, 368, 368, 371
    };
    for (new i = 0; i < sizeof(g_aWeaponModels); i ++) if (g_aWeaponModels[i] == model) {
        return 1;
	}
	return 0;
}

GetWeaponModel(weaponid) {
    new const g_aWeaponModels[] = {
		0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324,
		325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352,
		353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366,
		367, 368, 368, 371
    };
    if (1 <= weaponid <= 46)
        return g_aWeaponModels[weaponid];

	return 0;
}

DropPlayerItem(playerid, itemid, quantity = 1)
{
	if (itemid == -1 || !InventoryData[playerid][itemid][invExists])
	    return 0;

    new
		Float:x,
  		Float:y,
    	Float:z,
		Float:angle,
		string[32];

	strunpack(string, InventoryData[playerid][itemid][invItem]);

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	DropItem(string, ReturnName(playerid, 0), InventoryData[playerid][itemid][invModel], quantity, x, y, z - 0.9, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
 	Inventory_Remove(playerid, string, quantity);

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
 	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has dropped a \"%s\".", ReturnName(playerid, 0), string);
	return 1;
}

DropItem(item[], player[], model, quantity, Float:x, Float:y, Float:z, interior, world, weaponid = 0, ammo = 0)
{
	for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (!DroppedItems[i][droppedModel])
	{
	    format(DroppedItems[i][droppedItem], 32, item);
	    format(DroppedItems[i][droppedPlayer], 24, player);

		DroppedItems[i][droppedModel] = model;
		DroppedItems[i][droppedQuantity] = quantity;
		DroppedItems[i][droppedWeapon] = weaponid;
  		DroppedItems[i][droppedAmmo] = ammo;
		DroppedItems[i][droppedPos][0] = x;
		DroppedItems[i][droppedPos][1] = y;
		DroppedItems[i][droppedPos][2] = z;

		DroppedItems[i][droppedInt] = interior;
		DroppedItems[i][droppedWorld] = world;

		if (IsWeaponModel(model)) {
			DroppedItems[i][droppedObject] = CreateDynamicObject(model, x, y, z, 93.7, 120.0, 120.0, world, interior);
		} else {
			DroppedItems[i][droppedObject] = CreateDynamicObject(model, x, y, z, 0.0, 0.0, 0.0, world, interior);
		}
 		DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(item, COLOR_CYAN, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);
		return i;
	}
	return -1;
}

Item_Nearest(playerid)
{
    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]))
	{
	    if (GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld])
	        return i;
	}
	return -1;
}

Item_SetQuantity(itemid, amount)
{
	new
	    string[64];

	if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
	    DroppedItems[itemid][droppedQuantity] = amount;

	    format(string, sizeof(string), "UPDATE `dropped` SET `itemQuantity` = %d WHERE `ID` = '%d'", amount, DroppedItems[itemid][droppedID]);
		mysql_tquery(g_iHandle, string);
	}
	return 1;
}

Item_Delete(itemid)
{
    static
	    query[64];

    if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
        DroppedItems[itemid][droppedModel] = 0;
		DroppedItems[itemid][droppedQuantity] = 0;
	    DroppedItems[itemid][droppedPos][0] = 0.0;
	    DroppedItems[itemid][droppedPos][1] = 0.0;
	    DroppedItems[itemid][droppedPos][2] = 0.0;
	    DroppedItems[itemid][droppedInt] = 0;
	    DroppedItems[itemid][droppedWorld] = 0;

	    DestroyDynamicObject(DroppedItems[itemid][droppedObject]);
	    DestroyDynamic3DTextLabel(DroppedItems[itemid][droppedText3D]);

	    format(query, sizeof(query), "DELETE FROM `dropped` WHERE `ID` = '%d'", DroppedItems[itemid][droppedID]);
	    mysql_tquery(g_iHandle, query);
	}
	return 1;
}

PickupItem(playerid, itemid)
{
	if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
	    new id = Inventory_Add(playerid, DroppedItems[itemid][droppedItem], DroppedItems[itemid][droppedModel], DroppedItems[itemid][droppedQuantity]);

	    if (id == -1)
	        return SendErrorMessage(playerid, "You don't have any inventory slots left.");

	    Item_Delete(itemid);
	}
	return 1;
}

Faction_GetName(playerid) 
{
    new
		factionid = PlayerData[playerid][pFaction],
		name[32] = "None";

 	if (factionid == -1)
	    return name;

	format(name, 32, FactionData[factionid][factionName]);
	return name;
}

Faction_GetRank(playerid)
{
    new
		factionid = PlayerData[playerid][pFaction],
		rank[32] = "None";

 	if (factionid == -1)
	    return rank;

	format(rank, 32, FactionRanks[factionid][PlayerData[playerid][pFactionRank] - 1]);
	return rank;
}
Rack_Save(rackid)
{
	static
	    query[512];

	format(query, sizeof(query), "UPDATE `gunracks` SET `rackHouse` = '%d', `rackX` = '%.4f', `rackY` = '%.4f', `rackZ` = '%.4f', `rackA` = '%.4f', `rackInterior` = '%d', `rackWorld` = '%d', `rackWeapon1` = '%d', `rackWeapon2` = '%d', `rackWeapon3` = '%d', `rackWeapon4` = '%d', `rackAmmo1` = '%d', `rackAmmo2` = '%d', `rackAmmo3` = '%d', `rackAmmo4` = '%d' WHERE `rackID` = '%d'",
	    RackData[rackid][rackHouse],
	    RackData[rackid][rackPos][0],
	    RackData[rackid][rackPos][1],
	    RackData[rackid][rackPos][2],
	    RackData[rackid][rackPos][3],
	    RackData[rackid][rackInterior],
	    RackData[rackid][rackWorld],
	    RackData[rackid][rackWeapons][0],
	    RackData[rackid][rackWeapons][1],
	    RackData[rackid][rackWeapons][2],
	    RackData[rackid][rackWeapons][3],
	    RackData[rackid][rackAmmo][0],
	    RackData[rackid][rackAmmo][1],
	    RackData[rackid][rackAmmo][2],
	    RackData[rackid][rackAmmo][3],
	    RackData[rackid][rackID]
	);
	return mysql_tquery(g_iHandle, query);
}

Rack_Nearest(playerid)
{
	for (new i = 0; i != MAX_WEAPON_RACKS; i ++) if (RackData[i][rackExists] && IsPlayerInRangeOfPoint(playerid, 3.0, RackData[i][rackPos][0], RackData[i][rackPos][1], RackData[i][rackPos][2]))
	{
		if (GetPlayerInterior(playerid) == RackData[i][rackInterior] && GetPlayerVirtualWorld(playerid) == RackData[i][rackWorld])
		    return i;
	}
	return -1;
}

Rack_Count(houseid)
{
	new count;

	for (new i = 0; i != MAX_WEAPON_RACKS; i ++) if (RackData[i][rackExists] && RackData[i][rackHouse] == HouseData[houseid][houseID]) {
	    count++;
	}
	return count;
}

Rack_ShowGuns(playerid, rackid)
{
	if (rackid != -1 && RackData[rackid][rackExists])
	{
	    new
	        string[128];

		for (new i = 0; i < 4; i ++)
		{
		    if (!RackData[rackid][rackWeapons][i])
		        format(string, sizeof(string), "%s%d: Empty Slot\n", string, i + 1);

			else format(string, sizeof(string), "%s%d: %s - %d bullets\n", string, i + 1, ReturnWeaponName(RackData[rackid][rackWeapons][i]), RackData[rackid][rackAmmo][i]);
		}
		Dialog_Show(playerid, RackWeapons, DIALOG_STYLE_LIST, "Weapon Rack", string, "Select", "Cancel");
	}
	return 1;
}

Rack_Delete(rackid)
{
    if (rackid != -1 && RackData[rackid][rackExists])
	{
	    static
	        string[64];

	    format(string, sizeof(string), "DELETE FROM `gunracks` WHERE `rackID` = '%d'", RackData[rackid][rackID]);
	    mysql_tquery(g_iHandle, string);

        for (new i = 0; i < 5; i ++) if (IsValidDynamicObject(RackData[rackid][rackObjects][i])) {
			DestroyDynamicObject(RackData[rackid][rackObjects][i]);
		}
		if (IsValidDynamic3DTextLabel(RackData[rackid][rackText3D])) {
		    DestroyDynamic3DTextLabel(RackData[rackid][rackText3D]);
		}
		RackData[rackid][rackExists] = false;
		RackData[rackid][rackID] = 0;
		RackData[rackid][rackHouse] = 0;
	}
	return 1;
}

Rack_Create(playerid, houseid)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_WEAPON_RACKS; i ++) if (!RackData[i][rackExists])
		{
		    x += 1.5 * floatsin(-angle, degrees);
		    y += 1.5 * floatcos(-angle, degrees);

		    RackData[i][rackExists] = true;
		    RackData[i][rackHouse] = (houseid == -1) ? (-1) : (HouseData[houseid][houseID]);

		    RackData[i][rackPos][0] = x;
		    RackData[i][rackPos][1] = y;
		    RackData[i][rackPos][2] = z;
		    RackData[i][rackPos][3] = angle;
		    RackData[i][rackInterior] = GetPlayerInterior(playerid);
		    RackData[i][rackWorld] = GetPlayerVirtualWorld(playerid);

		    Rack_Refresh(i);
		    mysql_tquery(g_iHandle, "INSERT INTO `gunracks` (`rackHouse`) VALUES(0)", "OnRackCreated", "d", i);

		    return i;
		}
	}
	return -1;
}

Rack_RefreshGuns(rackid)
{
    if (rackid != -1 && RackData[rackid][rackExists])
	{
    	new
			Float:x,
	        Float:y,
			Float:z;

		z = RackData[rackid][rackPos][2] + 2.19;

		for (new i = 0; i < 4; i ++) if (IsValidDynamicObject(RackData[rackid][rackObjects][i])) {
		    DestroyDynamicObject(RackData[rackid][rackObjects][i]);

			RackData[rackid][rackObjects][i] = INVALID_OBJECT_ID;
		}
		for (new i = 0; i < 4; i ++)
		{
		    if (RackData[rackid][rackWeapons][i])
			{
				x = RackData[rackid][rackPos][0] - (0.2 * floatsin(-RackData[rackid][rackPos][3], degrees) + (0.45 * floatsin(-RackData[rackid][rackPos][3] - 90, degrees)));
				y = RackData[rackid][rackPos][1] - (0.2 * floatcos(-RackData[rackid][rackPos][3], degrees) + (0.45 * floatcos(-RackData[rackid][rackPos][3] - 90, degrees)));

		        RackData[rackid][rackObjects][i] = CreateDynamicObject(GetWeaponModel(RackData[rackid][rackWeapons][i]), x, y, z, 94.7, 93.7, (22 <= RackData[rackid][rackWeapons][i] <= 38) ? (RackData[rackid][rackPos][3] + 90.0) : (RackData[rackid][rackPos][3]), RackData[rackid][rackWorld], RackData[rackid][rackInterior]);
			}
			else
			{
			    RackData[rackid][rackObjects][i] = INVALID_OBJECT_ID;
			}
			z = z - 0.69;
		}
	}
	return 1;
}

Rack_Refresh(rackid)
{
	if (rackid != -1 && RackData[rackid][rackExists])
	{
	    static
	        str[64];

		if (IsValidDynamicObject(RackData[rackid][rackObjects][4])) {
		    DestroyDynamicObject(RackData[rackid][rackObjects][4]);
		}
		if (IsValidDynamic3DTextLabel(RackData[rackid][rackText3D])) {
		    DestroyDynamic3DTextLabel(RackData[rackid][rackText3D]);
		}
		format(str, sizeof(str), "[GUN RACK]\n{FFFFFF}Type "GREEN_E"/gunrack"WHITE_E" to use this rack.");
		RackData[rackid][rackText3D] = CreateDynamic3DTextLabel(str, COLOR_DARKBLUE, RackData[rackid][rackPos][0], RackData[rackid][rackPos][1], RackData[rackid][rackPos][2] + 1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, RackData[rackid][rackWorld], RackData[rackid][rackInterior]);

		Rack_RefreshGuns(rackid);
        RackData[rackid][rackObjects][4] = CreateDynamicObject(2475, RackData[rackid][rackPos][0], RackData[rackid][rackPos][1], RackData[rackid][rackPos][2], 0.0, 0.0, RackData[rackid][rackPos][3], RackData[rackid][rackWorld], RackData[rackid][rackInterior]);
	}
	return 1;
}

Furniture_GetCount(houseid)
{
	new count;

	for (new i = 0; i < MAX_FURNITURE; i ++) if (FurnitureData[i][furnitureExists] && FurnitureData[i][furnitureHouse] == houseid) {
	    count++;
	}
	return count;
}

Furniture_GetFreeID()
{
	for (new i = 0; i != MAX_FURNITURE; i ++) if (!FurnitureData[i][furnitureExists]) {
	    return i;
	}
	return -1;
}

Furniture_Refresh(furnitureid)
{
	if (furnitureid != -1 && FurnitureData[furnitureid][furnitureExists])
	{
	    if (IsValidDynamicObject(FurnitureData[furnitureid][furnitureObject]))
	        DestroyDynamicObject(FurnitureData[furnitureid][furnitureObject]);

	    FurnitureData[furnitureid][furnitureObject] = CreateDynamicObject(
			FurnitureData[furnitureid][furnitureModel],
			FurnitureData[furnitureid][furniturePos][0],
			FurnitureData[furnitureid][furniturePos][1],
			FurnitureData[furnitureid][furniturePos][2],
			FurnitureData[furnitureid][furnitureRot][0],
			FurnitureData[furnitureid][furnitureRot][1],
			FurnitureData[furnitureid][furnitureRot][2],
			HouseData[FurnitureData[furnitureid][furnitureHouse]][houseID] + 5000,
			HouseData[FurnitureData[furnitureid][furnitureHouse]][houseInterior]
		);
	}
	return 1;
}

Furniture_Save(furnitureid)
{
	static
	    string[300];

	format(string, sizeof(string), "UPDATE `furniture` SET `furnitureModel` = '%d', `furnitureName` = '%s', `furnitureX` = '%.4f', `furnitureY` = '%.4f', `furnitureZ` = '%.4f', `furnitureRX` = '%.4f', `furnitureRY` = '%.4f', `furnitureRZ` = '%.4f' WHERE `ID` = '%d' AND `furnitureID` = '%d'",
	    FurnitureData[furnitureid][furnitureModel],
	    FurnitureData[furnitureid][furnitureName],
	    FurnitureData[furnitureid][furniturePos][0],
	    FurnitureData[furnitureid][furniturePos][1],
	    FurnitureData[furnitureid][furniturePos][2],
	    FurnitureData[furnitureid][furnitureRot][0],
	    FurnitureData[furnitureid][furnitureRot][1],
	    FurnitureData[furnitureid][furnitureRot][2],
	    HouseData[FurnitureData[furnitureid][furnitureHouse]][houseID],
	    FurnitureData[furnitureid][furnitureID]
	);
	return mysql_tquery(g_iHandle, string);
}

Furniture_Add(houseid, name[], modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0)
{
	static
	    string[64],
		id = -1;

 	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	if ((id = Furniture_GetFreeID()) != -1)
	{
	    FurnitureData[id][furnitureExists] = true;
	    format(FurnitureData[id][furnitureName], 32, name);

        FurnitureData[id][furnitureHouse] = houseid;
	    FurnitureData[id][furnitureModel] = modelid;
	    FurnitureData[id][furniturePos][0] = x;
	    FurnitureData[id][furniturePos][1] = y;
	    FurnitureData[id][furniturePos][2] = z;
	    FurnitureData[id][furnitureRot][0] = rx;
	    FurnitureData[id][furnitureRot][1] = ry;
	    FurnitureData[id][furnitureRot][2] = rz;

	    Furniture_Refresh(id);

		format(string, sizeof(string), "INSERT INTO `furniture` (`ID`) VALUES(%d)", HouseData[houseid][houseID]);
		mysql_tquery(g_iHandle, string, "OnFurnitureCreated", "d", id);

		return id;
	}
	return -1;
}

Furniture_Delete(furnitureid)
{
	static
	    string[72];

	if (furnitureid != -1 && FurnitureData[furnitureid][furnitureExists])
	{
	    format(string, sizeof(string), "DELETE FROM `furniture` WHERE `ID` = '%d' AND `furnitureID` = '%d'", HouseData[FurnitureData[furnitureid][furnitureHouse]][houseID], FurnitureData[furnitureid][furnitureID]);
		mysql_tquery(g_iHandle, string);

		FurnitureData[furnitureid][furnitureExists] = false;
		FurnitureData[furnitureid][furnitureModel] = 0;

		DestroyDynamicObject(FurnitureData[furnitureid][furnitureObject]);
	}
	return 1;
}

House_Save(houseid)
{
	static
	    query[1536];

	format(query, sizeof(query), "UPDATE `houses` SET `houseOwner` = '%d', `housePrice` = '%d', `houseAddress` = '%s', `housePosX` = '%.4f', `housePosY` = '%.4f', `housePosZ` = '%.4f', `housePosA` = '%.4f', `houseIntX` = '%.4f', `houseIntY` = '%.4f', `houseIntZ` = '%.4f', `houseIntA` = '%.4f', `houseInterior` = '%d', `houseExterior` = '%d', `houseExteriorVW` = '%d'",
	    HouseData[houseid][houseOwner],
	    HouseData[houseid][housePrice],
	    SQL_ReturnEscaped(HouseData[houseid][houseAddress]),
	    HouseData[houseid][housePos][0],
	    HouseData[houseid][housePos][1],
	    HouseData[houseid][housePos][2],
	    HouseData[houseid][housePos][3],
	    HouseData[houseid][houseInt][0],
	    HouseData[houseid][houseInt][1],
	    HouseData[houseid][houseInt][2],
	    HouseData[houseid][houseInt][3],
        HouseData[houseid][houseInterior],
        HouseData[houseid][houseExterior],
        HouseData[houseid][houseExteriorVW]
	);
	for (new i = 0; i < 10; i ++) {
		format(query, sizeof(query), "%s, `houseWeapon%d` = '%d', `houseAmmo%d` = '%d'", query, i + 1, HouseData[houseid][houseWeapons][i], i + 1, HouseData[houseid][houseAmmo][i]);
	}
	format(query, sizeof(query), "%s, `houseLocked` = '%d', `houseSita` = '%d', `houseMoney` = '%d' WHERE `houseID` = '%d'",
	    query,
	    HouseData[houseid][houseLocked],
		HouseData[houseid][houseSita],
	    HouseData[houseid][houseMoney],
        HouseData[houseid][houseID]
	);
	return mysql_tquery(g_iHandle, query);
}

/*House_GetCount(playerid)
{
	new count = 0;

    for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && House_IsOwner(playerid, i)) {
	    count++;
	}
	return count;
}*/

House_Inside(playerid)
{
	if (PlayerData[playerid][pHouse] != -1)
	{
	    for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && HouseData[i][houseID] == PlayerData[playerid][pHouse] && GetPlayerInterior(playerid) == HouseData[i][houseInterior] && GetPlayerVirtualWorld(playerid) > 0) {
	        return i;
		}
	}
	return -1;
}

Gate_Nearest(playerid)
{
    for (new i = 0; i != MAX_GATES; i ++) if (GateData[i][gateExists] && IsPlayerInRangeOfPoint(playerid, GateData[i][gateRadius], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2])) {
		return i;
	}
	return -1;
}

Pump_Nearest(playerid)
{
    for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && IsPlayerInRangeOfPoint(playerid, 4.0, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]) && PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

Plant_Nearest(playerid)
{
    for (new i = 0; i != MAX_DRUG_PLANTS; i ++) if (PlantData[i][plantExists] && IsPlayerInRangeOfPoint(playerid, 4.0, PlantData[i][plantPos][0], PlantData[i][plantPos][1], PlantData[i][plantPos][2]))
	{
		if (GetPlayerInterior(playerid) == PlantData[i][plantInterior] && GetPlayerVirtualWorld(playerid) == PlantData[i][plantWorld])
			return i;
	}
	return -1;
}

Crate_Highest(crateid)
{
	new
		Float:height = -1.0,
		id = -1;

    for (new i = 0; i != MAX_CRATES; i ++) if (i != id && CrateData[i][crateExists] && CrateData[i][crateVehicle] == INVALID_VEHICLE_ID && CrateData[i][cratePos][0] == CrateData[crateid][cratePos][0] && CrateData[i][cratePos][1] == CrateData[crateid][cratePos][1] && CrateData[i][cratePos][2] > CrateData[crateid][cratePos][2] && !IsCrateInUse(crateid))
	{
	    if (CrateData[i][cratePos][2] > height)
	    {
	        height = CrateData[i][cratePos][2];
	        id = i;
		}
	}
	return id;
}

Crate_Nearest(playerid, Float:radius = 2.5)
{
	if (PlayerData[playerid][pCarryCrate] != -1 && CrateData[PlayerData[playerid][pCarryCrate]][crateExists])
	    return PlayerData[playerid][pCarryCrate];

    for (new i = 0; i != MAX_CRATES; i ++) if (CrateData[i][crateExists] && IsPlayerInRangeOfPoint(playerid, radius, CrateData[i][cratePos][0], CrateData[i][cratePos][1], CrateData[i][cratePos][2]))
	{
		if (GetPlayerInterior(playerid) == CrateData[i][crateInterior] && GetPlayerVirtualWorld(playerid) == CrateData[i][crateWorld])
			return i;
	}
	return -1;
}

House_Nearest(playerid)
{
    for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]))
	{
		if (GetPlayerInterior(playerid) == HouseData[i][houseExterior] && GetPlayerVirtualWorld(playerid) == HouseData[i][houseExteriorVW])
			return i;
	}
	return -1;
}

House_Refresh(houseid)
{
	if (houseid != -1 && HouseData[houseid][houseExists])
	{
		if (IsValidDynamic3DTextLabel(HouseData[houseid][houseText3D]))
		    DestroyDynamic3DTextLabel(HouseData[houseid][houseText3D]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickupExt]))
		    DestroyDynamicPickup(HouseData[houseid][housePickupExt]);

		if (IsValidDynamicMapIcon(HouseData[houseid][houseMapIcon]))
		    DestroyDynamicMapIcon(HouseData[houseid][houseMapIcon]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickupInt]))
		    DestroyDynamicPickup(HouseData[houseid][housePickupInt]);

		static
		    string[128];

		if (!HouseData[houseid][houseOwner]) 
		{
			HouseData[houseid][housePickupExt] = CreateDynamicPickup(1273, 23, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
			format(string, sizeof(string), ""BLUE_E"Rumah ini untuk dijual! "GREEN_E"(%s)\n"YELLOW_E"%s\n"WHITE_E"Taip "GREEN_E"/buy "WHITE_E"untuk beli", FormatNumber(HouseData[houseid][housePrice]), HouseData[houseid][houseAddress]);
            HouseData[houseid][houseText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
		}
		else 
		{
			format(string, sizeof(string), ""BLUE_E"%s\n"WHITE_E"Tekan "GREEN_E"F "WHITE_E"untuk masuk", HouseData[houseid][houseAddress]);
			HouseData[houseid][housePickupExt] = CreateDynamicPickup(1272, 23, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
			HouseData[houseid][houseText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
		}
        HouseData[houseid][houseMapIcon] = CreateDynamicMapIcon(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], (HouseData[houseid][houseOwner] != 0) ? (32) : (31), 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
		HouseData[houseid][housePickupInt] = CreateDynamicPickup(19130, 23, HouseData[houseid][houseInt][0], HouseData[houseid][houseInt][1], HouseData[houseid][houseInt][2], HouseData[houseid][houseID] + 5000, HouseData[houseid][houseInterior]);
	}
	return 1;
}

Car_GetCount(playerid)
{
	new
		count = 0;

	for (new i = 0; i != MAX_DYNAMIC_CARS; i ++)
	{
		if (CarData[i][carExists] && CarData[i][carOwner] == PlayerData[playerid][pID] && CarData[i][carGov] == 0)
   		{
   		    count++;
		}
	}
	return count;
}

House_GetCount(playerid)
{
	new
		count = 0;

	for (new i = 0; i != MAX_HOUSES; i ++)
	{
		if (HouseData[i][houseExists] && House_IsOwner(playerid, i))
   		{
   		    count++;
		}
	}
	return count;
}

Business_GetCount(playerid)
{
	new
		count = 0;

	for (new i = 0; i != MAX_BUSINESSES; i ++)
	{
		if (BusinessData[i][bizExists] && Business_IsOwner(playerid, i))
   		{
   		    count++;
		}
	}
	return count;
}

Car_IsOwner(playerid, carid)
{
	if (!PlayerData[playerid][pLogged] || PlayerData[playerid][pID] == -1)
	    return 0;

    if ((CarData[carid][carExists] && CarData[carid][carOwner] != 0) && CarData[carid][carOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

Car_WeaponStorage(playerid, carid)
{
    if (!CarData[carid][carExists] || CarData[carid][carLocked])
	    return 0;

    static
	    string[164];

	string[0] = 0;

	for (new i = 0; i < 5; i ++)
	{
	    if (22 <= CarData[carid][carWeapons][i] <= 38)
	        format(string, sizeof(string), "%s%s - Ammo: %d\n", string, ReturnWeaponName(CarData[carid][carWeapons][i]), CarData[carid][carAmmo][i]);

		else
		    format(string, sizeof(string), "%s%s\n", string, (CarData[carid][carWeapons][i]) ? (ReturnWeaponName(CarData[carid][carWeapons][i])) : ("Empty Slot"));
	}
	Dialog_Show(playerid, Trunk, DIALOG_STYLE_LIST, "Car Trunk", string, "Select", "Cancel");
	return 1;
}

Car_ShowTrunk(playerid, carid)
{
	static
	    string[MAX_CAR_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_CAR_STORAGE; i ++)
	{
	    if (!CarStorage[carid][i][cItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else {
			strunpack(name, CarStorage[carid][i][cItemName]);

			if (CarStorage[carid][i][cItemQuantity] == 1) {
                format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, CarStorage[carid][i][cItemQuantity]);
		}
	}
	strcat(string, "Weapon Storage");

	PlayerData[playerid][pStorageSelect] = 0;
	Dialog_Show(playerid, CarStorage, DIALOG_STYLE_LIST, "Car Storage", string, "Select", "Cancel");
	return 1;
}

SetFaction(playerid, id)
{
	if (id != -1 && FactionData[id][factionExists])
	{
		PlayerData[playerid][pFaction] = id;
		PlayerData[playerid][pFactionID] = FactionData[id][factionID];
	}
	return 1;
}

Faction_Refresh(factionid)
{
	if (factionid != -1 && FactionData[factionid][factionExists])
	{
	    if (FactionData[factionid][factionLockerPos][0] != 0.0 && FactionData[factionid][factionLockerPos][1] != 0.0 && FactionData[factionid][factionLockerPos][2] != 0.0)
	    {
		    static
		        string[128];

			if (IsValidDynamicPickup(FactionData[factionid][factionLockerPickup]))
			    DestroyDynamicPickup(FactionData[factionid][factionLockerPickup]);

			if (IsValidDynamic3DTextLabel(FactionData[factionid][factionLockerText3D]))
			    DestroyDynamic3DTextLabel(FactionData[factionid][factionLockerText3D]);
			
			if (IsValidDynamicPickup(FactionData[factionid][factionLeaderLockerPickup]))
			    DestroyDynamicPickup(FactionData[factionid][factionLeaderLockerPickup]);

			if (IsValidDynamic3DTextLabel(FactionData[factionid][factionLeaderLockerText3D]))
			    DestroyDynamic3DTextLabel(FactionData[factionid][factionLeaderLockerText3D]);

			FactionData[factionid][factionLockerPickup] = CreateDynamicPickup(1239, 23, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2], FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);
			FactionData[factionid][factionLeaderLockerPickup] = CreateDynamicPickup(1239, 23, FactionData[factionid][factionLeaderLockerPos][0], FactionData[factionid][factionLeaderLockerPos][1], FactionData[factionid][factionLeaderLockerPos][2], FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);

			format(string, sizeof(string), "[LOCKER]\n{FFFFFF}Press "GREEN_E"Y"WHITE_E" to access the locker.");
	  		FactionData[factionid][factionLockerText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2], 15.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);

			format(string, sizeof(string), "[LEADER LOCKER]\n{FFFFFF}Press "GREEN_E"Y"WHITE_E" to access the locker.");
	  		FactionData[factionid][factionLeaderLockerText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, FactionData[factionid][factionLeaderLockerPos][0], FactionData[factionid][factionLeaderLockerPos][1], FactionData[factionid][factionLeaderLockerPos][2], 15.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);
		}
	}
	return 1;
}

Faction_Save(factionid)
{
	static
	    query[2048];

	format(query, sizeof(query), "UPDATE `factions` SET `factionName` = '%s', `factionColor` = '%d', `factionType` = '%d', `factionRanks` = '%d', `factionMoney` = '%d', `factionLockerX` = '%.4f', `factionLockerY` = '%.4f', `factionLockerZ` = '%.4f', `factionLockerInt` = '%d', `factionLockerWorld` = '%d', `factionLeaderLockerX` = '%.4f', `factionLeaderLockerY` = '%.4f', `factionLeaderLockerZ` = '%.4f', `SpawnX` = '%f', `SpawnY` = '%f', `SpawnZ` = '%f', `SpawnInterior` = '%d', `SpawnVW` = '%d'",
		SQL_ReturnEscaped(FactionData[factionid][factionName]),
		FactionData[factionid][factionColor],
		FactionData[factionid][factionType],
		FactionData[factionid][factionRanks],
		FactionData[factionid][factionMoney],
		FactionData[factionid][factionLockerPos][0],
		FactionData[factionid][factionLockerPos][1],
		FactionData[factionid][factionLockerPos][2],
		FactionData[factionid][factionLockerInt],
		FactionData[factionid][factionLockerWorld],
		FactionData[factionid][factionLeaderLockerPos][0],
		FactionData[factionid][factionLeaderLockerPos][1],
		FactionData[factionid][factionLeaderLockerPos][2],
		FactionData[factionid][SpawnX],
		FactionData[factionid][SpawnY],
		FactionData[factionid][SpawnZ],
		FactionData[factionid][SpawnInterior],
		FactionData[factionid][SpawnVW]
	);
	for (new i = 0; i < 10; i ++)
	{
	    format(query, sizeof(query), "%s, `factionWeapon%d` = '%d', `factionAmmo%d` = '%d'", query, i + 1, FactionData[factionid][factionWeapons][i], i + 1, FactionData[factionid][factionAmmo][i]);
	}
	for (new i = 0; i < 14; i ++)
	{
		format(query, sizeof(query), "%s, `factionSkin%d` = '%d'", query, i + 1, FactionData[factionid][factionSkins][i], i + 1);
	}
	format(query, sizeof(query), "%s WHERE `factionID` = '%d'",
		query,
		FactionData[factionid][factionID]
	);
	return mysql_tquery(g_iHandle, query);
}

Faction_Delete(factionid)
{
	if (factionid != -1 && FactionData[factionid][factionExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `factions` WHERE `factionID` = '%d'", FactionData[factionid][factionID]);
		mysql_tquery(g_iHandle, string);

		format(string, sizeof(string), "UPDATE `characters` SET `Faction` = '-1' WHERE `Faction` = '%d'", FactionData[factionid][factionID]);
		mysql_tquery(g_iHandle, string);

		foreach (new i : Player)
		{
			if (PlayerData[i][pFaction] == factionid) {
		    	PlayerData[i][pFaction] = -1;
		    	PlayerData[i][pFactionID] = -1;
		    	PlayerData[i][pFactionRank] = -1;
			}
			if (PlayerData[i][pFactionEdit] == factionid) {
			    PlayerData[i][pFactionEdit] = -1;
			}
		}
		if (IsValidDynamicPickup(FactionData[factionid][factionLockerPickup]))
  			DestroyDynamicPickup(FactionData[factionid][factionLockerPickup]);

		if (IsValidDynamic3DTextLabel(FactionData[factionid][factionLockerText3D]))
  			DestroyDynamic3DTextLabel(FactionData[factionid][factionLockerText3D]);

		if (IsValidDynamicPickup(FactionData[factionid][factionLeaderLockerPickup]))
			DestroyDynamicPickup(FactionData[factionid][factionLeaderLockerPickup]);

		if (IsValidDynamic3DTextLabel(FactionData[factionid][factionLeaderLockerText3D]))
			DestroyDynamic3DTextLabel(FactionData[factionid][factionLeaderLockerText3D]);
			
	    FactionData[factionid][factionExists] = false;
	    FactionData[factionid][factionType] = 0;
	    FactionData[factionid][factionID] = 0;
	}
	return 1;
}

Faction_ShowRanks(playerid, factionid)
{
    if (factionid != -1 && FactionData[factionid][factionExists])
	{
		static
		    string[640];

		string[0] = 0;

		for (new i = 0; i < FactionData[factionid][factionRanks]; i ++)
		    format(string, sizeof(string), "%sRank %d: %s\n", string, i + 1, FactionRanks[factionid][i]);

		PlayerData[playerid][pFactionEdit] = factionid;
		Dialog_Show(playerid, EditRanks, DIALOG_STYLE_LIST, FactionData[factionid][factionName], string, "Change", "Cancel");
	}
	return 1;
}

Faction_Create(name[], type)
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (!FactionData[i][factionExists])
	{
	    format(FactionData[i][factionName], 32, name);

        FactionData[i][factionExists] = true;
        FactionData[i][factionColor] = 0xFFFFFF00;
        FactionData[i][factionType] = type;
        FactionData[i][factionRanks] = 5;

        FactionData[i][factionLockerPos][0] = 0.0;
        FactionData[i][factionLockerPos][1] = 0.0;
        FactionData[i][factionLockerPos][2] = 0.0;
        FactionData[i][factionLockerInt] = 0;
        FactionData[i][factionLockerWorld] = 0;

		FactionData[i][factionLeaderLockerPos][0] = 0.0;
        FactionData[i][factionLeaderLockerPos][1] = 0.0;
        FactionData[i][factionLeaderLockerPos][2] = 0.0;

        for (new j = 0; j < 14; j ++) {
            FactionData[i][factionSkins][j] = 0;
        }
        for (new j = 0; j < 10; j ++) {
            FactionData[i][factionWeapons][j] = 0;
            FactionData[i][factionAmmo][j] = 0;
	    }
	    for (new j = 0; j < 15; j ++) {
			format(FactionRanks[i][j], 32, "Rank %d", j + 1);
	    }
	    mysql_tquery(g_iHandle, "INSERT INTO `factions` (`factionType`) VALUES(0)", "OnFactionCreated", "d", i);
	    return i;
	}
	return -1;
}

Plant_Delete(plantid)
{
	if (plantid != -1 && PlantData[plantid][plantExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `plants` WHERE `plantID` = '%d'", PlantData[plantid][plantID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(PlantData[plantid][plantText3D]))
		    DestroyDynamic3DTextLabel(PlantData[plantid][plantText3D]);

		if (IsValidDynamicObject(PlantData[plantid][plantObject]))
		    DestroyDynamicObject(PlantData[plantid][plantObject]);

	    PlantData[plantid][plantExists] = false;
		PlantData[plantid][plantID] = 0;
	    PlantData[plantid][plantDrugs] = 0;
	}
	return 1;
}

Plant_Create(playerid, type)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
	    for (new i = 0; i != MAX_DRUG_PLANTS; i ++) if (!PlantData[i][plantExists])
	    {
	        PlantData[i][plantExists] = true;
	        PlantData[i][plantType] = type;
	        PlantData[i][plantDrugs] = 0;

	        PlantData[i][plantPos][0] = x;
	        PlantData[i][plantPos][1] = y;
	        PlantData[i][plantPos][2] = z;
	        PlantData[i][plantPos][3] = angle;
	        PlantData[i][plantInterior] = GetPlayerInterior(playerid);
	        PlantData[i][plantWorld] = GetPlayerVirtualWorld(playerid);

	        mysql_tquery(g_iHandle, "INSERT INTO `plants` (`plantType`) VALUES(0)", "OnPlantCreated", "d", i);
	        Plant_Refresh(i);
	        return i;
		}
	}
	return -1;
}

Plant_MaxGrams(type)
{
	new grams;

	switch (type)
	{
	    case 1: grams = 40; // Marijuana plant
	    case 2: grams = 30; // Cocaine plant
		case 3: grams = 25; // Heroin plant
		default: grams = 0;
	}
	return grams;
}

Plant_Save(plantid)
{
	static
	    query[256];

	format(query, sizeof(query), "UPDATE `plants` SET `plantType` = '%d', `plantDrugs` = '%d', `plantX` = '%.4f', `plantY` = '%.4f', `plantZ` = '%.4f', `plantA` = '%.4f', `plantInterior` = '%d', `plantWorld` = '%d' WHERE `plantID` = '%d'",
        PlantData[plantid][plantType],
        PlantData[plantid][plantDrugs],
        PlantData[plantid][plantPos][0],
        PlantData[plantid][plantPos][1],
        PlantData[plantid][plantPos][2],
        PlantData[plantid][plantPos][3],
        PlantData[plantid][plantInterior],
        PlantData[plantid][plantWorld],
        PlantData[plantid][plantID]
	);
	return mysql_tquery(g_iHandle, query);
}

Plant_GetType(type)
{
	static
	    str[16];

    switch (type) {
    	case 1: str = "Marijuana";
    	case 2: str = "Cocaine";
	    case 3: str = "Heroin";
	}
	return str;
}

Plant_Refresh(plantid)
{
	if (plantid != -1 && PlantData[plantid][plantExists])
	{
	    static
	        string[128];

		if (IsValidDynamicObject(PlantData[plantid][plantObject]))
		    DestroyDynamicObject(PlantData[plantid][plantObject]);

		if (IsValidDynamic3DTextLabel(PlantData[plantid][plantText3D]))
		    DestroyDynamic3DTextLabel(PlantData[plantid][plantText3D]);

		PlantData[plantid][plantObject] = CreateDynamicObject(3409, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2] - 1.80, 0.0, 0.0, PlantData[plantid][plantPos][3], PlantData[plantid][plantWorld], PlantData[plantid][plantInterior]);

		format(string, sizeof(string), "[PLANT]\n{FFFFFF}"GREEN_E"%s "WHITE_E"- "YELLOW_E"%d"WHITE_E"/"YELLOW_E"%d "WHITE_E"Grams", Plant_GetType(PlantData[plantid][plantType]), PlantData[plantid][plantDrugs], Plant_MaxGrams(PlantData[plantid][plantType]));
  		PlantData[plantid][plantText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, PlantData[plantid][plantPos][0], PlantData[plantid][plantPos][1], PlantData[plantid][plantPos][2], 10.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, PlantData[plantid][plantWorld], PlantData[plantid][plantInterior]);
	}
	return 1;
}

Crate_Refresh(crateid)
{
	if (crateid != -1 && CrateData[crateid][crateExists])
	{
	    static
	        string[128];

		if (IsValidDynamicObject(CrateData[crateid][crateObject]))
		    DestroyDynamicObject(CrateData[crateid][crateObject]);

		if (IsValidDynamic3DTextLabel(CrateData[crateid][crateText3D]))
		    DestroyDynamic3DTextLabel(CrateData[crateid][crateText3D]);

		CrateData[crateid][crateObject] = CreateDynamicObject(964, CrateData[crateid][cratePos][0], CrateData[crateid][cratePos][1], CrateData[crateid][cratePos][2], 0.0, 0.0, CrateData[crateid][cratePos][3], CrateData[crateid][crateWorld], CrateData[crateid][crateInterior]);

		if (CrateData[crateid][crateType] != 6) {
			format(string, sizeof(string), "CREATE: "YELLOW_E" %s"WHITE_E" Parts\nPress "GREEN_E"ALT"WHITE_E" to pickup", Crate_GetType(CrateData[crateid][crateType]));
		}
		else {
		    format(string, sizeof(string), "CREATE: "YELLOW_E"Drug Seeds"WHITE_E"\nPress "GREEN_E"ALT"WHITE_E" to pickup");
		}
  		CrateData[crateid][crateText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, CrateData[crateid][cratePos][0], CrateData[crateid][cratePos][1], CrateData[crateid][cratePos][2] + 0.5, 10.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, CrateData[crateid][crateWorld], CrateData[crateid][crateInterior]);
	}
	return 1;
}

Crate_Delete(crateid)
{
	if (crateid != -1 && CrateData[crateid][crateExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `crates` WHERE `crateID` = '%d'", CrateData[crateid][crateID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(CrateData[crateid][crateText3D]))
		    DestroyDynamic3DTextLabel(CrateData[crateid][crateText3D]);

		if (IsValidDynamicObject(CrateData[crateid][crateObject]))
		    DestroyDynamicObject(CrateData[crateid][crateObject]);

		foreach (new i : Player) if (PlayerData[i][pCarryCrate] == crateid) {
		    PlayerData[i][pCarryCrate] = -1;

		    RemovePlayerAttachedObject(i, 4);
		    SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);
		}
	    CrateData[crateid][crateExists] = false;
	    CrateData[crateid][crateID] = 0;
	    CrateData[crateid][crateVehicle] = INVALID_VEHICLE_ID;
	}
	return 1;
}

Crate_Drop(playerid, Float:radius = 0.0)
{
    static
		Float:x,
		Float:y,
		Float:z,
		Float:angle,
		id = -1;

	if ((id = PlayerData[playerid][pCarryCrate]) != -1 && CrateData[id][crateExists])
	{
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		if (radius != 0.0) {
		    x += radius * floatsin(-angle, degrees);
		    y += radius * floatcos(-angle, degrees);
		}
		CrateData[id][cratePos][0] = x;
		CrateData[id][cratePos][1] = y;
		CrateData[id][cratePos][2] = z - 0.9;
		CrateData[id][cratePos][3] = angle;
		CrateData[id][crateInterior] = GetPlayerInterior(playerid);
		CrateData[id][crateWorld] = GetPlayerVirtualWorld(playerid);

		Crate_Refresh(id);
		Crate_Save(id);
	}
	PlayerData[playerid][pCarryCrate] = -1;
	RemovePlayerAttachedObject(playerid, 4);
	return 1;
}

Crate_Save(crateid)
{
	static
	    query[255];

	format(query, sizeof(query), "UPDATE `crates` SET `crateType` = '%d', `crateX` = '%.4f', `crateY` = '%.4f', `crateZ` = '%.4f', `crateA` = '%.4f', `crateInterior` = '%d', `crateWorld` = '%d' WHERE `crateID` = '%d'",
	    CrateData[crateid][crateType],
	    CrateData[crateid][cratePos][0],
	    CrateData[crateid][cratePos][1],
	    CrateData[crateid][cratePos][2],
	    CrateData[crateid][cratePos][3],
	    CrateData[crateid][crateInterior],
	    CrateData[crateid][crateWorld],
	    CrateData[crateid][crateID]
	);
	return mysql_tquery(g_iHandle, query);
}

Crate_GetType(type)
{
	static
	    str[24];

	switch (type) {
	    case 1: str = "Melee";
	    case 2: str = "Pistol";
	    case 3: str = "SMG";
	    case 4: str = "Shotgun";
	    case 5: str = "Rifle";
	    case 6: str = "Drug Seeds";
	    default: str = "None";
	}
	return str;
}

Crate_Create(playerid, type)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
	    for (new i = 0; i != MAX_CRATES; i ++) if (!CrateData[i][crateExists])
	    {
         	if (Crate_Nearest(playerid, 2.5) != -1) {
			 	z = floatsub(z, 0.1);
	        }
            CrateData[i][crateExists] = true;
            CrateData[i][crateVehicle] = INVALID_VEHICLE_ID;
            CrateData[i][crateType] = type;

			CrateData[i][cratePos][0] = x;
   			CrateData[i][cratePos][1] = y;
            CrateData[i][cratePos][2] = z - 0.9;
            CrateData[i][cratePos][3] = angle;

            CrateData[i][crateInterior] = GetPlayerInterior(playerid);
            CrateData[i][crateWorld] = GetPlayerVirtualWorld(playerid);

            mysql_tquery(g_iHandle, "INSERT INTO `crates` (`crateInterior`) VALUES(0)", "OnCrateCreated", "d", i);
            Crate_Refresh(i);
            return i;
		}
	}
	return -1;
}

Job_Save(jobid)
{
	static
	    query[512];

	format(query, sizeof(query), "UPDATE `jobs` SET `jobType` = '%d', `jobPosX` = '%.4f', `jobPosY` = '%.4f', `jobPosZ` = '%.4f', `jobInterior` = '%d', `jobWorld` = '%d', `jobPointX` = '%.4f', `jobPointY` = '%.4f', `jobPointZ` = '%.4f', `jobDeliverX` = '%.4f', `jobDeliverY` = '%.4f', `jobDeliverZ` = '%.4f', `jobPointInt` = '%d', `jobPointWorld` = '%d' WHERE `jobID` = '%d'",
	    JobData[jobid][jobType],
	    JobData[jobid][jobPos][0],
	    JobData[jobid][jobPos][1],
	    JobData[jobid][jobPos][2],
	    JobData[jobid][jobInterior],
	    JobData[jobid][jobWorld],
	    JobData[jobid][jobPoint][0],
	    JobData[jobid][jobPoint][1],
	    JobData[jobid][jobPoint][2],
	    JobData[jobid][jobDeliver][0],
	    JobData[jobid][jobDeliver][1],
	    JobData[jobid][jobDeliver][2],
	    JobData[jobid][jobPointInt],
	    JobData[jobid][jobPointWorld],
	    JobData[jobid][jobID]
	);
	return mysql_tquery(g_iHandle, query);
}

Job_GetName(type)
{
	static
	    str[24];

	switch (type)
	{
	    case 1: str = "Courier";
		case 2: str = "Package Sorter";
		case 3: str = "Taxi Driver";
		case 4: str = "Weapon Smuggler";
		case 5: str = "Miner";
		case 6: str = "Food Vendor";
		case 7: str = "Garbage Man";
	    default: str = "None";
	}
	return str;
}

Job_Refresh(jobid)
{
	if (jobid != -1 && JobData[jobid][jobExists])
	{
	    for (new i = 0; i < 3; i ++) {
			if (IsValidDynamic3DTextLabel(JobData[jobid][jobText3D][i]))
		    	DestroyDynamic3DTextLabel(JobData[jobid][jobText3D][i]);

			if (IsValidDynamicPickup(JobData[jobid][jobPickups][i]))
		    	DestroyDynamicPickup(JobData[jobid][jobPickups][i]);
		}
		static
		    string[90];

		format(string, sizeof(string), "[%s]\n{FFFFFF}Type '/takejob' to acquire this job!", Job_GetName(JobData[jobid][jobType]));

		if (JobData[jobid][jobType] == 1) {
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel("[COURIER JOB]\n{FFFFFF}Type '/startdelivery' to start a delivery.", COLOR_DARKBLUE, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		}
		else if (JobData[jobid][jobType] == 4) {
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel("[WEAPON PARTS]\n{FFFFFF}Type '/craftparts' to craft a weapon crate.", COLOR_DARKBLUE, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		}
		else if (JobData[jobid][jobType] == 5) {
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel("[MINING JOB]\n{FFFFFF}Type '/mine' to begin mining.", COLOR_DARKBLUE, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);

			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel("[MINING JOB]\n{FFFFFF}Deliver your mining rocks at this spot.", COLOR_DARKBLUE, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], 15.0);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]);
		}
		else if (JobData[jobid][jobType] == 7) {
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel("[GARBAGE DUMP]\n{FFFFFF}Type '/dumpgarbage' to dump your trash.", COLOR_DARKBLUE, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1264, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		}
		else if (JobData[jobid][jobType] == 8) {
			JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel("[PACKAGE SORTING]\n{FFFFFF}Type '/sorting' to begin sorting packages.", COLOR_DARKBLUE, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);

			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel("[PACKAGE SORTING]\n{FFFFFF}Deliver your packages here for sorting.", COLOR_DARKBLUE, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], 15.0);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]);
		}
		JobData[jobid][jobText3D][0] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, JobData[jobid][jobPos][0], JobData[jobid][jobPos][1], JobData[jobid][jobPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobWorld], JobData[jobid][jobInterior]);
        JobData[jobid][jobPickups][0] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPos][0], JobData[jobid][jobPos][1], JobData[jobid][jobPos][2], JobData[jobid][jobWorld], JobData[jobid][jobInterior]);
	}
	return 1;
}

Job_Delete(jobid)
{
	if (jobid != -1 && JobData[jobid][jobExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `jobs` WHERE `jobID` = '%d'", JobData[jobid][jobID]);
		mysql_tquery(g_iHandle, string);

        for (new i = 0; i < 3; i ++) {
			if (IsValidDynamic3DTextLabel(JobData[jobid][jobText3D][i]))
		    	DestroyDynamic3DTextLabel(JobData[jobid][jobText3D][i]);

			if (IsValidDynamicPickup(JobData[jobid][jobPickups][i]))
		    	DestroyDynamicPickup(JobData[jobid][jobPickups][i]);
		}
		JobData[jobid][jobExists] = false;
	    JobData[jobid][jobType] = 0;
	    JobData[jobid][jobID] = 0;
	}
	return 1;
}

Job_Create(playerid, type)
{
	static
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++)
		{
	    	if (!JobData[i][jobExists])
	    	{
	        	JobData[i][jobExists] = true;
	        	JobData[i][jobType] = type;

				JobData[i][jobPos][0] = x;
	        	JobData[i][jobPos][1] = y;
	        	JobData[i][jobPos][2] = z;
	        	JobData[i][jobPoint][0] = 0.0;
	        	JobData[i][jobPoint][1] = 0.0;
	        	JobData[i][jobPoint][2] = 0.0;
	        	JobData[i][jobDeliver][0] = 0.0;
	        	JobData[i][jobDeliver][1] = 0.0;
	        	JobData[i][jobDeliver][2] = 0.0;

	        	JobData[i][jobInterior] = GetPlayerInterior(playerid);
	        	JobData[i][jobWorld] = GetPlayerVirtualWorld(playerid);

                JobData[i][jobPointInt] = 0;
                JobData[i][jobPointWorld] = 0;

	        	Job_Refresh(i);
	        	mysql_tquery(g_iHandle, "INSERT INTO `jobs` (`jobInterior`) VALUES(0)", "OnJobCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

Car_Create(ownerid, modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, rental = 0)
{
    for (new i = 0; i != MAX_DYNAMIC_CARS; i ++)
	{
		if (!CarData[i][carExists])
   		{
   		    if (color1 == -1)
   		        color1 = random(127);

			if (color2 == -1)
			    color2 = random(127);

   		    CarData[i][carExists] = true;
            CarData[i][carModel] = modelid;
            CarData[i][carOwner] = ownerid;
			CarData[i][carHealth] = 1000;
            CarData[i][carFuel] = 100;
			CarData[i][carSiren] = 0;
			CarData[i][carGov] = 0;
			CarData[i][carTemperature] = 0;

			new rand = RandomEx(1111, 9999);
			format(CarData[i][carPlate], 32, "SR %d", rand);

            CarData[i][carPos][0] = x;
            CarData[i][carPos][1] = y;
            CarData[i][carPos][2] = z;
            CarData[i][carPos][3] = angle;

            CarData[i][carColor1] = color1;
            CarData[i][carColor2] = color2;
            CarData[i][carPaintjob] = -1;
            CarData[i][carLocked] = false;
            CarData[i][carImpounded] = 0;
            CarData[i][carImpoundPrice] = 0;
			CarData[i][carRent] = rental;

            for (new j = 0; j < 14; j ++)
			{
                if (j < 5)
				{
                    CarData[i][carWeapons][j] = 0;
                    CarData[i][carAmmo][j] = 0;
                }
                CarData[i][carMods][j] = 0;
            }
            Car_Spawn(i);

            if (CarData[i][carVehicle] != INVALID_VEHICLE_ID) {
                ResetVehicle(CarData[i][carVehicle]);
            }
            mysql_tquery(g_iHandle, "INSERT INTO `cars` (`carModel`) VALUES(0)", "OnCarCreated", "d", i);
            return i;
		}
	}
	return -1;
}

Car_Delete(carid)
{
    if (carid != -1 && CarData[carid][carExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `cars` WHERE `carID` = '%d'", CarData[carid][carID]);
		mysql_tquery(g_iHandle, string);

		if (IsValidVehicle(CarData[carid][carVehicle]))
			DestroyVehicle(CarData[carid][carVehicle]);

		for (new i = 0; i < MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && BackpackData[i][backpackVehicle] == CarData[carid][carID]) {
		    Backpack_Delete(i);
		}
		Car_RemoveAllItems(carid);

        CarData[carid][carExists] = false;
	    CarData[carid][carID] = 0;
	    CarData[carid][carOwner] = 0;
	    CarData[carid][carVehicle] = 0;
	}
	return 1;
}


Car_Save(carid)
{
	if(IsValidVehicle(CarData[carid][carVehicle]) && CarData[carid][carVehicle] != INVALID_VEHICLE_ID)
	{
		GetVehicleHealth(CarData[carid][carVehicle], CarData[carid][carHealth]);
		GetVehiclePos(CarData[carid][carVehicle], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2]);
		GetVehicleZAngle(CarData[carid][carVehicle], CarData[carid][carPos][3]);
	}

	static
	    query[900];

	if (CarData[carid][carVehicle] != INVALID_VEHICLE_ID)
	{
	    for (new i = 0; i < 14; i ++) {
			CarData[carid][carMods][i] = GetVehicleComponentInSlot(CarData[carid][carVehicle], i);
	    }
	}
	format(query, sizeof(query), "UPDATE `cars` SET `carModel` = '%d', `carOwner` = '%d', `carPlate` = '%s', carHealth = '%f', carFuel = '%d', carTemperature = '%d',  carSiren = '%d',  carGov = '%d', `carPosX` = '%.4f', `carPosY` = '%.4f', `carPosZ` = '%.4f', `carPosR` = '%.4f', `carColor1` = '%d', `carColor2` = '%d', `carPaintjob` = '%d', `carLocked` = '%d', `carRent` = '%d'",
        CarData[carid][carModel],
        CarData[carid][carOwner],
		CarData[carid][carPlate],
		CarData[carid][carHealth],
		CarData[carid][carFuel],
		CarData[carid][carTemperature],
		CarData[carid][carSiren],
		CarData[carid][carGov],
        CarData[carid][carPos][0],
        CarData[carid][carPos][1],
        CarData[carid][carPos][2],
        CarData[carid][carPos][3],
        CarData[carid][carColor1],
        CarData[carid][carColor2],
        CarData[carid][carPaintjob],
        CarData[carid][carLocked],
		CarData[carid][carRent]
	);
	format(query, sizeof(query), "%s, `carMod1` = '%d', `carMod2` = '%d', `carMod3` = '%d', `carMod4` = '%d', `carMod5` = '%d', `carMod6` = '%d', `carMod7` = '%d', `carMod8` = '%d', `carMod9` = '%d', `carMod10` = '%d', `carMod11` = '%d', `carMod12` = '%d', `carMod13` = '%d', `carMod14` = '%d'",
		query,
		CarData[carid][carMods][0],
		CarData[carid][carMods][1],
		CarData[carid][carMods][2],
		CarData[carid][carMods][3],
		CarData[carid][carMods][4],
		CarData[carid][carMods][5],
		CarData[carid][carMods][6],
		CarData[carid][carMods][7],
		CarData[carid][carMods][8],
		CarData[carid][carMods][9],
		CarData[carid][carMods][10],
		CarData[carid][carMods][11],
		CarData[carid][carMods][12],
		CarData[carid][carMods][13]
	);
	format(query, sizeof(query), "%s, `carImpounded` = '%d', `carImpoundPrice` = '%d', `carWeapon1` = '%d', `carWeapon2` = '%d', `carWeapon3` = '%d', `carWeapon4` = '%d', `carWeapon5` = '%d', `carAmmo1` = '%d', `carAmmo2` = '%d', `carAmmo3` = '%d', `carAmmo4` = '%d', `carAmmo5` = '%d' WHERE `carID` = '%d'",
		query,
		CarData[carid][carImpounded],
		CarData[carid][carImpoundPrice],
		CarData[carid][carWeapons][0],
		CarData[carid][carWeapons][1],
		CarData[carid][carWeapons][2],
		CarData[carid][carWeapons][3],
		CarData[carid][carWeapons][4],
		CarData[carid][carAmmo][0],
		CarData[carid][carAmmo][1],
		CarData[carid][carAmmo][2],
		CarData[carid][carAmmo][3],
		CarData[carid][carAmmo][4],
		CarData[carid][carID]
	);
	return mysql_tquery(g_iHandle, query);
}

RemovePlayerCar(playerid)
{
	for (new i = 0; i != MAX_DYNAMIC_CARS; i ++)
	{
		if (Car_IsOwner(playerid, i))
		{
			Car_Save(i);
			if(CarData[i][carVehicle] != 0)
			{
				if(IsValidVehicle(CarData[i][carVehicle])) DestroyVehicle(CarData[i][carVehicle]);
				CarData[i][carVehicle] = 0;
			}
		}
	}
	return 1;
}

Entrance_Delete(entranceid)
{
	if (entranceid != -1 && EntranceData[entranceid][entranceExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `entrances` WHERE `entranceID` = '%d'", EntranceData[entranceid][entranceID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]))
		    DestroyDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickupExt]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickupExt]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickupInt]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickupInt]);

		if (IsValidDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]))
		    DestroyDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]);

	    EntranceData[entranceid][entranceExists] = false;
	    EntranceData[entranceid][entranceID] = 0;
	}
	return 1;
}

Entrance_Save(entranceid)
{
	static
	    query[1024];

	format(query, sizeof(query), "UPDATE `entrances` SET `entranceName` = '%s', `entrancePass` = '%s', `entranceIcon` = '%d', `entranceLocked` = '%d', `entrancePosX` = '%.4f', `entrancePosY` = '%.4f', `entrancePosZ` = '%.4f', `entrancePosA` = '%.4f', `entranceIntX` = '%.4f', `entranceIntY` = '%.4f', `entranceIntZ` = '%.4f', `entranceIntA` = '%.4f', `entranceInterior` = '%d', `entranceExterior` = '%d', `entranceExteriorVW` = '%d'",
	    SQL_ReturnEscaped(EntranceData[entranceid][entranceName]),
	    SQL_ReturnEscaped(EntranceData[entranceid][entrancePass]),
	    EntranceData[entranceid][entranceIcon],
	    EntranceData[entranceid][entranceLocked],
	    EntranceData[entranceid][entrancePos][0],
	    EntranceData[entranceid][entrancePos][1],
	    EntranceData[entranceid][entrancePos][2],
	    EntranceData[entranceid][entrancePos][3],
	    EntranceData[entranceid][entranceInt][0],
	    EntranceData[entranceid][entranceInt][1],
	    EntranceData[entranceid][entranceInt][2],
	    EntranceData[entranceid][entranceInt][3],
	    EntranceData[entranceid][entranceInterior],
	    EntranceData[entranceid][entranceExterior],
	    EntranceData[entranceid][entranceExteriorVW]
	);
	format(query, sizeof(query), "%s, `entranceCustom` = '%d', `entranceWorld` = '%d' WHERE `entranceID` = '%d'",
	    query,
	    EntranceData[entranceid][entranceCustom],
	    EntranceData[entranceid][entranceWorld],
	    EntranceData[entranceid][entranceID]
	);
	return mysql_tquery(g_iHandle, query);
}

IsPlayerNearMine(playerid)
{
	new
	    id = -1;

	if ((id = Job_NearestPoint(playerid, 10.0)) != -1 && JobData[id][jobType] == 5)
		return 1;

	return 0;
}

Entrance_Inside(playerid)
{
	if (PlayerData[playerid][pEntrance] != -1)
	{
	    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && GetPlayerInterior(playerid) == EntranceData[i][entranceInterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceWorld])
	        return i;
	}
	return -1;
}

Entrance_GetLink(playerid)
{
	if (GetPlayerVirtualWorld(playerid) > 0)
	{
	    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceID] == GetPlayerVirtualWorld(playerid) - 7000)
			return EntranceData[i][entranceID];
	}
	return -1;
}

Entrance_Nearest(playerid)
{
    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && IsPlayerInRangeOfPoint(playerid, 2.5, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]))
	{
		if (GetPlayerInterior(playerid) == EntranceData[i][entranceExterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceExteriorVW])
			return i;
	}
	return -1;
}

Job_NearestPoint(playerid, Float:radius = 4.0)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint][0], JobData[i][jobPoint][1], JobData[i][jobPoint][2])) {
		return i;
	}
	return -1;
}

Job_Nearest(playerid)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, 2.5, JobData[i][jobPos][0], JobData[i][jobPos][1], JobData[i][jobPos][2]))
	{
		if (GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
			return i;
	}
	return -1;
}

Entrance_Refresh(entranceid)
{
	if (entranceid != -1 && EntranceData[entranceid][entranceExists])
	{
		if (IsValidDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]))
		    DestroyDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickupExt]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickupExt]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickupInt]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickupInt]);

		if (IsValidDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]))
		    DestroyDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]);

		static
		    string[90];

		format(string, sizeof(string), "%s\n"WHITE_E"Tekan "GREEN_E"F "WHITE_E"untuk masuk", EntranceData[entranceid][entranceName]);

		EntranceData[entranceid][entranceText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);
        EntranceData[entranceid][entrancePickupExt] = CreateDynamicPickup(19132, 23, EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2], EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);
		EntranceData[entranceid][entrancePickupInt] = CreateDynamicPickup(19130, 23, EntranceData[entranceid][entranceInt][0], EntranceData[entranceid][entranceInt][1], EntranceData[entranceid][entranceInt][2], EntranceData[entranceid][entranceWorld], EntranceData[entranceid][entranceInterior]);

		if (EntranceData[entranceid][entranceIcon] != 0)
			EntranceData[entranceid][entranceMapIcon] = CreateDynamicMapIcon(EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2], EntranceData[entranceid][entranceIcon], 0, EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);
	}
	return 1;
}

Entrance_Create(playerid, name[])
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

    if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_HOUSES; i ++)
		{
	    	if (!EntranceData[i][entranceExists])
		    {
    	        EntranceData[i][entranceExists] = true;
        	    EntranceData[i][entranceIcon] = 0;
        	    EntranceData[i][entranceCustom] = 0;
        	    EntranceData[i][entranceLocked] = 0;

				format(EntranceData[i][entranceName], 32, name);
				EntranceData[i][entrancePass][0] = 0;

    	        EntranceData[i][entrancePos][0] = x;
    	        EntranceData[i][entrancePos][1] = y;
    	        EntranceData[i][entrancePos][2] = z;
    	        EntranceData[i][entrancePos][3] = angle;

                EntranceData[i][entranceInt][0] = x;
                EntranceData[i][entranceInt][1] = y;
                EntranceData[i][entranceInt][2] = z + 10000;
                EntranceData[i][entranceInt][3] = 0.0000;

				EntranceData[i][entranceInterior] = 0;
				EntranceData[i][entranceExterior] = GetPlayerInterior(playerid);
				EntranceData[i][entranceExteriorVW] = GetPlayerVirtualWorld(playerid);

				Entrance_Refresh(i);
				mysql_tquery(g_iHandle, "INSERT INTO `entrances` (`entranceIcon`) VALUES(0)", "OnEntranceCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

Business_RemoveVehicle(bizid, modelid)
{
	static
	    query[128];

    for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++) if (DealershipCars[bizid][i][vehModel] == modelid)
	{
	    DealershipCars[bizid][i][vehModel] = 0;
	    DealershipCars[bizid][i][vehPrice] = 0;

	    format(query, sizeof(query), "DELETE FROM `dealervehicles` WHERE `ID` = '%d' AND `vehID` = '%d'", BusinessData[bizid][bizID], DealershipCars[bizid][i][vehID]);
		mysql_tquery(g_iHandle, query);

		return 1;
	}
	return 0;
}

Business_AddVehicle(bizid, modelid, price)
{
	static
	    query[128];

	for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++) if (!DealershipCars[bizid][i][vehModel])
	{
	    DealershipCars[bizid][i][vehModel] = modelid;
	    DealershipCars[bizid][i][vehPrice] = price;

	    format(query, sizeof(query), "INSERT INTO `dealervehicles` (`ID`, `vehModel`, `vehPrice`) VALUES('%d', '%d', '%d')", BusinessData[bizid][bizID], modelid, price);
	    mysql_tquery(g_iHandle, query, "OnDealerCarCreated", "dd", bizid, i);

	    return 1;
	}
	return 0;
}

Business_CarMenu(playerid, bizid)
{
 	static
	    cars[MAX_DEALERSHIP_CARS];

    for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
	{
		if (!DealershipCars[bizid][i][vehModel])
			cars[i] = 19300;

		else
		    cars[i] = DealershipCars[bizid][i][vehModel];
	}
	ShowModelSelectionMenu(playerid, "Purchase Car", MODEL_SELECTION_BUY_CAR, cars, sizeof(cars), -16.0, 0.0, -55.0, 0.9, 1);
	return 1;
}

Business_EditCars(playerid, bizid)
{
	static
	    cars[MAX_DEALERSHIP_CARS];

    for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
	{
		if (!DealershipCars[bizid][i][vehModel])
			cars[i] = 19300;

		else
		    cars[i] = DealershipCars[bizid][i][vehModel];
	}
	ShowModelSelectionMenu(playerid, "Dealership Cars", MODEL_SELECTION_DEALER, cars, sizeof(cars), -16.0, 0.0, -55.0, 0.9, 1);
	return 1;
}

Pump_GetFreeID()
{
	for (new i = 0; i < MAX_GAS_PUMPS; i ++) if (!PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

Pump_Delete(pumpid)
{
	if (pumpid != -1 && PumpData[pumpid][pumpExists])
	{
	    new
	        string[90];

		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `ID` = '%d' AND `pumpID` = '%d'", BusinessData[PumpData[pumpid][pumpBusiness]][bizID], PumpData[pumpid][pumpID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D]))
		    DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);

		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]))
		    DestroyDynamicObject(PumpData[pumpid][pumpObject]);

		foreach (new i : Player) if (PlayerData[i][pGasPump] == pumpid) {
		    StopRefilling(i);
		}
	    PumpData[pumpid][pumpExists] = false;
	    PumpData[pumpid][pumpFuel] = 0;
	}
	return 1;
}

Pump_Create(playerid, bizid)
{
    static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle,
		string[64],
		id = -1;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		if ((id = Pump_GetFreeID()) != -1)
  		{
	        x += 5.0 * floatsin(-angle, degrees);
	        y += 5.0 * floatcos(-angle, degrees);

			PumpData[id][pumpExists] = true;
			PumpData[id][pumpBusiness] = bizid;
			PumpData[id][pumpPos][0] = x;
			PumpData[id][pumpPos][1] = y;
			PumpData[id][pumpPos][2] = z;
			PumpData[id][pumpPos][3] = angle;
            PumpData[id][pumpFuel] = 2000;
			PumpData[id][pumpObject] = CreateDynamicObject(1676, x, y, z, 0.0, 0.0, angle);

			format(string, sizeof(string), "INSERT INTO `pumps` (`ID`) VALUES(%d)", BusinessData[bizid][bizID]);
			mysql_tquery(g_iHandle, string, "OnPumpCreated", "d", id);
			return id;
		}
	}
	return -1;
}

Pump_Refresh(pumpid)
{
	if (pumpid != -1 && PumpData[pumpid][pumpExists])
	{
	    static
	        string[128];

		format(string, sizeof(string), "[GAS PUMP]\n{FFFFFF}Fuel Left:"YELLOW_E" %d"WHITE_E" liters\nPress "GREEN_E"Y"WHITE_E" to refuel the vehicle.", PumpData[pumpid][pumpFuel]);

        if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D]))
            DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);

		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]))
		    DestroyDynamicObject(PumpData[pumpid][pumpObject]);

		PumpData[pumpid][pumpText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 15.0);
        PumpData[pumpid][pumpObject] = CreateDynamicObject(1676, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 0.0, 0.0, PumpData[pumpid][pumpPos][3]);
	}
	return 1;
}

Pump_Save(pumpid)
{
	static
	    query[256];

	format(query, sizeof(query), "UPDATE `pumps` SET `pumpPosX` = '%.4f', `pumpPosY` = '%.4f', `pumpPosZ` = '%.4f', `pumpPosA` = '%.4f', `pumpFuel` = '%d' WHERE `ID` = '%d' AND `pumpID` = '%d'",
	    PumpData[pumpid][pumpPos][0],
	    PumpData[pumpid][pumpPos][1],
	    PumpData[pumpid][pumpPos][2],
		PumpData[pumpid][pumpPos][3],
	    PumpData[pumpid][pumpFuel],
	    BusinessData[PumpData[pumpid][pumpBusiness]][bizID],
	    PumpData[pumpid][pumpID]
	);
	return mysql_tquery(g_iHandle, query);
}

House_Create(playerid, address[], price)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_HOUSES; i ++)
		{
	    	if (!HouseData[i][houseExists])
		    {
    	        HouseData[i][houseExists] = true;
        	    HouseData[i][houseOwner] = 0;
            	HouseData[i][housePrice] = price;
            	HouseData[i][houseMoney] = 0;

				format(HouseData[i][houseAddress], 32, address);

    	        HouseData[i][housePos][0] = x;
    	        HouseData[i][housePos][1] = y;
    	        HouseData[i][housePos][2] = z;
    	        HouseData[i][housePos][3] = angle;

                HouseData[i][houseInt][0] = 2269.8772;
                HouseData[i][houseInt][1] = -1210.3240;
                HouseData[i][houseInt][2] = 1047.5625;
                HouseData[i][houseInt][3] = 90.0000;

				HouseData[i][houseInterior] = 10;
				HouseData[i][houseExterior] = GetPlayerInterior(playerid);
				HouseData[i][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

				HouseData[i][houseLights] = false;
				HouseData[i][houseLocked] = false;
				HouseData[i][houseSita] = false;

				House_Refresh(i);
				mysql_tquery(g_iHandle, "INSERT INTO `houses` (`houseOwner`) VALUES(0)", "OnHouseCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

House_RemoveFurniture(houseid)
{
	if (HouseData[houseid][houseExists])
	{
	    static
	        string[64];

	    for (new i = 0; i != MAX_FURNITURE; i ++) if (FurnitureData[i][furnitureExists] && FurnitureData[i][furnitureHouse] == houseid) {
	        FurnitureData[i][furnitureExists] = false;
	        FurnitureData[i][furnitureModel] = 0;
            FurnitureData[i][furnitureHouse] = -1;

	        DestroyDynamicObject(FurnitureData[i][furnitureObject]);
		}
		format(string, sizeof(string), "DELETE FROM `furniture` WHERE `ID` = '%d'", HouseData[houseid][houseID]);
		mysql_tquery(g_iHandle, string);
	}
	return 1;
}

House_Delete(houseid)
{
	if (houseid != -1 && HouseData[houseid][houseExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `houses` WHERE `houseID` = '%d'", HouseData[houseid][houseID]);
		mysql_tquery(g_iHandle, string);

        if (IsValidDynamic3DTextLabel(HouseData[houseid][houseText3D]))
		    DestroyDynamic3DTextLabel(HouseData[houseid][houseText3D]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickupExt]))
		    DestroyDynamicPickup(HouseData[houseid][housePickupExt]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickupInt]))
		    DestroyDynamicPickup(HouseData[houseid][housePickupInt]);

		if (IsValidDynamicMapIcon(HouseData[houseid][houseMapIcon]))
		    DestroyDynamicMapIcon(HouseData[houseid][houseMapIcon]);

        for (new i = 0; i < MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && BackpackData[i][backpackHouse] == HouseData[houseid][houseID]) {
		    Backpack_Delete(i);
		}
		House_RemoveFurniture(houseid);
		House_RemoveAllItems(houseid);

	    HouseData[houseid][houseExists] = false;
	    HouseData[houseid][houseOwner] = 0;
	    HouseData[houseid][houseID] = 0;
	}
	return 1;
}

House_IsOwner(playerid, houseid)
{
	if (!PlayerData[playerid][pLogged] || PlayerData[playerid][pID] == -1)
	    return 0;

    if ((HouseData[houseid][houseExists] && HouseData[houseid][houseOwner] != 0) && HouseData[houseid][houseOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

Business_ProductMenu(playerid, bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	static
	    string[512];

	switch (BusinessData[bizid][bizType])
	{
	    case 1, 6:
	    {
			format(string, sizeof(string), "Frozen Pizza - %s\nBaseball - %s\nFrozen Burger - %s\nBackpack - %s\nWater Bottle - %s\nSoda Bottle - %s\nLottery Ticket - %s\nLighter - %s\nFuel Can - %s\nCrowbar - %s\nRepairkit - %s\nMask - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6]),
				FormatNumber(BusinessData[bizid][bizPrices][7]),
				FormatNumber(BusinessData[bizid][bizPrices][8]),
				FormatNumber(BusinessData[bizid][bizPrices][9]),
				FormatNumber(BusinessData[bizid][bizPrices][10]),
				FormatNumber(BusinessData[bizid][bizPrices][11])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 2:
	    {
			format(string, sizeof(string), "Cellphone - %s\nGPS System - %s\nPortable Radio - %s\nBoombox - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 3:
	    {
			format(string, sizeof(string), "Clothes - %s\nGlasses - %s\nHats - %s\nBandana - %s\nHelmet - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 4:
	    {
			format(string, sizeof(string), "Water - %s\nSoda - %s\nFrench Fries - %s\nCheeseburger - %s\nChicken Burger - %s\nChicken Nuggets - %s\nSalad - %s",
    			FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 7:
	    {
	        string[0] = 0;

	        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
	            format(string, sizeof(string), "%s%s - %s\n", string, g_aFurnitureTypes[i], FormatNumber(BusinessData[bizid][bizPrices][i]));
			}
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
	}
	return 1;
}

Business_PurchaseMenu(playerid, bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	static
	    string[512];

 	switch (BusinessData[bizid][bizType])
	{
	    case 1, 6:
	    {
			format(string, sizeof(string), "Frozen Pizza - %s\nBaseball - %s\nFrozen Burger - %s\nBackpack - %s\nWater Bottle - %s\nSoda Bottle - %s\nLottery Ticket - %s\nLighter - %s\nFuel Can - %s\nCrowbar - %s\nRepairkit - %s\nMask - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6]),
				FormatNumber(BusinessData[bizid][bizPrices][7]),
				FormatNumber(BusinessData[bizid][bizPrices][8]),
				FormatNumber(BusinessData[bizid][bizPrices][9]),
				FormatNumber(BusinessData[bizid][bizPrices][10]),
				FormatNumber(BusinessData[bizid][bizPrices][11])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 2:
	    {
			format(string, sizeof(string), "Cellphone - %s\nGPS System - %s\nPortable Radio - %s\nBoombox - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 3:
	    {
			format(string, sizeof(string), "Clothes - %s\nGlasses - %s\nHats - %s\nBandana - %s\nHelmet - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 4:
		{
            format(string, sizeof(string), "Water - %s\nSoda - %s\nFrench Fries - %s\nCheeseburger - %s\nChicken Burger - %s\nChicken Nuggets - %s\nSalad - %s",
    			FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 7:
	    {
	        string[0] = 0;

	        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
	            format(string, sizeof(string), "%s%s - %s\n", string, g_aFurnitureTypes[i], FormatNumber(BusinessData[bizid][bizPrices][i]));
			}
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
	}
	return 1;
}

Business_Type(bizid)
{
	if (BusinessData[bizid][bizType] == 1 || BusinessData[bizid][bizType] == 6) {
		BusinessData[bizid][bizInt][0] = -27.3074;
		BusinessData[bizid][bizInt][1] = -30.8741;
		BusinessData[bizid][bizInt][2] = 1003.5573;
		BusinessData[bizid][bizInt][3] = 0.0000;
		BusinessData[bizid][bizInterior] = 4;

		BusinessData[bizid][bizCaunter][0] = -30.8771;
		BusinessData[bizid][bizCaunter][1] = -28.8908;
		BusinessData[bizid][bizCaunter][2] = 1003.5573;

		BusinessData[bizid][bizActor][0] = -31.0110;
		BusinessData[bizid][bizActor][1] = -30.7177;
		BusinessData[bizid][bizActor][2] = 1003.5573;
		BusinessData[bizid][bizActor][3] = 0.6267;

		BusinessData[bizid][bizPrices][0] = 5;
		BusinessData[bizid][bizPrices][1] = 10;
		BusinessData[bizid][bizPrices][2] = 15;
		BusinessData[bizid][bizPrices][3] = 5;
		BusinessData[bizid][bizPrices][4] = 3;
		BusinessData[bizid][bizPrices][5] = 2;
		BusinessData[bizid][bizPrices][6] = 10;
		BusinessData[bizid][bizPrices][7] = 7;
		BusinessData[bizid][bizPrices][8] = 20;
		BusinessData[bizid][bizPrices][9] = 10;
		BusinessData[bizid][bizPrices][10] = 13;
		BusinessData[bizid][bizPrices][11] = 200;
	}
	else if(BusinessData[bizid][bizType] ==  2) {
		BusinessData[bizid][bizInt][0] = -2029.6053;
		BusinessData[bizid][bizInt][1] = -119.1310;
		BusinessData[bizid][bizInt][2] = 1035.1719;
		BusinessData[bizid][bizInt][3] = 358.3131;
		BusinessData[bizid][bizInterior] = 3;

		BusinessData[bizid][bizCaunter][0] = -2033.4347;
		BusinessData[bizid][bizCaunter][1] = -117.4959;
		BusinessData[bizid][bizCaunter][2] = 1035.1719;

		BusinessData[bizid][bizActor][0] = -2035.0952;
		BusinessData[bizid][bizActor][1] = -117.5147;
		BusinessData[bizid][bizActor][2] = 1035.1719;
		BusinessData[bizid][bizActor][3] = 268.3936;

		BusinessData[bizid][bizPrices][0] = 75;
		BusinessData[bizid][bizPrices][1] = 125;
		BusinessData[bizid][bizPrices][2] = 100;
		BusinessData[bizid][bizPrices][3] = 150;
	}
	else if(BusinessData[bizid][bizType] ==  3) {
		BusinessData[bizid][bizInt][0] = 206.8692;
		BusinessData[bizid][bizInt][1] = -139.7568;
		BusinessData[bizid][bizInt][2] = 1003.5078;
		BusinessData[bizid][bizInt][3] = 355.9322;
		BusinessData[bizid][bizInterior] = 3;

		BusinessData[bizid][bizCaunter][0] = 207.0856;
		BusinessData[bizid][bizCaunter][1] = -129.1786;
		BusinessData[bizid][bizCaunter][2] = 1003.5078;

		BusinessData[bizid][bizActor][0] = 206.9810;	
		BusinessData[bizid][bizActor][1] = -127.8072;
		BusinessData[bizid][bizActor][2] = 1003.5078;
		BusinessData[bizid][bizActor][3] = 178.3131;

		BusinessData[bizid][bizPrices][0] = 25;
		BusinessData[bizid][bizPrices][1] = 15;
		BusinessData[bizid][bizPrices][2] = 10;
		BusinessData[bizid][bizPrices][3] = 10;
		BusinessData[bizid][bizPrices][4] = 100;
	}
	else if(BusinessData[bizid][bizType] ==  4) {
		BusinessData[bizid][bizInt][0] = 363.3402;
		BusinessData[bizid][bizInt][1] = -74.6679;
		BusinessData[bizid][bizInt][2] = 1001.5078;
		BusinessData[bizid][bizInt][3] = 315.0000;
		BusinessData[bizid][bizInterior] = 10;

		BusinessData[bizid][bizCaunter][0] = 376.3586;
		BusinessData[bizid][bizCaunter][1] = -67.4377;
		BusinessData[bizid][bizCaunter][2] = 1001.5078;

		BusinessData[bizid][bizActor][0] = 376.2107;
		BusinessData[bizid][bizActor][1] = -65.8410;
		BusinessData[bizid][bizActor][2] = 1001.5078;
		BusinessData[bizid][bizActor][3] = 176.2154;

		BusinessData[bizid][bizPrices][0] = 2;
		BusinessData[bizid][bizPrices][1] = 5;
		BusinessData[bizid][bizPrices][2] = 5;
		BusinessData[bizid][bizPrices][3] = 10;
		BusinessData[bizid][bizPrices][4] = 10;
		BusinessData[bizid][bizPrices][5] = 15;
		BusinessData[bizid][bizPrices][6] = 10;
	}
	else if(BusinessData[bizid][bizType] ==  5) {
		BusinessData[bizid][bizInt][0] = 1494.5612;
		BusinessData[bizid][bizInt][1] = 1304.2061;
		BusinessData[bizid][bizInt][2] = 1093.2891;
		BusinessData[bizid][bizInt][3] = 0.0000;
		BusinessData[bizid][bizInterior] = 3;

		BusinessData[bizid][bizCaunter][0] = 1490.3695;
		BusinessData[bizid][bizCaunter][1] = 1305.7124;
		BusinessData[bizid][bizCaunter][2] = 1093.2964;

		BusinessData[bizid][bizActor][0] = 1489.0360;
		BusinessData[bizid][bizActor][1] = 1305.7318;
		BusinessData[bizid][bizActor][2] = 1093.2964;
		BusinessData[bizid][bizActor][3] = 264.4324;
	}
	else if(BusinessData[bizid][bizType] ==  7) {
		BusinessData[bizid][bizInt][0] = -2240.4954;
		BusinessData[bizid][bizInt][1] = 128.3774;
		BusinessData[bizid][bizInt][2] = 1035.4210;
		BusinessData[bizid][bizInt][3] = 270.0000;
		BusinessData[bizid][bizInterior] = 6;

		BusinessData[bizid][bizCaunter][0] = -2237.2349;
		BusinessData[bizid][bizCaunter][1] = 130.1794;
		BusinessData[bizid][bizCaunter][2] = 1035.4141;

		BusinessData[bizid][bizActor][0] = -2237.1484;
		BusinessData[bizid][bizActor][1] = 128.5859;
		BusinessData[bizid][bizActor][2] = 1035.4141;
		BusinessData[bizid][bizActor][3] = 358.9641;

		BusinessData[bizid][bizPrices][0] = 75;
		BusinessData[bizid][bizPrices][1] = 115;
		BusinessData[bizid][bizPrices][2] = 15;
		BusinessData[bizid][bizPrices][3] = 95;
		BusinessData[bizid][bizPrices][4] = 3;
		BusinessData[bizid][bizPrices][5] = 2;
		BusinessData[bizid][bizPrices][6] = 10;
		BusinessData[bizid][bizPrices][7] = 100;
		BusinessData[bizid][bizPrices][8] = 20;
		BusinessData[bizid][bizPrices][9] = 10;
		BusinessData[bizid][bizPrices][10] = 140;
		BusinessData[bizid][bizPrices][11] = 190;
		BusinessData[bizid][bizPrices][12] = 150;
		BusinessData[bizid][bizPrices][13] = 60;
		BusinessData[bizid][bizPrices][14] = 50;
		BusinessData[bizid][bizPrices][15] = 5;
		BusinessData[bizid][bizPrices][16] = 10;
		BusinessData[bizid][bizPrices][17] = 5;
	}
	return 1;
}

Business_Save(bizid)
{
	static
	    query[2048];

	format(query, sizeof(query), "UPDATE `businesses` SET `bizName` = '%s', `bizMessage` = '%s', `bizOwner` = '%d', `bizType` = '%d', `bizPrice` = '%d', `bizPosX` = '%.4f', `bizPosY` = '%.4f', `bizPosZ` = '%.4f', `bizPosA` = '%.4f', `bizIntX` = '%.4f', `bizIntY` = '%.4f', `bizIntZ` = '%.4f', `bizIntA` = '%.4f', `bizInterior` = '%d', `bizExterior` = '%d', `bizExteriorVW` = '%d', `bizLocked` = '%d', `bizSita` = '%d', `bizVault` = '%d', `bizProducts` = '%d'",
		SQL_ReturnEscaped(BusinessData[bizid][bizName]),
		SQL_ReturnEscaped(BusinessData[bizid][bizMessage]),
		BusinessData[bizid][bizOwner],
		BusinessData[bizid][bizType],
		BusinessData[bizid][bizPrice],
		BusinessData[bizid][bizPos][0],
		BusinessData[bizid][bizPos][1],
		BusinessData[bizid][bizPos][2],
		BusinessData[bizid][bizPos][3],
		BusinessData[bizid][bizInt][0],
		BusinessData[bizid][bizInt][1],
		BusinessData[bizid][bizInt][2],
		BusinessData[bizid][bizInt][3],
		BusinessData[bizid][bizInterior],
		BusinessData[bizid][bizExterior],
		BusinessData[bizid][bizExteriorVW],
		BusinessData[bizid][bizLocked],
		BusinessData[bizid][bizSita],
		BusinessData[bizid][bizVault],
		BusinessData[bizid][bizProducts]
	);
	for (new i = 0; i < 20; i ++) {
		format(query, sizeof(query), "%s, `bizPrice%d` = '%d'", query, i + 1, BusinessData[bizid][bizPrices][i]);
	}
	format(query, sizeof(query), "%s, `bizSpawnX` = '%.4f', `bizSpawnY` = '%.4f', `bizSpawnZ` = '%.4f', `bizSpawnA` = '%.4f', `bizDeliverX` = '%.4f', `bizDeliverY` = '%.4f', `bizDeliverZ` = '%.4f', `bizCaunterX` = '%.4f', `bizCaunterY` = '%.4f', `bizCaunterZ` = '%.4f', `bizActorX` = '%.4f', `bizActorY` = '%.4f', `bizActorZ` = '%.4f', `bizActorA` = '%.4f', `bizShipment` = '%d' WHERE `bizID` = '%d'",
		query,
		BusinessData[bizid][bizSpawn][0],
		BusinessData[bizid][bizSpawn][1],
		BusinessData[bizid][bizSpawn][2],
		BusinessData[bizid][bizSpawn][3],
		BusinessData[bizid][bizDeliver][0],
		BusinessData[bizid][bizDeliver][1],
		BusinessData[bizid][bizDeliver][2],
		BusinessData[bizid][bizCaunter][0],
		BusinessData[bizid][bizCaunter][1],
		BusinessData[bizid][bizCaunter][2],
		BusinessData[bizid][bizActor][0],
		BusinessData[bizid][bizActor][1],
		BusinessData[bizid][bizActor][2],
		BusinessData[bizid][bizActor][3],
		BusinessData[bizid][bizShipment],
		BusinessData[bizid][bizID]
	);
	return mysql_tquery(g_iHandle, query);
}

Business_Inside(playerid)
{
	if (PlayerData[playerid][pBusiness] != -1)
	{
	    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizID] == PlayerData[playerid][pBusiness] && GetPlayerInterior(playerid) == BusinessData[i][bizInterior] && GetPlayerVirtualWorld(playerid) > 0) {
	        return i;
		}
	}
	return -1;
}

Car_Inside(playerid)
{
	new carid;

	if (IsPlayerInAnyVehicle(playerid) && (carid = Car_GetID(GetPlayerVehicleID(playerid))) != -1)
	    return carid;

	return -1;
}

Car_Nearest(playerid)
{
	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for (new i = 0; i != MAX_DYNAMIC_CARS; i ++) if (CarData[i][carExists]) {
		GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);

		if (IsPlayerInRangeOfPoint(playerid, 3.0, fX, fY, fZ)) {
		    return i;
		}
	}
	return -1;
}

Car_NearestEx(playerid)
{
	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for (new i = 0; i != MAX_DYNAMIC_CARS; i ++) if (CarData[i][carExists]) {
		GetVehiclePos(CarData[i][carVehicle], fX, fY, fZ);

		if (IsPlayerInRangeOfPoint(playerid, 5.0, fX, fY, fZ)) {
		    return i;
		}
	}
	return -1;
}

Business_NearestDeliver(playerid)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][bizDeliver][0], BusinessData[i][bizDeliver][1], BusinessData[i][bizDeliver][2])) {
        return i;
	}
	return -1;
}

Business_NearestCaunter(playerid)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, 2.0, BusinessData[i][bizCaunter][0], BusinessData[i][bizCaunter][1], BusinessData[i][bizCaunter][2]) && BusinessData[i][bizID] == PlayerData[playerid][pBusiness] && GetPlayerInterior(playerid) == BusinessData[i][bizInterior] && GetPlayerVirtualWorld(playerid) > 0) {
        return i;
	}
	return -1;
}

Business_Nearest(playerid, Float:radius = 2.5)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, radius, BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]))
	{
		if (GetPlayerInterior(playerid) == BusinessData[i][bizExterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][bizExteriorVW])
			return i;
	}
	return -1;
}

Business_Refresh(bizid)
{
	if (bizid != -1 && BusinessData[bizid][bizExists])
	{
		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizText3D]);

		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]);

		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizCaunterText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizCaunterText3D]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizPickupExt]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickupExt]);
		
		if (IsValidDynamicPickup(BusinessData[bizid][bizPickupInt]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickupInt]);

        if (IsValidDynamicPickup(BusinessData[bizid][bizDeliverPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizDeliverPickup]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizCaunterPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizCaunterPickup]);

		if (IsValidActor(BusinessData[bizid][bizActorr]))
		    DestroyActor(BusinessData[bizid][bizActorr]);

		static
		    string[128];

		if (!BusinessData[bizid][bizOwner]) {
			BusinessData[bizid][bizPickupExt] = CreateDynamicPickup(1318, 23, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
			format(string, sizeof(string), ""BLUE_E"Kedai ini untuk dijual! "GREEN_E"(%s)\n"WHITE_E"Taip "GREEN_E"/buy "WHITE_E"untuk beli", FormatNumber(BusinessData[bizid][bizPrice]));
            BusinessData[bizid][bizText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		else
		{
			format(string, sizeof(string), ""BLUE_E"%s\n"WHITE_E"Tekan "GREEN_E"F "WHITE_E"untuk masuk", BusinessData[bizid][bizName]);
			BusinessData[bizid][bizPickupExt] = CreateDynamicPickup(19133, 23, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
			BusinessData[bizid][bizText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		if (BusinessData[bizid][bizDeliver][0] != 0.0 && BusinessData[bizid][bizDeliver][0] != 0.0 && BusinessData[bizid][bizDeliver][0] != 0.0)
		{
		    format(string, sizeof(string), ""BLUE_E"%s\n"WHITE_E"Delivery point", BusinessData[bizid][bizName]);

		    BusinessData[bizid][bizDeliverPickup] = CreateDynamicPickup(1239, 23, BusinessData[bizid][bizDeliver][0], BusinessData[bizid][bizDeliver][1], BusinessData[bizid][bizDeliver][2]);
		    BusinessData[bizid][bizDeliverText3D] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, BusinessData[bizid][bizDeliver][0], BusinessData[bizid][bizDeliver][1], BusinessData[bizid][bizDeliver][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
		}
		if (BusinessData[bizid][bizCaunter][0] != 0.0 && BusinessData[bizid][bizCaunter][0] != 0.0 && BusinessData[bizid][bizCaunter][0] != 0.0)
		{
		    format(string, sizeof(string), "KAUNTER KEDAI\n"WHITE_E"Tekan "GREEN_E"Y "WHITE_E"untuk membeli", BusinessData[bizid][bizName]);

		    BusinessData[bizid][bizCaunterPickup] = CreateDynamicPickup(1239, 23, BusinessData[bizid][bizCaunter][0], BusinessData[bizid][bizCaunter][1], BusinessData[bizid][bizCaunter][2], BusinessData[bizid][bizID] + 6000, BusinessData[bizid][bizInterior]);
		    BusinessData[bizid][bizCaunterText3D] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, BusinessData[bizid][bizCaunter][0], BusinessData[bizid][bizCaunter][1], BusinessData[bizid][bizCaunter][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, BusinessData[bizid][bizID] + 6000, BusinessData[bizid][bizInterior]);
		}
		BusinessData[bizid][bizPickupInt] = CreateDynamicPickup(19130, 23, BusinessData[bizid][bizInt][0], BusinessData[bizid][bizInt][1], BusinessData[bizid][bizInt][2], BusinessData[bizid][bizID] + 6000, BusinessData[bizid][bizInterior]);
		BusinessData[bizid][bizActorr] = CreateActor(17, BusinessData[bizid][bizActor][0], BusinessData[bizid][bizActor][1], BusinessData[bizid][bizActor][2], 0.0); SetActorVirtualWorld(BusinessData[bizid][bizActorr], BusinessData[bizid][bizID] + 6000);
	}
	return 1;
}

Business_Create(playerid, type, price)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_HOUSES; i ++)
		{
	    	if (!BusinessData[i][bizExists])
		    {
    	        BusinessData[i][bizExists] = true;
        	    BusinessData[i][bizOwner] = 0;
            	BusinessData[i][bizPrice] = price;
            	BusinessData[i][bizType] = type;

				format(BusinessData[i][bizName], 32, "Unnamed Business");

    	        BusinessData[i][bizPos][0] = x;
    	        BusinessData[i][bizPos][1] = y;
    	        BusinessData[i][bizPos][2] = z;
    	        BusinessData[i][bizPos][3] = angle;

    	        BusinessData[i][bizSpawn][0] = x;
    	        BusinessData[i][bizSpawn][1] = y;
    	        BusinessData[i][bizSpawn][2] = z;
    	        BusinessData[i][bizSpawn][3] = angle;

    	        BusinessData[i][bizDeliver][0] = 0.0;
    	        BusinessData[i][bizDeliver][1] = 0.0;
    	        BusinessData[i][bizDeliver][2] = 0.0;

				Business_Type(i);

				BusinessData[i][bizExterior] = GetPlayerInterior(playerid);
				BusinessData[i][bizExteriorVW] = GetPlayerVirtualWorld(playerid);

				BusinessData[i][bizLocked] = true;
				BusinessData[i][bizSita] = false;
				BusinessData[i][bizVault] = 0;
				BusinessData[i][bizProducts] = 100;
				BusinessData[i][bizShipment] = 0;

				Business_Refresh(i);
				mysql_tquery(g_iHandle, "INSERT INTO `businesses` (`bizOwner`) VALUES(0)", "OnBusinessCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

Business_Delete(bizid)
{
	if (bizid != -1 && BusinessData[bizid][bizExists])
	{
	    new
	        string[82];

		format(string, sizeof(string), "DELETE FROM `businesses` WHERE `bizID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(g_iHandle, string);

		foreach (new i : Player) if (PlayerData[i][pShipment] == bizid) {
			PlayerData[i][pShipment] = -1;
			PlayerData[i][pDeliverShipment] = 0;

			DisablePlayerCheckpoint(i);
		}
        if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizText3D]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizPickupExt]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickupExt]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizPickupInt]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickupInt]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizDeliverPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizDeliverPickup]);
		
		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizCaunterPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizCaunterPickup]);
		
		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizCaunterText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizCaunterText3D]);

		if (IsValidActor(BusinessData[bizid][bizActorr]))
		    DestroyActor(BusinessData[bizid][bizActorr]);

		Business_RemovePumps(bizid);
		Business_RemoveCars(bizid);

	    BusinessData[bizid][bizExists] = false;
	    BusinessData[bizid][bizOwner] = 0;
	    BusinessData[bizid][bizID] = 0;
	}
	return 1;
}

Business_IsOwner(playerid, bizid)
{
	if (!PlayerData[playerid][pLogged] || PlayerData[playerid][pID] == -1)
	    return 0;

	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizOwner] == 99999999 && PlayerData[playerid][pAdmin] > 0)
		return 1;

    if ((BusinessData[bizid][bizExists] && BusinessData[bizid][bizOwner] != 0) && BusinessData[bizid][bizOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

ReturnDate()
{
	static
	    date[36];

	getdate(date[2], date[1], date[0]);
	gettime(date[3], date[4], date[5]);

	format(date, sizeof(date), "%02d/%02d/%d, %02d:%02d", date[0], date[1], date[2], date[3], date[4]);
	return date;
}

ReturnVehicleHealth(vehicleid)
{
	if (!IsValidVehicle(vehicleid))
	    return 0;

	static
	    Float:amount;

	GetVehicleHealth(vehicleid, amount);
	return floatround(amount, floatround_round);
}

ReturnArmour(playerid)
{
	static
	    Float:amount;

	GetPlayerArmour(playerid, amount);
	return floatround(amount, floatround_round);
}

ReturnHealth(playerid)
{
	static
	    Float:amount;

	GetPlayerHealth(playerid, amount);
	return floatround(amount, floatround_round);
}

ReturnName(playerid, underscore=1)
{
	static
	    name[MAX_PLAYER_NAME + 1];

	GetPlayerName(playerid, name, sizeof(name));

	if (!underscore) {
	    for (new i = 0, len = strlen(name); i < len; i ++) {
	        if (name[i] == '_') name[i] = ' ';
		}
	}
	if (PlayerData[playerid][pMaskOn])
	    format(name, sizeof(name), "Mask_#%d", PlayerData[playerid][pMaskID]);

	return name;
}

Blacklist_Add(ip[], username[], banner[], reason[])
{
	static
	    string[256];

	format(string, sizeof(string), "INSERT INTO `blacklist` (`IP`, `Username`, `BannedBy`, `Reason`, `Date`) VALUES('%s', '%s', '%s', '%s', '%s')",
		SQL_ReturnEscaped(ip),
		SQL_ReturnEscaped(username),
		SQL_ReturnEscaped(banner),
		SQL_ReturnEscaped(reason),
		ReturnDate()
	);
	mysql_tquery(g_iHandle, string);
}

Blacklist_Remove(username[])
{
	static
	    string[128];

	format(string, sizeof(string), "DELETE FROM `blacklist` WHERE `Username` = '%s'", SQL_ReturnEscaped(username));
    mysql_tquery(g_iHandle, string);
}

Blacklist_RemoveIP(ip[])
{
	static
	    string[128];

    format(string, sizeof(string), "DELETE FROM `blacklist` WHERE `IP` = '%s'", SQL_ReturnEscaped(ip));
    mysql_tquery(g_iHandle, string);
}

House_RemoveAllItems(houseid)
{
	static
	    query[64];

	for (new i = 0; i != MAX_HOUSE_STORAGE; i ++) {
        HouseStorage[houseid][i][hItemExists] = false;
        HouseStorage[houseid][i][hItemModel] = 0;
        HouseStorage[houseid][i][hItemQuantity] = 0;
	}
	format(query, 64, "DELETE FROM `housestorage` WHERE `ID` = '%d'", HouseData[houseid][houseID]);
	mysql_tquery(g_iHandle, query);

	for (new i = 0; i < 10; i ++) {
	    HouseData[houseid][houseWeapons][i] = 0;
	    HouseData[houseid][houseAmmo][i] = 0;
	}
	return 1;
}

Car_RemoveAllItems(carid)
{
	static
	    query[64];

	for (new i = 0; i != MAX_CAR_STORAGE; i ++) {
        CarStorage[carid][i][cItemExists] = false;
        CarStorage[carid][i][cItemModel] = 0;
        CarStorage[carid][i][cItemQuantity] = 0;
	}
	format(query, 64, "DELETE FROM `carstorage` WHERE `ID` = '%d'", CarData[carid][carID]);
	mysql_tquery(g_iHandle, query);

	for (new i = 0; i < 5; i ++) {
	    CarData[carid][carWeapons][i] = 0;
	    CarData[carid][carAmmo][i] = 0;
	}
	return 1;
}

FormatNumber(number, prefix[] = "RM")
{
	static
		value[32],
		length;

	format(value, sizeof(value), "%d", (number < 0) ? (-number) : (number));

	if ((length = strlen(value)) > 3)
	{
		for (new i = length, l = 0; --i >= 0; l ++) {
		    if ((l > 0) && (l % 3 == 0)) strins(value, ",", i + 1);
		}
	}
	if (prefix[0] != 0)
	    strins(value, prefix, 0);

	if (number < 0)
		strins(value, "-", 0);

	return value;
}

ResetFaction(playerid)
{
    PlayerData[playerid][pFaction] = -1;
    PlayerData[playerid][pFactionID] = -1;
    PlayerData[playerid][pFactionRank] = 0;
}

StopDragging(playerid)
{
	if (PlayerData[playerid][pDragged])
	{
	    PlayerData[playerid][pDragged] = 0;
		PlayerData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
		KillTimer(PlayerData[playerid][pDragTimer]);
	}
	return 1;
}

ResetEditing(playerid)
{
    if (PlayerData[playerid][pEditFurniture] != -1)
		Furniture_Refresh(PlayerData[playerid][pEditFurniture]);

	if (PlayerData[playerid][pEditPump] != -1)
	{
		Pump_Refresh(PlayerData[playerid][pEditPump]);
		PlayerData[playerid][pGasStation] = -1;
	}
	PlayerData[playerid][pEditType] = 0;
 	PlayerData[playerid][pEditGate] = -1;
 	PlayerData[playerid][pEditRack] = -1;
	PlayerData[playerid][pEditPump] = -1;
	PlayerData[playerid][pEditFurniture] = -1;
	return 1;
}

ResetPlayer(playerid)
{
    if (PlayerData[playerid][pFirstAid])
	    KillTimer(PlayerData[playerid][pAidTimer]);

	if (PlayerData[playerid][pDrivingTest])
	    DestroyVehicle(PlayerData[playerid][pTestCar]);

	if (PlayerData[playerid][pSweeper])
	    DestroyVehicle(PlayerData[playerid][pSweeperCar]);

	if (PlayerData[playerid][pWaypoint])
	{
        PlayerData[playerid][pWaypoint] = 0;
        PlayerTextDrawHide(playerid, WaypointTD[playerid]);
	}
	foreach (new i : Player) if (PlayerData[i][pDraggedBy] == playerid) {
	    StopDragging(i);
	}
	if (PlayerData[playerid][pDragged]) {
	    StopDragging(playerid);
	}
	PlayerData[playerid][pCooking] = 0;
	PlayerData[playerid][pCookingTime] = 0;
	PlayerData[playerid][pCookingHouse] = -1;
	PlayerData[playerid][pGasPump] = -1;
	PlayerData[playerid][pCarryTrash] = 0;
	PlayerData[playerid][pGasStation] = -1;
	PlayerData[playerid][pCrafting] = 0;
	PlayerData[playerid][pOpeningCrate] = 0;
	PlayerData[playerid][pHarvesting] = 0;
	PlayerData[playerid][pDrivingTest] = 0;
	PlayerData[playerid][pFuelCan] = 0;
	PlayerData[playerid][pFingerTime] = 0;
	PlayerData[playerid][pFingerItem] = -1;
	PlayerData[playerid][pFirstAid] = 0;
	PlayerData[playerid][pDrinkTime] = 0;
	PlayerData[playerid][pEmergency] = 0;
	PlayerData[playerid][pPlaceAd] = 0;
	PlayerData[playerid][pAdTime] = 0;
	PlayerData[playerid][pTaxiCalled] = 0;
	PlayerData[playerid][pMining] = 0;
	PlayerData[playerid][pMinedRock] = 0;
	PlayerData[playerid][pMineTime] = 0;
	PlayerData[playerid][pLoadType] = 0;
	PlayerData[playerid][pLoadCrate] = 0;
	PlayerData[playerid][pLoading] = 0;
	PlayerData[playerid][pUnloading] = -1;
	PlayerData[playerid][pUnloadVehicle] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pSorting] = -1;
	PlayerData[playerid][pSortCrate] = 0;
	PlayerData[playerid][pCP] = 0;
	PlayerData[playerid][pMaskOn] = 0;
	PlayerData[playerid][pHideTags] = 0;
	PlayerData[playerid][pCuffed] = 0;
	PlayerData[playerid][pGraffiti] = -1;
	PlayerData[playerid][pGraffitiTime] = 0;
	PlayerData[playerid][pPicking] = 0;
	PlayerData[playerid][pPickCar] = -1;
	PlayerData[playerid][pPickTime] = 0;
	PlayerData[playerid][pSweeper] = 0;

	RemovePlayerAttachedObject(playerid, 4);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	DisablePlayerCheckpoint(playerid);
	GameTextForPlayer(playerid, " ", 1, 3);
}

ResetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	for (new i = 0; i < 13; i ++) {
		PlayerData[playerid][pGuns][i] = 0;
		PlayerData[playerid][pAmmo][i] = 0;
	}
	return 1;
}

ResetWeapon(playerid, weaponid)
{
	ResetPlayerWeapons(playerid);

	for (new i = 0; i < 13; i ++) {
	    if (PlayerData[playerid][pGuns][i] != weaponid) {
	        GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);
		}
		else {
            PlayerData[playerid][pGuns][i] = 0;
            PlayerData[playerid][pAmmo][i] = 0;
	    }
	}
	return 1;
}

GiveWeaponToPlayer(playerid, weaponid, ammo)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;

	PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
	PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] += ammo;

	return GivePlayerWeapon(playerid, weaponid, ammo);
}

GiveMoney(playerid, amount)
{
	PlayerData[playerid][pMoney] += amount;
	return 1;
}

GetPlayerSQLID(playerid)
{
	return (PlayerData[playerid][pID]);
}

GetMoney(playerid)
{
	return (PlayerData[playerid][pMoney]);
}

IsValidPlayerName(const str[])
{
	if (!str[0] || str[0] == '\1')
		return 0;

	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
	        continue;

		if (str[i] == '_' || str[i] == '$' || str[i] == '@' || str[i] == '[' || str[i] == ']')
		    continue;

		else
		    return 0;
	}
	return 1;
}

IsAnIP(str[])
{
	if (!str[0] || str[0] == '\1')
		return 0;

	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
	        return 0;

	    if (0 < ((i == 0) ? (strval(str)) : (strval(str[i + 1]))) > 255)
	        return 0;
	}
	return 1;
}

Report_GetCount(playerid)
{
	new count;

    for (new i = 0; i != MAX_REPORTS; i ++)
	{
	    if (ReportData[i][rExists] && ReportData[i][rPlayer] == playerid)
	    {
	        count++;
		}
	}
	return count;
}


Report_Clear(playerid)
{
    for (new i = 0; i != MAX_REPORTS; i ++)
	{
	    if (ReportData[i][rExists] && ReportData[i][rPlayer] == playerid)
	    {
	        Report_Remove(i);
		}
	}
	return 1;
}

Report_Add(playerid, const text[], type = 1)
{
	for (new i = 0; i != MAX_REPORTS; i ++)
	{
	    if (!ReportData[i][rExists])
	    {
	        ReportData[i][rExists] = true;
	        ReportData[i][rType] = type;
	        ReportData[i][rPlayer] = playerid;

	        strpack(ReportData[i][rText], text, 128 char);
			return i;
		}
	}
	return -1;
}

Report_Remove(reportid)
{
	if (reportid != -1 && ReportData[reportid][rExists])
	{
	    ReportData[reportid][rExists] = false;
	    ReportData[reportid][rPlayer] = INVALID_PLAYER_ID;
	}
	return 1;
}

KickEx(playerid)
{
	if (PlayerData[playerid][pKicked])
	    return 0;

	PlayerData[playerid][pKicked] = 1;
	SetTimerEx("KickTimer", 200, false, "d", playerid);

	return 1;
}

IsValidRoleplayName(const name[]) {
	if (!name[0] || strfind(name, "_") == -1)
	    return 0;

	else for (new i = 0, len = strlen(name); i != len; i ++) {
	    if ((i == 0) && (name[i] < 'A' || name[i] > 'Z'))
	        return 0;

		else if ((i != 0 && i < len  && name[i] == '_') && (name[i + 1] < 'A' || name[i + 1] > 'Z'))
		    return 0;

		else if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != '.')
		    return 0;
	}
	return 1;
}

ResetStatistics(playerid)
{
	for (new i = 0; i < 3; i ++) {
	    PlayerCharacters[playerid][i][0] = 0;

	    for (new j = 0; j < 9; j ++) {
	    	AccessoryData[playerid][i][j] = 0.0;
	    }
	}
	for (new i = 0; i != MAX_INVENTORY; i ++) {
	    InventoryData[playerid][i][invExists] = false;
	    InventoryData[playerid][i][invModel] = 0;
	    InventoryData[playerid][i][invQuantity] = 0;
	}
	for (new i = 0; i < 12; i ++) {
	    PlayerData[playerid][pGuns][i] = 0;
	    PlayerData[playerid][pAmmo][i] = 0;
	}
	for (new i = 0; i != MAX_HOUSE_FURNITURE; i ++) {
	    ListedFurniture[playerid][i] = -1;
	}
	for (new i = 0; i < MAX_LISTED_ITEMS; i ++) {
	    NearestItems[playerid][i] = -1;
	}
	for (new i = 0; i != MAX_CONTACTS; i ++) {
	    ContactData[playerid][i][contactExists] = false;
	    ContactData[playerid][i][contactID] = 0;
	    ContactData[playerid][i][contactNumber] = 0;
	    ListedContacts[playerid][i] = -1;
	}
	for (new i = 0; i != MAX_GPS_LOCATIONS; i ++) {
	    LocationData[playerid][i][locationExists] = false;
	    LocationData[playerid][i][locationID] = 0;
	}
	for (new i = 0; i != MAX_PLAYER_TICKETS; i ++) {
	    TicketData[playerid][i][ticketID] = 0;
		TicketData[playerid][i][ticketExists] = false;
		TicketData[playerid][i][ticketFee] = 0; 
		TicketData[playerid][i][ticketFaction] = -1;
	}
	BoomboxData[playerid][boomboxPlaced] = 0;
	BoomboxData[playerid][boomboxPos][0] = 0.0;
	BoomboxData[playerid][boomboxPos][1] = 0.0;
	BoomboxData[playerid][boomboxPos][2] = 0.0;

	PlayerData[playerid][pID] = -1;
	PlayerData[playerid][pLogged] = 0;
	PlayerData[playerid][pCreated] = 0;
	PlayerData[playerid][pGender] = 1;
	PlayerData[playerid][pBirthdate][0] = 0;
	PlayerData[playerid][pOrigin][0] = 0;
	PlayerData[playerid][pSkin] = 98;
    PlayerData[playerid][pEditType] = 0;
    PlayerData[playerid][pGlasses] = 0;
    PlayerData[playerid][pHat] = 0; 
    PlayerData[playerid][pBandana] = 0;
    PlayerData[playerid][pPos] = 0.0;
	PlayerData[playerid][pSeatBelt] = 0;
    PlayerData[playerid][pInterior] = 0;
    PlayerData[playerid][pWorld] = 0;
    PlayerData[playerid][pCharacter] = 0;
    PlayerData[playerid][pKilled] = 0;
    PlayerData[playerid][pRepairTime] = 0;
    PlayerData[playerid][pMoney] = 250;
    PlayerData[playerid][pBankMoney] = 250;
    PlayerData[playerid][pSpawnPoint] = 0;
    PlayerData[playerid][pSavings] = 0;
    PlayerData[playerid][pAdmin] = 0;
	PlayerData[playerid][pStaterpack] = 0;
	PlayerData[playerid][pReportTime] = 0;
	PlayerData[playerid][pHelpTime] = 0;
	PlayerData[playerid][pSpectator] = INVALID_PLAYER_ID;
	PlayerData[playerid][pJailTime] = 0;
	PlayerData[playerid][pKicked] = 0;
	PlayerData[playerid][pMuted] = 0;
	PlayerData[playerid][pSpamCount] = 0;
	PlayerData[playerid][pCommandCount] = 0;
	PlayerData[playerid][pToggleGlasses] = 0;
	PlayerData[playerid][pToggleHat] = 0;
	PlayerData[playerid][pToggleBandana] = 0;
	PlayerData[playerid][pToggleArmor] = 0;
    PlayerData[playerid][pLastShot] = INVALID_PLAYER_ID;
    PlayerData[playerid][pShotTime] = 0;
	PlayerData[playerid][pInventoryItem] = 0;
	PlayerData[playerid][pStorageItem] = 0;
	PlayerData[playerid][pStorageSelect] = 0;
	PlayerData[playerid][pProductModify] = 0;
	PlayerData[playerid][pHouse] = -1;
	PlayerData[playerid][pBusiness] = -1;
	PlayerData[playerid][pEntrance] = -1;
	PlayerData[playerid][pGasPump] = -1;
	PlayerData[playerid][pGasStation] = -1;
    PlayerData[playerid][pLoading] = 0;
	PlayerData[playerid][pEditPump] = -1;
	PlayerData[playerid][pEditFurniture] = -1;
	PlayerData[playerid][pSpeedTime] = 0;
	PlayerData[playerid][pEditGate] = -1;
	PlayerData[playerid][pEditRack] = -1;
	PlayerData[playerid][pSelectFurniture] = 0;
	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
	PlayerData[playerid][pHouseSeller] = INVALID_PLAYER_ID;
	PlayerData[playerid][pHouseOffered] = -1;
	PlayerData[playerid][pHouseValue] = 0;
	PlayerData[playerid][pBusinessSeller] = INVALID_PLAYER_ID;
	PlayerData[playerid][pBusinessOffered] = -1;
	PlayerData[playerid][pBusinessValue] = 0;
	PlayerData[playerid][pCarSeller] = INVALID_PLAYER_ID;
	PlayerData[playerid][pCarOffered] = -1;
	PlayerData[playerid][pCarValue] = 0;
	PlayerData[playerid][pShakeOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pShakeType] = 0;
	PlayerData[playerid][pFriskOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pFoodSeller] = INVALID_PLAYER_ID;
	PlayerData[playerid][pFoodType] = 0;
	PlayerData[playerid][pFoodPrice] = 0;
	PlayerData[playerid][pFactionOffer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pFactionOffered] = -1;
	PlayerData[playerid][pPhone] = 0;
	PlayerData[playerid][pLottery] = 0;
	PlayerData[playerid][pLotteryB] = 0;
	PlayerData[playerid][pClubTime] = 0; 
	PlayerData[playerid][pBodyInsurance] = 0; 
	PlayerData[playerid][pUraine] = 0;
	PlayerData[playerid][pHunger] = 100; 
	PlayerData[playerid][pThirst] = 100;
	PlayerData[playerid][pStress] = 0;
	PlayerData[playerid][pHungerTime] = 0;
	PlayerData[playerid][pThirstTime] = 0;
	PlayerData[playerid][pStressTime] = 0;
	PlayerData[playerid][pCooking] = 0;
	PlayerData[playerid][pCookingTime] = 0;
	PlayerData[playerid][pScore] = 0;
	PlayerData[playerid][pMinutes] = 0;
	PlayerData[playerid][pArmorStatus] = 0;
	PlayerData[playerid][pArmorShown] = 0;
	PlayerData[playerid][pClothesType] = 0;
	PlayerData[playerid][pDrivingTest] = 0;
	PlayerData[playerid][pTestStage] = 0;
	PlayerData[playerid][pTestWarns] = 0;
	PlayerData[playerid][pFurnitureType] = 0;
	PlayerData[playerid][pJob] = 0;
	PlayerData[playerid][pTaxiFee] = 0;
	PlayerData[playerid][pTaxiTime] = 0;
	PlayerData[playerid][pTaxiPlayer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pTaxiDuty] = 0;
	PlayerData[playerid][pFirstAid] = 0;
	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[playerid][pMining] = 0;
	PlayerData[playerid][pMineTime] = 0;
	PlayerData[playerid][pMineCount] = 0;
	PlayerData[playerid][pMinedRock] = 0;
	PlayerData[playerid][pCarryTrash] = 0;
	PlayerData[playerid][pCarryCrate] = -1;
	PlayerData[playerid][pCrafting] = 0;
	PlayerData[playerid][pOpeningCrate] = 0;
	PlayerData[playerid][pHarvesting] = 0;
	PlayerData[playerid][pFaction] = -1;
	PlayerData[playerid][pFactionID] = -1;
	PlayerData[playerid][pFactionRank] = 0;
	PlayerData[playerid][pFactionEdit] = -1;
	PlayerData[playerid][pSelectedSlot] = -1;
	PlayerData[playerid][pOnDuty] = 0;
	PlayerData[playerid][pFacSkin] = 0; 
	PlayerData[playerid][pTazer] = 0;
	PlayerData[playerid][pBeanBag] = 0;
	PlayerData[playerid][pStunned] = 0;
	PlayerData[playerid][pCuffed] = 0;
    PlayerData[playerid][pDragged] = 0;
    PlayerData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
	PlayerData[playerid][pPrisoned] = 0;
	PlayerData[playerid][pInjured] = 0;
	PlayerData[playerid][pInjuredTime] = 0;
	PlayerData[playerid][pWarrants] = 0;
    PlayerData[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
    PlayerData[playerid][pTrackTime] = 0;
	PlayerData[playerid][pCP] = 0;
	PlayerData[playerid][pMuteTime] = 0;
	PlayerData[playerid][pTransfer] = INVALID_PLAYER_ID;
	PlayerData[playerid][pWaypoint] = 0;
	PlayerData[playerid][pWaypointPos][0] = 0.0;
	PlayerData[playerid][pWaypointPos][1] = 0.0;
	PlayerData[playerid][pWaypointPos][2] = 0.0;
	PlayerData[playerid][pFuelCan] = 0;
	PlayerData[playerid][pDrugTime] = 0;
	PlayerData[playerid][pDrugUsed] = 0;
	PlayerData[playerid][pFingerTime] = 0;
	PlayerData[playerid][pFingerItem] = 0;
	PlayerData[playerid][pWeapon] = 0;
	PlayerData[playerid][pBackpackLoot] = -1;
	PlayerData[playerid][pChannel] = 0;
	PlayerData[playerid][pEmergency] = 0;
	PlayerData[playerid][pPlaceAd] = 0;
	PlayerData[playerid][pTargets] = 0;
	PlayerData[playerid][pTargetLevel] = 0;
	PlayerData[playerid][pVendorTime] = 0;
	PlayerData[playerid][pLoopAnim] = 0;
	PlayerData[playerid][pExecute] = 0;
	PlayerData[playerid][pBoombox] = INVALID_PLAYER_ID;
	PlayerData[playerid][pDrinkTime] = 0;
	PlayerData[playerid][pTaxiCalled] = 0;
	PlayerData[playerid][pLoadType] = 0;
	PlayerData[playerid][pLoadCrate] = 0;
	PlayerData[playerid][pLoading] = 0;
	PlayerData[playerid][pUnloading] = -1;
	PlayerData[playerid][pUnloadVehicle] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pShipment] = -1;
	PlayerData[playerid][pDeliverShipment] = 0;
	PlayerData[playerid][pAdvertise][0] = 0;
	PlayerData[playerid][pFreeze] = 0;
    PlayerData[playerid][pSorting] = -1;
    PlayerData[playerid][pSortCrate] = 0;
    PlayerData[playerid][pHUD] = 1;
    PlayerData[playerid][pAdminDuty] = 0;
    PlayerData[playerid][pSeekHelp] = 0;
    PlayerData[playerid][pMaskOn] = 0;
    PlayerData[playerid][pFactionMod] = 0;
    PlayerData[playerid][pCapacity] = 35;
    PlayerData[playerid][pPlayRadio] = 0;
    PlayerData[playerid][pGraffiti] = -1;
    PlayerData[playerid][pGraffitiTime] = 0;
    PlayerData[playerid][pGraffitiColor] = 0;
    PlayerData[playerid][pEditGraffiti] = -1;
    PlayerData[playerid][pAdminHide] = 0;
    PlayerData[playerid][pPicking] = 0;
    PlayerData[playerid][pPickCar] = -1;
	PlayerData[playerid][pPickTime] = 0;
	PlayerData[playerid][pCarColor1] = 0;
	PlayerData[playerid][pCarColor2] = 0;
	PlayerData[playerid][pKaitKelapa] = 0;
	PlayerData[playerid][pKaitKelapaCP] = 0;
	PlayerData[playerid][pPin] = 0;
	PlayerData[playerid][pPassword] = 0;
	PlayerData[playerid][pSweeper] = 0;
	PlayerData[playerid][pSweeperCP] = 0;
	PlayerData[playerid][pDisableSpeedo] = 0;
	PlayerData[playerid][pAdminCode] = 0;
    ResetWarnings(playerid);
}

ResetWarnings(playerid)
{
    PlayerData[playerid][pWarnings] = 0;
   	PlayerData[playerid][pWarn1][0] = 0;
    PlayerData[playerid][pWarn2][0] = 0;
}

ClearChat(playerid)
{
	for (new i = 0; i < 100; i ++) {
	    SendClientMessage(playerid, -1, "");
	}
	return 1;
}

GetNumberOwner(number)
{
	foreach (new i : Player) if (PlayerData[i][pPhone] == number && Inventory_HasItem(i, "Cellphone")) {
		return i;
	}
	return INVALID_PLAYER_ID;
}

IsPlayerInsideTaxi(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (GetVehicleModel(vehicleid) == 420 || GetVehicleModel(vehicleid) == 438)
	{
	    foreach (new i : Player)
		{
			if ((i != playerid) && (PlayerData[i][pJob] == JOB_TAXI && PlayerData[i][pTaxiDuty] && GetPlayerState(i) == PLAYER_STATE_DRIVER) && GetPlayerVehicleID(i) == vehicleid)
				return 1;
		}
	}
	return 0;
}

SelectCharacter(playerid, id)
{
	PlayerData[playerid][pCharacter] = id;

	if (!PlayerCharacters[playerid][id - 1][0])
	    return Dialog_Show(playerid, CreateChar, DIALOG_STYLE_INPUT, "Buat Watak", "Sila masukkan nama watak baharu anda di bawah:\n\nAmaran: Nama anda mestilah dalam format Firstname_Lastname dan tidak melebihi 20 aksara.", "Buat", "Batal");

	SQL_LoadCharacter(playerid, PlayerData[playerid][pCharacter]);
	return 1;
}

IsNumeric(const str[])
{
	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if (i == 0 && str[0] == '-')
			continue;

	    else if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

ReturnWeaponName(weaponid)
{
	static
		name[32];

	GetWeaponName(weaponid, name, sizeof(name));

	if (!weaponid)
	    name = "None";

	else if (weaponid == 18)
	    name = "Molotov Cocktail";

	else if (weaponid == 44)
	    name = "Nightvision";

	else if (weaponid == 45)
	    name = "Infrared";

	return name;
}

ReturnVehicleModelName(model)
{
	new
	    name[32] = "None";

    if (model < 400 || model > 611)
	    return name;

	format(name, sizeof(name), g_arrVehicleNames[model - 400]);
	return name;
}

GetVehicleModelByName(const name[])
{
	if (IsNumeric(name) && (strval(name) >= 400 && strval(name) <= 611))
	    return strval(name);

	for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
	{
	    if (strfind(g_arrVehicleNames[i], name, true) != -1)
	    {
	        return i + 400;
		}
	}
	return 0;
}

GetVehicleDriver(vehicleid) {
	foreach (new i : Player) {
		if (GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid) return i;
	}
	return INVALID_PLAYER_ID;
}

RandomEx(min, max)
{
    return random(max - min) + min;
}

Uptime()
{
	new uptime[40];
	switch(up_days)
	{
	    case 0:
	    {
			if(up_hours)
			{
				if(up_minutes)
					format(uptime, sizeof(uptime), "%d hour%s and %d minute%s", up_hours, (up_hours != 1 ?("s") : ("")), up_minutes, (up_minutes != 1 ? ("s") : ("")));
				else
					format(uptime, sizeof(uptime), "%d hour%s", up_hours, (up_hours != 1 ? ("s") : ("")));
			}
			else
			{
				if(up_minutes)
					format(uptime, sizeof(uptime), "%d minute%s and %d second%s", up_minutes, (up_minutes != 1 ? ("s") : ("")), up_seconds, (up_seconds != 1 ? ("s") : ("")));
				else
					format(uptime, sizeof(uptime), "%d seconds", up_seconds);
			}
		}
		case 1:
		{
			switch(up_hours)
			{
				case 0: uptime = "24 hours";
				case 1: uptime = "one day and 1 hour";
				default: format(uptime, sizeof(uptime), "one day and %d hours", up_hours);
			}
		}
		default:
		{
			switch(up_hours)
			{
				case 0: format(uptime, sizeof(uptime), "%d days", up_days);
				case 1: format(uptime, sizeof(uptime), "%d days and 1 hour", up_days);
				default: format(uptime, sizeof(uptime), "%d days and %d hours", up_days, up_hours);
			}
		}
	}
	return uptime;
}

encode_lights(light1, light2, light3, light4) return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
encode_doors(bonnet, boot, driver_door, passenger_door)return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper) return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);

IsVehicleOccupied(vehicleid)
{
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(IsPlayerInVehicle(i,vehicleid)) return true;
    }
    return false;
}

/*DeathReason(weaponid)
{
    new weapon[22];
    switch(weaponid)
    {
        case 0: weapon = "Fist";
        case 18: weapon = "Molotov Cocktail";
		case 29: weapon = "Driver Shoot";
        case 44: weapon = "Night Vision Goggles";
		case 47: weapon = "Fake Pistol";
		case 49: weapon = "Vehicle";
        case 45: weapon = "Thermal Goggles";
		case 50: weapon = "Heli Blading";
		case 51: weapon = "Explosion";
		case 53: weapon = "Drowned";
        case 54: weapon = "Fall";
		case 255: weapon = "Suicide";
        default: GetWeaponName(weaponid, weapon, sizeof(weapon));
    }
    return weapon;
}*/

ShowStats(playerid, userid)
{
	new string[1124];

	format(string,sizeof(string),""RED_E"> "GREEN_E"AKAUN\n");
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Nama : %s\n", string, PlayerData[userid][pName]);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Jantina : %s\n", string, (PlayerData[userid][pGender] == 2) ? ("Perempuan") : ("Lelaki"));
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Tarikh Lahir : %s\n", string, PlayerData[userid][pBirthdate]);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Asal : %s\n", string, PlayerData[userid][pOrigin]);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Duit : %s\n", string, FormatNumber(PlayerData[userid][pMoney]));
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Duit Bank : %s\n", string, FormatNumber(PlayerData[userid][pBankMoney])); 
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Score : %d\n", string, PlayerData[userid][pScore]);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Nombor Telefon : %d\n", string, PlayerData[userid][pPhone]);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Warning : %d/3\n\n", string, PlayerData[userid][pWarnings]);

	format(string,sizeof(string),"%s"RED_E"> "GREEN_E"PEKERJAAN\n", string);
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Faction : %s\n", string, Faction_GetName(userid));
	if (PlayerData[userid][pFaction] != -1)
	{
 		format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Faction Rank : %s\n", string, Faction_GetRank(userid));
	}
	format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Job : %s\n\n", string, Job_GetName(PlayerData[userid][pJob]));

	format(string,sizeof(string),"%s"RED_E"> "GREEN_E"LESEN\n", string);
	if (Inventory_HasItem(playerid, "Driving License")) format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Lesen Memandu : Ada\n", string);
 	else format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Lesen Memandu : Tiada\n", string);
	if (Inventory_HasItem(playerid, "Weapon License")) format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Lesen Senjata : Ada\n", string);
	else format(string,sizeof(string),"%s"RED_E"- "WHITE_E"Lesen Senjata : Tiada\n", string);

	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "MYKAD ANDA", string, "Tutup", "");
}

ReturnDateTimestamp(timestamp)
{
	new year, month, day, hour, minute, second;
	TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);

	new date[30];
	format(date, sizeof (date), "%d/%d/%d - %d:%d:%d", month, day, year, hour, minute, second);
	return date;
}

ReplaceSpacesWithUnderscore(string[])
{
    new len = strlen(string);

    for (new i = 0; i < len; i++)
    {
        if (string[i] == ' ')
        {
            string[i] = '_';
        }
    }
}

UpdatePlayerHudData(i)
{
	if (PlayerData[i][pHUD] && PlayerData[i][pJailTime] < 1) 
	{
		new str[400];

		SetPlayerProgressBarValue(i, LAPARHAUSBAR[i][0], PlayerData[i][pHunger]);
		SetPlayerProgressBarValue(i, LAPARHAUSBAR[i][1], PlayerData[i][pThirst]);
		SetPlayerProgressBarValue(i, LAPARHAUSBAR[i][2], PlayerData[i][pStress]);

		format(str, sizeof(str), "%d", Iter_Count(Player));
		TextDrawSetString(PLAYERONLINE[i][3], str);

		format(str, sizeof(str), "%d", PlayerData[i][pMoney]);
		TextDrawSetString(LAPARHAUS[i][8], str);
	}
	return 1;
}

SetPlayerArmourEx(playerid, Float:armor)
{
	PlayerData[playerid][pArmorStatus] = armor;
	SetPlayerArmour(playerid, armor);
}

SetPlayerHealthEx(playerid, Float:health)
{
	PlayerData[playerid][pHealth] = health;
	SetPlayerHealth(playerid, health);
}

GivePlayerHelmet(playerid)
{
	new skin = GetPlayerSkin(playerid);
	if(HelmetPos[skin][0] == 0.0)
		return 0;

	static Float:HelmetScaleX = 1.0, Float:HelmetScaleY = 1.0, Float:HelmetScaleZ = 1.0;
	if(HelmetPos[skin][6] > 0.0) HelmetScaleX = HelmetPos[skin][6];
	if(HelmetPos[skin][7] > 0.0) HelmetScaleY = HelmetPos[skin][7];
	if(HelmetPos[skin][8] > 0.0) HelmetScaleZ = HelmetPos[skin][8];

	SetPlayerAttachedObject(playerid, 9, 18645, 2, HelmetPos[skin][0], HelmetPos[skin][1], HelmetPos[skin][2], HelmetPos[skin][3], HelmetPos[skin][4], HelmetPos[skin][5], HelmetScaleX, HelmetScaleY, HelmetScaleZ);
	return 1;
}

Rent_Delete(rentid)
{
	if (rentid != -1 && RentData[rentid][rentExists])
	{
	    static
	        string[64];

        if (IsValidDynamicPickup(RentData[rentid][rentPickup]))
		    DestroyDynamicPickup(RentData[rentid][rentPickup]);

		if (IsValidDynamic3DTextLabel(RentData[rentid][rentText3D]))
		    DestroyDynamic3DTextLabel(RentData[rentid][rentText3D]);

		format(string, sizeof(string), "DELETE FROM `rentpoints` WHERE `rentID` = '%d'", RentData[rentid][rentID]);
		mysql_tquery(g_iHandle, string);

		RentData[rentid][rentExists] = false;
		RentData[rentid][rentID] = 0;
	}
	return 1;
}

Rent_Create(Float:x, Float:y, Float:z, interior, world)
{
	for (new i = 0; i < MAX_RENT_POINTS; i ++) if (!RentData[i][rentExists])
	{
	    RentData[i][rentExists] = true;
	    RentData[i][rentPos][0] = x;
	    RentData[i][rentPos][1] = y;
	    RentData[i][rentPos][2] = z;
	    RentData[i][rentInterior] = interior;
	    RentData[i][rentWorld] = world;

	    mysql_tquery(g_iHandle, "INSERT INTO `rentpoints` (`rentInterior`) VALUES(0)", "OnRentCreated", "d", i);
		Rent_Refresh(i);
		return i;
	}
	return -1;
}

Rent_Save(rentid)
{
	static
	    query[220];

	format(query, sizeof(query), "UPDATE `rentpoints` SET `rentX` = '%.4f', `rentY` = '%.4f', `rentZ` = '%.4f', `rentInterior` = '%d', `rentWorld` = '%d' WHERE `rentID` = '%d'",
	    RentData[rentid][rentPos][0],
	    RentData[rentid][rentPos][1],
	    RentData[rentid][rentPos][2],
	    RentData[rentid][rentInterior],
	    RentData[rentid][rentWorld],
	    RentData[rentid][rentID]
	);
	return mysql_tquery(g_iHandle, query);
}

Rent_Refresh(rentid)
{
	if (rentid != -1 && RentData[rentid][rentExists])
	{
	    static
	        string[64];

		if (IsValidDynamicPickup(RentData[rentid][rentPickup]))
		    DestroyDynamicPickup(RentData[rentid][rentPickup]);

		if (IsValidDynamic3DTextLabel(RentData[rentid][rentText3D]))
		    DestroyDynamic3DTextLabel(RentData[rentid][rentText3D]);

		format(string, sizeof(string), "[RENT POINT]\n{FFFFFF}Press "GREEN_E"Y"WHITE_E" to rent vehicle.");

		RentData[rentid][rentPickup] = CreateDynamicPickup(19134, 23, RentData[rentid][rentPos][0], RentData[rentid][rentPos][1], RentData[rentid][rentPos][2], RentData[rentid][rentWorld], RentData[rentid][rentInterior]);
  		RentData[rentid][rentText3D] = CreateDynamic3DTextLabel(string, COLOR_DARKBLUE, RentData[rentid][rentPos][0], RentData[rentid][rentPos][1], RentData[rentid][rentPos][2], 10.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, RentData[rentid][rentWorld], RentData[rentid][rentInterior]);
	}
	return 1;
}

Rent_Nearest(playerid)
{
    for (new i = 0; i != MAX_RENT_POINTS; i ++) if (RentData[i][rentExists] && IsPlayerInRangeOfPoint(playerid, 4.0, RentData[i][rentPos][0], RentData[i][rentPos][1], RentData[i][rentPos][2]))
	{
		if (GetPlayerInterior(playerid) == RentData[i][rentInterior] && GetPlayerVirtualWorld(playerid) == RentData[i][rentWorld])
			return i;
	}
	return -1;
}

AddPlayerSalary(playerid, info[], money)
{
	new query[512];
	mysql_format(g_iHandle, query, sizeof(query), "INSERT INTO salary(Owner, Info, Money, Date) VALUES ('%d', '%s', '%d', CURRENT_TIMESTAMP())", PlayerData[playerid][pID], info, money);
	mysql_tquery(g_iHandle, query);
	return true;
}

// --------------------------------- End Natives