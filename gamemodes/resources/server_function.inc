function OnJailAccount(index)
{
	new
		string[128],
		name[24],
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);
	GetPVarString(index, "OnJailAccount", name, 24);
	//GetPVarString(index, "OnJailAccountReason", reason, 64);

	if(cache_affected_rows(g_iHandle)) {
		format(string, sizeof(string), "You have successfully jailed %s's account.", name);
		SendClientMessageEx(index, COLOR_WHITE, string);

	}
	else {
		format(string, sizeof(string), "There was an issue with jailing %s's account.", name);
		SendClientMessageEx(index, COLOR_WHITE, string);
	}

	DeletePVar(index, "OnJailAccount");

	return 1;
}

function BreakCuffs(playerid, userid)
{
	if (PlayerData[playerid][pCuffed] || PlayerData[playerid][pInjured] || !IsPlayerSpawned(playerid) || !Inventory_HasItem(playerid, "Crowbar") || !IsPlayerNearPlayer(playerid, userid, 6.0) || !PlayerData[userid][pCuffed])
	    return 1;

	if (random(2))
	{
	    SendErrorMessage(playerid, "You have failed to pick the cuffs.");
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has failed to pick the cuffs.", ReturnName(playerid, 0));
	}
	else
	{
	    PlayerData[userid][pCuffed] = 0;
	    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);

	    SendInfoMessage(playerid, "You have picked the cuffs.");
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked the cuffs from %s's wrists.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	return 1;
}

function UnfreezeTimer(playerid)
{
	TogglePlayerControllable(playerid, 1);
	return 1;
}

function UnfreezeJob(playerid)
{
	TogglePlayerControllable(playerid, 1);
	ClearAnimations(playerid, 1);
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

function RemoveAttachedObject(playerid, slot)
{
	if (IsPlayerConnected(playerid) && IsPlayerAttachedObjectSlotUsed(playerid, slot))
	{
	    RemovePlayerAttachedObject(playerid, slot);
	}
	return 1;
}

function FinishDrinking(playerid)
{
	if (IsPlayerConnected(playerid) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DRINK_SPRUNK)
	{
	    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE); 
	}
	return 1;
}

function HideTDMETER1(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][1]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][2]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][3]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][4]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][5]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER2(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][2]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][3]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][4]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][5]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER3(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][3]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][4]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][5]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER4 (playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][4]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][5]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER5(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][5]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER6(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][6]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER7(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][7]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER8(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][8]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER9(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][9]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER10(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][10]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER11(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][11]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER12(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][12]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER13(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][13]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER14(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][14]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]);
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER15(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][15]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]);TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER16(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][16]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER17(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][17]); TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}

function HideTDMETER18(playerid)
{
	TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][18]);
}


function MineTime(playerid)
{
	PlayerData[playerid][pMineTime] = 0;
}

function DestroyBlood(objectid)
{
	DestroyDynamicObject(objectid);
}

function HidePlayerBox(playerid, PlayerText:boxid)
{
	if (!IsPlayerConnected(playerid) || !SQL_IsLogged(playerid))
	    return 0;

	PlayerTextDrawHide(playerid, boxid);
	PlayerTextDrawDestroy(playerid, boxid);

	return 1;
}

function Advertise(playerid)
{
	if (!SQL_IsLogged(playerid) || !strlen(PlayerData[playerid][pAdvertise]))
	    return 0;

	new
	    text[128];

	strunpack(text, PlayerData[playerid][pAdvertise]);

	foreach (new i : Player) {
		SendClientMessageEx(i, 0x00AA00FF, "Newspaper: %s (contact: %d)", text, PlayerData[playerid][pPhone]);
	}

	PlayerData[playerid][pAdvertise][0] = 0;
	return 1;
}

function KickHouse(playerid, id)
{
	if (GetFactionType(playerid) != FACTION_POLICE || House_Nearest(playerid) != id)
	    return 0;

	switch (random(6))
	{
	    case 0..2:
	    {
	        SendErrorMessage(playerid, "You have failed to kick the door down.");
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has failed to kick the door down.", ReturnName(playerid, 0));
		}
		default:
		{
		    HouseData[id][houseLocked] = 0;
		    House_Save(id);

		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has successfully kicked the door down.", ReturnName(playerid, 0));
		    SendInfoMessage(playerid, "Press "YELLOW_E"F"WHITE_E" to enter the house.");
		}
	}
	return 1;
}

function KickBusiness(playerid, id)
{
	if (GetFactionType(playerid) != FACTION_POLICE || Business_Nearest(playerid) != id)
	    return 0;

	switch (random(6))
	{
	    case 0..2:
	    {
	        SendErrorMessage(playerid, "You have failed to kick the door down.");
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has failed to kick the door down.", ReturnName(playerid, 0));
		}
		default:
		{
		    BusinessData[id][bizLocked] = 0;
		    Business_Save(id);

		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has successfully kicked the door down.", ReturnName(playerid, 0));
		    SendErrorMessage(playerid, "Press "YELLOW_E"F"WHITE_E" to enter the business.");
		}
	}
	return 1;
}


function CloseGate(gateid, linkid, Float:fX, Float:fY, Float:fZ, Float:speed, Float:fRotX, Float:fRotY, Float:fRotZ)
{
	new id = -1;

	if (GateData[gateid][gateExists] && GateData[gateid][gateOpened])
 	{
	 	MoveDynamicObject(GateData[gateid][gateObject], fX, fY, fZ, speed, fRotX, fRotY, fRotZ);

	 	if ((id = GetGateByID(linkid)) != -1)
            MoveDynamicObject(GateData[id][gateObject], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], speed, GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5]);

		GateData[id][gateOpened] = 0;
		return 1;
	}
	return 0;
}

function SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z)
{
	if (!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
	    return 0;

	PlayerData[playerid][pFreeze] = 0;

	SetPlayerPos(playerid, x, y, z);
	TogglePlayerControllable(playerid, 1);
	return 1;
}

function RefillUpdate(playerid, vehicleid)
{
	if (!PlayerData[playerid][pFuelCan] || GetNearestVehicle(playerid) != vehicleid)
	    return 0;

	new id = Car_GetID(vehicleid);
	if (id != -1) 
	{
		CarData[id][carFuel] = (CarData[id][carFuel] + 15 >= 100) ? (100) : (CarData[id][carFuel] + 15);
	}

	PlayerData[playerid][pFuelCan] = 0;
	SendServerMessage(playerid, "You have filled up your vehicle with a can of fuel.");
	return 1;
}

function Graffiti_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_GRAFFITI_POINTS)
	{
	    cache_get_field_content(i, "graffitiText", GraffitiData[i][graffitiText], g_iHandle, 64);

    	GraffitiData[i][graffitiExists] = 1;
	    GraffitiData[i][graffitiID] = cache_get_field_int(i, "graffitiID");
	    GraffitiData[i][graffitiPos][0] = cache_get_field_float(i, "graffitiX");
	    GraffitiData[i][graffitiPos][1] = cache_get_field_float(i, "graffitiY");
	    GraffitiData[i][graffitiPos][2] = cache_get_field_float(i, "graffitiZ");
	    GraffitiData[i][graffitiPos][3] = cache_get_field_float(i, "graffitiAngle");
	    GraffitiData[i][graffitiColor] = cache_get_field_int(i, "graffitiColor");

		Graffiti_Refresh(i);
	}
	return 1;
}

function Speed_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_SPEED_CAMERAS)
	{
	    SpeedData[i][speedExists] = true;
	    SpeedData[i][speedID] = cache_get_field_int(i, "speedID");
	    SpeedData[i][speedRange] = cache_get_field_float(i, "speedRange");
	    SpeedData[i][speedLimit] = cache_get_field_float(i, "speedLimit");
		SpeedData[i][speedStatus] = cache_get_field_int(i, "speedStatus");
	    SpeedData[i][speedPos][0] = cache_get_field_float(i, "speedX");
	    SpeedData[i][speedPos][1] = cache_get_field_float(i, "speedY");
	    SpeedData[i][speedPos][2] = cache_get_field_float(i, "speedZ");
	    SpeedData[i][speedPos][3] = cache_get_field_float(i, "speedAngle");

	    Speed_Refresh(i);
	}
	return 1;
}

function Rack_Load()
{
    static
	    rows,
	    fields,
		str[24];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_WEAPON_RACKS)
	{
	    RackData[i][rackExists] = true;
	    RackData[i][rackID] = cache_get_field_int(i, "rackID");
	    RackData[i][rackHouse] = cache_get_field_int(i, "rackHouse");
     	RackData[i][rackPos][0] = cache_get_field_float(i, "rackX");
        RackData[i][rackPos][1] = cache_get_field_float(i, "rackY");
        RackData[i][rackPos][2] = cache_get_field_float(i, "rackZ");
        RackData[i][rackPos][3] = cache_get_field_float(i, "rackA");
        RackData[i][rackInterior] = cache_get_field_int(i, "rackInterior");
		RackData[i][rackWorld] = cache_get_field_int(i, "rackWorld");

		for (new j = 0; j < 4; j ++) {
		    format(str, 24, "rackWeapon%d", j + 1);
		    RackData[i][rackWeapons][j] = cache_get_field_int(i, str);

            format(str, 24, "rackAmmo%d", j + 1);
		    RackData[i][rackAmmo][j] = cache_get_field_int(i, str);
		}
		Rack_Refresh(i);
	}
	return 1;
}

function Vendor_Load()
{
    static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_VENDORS)
	{
	    VendorData[i][vendorExists] = true;
	    VendorData[i][vendorID] = cache_get_field_int(i, "vendorID");
	    VendorData[i][vendorType] = cache_get_field_int(i, "vendorType");
	    VendorData[i][vendorPos][0] = cache_get_field_float(i, "vendorX");
        VendorData[i][vendorPos][1] = cache_get_field_float(i, "vendorY");
        VendorData[i][vendorPos][2] = cache_get_field_float(i, "vendorZ");
        VendorData[i][vendorPos][3] = cache_get_field_float(i, "vendorA");
        VendorData[i][vendorInterior] = cache_get_field_int(i, "vendorInterior");
		VendorData[i][vendorWorld] = cache_get_field_int(i, "vendorWorld");

		Vendor_Refresh(i);
	}
	return 1;
}

function Garbage_Load()
{
    static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_GARBAGE_BINS)
	{
	    GarbageData[i][garbageExists] = true;
	    GarbageData[i][garbageID] = cache_get_field_int(i, "garbageID");
	    GarbageData[i][garbageModel] = cache_get_field_int(i, "garbageModel");
	    GarbageData[i][garbageCapacity] = cache_get_field_int(i, "garbageCapacity");
	    GarbageData[i][garbagePos][0] = cache_get_field_float(i, "garbageX");
        GarbageData[i][garbagePos][1] = cache_get_field_float(i, "garbageY");
        GarbageData[i][garbagePos][2] = cache_get_field_float(i, "garbageZ");
        GarbageData[i][garbagePos][3] = cache_get_field_float(i, "garbageA");
        GarbageData[i][garbageInterior] = cache_get_field_int(i, "garbageInterior");
		GarbageData[i][garbageWorld] = cache_get_field_int(i, "garbageWorld");

		Garbage_Refresh(i);
	}
	return 1;
}

function ATM_Load()
{
    static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_ATM_MACHINES)
	{
	    ATMData[i][atmExists] = true;
	    ATMData[i][atmID] = cache_get_field_int(i, "atmID");
	    ATMData[i][atmPos][0] = cache_get_field_float(i, "atmX");
        ATMData[i][atmPos][1] = cache_get_field_float(i, "atmY");
        ATMData[i][atmPos][2] = cache_get_field_float(i, "atmZ");
        ATMData[i][atmPos][3] = cache_get_field_float(i, "atmA");
        ATMData[i][atmInterior] = cache_get_field_int(i, "atmInterior");
		ATMData[i][atmWorld] = cache_get_field_int(i, "atmWorld");

		ATM_Refresh(i);
	}
	return 1;
}

function Backpack_Load()
{
    static
	    rows,
	    fields,
		str[64];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_BACKPACKS)
	{
	    BackpackData[i][backpackExists] = true;
	    BackpackData[i][backpackID] = cache_get_field_int(i, "backpackID");
	    BackpackData[i][backpackPlayer] = cache_get_field_int(i, "backpackPlayer");
	    BackpackData[i][backpackHouse] = cache_get_field_int(i, "backpackHouse");
	    BackpackData[i][backpackVehicle] = cache_get_field_int(i, "backpackVehicle");
	    BackpackData[i][backpackPos][0] = cache_get_field_float(i, "backpackX");
	    BackpackData[i][backpackPos][1] = cache_get_field_float(i, "backpackY");
	    BackpackData[i][backpackPos][2] = cache_get_field_float(i, "backpackZ");
	    BackpackData[i][backpackInterior] = cache_get_field_int(i, "backpackInterior");
	    BackpackData[i][backpackWorld] = cache_get_field_int(i, "backpackWorld");

	    if (!BackpackData[i][backpackPlayer]) {
	        Backpack_Refresh(i);
		}
	}
	for (new i = 0; i < MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists]) {
		format(str, sizeof(str), "SELECT * FROM `backpackitems` WHERE `ID` = '%d'", BackpackData[i][backpackID]);

		mysql_tquery(g_iHandle, str, "OnLoadBackpack", "d", i);
	}
	return 1;
}

function Gate_Load()
{
    static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_GATES)
	{
	    GateData[i][gateExists] = true;
	    GateData[i][gateOpened] = false;

	    GateData[i][gateID] = cache_get_field_int(i, "gateID");
	    GateData[i][gateModel] = cache_get_field_int(i, "gateModel");
	    GateData[i][gateSpeed] = cache_get_field_float(i, "gateSpeed");
	    GateData[i][gateRadius] = cache_get_field_float(i, "gateRadius");
	    GateData[i][gateTime] = cache_get_field_int(i, "gateTime");
	    GateData[i][gateInterior] = cache_get_field_int(i, "gateInterior");
	    GateData[i][gateWorld] = cache_get_field_int(i, "gateWorld");

	    GateData[i][gatePos][0] = cache_get_field_float(i, "gateX");
	    GateData[i][gatePos][1] = cache_get_field_float(i, "gateY");
	    GateData[i][gatePos][2] = cache_get_field_float(i, "gateZ");
	    GateData[i][gatePos][3] = cache_get_field_float(i, "gateRX");
	    GateData[i][gatePos][4] = cache_get_field_float(i, "gateRY");
	    GateData[i][gatePos][5] = cache_get_field_float(i, "gateRZ");

        GateData[i][gateMove][0] = cache_get_field_float(i, "gateMoveX");
	    GateData[i][gateMove][1] = cache_get_field_float(i, "gateMoveY");
	    GateData[i][gateMove][2] = cache_get_field_float(i, "gateMoveZ");
	    GateData[i][gateMove][3] = cache_get_field_float(i, "gateMoveRX");
	    GateData[i][gateMove][4] = cache_get_field_float(i, "gateMoveRY");
	    GateData[i][gateMove][5] = cache_get_field_float(i, "gateMoveRZ");

        GateData[i][gateLinkID] = cache_get_field_int(i, "gateLinkID");
	    GateData[i][gateFaction] = cache_get_field_int(i, "gateFaction");

	    cache_get_field_content(i, "gatePass", GateData[i][gatePass], g_iHandle, 32);

	    GateData[i][gateObject] = CreateDynamicObject(GateData[i][gateModel], GateData[i][gatePos][0], GateData[i][gatePos][1], GateData[i][gatePos][2], GateData[i][gatePos][3], GateData[i][gatePos][4], GateData[i][gatePos][5], GateData[i][gateWorld], GateData[i][gateInterior], -1, 300.00, 300.00);
	}
	return 1;
}


function Faction_Load()
{
	static
	    rows,
	    fields,
		str[32];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_FACTIONS)
	{
	    FactionData[i][factionExists] = true;
	    FactionData[i][factionID] = cache_get_field_int(i, "factionID");

	    cache_get_field_content(i, "factionName", FactionData[i][factionName], g_iHandle, 32);

	    FactionData[i][factionColor] = cache_get_field_int(i, "factionColor");
	    FactionData[i][factionType] = cache_get_field_int(i, "factionType");
	    FactionData[i][factionRanks] = cache_get_field_int(i, "factionRanks");
		FactionData[i][factionMoney] = cache_get_field_int(i, "factionMoney");
	    FactionData[i][factionLockerPos][0] = cache_get_field_float(i, "factionLockerX");
	    FactionData[i][factionLockerPos][1] = cache_get_field_float(i, "factionLockerY");
	    FactionData[i][factionLockerPos][2] = cache_get_field_float(i, "factionLockerZ");
	    FactionData[i][factionLockerInt] = cache_get_field_int(i, "factionLockerInt");
	    FactionData[i][factionLockerWorld] = cache_get_field_int(i, "factionLockerWorld");
		FactionData[i][factionLeaderLockerPos][0] = cache_get_field_float(i, "factionLeaderLockerX");
	    FactionData[i][factionLeaderLockerPos][1] = cache_get_field_float(i, "factionLeaderLockerY");
	    FactionData[i][factionLeaderLockerPos][2] = cache_get_field_float(i, "factionLeaderLockerZ");

		//Spawning
		FactionData[i][SpawnX] = cache_get_field_float(i, "SpawnX");
	 	FactionData[i][SpawnY] = cache_get_field_float(i, "SpawnY");
   		FactionData[i][SpawnZ] = cache_get_field_float(i, "SpawnZ");
		FactionData[i][SpawnInterior] = cache_get_field_int(i, "SpawnInterior");
  		FactionData[i][SpawnVW] = cache_get_field_int(i, "SpawnVW");

	    for (new j = 0; j < 14; j ++) {
	        format(str, sizeof(str), "factionSkin%d", j + 1);

	        FactionData[i][factionSkins][j] = cache_get_field_int(i, str);
		}
        for (new j = 0; j < 10; j ++) {
	        format(str, sizeof(str), "factionWeapon%d", j + 1);

	        FactionData[i][factionWeapons][j] = cache_get_field_int(i, str);

	        format(str, sizeof(str), "factionAmmo%d", j + 1);

			FactionData[i][factionAmmo][j] = cache_get_field_int(i, str);
		}
		for (new j = 0; j < 15; j ++) {
		    format(str, sizeof(str), "factionRank%d", j + 1);

		    cache_get_field_content(i, str, FactionRanks[i][j], g_iHandle, 32);
		}
		Faction_Refresh(i);
	}
	return 1;
}

function Plant_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_DRUG_PLANTS)
	{
	    PlantData[i][plantExists] = true;
	    PlantData[i][plantID] = cache_get_field_int(i, "plantID");
	    PlantData[i][plantType] = cache_get_field_int(i, "plantType");
	    PlantData[i][plantDrugs] = cache_get_field_int(i, "plantDrugs");
	    PlantData[i][plantPos][0] = cache_get_field_float(i, "plantX");
	    PlantData[i][plantPos][1] = cache_get_field_float(i, "plantY");
	    PlantData[i][plantPos][2] = cache_get_field_float(i, "plantZ");
	    PlantData[i][plantPos][3] = cache_get_field_float(i, "plantA");
	    PlantData[i][plantInterior] = cache_get_field_int(i, "plantInterior");
	    PlantData[i][plantWorld] = cache_get_field_int(i, "plantWorld");

		Plant_Refresh(i);
	}
	return 1;
}

function Crate_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_CRATES)
	{
	    CrateData[i][crateExists] = true;
	    CrateData[i][crateID] = cache_get_field_int(i, "crateID");
	    CrateData[i][crateType] = cache_get_field_int(i, "crateType");
	    CrateData[i][cratePos][0] = cache_get_field_float(i, "crateX");
	    CrateData[i][cratePos][1] = cache_get_field_float(i, "crateY");
	    CrateData[i][cratePos][2] = cache_get_field_float(i, "crateZ");
	    CrateData[i][cratePos][3] = cache_get_field_float(i, "crateA");
	    CrateData[i][crateInterior] = cache_get_field_int(i, "crateInterior");
	    CrateData[i][crateWorld] = cache_get_field_int(i, "crateWorld");
		CrateData[i][crateVehicle] = INVALID_VEHICLE_ID;

		Crate_Refresh(i);
	}
	return 1;
}

function Job_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

    for (new i = 0; i < rows; i ++) if (i < MAX_DYNAMIC_JOBS)
	{
	    JobData[i][jobExists] = true;
	    JobData[i][jobID] = cache_get_field_int(i, "jobID");
	    JobData[i][jobType] = cache_get_field_int(i, "jobType");
	    JobData[i][jobPos][0] = cache_get_field_float(i, "jobPosX");
	    JobData[i][jobPos][1] = cache_get_field_float(i, "jobPosY");
	    JobData[i][jobPos][2] = cache_get_field_float(i, "jobPosZ");
	    JobData[i][jobInterior] = cache_get_field_int(i, "jobInterior");
	    JobData[i][jobWorld] = cache_get_field_int(i, "jobWorld");
        JobData[i][jobPoint][0] = cache_get_field_float(i, "jobPointX");
	    JobData[i][jobPoint][1] = cache_get_field_float(i, "jobPointY");
	    JobData[i][jobPoint][2] = cache_get_field_float(i, "jobPointZ");
	    JobData[i][jobDeliver][0] = cache_get_field_float(i, "jobDeliverX");
	    JobData[i][jobDeliver][1] = cache_get_field_float(i, "jobDeliverY");
	    JobData[i][jobDeliver][2] = cache_get_field_float(i, "jobDeliverZ");
	    JobData[i][jobPointInt] = cache_get_field_int(i, "jobPointInt");
	    JobData[i][jobPointWorld] = cache_get_field_int(i, "jobPointWorld");

 	    Job_Refresh(i);
	}
	return 1;
}

function Entrance_Load()
{
    static
	    rows,
	    fields;

    cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_ENTRANCES)
	{
	    EntranceData[i][entranceExists] = true;
    	EntranceData[i][entranceID] = cache_get_field_int(i, "entranceID");

		cache_get_field_content(i, "entranceName", EntranceData[i][entranceName], g_iHandle, 32);
		cache_get_field_content(i, "entrancePass", EntranceData[i][entrancePass], g_iHandle, 32);

	    EntranceData[i][entranceIcon] = cache_get_field_int(i, "entranceIcon");
	    EntranceData[i][entranceLocked] = cache_get_field_int(i, "entranceLocked");
	    EntranceData[i][entrancePos][0] = cache_get_field_float(i, "entrancePosX");
	    EntranceData[i][entrancePos][1] = cache_get_field_float(i, "entrancePosY");
	    EntranceData[i][entrancePos][2] = cache_get_field_float(i, "entrancePosZ");
	    EntranceData[i][entrancePos][3] = cache_get_field_float(i, "entrancePosA");
	    EntranceData[i][entranceInt][0] = cache_get_field_float(i, "entranceIntX");
	    EntranceData[i][entranceInt][1] = cache_get_field_float(i, "entranceIntY");
	    EntranceData[i][entranceInt][2] = cache_get_field_float(i, "entranceIntZ");
	    EntranceData[i][entranceInt][3] = cache_get_field_float(i, "entranceIntA");
	    EntranceData[i][entranceInterior] = cache_get_field_int(i, "entranceInterior");
	    EntranceData[i][entranceExterior] = cache_get_field_int(i, "entranceExterior");
	    EntranceData[i][entranceExteriorVW] = cache_get_field_int(i, "entranceExteriorVW");
	    EntranceData[i][entranceCustom] = cache_get_field_int(i, "entranceCustom");
	    EntranceData[i][entranceWorld] = cache_get_field_int(i, "entranceWorld");

	    Entrance_Refresh(i);
	}
	return 1;
}

function Dropped_Load()
{
	static
	    rows,
	    fields;

    cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_DROPPED_ITEMS)
	{
	    DroppedItems[i][droppedID] = cache_get_field_int(i, "ID");

		cache_get_field_content(i, "itemName", DroppedItems[i][droppedItem], g_iHandle, 32);
		cache_get_field_content(i, "itemPlayer", DroppedItems[i][droppedPlayer], g_iHandle, 24);

		DroppedItems[i][droppedModel] = cache_get_field_int(i, "itemModel");
		DroppedItems[i][droppedQuantity] = cache_get_field_int(i, "itemQuantity");
		DroppedItems[i][droppedPos][0] = cache_get_field_float(i, "itemX");
		DroppedItems[i][droppedPos][1] = cache_get_field_float(i, "itemY");
		DroppedItems[i][droppedPos][2] = cache_get_field_float(i, "itemZ");
		DroppedItems[i][droppedInt] = cache_get_field_int(i, "itemInt");
		DroppedItems[i][droppedWorld] = cache_get_field_int(i, "itemWorld");

		if (IsWeaponModel(DroppedItems[i][droppedModel])) {
    	   	DroppedItems[i][droppedObject] = CreateDynamicObject(DroppedItems[i][droppedModel], DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 93.7, 120.0, 120.0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
		} else {
			DroppedItems[i][droppedObject] = CreateDynamicObject(DroppedItems[i][droppedModel], DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 0.0, 0.0, 0.0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
		}
		DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(DroppedItems[i][droppedItem], COLOR_CYAN, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
	}
	return 1;
}

function Business_Load()
{
    static
	    rows,
	    fields,
		str[64];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_BUSINESSES)
	{
	    BusinessData[i][bizExists] = true;
	    BusinessData[i][bizID] = cache_get_field_int(i, "bizID");

		cache_get_field_content(i, "bizName", BusinessData[i][bizName], g_iHandle, 32);
        cache_get_field_content(i, "bizMessage", BusinessData[i][bizMessage], g_iHandle, 128);

		BusinessData[i][bizOwner] = cache_get_field_int(i, "bizOwner");
		BusinessData[i][bizType] = cache_get_field_int(i, "bizType");
		BusinessData[i][bizPrice] = cache_get_field_int(i, "bizPrice");
		BusinessData[i][bizPos][0] = cache_get_field_float(i, "bizPosX");
		BusinessData[i][bizPos][1] = cache_get_field_float(i, "bizPosY");
		BusinessData[i][bizPos][2] = cache_get_field_float(i, "bizPosZ");
		BusinessData[i][bizPos][3] = cache_get_field_float(i, "bizPosA");
		BusinessData[i][bizInt][0] = cache_get_field_float(i, "bizIntX");
		BusinessData[i][bizInt][1] = cache_get_field_float(i, "bizIntY");
		BusinessData[i][bizInt][2] = cache_get_field_float(i, "bizIntZ");
		BusinessData[i][bizInt][3] = cache_get_field_float(i, "bizIntA");
		BusinessData[i][bizSpawn][0] = cache_get_field_float(i, "bizSpawnX");
		BusinessData[i][bizSpawn][1] = cache_get_field_float(i, "bizSpawnY");
		BusinessData[i][bizSpawn][2] = cache_get_field_float(i, "bizSpawnZ");
		BusinessData[i][bizSpawn][3] = cache_get_field_float(i, "bizSpawnA");
		BusinessData[i][bizDeliver][0] = cache_get_field_float(i, "bizDeliverX");
		BusinessData[i][bizDeliver][1] = cache_get_field_float(i, "bizDeliverY");
		BusinessData[i][bizDeliver][2] = cache_get_field_float(i, "bizDeliverZ");
		BusinessData[i][bizCaunter][0] = cache_get_field_float(i, "bizCaunterX");
		BusinessData[i][bizCaunter][1] = cache_get_field_float(i, "bizCaunterY");
		BusinessData[i][bizCaunter][2] = cache_get_field_float(i, "bizCaunterZ");
		BusinessData[i][bizActor][0] = cache_get_field_float(i, "bizActorX");
		BusinessData[i][bizActor][1] = cache_get_field_float(i, "bizActorY");
		BusinessData[i][bizActor][2] = cache_get_field_float(i, "bizActorZ");
		BusinessData[i][bizActor][3] = cache_get_field_float(i, "bizActorA");
		BusinessData[i][bizShipment] = cache_get_field_int(i, "bizShipment");
		BusinessData[i][bizInterior] = cache_get_field_int(i, "bizInterior");
		BusinessData[i][bizExterior] = cache_get_field_int(i, "bizExterior");
		BusinessData[i][bizExteriorVW] = cache_get_field_int(i, "bizExteriorVW");
		BusinessData[i][bizLocked] = cache_get_field_int(i, "bizLocked");
		BusinessData[i][bizSita] = cache_get_field_int(i, "bizSita");
		BusinessData[i][bizVault] = cache_get_field_int(i, "bizVault");
		BusinessData[i][bizProducts] = cache_get_field_int(i, "bizProducts");

		for (new j = 0; j < 20; j ++)
		{
			format(str, 32, "bizPrice%d", j + 1);
			BusinessData[i][bizPrices][j] = cache_get_field_int(i, str);
		}
		Business_Refresh(i);
	}
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists])
	{
		if (BusinessData[i][bizType] == 5) {
			format(str, sizeof(str), "SELECT * FROM `dealervehicles` WHERE `ID` = '%d'", BusinessData[i][bizID]);

			mysql_tquery(g_iHandle, str, "Business_LoadCars", "d", i);
		}
		else if (BusinessData[i][bizType] == 6) {
			format(str, sizeof(str), "SELECT * FROM `pumps` WHERE `ID` = '%d'", BusinessData[i][bizID]);

			mysql_tquery(g_iHandle, str, "Pump_Load", "d", i);
		}
	}
	return 1;
}

function House_Load()
{
	static
	    rows,
	    fields,
		str[128];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_HOUSES)
	{
		HouseData[i][houseExists] = true;
		HouseData[i][houseLights] = false;

		HouseData[i][houseID] = cache_get_field_int(i, "houseID");
		HouseData[i][houseOwner] = cache_get_field_int(i, "houseOwner");
		HouseData[i][housePrice] = cache_get_field_int(i, "housePrice");

		cache_get_field_content(i, "houseAddress", HouseData[i][houseAddress], g_iHandle, 32);

		HouseData[i][housePos][0] = cache_get_field_float(i, "housePosX");
		HouseData[i][housePos][1] = cache_get_field_float(i, "housePosY");
		HouseData[i][housePos][2] = cache_get_field_float(i, "housePosZ");
		HouseData[i][housePos][3] = cache_get_field_float(i, "housePosA");
		HouseData[i][houseInt][0] = cache_get_field_float(i, "houseIntX");
		HouseData[i][houseInt][1] = cache_get_field_float(i, "houseIntY");
		HouseData[i][houseInt][2] = cache_get_field_float(i, "houseIntZ");
		HouseData[i][houseInt][3] = cache_get_field_float(i, "houseIntA");
		HouseData[i][houseInterior] = cache_get_field_int(i, "houseInterior");
		HouseData[i][houseExterior] = cache_get_field_int(i, "houseExterior");
		HouseData[i][houseExteriorVW] = cache_get_field_int(i, "houseExteriorVW");
        HouseData[i][houseLocked] = cache_get_field_int(i, "houseLocked");
		HouseData[i][houseSita] = cache_get_field_int(i, "houseSita");
        HouseData[i][houseMoney] = cache_get_field_int(i, "houseMoney");

        for (new j = 0; j < 10; j ++)
		{
            format(str, 24, "houseWeapon%d", j + 1);
            HouseData[i][houseWeapons][j] = cache_get_field_int(i, str);

            format(str, 24, "houseAmmo%d", j + 1);
            HouseData[i][houseAmmo][j] = cache_get_field_int(i, str);
		}
		House_Refresh(i);
	}
	for (new i = 0; i < MAX_HOUSES; i ++) if (HouseData[i][houseExists]) {
		format(str, sizeof(str), "SELECT * FROM `housestorage` WHERE `ID` = '%d'", HouseData[i][houseID]);

		mysql_tquery(g_iHandle, str, "OnLoadStorage", "d", i);

		format(str, sizeof(str), "SELECT * FROM `furniture` WHERE `ID` = '%d'", HouseData[i][houseID]);

		mysql_tquery(g_iHandle, str, "OnLoadFurniture", "d", i);
	}
	return 1;
}

function HarvestPlant(playerid, plantid)
{
	PlayerData[playerid][pHarvesting] = 0;

	if (Plant_Nearest(playerid) != plantid || GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK || !PlantData[plantid][plantExists])
	    return 0;

	switch (PlantData[plantid][plantType])
	{
	    case 1:
	    {
	        new id = Inventory_Add(playerid, "Marijuana", 1578, PlantData[plantid][plantDrugs]);

	        if (id == -1)
	            return SendErrorMessage(playerid, "You don't have any room in your inventory.");

	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has harvested %d grams of marijuana.", ReturnName(playerid, 0), PlantData[plantid][plantDrugs]);
		}
		case 2:
	    {
	        new id = Inventory_Add(playerid, "Cocaine", 1575, PlantData[plantid][plantDrugs]);

	        if (id == -1)
	            return SendErrorMessage(playerid, "You don't have any room in your inventory.");

	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has harvested %d grams of cocaine.", ReturnName(playerid, 0), PlantData[plantid][plantDrugs]);
		}
        case 3:
	    {
	        new id = Inventory_Add(playerid, "Heroin", 1577, PlantData[plantid][plantDrugs]);

	        if (id == -1)
	            return SendErrorMessage(playerid, "You don't have any room in your inventory.");

	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has harvested %d grams of heroin.", ReturnName(playerid, 0), PlantData[plantid][plantDrugs]);
		}
	}
	Plant_Delete(plantid);
	return 1;
}

function OpenCrate(playerid, crateid)
{
	if (Crate_Nearest(playerid) != crateid || !CrateData[crateid][crateExists] || !IsPlayerSpawned(playerid) || !PlayerData[playerid][pOpeningCrate])
	    return 0;

    PlayerData[playerid][pOpeningCrate] = 0;

	ClearAnimations(playerid);
    TogglePlayerControllable(playerid, 1);

	if (Inventory_Items(playerid) >= MAX_INVENTORY - 4)
	    return SendErrorMessage(playerid, "You don't have any room in your inventory for 4 drug packages.");

	Inventory_Add(playerid, "Cocaine Seeds", 1575, 20);
	Inventory_Add(playerid, "Marijuana Seeds", 1578, 20);
	Inventory_Add(playerid, "Heroin Opium Seeds", 1577, 10);
	Inventory_Add(playerid, "Steroids", 1241, 5);

	Crate_Delete(crateid);
	SendServerMessage(playerid, "You have found an assortment of steroids and drug seeds (added to inventory).");
	return 1;
}

function CraftParts(playerid, crateid)
{
	if (PlayerData[playerid][pCarryCrate] != crateid || !CrateData[crateid][crateExists] || !IsPlayerSpawned(playerid) || !PlayerData[playerid][pCrafting])
	    return 0;

    PlayerData[playerid][pCrafting] = 0;
	PlayerData[playerid][pCarryCrate] = -1;

    TogglePlayerControllable(playerid, 1);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

    RemovePlayerAttachedObject(playerid, 4);
    Log_Write("logs/craft_log.txt", "[%s] %s has crafted a %s crate.", ReturnDate(), ReturnName(playerid, 0), Crate_GetType(CrateData[crateid][crateType]));

	switch (CrateData[crateid][crateType])
	{
	    case 1:
	    {
			GiveWeaponToPlayer(playerid, 2, 210);
			GiveWeaponToPlayer(playerid, 4, 210);
			GiveWeaponToPlayer(playerid, 6, 210);
			GiveWeaponToPlayer(playerid, 8, 210);

			Crate_Delete(crateid);
			SendServerMessage(playerid, "You have crafted 4 melee weapons.");
		}
	    case 2:
	    {
			GiveWeaponToPlayer(playerid, 22, 210);
			GiveWeaponToPlayer(playerid, 24, 210);

	        Crate_Delete(crateid);
			SendServerMessage(playerid, "You have crafted 2 pistols from pistol parts.");
		}
		case 3:
	    {
			GiveWeaponToPlayer(playerid, 28, 210);
			GiveWeaponToPlayer(playerid, 32, 210);
			GiveWeaponToPlayer(playerid, 29, 210);

			Crate_Delete(crateid);
			SendServerMessage(playerid, "You have crafted 3 SMG's from SMG parts.");
		}
		case 4:
	    {
			GiveWeaponToPlayer(playerid, 25, 210);

			Crate_Delete(crateid);
			SendServerMessage(playerid, "You have crafted a shotgun from Shotgun parts.");
		}
		case 5:
	    {
			GiveWeaponToPlayer(playerid, 30, 210);
			GiveWeaponToPlayer(playerid, 33, 210);
			GiveWeaponToPlayer(playerid, 34, 210);

			Crate_Delete(crateid);
			SendServerMessage(playerid, "You have crafted 3 rifles from Rifle parts.");
		}
	}
	return 1;
}

function FirstAidUpdate(playerid)
{
	static
	    Float:health;

	GetPlayerHealth(playerid, health);

    if (!IsPlayerInAnyVehicle(playerid) && GetPlayerAnimationIndex(playerid) != 1508)
    	ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	if (health >= 95.0)
	{
	    SetPlayerHealthEx(playerid, 100.0);
	    SendServerMessage(playerid, "Your first aid kit has been used up.");

		if (!IsPlayerInAnyVehicle(playerid)) 
		{
	        ClearAnimations(playerid, 1);
			PlayerData[playerid][pLoopAnim] = 0;
		}

		PlayerData[playerid][pFirstAid] = false;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}
	else {
	    SetPlayerHealthEx(playerid, floatadd(health, 4.0));
	}
	return 1;
}

function RepairCar(playerid, vehicleid)
{
	if (!IsPlayerNearHood(playerid, vehicleid)) {
		return 0;
	}
	SetVehicleHealth(vehicleid, 1000.0);
	GameTextForPlayer(playerid, " ", 1, 3);

	PlayerData[playerid][pRepairTime] = gettime() + 60;
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has successfully repaired the vehicle.", ReturnName(playerid, 0));

	return 1;
}

function Business_LoadCars(bizid)
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i != rows; i ++) {
		DealershipCars[bizid][i][vehID] = cache_get_field_int(i, "vehID");
		DealershipCars[bizid][i][vehModel] = cache_get_field_int(i, "vehModel");
		DealershipCars[bizid][i][vehPrice] = cache_get_field_int(i, "vehPrice");
	}
	return 1;
}

function OnLoadFurniture(houseid)
{
	static
	    rows,
	    fields,
		id = -1;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i != rows; i ++) if ((id = Furniture_GetFreeID()) != -1) {
	    FurnitureData[id][furnitureExists] = true;
	    FurnitureData[id][furnitureHouse] = houseid;

	    cache_get_field_content(i, "furnitureName", FurnitureData[id][furnitureName], g_iHandle, 32);

	    FurnitureData[id][furnitureID] = cache_get_field_int(i, "furnitureID");
	    FurnitureData[id][furnitureModel] = cache_get_field_int(i, "furnitureModel");
	    FurnitureData[id][furniturePos][0] = cache_get_field_float(i, "furnitureX");
	    FurnitureData[id][furniturePos][1] = cache_get_field_float(i, "furnitureY");
	    FurnitureData[id][furniturePos][2] = cache_get_field_float(i, "furnitureZ");
	    FurnitureData[id][furnitureRot][0] = cache_get_field_float(i, "furnitureRX");
	    FurnitureData[id][furnitureRot][1] = cache_get_field_float(i, "furnitureRY");
	    FurnitureData[id][furnitureRot][2] = cache_get_field_float(i, "furnitureRZ");

	    Furniture_Refresh(id);
	}
	return 1;
}

function OnLoadCarStorage(carid)
{
	static
	    rows,
	    fields,
		str[32];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i != rows; i ++) {
		CarStorage[carid][i][cItemExists] = true;
		CarStorage[carid][i][cItemID] = cache_get_field_int(i, "itemID");
		CarStorage[carid][i][cItemModel] = cache_get_field_int(i, "itemModel");
		CarStorage[carid][i][cItemQuantity] = cache_get_field_int(i, "itemQuantity");

		cache_get_field_content(i, "itemName", str, g_iHandle, sizeof(str));
		strpack(CarStorage[carid][i][cItemName], str, 32 char);
	}
	return 1;
}

function OnLoadStorage(houseid)
{
	static
	    rows,
	    fields,
		str[32];

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i != rows; i ++) {
		HouseStorage[houseid][i][hItemExists] = true;
		HouseStorage[houseid][i][hItemID] = cache_get_field_int(i, "itemID");
		HouseStorage[houseid][i][hItemModel] = cache_get_field_int(i, "itemModel");
		HouseStorage[houseid][i][hItemQuantity] = cache_get_field_int(i, "itemQuantity");

		cache_get_field_content(i, "itemName", str, g_iHandle, sizeof(str));
		strpack(HouseStorage[houseid][i][hItemName], str, 32 char);
	}
	return 1;
}

function OnLoadBackpack(id)
{
	static
	    rows,
	    fields,
		itemid = -1;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i != rows; i ++) if ((itemid = Backpack_GetFreeItem()) != -1) {
		BackpackItems[itemid][bItemExists] = true;
		BackpackItems[itemid][bItemBackpack] = id;
		BackpackItems[itemid][bItemID] = cache_get_field_int(i, "itemID");
		BackpackItems[itemid][bItemModel] = cache_get_field_int(i, "itemModel");
		BackpackItems[itemid][bItemQuantity] = cache_get_field_int(i, "itemQuantity");

		cache_get_field_content(i, "itemName", BackpackItems[itemid][bItemName], g_iHandle, 32);
	}
	return 1;
}

function Pump_Load(bizid)
{
	static
	    rows,
	    fields,
		id = -1;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if ((id = Pump_GetFreeID()) != -1)
	{
	    PumpData[id][pumpExists] = true;
	    PumpData[id][pumpBusiness] = bizid;
	    PumpData[id][pumpID] = cache_get_field_int(i, "pumpID");
	    PumpData[id][pumpPos][0] = cache_get_field_float(i, "pumpPosX");
	    PumpData[id][pumpPos][1] = cache_get_field_float(i, "pumpPosY");
	    PumpData[id][pumpPos][2] = cache_get_field_float(i, "pumpPosZ");
	    PumpData[id][pumpPos][3] = cache_get_field_float(i, "pumpPosA");
	    PumpData[id][pumpFuel] = cache_get_field_int(i, "pumpFuel");

	    PumpData[id][pumpObject] = CreateDynamicObject(1676, PumpData[id][pumpPos][0], PumpData[id][pumpPos][1], PumpData[id][pumpPos][2], 0.0, 0.0, PumpData[id][pumpPos][3]);
	    Pump_Refresh(id);
	}
	return 1;
}

function OpenInventory(playerid)
{
    if (!IsPlayerConnected(playerid) || !PlayerData[playerid][pCharacter])
	    return 0;

	static
	    items[MAX_INVENTORY],
		amounts[MAX_INVENTORY];

    for (new i = 0; i < PlayerData[playerid][pCapacity]; i ++)
	{
 		if (InventoryData[playerid][i][invExists]) {
   			items[i] = InventoryData[playerid][i][invModel];
   			amounts[i] = InventoryData[playerid][i][invQuantity];
		}
		else {
		    items[i] = -1;
		    amounts[i] = -1;
		}
	}
	PlayerData[playerid][pStorageSelect] = 0;
	return ShowModelSelectionMenu(playerid, "Inventory", MODEL_SELECTION_INVENTORY, items, sizeof(items), 0.0, 0.0, 0.0, 1.0, -1, true, amounts);
}

function DragUpdate(playerid, targetid)
{
	if (PlayerData[targetid][pDragged] && PlayerData[targetid][pDraggedBy] == playerid)
	{
	    static
	        Float:fX,
	        Float:fY,
	        Float:fZ,
			Float:fAngle;

		GetPlayerPos(playerid, fX, fY, fZ);
		GetPlayerFacingAngle(playerid, fAngle);

		fX -= 3.0 * floatsin(-fAngle, degrees);
		fY -= 3.0 * floatcos(-fAngle, degrees);

		SetPlayerPos(targetid, fX, fY, fZ);
		SetPlayerInterior(targetid, GetPlayerInterior(playerid));
		SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	}
	return 1;
}

function KickTimer(playerid)
{
	if (PlayerData[playerid][pKicked])
	{
		return Kick(playerid);
	}
	return 0;
}

function OnQueryExecute(playerid, query[])
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	if (strfind(query, "SELECT", true) != -1)
		Dialog_Show(playerid, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Success: MySQL returned %d rows from your query.\n\nPlease specify the MySQL query to execute below:", "Execute", "Back", rows);

	else
		Dialog_Show(playerid, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Success: Query executed successfully (affected rows: %d).\n\nPlease specify the MySQL query to execute below:", "Execute", "Back", cache_affected_rows());

	PlayerData[playerid][pExecute] = 0;
	return 1;
}

function OnQueryFinished(extraid, threadid)
{
	if (!IsPlayerConnected(extraid))
	    return 0;

	static
	    rows,
	    fields
	;
	switch (threadid)
	{
	    case THREAD_CREATE_CHAR:
	    {
	        PlayerData[extraid][pID] = cache_insert_id(g_iHandle);
	        PlayerData[extraid][pLogged] = 1;

			SQL_SaveCharacter(extraid);

			PlayerData[extraid][pID] = -1;
			PlayerData[extraid][pLogged] = 0;
	    }
		case THREAD_FIND_ACCOUNT:
		{
			cache_get_data(rows, fields, g_iHandle);

			if (rows)
			{
				cache_get_field_content(0, "Password", PlayerData[extraid][pPassword], g_iHandle, 120);
				PlayerData[extraid][pPin] = cache_get_field_int(0, "Token");

				new string[128];
				for (new i = 0; i < 28; i ++) 
				{
					TextDrawShowForPlayer(extraid, LOGINTD[i]);
					TextDrawShowForPlayer(extraid, LOGINTDNAME[extraid]);
					format(string, sizeof(string), "%s", ReturnName(extraid, 0)); TextDrawSetString(LOGINTDNAME[extraid], string);
					format(string, 60, "%d", Iter_Count(Player)); TextDrawSetString(LOGINTD[27], string);
				}
				SelectTextDraw(extraid, -1);
			}
			else
			{
				new str[230];
				format(str, sizeof(str), ""WHITE_E"Anda telah ditendang keluar! Perhatian "GREY_E"%s"WHITE_E".\n"WHITE_E"Nama ini tiada rekod mendaftar di SakuraRyzen, sila daftar di discord",
				ReturnName(extraid, 0));
				Dialog_Show(extraid, ShowOnly, DIALOG_STYLE_MSGBOX,"Whitelist", str, "Tutup", "");

				KickEx(extraid);
			}
		}
		case THREAD_CHARACTERS:
		{
			cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows; i ++) {
			    cache_get_field_content(i, "Character", PlayerCharacters[extraid][i], g_iHandle, MAX_PLAYER_NAME);
		    }
            ShowCharacterMenu(extraid);
		}
		case THREAD_LOAD_CHARACTER:
		{
		    static
		        string[128];

		    cache_get_data(rows, fields, g_iHandle);

			foreach (new i : Player)
			{
			    if (PlayerData[i][pCharacter] == PlayerData[extraid][pCharacter] && !strcmp(ReturnName(i), PlayerCharacters[extraid][PlayerData[extraid][pCharacter] - 1]) && i != extraid)
       			{
       			    ShowCharacterMenu(extraid);
				   	SendErrorMessage(extraid, "This character is already logged in.");
				}
			}
			switch (SetPlayerName(extraid, PlayerCharacters[extraid][PlayerData[extraid][pCharacter] - 1]))
			{
			    case -1: {
					SendClientMessageEx(extraid, COLOR_LIGHTRED, "Notice: Your character's name seems to be in use already.");
				}
				default:
				{
				    if (!rows) {
				        return 0;
					}
					static
					    query[128]
					;
			        PlayerData[extraid][pID] = cache_get_field_int(0, "ID");
			        PlayerData[extraid][pCreated] = cache_get_field_int(0, "Created");
			        PlayerData[extraid][pGender] = cache_get_field_int(0, "Gender");  

					cache_get_field_content(0, "Birthdate", PlayerData[extraid][pBirthdate], g_iHandle, 24);
			        cache_get_field_content(0, "Origin", PlayerData[extraid][pOrigin], g_iHandle, 32);
					cache_get_field_content(0, "Character", PlayerData[extraid][pName], g_iHandle, 32);

			        PlayerData[extraid][pSkin] = cache_get_field_int(0, "Skin");
					PlayerData[extraid][pOnDuty] = cache_get_field_int(0, "OnDuty");
					PlayerData[extraid][pFacSkin] = cache_get_field_int(0, "FacSkin"); 
			        PlayerData[extraid][pPos][0] = cache_get_field_float(0, "PosX");
			        PlayerData[extraid][pPos][1] = cache_get_field_float(0, "PosY");
			        PlayerData[extraid][pPos][2] = cache_get_field_float(0, "PosZ");
			        PlayerData[extraid][pPos][3] = cache_get_field_float(0, "PosA");
			        PlayerData[extraid][pHealth] = cache_get_field_float(0, "Health");
			        PlayerData[extraid][pInterior] = cache_get_field_int(0, "Interior");
			        PlayerData[extraid][pWorld] = cache_get_field_int(0, "World");
			        PlayerData[extraid][pMoney] = cache_get_field_int(0, "Money");
			        PlayerData[extraid][pBankMoney] = cache_get_field_int(0, "BankMoney");
					PlayerData[extraid][pSavings] = cache_get_field_int(0, "Savings");
					PlayerData[extraid][pStaterpack] = cache_get_field_int(0, "Staterpack");
			        PlayerData[extraid][pAdmin] = cache_get_field_int(0, "Admin");
			        PlayerData[extraid][pJailTime] = cache_get_field_int(0, "JailTime");
			        PlayerData[extraid][pMuted] = cache_get_field_int(0, "Muted");
			        PlayerData[extraid][pHouse] = cache_get_field_int(0, "House");
			        PlayerData[extraid][pBusiness] = cache_get_field_int(0, "Business");
			        PlayerData[extraid][pEntrance] = cache_get_field_int(0, "Entrance");
			        PlayerData[extraid][pPhone] = cache_get_field_int(0, "Phone");
			        PlayerData[extraid][pLottery] = cache_get_field_int(0, "Lottery");
			        PlayerData[extraid][pLotteryB] = cache_get_field_int(0, "LotteryB"); 
					PlayerData[extraid][pBodyInsurance] = cache_get_field_int(0, "BodyInsurance"); 
					PlayerData[extraid][pUraine] = cache_get_field_int(0, "Uraine");
					PlayerData[extraid][pStress] = cache_get_field_int(0, "Stress");
			        PlayerData[extraid][pHunger] = cache_get_field_int(0, "Hunger");
			        PlayerData[extraid][pThirst] = cache_get_field_int(0, "Thirst");
			        PlayerData[extraid][pScore] = cache_get_field_int(0, "Score");
			        PlayerData[extraid][pMinutes] = cache_get_field_int(0, "Minutes"); 
			        PlayerData[extraid][pArmorStatus] = cache_get_field_float(0, "ArmorStatus");
			        PlayerData[extraid][pJob] = cache_get_field_int(0, "Job");
			        PlayerData[extraid][pFactionID] = cache_get_field_int(0, "Faction");
			        PlayerData[extraid][pFactionRank] = cache_get_field_int(0, "FactionRank");
			        PlayerData[extraid][pPrisoned] = cache_get_field_int(0, "Prisoned");
					PlayerData[extraid][pInjuredTime] = cache_get_field_int(0, "InjuredTime");
			        PlayerData[extraid][pInjured] = cache_get_field_int(0, "Injured");
			        PlayerData[extraid][pWarrants] = cache_get_field_int(0, "Warrants");
			        PlayerData[extraid][pChannel] = cache_get_field_int(0, "Channel");
			        PlayerData[extraid][pAdminHide] = cache_get_field_int(0, "AdminHide");
			        PlayerData[extraid][pWarnings] = cache_get_field_int(0, "Warnings");
			        PlayerData[extraid][pMaskID] = cache_get_field_int(0, "MaskID");
			        PlayerData[extraid][pFactionMod] = cache_get_field_int(0, "FactionMod");
			        PlayerData[extraid][pCapacity] = cache_get_field_int(0, "Capacity");
			        PlayerData[extraid][pSpawnPoint] = cache_get_field_int(0, "SpawnPoint");
					PlayerData[extraid][pLastLogin] = cache_get_field_int(0, "LastLogin");

					cache_get_field_content(0, "Warn1", PlayerData[extraid][pWarn1], g_iHandle, 32);
					cache_get_field_content(0, "Warn2", PlayerData[extraid][pWarn2], g_iHandle, 32);

			        for (new i = 0; i < 13; i ++) {
			            format(query, sizeof(query), "Gun%d", i + 1);
			            PlayerData[extraid][pGuns][i] = cache_get_field_int(0, query);

			            format(query, sizeof(query), "Ammo%d", i + 1);
			            PlayerData[extraid][pAmmo][i] = cache_get_field_int(0, query);
			        }
			        PlayerData[extraid][pGlasses] = cache_get_field_int(0, "Glasses");
					PlayerData[extraid][pHat] = cache_get_field_int(0, "Hat");
					PlayerData[extraid][pBandana] = cache_get_field_int(0, "Bandana");

					cache_get_field_content(0, "GlassesPos", string, g_iHandle);
					sscanf(string, "p<|>fffffffff", AccessoryData[extraid][0][0], AccessoryData[extraid][0][1], AccessoryData[extraid][0][2], AccessoryData[extraid][0][3], AccessoryData[extraid][0][4], AccessoryData[extraid][0][5], AccessoryData[extraid][0][6], AccessoryData[extraid][0][7], AccessoryData[extraid][0][8]);

					cache_get_field_content(0, "HatPos", string, g_iHandle);
					sscanf(string, "p<|>fffffffff", AccessoryData[extraid][1][0], AccessoryData[extraid][1][1], AccessoryData[extraid][1][2], AccessoryData[extraid][1][3], AccessoryData[extraid][1][4], AccessoryData[extraid][1][5], AccessoryData[extraid][1][6], AccessoryData[extraid][1][7], AccessoryData[extraid][1][8]);

					cache_get_field_content(0, "BandanaPos", string, g_iHandle);
					sscanf(string, "p<|>fffffffff", AccessoryData[extraid][2][0], AccessoryData[extraid][2][1], AccessoryData[extraid][2][2], AccessoryData[extraid][2][3], AccessoryData[extraid][2][4], AccessoryData[extraid][2][5], AccessoryData[extraid][2][6], AccessoryData[extraid][2][7], AccessoryData[extraid][2][8]);

					if (!PlayerData[extraid][pMaskID])
					    PlayerData[extraid][pMaskID] = random(90000) + 10000;

					if (!PlayerData[extraid][pCapacity])
					    PlayerData[extraid][pCapacity] = 35;

					ClearChat(extraid);

					SendServerMessage(extraid, "Selamat kembali ke "RED_E"Sakura Ryzen"WHITE_E"! Anda terakhir log masuk pada "BLUE_E"%s"WHITE_E".", ReturnDateTimestamp(PlayerData[extraid][pLastLogin]));
					SendServerMessage(extraid, "Permainan terakhir di kemas kini pada "YELLOW_E"7 Jun 2024"WHITE_E", versi "RED_E"3.7.9-1"WHITE_E".");

					if (PlayerData[extraid][pWarnings] > 0)
				    {
				        SendInfoMessage(extraid, "Anda mempunyai "RED_E"%d"WHITE_E" warning.", PlayerData[extraid][pWarnings]);
				    }

				    if (PlayerData[extraid][pAdmin] > 0)
				    {
				        SendInfoMessage(extraid, "Anda login sebagai admin level "RED_E"%d"WHITE_E".", PlayerData[extraid][pAdmin]);
						new code = RandomEx(1111, 9999);
						PlayerData[extraid][pAdminCode] = code;
						SendInfoMessage(extraid, "Kod admin anda: "YELLOW_E"%d"WHITE_E".", PlayerData[extraid][pAdminCode]);
				    }
				    PlayerData[extraid][pLogged] = 1;

                    format(query, sizeof(query), "SELECT * FROM `inventory` WHERE `ID` = '%d'", PlayerData[extraid][pID]);
					mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_INVENTORY);

                    format(query, sizeof(query), "SELECT * FROM `contacts` WHERE `ID` = '%d'", PlayerData[extraid][pID]);
					mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_CONTACTS);

                    format(query, sizeof(query), "SELECT * FROM `tickets` WHERE `ID` = '%d'", PlayerData[extraid][pID]);
					mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_TICKETS);

                    format(query, sizeof(query), "SELECT * FROM `gps` WHERE `ID` = '%d'", PlayerData[extraid][pID]);
					mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_LOCATIONS);

					format(query, sizeof(query), "SELECT * FROM `cars` WHERE `carOwner` = '%d'", PlayerData[extraid][pID]);
					mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_LOAD_CAR);

					if (PlayerData[extraid][pFactionID] != -1) {
					    PlayerData[extraid][pFaction] = GetFactionByID(PlayerData[extraid][pFactionID]);

					    if (PlayerData[extraid][pFaction] == -1) {
					        ResetFaction(extraid);
						}
					}
				    if (!PlayerData[extraid][pCreated])
				    {
						Dialog_Show(extraid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");

						PlayerData[extraid][pSkin] = 98;

						PlayerData[extraid][pOrigin][0] = '\0';
						PlayerData[extraid][pBirthdate][0] = '\0';

						SendInfoMessage(extraid, "Sila tetapkan butiran watak anda.");
				    }
				    else
				    {
        				SetSpawnInfo(extraid, 0, PlayerData[extraid][pSkin], PlayerData[extraid][pPos][0], PlayerData[extraid][pPos][1], PlayerData[extraid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);

				        TogglePlayerSpectating(extraid, 0);
				        TogglePlayerControllable(extraid, 0);

				        SetTimerEx("UnfreezeTimer", 5000, false, "d", extraid);
					}
				}
			}
		}
		case THREAD_LOAD_INVENTORY:
		{
		    static
		        name[32];

		    cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows && i < MAX_INVENTORY; i ++) {
			    InventoryData[extraid][i][invExists] = true;
			    InventoryData[extraid][i][invID] = cache_get_field_int(i, "invID");
			    InventoryData[extraid][i][invModel] = cache_get_field_int(i, "invModel");
                InventoryData[extraid][i][invQuantity] = cache_get_field_int(i, "invQuantity");

				cache_get_field_content(i, "invItem", name, g_iHandle, sizeof(name));
				strpack(InventoryData[extraid][i][invItem], name, 32 char);
			}
		}
		case THREAD_LOAD_CONTACTS:
		{
		    cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows && i < MAX_CONTACTS; i ++) {
				cache_get_field_content(i, "contactName", ContactData[extraid][i][contactName], g_iHandle, 32);

				ContactData[extraid][i][contactExists] = true;
			    ContactData[extraid][i][contactID] = cache_get_field_int(i, "contactID");
			    ContactData[extraid][i][contactNumber] = cache_get_field_int(i, "contactNumber");
			}
		}
		case THREAD_LOAD_CAR:
		{
			static str[500];

			cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows && i < MAX_DYNAMIC_CARS; i ++) {
				CarData[i][carExists] = true;
				CarData[i][carID] = cache_get_field_int(i, "carID");
				CarData[i][carModel] = cache_get_field_int(i, "carModel");
				CarData[i][carOwner] = cache_get_field_int(i, "carOwner");
				cache_get_field_content(i, "carPlate", CarData[i][carPlate], g_iHandle, 24);
				CarData[i][carHealth] = cache_get_field_float(i, "carHealth");
				CarData[i][carFuel] = cache_get_field_int(i, "carFuel");
				CarData[i][carSiren] = cache_get_field_int(i, "carSiren");
				CarData[i][carGov] = cache_get_field_int(i, "carGov");
				CarData[i][carPos][0] = cache_get_field_float(i, "carPosX");
				CarData[i][carPos][1] = cache_get_field_float(i, "carPosY");
				CarData[i][carPos][2] = cache_get_field_float(i, "carPosZ");
				CarData[i][carPos][3] = cache_get_field_float(i, "carPosR");
				CarData[i][carColor1] = cache_get_field_int(i, "carColor1");
				CarData[i][carColor2] = cache_get_field_int(i, "carColor2");
				CarData[i][carPaintjob] = cache_get_field_int(i, "carPaintjob");
				CarData[i][carLocked] = cache_get_field_int(i, "carLocked");
				CarData[i][carRent] = cache_get_field_int(i, "carRent");
				CarData[i][carImpounded] = cache_get_field_int(i, "carImpounded");
				CarData[i][carImpoundPrice] = cache_get_field_int(i, "carImpoundPrice");
				CarData[i][carTemperature] = cache_get_field_int(i, "carTemperature");

				for (new j = 0; j < 14; j ++)
				{
					if (j < 5)
					{
						format(str, sizeof(str), "carWeapon%d", j + 1);
						CarData[i][carWeapons][j] = cache_get_field_int(i, str);

						format(str, sizeof(str), "carAmmo%d", j + 1);
						CarData[i][carAmmo][j] = cache_get_field_int(i, str);
					}
					format(str, sizeof(str), "carMod%d", j + 1);
					CarData[i][carMods][j] = cache_get_field_int(i, str);
				}

				if (CarData[i][carImpounded] == 1) {
					CarData[i][carVehicle] = 0;
				}
				else {
					Car_Spawn(i);
				}

			}
			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) if (CarData[i][carExists]) {
				format(str, sizeof(str), "SELECT * FROM `carstorage` WHERE `ID` = '%d'", CarData[i][carID]);

				mysql_tquery(g_iHandle, str, "OnLoadCarStorage", "d", i);
			}
		}
		case THREAD_LOAD_LOCATIONS:
		{
		    cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows && i < MAX_GPS_LOCATIONS; i ++) {
				cache_get_field_content(i, "locationName", LocationData[extraid][i][locationName], g_iHandle, 32);

				LocationData[extraid][i][locationExists] = true;
			    LocationData[extraid][i][locationID] = cache_get_field_int(i, "locationID");
			    LocationData[extraid][i][locationPos][0] = cache_get_field_float(i, "locationX");
			    LocationData[extraid][i][locationPos][1] = cache_get_field_float(i, "locationY");
			    LocationData[extraid][i][locationPos][2] = cache_get_field_float(i, "locationZ");
			}
		}
		case THREAD_LOAD_TICKETS:
		{
		    cache_get_data(rows, fields, g_iHandle);

			for (new i = 0; i < rows && i < MAX_PLAYER_TICKETS; i ++) {
				cache_get_field_content(i, "ticketReason", TicketData[extraid][i][ticketReason], g_iHandle, 64);
				cache_get_field_content(i, "ticketDate", TicketData[extraid][i][ticketDate], g_iHandle, 36);

				TicketData[extraid][i][ticketExists] = true;
			    TicketData[extraid][i][ticketID] = cache_get_field_int(i, "ticketID");
				TicketData[extraid][i][ticketFaction] = cache_get_field_int(i, "ticketFaction");
			    TicketData[extraid][i][ticketFee] = cache_get_field_int(i, "ticketFee");
			}
		}
		case THREAD_BAN_LOOKUP:
		{
		    new
		        reason[128],
				date[36],
				username[24],
				admin[24];

		    cache_get_data(rows, fields, g_iHandle);

		    if (rows) 
			{
		        cache_get_field_content(0, "BannedBy", admin, g_iHandle);
				cache_get_field_content(0, "Username", username, g_iHandle);
		        cache_get_field_content(0, "Date", date, g_iHandle);
				cache_get_field_content(0, "Reason", reason, g_iHandle);

				if (!strcmp(username, "null", true) || !username[0])
				{
					new str[500];
					format(str, sizeof(str), ""RED_E"Anda telah disenarai hitam!\n\n"SBLUE_E"Informasi Ban:\n"RED_E"Nama: "GREY_E"NULL\n"RED_E"IP: "GREY_E"************\n"RED_E"Admin: "GREY_E"%s\n"RED_E"Tarikh Ban: "GREY_E"%s\n"RED_E"Sebab Ban: "GREY_E"%s\n"RED_E"Masa Ban: "GREY_E"Kekal\n\n"WHITE_E"Jika ini adalah bug, sila pm admin di discord SakuraRyzen",
					admin, date, reason);
					Dialog_Show(extraid, ShowOnly, DIALOG_STYLE_MSGBOX,"Banned", str, "Tutup", "");

				    KickEx(extraid);
				}
				else
				{
					new str[500];
					format(str, sizeof(str), ""RED_E"Anda telah disenarai hitam!\n\n"SBLUE_E"Informasi Ban:\n"RED_E"Nama: "GREY_E"%s\n"RED_E"IP: "GREY_E"NULL\n"RED_E"Admin: "GREY_E"%s\n"RED_E"Tarikh Ban: "GREY_E"%s\n"RED_E"Sebab Ban: "GREY_E"%s\n"RED_E"Masa Ban: "GREY_E"Kekal\n\n"WHITE_E"Jika ini adalah bug, sila pm admin di discord SakuraRyzen",
					username, admin, date, reason);
					Dialog_Show(extraid, ShowOnly, DIALOG_STYLE_MSGBOX,"Banned", str, "Tutup", "");
				    KickEx(extraid);
				}
		    }
		}
	}
	return 1;
}

function OnViewCharges(extraid, name[])
{
	if (GetFactionType(extraid) != FACTION_POLICE)
	    return 0;

	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	if (!rows)
	    return SendErrorMessage(extraid, "No results found for charges on \"%s\".", name);

	static
	    string[1024],
		desc[128],
		date[36];

	string[0] = 0;

	for (new i = 0; i < rows; i ++) {
	    cache_get_field_content(i, "Description", desc, g_iHandle);
	    cache_get_field_content(i, "Date", date, g_iHandle);

	    format(string, sizeof(string), "%s%s (%s)\n", string, desc, date);
	}
	format(desc, sizeof(desc), "Charges: %s", name);
	Dialog_Show(extraid, ChargeList, DIALOG_STYLE_LIST, desc, string, "Close", "");
	return 1;
}

function OnResolveUsername(extraid, character[])
{
    new
		rows,
		fields,
		name[24];

	cache_get_data(rows, fields, g_iHandle);

	if (!rows)
 		return SendErrorMessage(extraid, "There is no account linked with the specified name.");

	cache_get_row(0, 0, name, g_iHandle);
	SendServerMessage(extraid, "%s's account username is: %s.", character, name);

	return 1;
}

function OnLoginDate(extraid, username[])
{
    if (!IsPlayerConnected(extraid))
	    return 0;

	static
	    rows,
	    fields,
	    date[36];

	cache_get_data(rows, fields, g_iHandle);

	if (rows) {
	    cache_get_row(0, 0, date, g_iHandle);

	    SendServerMessage(extraid, "%s's last login was on: %s.", username, date);
	}
	else {
	    SendErrorMessage(extraid, "Invalid username specified.");
	}
	return 1;
}

function OnCarStorageAdd(carid, itemid)
{
	CarStorage[carid][itemid][cItemID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnStorageAdd(houseid, itemid)
{
	HouseStorage[houseid][itemid][hItemID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnDealerCarCreated(bizid, slotid)
{
	DealershipCars[bizid][slotid][vehID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnFurnitureCreated(furnitureid)
{
	FurnitureData[furnitureid][furnitureID] = cache_insert_id(g_iHandle);
	Furniture_Save(furnitureid);
	return 1;
}

function OnContactAdd(playerid, id)
{
	ContactData[playerid][id][contactID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnInventoryAdd(playerid, itemid)
{
	InventoryData[playerid][itemid][invID] = cache_insert_id(g_iHandle);
	return 1;
}


function OnBanLookup(playerid, username[])
{
	if (!IsPlayerConnected(playerid))
	    return 0;

	static
	    rows,
	    fields,
	    reason[128],
	    date[36];

	cache_get_data(rows, fields, g_iHandle);

	if (rows) {
	    cache_get_field_content(0, "Reason", reason, g_iHandle);
	    cache_get_field_content(0, "Date", date, g_iHandle);

		SendServerMessage(playerid, "%s was banned on %s, reason: %s", username, date, reason);
	}
	else {
	    SendErrorMessage(playerid, "%s is not banned from this server.", username);
	}
	return 1;
}

function OnDeleteAccount(playerid, name[])
{
	static
	    rows,
	    fields,
		id = -1;

	cache_get_data(rows, fields, g_iHandle);

	if (!rows)
	    return SendErrorMessage(playerid, "The username \"%s\" doesn't exist.", name);

	static
	    query[128];

	for (new i = 0; i < rows; i ++)
	{
	    if ((id = cache_get_field_int(i, "ID")))
		{
	        format(query, sizeof(query), "DELETE FROM `contacts` WHERE `ID` = '%d'", id);
	        mysql_tquery(g_iHandle, query);

	        format(query, sizeof(query), "DELETE FROM `gps` WHERE `ID` = '%d'", id);
	        mysql_tquery(g_iHandle, query);

	        format(query, sizeof(query), "DELETE FROM `inventory` WHERE `ID` = '%d'", id);
	        mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `tickets` WHERE `ID` = '%d'", id);
	        mysql_tquery(g_iHandle, query);

			format(query, sizeof(query), "DELETE FROM `cars` WHERE `carOwner` = '%d'", id);
	        mysql_tquery(g_iHandle, query);
		}
	}
	format(query, sizeof(query), "DELETE FROM `accounts` WHERE `Username` = '%s'", name);
    mysql_tquery(g_iHandle, query);

    format(query, sizeof(query), "DELETE FROM `characters` WHERE `Username` = '%s'", name);
    mysql_tquery(g_iHandle, query);

    SendServerMessage(playerid, "You have deleted \"%s\" from the database.", name);
    return 1;
}

function OnNameChange(playerid, userid, newname[])
{
	if (!IsPlayerConnected(playerid) || !IsPlayerConnected(userid))
	    return 0;

	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	if (rows)
	    return SendErrorMessage(playerid, "The specified name \"%s\" is in use.", newname);

    new
		oldname[MAX_PLAYER_NAME];

	GetPlayerName(userid, oldname, sizeof(oldname));
	ChangeName(userid, newname);

    for (new i = 0, l = strlen(oldname); i != l; i ++) {
	    if (oldname[i] == '_') oldname[i] = ' ';
	}
	for (new i = 0, l = strlen(newname); i != l; i ++) {
	    if (newname[i] == '_') newname[i] = ' ';
	}
	SendServerMessage(playerid, "You have changed %s's name to %s.", oldname, newname);
	SendServerMessage(userid, "%s has changed your name to %s.", ReturnName(playerid, 0), newname);

	Log_Write("logs/name_log.txt", "[%s] %s has changed %s's name to %s.", ReturnDate(), ReturnName(playerid), oldname, newname);
	return 1;
}

function OnTicketCreated(playerid, ticketid)
{
	TicketData[playerid][ticketid][ticketID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnRackCreated(rackid)
{
	if (rackid == -1 || !RackData[rackid][rackExists])
	    return 0;

	RackData[rackid][rackID] = cache_insert_id(g_iHandle);
	Rack_Save(rackid);

	return 1;
}

function OnGateCreated(gateid)
{
	if (gateid == -1 || !GateData[gateid][gateExists])
	    return 0;

	GateData[gateid][gateID] = cache_insert_id(g_iHandle);
	Gate_Save(gateid);

	return 1;
}

function OnBusinessCreated(bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	BusinessData[bizid][bizID] = cache_insert_id(g_iHandle);
	Business_Save(bizid);

	return 1;
}

function OnEntranceCreated(entranceid)
{
	if (entranceid == -1 || !EntranceData[entranceid][entranceExists])
	    return 0;

	EntranceData[entranceid][entranceID] = cache_insert_id(g_iHandle);
	EntranceData[entranceid][entranceWorld] = EntranceData[entranceid][entranceID] + 7000;

	Entrance_Save(entranceid);

	return 1;
}

function OnCarCreated(carid)
{
	if (carid == -1 || !CarData[carid][carExists])
	    return 0;

	CarData[carid][carID] = cache_insert_id(g_iHandle);
	Car_Save(carid);

	return 1;
}

function OnPumpCreated(pumpid)
{
    PumpData[pumpid][pumpID] = cache_insert_id(g_iHandle);
	Pump_Save(pumpid);

	return 1;
}

function OnPlantCreated(plantid)
{
	if (plantid == -1 || !PlantData[plantid][plantExists])
	    return 0;

	PlantData[plantid][plantID] = cache_insert_id(g_iHandle);
	Plant_Save(plantid);

	return 1;
}

function OnCrateCreated(crateid)
{
	if (crateid == -1 || !CrateData[crateid][crateExists])
	    return 0;

	CrateData[crateid][crateID] = cache_insert_id(g_iHandle);
	Crate_Save(crateid);

	return 1;
}

function OnFactionCreated(factionid)
{
	if (factionid == -1 || !FactionData[factionid][factionExists])
	    return 0;

	FactionData[factionid][factionID] = cache_insert_id(g_iHandle);

	Faction_Save(factionid);
	Faction_SaveRanks(factionid);

	return 1;
}

function OnBackpackCreated(id)
{
	if (id == -1 || !BackpackData[id][backpackExists])
	    return 0;

	BackpackData[id][backpackID] = cache_insert_id(g_iHandle);
	Backpack_Save(id);

	return 1;
}

function OnATMCreated(atmid)
{
    if (atmid == -1 || !ATMData[atmid][atmExists])
		return 0;

	ATMData[atmid][atmID] = cache_insert_id(g_iHandle);
 	ATM_Save(atmid);

	return 1;
}

function OnGraffitiCreated(id)
{
	GraffitiData[id][graffitiID] = cache_insert_id(g_iHandle);
	Graffiti_Save(id);

	return 1;
}


function OnGarbageCreated(garbageid)
{
	if (garbageid == -1 || !GarbageData[garbageid][garbageExists])
	    return 0;

	GarbageData[garbageid][garbageID] = cache_insert_id(g_iHandle);
	Garbage_Save(garbageid);

	return 1;
}

function OnVendorCreated(vendorid)
{
	if (vendorid == -1 || !VendorData[vendorid][vendorExists])
	    return 0;

	VendorData[vendorid][vendorID] = cache_insert_id(g_iHandle);
	Vendor_Save(vendorid);

	return 1;
}

function OnSpeedCreated(speedid)
{
	if (speedid == -1 || !SpeedData[speedid][speedExists])
	    return 0;

	SpeedData[speedid][speedID] = cache_insert_id(g_iHandle);
	Speed_Save(speedid);

	return 1;
}

function OnHouseCreated(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	HouseData[houseid][houseID] = cache_insert_id(g_iHandle);
	House_Save(houseid);

	return 1;
}

function OnDroppedItem(itemid)
{
	if (itemid == -1 || !DroppedItems[itemid][droppedModel])
	    return 0;

	DroppedItems[itemid][droppedID] = cache_insert_id(g_iHandle);
	return 1;
}

function OnJobCreated(jobid)
{
	if (jobid == -1 || !JobData[jobid][jobExists])
	    return 0;

	JobData[jobid][jobID] = cache_insert_id(g_iHandle);
	Job_Save(jobid);

	return 1;
}

function OnCharacterCheck(extraid, character[])
{
	if (!IsPlayerConnected(extraid))
	    return 0;

	static
	    rows,
	    fields,
		query[150];

	cache_get_data(rows, fields, g_iHandle);

	if (rows)
	{
		Dialog_Show(extraid, CreateChar, DIALOG_STYLE_INPUT, "Buat Watak", "Ralat: Nama yang dimasukkan \"%s\" telah digunakan!\n\nSila masukkan nama watak baharu anda di bawah:\n\nAmaran: Nama anda mestilah dalam format Firstname_Lastname dan tidak melebihi 20 aksara.", "Buat", "Batal", character);
	}
	else
	{
		format(query, sizeof(query), "INSERT INTO `characters` (`Username`, `Character`, `CreateDate`) VALUES('%s', '%s', '%d')", PlayerData[extraid][pUsername], character, gettime());
		mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", extraid, THREAD_CREATE_CHAR);

		format(PlayerCharacters[extraid][PlayerData[extraid][pCharacter] - 1], MAX_PLAYER_NAME + 1, character);
		SendServerMessage(extraid, "Anda telah berjaya mencipta watak "YELLOW_E"%s"WHITE_E"!", character);

		ShowCharacterMenu(extraid);
		PlayerData[extraid][pLogged] = 0;
	}
	return 1;
}

function FlashShowTextDrawEx(playerid, PlayerText:textid, amount)
{
    if ((IsPlayerConnected(playerid) && PlayerData[playerid][pLogged] && PlayerData[playerid][pCharacter] != 0) && IsPlayerSpawned(playerid)) {
	    PlayerTextDrawShow(playerid, textid);

	    if (amount > 0) return SetTimerEx("HideTextDrawEx", 500, false, "ddd", playerid, _:textid, amount);
	}
	return 1;
}

function SQL_CheckAccount(playerid)
{
	new
	    query[128];

    format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Username` = '%s'", ReturnName(playerid));
	mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", playerid, THREAD_FIND_ACCOUNT);
	return 1; 
}

function HideTextDrawEx(playerid, PlayerText:textid, amount)
{
    if ((IsPlayerConnected(playerid) && PlayerData[playerid][pLogged] && PlayerData[playerid][pCharacter] != 0) && IsPlayerSpawned(playerid)) {
	    PlayerTextDrawHide(playerid, textid);

	    if (amount > 0) return SetTimerEx("FlashShowTextDrawEx", 500, false, "ddd", playerid, _:textid, --amount);
	}
	return 1;
}

function FlashShowTextDraw(playerid, PlayerText:textid)
{
	if ((IsPlayerConnected(playerid) && PlayerData[playerid][pLogged] && PlayerData[playerid][pCharacter] != 0) && IsPlayerSpawned(playerid)) {
	    PlayerTextDrawShow(playerid, textid);
	}
	return 1;
}

function OnPlayerUseItem(playerid, itemid, name[])
{
    if (IsFurnitureItem(name))
	{
        new id = House_Inside(playerid);

        if (id == -1)
            return SendErrorMessage(playerid, "You must be inside a house to place furniture.");

		if (!House_IsOwner(playerid, id))
		    return SendErrorMessage(playerid, "You can only place furniture in your own house.");

		static
		    Float:x,
		    Float:y,
		    Float:z,
		    Float:angle;

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        x += 5.0 * floatsin(-angle, degrees);
        y += 5.0 * floatcos(-angle, degrees);

		if (Furniture_GetCount(id) > MAX_HOUSE_FURNITURE)
		    return SendErrorMessage(playerid, "You can only have %d furniture items in your house.", MAX_HOUSE_FURNITURE);

		new furniture = Furniture_Add(id, name, InventoryData[playerid][itemid][invModel], x, y, z, 0.0, 0.0, angle);

		if (furniture == -1)
		    return SendErrorMessage(playerid, "The server has reached the furniture limit.");

		Inventory_Remove(playerid, name);
		PlayerData[playerid][pEditFurniture] = furniture;

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deployed their \"%s\".", ReturnName(playerid, 0), name);
		EditDynamicObject(playerid, FurnitureData[furniture][furnitureObject]);
	}
	else if (!strcmp(name, "Boombox", true)) {
	    cmd_boombox(playerid, "place");
	}
	else if (!strcmp(name, "Backpack", true)) {
	    Backpack_Open(playerid);
	}
	else if (!strcmp(name, "First Aid", true)) {
        if (PlayerData[playerid][pFirstAid])
			return SendErrorMessage(playerid, "You are already using a first aid kit.");

		if (ReturnHealth(playerid) > 99)
			return SendErrorMessage(playerid, "You don't need to use a first aid kit right now.");

		if (!IsPlayerInAnyVehicle(playerid))
			ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

		PlayerData[playerid][pFirstAid] = true;
		PlayerData[playerid][pAidTimer] = SetTimerEx("FirstAidUpdate", 1000, true, "d", playerid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens a first aid kit and uses it.", ReturnName(playerid, 0));
		Inventory_Remove(playerid, "First Aid");

		SendServerMessage(playerid, "You have used a first aid kit!");
    }
    else if (!strcmp(name, "Cellphone", true)) {
        Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
    }
    else if (!strcmp(name, "Portable Radio", true)) {
        SendUsageMessage(playerid, "Use \"/r [text]\" to chat with your radio.");
    }
    else if (!strcmp(name, "Fuel Can", true)) {
        new vehicleid = GetNearestVehicle(playerid);
		new id = Car_GetID(vehicleid);

		if (IsPlayerInAnyVehicle(playerid) || vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You are not standing near any vehicle.");

		if (GetEngineStatus(vehicleid))
			return SendErrorMessage(playerid, "You must shut off the engine first.");
		
		if (id != -1)
		{
			if (CarData[id][carFuel] > 95)
				return SendErrorMessage(playerid, "This vehicle doesn't need any fuel.");
		}

		if (PlayerData[playerid][pFuelCan])
			return SendErrorMessage(playerid, "You are already using a can of fuel.");

		PlayerData[playerid][pFuelCan] = 1;

		Inventory_Remove(playerid, "Fuel Can");
		GameTextForPlayer(playerid, "~r~Filling vehicle...", 5200, 3);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens a can of fuel and fills the vehicle.", ReturnName(playerid, 0));
		SetTimerEx("RefillUpdate", 5000, false, "dd", playerid, vehicleid);
    }
    else if (!strcmp(name, "Repair Kit", true)) {
        cmd_repair(playerid, "\1");
    }
    else if (!strcmp(name, "GPS System", true)) {
        cmd_gps(playerid, "\1");
    }
    else if (!strcmp(name, "Marijuana", true)) {
        cmd_usedrug(playerid, "marijuana");
    }
    else if (!strcmp(name, "Cocaine", true)) {
        cmd_usedrug(playerid, "cocaine");
    }
    else if (!strcmp(name, "Heroin", true)) {
        cmd_usedrug(playerid, "heroin");
    }
    else if (!strcmp(name, "Steroids", true)) {
        cmd_usedrug(playerid, "steroids");
    }
    else if (!strcmp(name, "Frozen Pizza", true)) {
        cmd_cook(playerid, "pizza");
    }
    else if (!strcmp(name, "Frozen Burger", true)) {
        cmd_cook(playerid, "burger");
    }
    else if (!strcmp(name, "Armored Vest", true)) {
        if (ReturnArmour(playerid) > 95)
			return SendErrorMessage(playerid, "You already have a full vest on.");

		SetPlayerArmourEx(playerid, 100.0);

		Inventory_Remove(playerid, "Armored Vest");
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a kevlar vest and puts it on.", ReturnName(playerid, 0));
    }
    else if (!strcmp(name, "Marijuana Seeds", true)) {
        cmd_plant(playerid, "Weed");
    }
    else if (!strcmp(name, "Cocaine Seeds", true)) {
        cmd_plant(playerid, "Cocaine");
    }
    else if (!strcmp(name, "Heroin Opium Seeds", true)) {
        cmd_plant(playerid, "Heroin");
    }
	else if (!strcmp(name, "Water Bottle", true)) {
        
		if (PlayerData[playerid][pThirst] > 90)
	    	return SendErrorMessage(playerid, "You are not thirsty right now.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);

		SetTimerEx("FinishDrinking", 3000, false, "d", playerid);

		PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 15 > 100) ? (100) : (PlayerData[playerid][pThirst] + 15);

		Inventory_Add(playerid, "Empty Bottle", 1484);
		Inventory_Remove(playerid, "Water Bottle");

 		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a water bottle of soda and opens it.", ReturnName(playerid, 0));
    }
	else if (!strcmp(name, "Soda", true)) {
		
		if (PlayerData[playerid][pThirst] > 90)
	    	return SendErrorMessage(playerid, "You are not thirsty right now.");

		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);

		SetTimerEx("FinishDrinking", 3000, false, "d", playerid);

		PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 15 > 100) ? (100) : (PlayerData[playerid][pThirst] + 15);

		Inventory_Add(playerid, "Empty Bottle", 1484);
		Inventory_Remove(playerid, "Soda");

 		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a bottle of soda and opens it.", ReturnName(playerid, 0));
    }
    else if (!strcmp(name, "Cooked Pizza", true))
	{
        if (PlayerData[playerid][pHunger] > 90)
            return SendErrorMessage(playerid, "You are not hungry right now.");

        if (!IsPlayerAttachedObjectSlotUsed(playerid, 4))
		{
		    SetPlayerAttachedObject(playerid, 4, 2702, 6, 0.173041, 0.049197, 0.056789, 0.000000, 274.166107, 299.057983, 1.000000, 1.000000, 1.000000);
			SetTimerEx("RemoveAttachedObject", 3000, false, "dd", playerid, 4);
		}
        PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 15 > 100) ? (100) : (PlayerData[playerid][pHunger] + 15);
		Inventory_Remove(playerid, "Cooked Pizza");

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a slice of pizza and eats it.", ReturnName(playerid, 0));
    }
    else if (!strcmp(name, "Cooked Burger", true))
	{
	    if (PlayerData[playerid][pHunger] > 90)
            return SendErrorMessage(playerid, "You are not hungry right now.");

		if (!IsPlayerAttachedObjectSlotUsed(playerid, 4))
		{
		    SetPlayerAttachedObject(playerid, 4, 2703, 6, 0.078287, 0.019677, -0.001004, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);
			SetTimerEx("RemoveAttachedObject", 3000, false, "dd", playerid, 4);
		}
        PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 20 > 100) ? (100) : (PlayerData[playerid][pHunger] + 20);
		Inventory_Remove(playerid, "Cooked Burger");

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a cooked burger and eats it.", ReturnName(playerid, 0));
    }
    else if (!strcmp(name, "Chicken", true))
	{
	    if (PlayerData[playerid][pHunger] > 90)
            return SendErrorMessage(playerid, "You are not hungry right now.");

        PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 25 > 100) ? (100) : (PlayerData[playerid][pHunger] + 25);
		Inventory_Remove(playerid, "Chicken");

		ApplyAnimation(playerid, "VENDING", "VEND_Eat_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a piece of chicken and eats it.", ReturnName(playerid, 0));
    }
	else if (!strcmp(name, "Cigarette", true))
	{
		if (!Inventory_HasItem(playerid, "Lighter"))
	        return SendErrorMessage(playerid, "You don't have any lighter.");

	    if (PlayerData[playerid][pStress] < 10)
            return SendErrorMessage(playerid, "You are not stress right now.");

		Inventory_Remove(playerid, "Cigarette");
		Inventory_Remove(playerid, "Lighter");

        PlayerData[playerid][pStress] -= 10;

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a cigarette and lighter and start smoke it.", ReturnName(playerid, 0));
		ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
    }
	else if (!strcmp(name, "Alcohol", true))
	{
	    if (PlayerData[playerid][pStress] < 10)
            return SendErrorMessage(playerid, "You are not stress right now.");

		Inventory_Remove(playerid, "Alcohol");

        PlayerData[playerid][pStress] -= 10;

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a alcohol and start drink it.", ReturnName(playerid, 0));
		ApplyAnimationEx(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1, 1);

		PlayerData[playerid][pUraine] = 1;
    }
	else if (!strcmp(name, "Helmet", true))
	{
	    switch(PlayerData[playerid][pHelmet])
		{
			case 0:
			{
				SendClientMessage(playerid, COLOR_WHITE, "HELMET: "GREEN_E"ON");
				ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
				PlayerData[playerid][pHelmet] = 1;
				GivePlayerHelmet(playerid);
			}
			case 1:
			{
				SendClientMessage(playerid, COLOR_WHITE, "HELMET: "RED_E"OFF");
				PlayerData[playerid][pHelmet] = 0;
				ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
				RemovePlayerAttachedObject(playerid, 9);
			}
		}
    }
	// Weapon
	else if (!strcmp(name, "Brass Knuckles", true)) { 
        GivePlayerWeapon(playerid, 1, 10); 
    }
    else if (!strcmp(name, "Golf CLub", true)) { 
        GivePlayerWeapon(playerid, 2, 10); 
    }
    else if (!strcmp(name, "Nightstick", true)) { 
        GivePlayerWeapon(playerid, 3, 10); 
    }
    else if (!strcmp(name, "Knife", true)) { 
        GivePlayerWeapon(playerid, 4, 10); 
    }
    else if (!strcmp(name, "Baseball Bat", true)) { 
        GivePlayerWeapon(playerid, 5, 10); 
    }
    else if (!strcmp(name, "Shovel", true)) { 
        GivePlayerWeapon(playerid, 6, 10); 
    }
    else if (!strcmp(name, "Pool Cue", true)) { 
        GivePlayerWeapon(playerid, 7, 10); 
    }
    else if (!strcmp(name, "Katana", true)) { 
        GivePlayerWeapon(playerid, 8, 10); 
    }
    else if (!strcmp(name, "Chainsaw", true)) { 
        GivePlayerWeapon(playerid, 9, 10); 
    }
    else if (!strcmp(name, "Purple Dildo", true)) { 
        GivePlayerWeapon(playerid, 10, 10); 
    }
    else if (!strcmp(name, "Dildo", true)) { 
        GivePlayerWeapon(playerid, 11, 10); 
    }
    else if (!strcmp(name, "Vibrator", true)) { 
        GivePlayerWeapon(playerid, 12, 10); 
    }
    else if (!strcmp(name, "Silver Vibrator", true)) { 
        GivePlayerWeapon(playerid, 13, 10); 
    }
    else if (!strcmp(name, "Flowers", true)) { 
        GivePlayerWeapon(playerid, 14, 10); 
    }
    else if (!strcmp(name, "Cane", true)) { 
        GivePlayerWeapon(playerid, 15, 10); 
    }
    else if (!strcmp(name, "Grenade", true)) { 
        GivePlayerWeapon(playerid, 16, 10); 
    }
    else if (!strcmp(name, "Tear Gas", true)) { 
        GivePlayerWeapon(playerid, 17, 10); 
    }
    else if (!strcmp(name, "Molotov Cocktail", true)) { 
        GivePlayerWeapon(playerid, 18, 10); 
    }
    else if (!strcmp(name, "9mm", true)) { 
        GivePlayerWeapon(playerid, 22, 10); 
    }
    else if (!strcmp(name, "Silenced 9mm", true)) { 
        GivePlayerWeapon(playerid, 23, 10); 
    }
    else if (!strcmp(name, "Desert Eagle", true)) { 
        GivePlayerWeapon(playerid, 24, 10); 
    }
    else if (!strcmp(name, "Shotgun", true)) { 
        GivePlayerWeapon(playerid, 25, 10); 
    }
    else if (!strcmp(name, "Sawnoff Shotgun", true)) { 
        GivePlayerWeapon(playerid, 26, 10); 
    }
    else if (!strcmp(name, "Combat Shotgun", true)) { 
        GivePlayerWeapon(playerid, 27, 10); 
    }
    else if (!strcmp(name, "Uzi", true)) { 
        GivePlayerWeapon(playerid, 28, 10); 
    }
    else if (!strcmp(name, "MP5", true)) { 
        GivePlayerWeapon(playerid, 29, 10); 
    }
    else if (!strcmp(name, "AK-47", true)) { 
        GivePlayerWeapon(playerid, 30, 10); 
    }
    else if (!strcmp(name, "M4", true)) { 
        GivePlayerWeapon(playerid, 31, 10); 
    }
    else if (!strcmp(name, "Tec-9", true)) { 
        GivePlayerWeapon(playerid, 32, 10); 
    }
    else if (!strcmp(name, "Country Rifle", true)) { 
        GivePlayerWeapon(playerid, 33, 10); 
    }
    else if (!strcmp(name, "Sniper Rifle", true)) { 
        GivePlayerWeapon(playerid, 34, 10); 
    }
    else if (!strcmp(name, "RPG", true)) { 
        GivePlayerWeapon(playerid, 35, 10); 
    }
    else if (!strcmp(name, "HS Rocket", true)) { 
        GivePlayerWeapon(playerid, 36, 10); 
    }
    else if (!strcmp(name, "Flamethrower", true)) { 
        GivePlayerWeapon(playerid, 37, 10); 
    }
    else if (!strcmp(name, "Minigun", true)) { 
        GivePlayerWeapon(playerid, 38, 10); 
    }
    else if (!strcmp(name, "Satchel Charge", true)) { 
        GivePlayerWeapon(playerid, 39, 10); 
    }
    else if (!strcmp(name, "Detonator", true)) { 
        GivePlayerWeapon(playerid, 40, 10); 
    }
    else if (!strcmp(name, "Spraycan", true)) { 
        GivePlayerWeapon(playerid, 41, 10); 
    }
    else if (!strcmp(name, "Fire Extinguisher", true)) { 
        GivePlayerWeapon(playerid, 42, 10); 
    }
    else if (!strcmp(name, "Camera", true)) { 
        GivePlayerWeapon(playerid, 43, 10); 
    }
    else if (!strcmp(name, "Night Vision Goggles", true)) { 
        GivePlayerWeapon(playerid, 44, 10); 
    }
    else if (!strcmp(name, "Thermal Goggles", true)) { 
        GivePlayerWeapon(playerid, 45, 10); 
    }
    else if (!strcmp(name, "Parachute", true)) { 
        GivePlayerWeapon(playerid, 46, 10); 
    }
    return 1;
}

function PutInsideVehicle(playerid, vehicleid)
{
	if (!PlayerData[playerid][pDrivingTest])
	    return 0;

	RemoveFromVehicle(vehicleid);
    PutPlayerInVehicle(playerid, vehicleid, 0);
    return 1;
}


function LotteryUpdate()
{
	new
		number = random(60) + 1,
		jackpot = random(2000) + 1000;

	foreach (new i : Player)
	{
	    if(PlayerData[i][pLotteryB] == 1)
	    {
			if (PlayerData[i][pLottery] == number)
			{
				GiveMoney(i, jackpot);
				SendServerMessage(i, "You have won the lottery jackpot of %s!", FormatNumber(jackpot));
			}
			else
			{
		    	SendServerMessage(i, "You didn't win the lottery draw this time.");
			}
			PlayerData[i][pLottery] = 0;
			PlayerData[i][pLotteryB] = 0;
		}
	}
	return 1;
}

function OnlineTimer()
{
	new datestring[64], timestring[64];
	new hours, days, months, years, minutes, seconds;
	new MonthName[12][] = { "January", "February", "March", "April", "May", "June", "July",	"August", "September", "October", "November", "December" };

	getdate(years, months, days);
	gettime(hours, minutes, seconds);

	format(timestring, sizeof timestring, "%s%d:%s%d", (hours < 10) ? ("0") : (""), hours, (minutes < 10) ? ("0") : (""), minutes);
	format(datestring, sizeof datestring, "%s%d %s %s%d", ((days < 10) ? ("0") : ("")), days, MonthName[months-1], (years < 10) ? ("0") : (""), years);

	up_seconds ++;
	if(up_seconds == 60)
	{
	    up_seconds = 0, up_minutes ++;
	    if(up_minutes == 60)
	    {
			SendClientMessageToAllEx(COLOR_WHITE, ""BLUE_E"[STATUS]: "WHITE_E"The server has been online for "GREEN_E"%s"WHITE_E".", Uptime());

	        up_minutes = 0, up_hours ++;
	        if(up_hours == 24) up_hours = 0, up_days ++;
		}
	} 
	return 1;
}

function MinuteCheck()
{
	static
	    Float:hp;

    foreach (new i : Player)
	{
	    if (!PlayerData[i][pLogged] && !PlayerData[i][pCharacter])
	        continue;

        PlayerData[i][pMinutes]++;

        if (PlayerData[i][pMinutes] >= 60)
       	{
        	PlayerData[i][pMinutes] = 0;

			PlayerData[i][pScore]++;

         	SendInfoMessage(i, "CHARACTER LEVEL +1");
		}

		if (PlayerData[i][pInjured])
		{
		    GetPlayerHealth(i, hp);
		    SetPlayerHealthEx(i, hp - 10.0);
		}
	}
	for (new i = 0; i != MAX_DRUG_PLANTS; i ++) if (PlantData[i][plantExists] && PlantData[i][plantDrugs] < Plant_MaxGrams(PlantData[i][plantType])) {
	    PlantData[i][plantDrugs]++;

	    Plant_Refresh(i);
	    Plant_Save(i);
	}
	return 1;
}

function VehicleCheck()
{
	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
	{
		if(IsValidVehicle(CarData[i][carVehicle]))
		{
			if(CarData[i][carRent] != 0 && CarData[i][carRent] <= gettime())
			{
				CarData[i][carRent] = 0;
				Car_Delete(i);
			}
		}
	}
	return 1;
}

function PlayerCheck()
{
	static
		str[128],
		Float:health,
		id = -1;

	TotalledCheck();

	foreach (new i : Player)
	{
	    if (!PlayerData[i][pLogged] && !PlayerData[i][pCharacter])
	        continue;
		
		if(PlayerData[i][pAdminDuty] == 0)
		{
			if(GetPlayerState(i) == PLAYER_STATE_ONFOOT)
			{
				switch(GetPlayerAnimationIndex(i))
				{
					case 958, 1538, 1539, 1543:
					{
						new
							Float:z,
							Float:vx,
							Float:vy,
							Float:vz;

						GetPlayerPos(i, z, z, z);
						GetPlayerVelocity(i, vx, vy, vz);

						if((z > 20.0) && (0.9 <= floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) <= 1.9))
						{
							Log_Write("logs/cheat_log.txt", "[%s] %s has possibly flying hacks.", ReturnDate(), ReturnName(i, 0));

							SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(i, 0));
							SendClientMessageToAllEx(COLOR_GREY, "Reason: Flying Hack");

							KickEx(i);
						}
					}
				}
			}
			if (GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK && !PlayerData[i][pJetpack])
			{
				Log_Write("logs/cheat_log.txt", "[%s] %s has spawned a jetpack using hacks.", ReturnDate(), ReturnName(i, 0));

				SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(i, 0));
				SendClientMessageToAllEx(COLOR_GREY, "Reason: Jetpact Hack");

				KickEx(i);
			}
			if (GetPlayerSpeed(i) > 300)
			{
				if (!IsAPlane(GetPlayerVehicleID(i)) && GetPlayerState(i) != PLAYER_STATE_PASSENGER)
				{
					Log_Write("logs/cheat_log.txt", "[%s] %s has possibly used speed hacks (%.0f KM/H).", ReturnDate(), ReturnName(i, 0), GetPlayerSpeed(i));

					SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(i, 0));
					SendClientMessageToAllEx(COLOR_GREY, "Reason: Speed Hack");

					KickEx(i);

				}
			}
		}
		if(PlayerData[i][pChannel] == 911 && GetFactionType(i) != FACTION_POLICE)
		{
		    PlayerData[i][pChannel] = 0;
		}
		if (PlayerData[i][pPicking])
		{
			if ((id = PlayerData[i][pPickCar]) != -1)
			{
			    if (Car_Nearest(i) != id)
			    {
			        PlayerData[i][pPicking] = 0;
			        PlayerData[i][pPickCar] = -1;
			        PlayerData[i][pPickTime] = 0;
				}
				else
				{
				    PlayerData[i][pPickTime]++;

				    format(str, sizeof(str), "~w~Picking... %d", 60 - PlayerData[i][pPickTime]);
					GameTextForPlayer(i, str, 1000, 3);

					if (PlayerData[i][pPickTime] >= 60)
					{
                        static
					        engine, lights, alarm, doors, bonnet, boot, objective;

	    				GetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, doors, bonnet, boot, objective);
					    SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 0, bonnet, boot, objective);

                        PlayerData[i][pPicking] = 0;
                        PlayerData[i][pPickCar] = -1;
                        PlayerData[i][pPickTime] = 0;

                        CarData[id][carLocked] = 0;
						Car_Save(id);

					    SendNearbyMessage(i, 30.0, COLOR_PURPLE, "** %s has picked the lock of the vehicle.", ReturnName(i, 0));
					    SendServerMessage(i, "You have unlocked the vehicle!");
					}
				}
		    }
		}
		else if (PlayerData[i][pMuted] && PlayerData[i][pMuteTime] > 0)
		{
		    PlayerData[i][pMuteTime]--;

		    if (!PlayerData[i][pMuteTime])
		    {
				PlayerData[i][pMuted] = 0;
				PlayerData[i][pMuteTime] = 0;
		    }
		}
		else if (PlayerData[i][pGraffiti] != -1 && PlayerData[i][pGraffitiTime] > 0)
		{
			if (Graffiti_Nearest(i) != PlayerData[i][pGraffiti])
			{
			    PlayerData[i][pGraffiti] = -1;
                PlayerData[i][pGraffitiTime] = 0;
			}
			else
			{
	            PlayerData[i][pGraffitiTime]--;

	            if (PlayerData[i][pGraffitiTime] < 1)
				{
				    strunpack(str, PlayerData[i][pGraffitiText]);
	                format(GraffitiData[PlayerData[i][pGraffiti]][graffitiText], 64, str);

				    GraffitiData[PlayerData[i][pGraffiti]][graffitiColor] = PlayerData[i][pGraffitiColor];

					Graffiti_Refresh(PlayerData[i][pGraffiti]);
				    Graffiti_Save(PlayerData[i][pGraffiti]);

				    ClearAnimations(i, 1);
					SendNearbyMessage(i, 30.0, COLOR_PURPLE, "** %s puts their can of spray paint away.", ReturnName(i, 0));

	                PlayerData[i][pGraffiti] = -1;
	                PlayerData[i][pGraffitiTime] = 0;
				}
			}
		}
		else if (PlayerData[i][pSpamCount] > 0)
		{
		    PlayerData[i][pSpamCount]--;
		}
		else if (PlayerData[i][pCommandCount] > 0)
		{
		    PlayerData[i][pCommandCount]--;
		}
		else if (PlayerData[i][pVendorTime] > 0)
		{
		    PlayerData[i][pVendorTime]--;
		}
		else if (PlayerData[i][pDrinkTime] > 0)
		{
		    PlayerData[i][pDrinkTime]--;
		}
		else if (PlayerData[i][pAdTime] > 0)
		{
		    PlayerData[i][pAdTime]--;
		}
		else if (PlayerData[i][pSpeedTime] > 0)
		{
		    PlayerData[i][pSpeedTime]--;
		}
		else if (PlayerData[i][pFingerTime] > 0)
		{
		    PlayerData[i][pFingerTime]--;

		    if (!PlayerData[i][pFingerTime] && DroppedItems[PlayerData[i][pFingerItem]][droppedModel] && IsPlayerInRangeOfPoint(i, 1.5, DroppedItems[PlayerData[i][pFingerItem]][droppedPos][0], DroppedItems[PlayerData[i][pFingerItem]][droppedPos][1], DroppedItems[PlayerData[i][pFingerItem]][droppedPos][2]))
		    {
		        SendServerMessage(i, "The fingerprint scanner has detected a match: %s.", DroppedItems[PlayerData[i][pFingerItem]][droppedPlayer]);
                PlayerData[i][pFingerItem] = -1;
			}
		}
		else if (PlayerData[i][pDrugUsed] != 0 && PlayerData[i][pDrugTime] > 0)
		{
		    if (--PlayerData[i][pDrugTime] && 1 <= PlayerData[i][pDrugUsed] <= 3 && GetPlayerDrunkLevel(i) < 5000) {
		        SetPlayerDrunkLevel(i, 10000);

				PlayerTextDrawShow(i, DrugTD[i]);

				if (PlayerData[i][pDrugUsed] == 3) {
				    SetPlayerWeather(i, -67);
				    SetPlayerTime(i, 12, 12); // Set the time (the drug weather is buggy at night)
				}
			}
		    if (1 <= PlayerData[i][pDrugUsed] <= 3 && ReturnHealth(i) <= 95) {
		    	SetPlayerHealthEx(i, ReturnHealth(i) + 5);
			}
		    if (!PlayerData[i][pDrugTime])
		    {
		        SetPlayerDrunkLevel(i, 500);
				PlayerTextDrawHide(i, DrugTD[i]);

				PlayerData[i][pDrugUsed] = 0;
		        SendServerMessage(i, "The effects from the drugs have subsided.");
		    }
		}
		else if (PlayerData[i][pStunned] > 0)
		{
            PlayerData[i][pStunned]--;

			if (GetPlayerAnimationIndex(i) != 388)
            	ApplyAnimation(i, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

            if (!PlayerData[i][pStunned])
            {
                TogglePlayerControllable(i, 1);
                SendInfoMessage(i, "You are no longer stunned.");
			}
		}
		else if (PlayerData[i][pJailTime] > 0)
		{
		    static
		        hours,
		        minutes,
		        seconds;

		    PlayerData[i][pJailTime]--;

			GetElapsedTime(PlayerData[i][pJailTime], hours, minutes, seconds);

			format(str, sizeof(str), "~g~Jail Time~n~~w~ %02d:%02d:%02d", hours, minutes, seconds);
			GameTextForPlayer(i, str, 1000, 3); 

		    if (!PlayerData[i][pJailTime])
		    {
		        PlayerData[i][pPrisoned] = 0;

		        SetDefaultSpawn(i);

				SendServerMessage(i, "You have been released from jail.");
			}
		}
		else if (PlayerData[i][pTrackTime] > 0 && IsPlayerConnected(PlayerData[i][pMDCPlayer]) && GetFactionType(i) == FACTION_POLICE)
		{
		    PlayerData[i][pTrackTime]--;

		    if (!PlayerData[i][pTrackTime])
		    {
		        if ((id = House_Inside(PlayerData[i][pMDCPlayer])) != -1)
				{
				    PlayerData[i][pCP] = 1;

				    SetPlayerCheckpoint(i, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], 3.0);
		            SendServerMessage(i, "%s's last reported location was at \"%s\" (marked on radar).", ReturnName(PlayerData[i][pMDCPlayer], 0), HouseData[id][houseAddress]);
		        }
		        else if ((id = Business_Inside(PlayerData[i][pMDCPlayer])) != -1)
		        {
		            PlayerData[i][pCP] = 1;

		            SetPlayerCheckpoint(i, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2], 3.0);
		            SendServerMessage(i, "%s's last reported location was at \"%s\" (marked on radar).", ReturnName(PlayerData[i][pMDCPlayer], 0), BusinessData[id][bizName]);
		        }
		        else if (GetPlayerInterior(PlayerData[i][pMDCPlayer]) == 0)
		        {
		            static
		                Float:fX,
		                Float:fY,
		                Float:fZ;

		            GetPlayerPos(PlayerData[i][pMDCPlayer], fX, fY, fZ);
		            PlayerData[i][pCP] = 1;

                    SetPlayerCheckpoint(i, fX, fY, fZ, 3.0);
		            SendServerMessage(i, "%s's last reported location was at \"%s\" (marked on radar).", ReturnName(PlayerData[i][pMDCPlayer], 0), GetLocation(fX, fY, fZ));
		        }
		        else
		        {
		            SendServerMessage(i, "Unable to locate %s; the target is out of range (inside an interior).", ReturnName(PlayerData[i][pMDCPlayer], 0));
				}
			}
		}
		else if (PlayerData[i][pCooking] && IsPlayerSpawned(i))
		{
		    PlayerData[i][pCookingTime]--;

		    if (House_Inside(i) == PlayerData[i][pCookingHouse])
		    {
			    format(str, sizeof(str), "~b~~h~Cooking...~w~ %d seconds", PlayerData[i][pCookingTime]);
			    GameTextForPlayer(i, str, 1200, 3);
			}
		    if (PlayerData[i][pCookingTime] < 1)
		    {
		        if (House_Inside(i) != PlayerData[i][pCookingHouse])
		        {
		            SendServerMessage(i, "You have left your food unattended and burned it.");
		        }
		        else
				{
					switch (PlayerData[i][pCooking])
		        	{
                    	case 1:
		            	{
		               	    id = Inventory_Add(i, "Cooked Burger", 2703, 1);

		               	    if (id == -1)
		               	        return SendErrorMessage(i, "You don't have any inventory slots left.");

		                	SendNearbyMessage(i, 30.0, COLOR_PURPLE, "** The microwave beeps, you can smell a burger! (( %s ))", ReturnName(i, 0));
		                	SendServerMessage(i, "The cooked burger was added to your inventory.");
		            	}
			            case 2:
			            {
			                id = Inventory_Add(i, "Cooked Pizza", 2702, 6);

			                if (id == -1)
		               	        return SendErrorMessage(i, "You don't have any inventory slots left.");

		    	            SendNearbyMessage(i, 30.0, COLOR_PURPLE, "** The oven beeps, you can smell pizza! (( %s ))", ReturnName(i, 0));
		    	            SendServerMessage(i, "The cooked pizza was added to your inventory.");
		        	    }
					}
				}
                PlayerData[i][pCooking] = 0;
                PlayerData[i][pCookingTime] = 0;
                PlayerData[i][pCookingHouse] = -1;
		    }
		}
		else if (PlayerData[i][pSweeper] && IsPlayerInVehicle(i, PlayerData[i][pSweeperCar])) 
		{
		    if (!IsPlayerInRangeOfPoint(i, 300.0, g_arrSweeperCheckpoints[PlayerData[i][pSweeperCP]][0], g_arrSweeperCheckpoints[PlayerData[i][pSweeperCP]][1], g_arrSweeperCheckpoints[PlayerData[i][pSweeperCP]][2]))
			{
		        DestroyVehicle(PlayerData[i][pSweeperCar]);
  				PlayerData[i][pSweeper] = false;
				PlayerData[i][pSweeperCP] = 0;
				DisablePlayerCheckpoint(i);
				SendInfoMessage(i, "Anda telah gagal menyelesaikan kerja ini kerana anda keluar dari laluan kerja.");
    		}
		}
		else if (PlayerData[i][pKaitKelapa])
		{
		    if (!IsPlayerInRangeOfPoint(i, 100.0, g_arrKaitKelapaCheckpoints[PlayerData[i][pKaitKelapaCP]][0], g_arrKaitKelapaCheckpoints[PlayerData[i][pKaitKelapaCP]][1], g_arrKaitKelapaCheckpoints[PlayerData[i][pKaitKelapaCP]][2]))
			{
  				PlayerData[i][pKaitKelapa] = false;
				PlayerData[i][pKaitKelapaCP] = 0;
				DisablePlayerCheckpoint(i);
				SendInfoMessage(i, "Anda telah gagal menyelesaikan kerja ini kerana anda keluar dari kawasan kerja.");
    		}
		}
		else if (PlayerData[i][pDrivingTest] && IsPlayerInVehicle(i, PlayerData[i][pTestCar]))
		{
		    if (!IsPlayerInRangeOfPoint(i, 100.0, g_arrDrivingCheckpoints[PlayerData[i][pTestStage]][0], g_arrDrivingCheckpoints[PlayerData[i][pTestStage]][1], g_arrDrivingCheckpoints[PlayerData[i][pTestStage]][2]))
			{
		        CancelDrivingTest(i);
				SendInfoMessage(i, "You have failed the test due to leaving the test area.");
    		}
			else if (GetPlayerSpeed(i) >= 55.0)
   			{
				if (++PlayerData[i][pTestWarns] < 3)
				{
    				SendInfoMessage(i, "You are going too fast, slow down! (%d/3)", PlayerData[i][pTestWarns]);
        		}
	       		else
				{
    				CancelDrivingTest(i);
        			SendInfoMessage(i, "You have failed the test due to excessive speeding!");
			    }
			}
		}
		else if (IsPlayerInsideTaxi(i))
		{
		    PlayerData[i][pTaxiTime]++;

		    if (PlayerData[i][pTaxiTime] == 15)
		    {
		        PlayerData[i][pTaxiTime] = 0;
		        PlayerData[i][pTaxiFee] += 10;
		    }
		    format(str, sizeof(str), "~g~%s...~w~ %d seconds", FormatNumber(PlayerData[i][pTaxiFee]), PlayerData[i][pTaxiTime]);

			GameTextForPlayer(i, str, 1100, 3);
			GameTextForPlayer(GetVehicleDriver(GetPlayerVehicleID(i)), str, 1100, 3);
		}
		if (PlayerData[i][pCreated] && !PlayerData[i][pJailTime] && !PlayerData[i][pInjured] && PlayerData[i][pCreated] && IsPlayerSpawned(i))
		{
		    GetPlayerHealth(i, health);

		    if (++ PlayerData[i][pHungerTime] >= 290)
			{
				if (PlayerData[i][pHunger] > 0)
				{
    	        	PlayerData[i][pHunger]--;
    		    }
        		else if (PlayerData[i][pHunger] <= 0)
				{
					SendInfoMessage(i, "Anda telah mula merasa lapar! Sila makan.");
    	        	SetPlayerHealthEx(i, health - 10);
					PlayerData[i][pStress]--;
        		}
        		PlayerData[i][pHungerTime] = 0;
        	}
	        if (++ PlayerData[i][pThirstTime] >= 270)
			{
				if (PlayerData[i][pThirst] > 0)
				{
    	        	PlayerData[i][pThirst]--;
				}
				else if (PlayerData[i][pThirst] <= 0)
				{
					SendInfoMessage(i, "Anda telah mula merasa dahaga! Sila minum.");
		        	SetPlayerHealthEx(i, health - 5);
					PlayerData[i][pStress]--;
        		}
        		PlayerData[i][pThirstTime] = 0;
			}

			if (++ PlayerData[i][pStressTime] >= 280)
			{
				if (PlayerData[i][pStress] < 100)
				{
    	        	PlayerData[i][pStress]++;
				}
				else if (PlayerData[i][pStress] > 95)
				{
					SendInfoMessage(i, "Anda telah mula merasa stres! Sila pergi ke club.");
		        	SetPlayerHealthEx(i, health - 14);
        		}
        		PlayerData[i][pStressTime] = 0;
			}
		}
		if ((id = Boombox_Nearest(i)) != INVALID_PLAYER_ID && PlayerData[i][pBoombox] != id && strlen(BoomboxData[id][boomboxURL]) && !IsPlayerInAnyVehicle(i))
		{
		    strunpack(str, BoomboxData[id][boomboxURL]);
		    PlayerData[i][pBoombox] = id;

		    StopAudioStreamForPlayer(i);
		    PlayAudioStreamForPlayer(i, str, BoomboxData[id][boomboxPos][0], BoomboxData[id][boomboxPos][1], BoomboxData[id][boomboxPos][2], 30.0, 1);
		}
		else if (PlayerData[i][pBoombox] != INVALID_PLAYER_ID && !IsPlayerInRangeOfPoint(i, 30.0, BoomboxData[PlayerData[i][pBoombox]][boomboxPos][0], BoomboxData[PlayerData[i][pBoombox]][boomboxPos][1], BoomboxData[PlayerData[i][pBoombox]][boomboxPos][2]))
		{
		    PlayerData[i][pBoombox] = INVALID_PLAYER_ID;
		    StopAudioStreamForPlayer(i);
		}
		if (PlayerData[i][pInjured] == 1)
		{
			if(PlayerData[i][pInjuredTime] > 0)
			{
				PlayerData[i][pInjuredTime]--;
				new tstr[128];
				format(tstr, sizeof(tstr), "~r~Anda Telah Pengsan!~n~~w~Masa Pengsan: %d", PlayerData[i][pInjuredTime]);
				GameTextForPlayer(i, tstr, 1000, 3); 
				ApplyAnimation(i, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
			}
			else
			{
				if(PlayerData[i][pBodyInsurance] == 0)
				{
					SendInfoMessage(i, "Semua barang di inventory anda telah hilang kerana anda tidak mempunyai insuran badan.");
					Inventory_Clear(i);
				}

				PlayerData[i][pBodyInsurance] -= 1;

				SetPlayerPos(i, 1187.3882, -1323.5475, 13.5590);
				SetPlayerFacingAngle(i, 271.5479);

				SetPlayerInterior(i, 0);
				SetPlayerVirtualWorld(i, 0);

			    TogglePlayerControllable(i, 1);
			    SetCameraBehindPlayer(i);

			    SendServerMessage(i, "Anda telah dihantar ke hospital.");

			    GameTextForPlayer(i, " ", 1, 3);

			    PlayerData[i][pInjured] = 0;
				PlayerData[i][pInjuredTime] = 0;
			}
		}
        if (PlayerData[i][pHealthTime] > 0)
        {
            PlayerData[i][pHealthTime]--;
		}

		GetPlayerHealth(i, PlayerData[i][pHealth]);
	    GetPlayerArmour(i, PlayerData[i][pArmorStatus]);

		if(PlayerData[i][pHUD] == 1 && PlayerData[i][pLogged])
		{
			UpdatePlayerHudData(i);
			ShowHungerTextdraw(i, 1);
		}
	}
	return 1;
}

function RefuelCheck()
{
	new
	    string[128];

	foreach (new i : Player)
	{
	    if (!PlayerData[i][pLogged] || PlayerData[i][pRefill] == INVALID_VEHICLE_ID)
	        continue;

        if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID && PlayerData[i][pGasPump] != -1)
		{
		    PlayerData[i][pRefillPrice]++;

		    CarData[PlayerData[i][pRefill]][carFuel] ++;
		    PumpData[PlayerData[i][pGasPump]][pumpFuel] --;

		    if (PumpData[PlayerData[i][pGasPump]][pumpExists])
			{
			    format(string, sizeof(string), "[GAS PUMP]\n{FFFFFF}Fuel Left: "YELLOW_E"%d"WHITE_E" liters\nPress "GREEN_E"Y"WHITE_E" to refuel the vehicle.", PumpData[PlayerData[i][pGasPump]][pumpFuel]);
			    UpdateDynamic3DTextLabelText(PumpData[PlayerData[i][pGasPump]][pumpText3D], COLOR_DARKBLUE, string);
			}
			if (CarData[PlayerData[i][pRefill]][carFuel] >= 100 || GetEngineStatus(PlayerData[i][pRefill]) || !PumpData[PlayerData[i][pGasPump]][pumpExists] || PumpData[PlayerData[i][pGasPump]][pumpFuel] < 0)
			{
			    CarData[PlayerData[i][pRefill]][carFuel] = 100;
			
			    GiveMoney(i, -PlayerData[i][pRefillPrice]);
			    SendServerMessage(i, "You have refilled your vehicle for %s.", FormatNumber(PlayerData[i][pRefillPrice]));

			    if (PumpData[PlayerData[i][pGasPump]][pumpExists])
				{
					if (PumpData[PlayerData[i][pGasPump]][pumpFuel] < 0)
						PumpData[PlayerData[i][pGasPump]][pumpFuel] = 0;

					BusinessData[PlayerData[i][pGasStation]][bizVault] += PlayerData[i][pRefillPrice];
					Business_Save(PlayerData[i][pGasStation]);

					Pump_Save(PlayerData[i][pGasPump]);
				}
				StopRefilling(i);
			}
		}
	}
	return 1;
}

function CarDataUpdate()
{
	for (new i = 1; i != MAX_VEHICLES; i ++) 
	{
		if (IsEngineVehicle(i) && GetEngineStatus(i))
		{
			new id = Car_GetID(i);
			
			if (id != -1)  
			{
				// Minyak
				if (CarData[id][carFuel] > 0)
				{
					CarData[id][carFuel]--;

					if (CarData[id][carFuel] >= 1 && CarData[id][carFuel] <= 5)
					{
						SendInfoMessage(GetVehicleDriver(i), "Kenderaan ini akan kehabisan minyak! Sila pergi ke stesen minyak.");
					}
				}
				if (CarData[id][carFuel] <= 0)
				{
					CarData[id][carFuel] = 0;
					SetEngineStatus(i, false);
				}
				
				// Temperature
				if (CarData[id][carTemperature] < 1500)
				{
					CarData[id][carTemperature]++;

					if (CarData[id][carTemperature] <= 1499 && CarData[id][carTemperature] >= 1455)
					{
						SendInfoMessage(GetVehicleDriver(i), "Temperature kenderaan ni telah mencapai tahap maksimum! Sila matikan enjin kenderaan anda.");
					}
				}
				if (CarData[id][carTemperature] >= 1500)
				{
					CarData[id][carTemperature] = 1500;
					SetEngineStatus(i, false);
					SetVehicleHealth(i, 0);
				}
			}
		}
		if (IsEngineVehicle(i) && !GetEngineStatus(i))
		{
			new id = Car_GetID(i);
			
			if (id != -1)  
			{
				if (CarData[id][carTemperature] > 0)
				{
					CarData[id][carTemperature] -= 10;
				}
				if (CarData[id][carTemperature] <= 0)
				{
					CarData[id][carTemperature] = 0;
				}
			}
		}
	}
	return 1;
}

function Rent_Load()
{
	static
	    rows,
	    fields;

	cache_get_data(rows, fields, g_iHandle);

	for (new i = 0; i < rows; i ++) if (i < MAX_RENT_POINTS)
	{
	    RentData[i][rentExists] = true;

	    RentData[i][rentID] = cache_get_field_int(i, "rentID");
	    RentData[i][rentPos][0] = cache_get_field_float(i, "rentX");
	    RentData[i][rentPos][1] = cache_get_field_float(i, "rentY");
	    RentData[i][rentPos][2] = cache_get_field_float(i, "rentZ");
	    RentData[i][rentInterior] = cache_get_field_int(i, "rentInterior");
	    RentData[i][rentWorld] = cache_get_field_int(i, "rentWorld");

	    Rent_Refresh(i);
	}
	return 1;
}

function OnRentCreated(rentid)
{
	if (rentid == -1 || !RentData[rentid][rentExists])
	    return 0;

	RentData[rentid][rentID] = cache_insert_id(g_iHandle);
	Rent_Save(rentid);

	return 1;
}

function RemoveDisconnectLabel(playerid)
{
	if (IsValidDynamic3DTextLabel(PlayerData[playerid][pDisconnectLabel])) DestroyDynamic3DTextLabel(PlayerData[playerid][pDisconnectLabel]);
	return 1;
}

function AddDisconnectLabel(playerid, reason)
{
    new Float:x, Float:y, Float:z, str[230];
	GetPlayerPos(playerid, x, y, z);
	switch(reason)
	{
		case 0: format(str, sizeof(str), "%s (%i) has left the server.\nReason: Crash/ Timeout.", ReturnName(playerid), playerid);
		case 1: format(str, sizeof(str), "%s (%i) has left the server.\nReason: Exiting.", ReturnName(playerid), playerid);
		case 2: format(str, sizeof(str), "%s (%i) has left the server.\nReason: Kicked/ Banned.", ReturnName(playerid), playerid);
	}
	PlayerData[playerid][pDisconnectLabel] = CreateDynamic3DTextLabel(str, -1, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	SetTimerEx("RemoveDisconnectLabel", 8000, false, "i", playerid);
    return 1;
}

// --------------------------------- End Functions