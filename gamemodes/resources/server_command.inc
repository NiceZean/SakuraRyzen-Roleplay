CMD:x(playerid, params[])
{
	new Float:x, Float:y, Float:z, Float:npos;
	if(PlayerData[playerid][pAdmin] >= 2)
	{
		if(PlayerData[playerid][pAdminDuty] == 0)
			return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

		if(sscanf(params, "f", npos)) return SendErrorMessage(playerid, "/x [Cordinate]");
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x+npos, y, z);
		return 1;
	}
	else return SendErrorMessage(playerid, "You're not authorized.");
}
CMD:y(playerid, params[])
{
	new Float:x, Float:y, Float:z, Float:npos;
	if(PlayerData[playerid][pAdmin] >= 2)
	{
		if(PlayerData[playerid][pAdminDuty] == 0)
			return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

		if(sscanf(params, "f", npos)) return SendErrorMessage(playerid, "/y [Cordinate]");
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y+npos, z);
		return 1;
	}
	else return SendErrorMessage(playerid, "You're not authorized.");
}
CMD:z(playerid, params[])
{
	new Float:x, Float:y, Float:z, Float:npos;
	if(PlayerData[playerid][pAdmin] >= 2)
	{
		if(PlayerData[playerid][pAdminDuty] == 0)
			return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

		if(sscanf(params, "f", npos)) return SendErrorMessage(playerid, "/z [Cordinate]");
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z+npos);
		return 1;
	}
	else return SendErrorMessage(playerid, "You're not authorized.");
}
//
CMD:callsign(playerid, params[])
{
    new vehicleid;
    vehicleid = GetPlayerVehicleID(playerid);
	new string[32];
	if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "You're not in a vehicle.");

	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsACruiser(GetPlayerVehicleID(playerid)))
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam mpv polis.");

	if(vehiclecallsign[GetPlayerVehicleID(playerid)] == 1)
	{
 		Delete3DTextLabel(vehicle3Dtext[vehicleid]);
	    vehiclecallsign[vehicleid] = 0;
	    SendClientMessage(playerid, COLOR_RED, "CALLSIGN REMOVED");
	    return 1;
	}
	if(sscanf(params, "s[32]",string)) return SendErrorMessage(playerid, "Sila masukkan callsign untuk di-attach.");
	if(vehiclecallsign[GetPlayerVehicleID(playerid)] == 0)
	{
		vehicle3Dtext[vehicleid] = Create3DTextLabel(string, COLOR_WHITE, 0.0, 0.0, 0.0, 10.0, 0, 1);
		Attach3DTextLabelToVehicle(vehicle3Dtext[vehicleid], vehicleid, 0.0, -2.8, 0.0);
		vehiclecallsign[vehicleid] = 1;
		SendServerMessage(playerid, "CALLSIGN ATTACHED");
	}
	return 1;
}

CMD:aremovecall(playerid, params[])
{
	new vehicleid;
	if (PlayerData[playerid][pAdmin] < 1)
		return SendErrorMessage(playerid, "You must be an administrator.");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if(sscanf(params, "i", vehicleid)) return SendErrorMessage(playerid, "Sila masukkan id kenderaan.");

    if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	Delete3DTextLabel(vehicle3Dtext[vehicleid]);
	SendServerMessage(playerid, "Callsign untuk id kenderaan tersebut telah dibuang.");
	return 1;
}

CMD:b(playerid, params[])
{
    if(isnull(params))
        return SendUsageMessage(playerid, "/b [local OOC]");
		
	if(PlayerData[playerid][pAdminDuty] == 1)
    {
        return SendErrorMessage(playerid, "Anda kini sedang onduty admin! OOC local chat tidak dapat digunakan.");
	}
	else
	{
		if(strlen(params) > 64)
		{
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "(( OOC %s: %.64s ..", ReturnName(playerid, 0), params);
            SendNearbyMessage(playerid, 20.0, COLOR_WHITE, ".. %s ))", params[64]);
		}
		else
        {
            SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "(( OOC %s: %s ))", ReturnName(playerid, 0), params);
            return 1;
        }
	}
	new string[64];
	format(string, sizeof(string), "(( %s ))", params);
	SetPlayerChatBubble(playerid, string, COLOR_WHITE, 10.0, 6000);
    return 1;
}

CMD:me(playerid, params[])
{

	if (isnull(params))
	    return SendUsageMessage(playerid, "/me [action]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s %.64s", ReturnName(playerid, 0), params);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "...%s", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s %s", ReturnName(playerid, 0), params);
	}
	new string[64];
	format(string, sizeof(string), "* %s %s", ReturnName(playerid, 0), params);
 	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 6000);
	return 1;
}

CMD:do(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/do [description]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %.64s", params);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "...%s (( %s ))", params[64], ReturnName(playerid, 0));
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s (( %s ))", params, ReturnName(playerid, 0));
	}
	new string[64];
	format(string, sizeof(string), "* %s (( %s ))", params, ReturnName(playerid, 0));
 	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 6000);
	return 1;
}

CMD:ame(playerid, params[])
{
	static
	    string[128];

	if (isnull(params))
	    return SendUsageMessage(playerid, "/ame [action]");

	format(string, sizeof(string), "* %s %s", ReturnName(playerid, 0), params);
 	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 10000);

 	SendClientMessageEx(playerid, COLOR_PURPLE, "* %s %s", ReturnName(playerid, 0), params);
	return 1;
}

CMD:ado(playerid, params[])
{
    static
	    string[128];

	if (isnull(params))
	    return SendUsageMessage(playerid, "/ado [description]");

	format(string, sizeof(string), "* %s (( %s ))", params, ReturnName(playerid, 0));
 	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 10000);

 	SendClientMessageEx(playerid, COLOR_PURPLE, "* %s (( %s ))", params, ReturnName(playerid, 0));
	return 1;
}

CMD:s(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/(s)hout [shout text]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s menjerit: %.64s", ReturnName(playerid, 0), params);
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "...%s !!!", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s menjerit: %s !!!", ReturnName(playerid, 0), params);
	}
	new string[64];
 	format(string, sizeof(string), "menjerit: %s", params);
	SetPlayerChatBubble(playerid, string, COLOR_WHITE, 30.0, 6000);
	return 1;
}

CMD:l(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/(l)ow [low text]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[LOW] %s says: %.64s", ReturnName(playerid, 0), params);
	    SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "...%s", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[LOW] %s says: %s", ReturnName(playerid, 0), params);
	}
	new string[64];
 	format(string, sizeof(string), "[LOW] says: %s", params);
	SetPlayerChatBubble(playerid, string, COLOR_WHITE, 5.0, 6000);
	return 1;
}

CMD:o(playerid, params[])
{            
    if(g_StatusOOC == 1 && PlayerData[playerid][pAdminDuty] < 1) 
        return SendErrorMessage(playerid, "An staff has disabled global OOC chat.");

    if(isnull(params))
        return SendUsageMessage(playerid, "/o [text]");

    if(strlen(params) < 64)
    {
        foreach (new i : Player)
        {
			if(PlayerData[playerid][pAdminDuty] == 1)
			{
				SendClientMessageEx(i, COLOR_WHITE, "{ff0000}(( {00ff3c}[OOC Global]: {FF0000}ADMIN {00ff3c}%s : {ffffff}%s {ff0000}))", ReturnName(playerid, 0), params);
			}
			else
			{
				SendClientMessageEx(i, COLOR_WHITE, "{ff0000}(( {00ff3c}[OOC Global]: %s : {ffffff}%s {ff0000}))", ReturnName(playerid, 0), params);
			}
        }
    }
    else
        return SendErrorMessage(playerid, "Teks terlalu panjang, maksium teks adalah 64.");
    return 1;
}

CMD:help(playerid, params[])
{
	Dialog_Show(playerid, Help, DIALOG_STYLE_LIST, ""WHITE_E"Help Menu", ""WHITE_E"General Commands\nVehicle Commands\nFaction Commands\nJob Commands\nBusiness Commands\nHouse Commands", "Pilih", "Tutup");
	return 1;
}

CMD:lastlogged(playerid, params[]) 
{
	if (isnull(params) || strlen(params) > 24)
	    return SendUsageMessage(playerid, "/lastlogged [username]");

	static
	    query[128];

	format(query, sizeof(query), "SELECT `LoginDate` FROM `accounts` WHERE `Username` = '%s'", SQL_ReturnEscaped(params));
	mysql_tquery(g_iHandle, query, "OnLoginDate", "ds", playerid, params);

 	return 1;
}

CMD:engine(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (!IsEngineVehicle(vehicleid))
		return SendErrorMessage(playerid, "Anda perlu berada di dalam kenderaan.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "Anda perlu membawa kenderaan.");

	new id = Car_GetID(vehicleid);

	if (id != -1)
	{
		if (CarData[id][carFuel] < 1)
			return SendErrorMessage(playerid, "Kenderaan ini tidak mempunyai minyak! Anda tidak dapat menghidupkannya.");
		
		if (CarData[id][carTemperature] > 1455)
			return SendErrorMessage(playerid, "Temperature kenderaan ini telah mencapai tahap maksimum! Anda tidak dapat menghidupkannya.");
	}

	if (ReturnVehicleHealth(vehicleid) <= 300)
	    return SendErrorMessage(playerid, "Kenderaan ini telah rosak! Anda tidak dapat menghidupkannya.");

	switch (GetEngineStatus(vehicleid))
	{
	    case false:
	    {
	        SetEngineStatus(vehicleid, true);
	        SendServerMessage(playerid, "Anda telah menghidupkan enjin kenderaan ini!");
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s memasukkan kunci ke dalam penyalaan dan menghidupkan enjin.", ReturnName(playerid, 0));
		}
		case true:
		{
		    SetEngineStatus(vehicleid, false);
		    SendServerMessage(playerid, "Anda telah menghentikan enjin kenderaan ini!");
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s memasukkan kunci ke dalam penyalaan dan menghentikan enjin.", ReturnName(playerid, 0));
		}
	}
	return 1;
}

CMD:lights(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (!IsEngineVehicle(vehicleid))
		return SendErrorMessage(playerid, "Anda tidak berada di dalam kenderaan.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "Anda perlu membawa kenderaan.");

	switch (GetLightStatus(vehicleid))
	{
	    case false:
	    {
	        SetLightStatus(vehicleid, true);
	        SendServerMessage(playerid, "Anda telah menghidupkan lampu kenderaan ini!");
		}
		case true:
		{
		    SetLightStatus(vehicleid, false);
		    SendServerMessage(playerid, "Anda telah menutup lampu kenderaan ini!");
		}
	}
	return 1;
}

CMD:hood(playerid, params[])
{
	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && IsPlayerNearHood(playerid, i))
	{
	    if (!IsDoorVehicle(i))
	        return SendErrorMessage(playerid, "Kenderaan ini tidak mempunyai pintu.");

	    if (!GetHoodStatus(i))
		{
	        SetHoodStatus(i, true);
	        SendServerMessage(playerid, "Anda telah membuka hood kenderaan ini!");
		}
		else
		{
			SetHoodStatus(i, false);
	        SendServerMessage(playerid, "Anda telah menutup hood kenderaan ini!");
		}
	    return 1;
	}
	SendErrorMessage(playerid, "Anda tidak berada di dekat kenderaan.");
	return 1;
}

CMD:windows(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (!IsWindowedVehicle(vehicleid))
		return SendErrorMessage(playerid, "Anda tidak berada di dalam kenderaan yang mempunyai pintu.");

	switch (CoreVehicles[vehicleid][vehWindowsDown])
	{
	    case false:
	    {
	        CoreVehicles[vehicleid][vehWindowsDown] = true;
	        SendServerMessage(playerid, "Anda telah menurunkan tingkap kenderaan ini!");
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s menekan butang dan menurunkan tingkap.", ReturnName(playerid, 0));
			SetVehicleParamsCarWindows(vehicleid, 1, 1, 1, 1);
		}
		case true:
		{
		    CoreVehicles[vehicleid][vehWindowsDown] = false;
		    SendServerMessage(playerid, "Anda telah menaikkan tingkap kenderaan ini!");
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s menekan butang dan menaikkan tingkap.", ReturnName(playerid, 0));
			SetVehicleParamsCarWindows(vehicleid, 0, 0, 0, 0);
		}
	}
	return 1;
}

CMD:makeadmin(playerid, params[])
{
	static
		userid,
	    level;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, level))
		return SendUsageMessage(playerid, "/makeadmin [playerid/name] [level]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (level < 0 || level > 3)
	    return SendErrorMessage(playerid, "Invalid admin level. Levels range from 0 to 3.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s telah mentapkan level admin %s kepada level %d.", ReturnName(playerid, 0), ReturnName(userid, 0), level);
	SendInfoMessage(userid, "%s telah mentapkan level admin anda kepada %d.", ReturnName(playerid, 0), level);

	PlayerData[userid][pAdmin] = level;
 	Log_Write("logs/admin_log.txt", "[%s] %s has set %s's admin level to %d.", ReturnDate(), ReturnName(playerid, 0), ReturnName(userid, 0), level);

	return 1;
}

CMD:a(playerid, params[])
{
	if (!PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "You are not an administrator.");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
	    return SendUsageMessage(playerid, "/a [admin text]");

	if (strlen(params) > 64) {
	    SendAdminAlert(COLOR_RED, "** (Admin Level %d) %s: %.64s", PlayerData[playerid][pAdmin], ReturnName(playerid, 0), params);
	    SendAdminAlert(COLOR_RED, "...%s **", params[64]);
	}
	else {
	    SendAdminAlert(COLOR_RED, "** (Admin Level %d) %s: %s **", PlayerData[playerid][pAdmin], ReturnName(playerid, 0), params);
	}
	return 1;
}

CMD:aduty(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if (!PlayerData[playerid][pAdminDuty])
	{
		SetPlayerColor(playerid, COLOR_RED);

		PlayerData[playerid][pAdminDuty] = 1;
		SetPlayerName(playerid, PlayerData[playerid][pUsername]);
		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s telah "GREEN_E"onduty "WHITE_E"sebagai admin.", ReturnName(playerid, 0));
	}
	else
	{
	    SetPlayerColor(playerid, DEFAULT_COLOR);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s telah "RED_E"offduty "WHITE_E"sebagai admin.", ReturnName(playerid, 0));
		PlayerData[playerid][pAdminDuty] = 0;
		SetPlayerName(playerid, PlayerData[playerid][pName]);
	}
	return 1;
}

CMD:od(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 3)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if (!PlayerData[playerid][pAdminDuty])
		PlayerData[playerid][pAdminDuty] = 1;
	else
		PlayerData[playerid][pAdminDuty] = 0;

	return 1;
}

CMD:ahelp(playerid, params[])
{
	if (!PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "Anda bukan admin.");

    Dialog_Show(playerid, aHelp, DIALOG_STYLE_LIST, ""WHITE_E"Help Menu", ""WHITE_E"Administrator Commands\nDeveloper Commands\nExecutive Commands", "Pilih", "Tutup");
	return 1;
}

CMD:report(playerid, params[])
{
	new reportid = -1;

	if (isnull(params))
	{
	    SendUsageMessage(playerid, "/report [reason]");
	    return 1;
	}
	if (Report_GetCount(playerid) > 1)
	    return SendErrorMessage(playerid, "Anda telah mempunyai 1 laporan aktif!");

	if (PlayerData[playerid][pReportTime] >= gettime())
	    return SendErrorMessage(playerid, "Anda perlu menunggu %d saat untuk menghantar laporan seterusnya.", PlayerData[playerid][pReportTime] - gettime());

	if ((reportid = Report_Add(playerid, params)) != -1)
	{
		foreach (new i : Player)
		{
			if (PlayerData[i][pAdmin] > 0 && PlayerData[i][pAdminDuty]) {
				SendClientMessageEx(i, COLOR_LIGHTYELLOW, ""RED_E"[Report #%d]: "WHITE_E"%s (ID: %d) reported: %s", reportid, ReturnName(playerid, 0), playerid, params);
			}
		}
		PlayerData[playerid][pReportTime] = gettime() + 15;
		SendClientMessageEx(playerid, COLOR_WHITE, "LAPORAN ANDA: "YELLOW_E"%s", params);
	}
	else
	{
	    SendErrorMessage(playerid, "Laporan telah penuh! Sila tunggu.");
	}
	return 1;
}

CMD:reports(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new string[150 * MAX_REPORTS], header[512], count, text[500];
	header = "";
	strcat(header,"ID\tPemain\tLaporan\n",sizeof(header));

	for (new i = 0; i != MAX_REPORTS; i ++)
	{
	    if (!ReportData[i][rExists])
			continue;

		strunpack(text, ReportData[i][rText]);

		format(string, sizeof(string), ""WHITE_E"%s%d\t%s\t%s\n", string, i, ReturnName(ReportData[i][rPlayer]), text);
		count++;
	}
	if (!count)
	    return SendErrorMessage(playerid, "Kini tiada laporan yang aktif.");

	strcat(header, string);
	Dialog_Show(playerid, Report, DIALOG_STYLE_TABLIST_HEADERS, ""WHITE_E"Senarai Laporan", header, "Pilih", "Batal");
	return 1;
}

CMD:spectate(playerid, params[])
{
	new userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!isnull(params) && !strcmp(params, "off", true))
	{
	    if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
			return SendErrorMessage(playerid, "Anda kini tidak spectate mana-mana pemain.");

	    PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
	    PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);

	    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], PlayerData[playerid][pPos][3], 0, 0, 0, 0, 0, 0);
	    TogglePlayerSpectating(playerid, false);

	    return SendServerMessage(playerid, "Anda kini tidak berada dalam spectate mode.");
	}
	if (sscanf(params, "u", userid))
		return SendUsageMessage(playerid, "/spectate [playerid/name] - Taip \"/spectate off\" untuk berhenti spectating.");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if(PlayerData[playerid][pAdmin] < PlayerData[userid][pAdmin])
        return SendErrorMessage(playerid, "Anda tidak boleh spectate admin dengan level tinggi dari anda.");

	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	{
		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		GetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

		PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
		PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
	}
	SetPlayerInterior(playerid, GetPlayerInterior(userid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(userid));

	TogglePlayerSpectating(playerid, 1);

	if (IsPlayerInAnyVehicle(userid))
	    PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userid));

	else
		PlayerSpectatePlayer(playerid, userid);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s kini sedang spectate %s (ID: %d).", ReturnName(playerid, 0), ReturnName(userid, 0), userid);
	PlayerData[playerid][pSpectator] = userid;

	return 1;
}

CMD:ajail(playerid, params[])
{
	static
		userid,
		minutes,
		reason[128];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if (sscanf(params, "uds[128]", userid, minutes, reason))
	    return SendUsageMessage(playerid, "/ajail [playerid/name] [minutes] [reason]");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (minutes < 1)
		return SendErrorMessage(playerid, "Anda tidak boleh memenjarakan pemain di bawah 0 minit.");

	if(PlayerData[playerid][pAdmin] < PlayerData[userid][pAdmin])
        return SendErrorMessage(playerid, "Anda tidak boleh memenjara admin dengan level tinggi dari anda.");

	ClearAnimations(userid);

    SetPlayerPos(userid, 197.6346, 175.3765, 1003.0234);
    SetPlayerInterior(userid, 3);

	SetPlayerVirtualWorld(userid, (playerid + 100));
 	SetPlayerFacingAngle(userid, 0.0);

	SetCameraBehindPlayer(userid);
	ResetWeapons(userid);

	ResetPlayer(userid);

	PlayerData[userid][pJailTime] = minutes * 60;
	PlayerData[userid][pPrisoned] = 0;

	SendInfoMessage(playerid, "Anda telah memenjarakan %s selama %d minit dengan sebab %s.", ReturnName(userid, 0), minutes, reason);
	SendInfoMessage(userid, "%s telah memenjarakan anda selama %d minit, kerana %s.", ReturnName(playerid, 0), minutes, reason);

	SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has jailed %s for %d minutes", ReturnName(playerid, 0), ReturnName(userid, 0), minutes);
	SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);

	Log_Write("logs/jail_log.txt", "[%s] %s has jailed %s for %d minutes, reason: %s.", ReturnDate(), ReturnName(playerid, 0), ReturnName(userid, 0), minutes, reason);
	return 1;
}

CMD:release(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/release [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!PlayerData[userid][pJailTime])
	    return SendErrorMessage(playerid, "Anda tidak boleh mengeluarkan pemain yang tidak berada di dalam penjara.");

	PlayerData[userid][pJailTime] = 1;

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s telah mengeluarkan %s dari penjara.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "%s telah mengeluarkan anda dari penjara.", ReturnName(playerid, 0));

	Log_Write("logs/jail_log.txt", "[%s] %s has released %s from jail.", ReturnDate(), ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:kick(playerid, params[])
{
	static
	    userid,
	    reason[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[128]", userid, reason))
	    return SendUsageMessage(playerid, "/kick [playerid/name] [reason]");

	if (userid == INVALID_PLAYER_ID || (IsPlayerConnected(userid) && PlayerData[userid][pKicked]))
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    if (PlayerData[userid][pAdmin] > PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "Anda tidak boleh kick admin level tinggi dari anda");

	SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has kicked %s", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);

	Log_Write("logs/kick_log.txt", "[%s] %s has kicked %s for: %s.", ReturnDate(), ReturnName(playerid, 0), ReturnName(userid, 0), reason);

	KickEx(userid);
	return 1;
}

CMD:mute(playerid, params[])
{
    static
	    userid,
	    reason[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");
		
	if (sscanf(params, "us[128]", userid, reason))
	    return SendUsageMessage(playerid, "/mute [playerid/name] [reason]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You can't mute yourself!");

	if (PlayerData[userid][pMuted])
	    return SendErrorMessage(playerid, "The player you're attempting to mute is muted already.");

    if (PlayerData[userid][pAdmin] > PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "The specified player has higher authority.");

	PlayerData[userid][pMuted] = 1;

	SendInfoMessage(playerid, "You have muted %s from using text and commands.", ReturnName(userid, 0));

	SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has muted %s from using text and commands.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);

	SendInfoMessage(userid, "%s has muted you from using text and commands.", ReturnName(playerid, 0));

	return 1;
}

CMD:unmute(playerid, params[])
{
    static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/unmute [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!PlayerData[userid][pMuted])
	    return SendErrorMessage(playerid, "The player you're attempting to mute is not muted.");

	PlayerData[userid][pMuted] = 0;

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has unmuted %s from using text and commands.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "You have been unmuted by %s.", ReturnName(playerid, 0));

	return 1;
}

CMD:freeze(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/freeze [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	TogglePlayerControllable(userid, 0);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has freeze movement %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "%s has frozen your movements.", ReturnName(playerid, 0));
	return 1;
}

CMD:unfreeze(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/unfreeze [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    PlayerData[playerid][pFreeze] = 0;

	TogglePlayerControllable(userid, 1);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has unfreeze movement %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "%s has unfrozen your movements.", ReturnName(playerid, 0));
	return 1;
}

CMD:revive(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/revive [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!PlayerData[userid][pInjured])
	    return SendErrorMessage(playerid, "You can't revive a player that's not injured.");

	PlayerData[userid][pInjured] = 0;

	ClearAnimations(userid);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has revive character %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "%s has revived your character.", ReturnName(playerid, 0));
	return 1;
}

CMD:respawn(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/respawn [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!IsPlayerSpawned(userid))
	    return SendErrorMessage(playerid, "You can't respawn a player that's not spawned.");

	RespawnPlayer(userid);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has respawned %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "You have been respawned by %s.", ReturnName(playerid, 0));

	return 1;
}

CMD:refill(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/refill [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	PlayerData[userid][pHunger] = 100;
	PlayerData[userid][pThirst] = 100;
	PlayerData[userid][pStress] = 0;

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has refill hunger, thirst and stress %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	SendInfoMessage(userid, "Your hunger, thirst and stress was refilled by %s.", ReturnName(playerid, 0));

	return 1;
}

CMD:skin(playerid, params[])
{
	static
	    userid,
		skinid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, skinid))
	    return SendUsageMessage(playerid, "/skin [playerid/name] [skin id]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if(PlayerData[playerid][pAdmin] < PlayerData[userid][pAdmin])
        return SendErrorMessage(playerid, "You can't set skin admin higher than you.");

	if (skinid < 0 || skinid > 299)
	    return SendErrorMessage(playerid, "Invalid skin ID. Skins range from 0 to 299.");

	SetPlayerSkin(userid, skinid);
	PlayerData[userid][pSkin] = skinid;

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set skin %s to skin id %d.", ReturnName(playerid, 0), ReturnName(userid, 0), skinid);
	SendInfoMessage(userid, "%s has set your skin to ID: %d.", ReturnName(playerid, 0), skinid);

	return 1;
}

CMD:username(playerid, params[])
{
	if (isnull(params) || strlen(params) > 24)
		return SendUsageMessage(playerid, "/username [character name]");

	static
	    query[128];

	format(query, sizeof(query), "SELECT `Username` FROM `characters` WHERE `Character` = '%s'", SQL_ReturnEscaped(params));
	mysql_tquery(g_iHandle, query, "OnResolveUsername", "ds", playerid, params);

	return 1;
}

CMD:stats(playerid, params[])
{
	ShowStats(playerid, playerid);
	return 1;
}

CMD:checkstats(playerid, params[])
{
    static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/checkstats [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!PlayerData[userid][pLogged] && !PlayerData[userid][pCharacter])
	    return SendErrorMessage(playerid, "That player is not logged in yet.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has check stats %s.", ReturnName(playerid, 0), ReturnName(userid, 0));

	ShowStats(playerid, userid);
	return 1;
}

CMD:acc(playerid, params[])
{
	new
	    string[128];

	format(string, sizeof(string), "Glasses: %s\nHat: %s\nBandana: %s", (PlayerData[playerid][pGlasses]) ? ("Yes") : ("No"), (PlayerData[playerid][pHat]) ? ("Yes") : ("No"), (PlayerData[playerid][pBandana]) ? ("Yes") : ("No"));
	Dialog_Show(playerid, Accessory, DIALOG_STYLE_LIST, "Accessories", string, "Select", "Cancel");

	return 1;
}

CMD:shooter(playerid, params[])
{
	static
	    userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/shooter [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (PlayerData[userid][pLastShot] == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player hasn't been shot since they joined.");

    SendInfoMessage(playerid, "%s was last shot by %s (%s).", ReturnName(userid, 0), ReturnName(PlayerData[userid][pLastShot]), GetDuration(gettime() - PlayerData[userid][pShotTime]));
    return 1;
}

CMD:ann(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if(isnull(params)) return SendUsageMessage(playerid, "/ann [text]");

	if(strfind(params, "~x~", true) != -1)
		return SendErrorMessage(playerid, "~x~ is not allowed in announce.");
		
	if(strfind(params, "#k~", true) != -1)
		return SendErrorMessage(playerid, "The constant key is not allowed in announce.");

	if(strfind(params, "/q", true) != -1)
		return SendErrorMessage(playerid, "You are not allowed to type /q in announcement!");

	new iTemp = 0;
	for(new i = (strlen(params)-1); i != -1; i--)
	{
		if(params[i] == '~')
			iTemp ++;
	}
	if(iTemp % 2 == 1)
		return SendErrorMessage(playerid, "You either have an extra ~ or one is missing in the announcement!");
	
	new str[512];
	format(str, sizeof(str), "~w~%s", params);
	GameTextForAll(str, 6500, 3);
    return 1;
}

CMD:aslap(playerid, params[])
{
    new otherid, reason[128], Float:POS[3];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if(sscanf(params, "us[128]", otherid, reason))
        return SendUsageMessage(playerid, "/aslap [playerid/PartOfName] [reason]");

	if (!IsPlayerSpawned(otherid))
		return SendErrorMessage(playerid, "You can't slap a player that's not spawned.");

	if(PlayerData[playerid][pAdmin] < PlayerData[otherid][pAdmin])
        return SendErrorMessage(playerid, "You can't slap admin higher than you.");

	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	SetPlayerPos(otherid, POS[0], POS[1], POS[2] + 9.0);

	SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has slap %s", ReturnName(playerid, 0), ReturnName(otherid, 0));
	SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);
	
	PlayerPlaySound(otherid, 1130, 0.0, 0.0, 0.0);
    return 1;
}

CMD:playervehicle(playerid, params[])
{
	new otherid;

	if(sscanf(params, "u", otherid)) return SendUsageMessage(playerid, "/playervehicle [playerid]");

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsPlayerSpawned(otherid))
		return SendErrorMessage(playerid, "Invalid playerid specified.");

	new string[256 * MAX_OWNABLE_CARS], header[512], count, status[500];
	header = "";
	strcat(header,"#\tModel\tPlate\tStatus\n",sizeof(header));

	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) if (Car_IsOwner(otherid, i)) 
	{	
		if (CarData[i][carImpounded] == 1)
		{
			status = ""BLUE_E"Impounded"WHITE_E"";
		}
		else if(IsValidVehicle(CarData[i][carVehicle]))
		{
			status = ""GREEN_E"Spawned"WHITE_E"";
		}
		else
		{
			status = ""RED_E"Despawned"WHITE_E"";
		}

		if(CarData[i][carGov] == 1)
		{
			format(string, sizeof(string), ""WHITE_E"%s%d\t%s\t"YELLOW_E"%s"WHITE_E"\t%s\n", string, CarData[i][carVehicle], ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate], status);
		}
		else
		{
			format(string, sizeof(string), ""WHITE_E"%s%d\t%s\t%s\t%s\n", string, CarData[i][carVehicle], ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate], status);
		}
		count++;
	}
	if (!count)
		return SendErrorMessage(playerid, "Pemain ini tidak mempunyai sebarang kenderaan.");

	strcat(header, string);
	new str[400];
	format(str, sizeof(str), ""WHITE_E"%s Vehicles", ReturnName(otherid, 0));
	Dialog_Show(playerid, CarMenu, DIALOG_STYLE_TABLIST_HEADERS, str, header, "Close", "");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s telah memeriksa kenderaan milik %s.", ReturnName(playerid, 0), ReturnName(otherid, 0));
    return 1;
}

CMD:playerproperties(playerid, params[])
{
	new otherid;

	if(sscanf(params, "u", otherid)) return SendUsageMessage(playerid, "/playerproperties [playerid]");

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsPlayerSpawned(otherid))
		return SendErrorMessage(playerid, "Invalid playerid specified.");

	new string[150 * MAX_HOUSES], header[512], count, status[500];
	header = "";
	strcat(header,"ID\tAdress\tLocation\tStatus\n",sizeof(header));

	for (new i = 0; i < MAX_HOUSES; i ++) if (House_IsOwner(otherid, i)) {
		if (HouseData[i][houseLocked])
		{
			status = ""RED_E"Locked"WHITE_E"";
		}
		else
		{
			status = ""GREEN_E"Unlocked"WHITE_E"";
		}
		format(string, sizeof(string), ""WHITE_E"%s%d (House)\t%s\t%s\t%s\n", string, i, HouseData[i][houseAddress], GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]), status);
		count++;
	}
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (Business_IsOwner(otherid, i) && BusinessData[i][bizOwner] != 99999999) {
		if (BusinessData[i][bizLocked])
		{
			status = ""RED_E"Closed"WHITE_E"";
		}
		else
		{
			status = ""GREEN_E"Opened"WHITE_E"";
		}
		format(string, sizeof(string), ""WHITE_E"%s%d (Business)\t%s\t%s\t%s\n", string, i, BusinessData[i][bizName], GetLocation(BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]), status);
		count++;
	}
	if (!count)
		return SendErrorMessage(playerid, "Pemain ini tidak mempunyai sebarang hartanah.");
	
	strcat(header, string);
	new str[400];
	format(str, sizeof(str), ""WHITE_E"%s Properties", ReturnName(otherid, 0));
	Dialog_Show(playerid, PropertiesMenu, DIALOG_STYLE_TABLIST_HEADERS, str, header, "Tutup", "");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s telah memeriksa hartanah milik %s.", ReturnName(playerid, 0), ReturnName(otherid, 0));
    return 1;
}

CMD:get(playerid, params[])
{
    new otherid;

	if (sscanf(params, "u", otherid))
 	{
	 	SendUsageMessage(playerid, "/get [playerid]");
		return 1;
	}

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsPlayerSpawned(otherid))
		return SendErrorMessage(playerid, "You can't get a player that's not spawned.");

	if(PlayerData[playerid][pAdmin] < PlayerData[otherid][pAdmin])
        return SendErrorMessage(playerid, "You can't get admin higher than you.");

	SendPlayerToPlayer(otherid, playerid);

	SendInfoMessage(otherid, "%s telah menarik anda ke posisi-nya.", ReturnName(playerid, 0));

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s telah menarik %s ke posisi-nya.", ReturnName(playerid, 0), ReturnName(otherid, 0));
    return 1;
}

CMD:gotoco(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new len = strlen(params);

	for (new i = 0; i < len; i++) { if (params[i] == ',') { params[i] = ' '; } }

	new Float: pos[3];

	if(sscanf(params, "fff", pos[0], pos[1], pos[2])) return SendErrorMessage(playerid, "/gotoco [x coordinate] [y coordinate] [z coordinate]");
	
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return 1;
}

CMD:goto(playerid, params[])
{
	static
	    id,
	    type[24],
		string[64];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", id))
 	{
	 	SendUsageMessage(playerid, "/goto [player or name]");
		SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} spawn, prison, house, business, entrance, job, gate, interior, car");
		return 1;
	}
    if (id == INVALID_PLAYER_ID)
	{
	    if (sscanf(params, "s[24]S()[64]", type, string))
		{
		    SendUsageMessage(playerid, "/goto [player or name]");
			SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} spawn, prison, house, business, entrance, job, gate, interior");
			return 1;
	    }
	    if (!strcmp(type, "spawn", true)) {
	        SetDefaultSpawn(playerid);

	        return SendServerMessage(playerid, "You have teleported to the default spawn.");
		}
		else if (!strcmp(type, "prison", true))
		{
	        SetPlayerPos(playerid, 283.5930, 1413.3511, 10.4078);
	        SetPlayerFacingAngle(playerid, 180.0000);

	        SetPlayerInterior(playerid, 0);
	        SetPlayerVirtualWorld(playerid, 0);

	        return SendServerMessage(playerid, "You have teleported to the prison facility.");
		}
		//
		else if (!strcmp(type, "house", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [house] [house ID]");

			if ((id < 0 || id >= MAX_HOUSES) || !HouseData[id][houseExists])
			    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

		    SetPlayerPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
		    SetPlayerInterior(playerid, HouseData[id][houseExterior]);

			SetPlayerVirtualWorld(playerid, HouseData[id][houseExteriorVW]);
		    SendServerMessage(playerid, "You have teleported to house ID: %d.", id);
		    return 1;
		}
		else if (!strcmp(type, "business", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [business] [business ID]");

			if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
			    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

		    SetPlayerPos(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
		    SetPlayerInterior(playerid, BusinessData[id][bizExterior]);

			SetPlayerVirtualWorld(playerid, BusinessData[id][bizExteriorVW]);
		    SendServerMessage(playerid, "You have teleported to business ID: %d.", id);
		    return 1;
		}
		else if (!strcmp(type, "entrance", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [entrance] [entrance ID]");

			if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
			    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

		    SetPlayerPos(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);
		    SetPlayerInterior(playerid, EntranceData[id][entranceExterior]);

			SetPlayerVirtualWorld(playerid, EntranceData[id][entranceExteriorVW]);
		    SendServerMessage(playerid, "You have teleported to entrance ID: %d.", id);
		    return 1;
		}
		else if (!strcmp(type, "job", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [job] [job ID]");

			if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
			    return SendErrorMessage(playerid, "You have specified an invalid job ID.");

		    SetPlayerPos(playerid, JobData[id][jobPos][0], JobData[id][jobPos][1], JobData[id][jobPos][2]);
		    SetPlayerInterior(playerid, JobData[id][jobInterior]);

			SetPlayerVirtualWorld(playerid, JobData[id][jobWorld]);
		    SendServerMessage(playerid, "You have teleported to job ID: %d.", id);
		    return 1;
		}
		else if (!strcmp(type, "gate", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [gate] [gate ID]");

			if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
			    return SendErrorMessage(playerid, "You have specified an invalid gate ID.");

		    SetPlayerPos(playerid, GateData[id][gatePos][0] - (2.5 * floatsin(-GateData[id][gatePos][3], degrees)), GateData[id][gatePos][1] - (2.5 * floatcos(-GateData[id][gatePos][3], degrees)), GateData[id][gatePos][2]);
		    SetPlayerInterior(playerid, GateData[id][gateInterior]);

			SetPlayerVirtualWorld(playerid, GateData[id][gateWorld]);
		    SendServerMessage(playerid, "You have teleported to gate ID: %d.", id);
		    return 1;
		}
		else if (!strcmp(type, "car", true))
		{
		    if (sscanf(string, "d", id))
		        return SendUsageMessage(playerid, "/goto [car] [car ID]");

			if (id < 1 || id > MAX_VEHICLES || !IsValidVehicle(id))
				return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

			static
				Float:x,
				Float:y,
				Float:z;

			GetVehiclePos(id, x, y, z);
			SetPlayerPos(playerid, x, y - 2, z + 2);
			return 1;
		}
		else if (!strcmp(type, "interior", true))
		{
		    static
		        str[1536];

			str[0] = '\0';

			for (new i = 0; i < sizeof(g_arrInteriorData); i ++) {
			    strcat(str, g_arrInteriorData[i][e_InteriorName]);
			    strcat(str, "\n");
		    }
		    Dialog_Show(playerid, TeleportInterior, DIALOG_STYLE_LIST, "Teleport: Interior List", str, "Select", "Cancel");
		    return 1;
		}
	    else return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");
	}
	if (!IsPlayerSpawned(id))
		return SendErrorMessage(playerid, "You can't teleport to a player that's not spawned.");

	SendPlayerToPlayer(playerid, id);

	SendServerMessage(playerid, "You have teleported to %s.", ReturnName(id, 0));
	return 1;
}

CMD:send(playerid, params[])
{
	static
	    userid,
	    type[24];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[32]", userid, type))
 	{
	 	SendUsageMessage(playerid, "/send [player] [name]");
		SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} spawn, prison");
		return 1;
	}
    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

 	if (!strcmp(type, "spawn", true))
	 {
  		SetDefaultSpawn(userid);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has send %s to default spawn.", ReturnName(playerid, 0), ReturnName(userid, 0));
		SendInfoMessage(userid, "%s has teleported you to the default spawn.", ReturnName(playerid, 0));
	}
	else if (!strcmp(type, "prison", true))
	{
		SetPlayerPos(playerid, 283.5930, 1413.3511, 10.4078);
  		SetPlayerFacingAngle(playerid, 180.0000);

		SetPlayerInterior(playerid, 0);
  		SetPlayerVirtualWorld(playerid, 0);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has send %s to prison facility.", ReturnName(playerid, 0), ReturnName(userid, 0));
		SendInfoMessage(userid, "%s has teleported you to the prison facility.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:bring(playerid, params[])
{
	static
	    userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/bring [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!IsPlayerSpawned(userid))
		return SendErrorMessage(playerid, "You can't teleport a player that's not spawned.");

	SendPlayerToPlayer(userid, playerid);
	SendServerMessage(playerid, "You have teleported %s to you.", ReturnName(userid, 0));
	return 1;
}

CMD:setinterior(playerid, params[])
{
	static
		userid,
	    interior;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, interior))
		return SendUsageMessage(playerid, "/setinterior [playerid/name] [interior]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	SetPlayerInterior(userid, interior);
	PlayerData[userid][pInterior] = interior;

	SendServerMessage(userid, "%s has set your interior to %d.", ReturnName(playerid, 0), interior);
	return 1;
}

CMD:setvw(playerid, params[])
{
	static
		userid,
	    world;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, world))
		return SendUsageMessage(playerid, "/setvw [playerid/name] [world]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	SetPlayerVirtualWorld(userid, world);
	PlayerData[userid][pWorld] = world;

	SendServerMessage(userid, "%s has set your virtual world to %d.", ReturnName(playerid, 0), world);
	return 1;
}

CMD:atalk(playerid, params[])
{
	static
	    userid,
	    text[128];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[128]", userid, text))
		return SendUsageMessage(playerid, "/atalk [playerid/name] [message]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	SendClientMessageEx(userid, COLOR_YELLOW, "[ADMIN]: %s says: %s", ReturnName(playerid, 0), text);

	if (playerid != userid) {
		SendClientMessageEx(playerid, COLOR_YELLOW, "[ADMIN]: %s says: %s", ReturnName(playerid, 0), text);
	}
	return 1;
}

CMD:sendto(playerid, params[])
{
	static
	    userid,
	    targetid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "uu", userid, targetid))
	    return SendUsageMessage(playerid, "/sendto [playerid/name] [playerid/name]");

	if (userid == INVALID_PLAYER_ID || targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "The specified user(s) are not connected.");

	SendPlayerToPlayer(userid, targetid);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has teleported %s to %s.",  ReturnName(playerid, 0), ReturnName(userid, 0), ReturnName(targetid));
	SendServerMessage(userid, "%s has teleported you to %s.", ReturnName(playerid, 0), ReturnName(targetid));
	return 1;
}

CMD:unban(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params) || strlen(params) > 24)
	{
		SendUsageMessage(playerid, "/unban [username]");
		SendClientMessage(playerid, COLOR_LIGHTRED, "[NOTE]:{FFFFFF} Type \"/username\" to resolve the username from a character's name.");
	}
	else
	{
	    Blacklist_Remove(params);

	    SendServerMessage(playerid, "You have unbanned \"%s\" successfully.", params);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has unbanned account \"%s\".", ReturnName(playerid, 0), params);

	    Log_Write("logs/ban_log.txt", "[%s] %s has unbanned account \"%s\".", ReturnDate(), ReturnName(playerid, 0), params);
	}
	return 1;
}

CMD:blacklist(playerid, params[])
{
	static
		type[24],
		reason[400];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "s[24]s[128]s[128]", type, params, reason))
 	{
	 	SendUsageMessage(playerid, "/blacklist [name] [parameter] [reason]");
	 	SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} ban, banip, unbanip");
	 	return 1;
	}
	if (!strcmp(type, "ban", true))
	{
	    if (!IsValidPlayerName(params))
	        return SendErrorMessage(playerid, "The name you've entered is not in the correct format.");

		foreach (new i : Player) if (!strcmp(PlayerData[i][pUsername], params) || !strcmp(ReturnName(i), params, true)) {
		    KickEx(i);
		}
		Blacklist_Add("0.0.0.0", params, PlayerData[playerid][pUsername], reason);

	    SendServerMessage(playerid, "You have banned \"%s\" successfully.", params);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has banned \"%s\" reason %s.", ReturnName(playerid, 0), params, reason);

	    Log_Write("logs/ban_log.txt", "[%s] %s has banned \"%s\" reason %s.", ReturnDate(), ReturnName(playerid, 0), params, reason);

		SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has blacklisted %s", ReturnName(playerid, 0), params);
		SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);
	}
	else if (!strcmp(type, "banip", true))
	{
	    if (!IsAnIP(params))
	        return SendErrorMessage(playerid, "The IP address you've entered is not in the correct format.");

		foreach (new i : Player) if (!strcmp(PlayerData[i][pIP], params)) {
		    KickEx(i);
		}
		Blacklist_Add(params, "", PlayerData[playerid][pUsername], reason);

	    SendServerMessage(playerid, "You have banned IP \"%s\" successfully.", params);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has banned IP \"%s\" reason %s.", ReturnName(playerid, 0), params, reason);

	    Log_Write("logs/ban_log.txt", "[%s] %s has banned IP \"%s\" reason %s.", ReturnDate(), ReturnName(playerid, 0), params, reason);
	}
	else if (!strcmp(type, "unbanip", true))
	{
	    if (!IsAnIP(params))
	        return SendErrorMessage(playerid, "The IP address you've entered is not in the correct format.");

		Blacklist_RemoveIP(params);

	    SendServerMessage(playerid, "You have unbanned IP \"%s\" successfully.", params);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has unbanned IP \"%s\" reason %s.", ReturnName(playerid, 0), params, reason);

	    Log_Write("logs/ban_log.txt", "[%s] %s has unbanned IP \"%s\" reason %s.", ReturnDate(), ReturnName(playerid, 0), params, reason);
	}
	return 1;
}

CMD:getip(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/getip [playerid/name]");

	if(PlayerData[playerid][pAdmin] < PlayerData[userid][pAdmin])
        return SendErrorMessage(playerid, "You can't get ip admin higher than you.");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has get ip address %s.",  ReturnName(playerid, 0), ReturnName(userid, 0));
	SendServerMessage(playerid, "%s's IP address is %s.", ReturnName(userid, 0), PlayerData[userid][pIP]);
	return 1;
}

CMD:togooc(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!g_StatusOOC)
	{
		SendClientMessageToAllEx(COLOR_GREEN, "{00ff3c}OOC Global Chat has been disabled by admin!");
	    g_StatusOOC = true;
	}
	else
	{
	    SendClientMessageToAllEx(COLOR_GREEN, "{00ff3c}OOC Global Chat has been enabled by admin!");
	    g_StatusOOC = false;
	}
	return 1;
}

CMD:health(playerid, params[])
{
	static
		userid,
	    Float:amount;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "uf", userid, amount))
		return SendUsageMessage(playerid, "/health [playerid/name] [amount]");

	if(PlayerData[playerid][pAdmin] < PlayerData[userid][pAdmin])
        return SendErrorMessage(playerid, "You can't set health admin higher than you.");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	SetPlayerHealthEx(userid, amount);
	SendServerMessage(userid, "%s has set your health to %.2f.", ReturnName(userid, 0), amount);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set %s health to %.2f.",  ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	return 1;
}

CMD:armor(playerid, params[])
{
	static
		userid,
	    Float:amount;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "uf", userid, amount))
		return SendUsageMessage(playerid, "/armor [playerid/name] [amount]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    SetPlayerArmourEx(userid, amount);
	SendServerMessage(userid, "%s has set your armor to %.2f.", ReturnName(userid, 0), amount);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set %s armor to %.2f.",  ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	return 1;
}

CMD:resetweps(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/resetweps [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	ResetWeapons(userid);
	SendInfoMessage(userid, "%s has reset your weapons.", ReturnName(playerid, 0));
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has reset weapon %s.",  ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:arepair(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (vehicleid > 0 && isnull(params))
	{
		RepairVehicle(vehicleid);
		SetVehicleHealth(vehicleid, 1000);
		SendServerMessage(playerid, "You have repaired your current vehicle.");
	}
	else
	{
		if (sscanf(params, "d", vehicleid))
	    	return SendUsageMessage(playerid, "/arepair [vehicle ID]");

		else if (!IsValidVehicle(vehicleid))
	    	return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

		RepairVehicle(vehicleid);
		SetVehicleHealth(vehicleid, 1000);
		SendServerMessage(playerid, "You have repaired vehicle ID: %d.", vehicleid);
	}
	return 1;
}

CMD:respawncar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (vehicleid > 0 && isnull(params))
	{
		Car_Save(vehicleid);
		RespawnVehicle(vehicleid);
		SendServerMessage(playerid, "You have respawned vehicle ID: %d.", vehicleid);
	}
	else
	{
		if (sscanf(params, "d", vehicleid))
	    	return SendUsageMessage(playerid, "/respawncar [vehicle ID]");

		if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
			return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

		Car_Save(vehicleid);
		RespawnVehicle(vehicleid);
		SendServerMessage(playerid, "You have respawned vehicle ID: %d.", vehicleid);
	}
	return 1;
}

CMD:setplate(playerid, params[])
{
	static
	    id = 0,
		plate[32];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]", id, plate))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);

		    if (sscanf(params, "s[24]", plate))
		        return SendUsageMessage(playerid, "/setplate [plate]");

			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
			{
				if(id == CarData[i][carVehicle])
				{
					format(CarData[i][carPlate], 32, "%s", plate);

					Car_Save(i);

					SendServerMessage(playerid, "You have change plate vehicle ID: %d to %s.", i, plate);
				}
			}
			return 1;
		}
		else return SendUsageMessage(playerid, "/setplate [vehicle id] [plate]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
	{
		if(id == CarData[i][carVehicle])
		{
			format(CarData[i][carPlate], 32, "%s", plate);

			Car_Save(i);

			SendServerMessage(playerid, "You have change plate vehicle ID: %d to %s.", id, plate);
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has changed plate vehicle id %d to %s.",  ReturnName(playerid, 0), i, plate);
		}
	}
	return 1;
}

CMD:setsiren(playerid, params[])
{
	static
	    id = 0,
		status;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "dd", id, status))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);

		    if (sscanf(params, "d", status))
		        return SendUsageMessage(playerid, "/setsiren [0/1]");

			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
			{
				if(id == CarData[i][carVehicle])
				{
					CarData[i][carSiren] = status;

					Car_Save(i);

					SendServerMessage(playerid, "You have set the siren of vehicle ID: "YELLOW_E"%d"WHITE_E" to %s"WHITE_E".", i, (CarData[i][carSiren] == 1) ? (""GREEN_E"Enabled") : (""RED_E"Disabled"));
				}
			}
			return 1;
		}
		else return SendUsageMessage(playerid, "/setsiren [vehicle id] [0/1]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
	{
		if(id == CarData[i][carVehicle])
		{
			CarData[i][carSiren] = status;

			Car_Save(i);

			SendServerMessage(playerid, "You have set the siren of vehicle ID: "YELLOW_E"%d"WHITE_E" to %s"WHITE_E".", i, (CarData[i][carSiren] == 1) ? (""GREEN_E"Enabled") : (""RED_E"Disabled"));
		}
	}
	return 1;
}

CMD:setgovcar(playerid, params[])
{
	static
	    id = 0,
		status;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "dd", id, status))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);

		    if (sscanf(params, "d", status))
		        return SendUsageMessage(playerid, "/setgovcar [0/1]");

			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
			{
				if(id == CarData[i][carVehicle])
				{
					CarData[i][carGov] = status;

					Car_Save(i);

					SendServerMessage(playerid, "You have set the gov status of vehicle ID: "YELLOW_E"%d"WHITE_E" to %s"WHITE_E".", i, (CarData[i][carGov] == 1) ? (""GREEN_E"Enabled") : (""RED_E"Disabled"));
				}
			}
			return 1;
		}
		else return SendUsageMessage(playerid, "/setgovcar [vehicle id] [0/1]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
	{
		if(id == CarData[i][carVehicle])
		{
			CarData[i][carGov] = status;

			Car_Save(i);

			SendServerMessage(playerid, "You have set the gov status of vehicle ID: "YELLOW_E"%d"WHITE_E" to %s"WHITE_E".", i, (CarData[i][carGov] == 1) ? (""GREEN_E"Enabled") : (""RED_E"Disabled"));
		}
	}
	return 1;
}


CMD:bringcar(playerid, params[])
{
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", vehicleid))
	    return SendUsageMessage(playerid, "/bringcar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehicleid, x + 2, y - 2, z);

 	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	return 1;
}

CMD:entercar(playerid, params[])
{
	new vehicleid, seatid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", vehicleid))
	    return SendUsageMessage(playerid, "/entercar [veh]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	seatid = GetAvailableSeat(vehicleid, 0);

	if (seatid == -1)
	    return SendErrorMessage(playerid, "There are no seats left to enter.");
	
	PutPlayerInVehicle(playerid, vehicleid, seatid);
	return 1;
}

CMD:respawncars(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new count;

	for (new i = 1; i != MAX_VEHICLES; i ++)
	{
	    if (IsValidVehicle(i) && GetVehicleDriver(i) == INVALID_PLAYER_ID)
	    {
			Car_Save(i);
	        RespawnVehicle(i);
			count++;
		}
	}
	if (!count)
	    return SendErrorMessage(playerid, "There are no vehicles to respawn.");

	SendServerMessage(playerid, "You have respawned %d unoccupied vehicles.", count);
	return 1;
}

CMD:respawnnear(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new count;

	for (new i = 1; i != MAX_VEHICLES; i ++)
	{
	    static
	        Float:fX,
	        Float:fY,
	        Float:fZ;

	    if (IsValidVehicle(i) && GetVehicleDriver(i) == INVALID_PLAYER_ID)
		{
			GetVehiclePos(i, fX, fY, fZ);

			if (IsPlayerInRangeOfPoint(playerid, 50.0, fX, fY, fZ))
			{
				Car_Save(i);
		        RespawnVehicle(i);
				count++;
			}
		}
	}
	if (!count)
	    return SendErrorMessage(playerid, "There are no closest vehicles to respawn.");

	SendServerMessage(playerid, "You have respawned the %d closest vehicles.", count);
	return 1;
}

CMD:veh(playerid, params[])
{
	static
	    model[32],
		color1,
		color2;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "s[32]I(-1)I(-1)", model, color1, color2))
	    return SendUsageMessage(playerid, "/veh [model id/name] <color 1> <color 2>");

	if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return SendErrorMessage(playerid, "Invalid model ID.");

	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:a,
		vehicleid;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	vehicleid = CreateVehicle(model[0], x, y + 2, z, a, color1, color2, 0);

	if (GetPlayerInterior(playerid) != 0)
	    LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

	if (GetPlayerVirtualWorld(playerid) != 0)
		SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));

	if (IsABoat(vehicleid) || IsAPlane(vehicleid) || IsAHelicopter(vehicleid))
	    PutPlayerInVehicle(playerid, vehicleid, 0);

	ResetVehicle(vehicleid);

	CoreVehicles[vehicleid][vehTemporary] = true; 
	CarData[vehicleid][carFuel] = 100;
	SetEngineStatus(vehicleid, true);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SetVehicleNumberPlate(vehicleid, "ADMIN");
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has spawned a %s (%d, %d).",  ReturnName(playerid, 0), ReturnVehicleModelName(model[0]), color1, color2);
	return 1;
}

CMD:destroyveh(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!isnull(params) && !strcmp(params, "all", true))
	{
	    for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && CoreVehicles[i][vehTemporary])
		{
	        CoreVehicles[i][vehTemporary] = false;

	        DestroyVehicle(i);

	        ResetVehicle(i);
	    }
	    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed the temporary vehicles.", ReturnName(playerid, 0));
	    return 1;
	}
	else if (IsPlayerInAnyVehicle(playerid))
	{
	    new vehicleid = GetPlayerVehicleID(playerid);

	    if (CoreVehicles[vehicleid][vehTemporary])
		{
	        CoreVehicles[vehicleid][vehTemporary] = false;
	        DestroyVehicle(vehicleid);

	        ResetVehicle(vehicleid);
	        SendServerMessage(playerid, "You have destroyed this admin vehicle.");
		}
		else
		{
		    SendErrorMessage(playerid, "You cannot destroy a non-temporary vehicle.");
		}
	}
	return 1;
}

CMD:givewep(playerid, params[])
{
	static
	    userid,
	    weaponid,
	    ammo;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "udI(500)", userid, weaponid, ammo))
	    return SendUsageMessage(playerid, "/givewep [playerid/name] [weaponid] [ammo]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You cannot give weapons to disconnected players.");

	if (!IsPlayerSpawned(userid))
	    return SendErrorMessage(playerid, "You cannot give weapons to unspawned players.");

	if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		return SendErrorMessage(playerid, "You have specified an invalid weapon.");

	GiveWeaponToPlayer(userid, weaponid, ammo);
	SendServerMessage(userid, "%s has gave you a %s with %d ammo.", ReturnName(playerid, 0), ReturnWeaponName(weaponid), ammo);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has gave %s a %s with %d ammo.", ReturnName(playerid, 0), ReturnName(userid, 0), ReturnWeaponName(weaponid), ammo);
	return 1;
}

CMD:setplayer(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	static
	    userid,
	    type[16],
	    amount[32];

	if (sscanf(params, "us[16]S()[32]", userid, type, amount))
 	{
	 	SendUsageMessage(playerid, "/setplayer [playerid/name] [name]");
	 	SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} gender, birthdate, origin, bank, savings, hunger, thirst, score");
		SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} job, warrants, channel, stress");
		return 1;
	}
	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!strcmp(type, "gender", true))
	{
	    if (isnull(amount) || strval(amount) < 1 || strval(amount) > 2)
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [gender] [1: male - 2: female]");

		PlayerData[userid][pGender] = strval(amount);

		if (PlayerData[userid][pGender] == 1)
		{
			SendServerMessage(userid, "%s has set your gender to male.", ReturnName(playerid, 0));
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set gender %s to male", ReturnName(playerid, 0), ReturnName(userid, 0));
		}
		else if (PlayerData[userid][pGender] == 2)
		{
			SendServerMessage(userid, "%s has set your gender to female.", ReturnName(playerid, 0));
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set gender %s to female", ReturnName(playerid, 0), ReturnName(userid, 0));
		}
	}
	else if (!strcmp(type, "birthdate", true))
	{
	    if (isnull(amount) || strlen(amount) > 24)
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [birthdate] [birth date]");

		format(PlayerData[userid][pBirthdate], 24, amount);
		SendServerMessage(userid, "%s has set your birthdate to \"%s\".", ReturnName(playerid, 0), amount);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set birthdate %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	else if (!strcmp(type, "origin", true))
	{
	    if (isnull(amount) || strlen(amount) > 32)
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [origin] [new origin]");

		format(PlayerData[userid][pOrigin], 32, amount);
		SendServerMessage(userid, "%s has set your origin to \"%s\".", ReturnName(playerid, 0), amount);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set origin %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	else if (!strcmp(type, "bank", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [bank] [bank funds]");

		PlayerData[userid][pBankMoney] = strval(amount);
		SendServerMessage(userid, "%s has set your bank money to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount)));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set bank money %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), FormatNumber(strval(amount)));
	}
	else if (!strcmp(type, "savings", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [savings] [savings funds]");

		PlayerData[userid][pSavings] = strval(amount);
		SendServerMessage(userid, "%s has set your savings to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount)));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set savings %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), FormatNumber(strval(amount)));
	}
	else if (!strcmp(type, "hunger", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [hunger] [amount]");

		if (strval(amount) < 0 || strval(amount) > 1000)
		    return SendErrorMessage(playerid, "You can't specify an amount below 0 or above 1,000.");

		PlayerData[userid][pHunger] = strval(amount);
		SendServerMessage(userid, "%s has set your hunger to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount), ""));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set hunger %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	else if (!strcmp(type, "stress", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [hunger] [amount]");

		if (strval(amount) < 0 || strval(amount) > 1000)
		    return SendErrorMessage(playerid, "You can't specify an amount below 0 or above 1,000.");

		PlayerData[userid][pStress] = strval(amount);
		SendServerMessage(userid, "%s has set your stress to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount), ""));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set stress %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	else if (!strcmp(type, "thirst", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [thirst] [amount]");

        if (strval(amount) < 0 || strval(amount) > 1000)
		    return SendErrorMessage(playerid, "You can't specify an amount below 0 or above 1,000.");

		PlayerData[userid][pThirst] = strval(amount);
		SendServerMessage(userid, "%s has set your thirst to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount), ""));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set thirst %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	else if (!strcmp(type, "score", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [score] [amount]");

		PlayerData[userid][pScore] = strval(amount);
		SendServerMessage(userid, "%s has set your score to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount), ""));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set score %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
    else if (!strcmp(type, "job", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [job] [amount]");

		if (strval(amount) < 0 || strval(amount) > 9)
		    return SendErrorMessage(playerid, "You have specified an invalid job ID.");

		PlayerData[userid][pJob] = strval(amount);
		SendServerMessage(userid, "%s has set your job to %s.", ReturnName(playerid, 0), Job_GetName(PlayerData[userid][pJob]));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set job %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), Job_GetName(PlayerData[userid][pJob]));
	}
    else if (!strcmp(type, "warrants", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [warrants] [amount]");

		PlayerData[userid][pWarrants] = strval(amount);
		SendServerMessage(userid, "%s has set your warrants to %s.", ReturnName(playerid, 0), FormatNumber(strval(amount), ""));
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set warrants %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), FormatNumber(strval(amount), ""));
	}
	else if (!strcmp(type, "channel", true))
	{
	    if (isnull(amount))
	        return SendUsageMessage(playerid, "/setplayer [playerid/name] [channel] [radio channel]");

		PlayerData[userid][pChannel] = strval(amount);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set channel %s to %s.", ReturnName(playerid, 0), ReturnName(userid, 0), amount);
	}
	return 1;
}

CMD:baninfo(playerid, params[])
{
    static
		string[128];

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params) || strlen(params) > 24)
	{
		SendUsageMessage(playerid, "/baninfo [username]");
		SendClientMessage(playerid, COLOR_LIGHTRED, "[NOTE]:{FFFFFF} Type \"/username\" to resolve the username from a character's name.");
	}
	else
	{
	    format(string, sizeof(string), "SELECT * FROM `blacklist` WHERE `Username` = '%s'", SQL_ReturnEscaped(params));
	    mysql_tquery(g_iHandle, string, "OnBanLookup", "ds", playerid, params);
	}
	return 1;
}

CMD:factionmod(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/factionmod [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (PlayerData[userid][pFactionMod])
	{
	    PlayerData[userid][pFactionMod] = false;

	    SendInfoMessage(playerid, "You have taken away %s's faction management status.", ReturnName(userid, 0));
		SendInfoMessage(userid, "%s has kicked you from the faction management team.", ReturnName(playerid, 0));
	}
	else
	{
	    PlayerData[userid][pFactionMod] = true;

        SendInfoMessage(playerid, "You have invited %s to the faction management team.", ReturnName(userid, 0));
		SendInfoMessage(userid, "%s has invited you to the faction management team.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:setname(playerid, params[])
{
	static
	    userid,
	    newname[24],
		query[128];

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[24]", userid, newname))
	    return SendUsageMessage(playerid, "/setname [playerid/name] [new name]");

	if (userid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (!PlayerData[userid][pLogged] && !PlayerData[userid][pCharacter])
	    return SendErrorMessage(playerid, "That player hasn't set a character yet.");

	if (!IsValidPlayerName(newname))
	    return SendErrorMessage(playerid, "You have specified an invalid name format.");

	foreach (new i : Player) if (!strcmp(ReturnName(i), newname)) {
	    return SendErrorMessage(playerid, "The specified name is in use.");
	}
	format(query, sizeof(query), "SELECT `ID` FROM `characters` WHERE `Character` = '%s'", SQL_ReturnEscaped(newname));
	mysql_tquery(g_iHandle, query, "OnNameChange", "dds", playerid, userid, newname);

	return 1;
}

CMD:clearchat(playerid, params[])
{
	ClearChat(playerid);
	return 1;
}

CMD:createhouse(playerid, params[])
{
	static
	    price,
	    id,
	    address[32];

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[32]", price, address))
	    return SendUsageMessage(playerid, "/createhouse [price] [address]");

	for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && !strcmp(HouseData[i][houseAddress], address, true)) {
	    return SendErrorMessage(playerid, "The address \"%s\" is already in use (ID: %d).", address, i);
	}
	id = House_Create(playerid, address, price);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for houses.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created house ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroyhouse(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyhouse [house id]");

	if ((id < 0 || id >= MAX_HOUSES) || !HouseData[id][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	House_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed house ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:buy(playerid, params[])
{
	static
		id = -1;

	if ((id = House_Nearest(playerid)) != -1)
	{
		if (House_GetCount(playerid) >= MAX_OWNABLE_HOUSES)
			return SendErrorMessage(playerid, "You can only own %d houses at a time.", MAX_OWNABLE_HOUSES);

		if (HouseData[id][houseOwner] != 0)
		    return SendErrorMessage(playerid, "This house is already owned at the moment.");

		if (HouseData[id][housePrice] > GetMoney(playerid))
		    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

	    HouseData[id][houseOwner] = GetPlayerSQLID(playerid);

		House_Refresh(id);
		House_Save(id);

	    GiveMoney(playerid, -HouseData[id][housePrice]);
	    SendServerMessage(playerid, "You have purchased \"%s\" for %s!", HouseData[id][houseAddress], FormatNumber(HouseData[id][housePrice]));

	    Log_Write("logs/house_log.txt", "[%s] %s has purchased house ID: %d for %s.", ReturnDate(), ReturnName(playerid), id, FormatNumber(HouseData[id][housePrice]));
	}
	else if ((id = Business_Nearest(playerid)) != -1)
	{
	    if (Business_GetCount(playerid) >= MAX_OWNABLE_BUSINESSES)
			return SendErrorMessage(playerid, "You can only own %d businesses at a time.", MAX_OWNABLE_BUSINESSES);

		if (BusinessData[id][bizOwner] != 0)
		    return SendErrorMessage(playerid, "This business is already owned at the moment.");

		if (BusinessData[id][bizPrice] > GetMoney(playerid))
		    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

	    BusinessData[id][bizOwner] = GetPlayerSQLID(playerid);

		Business_Refresh(id);
		Business_Save(id);

	    GiveMoney(playerid, -BusinessData[id][bizPrice]);
	    SendServerMessage(playerid, "You have purchased \"%s\" for %s!", BusinessData[id][bizName], FormatNumber(BusinessData[id][bizPrice]));

	    Log_Write("logs/biz_log.txt", "[%s] %s has purchased business ID: %d for %s.", ReturnDate(), ReturnName(playerid), id, FormatNumber(BusinessData[id][bizPrice]));
	}
	return 1;
}

CMD:abandon(playerid, params[])
{
	static
	    id = -1;

    if (!IsPlayerInAnyVehicle(playerid) && (id = House_Nearest(playerid)) != -1 && House_IsOwner(playerid, id))
	{
	    if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
	    {
	        SendUsageMessage(playerid, "/abandon [confirm]");
	        SendInfoMessage(playerid, "You are about to abandon your house with no refund.");
		}
		else if (!strcmp(params, "confirm", true))
		{
			HouseData[id][houseOwner] = 0;

			House_Refresh(id);
			House_Save(id);

			SendServerMessage(playerid, "You have abandoned your house: %s.", HouseData[id][houseAddress]);
			Log_Write("logs/house_log.txt", "[%s] %s has abandoned house ID: %d.", ReturnDate(), ReturnName(playerid), id);
		}
	}
	else if (!IsPlayerInAnyVehicle(playerid) && (id = Business_Nearest(playerid)) != -1 && Business_IsOwner(playerid, id))
	{
	    if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
	    {
	        SendUsageMessage(playerid, "/abandon [confirm]");
	        SendInfoMessage(playerid, "You are about to abandon your business with no refund.");
		}
		else if (!strcmp(params, "confirm", true))
		{
			BusinessData[id][bizOwner] = 0;

			Business_Refresh(id);
			Business_Save(id);

			SendServerMessage(playerid, "You have abandoned your business: %s.", BusinessData[id][bizName]);
			Log_Write("logs/biz_log.txt", "[%s] %s has abandoned business ID: %d.", ReturnDate(), ReturnName(playerid), id);
		}
	}
	else if ((id = Car_Inside(playerid)) != -1 && Car_IsOwner(playerid, id))
	{
	    if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
	    {
	        SendUsageMessage(playerid, "/abandon [confirm]");
	        SendInfoMessage(playerid, "You are about to abandon your vehicle with no refund.");
		}
		else if (CarData[id][carImpounded] != -1)
    		return SendErrorMessage(playerid, "This vehicle is impounded and you can't use it.");

		else if (!strcmp(params, "confirm", true))
		{
			new
			    model = CarData[id][carModel];

			Car_Delete(id);

			SendServerMessage(playerid, "You have abandoned your %s.", ReturnVehicleModelName(model));
			Log_Write("logs/car_log.txt", "[%s] %s has abandoned their %s.", ReturnDate(), ReturnName(playerid), ReturnVehicleModelName(model));
		}
	}
	else SendErrorMessage(playerid, "You are not in range of anything you can abandon.");
	return 1;
}

CMD:switch(playerid, params[])
{
	static
	    id = -1;

	if ((id = House_Inside(playerid)) != -1)
	{
		if (!HouseData[id][houseLights])
		{
		    foreach (new i : Player) if (House_Inside(i) == id) {
		        PlayerTextDrawHide(i, LampTD[i]);
		    }
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s flicks the light switch on.", ReturnName(playerid, 0));
		    HouseData[id][houseLights] = true;
		}
		else
		{
		    foreach (new i : Player) if (House_Inside(i) == id) {
		        PlayerTextDrawShow(i, LampTD[i]);
		    }
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s flicks the light switch off.", ReturnName(playerid, 0));
		    HouseData[id][houseLights] = false;
		}
	}
	else {
	    SendErrorMessage(playerid, "You must be in a house to use the lights.");
	}
	return 1;
}

CMD:lock(playerid, params[])
{
	static
	    id = -1;

	if (!IsPlayerInAnyVehicle(playerid) && (id = (House_Inside(playerid) == -1) ? (House_Nearest(playerid)) : (House_Inside(playerid))) != -1 && House_IsOwner(playerid, id))
	{
		if (!HouseData[id][houseLocked])
		{
			HouseData[id][houseLocked] = true;
			House_Save(id);

			SendServerMessage(playerid, "You have locked your house!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		else
		{
			HouseData[id][houseLocked] = false;
			House_Save(id);

			SendServerMessage(playerid, "You have unlocked your house!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
	}
	else if (!IsPlayerInAnyVehicle(playerid) && (id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1)
	{
		if (Business_IsOwner(playerid, id))
		{
			if (!BusinessData[id][bizLocked])
			{
				BusinessData[id][bizLocked] = true;
				Business_Save(id);

				SendServerMessage(playerid, "You have locked the business!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
  			else
			{
				BusinessData[id][bizLocked] = false;
				Business_Save(id);

				SendServerMessage(playerid, "You have unlocked the business!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	else if (!IsPlayerInAnyVehicle(playerid) && (id = (Entrance_Inside(playerid) == -1) ? (Entrance_Nearest(playerid)) : (Entrance_Inside(playerid))) != -1)
	{
		if (strlen(EntranceData[id][entrancePass]))
		{
			Dialog_Show(playerid, EntrancePass, DIALOG_STYLE_INPUT, "Entrance Pass", "Please enter the password for this entrance:", "Submit", "Cancel");
		}
	}
	else if ((id = Car_Nearest(playerid)) != -1)
	{
	    static
	        engine,
	        lights,
	        alarm,
	        doors,
	        bonnet,
	        boot,
	        objective;

	    GetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, doors, bonnet, boot, objective);

	    if (Car_IsOwner(playerid, id) || (PlayerData[playerid][pFaction] != -1))
	    {
			if (!CarData[id][carLocked])
			{
				CarData[id][carLocked] = true;
				Car_Save(id);

				SendServerMessage(playerid, "You have locked the vehicle!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

				SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 1, bonnet, boot, objective);
			}
			else
			{
				CarData[id][carLocked] = false;
				Car_Save(id);

				SendServerMessage(playerid, "You have unlocked the vehicle!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

				SetVehicleParamsEx(CarData[id][carVehicle], engine, lights, alarm, 0, bonnet, boot, objective);
			}
		}
	}
	else SendErrorMessage(playerid, "You are not in range of anything you can lock.");
	return 1;
}


CMD:sita(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	static
	    id = -1;

	if (!IsPlayerInAnyVehicle(playerid) && (id = (House_Inside(playerid) == -1) ? (House_Nearest(playerid)) : (House_Inside(playerid))) != -1)
	{
		if (!HouseData[id][houseSita])
		{
			HouseData[id][houseSita] = true;
			House_Save(id);

			SendServerMessage(playerid, "Anda telah menyita rumah ini!");
		}
		else
		{
			HouseData[id][houseSita] = false;
			House_Save(id);

			SendServerMessage(playerid, "Anda telah menyahsita rumah ini!");
		}
	}
	else if (!IsPlayerInAnyVehicle(playerid) && (id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1)
	{
		if (!BusinessData[id][bizSita])
		{
			BusinessData[id][bizSita] = true;
			Business_Save(id);

			SendServerMessage(playerid, "Anda telah menyita business ini!");
		}
		else
		{
			BusinessData[id][bizSita] = false;
			Business_Save(id);

			SendServerMessage(playerid, "Anda telah menyahsita business ini!");
		}
	}
	return 1;
}

CMD:togglespeed(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	static
	    id = -1;

	if ((id = Speed_Nearest(playerid)) != -1)
	{
		if (!SpeedData[id][speedStatus])
		{
			SpeedData[id][speedStatus] = true;
			Speed_Save(id);
			Speed_Refresh(id);

			SendServerMessage(playerid, "Anda telah menghidupkan speedtrap ini!");
		}
		else
		{
			SpeedData[id][speedStatus] = false;
			Speed_Save(id);
			Speed_Refresh(id);

			SendServerMessage(playerid, "Anda telah memdamkan speedtrap ini!");
		}
	}
	return 1;
}

CMD:sell(playerid, params[])
{
	static
	    targetid,
	    type[24],
	    string[128];

	if (sscanf(params, "us[24]S()[128]", targetid, type, string))
	{
	    SendUsageMessage(playerid, "/sell [playerid/name] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} house, business, vehicle");
	    return 1;
	}
	if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
	{
		SendErrorMessage(playerid, "The player is disconnected or not near you.");
		return 1;
	}
	if (targetid == playerid)
	{
		SendErrorMessage(playerid, "You cannot sell to yourself.");
		return 1;
	}
	if (!strcmp(type, "house", true))
	{
		static
		    price,
			houseid = -1;

		if (sscanf(string, "d", price))
			return SendUsageMessage(playerid, "/sell [playerid/name] [house] [price]");

		if (price < 1)
		    return SendErrorMessage(playerid, "The price you've entered cannot below the value of RM1.");

		if ((houseid = House_Nearest(playerid)) != -1 && House_IsOwner(playerid, houseid)) {
			PlayerData[targetid][pHouseSeller] = playerid;
			PlayerData[targetid][pHouseOffered] = houseid;
			PlayerData[targetid][pHouseValue] = price;

		    SendServerMessage(playerid, "You have requested %s to purchase your house (%s).", ReturnName(targetid, 0), FormatNumber(price));
            SendServerMessage(targetid, "%s has offered you their house for %s (type \"/approve house\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		}
		else SendErrorMessage(playerid, "You are not in range of any of your houses.");
	}
	else if (!strcmp(type, "business", true))
	{
		static
		    price,
			bizid = -1;

		if (sscanf(string, "d", price))
			return SendUsageMessage(playerid, "/sell [playerid/name] [business] [price]");

		if (price < 1)
		    return SendErrorMessage(playerid, "The price you've entered cannot below the value of RM1.");

		if ((bizid = Business_Nearest(playerid)) != -1 && Business_IsOwner(playerid, bizid)) {
			PlayerData[targetid][pBusinessSeller] = playerid;
			PlayerData[targetid][pBusinessOffered] = bizid;
			PlayerData[targetid][pBusinessValue] = price;

		    SendServerMessage(playerid, "You have requested %s to purchase your business (%s).", ReturnName(targetid, 0), FormatNumber(price));
            SendServerMessage(targetid, "%s has offered you their business for %s (type \"/approve business\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		}
		else SendErrorMessage(playerid, "You are not in range of any of your businesses.");
	}
	else if (!strcmp(type, "vehicle", true))
	{
		static
		    price,
			carid = -1;

		if (sscanf(string, "d", price))
			return SendUsageMessage(playerid, "/sell [playerid/name] [veh] [price]");

		if (price < 1)
		    return SendErrorMessage(playerid, "The price you've entered cannot below the value of RM1.");

		if ((carid = Car_Inside(playerid)) != -1 && Car_IsOwner(playerid, carid)) {
			PlayerData[targetid][pCarSeller] = playerid;
			PlayerData[targetid][pCarOffered] = carid;
			PlayerData[targetid][pCarValue] = price;

		    SendServerMessage(playerid, "You have requested %s to purchase your %s (%s).", ReturnName(targetid, 0), ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(price));
            SendServerMessage(targetid, "%s has offered you their %s for %s (type \"/approve car\" to accept).", ReturnName(playerid, 0), ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(price));
		}
		else SendErrorMessage(playerid, "You are not inside any of your vehicles.");
	}
	return 1;
}

CMD:approve(playerid, params[])
{
	if (isnull(params))
 	{
	 	SendUsageMessage(playerid, "/approve [name]");
		SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} house, business, car, food, faction, greet, frisk");
		return 1;
	}
	if (!strcmp(params, "house", true) && PlayerData[playerid][pHouseSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pHouseSeller],
	        houseid = PlayerData[playerid][pHouseOffered],
	        price = PlayerData[playerid][pHouseValue];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds to purchase this house.");

		if (House_Nearest(playerid) != houseid)
		    return SendErrorMessage(playerid, "You must be near the house to purchase it.");

		if (!House_IsOwner(sellerid, houseid))
		    return SendErrorMessage(playerid, "This house offer is no longer valid.");

		SendServerMessage(playerid, "You have successfully purchased %s's house for %s.", ReturnName(sellerid, 0), FormatNumber(price));
		SendServerMessage(sellerid, "%s has successfully purchased your house for %s.", ReturnName(playerid, 0), FormatNumber(price));

		HouseData[houseid][houseOwner] = GetPlayerSQLID(playerid);
		House_Save(houseid);

		GiveMoney(playerid, -price);
		GiveMoney(playerid, price);

		Log_Write("logs/offer_log.txt", "[%s] %s (%s) has sold a house to %s (%s) for %s.", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnName(sellerid, 0), PlayerData[sellerid][pIP], FormatNumber(price));

		PlayerData[playerid][pHouseSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pHouseOffered] = -1;
		PlayerData[playerid][pHouseValue] = 0;
	}
	if (!strcmp(params, "business", true) && PlayerData[playerid][pBusinessSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pBusinessSeller],
	        bizid = PlayerData[playerid][pBusinessOffered],
	        price = PlayerData[playerid][pBusinessValue];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds to purchase this business.");

		if (Business_Nearest(playerid) != bizid)
		    return SendErrorMessage(playerid, "You must be near the business to purchase it.");

		if (!Business_IsOwner(sellerid, bizid))
		    return SendErrorMessage(playerid, "This business offer is no longer valid.");

		SendServerMessage(playerid, "You have successfully purchased %s's business for %s.", ReturnName(sellerid, 0), FormatNumber(price));
		SendServerMessage(sellerid, "%s has successfully purchased your business for %s.", ReturnName(playerid, 0), FormatNumber(price));

		BusinessData[bizid][bizOwner] = GetPlayerSQLID(playerid);
		Business_Save(bizid);

		GiveMoney(playerid, -price);
		GiveMoney(playerid, price);

		Log_Write("logs/offer_log.txt", "[%s] %s (%s) has sold a business to %s (%s) for %s.", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnName(sellerid, 0), PlayerData[sellerid][pIP], FormatNumber(price));

		PlayerData[playerid][pBusinessSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pBusinessOffered] = -1;
		PlayerData[playerid][pBusinessValue] = 0;
	}
	if (!strcmp(params, "car", true) && PlayerData[playerid][pCarSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pCarSeller],
	        carid = PlayerData[playerid][pCarOffered],
	        price = PlayerData[playerid][pCarValue];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds to purchase this vehicle.");

		if (Car_Nearest(playerid) != carid)
		    return SendErrorMessage(playerid, "You must be near the vehicle to purchase it.");

		if (!Car_IsOwner(sellerid, carid))
		    return SendErrorMessage(playerid, "This vehicle offer is no longer valid.");

		SendServerMessage(playerid, "You have successfully purchased %s's %s for %s.", ReturnName(sellerid, 0), ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(price));
		SendServerMessage(sellerid, "%s has successfully purchased your %s for %s.", ReturnName(playerid, 0), ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(price));

		CarData[carid][carOwner] = GetPlayerSQLID(playerid);
		Car_Save(carid);

		GiveMoney(playerid, -price);
		GiveMoney(playerid, price);

		Log_Write("logs/offer_log.txt", "[%s] %s (%s) has sold a %s to %s (%s) for %s.", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnVehicleModelName(CarData[carid][carModel]), ReturnName(sellerid, 0), PlayerData[sellerid][pIP], FormatNumber(price));

		PlayerData[playerid][pCarSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pCarOffered] = -1;
		PlayerData[playerid][pCarValue] = 0;
	}
	if (!strcmp(params, "food", true) && PlayerData[playerid][pFoodSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pFoodSeller],
			type = PlayerData[playerid][pFoodType],
	        price = PlayerData[playerid][pFoodPrice];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds for the food.");

		switch (type)
		{
		    case 1:
		    {
				new id = Inventory_Add(playerid, "Water Bottle", 2958);

				if (id == -1)
				    return SendErrorMessage(playerid, "You don't have anymore room in your inventory.");

		        SendServerMessage(playerid, "You have purchased some water from %s for %s (added to inventory).", ReturnName(sellerid, 0), FormatNumber(price));
		        SendInfoMessage(sellerid, "%s has accepted the water for %s.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 2:
		    {
				new id = Inventory_Add(playerid, "Soda", 1543);

				if (id == -1)
				    return SendErrorMessage(playerid, "You don't have anymore room in your inventory.");

		        SendServerMessage(playerid, "You have purchased a soda from %s for %s (added to inventory).", ReturnName(sellerid, 0), FormatNumber(price));
		        SendInfoMessage(sellerid, "%s has accepted the soda for %s.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 3:
		    {
				new id = Inventory_Add(playerid, "Cooked Burger", 2703);

				if (id == -1)
				    return SendErrorMessage(playerid, "You don't have anymore room in your inventory.");

		        SendServerMessage(playerid, "You have purchased a burger from %s for %s (added to inventory).", ReturnName(sellerid, 0), FormatNumber(price));
		        SendInfoMessage(sellerid, "%s has acceptedthe burger for %s.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 4:
		    {
				new id = Inventory_Add(playerid, "Cooked Pizza", 2702);

				if (id == -1)
				    return SendErrorMessage(playerid, "You don't have anymore room in your inventory.");

		        SendServerMessage(playerid, "You have purchased a slice of pizza from %s for %s (added to inventory).", ReturnName(sellerid, 0), FormatNumber(price));
		        SendInfoMessage(sellerid, "%s has accepted the slice of pizza for %s.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 5:
		    {
				new id = Inventory_Add(playerid, "Chicken", 2663);

				if (id == -1)
				    return SendErrorMessage(playerid, "You don't have anymore room in your inventory.");

		        SendServerMessage(playerid, "You have purchased some chicken from %s for %s (added to inventory).", ReturnName(sellerid, 0), FormatNumber(price));
		        SendInfoMessage(sellerid, "%s has accepted the chicken for %s.", ReturnName(playerid, 0), FormatNumber(price));
			}
		}
		PlayerData[playerid][pFoodSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pFoodType] = 0;
		PlayerData[playerid][pFoodPrice] = 0;
	}
	if (!strcmp(params, "faction", true) && PlayerData[playerid][pFactionOffer] != INVALID_PLAYER_ID)
	{
	    new
	        targetid = PlayerData[playerid][pFactionOffer],
	        factionid = PlayerData[playerid][pFactionOffered];

		if (!FactionData[factionid][factionExists] || PlayerData[targetid][pFactionRank] < FactionData[PlayerData[targetid][pFaction]][factionRanks] - 1)
	   	 	return SendErrorMessage(playerid, "The faction offer is no longer available.");

		SetFaction(playerid, factionid);
		PlayerData[playerid][pFactionRank] = 1;

		SendServerMessage(playerid, "You have accepted %s's offer to join \"%s\".", ReturnName(targetid, 0), Faction_GetName(targetid));
		SendServerMessage(targetid, "%s has accepted your offer to join \"%s\".", ReturnName(playerid, 0), Faction_GetName(targetid));

        PlayerData[playerid][pFactionOffer] = INVALID_PLAYER_ID;
        PlayerData[playerid][pFactionOffered] = -1;
	}
	if (!strcmp(params, "greet", true) && PlayerData[playerid][pShakeOffer] != INVALID_PLAYER_ID)
	{
	    new
	        targetid = PlayerData[playerid][pShakeOffer],
	        type = PlayerData[playerid][pShakeType];

        if (!IsPlayerNearPlayer(playerid, targetid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		SetPlayerToFacePlayer(playerid, targetid);
		SetPlayerToFacePlayer(targetid, playerid);

		PlayerData[playerid][pShakeOffer] = INVALID_PLAYER_ID;
		PlayerData[playerid][pShakeType] = 0;

		switch (type)
		{
		    case 1:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(targetid, "GANGS", "hndshkaa", 4.0, 0, 0, 0, 0, 0, 1);
			}
			case 2:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(targetid, "GANGS", "hndshkba", 4.0, 0, 0, 0, 0, 0, 1);
			}
			case 3:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(targetid, "GANGS", "hndshkda", 4.0, 0, 0, 0, 0, 0, 1);
			}
			case 4:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(targetid, "GANGS", "hndshkea", 4.0, 0, 0, 0, 0, 0, 1);
			}
			case 5:
			{
				ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0, 1);
				ApplyAnimation(targetid, "GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0, 1);
			}
			case 6:
			{
			    ApplyAnimation(playerid, "GANGS", "prtial_hndshk_biz_01", 4.0, 0, 0, 0, 0, 0, 1);
			    ApplyAnimation(targetid, "GANGS", "prtial_hndshk_biz_01", 4.0, 0, 0, 0, 0, 0, 1);
			}
	    }
	    SendServerMessage(playerid, "You have accepted %s's handshake.", ReturnName(targetid, 0));
	    SendServerMessage(targetid, "%s has accepted your handshake.", ReturnName(playerid, 0));
	}
	if (!strcmp(params, "frisk", true) && PlayerData[playerid][pFriskOffer] != INVALID_PLAYER_ID)
	{
	    new
			targetid = PlayerData[playerid][pFriskOffer];

	    if (!IsPlayerNearPlayer(playerid, targetid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		new
		    models[MAX_INVENTORY],
		    amount[MAX_INVENTORY];

		for (new i = 0; i < PlayerData[playerid][pCapacity]; i ++)
		{
	 		if (InventoryData[playerid][i][invExists]) {
	   			models[i] = InventoryData[playerid][i][invModel];
	   			amount[i] = InventoryData[playerid][i][invQuantity];
			}
			else {
			    models[i] = -1;
			    amount[i] = -1;
			}
		}
		PlayerData[playerid][pFriskOffer] = INVALID_PLAYER_ID;
		ShowModelSelectionMenu(targetid, ReturnName(playerid), MODEL_SELECTION_FRISK, models, sizeof(models), 0.0, 0.0, 0.0, 1.0, -1, true, amount);
		PlayerData[targetid][pGiveItem] = playerid;
	}
	return 1;
}

CMD:storage(playerid, params[])
{
	static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1) {
	    House_OpenStorage(playerid, houseid);
	}
	else SendErrorMessage(playerid, "You are not in range of house interior.");
	return 1;
}

CMD:edithouse(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/edithouse [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, price, address, type");
		return 1;
	}
	if ((id < 0 || id >= MAX_HOUSES) || !HouseData[id][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][housePos][3]);

		HouseData[id][houseExterior] = GetPlayerInterior(playerid);
		HouseData[id][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

		House_Refresh(id);
		House_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the location of house ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][houseInt][3]);

		HouseData[id][houseInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pHouse] == HouseData[id][houseID])
			{
				SetPlayerPos(i, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
				SetPlayerFacingAngle(i, HouseData[id][houseInt][3]);

				SetPlayerInterior(i, HouseData[id][houseInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		House_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the interior spawn of house ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "price", true))
	{
	    new price;

	    if (sscanf(string, "d", price))
	        return SendUsageMessage(playerid, "/edithouse [id] [price] [new price]");

	    HouseData[id][housePrice] = price;

	    House_Refresh(id);
	    House_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the price of house ID: %d to %s.", ReturnName(playerid, 0), id, FormatNumber(price));
	}
	else if (!strcmp(type, "address", true))
	{
	    new address[32];

	    if (sscanf(string, "s[32]", address))
	        return SendUsageMessage(playerid, "/edithouse [id] [address] [new address]");

	    format(HouseData[id][houseAddress], 32, address);

	    House_Refresh(id);
	    House_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the address of house ID: %d to \"%s\".", ReturnName(playerid, 0), id, address);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	        return SendUsageMessage(playerid, "/edithouse [id] [type] [interior type]");

		if (typeint < 1 || typeint > sizeof(arrHouseInteriors))
			return SendErrorMessage(playerid, "The specified type must be between 1 and %d.", sizeof(arrHouseInteriors));

	    HouseData[id][houseInt][0] = arrHouseInteriors[typeint][eHouseX];
	    HouseData[id][houseInt][1] = arrHouseInteriors[typeint][eHouseY];
	    HouseData[id][houseInt][2] = arrHouseInteriors[typeint][eHouseZ];
	    HouseData[id][houseInt][3] = arrHouseInteriors[typeint][eHouseAngle];
        HouseData[id][houseInterior] = arrHouseInteriors[typeint][eHouseInterior];

		foreach (new i : Player)
		{
			if (PlayerData[i][pHouse] == HouseData[id][houseID])
			{
				SetPlayerPos(i, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
				SetPlayerFacingAngle(i, HouseData[id][houseInt][3]);

				SetPlayerInterior(i, HouseData[id][houseInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		House_Refresh(id);
	    House_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the type of house ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	return 1;
}

CMD:near(playerid, params[])
{
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if ((id = House_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near house ID: %d.", id);

    if ((id = Business_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near business ID: %d.", id);

    if ((id = Entrance_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near entrance ID: %d.", id);

    if ((id = Job_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near job ID: %d.", id);

    if ((id = Pump_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near pump ID: %d.", id);

    if ((id = Crate_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near crate ID: %d.", id);

    if ((id = Gate_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near gate ID: %d.", id);

    if ((id = ATM_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near ATM ID: %d.", id);

    if ((id = Garbage_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near garbage bin ID: %d.", id);

    if ((id = Vendor_Nearest(playerid)) != -1)
	    SendServerMessage(playerid, "You are standing near vendor ID: %d.", id);

	if ((id = Rack_Nearest(playerid)) != -1)
 		SendServerMessage(playerid, "You are standing near weapon rack ID: %d.", id);

    if ((id = Speed_Nearest(playerid)) != -1)
 		SendServerMessage(playerid, "You are standing near speed camera ID: %d.", id);

    if ((id = Graffiti_Nearest(playerid)) != -1)
 		SendServerMessage(playerid, "You are standing near graffiti ID: %d.", id);

	if ((id = Rent_Nearest(playerid)) != -1)
 		SendServerMessage(playerid, "You are standing near rent ID: %d.", id);
	
	if ((id = Plant_Nearest(playerid)) != -1)
 		SendServerMessage(playerid, "You are standing near plant ID: %d.", id);
	return 1;
}

CMD:createbiz(playerid, params[])
{
    static
		type,
	    price,
	    id;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "dd", type, price))
 	{
	 	SendUsageMessage(playerid, "/createbiz [type] [price]");
    	SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Retail | 2: Electronic | 3: Clothes | 4: Fast Food | 5: Dealership | 6: Gas Station | 7: Furniture");
    	return 1;
	}
	if (type < 1 || type > 7)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 7.");

	id = Business_Create(playerid, type, price);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for businesses.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created business ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:editbiz(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/editbiz [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, deliver, name, price, stock, cars, spawn, caunter, type, actor");
		return 1;
	}
	if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	if (!strcmp(type, "location", true))
	{
 		GetPlayerPos(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizPos][3]);

		BusinessData[id][bizExterior] = GetPlayerInterior(playerid);
		BusinessData[id][bizExteriorVW] = GetPlayerVirtualWorld(playerid);

		Business_Refresh(id);
		Business_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the location of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizInt][3]);

		BusinessData[id][bizInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pBusiness] == BusinessData[id][bizID])
			{
				SetPlayerPos(i, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]);
				SetPlayerFacingAngle(i, BusinessData[id][bizInt][3]);

				SetPlayerInterior(i, BusinessData[id][bizInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the interior spawn of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "deliver", true))
	{
	    if (BusinessData[id][bizType] == 5)
	        return SendErrorMessage(playerid, "This business doesn't accept deliveries.");

	    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
	        return SendErrorMessage(playerid, "You can only place the delivery point outside interiors.");

	    GetPlayerPos(playerid, BusinessData[id][bizDeliver][0], BusinessData[id][bizDeliver][1], BusinessData[id][bizDeliver][2]);
		Business_Refresh(id);

		Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the deliver point of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "caunter", true))
	{
		GetPlayerPos(playerid, BusinessData[id][bizCaunter][0], BusinessData[id][bizCaunter][1], BusinessData[id][bizCaunter][2]);

		Business_Refresh(id);

		Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the caunter point of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "actor", true))
	{
		GetPlayerPos(playerid, BusinessData[id][bizActor][0], BusinessData[id][bizActor][1], BusinessData[id][bizActor][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizActor][3]);

		Business_Refresh(id);

		Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the caunter point of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "price", true))
	{
	    new price;

	    if (sscanf(string, "d", price))
	        return SendUsageMessage(playerid, "/editbiz [id] [price] [new price]");

	    BusinessData[id][bizPrice] = price;

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the price of business ID: %d to %s.", ReturnName(playerid, 0), id, FormatNumber(price));
	}
	else if (!strcmp(type, "stock", true))
	{
	    new amount;

	    if (sscanf(string, "d", amount))
	        return SendUsageMessage(playerid, "/editbiz [id] [stock] [product amount]");

	    BusinessData[id][bizProducts] = amount;

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the stock of business ID: %d to %s products.", ReturnName(playerid, 0), id, FormatNumber(amount, ""));
	}
	else if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendUsageMessage(playerid, "/editbiz [id] [name] [new name]");

	    format(BusinessData[id][bizName], 32, name);

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the name of business ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	else if (!strcmp(type, "cars", true))
	{
	    if (BusinessData[id][bizType] != 5)
	        return SendErrorMessage(playerid, "This business is not a dealership!");

		PlayerData[playerid][pDealership] = id;
		Business_EditCars(playerid, id);
	}
	else if (!strcmp(type, "spawn", true))
	{
	    if (BusinessData[id][bizType] != 5)
	        return SendErrorMessage(playerid, "This business is not a dealership!");

	    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
	        return SendErrorMessage(playerid, "You can only place the vehicle spawn outside interiors.");

	    GetPlayerPos(playerid, BusinessData[id][bizSpawn][0], BusinessData[id][bizSpawn][1], BusinessData[id][bizSpawn][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizSpawn][3]);

		BusinessData[id][bizExterior] = GetPlayerInterior(playerid);

		Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the vehicle spawn of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	    {
	        SendUsageMessage(playerid, "/editbiz [id] [type] [business type]");
			SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Retail | 2: Electronic | 3: Clothes | 4: Fast Food | 5: Dealership | 6: Gas Station | 7: Furniture");
			return 1;
		}
		if (typeint < 1 || typeint > 7)
			return SendErrorMessage(playerid, "The specified type must be between 1 and 7.");

        BusinessData[id][bizType] = typeint;

        Business_Type(id);

		foreach (new i : Player)
		{
			if (PlayerData[i][pBusiness] == BusinessData[id][bizID])
			{
				SetPlayerPos(i, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]);
				SetPlayerFacingAngle(i, BusinessData[id][bizInt][3]);

				SetPlayerInterior(i, BusinessData[id][bizInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Business_Refresh(id);

	    Business_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the type of business ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	return 1;
}

CMD:products(playerid, params[])
{
	static
	    bizid = -1;

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid)) {
	    Business_ProductMenu(playerid, bizid);
	}
	else SendErrorMessage(playerid, "You are not in range of your business interior.");
	return 1;
}


CMD:destroybiz(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroybiz [biz id]");

	if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	Business_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed business ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:cook(playerid, params[])
{
	new houseid = House_Inside(playerid);

	if (houseid == -1)
	    return SendErrorMessage(playerid, "You must be inside a house to cook meals.");

	if (isnull(params))
	    return SendUsageMessage(playerid, "/cook [burger/pizza]");

    if (PlayerData[playerid][pCuffed])
	    return SendErrorMessage(playerid, "You can't use this command at the moment.");

	if (!strcmp(params, "burger", true))
	{
	    if (!Inventory_HasItem(playerid, "Frozen Burger"))
	        return SendErrorMessage(playerid, "You don't have any frozen burgers.");

		
	}
	else if (!strcmp(params, "pizza", true))
	{
	    if (!Inventory_HasItem(playerid, "Frozen Pizza"))
	        return SendErrorMessage(playerid, "You don't have any boxes of frozen pizza.");

		if (PlayerData[playerid][pCooking])
		    return SendErrorMessage(playerid, "You are already cooking a meal.");

        Inventory_Add(playerid, "Cardboard", 928);

		PlayerData[playerid][pCooking] = 2;
		PlayerData[playerid][pCookingTime] = 55;
		PlayerData[playerid][pCookingHouse] = houseid;

        Inventory_Remove(playerid, "Frozen Pizza");
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s prepares the oven and heats up a frozen pizza (55 seconds).", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:createentrance(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params) || strlen(params) > 32)
	    return SendUsageMessage(playerid, "/createentrance [name]");

	new id = Entrance_Create(playerid, params);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for entrances.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created entrance ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:editentrance(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/editentrance [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, password, name, locked, mapicon, custom, virtual");
		return 1;
	}
	if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
	    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

	if (!strcmp(type, "location", true))
	{
	    GetPlayerPos(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);
		GetPlayerFacingAngle(playerid, EntranceData[id][entrancePos][3]);

		EntranceData[id][entranceExterior] = GetPlayerInterior(playerid);
		EntranceData[id][entranceExteriorVW] = GetPlayerVirtualWorld(playerid);

		Entrance_Refresh(id);
		Entrance_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the location of entrance ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
		GetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);

		EntranceData[id][entranceInterior] = GetPlayerInterior(playerid);
		EntranceData[id][entranceWorld] = GetPlayerVirtualWorld(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pEntrance] == EntranceData[id][entranceID])
			{
				SetPlayerPos(i, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
				SetPlayerFacingAngle(i, EntranceData[id][entranceInt][3]);

				SetPlayerInterior(i, EntranceData[id][entranceInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Entrance_Refresh(id);
		Entrance_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the interior spawn of entrance ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "custom", true))
	{
	    new status;

	    if (sscanf(string, "d", status))
	        return SendUsageMessage(playerid, "/editentrance [id] [custom] [0/1]");

		if (status < 0 || status > 1)
		    return SendErrorMessage(playerid, "You must specify at least 0 or 1.");

	    EntranceData[id][entranceCustom] = status;
	    Entrance_Save(id);

	    if (status) {
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has enabled custom interior mode for entrance ID: %d.", ReturnName(playerid, 0), id);
		}
		else {
		    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has disabled custom interior mode for entrance ID: %d.", ReturnName(playerid, 0), id);
		}
	}
	else if (!strcmp(type, "virtual", true))
	{
	    new worldid;

	    if (sscanf(string, "d", worldid))
	        return SendUsageMessage(playerid, "/editentrance [id] [virtual] [interior world]");

	    EntranceData[id][entranceWorld] = worldid;

		foreach (new i : Player) if (Entrance_Inside(i) == id) {
			SetPlayerVirtualWorld(i, worldid);
		}
		Entrance_Refresh(id);
		Entrance_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the virtual of entrance ID: %d to %d.", ReturnName(playerid, 0), id, worldid);
	}
	else if (!strcmp(type, "mapicon", true))
	{
	    new icon;

	    if (sscanf(string, "d", icon))
	        return SendUsageMessage(playerid, "/editentrance [id] [mapicon] [map icon]");

		if (icon < 0 || icon > 63)
		    return SendErrorMessage(playerid, "Invalid map icon! Valid map icons can be found at \"wiki.sa-mp.com/wiki/MapIcons\".");

	    EntranceData[id][entranceIcon] = icon;

	    Entrance_Refresh(id);
	    Entrance_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the price of entrance ID: %d to %d.", ReturnName(playerid, 0), id, icon);
	}
	else if (!strcmp(type, "password", true))
	{
	    new password[32];

	    if (sscanf(string, "s[32]", password))
	        return SendUsageMessage(playerid, "/editentrance [id] [password] [entrance pass] (use 'none' to disable)");

		if (!strcmp(password, "none", true)) {
			EntranceData[id][entrancePass][0] = 0;
		}
		else {
		    format(EntranceData[id][entrancePass], 32, password);
		}
	    Entrance_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the password of entrance ID: %d to \"%s\".", ReturnName(playerid, 0), id, password);
	}
	else if (!strcmp(type, "locked", true))
	{
	    new locked;

	    if (sscanf(string, "d", locked))
	        return SendUsageMessage(playerid, "/editentrance [id] [locked] [locked 0/1]");

		if (locked < 0 || locked > 1)
		    return SendErrorMessage(playerid, "Invalid value. Use 0 for unlocked and 1 for locked.");

	    EntranceData[id][entranceLocked] = locked;
	    Entrance_Save(id);

	    if (locked) {
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has locked entrance ID: %d.", ReturnName(playerid, 0), id);
		} else {
		    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has unlocked entrance ID: %d.", ReturnName(playerid, 0), id);
		}
	}
	else if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendUsageMessage(playerid, "/editentrance [id] [name] [new name]");

	    format(EntranceData[id][entranceName], 32, name);

	    Entrance_Refresh(id);
	    Entrance_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the name of entrance ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	return 1;
}

CMD:destroyentrance(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyentrance [entrance id]");

	if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
	    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

	Entrance_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed entrance ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:createpump(playerid, params[])
{
	static
	    id,
		bizid = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", bizid))
	    return SendUsageMessage(playerid, "/createpump [business id]");

	if ((bizid < 0 || bizid >= MAX_BUSINESSES) || !BusinessData[bizid][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	if (BusinessData[bizid][bizType] != 6)
	    return SendErrorMessage(playerid, "This business is not a gas station!");

    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
		return SendErrorMessage(playerid, "You can only create gas pumps outside interiors.");

	id = Pump_Create(playerid, bizid);

	if (id == -1)
	    return SendErrorMessage(playerid, "The business has reached the limit for gas pumps.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created pump ID %d.", ReturnName(playerid, 0), id);
	EditDynamicObject(playerid, PumpData[id][pumpObject]);

	PlayerData[playerid][pEditPump] = id;
	return 1;
}

CMD:destroypump(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");
		
	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroypump [pump id]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
	    return SendErrorMessage(playerid, "Invalid pump ID.");

	Pump_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed pump ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:setpump(playerid, params[])
{
	static
	    id = 0,
		amount;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "dd", id, amount))
	    return SendUsageMessage(playerid, "/setpump [pump id] [fuel amount]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
	    return SendErrorMessage(playerid, "Invalid pump ID.");

	PumpData[id][pumpFuel] = amount;

	Pump_Refresh(id);
	Pump_Save(id);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set fuel tp %d for pump ID %d.", ReturnName(playerid, 0), amount, id);
	return 1;
}

CMD:unmod(playerid, params[])
{
	new
	    carid = GetPlayerVehicleID(playerid);

	if (!carid)
	    return SendErrorMessage(playerid, "You must be inside your vehicle.");

	if ((carid = Car_GetID(carid)) != -1 && Car_IsOwner(playerid, carid))
	{
	    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	        return SendErrorMessage(playerid, "You must be the driver!");

		for (new i = 0; i < 14; i ++) {
		    RemoveVehicleComponent(CarData[carid][carVehicle], CarData[carid][carMods][i]);

		    CarData[carid][carMods][i] = 0;
		}
		Car_Save(carid);
		SendServerMessage(playerid, "You have removed the modifications from this vehicle.");
	}
	else SendErrorMessage(playerid, "You are not inside anything you can unmodify.");
	return 1;
}

CMD:trunk(playerid, params[])
{
	new
	    id = -1;

	new vehicleid = GetNearestVehicle(playerid);

	if ((id = Car_NearestEx(playerid)) != -1)
	{
	    if (IsPlayerInAnyVehicle(playerid))
	        return SendErrorMessage(playerid, "You must exit the vehicle first.");

		if (!IsDoorVehicle(CarData[id][carVehicle]))
		    return SendErrorMessage(playerid, "This vehicle doesn't have a trunk.");

		if (CarData[id][carLocked])
		    return SendErrorMessage(playerid, "The vehicle's trunk is locked.");

		SetTrunkStatus(vehicleid, true);
		Car_ShowTrunk(playerid, id);
	}
	else SendErrorMessage(playerid, "You are not in range of any vehicle.");
	return 1;
}

CMD:aojail(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] >= 1)
	{
		if(PlayerData[playerid][pAdminDuty] == 0)
			return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

		new string[128], name[MAX_PLAYER_NAME], minutes;
		if(sscanf(params, "s[24]ds[64]", name, minutes)) return SendErrorMessage(playerid, "/aojail [player name] [time (minutes)]");

		new tmpName[24], query[512];
		mysql_real_escape_string(name, tmpName);

		SetPVarString(playerid, "OnJailAccount", tmpName);

		format(string, sizeof(string), "Attempting to jail %s's account for %d minutes...", tmpName, minutes);
		SendClientMessageEx(playerid, COLOR_LIGHTYELLOW, string);

		format(query,sizeof(query),"UPDATE `characters` SET `JailTime` = %d WHERE `Admin` < %d AND `Username` = '%s'", minutes*60, PlayerData[playerid][pAdmin], tmpName);
		mysql_tquery(g_iHandle, query, "OnJailAccount", "i", playerid);
	}
	return 1;
}
CMD:furniture(playerid, params[])
{
    static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1 && House_IsOwner(playerid, houseid))
	{
        new
			count = 0,
			string[MAX_FURNITURE * 32];

        for (new i = 0; i != MAX_FURNITURE; i ++) if (count < MAX_HOUSE_FURNITURE && FurnitureData[i][furnitureExists] && FurnitureData[i][furnitureHouse] == houseid) {
    		ListedFurniture[playerid][count++] = i;

    		format(string, sizeof(string), "%s%s (%.2f meters)\n", string, FurnitureData[i][furnitureName], GetPlayerDistanceFromPoint(playerid, FurnitureData[i][furniturePos][0], FurnitureData[i][furniturePos][1], FurnitureData[i][furniturePos][2]));
		}
		if (count) {
			Dialog_Show(playerid, ListedFurniture, DIALOG_STYLE_LIST, "Listed Furniture", string, "Select", "Cancel");
     	}
     	else SendErrorMessage(playerid, "This house doesn't have any furniture spawned.");
	}
	else SendErrorMessage(playerid, "You are not in range of your house interior.");
	return 1;
}

CMD:createjob(playerid, params[])
{
	static
	    type,
		id = -1;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/createjob [type]");

	if (type < 1 || type > 9)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 9.");

	id = Job_Create(playerid, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for jobs.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created job ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroyjob(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyjob [job id]");

	if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
	    return SendErrorMessage(playerid, "You have specified an invalid job ID.");

	Job_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed job ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:editjob(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/editjob [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, type, point, deliver");
		return 1;
	}
	if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
	    return SendErrorMessage(playerid, "You have specified an invalid job ID.");

	if (!strcmp(type, "location", true))
	{
	    static
	        Float:x,
	        Float:y,
	        Float:z;

	    GetPlayerPos(playerid, x, y, z);

		JobData[id][jobPos][0] = x;
		JobData[id][jobPos][1] = y;
		JobData[id][jobPos][2] = z;

		JobData[id][jobInterior] = GetPlayerInterior(playerid);
		JobData[id][jobWorld] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the location of job ID: %d.", ReturnName(playerid, 0), id);
	}
 	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	        return SendUsageMessage(playerid, "/edithouse [id] [type] [new type]");

        if (typeint < 1 || typeint > 9)
	    	return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 9.");

	    JobData[id][jobType] = typeint;

	    Job_Refresh(id);
	    Job_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the type of job ID: %d to %s.", ReturnName(playerid, 0), id, Job_GetName(typeint));
	}
	else if (!strcmp(type, "point", true))
	{
	    static
	        Float:x,
	        Float:y,
	        Float:z;

	    GetPlayerPos(playerid, x, y, z);

		JobData[id][jobPoint][0] = x;
		JobData[id][jobPoint][1] = y;
		JobData[id][jobPoint][2] = z;
        JobData[id][jobPointInt] = GetPlayerInterior(playerid);
        JobData[id][jobPointWorld] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the point of job ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "deliver", true))
	{
	    static
	        Float:x,
	        Float:y,
	        Float:z;

	    GetPlayerPos(playerid, x, y, z);

		JobData[id][jobDeliver][0] = x;
		JobData[id][jobDeliver][1] = y;
		JobData[id][jobDeliver][2] = z;

		Job_Refresh(id);
		Job_Save(id);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the deliver point of job ID: %d.", ReturnName(playerid, 0), id);
	}
	return 1;
}

CMD:quitjob(playerid, params[])
{
	if (PlayerData[playerid][pJob] != 0)
	{
		if (PlayerData[playerid][pMinedRock])
		{
	    	PlayerData[playerid][pMinedRock] = 0;
			PlayerData[playerid][pMineCount] = 0;

			DisablePlayerCheckpoint(playerid);

			RemovePlayerAttachedObject(playerid, 4);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
		if (PlayerData[playerid][pJob] == JOB_COURIER)
		{
			if (PlayerData[playerid][pUnloading] != -1)
			{
	   		 	PlayerData[playerid][pUnloading] = -1;
	    		PlayerData[playerid][pUnloadVehicle] = INVALID_VEHICLE_ID;

	    		DisablePlayerCheckpoint(playerid);
			}
			if (PlayerData[playerid][pDeliverShipment])
			{
			    PlayerData[playerid][pShipment] = -1;
			    PlayerData[playerid][pDeliverShipment] = 0;

			    DisablePlayerCheckpoint(playerid);
			}
			if (PlayerData[playerid][pLoading])
			{
	   	 		PlayerData[playerid][pLoading] = 0;
	    		PlayerData[playerid][pLoadType] = 0;

	    		DisablePlayerCheckpoint(playerid);
			}
			if (PlayerData[playerid][pLoadCrate])
 			{
  				PlayerData[playerid][pLoadCrate] = 0;

				RemovePlayerAttachedObject(playerid, 4);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			}
		}
		SendServerMessage(playerid, "You have quit your job as a \"%s\".", Job_GetName(PlayerData[playerid][pJob]));
		PlayerData[playerid][pJob] = 0;
	}
	else SendErrorMessage(playerid, "You don't have a job to quit.");
	return 1;
}

CMD:takejob(playerid, params[])
{
	static
	    id = -1;

	if ((id = Job_Nearest(playerid)) != -1)
	{
	    if (PlayerData[playerid][pJob] == JobData[id][jobType])
	        return SendErrorMessage(playerid, "You have this job already.");

	    PlayerData[playerid][pJob] = JobData[id][jobType];

	    return SendServerMessage(playerid, "You are now a %s - type \"/help\" for job commands.", Job_GetName(JobData[id][jobType]));
	}
    SendErrorMessage(playerid, "You are not in range of any job pickup.");
	return 1;
}

CMD:unload(playerid, params[])
{
	new
		id = Business_NearestDeliver(playerid),
		vid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pJob] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

    if (id == -1)
	    return SendErrorMessage(playerid, "You are not in range of any delivery point.");

 	if (!IsLoadableVehicle(vid))
  		return SendErrorMessage(playerid, "You are not inside any loadable vehicle.");

	if (!CoreVehicles[vid][vehLoadType] || CoreVehicles[vid][vehLoads] < 1)
	    return SendErrorMessage(playerid, "There is nothing loaded in this vehicle.");

	if (PlayerData[playerid][pUnloading] != -1)
	    return SendErrorMessage(playerid, "You are already unloading your crates.");

	if (PlayerData[playerid][pShipment] != -1 && id != PlayerData[playerid][pShipment])
	    return SendErrorMessage(playerid, "You didn't accept shipment for this business.");

	switch (CoreVehicles[vid][vehLoadType])
 	{
	 	case 1:
	 	{
	 	    if (BusinessData[id][bizType] != 1 && BusinessData[id][bizType] != 6)
	 	        return SendErrorMessage(playerid, "This business can't accept this load (wrong type).");
		}
		case 2..4:
		{
		    if (BusinessData[id][bizType] != CoreVehicles[vid][vehLoadType])
	 	        return SendErrorMessage(playerid, "This business can't accept this load (wrong type).");
		}
		case 5:
		{
		    if (BusinessData[id][bizType] != 6)
	 	        return SendErrorMessage(playerid, "This business can't accept this load (wrong type).");
		}
		case 6:
		{
		    if (BusinessData[id][bizType] != 7)
	 	        return SendErrorMessage(playerid, "This business can't accept this load (wrong type).");
		}
	}
	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	DisableWaypoint(playerid);

	GetVehicleBoot(vid, fX, fY, fZ);
	RemovePlayerFromVehicle(playerid);

	PlayerData[playerid][pUnloading] = id;
	PlayerData[playerid][pUnloadVehicle] = vid;

	SetPlayerCheckpoint(playerid, fX, fY, fZ, 1.0);
	SendServerMessage(playerid, "Please unload the crates and deliver them to the point.");

	return 1;
}

CMD:repair(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_MECHANIC)
		return SendErrorMessage(playerid, "You must be a mechanic member.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (IsPlayerInAnyVehicle(playerid))
	    return SendErrorMessage(playerid, "You must exit the vehicle first.");

	if (!Inventory_HasItem(playerid, "Repair Kit"))
	    return SendErrorMessage(playerid, "You don't have a repair kit on you.");

	if (PlayerData[playerid][pRepairTime] > gettime())
	    return SendErrorMessage(playerid, "You must wait %d seconds before repairing again.", PlayerData[playerid][pRepairTime] - gettime());

	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && IsPlayerNearHood(playerid, i))
	{
	    if (!IsEngineVehicle(i))
	        return SendErrorMessage(playerid, "This vehicle can't be repaired.");

	    if (!GetHoodStatus(i))
	        return SendErrorMessage(playerid, "The hood must be opened before a repair.");

        if (CoreVehicles[i][vehRepairing])
            return SendErrorMessage(playerid, "This vehicle is already being repaired.");

		Inventory_Remove(playerid, "Repair Kit");
		ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);

        CoreVehicles[i][vehRepairing] = true;
        SetTimerEx("RepairCar", 5000, false, "dd", playerid, i);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s starts to repair the vehicle.", ReturnName(playerid, 0));
		GameTextForPlayer(playerid, "~g~Repairing...~w~ Please wait", 5500, 3);
		return 1;
	}
	SendErrorMessage(playerid, "You are not in range of any vehicle's hood.");
	return 1;
}

CMD:acceptcall(playerid, params[])
{
    if (PlayerData[playerid][pJob] != JOB_TAXI)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (!PlayerData[playerid][pTaxiDuty])
	    return SendErrorMessage(playerid, "You must be on taxi duty to accept calls.");

	Taxi_ShowCalls(playerid);
	return 1;
}

CMD:taxi(playerid, params[])
{
	new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));

    if (PlayerData[playerid][pJob] != JOB_TAXI)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (modelid != 438 && modelid != 420)
	    return SendErrorMessage(playerid, "You must be inside a taxi.");

	if (PlayerData[playerid][pTaxiDuty])
	{
	    foreach (new i : Player) if (PlayerData[i][pTaxiPlayer] == playerid && IsPlayerInVehicle(i, GetPlayerVehicleID(playerid))) {
	        LeaveTaxi(i, playerid);
	    }
	    SetPlayerColor(playerid, DEFAULT_COLOR);

        PlayerData[playerid][pTaxiDuty] = false;
        SendServerMessage(playerid, "You are no longer on taxi duty!");
	}
	else
	{
		SetPlayerColor(playerid, 0xF5DEB300);

	    PlayerData[playerid][pTaxiDuty] = true;
	    SendClientMessageToAllEx(COLOR_GREEN, "[TAXI]: %s is now on taxi duty. Type \"/call 1222\" to call a taxi!", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:sms(playerid, params[])
{
    if (!Inventory_HasItem(playerid, "Cellphone"))
	    return SendErrorMessage(playerid, "You don't have a cellphone on you.");

	static
	    targetid,
		number,
		text[128];

	if (sscanf(params, "ds[128]", number, text))
	    return SendUsageMessage(playerid, "/text [phone number] [message]");

	if (!number)
	    return SendErrorMessage(playerid, "The specified phone number is not in service.");

	if ((targetid = GetNumberOwner(number)) != INVALID_PLAYER_ID)
	{
	    if (targetid == playerid)
	        return SendErrorMessage(playerid, "You can't text yourself!");

        GiveMoney(playerid, -1);
		SendServerMessage(playerid, "You've been charged RM1 to send a text.");

		SendClientMessageEx(targetid, COLOR_YELLOW, "[TEXT]: %s - %s (%d)", text, ReturnName(playerid, 0), PlayerData[playerid][pPhone]);
		SendClientMessageEx(playerid, COLOR_YELLOW, "[TEXT]: %s - %s (%d)", text, ReturnName(playerid, 0), PlayerData[playerid][pPhone]);

        PlayerPlaySoundEx(targetid, 21001);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their phone and sends a text.", ReturnName(playerid, 0));
	}
	else
	{
	    SendErrorMessage(playerid, "The specified phone number is not in service.");
	}
	return 1;
}

CMD:answer(playerid, params[])
{
	if (!PlayerData[playerid][pIncomingCall])
	    return SendErrorMessage(playerid, "There are no incoming calls to accept.");

	if (PlayerData[playerid][pCuffed])
	    return SendErrorMessage(playerid, "You can't use this command at the moment.");

	new targetid = PlayerData[playerid][pCallLine];

	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;

	SendServerMessage(playerid, "You have answered the call.");
	SendInfoMessage(targetid, "The other line has accepted the call.");

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has accepted the incoming call.", ReturnName(playerid, 0));
	return 1;
}

CMD:hangup(playerid, params[])
{
	new targetid = PlayerData[playerid][pCallLine];

	if (PlayerData[playerid][pEmergency] || PlayerData[playerid][pPlaceAd])
	{
	    PlayerData[playerid][pEmergency] = 0;
	    PlayerData[playerid][pPlaceAd] = 0;

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has hung up their cellphone.", ReturnName(playerid, 0));
        return 1;
	}
	if (targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "There are no calls to hangup.");

	if (PlayerData[playerid][pIncomingCall])
	{
	    SendClientMessage(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} You have declined the incoming call.");
	    SendClientMessage(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} The other line has declined the call.");

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has declined the call.", ReturnName(playerid, 0));
	}
	else
	{
        SendClientMessage(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} You have hung up the call.");
	    SendClientMessage(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} The other line has hung up the call.");

	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has hung up their cellphone.", ReturnName(playerid, 0));
	    SendNearbyMessage(targetid, 30.0, COLOR_PURPLE, "** %s has hung up their cellphone.", ReturnName(targetid, 0));
	}
	PlayerData[playerid][pIncomingCall] = 0;
	PlayerData[targetid][pIncomingCall] = 0;

	PlayerData[playerid][pCallLine] = INVALID_PLAYER_ID;
	PlayerData[targetid][pCallLine] = INVALID_PLAYER_ID;

	return 1;
}

CMD:id(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/id [playerid/name]");

	if (strlen(params) < 3)
		return SendErrorMessage(playerid, "You must specify at least 3 characters.");

	new count;

	foreach (new i : Player)
	{
	    if (strfind(ReturnName(i), params, true) != -1)
	    {
	        SendClientMessageEx(playerid, COLOR_WHITE, "** %s - ID: %d", ReturnName(i), i);
	        count++;
		}
	}
	if (!count)
	    return SendErrorMessage(playerid, "No users matched the search criteria: \"%s\".", params);

	return 1;
}

CMD:mine(playerid, params[])
{
    if (PlayerData[playerid][pJob] != JOB_MINER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (!IsPlayerNearMine(playerid))
	    return SendErrorMessage(playerid, "You must be near the mine.");

	if (PlayerData[playerid][pMining])
	{
	    PlayerData[playerid][pMining] = false;
	    PlayerData[playerid][pMineCount] = 0;

		RemovePlayerAttachedObject(playerid, 4);
	    SendServerMessage(playerid, "You have finished your mining job.");
	}
	else
	{
	    PlayerData[playerid][pMining] = true;
        PlayerData[playerid][pMineCount] = 0;

	    SendServerMessage(playerid, "You are now mining! Use the fire key to begin digging.");
	    SetPlayerAttachedObject(playerid, 4, 18634, 6, 0.156547, 0.039423, 0.026570, 198.109115, 6.364907, 262.997558, 1.000000, 1.000000, 1.000000);
	}
	return 1;
}

CMD:sellfood(playerid, params[])
{
	if (PlayerData[playerid][pJob] != JOB_FOOD_VENDOR)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 423)
 		return SendErrorMessage(playerid, "You are not inside a food truck.");

	static
	    userid,
	    food[24],
	    price;

	if (sscanf(params, "us[24]d", userid, food, price))
	{
	    SendUsageMessage(playerid, "/sellfood [playerid/name] [food name] [price]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} water, soda, burger, pizza, chicken");
	    return 1;
	}
	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 7.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (price < 1 || price > 20)
	    return SendErrorMessage(playerid, "The price can't be below RM1 or above RM20.");

	if (!strcmp(food, "water", true))
	{
	    PlayerData[userid][pFoodSeller] = playerid;
	    PlayerData[userid][pFoodType] = 1;
	    PlayerData[userid][pFoodPrice] = price;

		SendServerMessage(userid, "%s has offered you some water for %s (type \"/approve food\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		SendServerMessage(playerid, "You have offered some water to %s for %s.", ReturnName(userid, 0), FormatNumber(price));
	}
	else if (!strcmp(food, "soda", true))
	{
	    PlayerData[userid][pFoodSeller] = playerid;
	    PlayerData[userid][pFoodType] = 2;
	    PlayerData[userid][pFoodPrice] = price;

		SendServerMessage(userid, "%s has offered you a soda for %s (type \"/approve food\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		SendServerMessage(playerid, "You have offered a soda to %s for %s.", ReturnName(userid, 0), FormatNumber(price));
	}
	else if (!strcmp(food, "burger", true))
	{
	    PlayerData[userid][pFoodSeller] = playerid;
	    PlayerData[userid][pFoodType] = 3;
	    PlayerData[userid][pFoodPrice] = price;

		SendServerMessage(userid, "%s has offered you a burger for %s (type \"/approve food\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		SendServerMessage(playerid, "You have offered a burger to %s for %s.", ReturnName(userid, 0), FormatNumber(price));
	}
	else if (!strcmp(food, "pizza", true))
	{
	    PlayerData[userid][pFoodSeller] = playerid;
	    PlayerData[userid][pFoodType] = 4;
	    PlayerData[userid][pFoodPrice] = price;

		SendServerMessage(userid, "%s has offered you a slice of pizza for %s (type \"/approve food\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		SendServerMessage(playerid, "You have offered a slice of pizza to %s for %s.", ReturnName(userid, 0), FormatNumber(price));
	}
	else if (!strcmp(food, "chicken", true))
	{
	    PlayerData[userid][pFoodSeller] = playerid;
	    PlayerData[userid][pFoodType] = 5;
	    PlayerData[userid][pFoodPrice] = price;

		SendServerMessage(userid, "%s has offered you some chicken for %s (type \"/approve food\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		SendServerMessage(playerid, "You have offered some chicken to %s for %s.", ReturnName(userid, 0), FormatNumber(price));
	}
	return 1;
}

CMD:createcrate(playerid, params[])
{
	static
	    id = -1,
		type;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", type))
	{
	    SendUsageMessage(playerid, "/createcrate [type]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Melee | 2: Pistol Parts | 3: SMG Parts | 4: Shotgun Parts | 5: Rifle Parts | 6: Drugs");
		return 1;
	}
	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 6.");

	id = Crate_Create(playerid, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for crates.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created crate ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroycrate(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroycrate [crate id]");

	if ((id < 0 || id >= MAX_CRATES) || !CrateData[id][crateExists])
	    return SendErrorMessage(playerid, "You have specified an invalid crate ID.");

	Crate_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed crate ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:crates(playerid, params[])
{
	static
	    string[512];

	string[0] = '\0';

	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsLoadableVehicle(i) && IsPlayerNearBoot(playerid, i))
	{
	    if (GetVehicleCrates(i) < 1)
	        return SendErrorMessage(playerid, "There are no crates in this vehicle.");

		for (new j = 0; j != MAX_CRATES; j ++) if (CrateData[j][crateExists] && CrateData[j][crateVehicle] == i) {
			format(string, sizeof(string), "%sCrate #%d: %s Parts\n", string, j, Crate_GetType(CrateData[j][crateType]));
		}
		PlayerData[playerid][pCrateVehicle] = i;
		return Dialog_Show(playerid, Crates, DIALOG_STYLE_LIST, "Vehicle Crates", string, "Take", "Cancel");
	}
	SendErrorMessage(playerid, "You are not in range of any loadable vehicle.");
	return 1;
}

CMD:craftparts(playerid, params[])
{
	new id = -1;

	if (PlayerData[playerid][pJob] != JOB_WEAPON_SMUGGLER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

    if ((id = Job_NearestPoint(playerid)) == -1 || JobData[id][jobType] != JOB_WEAPON_SMUGGLER)
		return SendErrorMessage(playerid, "You are not in range of the craft factory.");

	if (PlayerData[playerid][pCarryCrate] == -1)
	    return SendErrorMessage(playerid, "You are not carrying any crate.");

	if (PlayerData[playerid][pCrafting])
	    return SendErrorMessage(playerid, "You are already crafting weapon parts.");

	if (CrateData[PlayerData[playerid][pCarryCrate]][crateType] < 1 || CrateData[PlayerData[playerid][pCarryCrate]][crateType] > 5)
	    return SendErrorMessage(playerid, "There are no weapon parts in this crate.");

    PlayerData[playerid][pCrafting] = 1;

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s begins crafting their %s Parts.", ReturnName(playerid, 0), Crate_GetType(CrateData[PlayerData[playerid][pCarryCrate]][crateType]));
	GameTextForPlayer(playerid, "~r~Crafting parts...", 11000, 3);

	TogglePlayerControllable(playerid, 0);
	SetTimerEx("CraftParts", 8000, false, "dd", playerid, PlayerData[playerid][pCarryCrate]);
	return 1;
}

CMD:opencrate(playerid, params[])
{
	new id = Crate_Nearest(playerid);

	if (id == -1 || CrateData[id][crateType] != 6)
	    return SendErrorMessage(playerid, "You are not in range of any drug crate.");

	if (!Inventory_HasItem(playerid, "Crowbar"))
		return SendErrorMessage(playerid, "You need a crowbar to open this crate.");

	if (PlayerData[playerid][pOpeningCrate])
	    return SendErrorMessage(playerid, "You are already opening a crate.");

	PlayerData[playerid][pOpeningCrate] = 1;

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a crowbar and breaks the drug crate open.", ReturnName(playerid, 0));
	GameTextForPlayer(playerid, "~r~Opening crate...", 3000, 3);

 	TogglePlayerControllable(playerid, 0);
  	ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.0, 1, 1, 1, 1, 0, 1);

	SetTimerEx("OpenCrate", 3000, false, "dd", playerid, id);
    return 1;
}

CMD:plant(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/plant [weed/cocaine/heroin]");

	if (Plant_Nearest(playerid) != -1)
	    return SendErrorMessage(playerid, "You can't plant seeds near other plants.");

	if (!strcmp(params, "weed", true))
	{
	    if (Inventory_Count(playerid, "Marijuana Seeds") < 10)
	        return SendErrorMessage(playerid, "You need at least 10 marijuana seeds.");

		Inventory_Remove(playerid, "Marijuana Seeds", 10);

		Plant_Create(playerid, 1);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s plants some marijuana seeds into the ground.", ReturnName(playerid, 0));
	}
	else if (!strcmp(params, "cocaine", true))
	{
	    if (Inventory_Count(playerid, "Cocaine Seeds") < 10)
	        return SendErrorMessage(playerid, "You need at least 10 cocaine seeds.");

		Inventory_Remove(playerid, "Cocaine Seeds", 10);

		Plant_Create(playerid, 2);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s plants some cocaine seeds into the ground.", ReturnName(playerid, 0));
	}
	else if (!strcmp(params, "heroin", true))
	{
	    if (Inventory_Count(playerid, "Heroin Opium Seeds") < 10)
	        return SendErrorMessage(playerid, "You need at least 10 heroin opium seeds.");

		Inventory_Remove(playerid, "Heroin Opium Seeds", 10);

		Plant_Create(playerid, 3);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s plants some heroin opium seeds into the ground.", ReturnName(playerid, 0));
	}
	else {
	    SendUsageMessage(playerid, "/plant [weed/cocaine/heroin]");
	}
	return 1;
}

CMD:harvest(playerid, params[])
{
	new id = Plant_Nearest(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "You must be near a drug plant.");

	if (PlantData[id][plantDrugs] < Plant_MaxGrams(PlantData[id][plantType]))
	    return SendErrorMessage(playerid, "This plant is not fully grown yet.");

	if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK)
	    return SendErrorMessage(playerid, "You must be crouched to harvest drug plant.");

	if (PlayerData[playerid][pHarvesting])
	    return SendErrorMessage(playerid, "You are already harvesting a plant.");

	GameTextForPlayer(playerid, "~r~Harvesting plant...", 3100, 3);
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s begins to harvest the drug plant.", ReturnName(playerid, 0));

	PlayerData[playerid][pHarvesting] = 1;
	SetTimerEx("HarvestPlant", 3000, false, "dd", playerid, id);
	return 1;
}

CMD:createfaction(playerid, params[])
{
	static
	    id = -1,
		type,
		name[32];

    if (PlayerData[playerid][pAdmin] < 2 && !PlayerData[playerid][pFactionMod])
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[32]", type, name))
	{
	    SendUsageMessage(playerid, "/createfaction [type] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Police | 2: Medical | 3: Mechanic | 4: Gang");
		return 1;
	}
	if (type < 1 || type > 5)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 5.");

	id = Faction_Create(name, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for factions.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created faction ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroyfaction(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2 && !PlayerData[playerid][pFactionMod])
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyfaction [faction id]");

	if ((id < 0 || id >= MAX_FACTIONS) || !FactionData[id][factionExists])
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	Faction_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed faction ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:drop(playerid, params[])
{
	new weaponid = 0;

    if (IsPlayerInAnyVehicle(playerid) || !IsPlayerSpawned(playerid))
    	return SendErrorMessage(playerid, "You can't drop any weapons right now.");

	if ((weaponid = GetWeapon(playerid)) == 0)
	    return SendErrorMessage(playerid, "You can't drop a weapon unless you're holding one.");

	if (weaponid == 23 && PlayerData[playerid][pTazer])
	    return SendErrorMessage(playerid, "You can't drop a tazer.");

    if (weaponid == 25 && PlayerData[playerid][pBeanBag])
	    return SendErrorMessage(playerid, "You can't drop a beanbag shotgun.");

	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	x += 1.5 * floatsin(-angle, degrees);
	y += 1.5 * floatcos(-angle, degrees);

    DropItem(ReturnWeaponName(weaponid), ReturnName(playerid, 0), GetWeaponModel(weaponid), 1, x, y, z - 1, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), weaponid, GetPlayerAmmo(playerid));
	ResetWeapon(playerid, weaponid);

    ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a %s and drops it on the floor.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));
 	Log_Write("logs/droppick.txt", "[%s] %s has dropped a %s.", ReturnDate(), ReturnName(playerid, 0), ReturnWeaponName(weaponid));
	return 1;
}

CMD:flist(playerid, params[])
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists]) {
	    SendClientMessageEx(playerid, COLOR_WHITE, "[ID: %d] {%06x}%s", i, FactionData[i][factionColor] >>> 8, FactionData[i][factionName]);
	}
	return 1;
}

CMD:editfaction(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2 && !PlayerData[playerid][pFactionMod])
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/editfaction [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} name, color, type, models, locker, ranks, maxranks, money");
		return 1;
	}
	if ((id < 0 || id >= MAX_FACTIONS) || !FactionData[id][factionExists])
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

    if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendUsageMessage(playerid, "/editfaction [id] [name] [new name]");

	    format(FactionData[id][factionName], 32, name);

	    Faction_Save(id);
		SendFactionAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the name of faction ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	else if (!strcmp(type, "maxranks", true))
	{
	    new ranks;

	    if (sscanf(string, "d", ranks))
	        return SendUsageMessage(playerid, "/editfaction [id] [maxranks] [maximum ranks]");

		if (ranks < 1 || ranks > 15)
		    return SendErrorMessage(playerid, "The specified ranks can't be below 1 or above 15.");

	    FactionData[id][factionRanks] = ranks;

	    Faction_Save(id);
		SendFactionAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the maximum ranks of faction ID: %d to %d.", ReturnName(playerid, 0), id, ranks);
	}
	else if (!strcmp(type, "ranks", true))
	{
	    Faction_ShowRanks(playerid, id);
	}
	else if (!strcmp(type, "color", true))
	{
	    new color;

	    if (sscanf(string, "h", color))
	        return SendUsageMessage(playerid, "/editfaction [id] [color] [hex color]");

	    FactionData[id][factionColor] = color;

	    Faction_Save(id);
		SendFactionAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has adjusted the {%06x}color{FF6347} of faction ID: %d.", ReturnName(playerid, 0), color >>> 8, id);
	}
	else if (!strcmp(type, "money", true))
	{
	    new amount;

	    if (sscanf(string, "d", amount))
     	{
		 	SendUsageMessage(playerid, "/editfaction [id] [money] [amount]");
            return 1;
		}
	    FactionData[id][factionMoney] = amount;

	    Faction_Save(id);
		SendFactionAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the money amount of faction ID: %d to %s.", ReturnName(playerid, 0), id, FormatNumber(amount));
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
		 	SendUsageMessage(playerid, "/editfaction [id] [type] [faction type]");
            SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Police | 2: Medical | 3: Mechanic | 4: Gang");
            return 1;
		}
		if (typeint < 1 || typeint > 5)
		    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 5.");

	    FactionData[id][factionType] = typeint;

	    Faction_Save(id);
		SendFactionAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the type of faction ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	else if (!strcmp(type, "models", true))
	{
	    static
	        skins[14];

		for (new i = 0; i < sizeof(skins); i ++)
		    skins[i] = (FactionData[id][factionSkins][i]) ? (FactionData[id][factionSkins][i]) : (19300);

	    PlayerData[playerid][pFactionEdit] = id;
		ShowModelSelectionMenu(playerid, "Faction Skins", MODEL_SELECTION_SKINS, skins, sizeof(skins), -16.0, 0.0, -55.0);
	}
	else if (!strcmp(type, "locker", true))
	{
        PlayerData[playerid][pFactionEdit] = id;
		Dialog_Show(playerid, FactionLocker, DIALOG_STYLE_LIST, "Faction Locker", "Set Locker Location\nSet Leader Locker Location\nLocker Locker Weapons", "Select", "Cancel");
	}
	return 1;
}

CMD:color(playerid, params[])
{
	static
	    color;

	if (sscanf(params, "h", color)) {
	 	SendUsageMessage(playerid, "/color [hex color]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[EXAMPLE]:{FFFFFF} 0xFFFFFFFF is white, 0xFF0000FF is red, etc.");
	}
	else {
	    SendClientMessageEx(playerid, color, "This is a test message, testing color 0x%06xFF.", color >>> 8);
	}
	return 1;
}

CMD:setleader(playerid, params[])
{
	static
		userid,
		id;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, id))
	    return SendUsageMessage(playerid, "/setleader [playerid/name] [faction id] (Use -1 to unset)");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    if ((id < -1 || id >= MAX_FACTIONS) || (id != -1 && !FactionData[id][factionExists]))
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	if (id == -1)
	{
	    ResetFaction(userid);

	    SendServerMessage(playerid, "You have removed %s's faction leadership.", ReturnName(userid, 0));
    	SendServerMessage(userid, "%s has removed your faction leadership.", ReturnName(playerid, 0));
	}
	else
	{
		SetFaction(userid, id);
		PlayerData[userid][pFactionRank] = FactionData[id][factionRanks];

		SendServerMessage(playerid, "You have made %s the leader of \"%s\".", ReturnName(userid, 0), FactionData[id][factionName]);
    	SendServerMessage(userid, "%s has made you the leader of \"%s\".", ReturnName(playerid, 0), FactionData[id][factionName]);
	}
    return 1;
}

CMD:asetfaction(playerid, params[])
{
	static
		userid,
		id;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, id))
	    return SendUsageMessage(playerid, "/asetfaction [playerid/name] [faction id] (Use -1 to unset)");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    if ((id < -1 || id >= MAX_FACTIONS) || (id != -1 && !FactionData[id][factionExists]))
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	if (id == -1)
	{
	    ResetFaction(userid);

	    SendServerMessage(playerid, "You have removed %s from their faction.", ReturnName(userid, 0));
    	SendServerMessage(userid, "%s has removed you from your faction.", ReturnName(playerid, 0));
	}
	else
	{
		SetFaction(userid, id);

		if (!PlayerData[userid][pFactionRank])
	    	PlayerData[userid][pFactionRank] = 1;

		SendServerMessage(playerid, "You have set %s's faction to \"%s\".", ReturnName(userid, 0), FactionData[id][factionName]);
    	SendServerMessage(userid, "%s has set your faction to \"%s\".", ReturnName(playerid, 0), FactionData[id][factionName]);
	}
    return 1;
}

CMD:asetrank(playerid, params[])
{
	static
		userid,
		rank,
		factionid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, rank))
	    return SendUsageMessage(playerid, "/asetrank [playerid/name] [rank id]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if ((factionid = PlayerData[userid][pFaction]) == -1)
	    return SendErrorMessage(playerid, "That player is not a member of any faction.");

    if (rank < 1 || rank > FactionData[factionid][factionRanks])
        return SendErrorMessage(playerid, "Invalid rank. Ranks for this faction range from 1 to %d.", FactionData[factionid][factionRanks]);

	PlayerData[userid][pFactionRank] = rank;

	SendServerMessage(playerid, "You have set %s's faction rank to %d.", ReturnName(userid, 0), rank);
    SendServerMessage(userid, "%s has set your faction rank to %d.", ReturnName(playerid, 0), rank);

    return 1;
}

CMD:rr(playerid, params[])
{
    new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

    if (isnull(params))
        return SendUsageMessage(playerid, "/rr [text]");

	if (GetFactionType(playerid) != FACTION_GANG)
	{
		if(PlayerData[playerid][pOnDuty] == 0) return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "** [RADIO] %s %s: %s **", Faction_GetRank(playerid), ReturnName(playerid, 0), params);
	}
	else SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "** [RADIO] %s %s: %s **", Faction_GetRank(playerid), ReturnName(playerid, 0) , params);
    return 1;
}

CMD:online(playerid, params[])
{
	new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

	SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

    foreach (new i : Player) if (PlayerData[i][pFaction] == factionid)
	{
		if (PlayerData[i][pOnDuty])
			SendClientMessageEx(playerid, COLOR_WHITE, "{FFFFFF}* %s ({0045ff}Rank: %s{FFFFFF}) {FFFFFF}Status: {FFFFFF}({00ff18}Onduty{FFFFFF})", ReturnName(i, 0), Faction_GetRank(i));

		else
		    SendClientMessageEx(playerid, COLOR_WHITE, "{FFFFFF}* %s ({0045ff}Rank: %s{FFFFFF}) {FFFFFF}Status: {FFFFFF}({ff0000}Offduty{FFFFFF})", ReturnName(i, 0), Faction_GetRank(i));

	}
	SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

	return 1;
}

CMD:fquit(playerid, params[])
{
	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

	if(PlayerData[playerid][pOnDuty] == 1)
		return SendErrorMessage(playerid, "Anda perlu offduty untuk command menggunakan ini!");

	if (GetFactionType(playerid) == FACTION_POLICE)
	{
	    SetPlayerArmourEx(playerid, 0);
	    ResetWeapons(playerid);
	}
	SendServerMessage(playerid, "You have quit the \"%s\" faction (rank %d).", Faction_GetName(playerid), PlayerData[playerid][pFactionRank]);
    ResetFaction(playerid);

    return 1;
}

CMD:finvite(playerid, params[])
{
	new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/finvite [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (PlayerData[userid][pFaction] == PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is already part of your faction.");

    if (PlayerData[userid][pFaction] != -1)
	    return SendErrorMessage(playerid, "That player is already part of another faction.");

	PlayerData[userid][pFactionOffer] = playerid;
    PlayerData[userid][pFactionOffered] = PlayerData[playerid][pFaction];

    SendServerMessage(playerid, "You have requested %s to join \"%s\".", ReturnName(userid, 0), Faction_GetName(playerid));
    SendServerMessage(userid, "%s has offered you to join \"%s\" (type \"/approve faction\").", ReturnName(playerid, 0), Faction_GetName(playerid));

	return 1;
}

CMD:fremove(playerid, params[])
{
    new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/fremove [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (PlayerData[userid][pFaction] != PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is not part of your faction.");

    SendServerMessage(playerid, "You have removed %s from \"%s\".", ReturnName(userid, 0), Faction_GetName(playerid));
    SendServerMessage(userid, "%s has removed you from the \"%s\" faction.", ReturnName(playerid, 0), Faction_GetName(playerid));

    ResetFaction(userid);

	return 1;
}

CMD:frank(playerid, params[])
{
    new
	    userid,
		rankid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "Anda perlu berada di dalam faction untuk menggunakan command ini.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "ud", userid, rankid))
	    return SendUsageMessage(playerid, "/frank [playerid/name] [rank (1-%d)]", FactionData[PlayerData[playerid][pFaction]][factionRanks]);

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot set your own rank.");

	if (PlayerData[userid][pFaction] != PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is not part of your faction.");

	if (rankid < 0 || rankid > FactionData[PlayerData[playerid][pFaction]][factionRanks])
	    return SendErrorMessage(playerid, "Invalid rank specified. Ranks range from 1 to %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks]);

	PlayerData[userid][pFactionRank] = rankid;

    SendServerMessage(playerid, "You have promoted %s to %s (%d).", ReturnName(userid, 0), Faction_GetRank(userid), rankid);
    SendServerMessage(userid, "%s has promoted you to %s (%d).", ReturnName(playerid, 0), Faction_GetRank(userid), rankid);

	return 1;
}

CMD:spawnpoint(playerid, params[])
{
	new point;
	if(sscanf(params, "i", point)) return SendUsageMessage(playerid, "/spawnpoint [0-2] (0 = Airport, 1 = Faction, 2 = Last logged)");
	if(point == 0)
	{
	    SendServerMessage(playerid, "You've changed your spawn point to airport.");
		PlayerData[playerid][pSpawnPoint] = 0;
		return 1;
	}
	if(point == 1)
	{
	    if(PlayerData[playerid][pFactionID] == -1)
	    {
	        SendErrorMessage(playerid, "You're not apart of a faction.");
	        return 1;
		}
		SendServerMessage(playerid, "You've changed your spawn to faction.");
		PlayerData[playerid][pSpawnPoint] = 1;
		return 1;
	}
	if(point == 2)
	{
	    SendServerMessage(playerid, "You've changed your spawn to your last logged off.");
		PlayerData[playerid][pSpawnPoint] = 2;
		return 1;
	}
	return 1;
}
CMD:fspawn(playerid, params[])
{
	new faction = PlayerData[playerid][pFactionID];

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction leader.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);
	
	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	FactionData[faction][SpawnX] = X;
	FactionData[faction][SpawnY] = Y;
	FactionData[faction][SpawnZ] = Z;
	FactionData[faction][SpawnInterior] = GetPlayerInterior(playerid);
	FactionData[faction][SpawnVW] = GetPlayerVirtualWorld(playerid);
	Faction_Save(faction);
	return 1;
}

CMD:tazer(playerid, params[])
{
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || !IsPlayerSpawned(playerid))
	    return SendErrorMessage(playerid, "You can't use this command right now.");

	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!PlayerData[playerid][pTazer])
	{
	    PlayerData[playerid][pTazer] = 1;
	    GetPlayerWeaponData(playerid, 2, PlayerData[playerid][pGuns][2], PlayerData[playerid][pAmmo][2]);

		GivePlayerWeapon(playerid, 23, 20000);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a tazer from their holster.", ReturnName(playerid, 0));
	}
	else
	{
	    PlayerData[playerid][pTazer] = 0;
		SetWeapons(playerid);

		SetPlayerArmedWeapon(playerid, PlayerData[playerid][pGuns][2]);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s puts their tazer into their holster.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:beanbag(playerid, params[])
{
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || !IsPlayerSpawned(playerid))
	    return SendErrorMessage(playerid, "You can't use this command right now.");

	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!PlayerData[playerid][pBeanBag])
	{
	    PlayerData[playerid][pBeanBag] = 1;
	    GetPlayerWeaponData(playerid, 3, PlayerData[playerid][pGuns][3], PlayerData[playerid][pAmmo][3]);

		GivePlayerWeapon(playerid, 25, 20000);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a beanbag shotgun.", ReturnName(playerid, 0));
	}
	else
	{
	    PlayerData[playerid][pBeanBag] = 0;
		SetWeapons(playerid);

		SetPlayerArmedWeapon(playerid, PlayerData[playerid][pGuns][3]);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s puts their beanbag shotgun away.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:cuff(playerid, params[])
{
    new
	    userid;

	if (!Inventory_HasItem(playerid, "Cuff"))
		return SendErrorMessage(playerid, "Anda tidak mempunyai item gari.");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/cuff [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot handcuff yourself.");

	if (!IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

    if (PlayerData[userid][pStunned] < 0 && GetPlayerSpecialAction(userid) != SPECIAL_ACTION_HANDSUP && !IsPlayerIdle(userid))
	    return SendErrorMessage(playerid, "The player must be idle or stunned.");

	if (GetPlayerState(userid) != PLAYER_STATE_ONFOOT)
	    return SendErrorMessage(playerid, "The player must be onfoot before you can cuff them.");

    if (PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player is already cuffed at the moment.");

    PlayerData[userid][pCuffed] = 1;
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);

	Inventory_Remove(playerid, "Cuff");

	SendInfoMessage(userid, "You've been cuffed by %s.", ReturnName(playerid, 0));

    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s tightens a pair of handcuffs on %s's wrists.", ReturnName(playerid, 0), ReturnName(userid, 0));
    return 1;
}

CMD:uncuff(playerid, params[])
{
    new
	    userid;

	if (!Inventory_HasItem(playerid, "Cuff Key"))
		return SendErrorMessage(playerid, "Anda tidak mempunyai kunci khas untuk membuka gari.");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/uncuff [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot uncuff yourself.");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

    if (!PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player is not cuffed at the moment.");

    PlayerData[userid][pCuffed] = 0;
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);

	SendInfoMessage(userid, "You've been uncuffed by %s.", ReturnName(playerid, 0));

    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s loosens the pair of handcuffs on %s's wrists.", ReturnName(playerid, 0), ReturnName(userid, 0));

	Inventory_Add(playerid, "Cuff", 11749, 1);
    return 1;
}

CMD:drag(playerid, params[])
{
	new
	    userid;

    if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/drag [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot drag yourself.");

	if (!IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

    if (!PlayerData[userid][pCuffed] && !PlayerData[userid][pStunned])
        return SendErrorMessage(playerid, "The player is not cuffed or stunned.");

	if (PlayerData[userid][pDragged])
	{
	    PlayerData[userid][pDragged] = 0;
	    PlayerData[userid][pDraggedBy] = INVALID_PLAYER_ID;

	    KillTimer(PlayerData[userid][pDragTimer]);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s releases %s from their grip.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	else
	{
	    PlayerData[userid][pDragged] = 1;
	    PlayerData[userid][pDraggedBy] = playerid;

	    PlayerData[userid][pDragTimer] = SetTimerEx("DragUpdate", 200, true, "dd", playerid, userid);
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s grabs %s and starts dragging them.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	return 1;
}

CMD:detain(playerid, params[])
{
	new
		userid,
		vehicleid = GetNearestVehicle(playerid);

	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/detain [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot detained yourself.");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

    if (!PlayerData[userid][pCuffed])
        return SendErrorMessage(playerid, "The player is not cuffed at the moment.");

	if (vehicleid == INVALID_VEHICLE_ID)
	    return SendErrorMessage(playerid, "You are not near any vehicle.");

	if (GetVehicleMaxSeats(vehicleid) < 2)
  	    return SendErrorMessage(playerid, "You can't detain that player in this vehicle.");

	if (IsPlayerInVehicle(userid, vehicleid))
	{
		TogglePlayerControllable(userid, 1);

		RemoveFromVehicle(userid);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens the door and pulls %s out the vehicle.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	else
	{
		new seatid = GetAvailableSeat(vehicleid, 2);

		if (seatid == -1)
		    return SendErrorMessage(playerid, "There are no more seats remaining.");

		SendInfoMessage(userid, "You've been detained by %s.", ReturnName(playerid, 0));
		TogglePlayerControllable(userid, 0);

		StopDragging(userid);
		PutPlayerInVehicle(userid, vehicleid, seatid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens the door and places %s into the vehicle.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	return 1;
}

CMD:mdc(playerid, params[])
{
    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsACruiser(GetPlayerVehicleID(playerid)))
	    return SendErrorMessage(playerid, "You must be inside a police cruiser.");

	Dialog_Show(playerid, MainMDC, DIALOG_STYLE_LIST, "Mobile Data Computer", "Active Warrants\nPlace Charges\nView Charges", "Select", "Cancel");
	return 1;
}

CMD:arrest(playerid, params[])
{
	static
	    userid,
		time;

    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1546.6732, 1349.8698, 1510.9160))
	    return SendErrorMessage(playerid, "You must be near an arrest point.");

	if (sscanf(params, "ud", userid, time))
	    return SendUsageMessage(playerid, "/arrest [playerid/name] [minutes]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "The player is disconnected or not near you.");

	if (time < 1 || time > 120)
	    return SendErrorMessage(playerid, "The specified time can't be below 1 or above 120.");

	if (!PlayerData[userid][pCuffed])
	    return SendErrorMessage(playerid, "The player must be cuffed before an arrest is made.");

	PlayerData[userid][pPrisoned] = 1;
	PlayerData[userid][pJailTime] = time * 60;

	StopDragging(userid);
	SetPlayerInPrison(userid);

	ResetWeapons(userid);
	ResetPlayer(userid);

	PlayerData[userid][pWarrants] = 0;
	PlayerData[userid][pCuffed] = 0;

    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);

    SendClientMessageToAllEx(COLOR_LIGHTRED, "[PRISON]: "WHITE_E"%s was imprisoned for %d days at Sakura Prison.", ReturnName(userid, 0), time);
    return 1;
}

CMD:seizeplant(playerid, params[])
{
	static
	    plantid;

    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if ((plantid = Plant_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "You are not standing near any drug plant.");

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has seized a %s plant weighing %d grams.", ReturnName(playerid, 0), Plant_GetType(PlantData[plantid][plantType]), PlantData[plantid][plantDrugs]);
	Plant_Delete(plantid);
	return 1;
}

CMD:loadinjured(playerid, params[])
{
	static
	    userid,
		seatid;

	if (GetFactionType(playerid) != FACTION_MEDIC)
	    return SendErrorMessage(playerid, "You must be part of a medical faction.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/loadinjured [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 10.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You can't load yourself into an ambulance.");

	if (!PlayerData[userid][pInjured])
	    return SendErrorMessage(playerid, "That player is not injured.");

	for (new i = 0; i != MAX_VEHICLES; i ++) if (IsPlayerNearBoot(playerid, i) && GetVehicleModel(i) == 416)
	{
	    seatid = GetAvailableSeat(i, 2);

	    if (seatid == -1)
	        return SendErrorMessage(playerid, "There is no room for the patient.");

		ClearAnimations(userid);
		PlayerData[userid][pInjured] = 2;

		PutPlayerInVehicle(userid, i, seatid);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens up the ambulance and loads %s on the stretcher.", ReturnName(playerid, 0), ReturnName(userid, 0));

		TogglePlayerControllable(userid, 0);
		SetPlayerHealthEx(userid, 100.0);
		return 1;
	}
	SendErrorMessage(playerid, "You must be near an ambulance.");
	return 1;
}

CMD:gr(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
	    return SendErrorMessage(playerid, "You can't use the gov radio.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
	    return SendUsageMessage(playerid, "/gr [message]");

	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionType] == FACTION_POLICE || FactionData[i][factionType] == FACTION_MEDIC) 
	{
		if (GetFactionType(playerid) == FACTION_POLICE) {
 		    SendFactionMessage(i, COLOR_RADIO, "** [GOV RADIO] (POLICE) %s: %s **", ReturnName(playerid, 0), params);
		}
  		else if (GetFactionType(playerid) == FACTION_MEDIC) {
 		    SendFactionMessage(i, COLOR_RADIO, "** [GOV RADIO] (MEDICAL) %s: %s **", ReturnName(playerid, 0), params);
		}

	}
	return 1;
}

CMD:m(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
	    return SendErrorMessage(playerid, "You can't use the megaphone.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
	    return SendUsageMessage(playerid, "/(m)egaphone [message]");

	if (strlen(params) > 64) {
	    SendNearbyMessage(playerid, 30.0, COLOR_YELLOW, "(Megaphone) %s says: %.64s", ReturnName(playerid, 0), params);
	    SendNearbyMessage(playerid, 30.0, COLOR_YELLOW, "...%s", params[64]);
	}
	else {
	    SendNearbyMessage(playerid, 30.0, COLOR_YELLOW, "(Megaphone) %s says: %s", ReturnName(playerid, 0), params);
	}
	return 1;
}

CMD:gov(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC)
	    return SendErrorMessage(playerid, "You can't use the government announcement.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if(isnull(params)) return SendUsageMessage(playerid, "/gov [text]");

	if(strlen(params) > 64) {
        SendClientMessageToAllEx(COLOR_YELLOW, "[Government]: "WHITE_E"%s: %.64s", ReturnName(playerid, 0), params);
        SendClientMessageToAllEx(COLOR_YELLOW, "...%s", params[64]);
    }
    else {
        SendClientMessageToAllEx(COLOR_YELLOW, "[Government]: "WHITE_E"%s: %s", ReturnName(playerid, 0), params);
    }
	return 1;
}

CMD:heal(playerid, params[])
{
    static
	    userid;

	if (GetFactionType(playerid) != FACTION_MEDIC)
	    return SendErrorMessage(playerid, "You must be part of a medical faction.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/heal [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 6.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You can't use this command for yourself.");

	if (PlayerData[userid][pFirstAid])
	    return SendErrorMessage(playerid, "That player is already being bandaged.");

    if (ReturnHealth(userid) > 99)
	    return SendErrorMessage(playerid, "That player doesn't need to be bandaged.");

    PlayerData[userid][pFirstAid] = true;
    PlayerData[userid][pAidTimer] = SetTimerEx("FirstAidUpdate", 1000, true, "d", userid);

    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s opens a first aid kit and uses a bandage on %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
    return 1;
}

CMD:pay(playerid, params[])
{
	static
	    userid,
	    amount;

	if (sscanf(params, "ud", userid, amount))
	    return SendUsageMessage(playerid, "/pay [playerid/name] [amount]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
		return SendErrorMessage(playerid, "You can't give yourself money.");

	if (amount < 1)
	    return SendErrorMessage(playerid, "Please specify an amount above RM1.");

	if (amount > 100 && PlayerData[playerid][pScore] < 2)
	    return SendErrorMessage(playerid, "You can't pay above RM100 with less than 2 score.");

	if (amount > GetMoney(playerid))
	    return SendErrorMessage(playerid, "You don't have that much money.");

	GiveMoney(playerid, -amount);
	GiveMoney(userid, amount);

	SendInfoMessage(userid, "You have received %s from %s.", FormatNumber(amount), ReturnName(playerid, 0));

	SendServerMessage(playerid, "You have given %s to %s.", FormatNumber(amount), ReturnName(userid, 0));

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out %s from their wallet and hands it to %s.", ReturnName(playerid, 0), FormatNumber(amount), ReturnName(userid, 0));
	Log_Write("logs/pay_log.txt", "[%s] %s (%s) has paid %s to %s (%s).", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], FormatNumber(amount), ReturnName(userid, 0), PlayerData[userid][pIP]);

	return 1;
}

CMD:factions(playerid, params[])
{
	ViewFactions(playerid);
	return 1;
}

CMD:gps(playerid, params[])
{
	if (!Inventory_HasItem(playerid, "GPS System"))
	    return SendErrorMessage(playerid, "You must have a GPS system to use this.");

	if (PlayerData[playerid][pInjured] || PlayerData[playerid][pLoading] > 0 || PlayerData[playerid][pUnloading] != -1 || PlayerData[playerid][pDeliverShipment] > 0)
	    return SendErrorMessage(playerid, "You can't use this command at the moment.");

	Dialog_Show(playerid, MainGPS, DIALOG_STYLE_LIST, "GPS System", "General Location\nFind House\nFind Business\nFind Job\nFind Sidejob\nCustom Locations", "Select", "Cancel");
	return 1;
}

CMD:ticket(playerid, params[])
{
	static
	    userid,
	    price,
	    reason[64];

	if (GetFactionType(playerid) != FACTION_POLICE && GetFactionType(playerid) != FACTION_MEDIC && GetFactionType(playerid) != FACTION_MECHANIC)
	    return SendErrorMessage(playerid, "You can't use the ticket.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "uds[64]", userid, price, reason))
		return SendUsageMessage(playerid, "/ticket [playerid/name] [price] [reason]");

	new factionid = PlayerData[playerid][pFaction]; 

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (price < 1 || price > 10000)
	    return SendErrorMessage(playerid, "The price can't be below RM1 or above RM10,000.");

	new id = Ticket_Add(userid, price, factionid, reason);

	if (id != -1) {
	    SendServerMessage(playerid, "You have written %s a ticket for %s, reason: %s", ReturnName(userid, 0), FormatNumber(price), reason);
	    SendServerMessage(userid, "%s has written you a ticket for %s, reason: %s", ReturnName(playerid, 0), FormatNumber(price), reason);

	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has written up a ticket for%s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	    Log_Write("logs/ticket_log.txt", "[%s] %s has written a %s ticket to %s, reason: %s", ReturnDate(), ReturnName(playerid, 0), FormatNumber(price), ReturnName(userid, 0), reason);
	}
	else {
	    SendErrorMessage(playerid, "That player already has %d outstanding tickets.", MAX_PLAYER_TICKETS);
	}
	return 1;
}

CMD:drone(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You are not a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

    new str[128];
    if(sscanf(params, "s", str)) return SendUsageMessage(playerid, "/drone [spawn/detonate/destroy]");
 
    if(strcmp(str, "spawn") == 0) 
	{
        if( GetPVarInt( playerid, "DroneSpawned" ) == 0 ) 
		{
            new Float:Health;
            GetPlayerHealth( playerid, Health );
 
            if(Health != 0) 
			{
                new Float:PosX, Float:PosY, Float:PosZ;
                GetPlayerPos( playerid, PosX, PosY, PosZ );
                SetPVarFloat( playerid, "OldPosX", PosX );
                SetPVarFloat( playerid, "OldPosY", PosY );
                SetPVarFloat( playerid, "OldPosZ", PosZ );
                SetPVarInt( playerid, "DroneSpawned", 1 );
                SendServerMessage( playerid, "You have successfully spawned a drone." );
                PoliceDrone[playerid] = CreateVehicle( 465, PosX, PosY, PosZ + 20, 0, 0, 0, 0, -1 );
                PutPlayerInVehicle( playerid, PoliceDrone[playerid], 0 );
            }
        } 
		else 
		{
            SendErrorMessage( playerid, "You already have a drone spawned in!" );
        }
    }
	else 
	{
        if( strcmp( str, "detonate" ) == 0 ) 
		{
            if( GetPVarInt( playerid, "DroneSpawned" ) == 1 ) 
			{
                new Float:PosX, Float:PosY, Float:PosZ;
                GetVehiclePos( PoliceDrone[playerid], PosX, PosY, PosZ );
 
                SetPVarInt( playerid, "DroneSpawned", 0 );
                SendServerMessage( playerid, "Drone successfully detonated." );
                DestroyVehicle( PoliceDrone[playerid] );
 
                CreateExplosion( PosX, PosY, PosZ, 7, 25 );
 
                SetPlayerPos(playerid, GetPVarFloat( playerid, "OldPosX" ), GetPVarFloat( playerid, "OldPosY" ), GetPVarFloat( playerid, "OldPosZ" ));
            } 
			else 
			{
                SendErrorMessage( playerid, "You need to have a drone spawned in!" );
            }
        } 
		else 
		{
            if( strcmp( str, "destroy" ) == 0 ) 
			{
                if( GetPVarInt( playerid, "DroneSpawned" ) == 1 ) 
				{
                    SetPVarInt( playerid, "DroneSpawned", 0 );
                    SendServerMessage( playerid, "You have shut your drone down." );
                    DestroyVehicle( PoliceDrone[playerid] );
 
                    SetPlayerPos(playerid, GetPVarFloat( playerid, "OldPosX" ), GetPVarFloat( playerid, "OldPosY" ), GetPVarFloat( playerid, "OldPosZ" ));
                } 
				else 
				{
                    SendErrorMessage( playerid, "You need to have a drone spawned in!" );
                }
            }
        }
    }
    return 1;
}

CMD:spike(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You are not a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
 	{
	 	SendUsageMessage(playerid, "/spike [option]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[OPTIONS]:{FFFFFF} drop, destroy, destroyall");
		return 1;
	}
	static
        Float:fX,
        Float:fY,
        Float:fZ,
        Float:fA;

    GetPlayerPos(playerid, fX, fY, fZ);
    GetPlayerFacingAngle(playerid, fA);

	if (!strcmp(params, "drop", true))
	{
	    if (IsPlayerInAnyVehicle(playerid))
	        return SendErrorMessage(playerid, "You must exit the vehicle first.");

	    for (new i = 0; i != MAX_BARRICADES; i ++) if (!BarricadeData[i][cadeExists])
	    {
            BarricadeData[i][cadeExists] = true;
            BarricadeData[i][cadeType] = 1;

            BarricadeData[i][cadePos][0] = fX;
            BarricadeData[i][cadePos][1] = fY;
            BarricadeData[i][cadePos][2] = fZ;

            BarricadeData[i][cadeObject] = CreateDynamicObject(2899, fX, fY, fZ - 0.8, 0.0, 0.0, fA + 90.0);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has dropped a spikestrip.", ReturnName(playerid, 0));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has dropped a spikestrip at %s.", ReturnName(playerid, 0), GetLocation(fX, fY, fZ));

			return 1;
		}
		SendErrorMessage(playerid, "The server has reached the limit for spikestrips.");
	}
	else if (!strcmp(params, "destroy", true))
	{
        for (new i = 0; i != MAX_BARRICADES; i ++) if (BarricadeData[i][cadeExists] && BarricadeData[i][cadeType] == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, BarricadeData[i][cadePos][0], BarricadeData[i][cadePos][1], BarricadeData[i][cadePos][2]))
	    {
            BarricadeData[i][cadeExists] = 0;
            BarricadeData[i][cadeType] = 0;

            DestroyDynamicObject(BarricadeData[i][cadeObject]);

            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a spikestrip.", ReturnName(playerid, 0));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has picked up a spikestrip at %s.", ReturnName(playerid, 0), GetLocation(fX, fY, fZ));
			return 1;
		}
		SendErrorMessage(playerid, "You are not in range of any spikestrip.");
	}
	else if (!strcmp(params, "destroyall", true))
	{
        for (new i = 0; i != MAX_BARRICADES; i ++) if (BarricadeData[i][cadeExists] && BarricadeData[i][cadeType] == 1)
	    {
            BarricadeData[i][cadeExists] = 0;
            BarricadeData[i][cadeType] = 0;

			DestroyDynamicObject(BarricadeData[i][cadeObject]);
		}
		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has destroyed all of the spikestrips.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:roadblock(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You are not a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
 	{
	 	SendUsageMessage(playerid, "/roadblock [option]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[OPTIONS]:{FFFFFF} drop, destroy, destroyall");
		return 1;
	}
	static
        Float:fX,
        Float:fY,
        Float:fZ,
        Float:fA;

    GetPlayerPos(playerid, fX, fY, fZ);
    GetPlayerFacingAngle(playerid, fA);

	if (!strcmp(params, "drop", true))
	{
	    if (IsPlayerInAnyVehicle(playerid))
	        return SendErrorMessage(playerid, "You must exit the vehicle first.");

	    for (new i = 0; i != MAX_BARRICADES; i ++) if (!BarricadeData[i][cadeExists])
	    {
            BarricadeData[i][cadeExists] = true;
            BarricadeData[i][cadeType] = 2;

            BarricadeData[i][cadePos][0] = fX;
            BarricadeData[i][cadePos][1] = fY;
            BarricadeData[i][cadePos][2] = fZ;

            BarricadeData[i][cadeObject] = CreateDynamicObject(981, fX, fY, fZ, 0.0, 0.0, fA);
            SetPlayerPos(playerid, fX + 2, fY + 2, fZ + 2);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has dropped a roadblock.", ReturnName(playerid, 0));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has dropped a roadblock at %s.", ReturnName(playerid, 0), GetLocation(fX, fY, fZ));

			return 1;
		}
		SendErrorMessage(playerid, "The server has reached the limit for roadblock.");
	}
	else if (!strcmp(params, "destroy", true))
	{
        for (new i = 0; i != MAX_BARRICADES; i ++) if (BarricadeData[i][cadeExists] && BarricadeData[i][cadeType] == 2 && IsPlayerInRangeOfPoint(playerid, 5.0, BarricadeData[i][cadePos][0], BarricadeData[i][cadePos][1], BarricadeData[i][cadePos][2]))
	    {
            BarricadeData[i][cadeExists] = 0;
            BarricadeData[i][cadeType] = 0;

            DestroyDynamicObject(BarricadeData[i][cadeObject]);

            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a roadblock.", ReturnName(playerid, 0));
			SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has picked up a roadblock at %s.", ReturnName(playerid, 0), GetLocation(fX, fY, fZ));
			return 1;
		}
		SendErrorMessage(playerid, "You are not in range of any roadblock.");
	}
	else if (!strcmp(params, "destroyall", true))
	{
        for (new i = 0; i != MAX_BARRICADES; i ++) if (BarricadeData[i][cadeExists] && BarricadeData[i][cadeType] == 2)
	    {
            BarricadeData[i][cadeExists] = 0;
            BarricadeData[i][cadeType] = 0;

			DestroyDynamicObject(BarricadeData[i][cadeObject]);
		}
		SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has destroyed all of the roadblocks.", ReturnName(playerid, 0));
	}
	return 1;
}


CMD:deleteaccount(playerid, params[])
{
	static
	    query[64];

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params) || strlen(params) > 24)
	    return SendUsageMessage(playerid, "/deleteaccount [username]");

    if (!IsValidPlayerName(params))
	    return SendErrorMessage(playerid, "You have specified an invalid name format.");

	foreach (new i : Player) if (!strcmp(PlayerData[i][pUsername], params, true)) {
	    return SendErrorMessage(playerid, "You can't delete an online player's account.");
	}
	format(query, sizeof(query), "SELECT * FROM `accounts` WHERE `Username` = '%s'", SQL_ReturnEscaped(params));
	mysql_tquery(g_iHandle, query, "OnDeleteAccount", "ds", playerid, params);

	return 1;
}

CMD:doorbell(playerid, params[])
{
	new id = House_Nearest(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "You must be standing near a house.");

	foreach (new i : Player) if (House_Inside(i) == id) {
	    SendClientMessage(i, COLOR_PURPLE, "** You can hear the doorbell ringing.");
	    //PlayerPlaySound(i, 20801, 0, 0, 0);
		PlayAudioStreamForPlayer(i, "http://k.top4top.io/m_29847r5dp0.mp3");
	}
	//PlayerPlaySoundEx(playerid, 20801);
	PlayAudioStreamForPlayer(playerid, "http://k.top4top.io/m_29847r5dp0.mp3");
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s rings the doorbell of the house.", ReturnName(playerid, 0));
	return 1;
}

CMD:creategate(playerid, params[])
{
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	id = Gate_Create(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for gates.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created gate ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroygate(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroygate [gate id]");

	if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
	    return SendErrorMessage(playerid, "You have specified an invalid gate ID.");

	Gate_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed gate ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:editgate(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendUsageMessage(playerid, "/editgate [id] [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, speed, radius, time, model, pos, move, pass, linkid, faction");
		return 1;
	}
	if ((id < 0 || id >= MAX_GATES) || !GateData[id][gateExists])
	    return SendErrorMessage(playerid, "You have specified an invalid gate ID.");

    if (!strcmp(type, "location", true))
	{
		static
		    Float:x,
		    Float:y,
		    Float:z,
		    Float:angle;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		x += 3.0 * floatsin(-angle, degrees);
		y += 3.0 * floatcos(-angle, degrees);

		GateData[id][gatePos][0] = x;
		GateData[id][gatePos][1] = y;
		GateData[id][gatePos][2] = z;
		GateData[id][gatePos][3] = 0.0;
		GateData[id][gatePos][4] = 0.0;
		GateData[id][gatePos][5] = angle;

		SetDynamicObjectPos(GateData[id][gateObject], x, y, z);
		SetDynamicObjectRot(GateData[id][gateObject], 0.0, 0.0, angle);

		GateData[id][gateOpened] = false;

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the position of gate ID: %d.", ReturnName(playerid, 0), id);
		return 1;
	}
	else if (!strcmp(type, "speed", true))
	{
	    static
	        Float:speed;

		if (sscanf(string, "f", speed))
		    return SendUsageMessage(playerid, "/editgate [id] [speed] [move speed]");

		if (speed < 0.0 || speed > 20.0)
		    return SendErrorMessage(playerid, "The specified speed can't be below 0 or above 20.");

        GateData[id][gateSpeed] = speed;

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the speed of gate ID: %d to %.2f.", ReturnName(playerid, 0), id, speed);
		return 1;
	}
	else if (!strcmp(type, "radius", true))
	{
	    static
	        Float:radius;

		if (sscanf(string, "f", radius))
		    return SendUsageMessage(playerid, "/editgate [id] [radius] [open radius]");

		if (radius < 0.0 || radius > 20.0)
		    return SendErrorMessage(playerid, "The specified radius can't be below 0 or above 20.");

        GateData[id][gateRadius] = radius;

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the radius of gate ID: %d to %.2f.", ReturnName(playerid, 0), id, radius);
		return 1;
	}
	else if (!strcmp(type, "time", true))
	{
	    static
	        time;

		if (sscanf(string, "d", time))
		    return SendUsageMessage(playerid, "/editgate [id] [time] [close time] (0 to disable)");

		if (time < 0 || time > 60000)
		    return SendErrorMessage(playerid, "The specified time can't be 0 or above 60,000 ms.");

        GateData[id][gateTime] = time;

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the close time of gate ID: %d to %d.", ReturnName(playerid, 0), id, time);
		return 1;
	}
	else if (!strcmp(type, "model", true))
	{
	    static
	        model;

		if (sscanf(string, "d", model))
		    return SendUsageMessage(playerid, "/editgate [id] [model] [gate model]");

		if (!IsValidObjectModel(model))
		    return SendErrorMessage(playerid, "Invalid object model.");

        GateData[id][gateModel] = model;

		DestroyDynamicObject(GateData[id][gateObject]);
		GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the model of gate ID: %d to %d.", ReturnName(playerid, 0), id, model);
		return 1;
	}
    else if (!strcmp(type, "pos", true))
	{
	    ResetEditing(playerid);
	   	EditDynamicObject(playerid, GateData[id][gateObject]);

		PlayerData[playerid][pEditGate] = id;
		PlayerData[playerid][pEditType] = 1;

		SendServerMessage(playerid, "You are now adjusting the position of gate ID: %d.", id);
		return 1;
	}
	else if (!strcmp(type, "move", true))
	{
	    ResetEditing(playerid);
	   	EditDynamicObject(playerid, GateData[id][gateObject]);

		PlayerData[playerid][pEditGate] = id;
		PlayerData[playerid][pEditType] = 2;

		SendServerMessage(playerid, "You are now adjusting the moving position of gate ID: %d.", id);
		return 1;
	}
	else if (!strcmp(type, "linkid", true))
	{
	    static
	        linkid = -1;

		if (sscanf(string, "d", linkid))
		    return SendUsageMessage(playerid, "/editgate [id] [linkid] [gate link] (-1 for none)");

        if ((linkid < -1 || linkid >= MAX_GATES) || (linkid != -1 && !GateData[linkid][gateExists]))
	    	return SendErrorMessage(playerid, "You have specified an invalid gate ID.");

        GateData[id][gateLinkID] = (linkid == -1) ? (-1) : (GateData[linkid][gateID]);
		Gate_Save(id);

		if (id == -1)
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the link of gate ID: %d to no gate.", ReturnName(playerid, 0), id);

		else
		    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the link of gate ID: %d to ID: %d.", ReturnName(playerid, 0), id, linkid);

		return 1;
	}
	else if (!strcmp(type, "faction", true))
	{
	    static
	        factionid = -1;

		if (sscanf(string, "d", factionid))
		    return SendUsageMessage(playerid, "/editgate [id] [faction] [gate faction] (-1 for none)");

        if ((factionid < -1 || factionid >= MAX_FACTIONS) || (factionid != -1 && !FactionData[factionid][factionExists]))
	    	return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

        GateData[id][gateFaction] = (factionid == -1) ? (-1) : (FactionData[factionid][factionID]);
		Gate_Save(id);

		if (factionid == -1)
			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the faction of gate ID: %d to no faction.", ReturnName(playerid, 0), id);

		else
		    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the faction of gate ID: %d to \"%s\".", ReturnName(playerid, 0), id, FactionData[factionid][factionName]);

		return 1;
	}
	else if (!strcmp(type, "pass", true))
	{
	    static
	        pass[32];

		if (sscanf(string, "s[32]", pass))
		    return SendUsageMessage(playerid, "/editgate [id] [pass] [gate password] (Use 'none' to disable)");

		if (!strcmp(params, "none", true))
			GateData[id][gatePass][0] = 0;

		else format(GateData[id][gatePass], 32, pass);

		Gate_Save(id);
		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has adjusted the password of gate ID: %d to %s.", ReturnName(playerid, 0), id, pass);
		return 1;
	}
	return 1;
}

CMD:givecash(playerid, params[])
{
	static
		userid,
	    amount;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, amount))
		return SendUsageMessage(playerid, "/givecash [playerid/name] [amount]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	GiveMoney(userid, amount);

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has given %s to %s.", ReturnName(playerid, 0), FormatNumber(amount), ReturnName(userid, 0));
 	Log_Write("logs/admin_log.txt", "[%s] %s has given %s to %s.", ReturnDate(), ReturnName(playerid, 0), FormatNumber(amount), ReturnName(userid, 0));

	return 1;
}

CMD:usedrug(playerid, params[])
{
	if (isnull(params))
	{
	    SendUsageMessage(playerid, "/usedrug [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} marijuana, cocaine, heroin, steroids");
		return 1;
	}
	if (PlayerData[playerid][pDrugTime] > 0)
	    return SendErrorMessage(playerid, "Please wait until the effects have subsided first.");

	if (!strcmp(params, "marijuana", true))
	{
	    if (Inventory_Count(playerid, "Marijuana") < 2)
	        return SendErrorMessage(playerid, "You need at least 2 grams of marijuana.");

        PlayerData[playerid][pDrugTime] = 20;
		PlayerData[playerid][pDrugUsed] = 1;

		Inventory_Remove(playerid, "Marijuana", 2);
		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a lighter and lights up a joint.", ReturnName(playerid, 0));

		PlayerData[playerid][pUraine] = 1;
	}
	else if (!strcmp(params, "cocaine", true))
	{
	    if (Inventory_Count(playerid, "Cocaine") < 2)
	        return SendErrorMessage(playerid, "You need at least 2 grams of cocaine.");

        PlayerData[playerid][pDrugTime] = 35;
		PlayerData[playerid][pDrugUsed] = 2;

		Inventory_Remove(playerid, "Cocaine", 2);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out some cocaine and snorts it.", ReturnName(playerid, 0));

		PlayerData[playerid][pUraine] = 1;
	}
	else if (!strcmp(params, "heroin", true))
	{
	    if (Inventory_Count(playerid, "Heroin") < 2)
	        return SendErrorMessage(playerid, "You need at least 2 grams of heroin.");

        PlayerData[playerid][pDrugTime] = 30;
		PlayerData[playerid][pDrugUsed] = 3;

		Inventory_Remove(playerid, "Heroin", 2);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out some heroin and injects it.", ReturnName(playerid, 0));

		PlayerData[playerid][pUraine] = 1;
	}
	else if (!strcmp(params, "steroids", true))
	{
	    if (!Inventory_HasItem(playerid, "Steroids"))
	        return SendErrorMessage(playerid, "You need at least one steroid pill.");

		if (ReturnHealth(playerid) <= 5)
		    return SendErrorMessage(playerid, "Your health is too low to take steroids.");

        PlayerData[playerid][pDrugTime] = 60;
		PlayerData[playerid][pDrugUsed] = 4;

		SetPlayerHealthEx(playerid, ReturnHealth(playerid) - 5);
		Inventory_Remove(playerid, "Steroids", 2);

		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out some steroids and swallows them.", ReturnName(playerid, 0));

		PlayerData[playerid][pUraine] = 1;
	}
	return 1;
}

CMD:sb(playerid, params[])
{	
	if (!IsDoorVehicle(GetPlayerVehicleID(playerid)))
		return SendErrorMessage(playerid, "This vehicle doesn't have a seatbelt.");

	if(IsPlayerInAnyVehicle(playerid) == 1 && PlayerData[playerid][pSeatBelt] == 0)
	{
		SendClientMessage(playerid, COLOR_WHITE, "SEATBELT: "GREEN_E"ON");
		PlayerData[playerid][pSeatBelt] = 1;
		for (new i = 0; i < 3; i ++) 
		{
			TextDrawHideForPlayer(playerid, NoSEATBELT[playerid][i]);
		}
	}
	else if(IsPlayerInAnyVehicle(playerid) == 1 && PlayerData[playerid][pSeatBelt] == 1)
	{
		SendClientMessage(playerid, COLOR_WHITE, "SEATBELT: "RED_E"OFF");
		PlayerData[playerid][pSeatBelt] = 0;
		for (new i = 0; i < 3; i ++) 
		{
			TextDrawShowForPlayer(playerid, NoSEATBELT[playerid][i]);
		}
	}
	return 1;
}

CMD:checkurine(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_MEDIC)
		return SendErrorMessage(playerid, "You must be a medical.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new target;
	if(sscanf(params, "u", target))
	    return SendUsageMessage(playerid, "/checkurine [playerid/name]");
	    
    if(target == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, target, 4.0))
        return SendErrorMessage(playerid, "Invalid player or you're not close with that player!");
        
	SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "* %s checking %s's uraine status", ReturnName(playerid, 0), ReturnName(target, 0));
	SendServerMessage(playerid, "{FFFFFF}%s uraine status is %s {FFFFFF}!", ReturnName(target, 0), (!PlayerData[playerid][pUraine]) ? ("{FF0000}Negatif") : ("{00FF00}Positif"));
	return 1;
}

CMD:checkbelt(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new target;
	if(sscanf(params, "u", target))
	    return SendUsageMessage(playerid, "/checkbelt [playerid/name]");
	    
    if(target == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, target, 4.0))
        return SendErrorMessage(playerid, "Invalid player or you're not close with that player!");
        
	if(!IsPlayerInAnyVehicle(target))
	    return SendErrorMessage(playerid, "That player is no inside vehicle!");
	    
	SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "* %s checking %s's seatbelt status", ReturnName(playerid, 0), ReturnName(target, 0));
	SendServerMessage(playerid, "{FFFFFF}%s is %s {FFFFFF}a Seatbelt!", ReturnName(target, 0), (!PlayerData[playerid][pSeatBelt]) ? ("{FF0000}Not using") : ("{00FF00}Using"));
	return 1;
}

CMD:fingerprint(playerid, params[])
{
    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (PlayerData[playerid][pFingerTime] > 0)
	    return SendErrorMessage(playerid, "You are already using the fingerprint scanner.");

    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2])) {
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s runs the fingerprint scanner over the item.", ReturnName(playerid, 0));

        PlayerData[playerid][pFingerTime] = 3;
        PlayerData[playerid][pFingerItem] = i;

        return 1;
	}
	SendErrorMessage(playerid, "There is no item nearby.");
	return 1;
}

CMD:dropbackpack(playerid, params[])
{
	new
		id = GetPlayerBackpack(playerid);

	if (!Inventory_HasItem(playerid, "Backpack") || id == -1)
	    return SendErrorMessage(playerid, "You don't have a backpack on you.");

	if (!Backpack_GetItems(id))
	    return SendErrorMessage(playerid, "You can't drop an empty backpack.");

    if (IsPlayerInAnyVehicle(playerid) || !IsPlayerSpawned(playerid))
    	return SendErrorMessage(playerid, "You can't drop your backpack right now.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);

	BackpackData[id][backpackPlayer] = 0;
    BackpackData[id][backpackPos][0] = x;
    BackpackData[id][backpackPos][1] = y;
    BackpackData[id][backpackPos][2] = z;
    BackpackData[id][backpackInterior] = GetPlayerInterior(playerid);
    BackpackData[id][backpackWorld] = GetPlayerVirtualWorld(playerid);

	Backpack_Refresh(id);
	Backpack_Save(id);

	Inventory_Remove(playerid, "Backpack");
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has dropped their backpack.", ReturnName(playerid, 0));

	SetAccessories(playerid);

	return 1;
}

CMD:setitem(playerid, params[])
{
	static
	    userid,
		item[32],
		amount;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "uds[32]", userid, amount, item))
	    return SendUsageMessage(playerid, "/setitem [playerid/name] [amount] [item name]");

    if (IsFurnitureItem(item))
	{
	    for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (!strcmp(g_aFurnitureData[i][e_FurnitureName], item, true))
		{
	        Inventory_Set(userid, g_aFurnitureData[i][e_FurnitureName], g_aFurnitureData[i][e_FurnitureModel], amount);

			SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set %s item %s to %d.", ReturnName(playerid, 0), item, ReturnName(userid, 0), amount);

			SendServerMessage(userid, "%s has set your \"%s\" to %d.", ReturnName(userid, 0), item, amount);
			return 1;
		}
	}
	else for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
	    if (!strcmp(item, "Cellphone", true)) {
	        PlayerData[userid][pPhone] = random(90000) + 10000;
	    }
        Inventory_Set(userid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);

		SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has set %s item %s to %d.", ReturnName(playerid, 0), item, ReturnName(userid, 0), amount);

		return SendServerMessage(userid, "%s has set your \"%s\" to %d.", ReturnName(userid, 0), item, amount);
	}
	SendErrorMessage(playerid, "Invalid item name (use /itemlist for a list).");
	return 1;
}

CMD:itemlist(playerid, params[])
{
	static
	    string[1024];

	if (!strlen(string)) {
		for (new i = 0; i < sizeof(g_aInventoryItems); i ++) {
			format(string, sizeof(string), "%s%s\n", string, g_aInventoryItems[i][e_InventoryItem]);
		}
	}
	return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_LIST, "List of Items", string, "Select", "Cancel");
}

CMD:tow(playerid, params[])
{
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return SendErrorMessage(playerid, "You are not driving a tow truck.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
	    return SendErrorMessage(playerid, "You are not the driver.");

	new vehicleid = GetVehicleFromBehind(GetPlayerVehicleID(playerid));

	if (IsValidVehicle(vehicleid))
	    return SendErrorMessage(playerid, "There is no vehicle in range.");

	if (!IsDoorVehicle(vehicleid) || IsAPlane(vehicleid) || IsABoat(vehicleid) || IsAHelicopter(vehicleid))
	    return SendErrorMessage(playerid, "You can't tow this vehicle.");

	AttachTrailerToVehicle(vehicleid, GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has hooked a %s onto their tow truck.", ReturnName(playerid, 0), ReturnVehicleName(vehicleid));
	return 1;
}

CMD:untow(playerid, params[])
{
	if (GetVehicleModel(GetPlayerVehicleID(playerid)) != 525)
	    return SendErrorMessage(playerid, "You are not driving a tow truck.");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "You are not the driver.");

	new
	    trailerid = GetVehicleTrailer(GetPlayerVehicleID(playerid));

    if (!trailerid)
	    return SendErrorMessage(playerid, "There is no vehicle hooked onto the truck.");

	DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has unhooked the %s from the tow truck.", ReturnName(playerid, 0), ReturnVehicleName(trailerid));

	return 1;
}

CMD:impound(playerid, params[])
{
	new
		price,
		vehicleid = GetPlayerVehicleID(playerid);

    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

    if (sscanf(params, "d", price))
        return SendUsageMessage(playerid, "/impound [price]");

	if (price < 1 || price > 1000)
	    return SendErrorMessage(playerid, "The price can't be above RM1,000 or below RM1.");

 	vehicleid = Car_GetID(vehicleid);

	if (vehicleid == -1)
	    return SendErrorMessage(playerid, "You can't impound this vehicle.");

	CarData[vehicleid][carImpounded] = 1;
	CarData[vehicleid][carImpoundPrice] = price;

	GetVehiclePos(CarData[vehicleid][carVehicle], CarData[vehicleid][carPos][0], CarData[vehicleid][carPos][1], CarData[vehicleid][carPos][2]);
	Car_Save(vehicleid);

	if(IsValidVehicle(CarData[vehicleid][carVehicle])) DestroyVehicle(CarData[vehicleid][carVehicle]);

	CarData[vehicleid][carVehicle] = 0;

	SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has impounded a %s for %s.", ReturnName(playerid, 0), ReturnVehicleModelName(CarData[vehicleid][carModel]), FormatNumber(price));
	return 1;
}

CMD:channel(playerid, params[])
{
	new channel;

	if (!Inventory_HasItem(playerid, "Portable Radio"))
	    return SendErrorMessage(playerid, "You must have a portable radio.");

	if (sscanf(params, "d", channel))
 	{
	 	SendUsageMessage(playerid, "/channel [radio channel] (0 to disable)");

	 	if (PlayerData[playerid][pChannel] > 0)
			SendClientMessageEx(playerid, COLOR_YELLOW, "[NOTE]:{FFFFFF} Your current radio channel is set to %d.", PlayerData[playerid][pChannel]);

		return 1;
	}
	if (channel < 0 || channel > 999999)
	    return SendErrorMessage(playerid, "The channel can't be below 0 or above 999,999.");

	PlayerData[playerid][pChannel] = channel;

	if (channel == 0)
	    SendServerMessage(playerid, "You have disabled your portable radio.");

	else SendServerMessage(playerid, "You have set your radio's channel to %d (\"/r [text]\" to chat).", channel);
	return 1;
}

CMD:r(playerid, params[])
{
	if (isnull(params))
	    return SendUsageMessage(playerid, "/r [Radio]");

    if (!Inventory_HasItem(playerid, "Portable Radio"))
	    return SendErrorMessage(playerid, "You must have a portable radio.");

	if (!PlayerData[playerid][pChannel])
	    return SendErrorMessage(playerid, "Your portable radio is disabled (/channel).");

	static
	    string[128];

	if (strlen(params) > 64)
	{
		format(string, sizeof(string), "** [RADIO: %dMHZ] %s: %.64s",PlayerData[playerid][pChannel],ReturnName(playerid, 0), params);
		SendRadioMessage(PlayerData[playerid][pChannel], COLOR_SERVER, string);
		format(string, sizeof(string), "...%s **",params[64]);
		SendRadioMessage(PlayerData[playerid][pChannel], COLOR_SERVER, string);
	}
	else {
		format(string, sizeof(string),"** [RADIO %dMHZ] %s: %s **", PlayerData[playerid][pChannel],ReturnName(playerid, 0), params);
		SendRadioMessage(PlayerData[playerid][pChannel], COLOR_SERVER, string);
	}
	return 1;
}

CMD:createatm(playerid, params[])
{
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	id = ATM_Create(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for ATM machines.");

	SendAdminAlert(COLOR_RED, "[ADMIN]: "WHITE_E"%s has created atm ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroyatm(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyatm [atm id]");

	if ((id < 0 || id >= MAX_ATM_MACHINES) || !ATMData[id][atmExists])
	    return SendErrorMessage(playerid, "You have specified an invalid ATM ID.");

	ATM_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed house ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:disablecp(playerid, params[])
{
	if (PlayerData[playerid][pDrivingTest])
	    return SendErrorMessage(playerid, "You can't do this during your driving test.");

	PlayerData[playerid][pCP] = 0;

	if (PlayerData[playerid][pSorting] != -1)
	{
	    PlayerData[playerid][pSorting] = -1;
		PlayerData[playerid][pSortCrate] = 0;

		RemovePlayerAttachedObject(playerid, 4);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	if (PlayerData[playerid][pMinedRock])
	{
	    PlayerData[playerid][pMinedRock] = 0;
		PlayerData[playerid][pMineCount] = 0;

		RemovePlayerAttachedObject(playerid, 4);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
	if (PlayerData[playerid][pUnloading] != -1)
	{
	    PlayerData[playerid][pUnloading] = -1;
	    PlayerData[playerid][pUnloadVehicle] = INVALID_VEHICLE_ID;
	}
	if (PlayerData[playerid][pLoading])
	{
	    PlayerData[playerid][pLoading] = 0;
	    PlayerData[playerid][pLoadType] = 0;
	}
	if (PlayerData[playerid][pLoadCrate])
 	{
  		PlayerData[playerid][pLoadCrate] = 0;

		RemovePlayerAttachedObject(playerid, 4);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	}
    DisablePlayerCheckpoint(playerid);
    SendServerMessage(playerid, "You have disabled any active checkpoints.");
    return 1;
}

CMD:asellhouse(playerid, params[])
{
	new houseid = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", houseid))
	    return SendUsageMessage(playerid, "/asellhouse [house ID]");

	if ((houseid < 0 || houseid >= MAX_HOUSES) || !HouseData[houseid][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	HouseData[houseid][houseOwner] = 0;

	House_Refresh(houseid);
	House_Save(houseid);

	SendServerMessage(playerid, "You have sold house ID: %d.", houseid);
	return 1;
}

CMD:asellbiz(playerid, params[])
{
	new bizid = -1;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", bizid))
	    return SendUsageMessage(playerid, "/asellbiz [business ID]");

	if ((bizid < 0 || bizid >= MAX_HOUSES) || !BusinessData[bizid][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	BusinessData[bizid][bizOwner] = 0;

	Business_Refresh(bizid);
	Business_Save(bizid);

	SendServerMessage(playerid, "You have sold business ID: %d.", bizid);
	return 1;
}

CMD:revokeweapon(playerid, params[])
{
	new userid;

	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You must be an officer or a government member.");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/revokeweapon [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You can't revoke your own weapon license.");

	if (!Inventory_HasItem(userid, "Weapon License"))
	    return SendErrorMessage(playerid, "That player doesn't have a weapon license.");

	Inventory_Remove(userid, "Weapon License");

	SendServerMessage(playerid, "You have revoked %s's weapon license.", ReturnName(userid, 0));
	SendServerMessage(userid, "Your weapon license was revoked by %s.", ReturnName(playerid, 0));

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has revoked %s's weapon license.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:jetpack(playerid, params[])
{
	new userid;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
 	{
 	    PlayerData[playerid][pJetpack] = 1;
	 	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	}
	else
	{
		PlayerData[userid][pJetpack] = 1;

		SetPlayerSpecialAction(userid, SPECIAL_ACTION_USEJETPACK);
		SendServerMessage(playerid, "You have spawned a jetpack for %s.", ReturnName(userid, 0));
	}
	return 1;
}

CMD:settime(playerid, params[])
{
	new time;

	if (sscanf(params, "d", time))
	    return SendUsageMessage(playerid, "/settime [time]");

	SetPlayerTime(playerid, time, 0);
	SendServerMessage(playerid, "You have changed the time to %d.", time);
	return 1;
}

CMD:setworldtime(playerid, params[])
{
	new time;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", time))
	    return SendUsageMessage(playerid, "/setworldtime [time]");

	SetWorldTime(time);
	WorldTime = time;
	foreach(new ii : Player)
	{
		SetPlayerTime(ii, time, 0);
	}
	SendServerMessage(playerid, "You have changed the time to %d.", time);
	return 1;
}

CMD:setweather(playerid, params[])
{
	new weatherid;

	if (sscanf(params, "d", weatherid))
	    return SendUsageMessage(playerid, "/setweather [weather ID]");

	SetPlayerWeather(playerid, weatherid);
	SendServerMessage(playerid, "You have changed the weather to ID: %d.", weatherid);
	return 1;
}

CMD:setworldweather(playerid, params[])
{
	new weatherid;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", weatherid))
	    return SendUsageMessage(playerid, "/setworldweather [weather ID]");

	SetWeather(weatherid);
	WorldWeather = weatherid;
	foreach(new ii : Player)
	{
		SetPlayerWeather(ii, weatherid);
	}
	SendServerMessage(playerid, "You have changed the weather to ID: %d.", weatherid);
	return 1;
}

CMD:setfuel(playerid, params[])
{
	static
	    id = 0,
		amount;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "dd", id, amount))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);
			new vehid = Car_GetID(id);

		    if (sscanf(params, "d", amount))
		        return SendUsageMessage(playerid, "/setfuel [amount]");

			if (amount < 0)
			    return SendErrorMessage(playerid, "The amount can't be below 0.");
			
			if (vehid != -1) 
			{
				CarData[vehid][carFuel] = amount;
			}
			SendServerMessage(playerid, "You have set the fuel of vehicle ID: %d to %d percent.", id, amount);
			return 1;
		}
		else return SendUsageMessage(playerid, "/setfuel [vehicle id] [amount]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	new vehid = Car_GetID(id);

	if (amount < 0)
 		return SendErrorMessage(playerid, "The amount can't be below 0.");

	if (vehid != -1) 
	{
		CarData[vehid][carFuel] = amount;
	}
	SendServerMessage(playerid, "You have set the fuel of vehicle ID: %d to %d percent.", id, amount);
	return 1;
}

CMD:setcarhp(playerid, params[])
{
	static
	    id = 0,
		Float:amount;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "df", id, amount))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		{
		    id = GetPlayerVehicleID(playerid);

		    if (sscanf(params, "f", amount))
		        return SendUsageMessage(playerid, "/setcarhp [amount]");

			if (amount < 0.0)
			    return SendErrorMessage(playerid, "The amount can't be below 0.");

			SetVehicleHealth(id, amount);
			SendServerMessage(playerid, "You have set the health of vehicle ID: %d to %.1f.", id, amount);
			return 1;
		}
		else return SendUsageMessage(playerid, "/setcarhp [vehicle id] [amount]");
	}
	if (!IsValidVehicle(id))
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	if (amount < 0.0)
	    return SendErrorMessage(playerid, "The amount can't be below 0.");

	SetVehicleHealth(id, amount);
	SendServerMessage(playerid, "You have set the health of vehicle ID: %d to %.1f.", id, amount);
	return 1;
}

CMD:creategarbage(playerid, params[])
{
	static
	    id = -1,
		type;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", type))
	{
	    SendUsageMessage(playerid, "/creategarbage [type]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Dumpster | 2: Trash Can");
		return 1;
	}
	if (type < 1 || type > 2)
	    return SendErrorMessage(playerid, "The specified type can't be below 1 or above 2.");

	id = Garbage_Create(playerid, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for garbage bins.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created garbage ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroygarbage(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroygarbage [garbage id]");

	if ((id < 0 || id >= MAX_GARBAGE_BINS) || !GarbageData[id][garbageExists])
	    return SendErrorMessage(playerid, "You have specified an invalid garbage ID.");

	Garbage_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed garbage ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:takebag(playerid, params[])
{
	new
		id = Garbage_Nearest(playerid),
		string[64];

	if (PlayerData[playerid][pJob] != JOB_GARBAGE)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (id == -1)
	    return SendErrorMessage(playerid, "You are not in range of any garbage bin.");

	if (GarbageData[id][garbageCapacity] < 1)
	    return SendErrorMessage(playerid, "This garbage bin is empty.");

	if (PlayerData[playerid][pCarryTrash])
	    return SendErrorMessage(playerid, "You are already carrying a garbage bag.");

    GarbageData[id][garbageCapacity]--;
   	Garbage_Save(id);

	PlayerData[playerid][pCarryTrash] = 1;
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a trash bag from the garbage bin.", ReturnName(playerid, 0), string);

	format(string, sizeof(string), "[GARBAGE]\n{FFFFFF}Trash Capacity: "YELLOW_E"%d/20", GarbageData[id][garbageCapacity]);
  	UpdateDynamic3DTextLabelText(GarbageData[id][garbageText3D], COLOR_DARKBLUE, string);

  	SetPlayerAttachedObject(playerid, 4, 1264, 6, 0.000000, 0.000000, 0.000000, 0.000000, 270.000000, 90.000000, 0.500000, 0.500000, 0.500000);
	SendInfoMessage(playerid, "Press "YELLOW_E"ALT"WHITE_E" to load the garbage bag.");

	return 1;
}

CMD:dumpgarbage(playerid, params[])
{
	new
		vehicleid = GetPlayerVehicleID(playerid),
		id = Job_NearestPoint(playerid, 5.0);

	if (PlayerData[playerid][pJob] != JOB_GARBAGE)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (GetVehicleModel(vehicleid) != 408)
	    return SendErrorMessage(playerid, "You must be driving a garbage truck.");

	if (id == -1 || JobData[id][jobType] != JOB_GARBAGE)
	    return SendErrorMessage(playerid, "You are not in range of any trash dump.");

	if (CoreVehicles[vehicleid][vehTrash] < 1)
	    return SendErrorMessage(playerid, "There is no trash loaded in this vehicle.");

	GiveMoney(playerid, (CoreVehicles[vehicleid][vehTrash] * 25));

	SendServerMessage(playerid, "You have earned %s for dumping %d bags of trash.", FormatNumber((CoreVehicles[vehicleid][vehTrash] * 15)), CoreVehicles[vehicleid][vehTrash]);
	CoreVehicles[vehicleid][vehTrash] = 0;

	return 1;
}

CMD:createvendor(playerid, params[])
{
	static
	    id = -1,
		type;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", type))
	{
	    SendUsageMessage(playerid, "/createvendor [type]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]:{FFFFFF} 1: Food | 2: Soda");
		return 1;
	}
	if (type < 1 || type > 2)
	    return SendErrorMessage(playerid, "The specified type can't be below 1 or above 2.");

	id = Vendor_Create(playerid, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for vendors.");

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has created vendor ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:destroyvendor(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyvendor [vendor id]");

	if ((id < 0 || id >= MAX_VENDORS) || !VendorData[id][vendorExists])
	    return SendErrorMessage(playerid, "You have specified an invalid vendor ID.");

	Vendor_Delete(id);
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has destroyed vendor ID %d.", ReturnName(playerid, 0), id);
	return 1;
}

CMD:dance(playerid, params[])
{
	new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/dance [1-4]");

	if (type < 1 || type > 4)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
	    case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
	    case 3: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
	    case 4: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
	}
	return 1;
}

CMD:handsup(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
	return 1;
}

CMD:piss(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	SetPlayerSpecialAction(playerid, 68);
	return 1;
}

CMD:animcmds(playerid, params[])
{
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /dance, /handsup, /bat, /slap, /bar, /wash, /lay, /workout, /bomb.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /carry, /crack, /sleep, /jump, /deal, /dancing, /eating, /puke, /gsign, /chat.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /goggles, /spray, /throw, /swipe, /office, /kiss, /knife, /cpr, /scratch, /point.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /cheer, /wave, /strip, /smoke, /reload, /taichi, /hide, /skates, /drunk.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /cry, /tired, /sit, /crossarms, /fucku, /walk, /piss, /salute, /angkat, /stopanim.");
	return 1;
}

CMD:angkat(playerid, params[])
{
	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid,"CARRY", "crry_prtial", 4.1, 1,1, 1,1 , 1, 1);
	return 1;
}

CMD:bat(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/bat [1-5]");

	if (type < 1 || type > 5)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "BASEBALL", "Bat_1", 4.1, 0, 1, 1, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "BASEBALL", "Bat_2", 4.1, 0, 1, 1, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "BASEBALL", "Bat_3", 4.1, 0, 1, 1, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "BASEBALL", "Bat_IDLE", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:cower(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimationEx(playerid, "PED", "cower", 4.1, 0, 0, 0, 1, 0, 1);
	return 1;
}

CMD:blowjob(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/blowjob [1-4]");

	if (type < 1 || type > 4)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:wank(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/wank [1-3]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "PAULNMAC", "wank_loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "PAULNMAC", "wank_in", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "PAULNMAC", "wank_out", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:slap(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "BASEBALL", "Bat_M", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:bar(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/bar [1-8]");

	if (type < 1 || type > 8)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "BAR", "Barserve_bottle", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "BAR", "Barserve_glass", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "BAR", "Barserve_in", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimation(playerid, "BAR", "Barserve_order", 4.1, 0, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "BAR", "BARman_idle", 4.1, 1, 0, 0, 0, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "BAR", "dnk_stndM_loop", 4.1, 0, 0, 0, 0, 0, 1);
	    case 8: ApplyAnimationEx(playerid, "BAR", "dnk_stndF_loop", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:wash(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:lay(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/lay [1-5]");

	if (type < 1 || type > 5)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "BEACH", "bather", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "BEACH", "Lay_Bac_Loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "BEACH", "ParkSit_M_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "BEACH", "ParkSit_W_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "BEACH", "SitnWait_loop_W", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:workout(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/workout [1-7]");

	if (type < 1 || type > 7)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "benchpress", "gym_bp_celebrate", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "benchpress", "gym_bp_down", 4.1, 0, 0, 0, 1, 0, 1);
	    case 3: ApplyAnimation(playerid, "benchpress", "gym_bp_getoff", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "benchpress", "gym_bp_geton", 4.1, 0, 0, 0, 1, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_A", 4.1, 0, 0, 0, 1, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_B", 4.1, 0, 0, 0, 1, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_smooth", 4.1, 0, 0, 0, 1, 0, 1);
	}
	return 1;
}


CMD:bomb(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:carry(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/carry [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "CARRY", "liftup05", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimation(playerid, "CARRY", "putdwn05", 4.1, 0, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimation(playerid, "CARRY", "putdwn105", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:crack(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/crack [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "CRACK", "crckdeth3", 4.1, 0, 0, 0, 1, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "CRACK", "crckidle1", 4.1, 0, 0, 0, 1, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "CRACK", "crckidle2", 4.1, 0, 0, 0, 1, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "CRACK", "crckidle3", 4.1, 0, 0, 0, 1, 0, 1);
	}
	return 1;
}

CMD:sleep(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/sleep [1-2]");

	if (type < 1 || type > 2)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "CRACK", "crckidle4", 4.1, 0, 0, 0, 1, 0, 1);
	}
	return 1;
}

CMD:jump(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "DODGE", "Crush_Jump", 4.1, 0, 1, 1, 0, 0, 1);
	return 1;
}

CMD:deal(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/deal [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "DEALER", "DRUGS_BUY", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_01", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_02", 4.1, 1, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_03", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:dancing(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/dancing [1-10]");

	if (type < 1 || type > 10)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "DANCING", "dance_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "DANCING", "DAN_Left_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "DANCING", "DAN_Right_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DANCING", "DAN_Loop_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "DANCING", "DAN_Up_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "DANCING", "DAN_Down_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "DANCING", "dnce_M_a", 4.1, 1, 0, 0, 0, 0, 1);
	    case 8: ApplyAnimationEx(playerid, "DANCING", "dnce_M_e", 4.1, 1, 0, 0, 0, 0, 1);
	    case 9: ApplyAnimationEx(playerid, "DANCING", "dnce_M_b", 4.1, 1, 0, 0, 0, 0, 1);
	    case 10: ApplyAnimationEx(playerid, "DANCING", "dnce_M_c", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:eating(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/eating [1-3]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "FOOD", "EAT_Chicken", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "FOOD", "EAT_Pizza", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:puke(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:gsign(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/gsign [1-15]");

	if (type < 1 || type > 15)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "GHANDS", "gsign1", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "GHANDS", "gsign1LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "GHANDS", "gsign2", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "GHANDS", "gsign3", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "GHANDS", "gsign3LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "GHANDS", "gsign4", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "GHANDS", "gsign4LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 9: ApplyAnimation(playerid, "GHANDS", "gsign5", 4.1, 0, 0, 0, 0, 0, 1);
		case 10: ApplyAnimation(playerid, "GHANDS", "gsign5", 4.1, 0, 0, 0, 0, 0, 1);
		case 11: ApplyAnimation(playerid, "GHANDS", "gsign5LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 12: ApplyAnimation(playerid, "GANGS", "Invite_No", 4.1, 0, 0, 0, 0, 0, 1);
		case 13: ApplyAnimation(playerid, "GANGS", "Invite_Yes", 4.1, 0, 0, 0, 0, 0, 1);
		case 14: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkD", 4.1, 0, 0, 0, 0, 0, 1);
		case 15: ApplyAnimation(playerid, "GANGS", "smkcig_prtl", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:chat(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/chat [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkB", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkE", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkF", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkG", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkH", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:goggles(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:spray(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

 	ApplyAnimationEx(playerid, "GRAFFITI", "spraycan_fire", 4.1, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:throw(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throw", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:swipe(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:office(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/office [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Bored_Loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Crash", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Drink", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Read", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Watch", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:kiss(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/kiss [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:knife(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/knife [1-8]");

	if (type < 1 || type > 8)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "KNIFE", "knife_1", 4.1, 0, 1, 1, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "KNIFE", "knife_2", 4.1, 0, 1, 1, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "KNIFE", "knife_3", 4.1, 0, 1, 1, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "KNIFE", "knife_4", 4.1, 0, 1, 1, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "KNIFE", "WEAPON_knifeidle", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Player", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Damage", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:cpr(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
	return 1;
}

CMD:scratch(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/scratch [1-4]");

	if (type < 1 || type > 4)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
    	case 1: ApplyAnimationEx(playerid, "SCRATCHING", "scdldlp", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "SCRATCHING", "scdlulp", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "SCRATCHING", "scdrdlp", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "SCRATCHING", "scdrulp", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:point(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/point [1-3]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "PED", "ARRESTgun", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 1, 0, 0, 0, 0, 1);
    	case 3: ApplyAnimationEx(playerid, "ON_LOOKERS", "point_loop", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:salute(playerid, params[])
{
	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");
		
	ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.0, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:cheer(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/cheer [1-8]");

	if (type < 1 || type > 8)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "ON_LOOKERS", "shout_02", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "ON_LOOKERS", "shout_in", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "RIOT", "RIOT_CHANT", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "RIOT", "RIOT_shout", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "STRIP", "PUN_HOLLER", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "OTB", "wtchrace_win", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:strip(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/strip [1-7]");

	if (type < 1 || type > 7)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "STRIP", "strip_A", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "STRIP", "strip_B", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "STRIP", "strip_C", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "STRIP", "strip_D", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "STRIP", "strip_E", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimationEx(playerid, "STRIP", "strip_F", 4.1, 1, 0, 0, 0, 0, 1);
		case 7: ApplyAnimationEx(playerid, "STRIP", "strip_G", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:wave(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/wave [1-3]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "PED", "endchat_03", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_loop", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:smoke(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/smoke [1-3]");

	if (type < 1 || type > 3)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "SMOKING", "M_smklean_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "SMOKING", "M_smkstnd_loop", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:reload(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/reload [1-4]");

	if (type < 1 || type > 4)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimation(playerid, "BUDDY", "buddy_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "UZI", "UZI_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:taichi(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimationEx(playerid, "PARK", "Tai_Chi_Loop", 4.1, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:hide(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimationEx(playerid, "PED", "cower", 4.1, 0, 0, 0, 1, 0, 1);
	return 1;
}

CMD:skates(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/skates [1-2]");

	if (type < 1 || type > 2)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "SKATE", "skate_idle", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "SKATE", "skate_run", 4.1, 1, 1, 1, 1, 1, 1);
	}
	return 1;
}

CMD:drunk(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimationEx(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1, 1);
	return 1;
}

CMD:cry(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimationEx(playerid, "GRAVEYARD", "mrnF_loop", 4.1, 1, 0, 0, 0, 0, 1);
    return 1;
}

CMD:tired(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/tired [1-2]");

	if (type < 1 || type > 2)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "FAT", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
	}
	return 1;
}

CMD:sit(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/sit [1-6]");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
		case 2: ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_In", 4.1, 0, 0, 0, 1, 0);
		case 3: ApplyAnimationEx(playerid, "MISC", "SEAT_LR", 4.1, 1, 0, 0, 0, 0);
		case 4: ApplyAnimationEx(playerid, "MISC", "Seat_talk_01", 4.1, 1, 0, 0, 0, 0);
		case 5: ApplyAnimationEx(playerid, "MISC", "Seat_talk_02", 4.1, 1, 0, 0, 0, 0);
		case 6: ApplyAnimationEx(playerid, "ped", "SEAT_down", 4.1, 0, 0, 0, 1, 0);
	}
	return 1;
}

CMD:crossarms(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/crossarms [1-4]");

	if (type < 1 || type > 4)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "GRAVEYARD", "prst_loopa", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "GRAVEYARD", "mrnM_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE", 4.1, 0, 1, 1, 1, 0, 1);
	}
	return 1;
}

CMD:fucku(playerid, params[])
{
    if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	ApplyAnimation(playerid, "PED", "fucku", 4.1, 0, 0, 0, 0, 0);
	return 1;
}

CMD:walk(playerid, params[])
{
    new type;

	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You can't perform animations at the moment.");

	if (sscanf(params, "d", type))
	    return SendUsageMessage(playerid, "/walk [1-16]");

	if (type < 1 || type > 17)
	    return SendErrorMessage(playerid, "Invalid type specified.");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "FAT", "FatWalk", 4.1, 1, 1, 1, 1, 1, 1);
	    case 2: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleWalk", 4.1, 1, 1, 1, 1, 1, 1);
	    case 3: ApplyAnimationEx(playerid, "PED", "WALK_armed", 4.1, 1, 1, 1, 1, 1, 1);
	    case 4: ApplyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
	    case 5: ApplyAnimationEx(playerid, "PED", "WALK_fat", 4.1, 1, 1, 1, 1, 1, 1);
	    case 6: ApplyAnimationEx(playerid, "PED", "WALK_fatold", 4.1, 1, 1, 1, 1, 1, 1);
	    case 7: ApplyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
	    case 8: ApplyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
	    case 9: ApplyAnimationEx(playerid, "PED", "WALK_player", 4.1, 1, 1, 1, 1, 1, 1);
	    case 10: ApplyAnimationEx(playerid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 1, 1);
	    case 11: ApplyAnimationEx(playerid, "PED", "WALK_wuzi", 4.1, 1, 1, 1, 1, 1, 1);
	    case 12: ApplyAnimationEx(playerid, "PED", "WOMAN_walkbusy", 4.1, 1, 1, 1, 1, 1, 1);
	    case 13: ApplyAnimationEx(playerid, "PED", "WOMAN_walkfatold", 4.1, 1, 1, 1, 1, 1, 1);
	    case 14: ApplyAnimationEx(playerid, "PED", "WOMAN_walknorm", 4.1, 1, 1, 1, 1, 1, 1);
	    case 15: ApplyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
	    case 16: ApplyAnimationEx(playerid, "PED", "WOMAN_walkshop", 4.1, 1, 1, 1, 1, 1, 1);
	}
	return 1;
}

CMD:panel(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 3 )
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (g_ServerLocked)
		Dialog_Show(playerid, ServerPanel, DIALOG_STYLE_LIST, "Server Panel", "Unlock Server\nSet Hostname\nExecute Query", "Select", "Cancel");

	else Dialog_Show(playerid, ServerPanel, DIALOG_STYLE_LIST, "Server Panel", "Lock Server\nSet Hostname\nExecute Query", "Select", "Cancel");
	return 1;
}

CMD:spawnitem(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (isnull(params))
	    return SendUsageMessage(playerid, "/spawnitem [item name] (/itemlist for a list)");

	static
		Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);

    for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], params, true))
	{
	    new id = DropItem(g_aInventoryItems[i][e_InventoryItem], "Admin", g_aInventoryItems[i][e_InventoryModel], 1, x, y, z - 0.9, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

	    if (id == -1)
	        return SendErrorMessage(playerid, "The server has reached a limit for spawned items.");
        Log_Write("logs/spawnitem.txt", "[%s] %s has spawned %s", ReturnDate(), ReturnName(playerid, 0), g_aInventoryItems[i][e_InventoryItem]);
		SendServerMessage(playerid, "You have spawned a \"%s\" (type /setquantity to set the quantity).", g_aInventoryItems[i][e_InventoryItem]);
		return 1;
	}
    SendErrorMessage(playerid, "Invalid item name (use /itemlist for a list).");
	return 1;
}

CMD:setquantity(playerid, params[])
{
	static
	    id = -1,
		amount;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if ((id = Item_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "You are not in range of any spawned items.");

	if (sscanf(params, "d", amount))
	    return SendUsageMessage(playerid, "/setquantity [amount]");

	if (amount < 1)
	    return SendErrorMessage(playerid, "The specified amount can't be below 1.");

    Item_SetQuantity(id, amount);
    Log_Write("logs/spawnitem.txt", "[%s] %s has set the quantity of %s to %d.", ReturnDate(), ReturnName(playerid, 0), DroppedItems[id][droppedItem], amount);
    SendServerMessage(playerid, "You have set the quantity of \"%s\" to %d.", DroppedItems[id][droppedItem], amount);
    return 1;
}

CMD:destroyitem(playerid, params[])
{
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if ((id = Item_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "You are not in range of any spawned items.");

    SendServerMessage(playerid, "You have deleted a \"%s\".", DroppedItems[id][droppedItem]);
    Item_Delete(id);
    return 1;
}

CMD:boombox(playerid, params[])
{
	static
	    type[24],
	    string[128];

	if (!Inventory_HasItem(playerid, "Boombox"))
	    return SendErrorMessage(playerid, "You don't have a boombox on you.");

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendUsageMessage(playerid, "/boombox [name]");
	    SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} place, pickup, url");
	    return 1;
	}
	if (!strcmp(type, "place", true))
	{
	    if (BoomboxData[playerid][boomboxPlaced])
	        return SendErrorMessage(playerid, "You have placed a boombox already.");

		if (Boombox_Nearest(playerid) != INVALID_PLAYER_ID)
		    return SendErrorMessage(playerid, "You are in range of another boombox already.");

		if (IsPlayerInAnyVehicle(playerid))
		    return SendErrorMessage(playerid, "You must exit the vehicle first.");

		Boombox_Place(playerid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a boombox and sets it down.", ReturnName(playerid, 0));
		SendServerMessage(playerid, "You have placed your boombox (use \"/boombox\" for options).");
	}
	else if (!strcmp(type, "pickup", true))
	{
	    if (!BoomboxData[playerid][boomboxPlaced])
	        return SendErrorMessage(playerid, "You don't have a boombox deployed.");

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]))
		    return SendErrorMessage(playerid, "You are not in range of your boombox.");

		Boombox_Destroy(playerid);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up their boombox.", ReturnName(playerid, 0));
	}
	else if (!strcmp(type, "url", true))
	{
	    if (sscanf(string, "s[128]", string))
	        return SendUsageMessage(playerid, "/boombox [url] [song url]");

        if (!BoomboxData[playerid][boomboxPlaced])
	        return SendErrorMessage(playerid, "You don't have a boombox deployed.");

		if (!IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[playerid][boomboxPos][0], BoomboxData[playerid][boomboxPos][1], BoomboxData[playerid][boomboxPos][2]))
		    return SendErrorMessage(playerid, "You are not in range of your boombox.");

		Boombox_SetURL(playerid, string);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s turns the dial of the boombox to another station.", ReturnName(playerid, 0));
	}
	return 1;
}

CMD:adestroybox(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	foreach (new i : Player) if (BoomboxData[i][boomboxPlaced] && IsPlayerInRangeOfPoint(playerid, 3.0, BoomboxData[i][boomboxPos][0], BoomboxData[i][boomboxPos][1], BoomboxData[i][boomboxPos][2])) {
		Boombox_Destroy(i);

		SendServerMessage(playerid, "You have destroyed %s's boombox.", ReturnName(i, 0));
		return SendServerMessage(i, "%s has destroyed your boombox.", ReturnName(playerid, 0));
	}
	SendErrorMessage(playerid, "You are not in range of any boombox.");
	return 1;
}

CMD:findgarbage(playerid, params[])
{
	if (PlayerData[playerid][pJob] != JOB_GARBAGE)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	new id = GetClosestGarbage(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "There are no garbage bins available.");

	PlayerData[playerid][pCP] = 1;

	SetPlayerCheckpoint(playerid, GarbageData[id][garbagePos][0], GarbageData[id][garbagePos][1], GarbageData[id][garbagePos][2], 2.5);
	SendServerMessage(playerid, "Marker set to the closest garbage bin.");
	return 1;
}

CMD:search(playerid, params[])
{
	new userid;

	if (sscanf(params, "u", userid))
	{
		SendUsageMessage(playerid, "/search [playerid/name]");
		SendClientMessage(playerid, COLOR_YELLOW, "[HINT]:{FFFFFF} Use /searchbp to search a player's backpack.");
		return 1;
	}
	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (Inventory_HasItem(userid, "Marijuana Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Marijuana Seeds (%d)", Inventory_Count(userid, "Marijuana Seeds"));

    if (Inventory_HasItem(userid, "Cocaine Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Cocaine Seeds (%d)", Inventory_Count(userid, "Cocaine Seeds"));

    if (Inventory_HasItem(userid, "Heroin Opium Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Heroin Opium Seeds (%d)", Inventory_Count(userid, "Heroin Opium Seeds"));

	if (Inventory_HasItem(userid, "Steroids"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Steroids (%d)", Inventory_Count(userid, "Steroids"));

    if (Inventory_HasItem(userid, "Marijuana"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Marijuana (%d)", Inventory_Count(userid, "Marijuana"));

    if (Inventory_HasItem(userid, "Cocaine"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Cocaine (%d)", Inventory_Count(userid, "Cocaine"));

    if (Inventory_HasItem(userid, "Heroin"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Heroin (%d)", Inventory_Count(userid, "Heroin"));

	for (new i = 0; i < 12; i ++) if (PlayerData[userid][pGuns][i] && PlayerData[userid][pAmmo][i] > 0) {
	    SendClientMessageEx(playerid, COLOR_LIGHTRED, "** %s", ReturnWeaponName(PlayerData[userid][pGuns][i]));
	}
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s starts to search %s for illegal items.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:searchbp(playerid, params[])
{
    new userid, backpack;

	if (sscanf(params, "u", userid))
		return SendUsageMessage(playerid, "/searchbp [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (!Inventory_HasItem(userid, "Backpack") || (backpack = GetPlayerBackpack(userid)) == -1)
	    return SendErrorMessage(playerid, "That player doesn't have a backpack.");

    if (Backpack_HasItem(backpack, "Marijuana Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Marijuana Seeds (%d)", Backpack_Count(backpack, "Marijuana Seeds"));

    if (Backpack_HasItem(backpack, "Cocaine Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Cocaine Seeds (%d)", Backpack_Count(backpack, "Cocaine Seeds"));

    if (Backpack_HasItem(backpack, "Heroin Opium Seeds"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Heroin Opium Seeds (%d)", Backpack_Count(backpack, "Heroin Opium Seeds"));

	if (Backpack_HasItem(backpack, "Steroids"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Steroids (%d)", Backpack_Count(backpack, "Steroids"));

    if (Backpack_HasItem(backpack, "Marijuana"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Marijuana (%d)", Backpack_Count(backpack, "Marijuana"));

    if (Backpack_HasItem(backpack, "Cocaine"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Cocaine (%d)", Backpack_Count(backpack, "Cocaine"));

    if (Backpack_HasItem(backpack, "Heroin"))
		SendClientMessageEx(playerid, COLOR_LIGHTRED, "** Heroin (%d)", Backpack_Count(backpack, "Heroin"));

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has searched %s's backpack for illegal items.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:cekbadan(playerid, params[])
{
	new
	    targetid;

    if (GetFactionType(playerid) != FACTION_POLICE)
		return SendErrorMessage(playerid, "You must be a police officer.");

	if (sscanf(params, "u", targetid))
	    return SendUsageMessage(playerid, "/check [playerid/name]");

	if (!IsPlayerNearPlayer(playerid, targetid, 6.0))
		return SendErrorMessage(playerid, "You are not near that player.");

	new
		models[MAX_INVENTORY],
		amount[MAX_INVENTORY];

	for (new i = 0; i < PlayerData[targetid][pCapacity]; i ++)
	{
		if (InventoryData[targetid][i][invExists]) {
			models[i] = InventoryData[targetid][i][invModel];
			amount[i] = InventoryData[targetid][i][invQuantity];
		}
		else {
			models[i] = -1;
			amount[i] = -1;
		}
	}
	ShowModelSelectionMenu(playerid, ReturnName(targetid), MODEL_SELECTION_FRISK, models, sizeof(models), 0.0, 0.0, 0.0, 1.0, -1, true, amount);
	PlayerData[playerid][pGiveItem] = targetid;
	SendInfoMessage(targetid, "You are being checked by the police officer.");
	return 1;
}

CMD:kickdoor(playerid, params[])
{
	static
	    id = -1;

	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You must be a police officer.");

	if ((id = House_Nearest(playerid)) != -1)
	{
	    if (!HouseData[id][houseLocked])
	        return SendErrorMessage(playerid, "This house is already unlocked.");

	    SendServerMessage(playerid, "Attempting to break door...");
	    ApplyAnimation(playerid, "POLICE", "Door_Kick", 4.0, 0, 0, 0, 0, 0);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s attempts to kick the house's door down.", ReturnName(playerid, 0));
	    SetTimerEx("KickHouse", 1500, false, "dd", playerid, id);
	}
	else if ((id = Business_Nearest(playerid)) != -1)
	{
		if (!BusinessData[id][bizLocked])
		    return SendErrorMessage(playerid, "This business is already unlocked.");

		SendServerMessage(playerid, "Attempting to break door...");
        ApplyAnimation(playerid, "POLICE", "Door_Kick", 4.0, 0, 0, 0, 0, 0);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s attempts to kick the business door down.", ReturnName(playerid, 0));
	    SetTimerEx("KickBusiness", 1500, false, "dd", playerid, id);
	}
	else {
		SendErrorMessage(playerid, "You must be in range of a house or business.");
	}
	return 1;
}

CMD:buyrack(playerid, params[])
{
	new houseid = House_Inside(playerid);

	if (houseid == -1 || !House_IsOwner(playerid, houseid))
	    return SendErrorMessage(playerid, "You are not in range of your house interior.");

	if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
		return SendUsageMessage(playerid, "/buyrack [confirm] (RM1,000 fee)");

	if (Rack_Count(playerid) >= 4)
	    return SendErrorMessage(playerid, "Your house can only have up to 4 weapon racks.");

	if (Rack_Nearest(playerid) != -1)
	    return SendErrorMessage(playerid, "You can't use this command near another rack.");

	if (GetMoney(playerid) < 1000)
	    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

	new id = Rack_Create(playerid, houseid);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for weapon racks.");

    ResetEditing(playerid);

	PlayerData[playerid][pEditRack] = id;
	EditDynamicObject(playerid, RackData[id][rackObjects][4]);

    GiveMoney(playerid, -1000);
	SendServerMessage(playerid, "You have purchased a weapon rack for RM1,000.");
	return 1;
}

CMD:gunrack(playerid, params[])
{
	new id = Rack_Nearest(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "You are not in range of any weapon rack.");

	Rack_ShowGuns(playerid, id);
	return 1;
}

CMD:deleterack(playerid, params[])
{
	new
		id = -1,
		houseid = House_Inside(playerid);

	if (houseid == -1 || !House_IsOwner(playerid, houseid))
	    return SendErrorMessage(playerid, "You are not in range of your house interior.");

	if ((id = Rack_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "You are not in range of any weapon rack.");

	Rack_Delete(id);
	SendServerMessage(playerid, "You have deleted the weapon rack from your house.");
	return 1;
}

CMD:createrack(playerid, params[])
{
	static
	    id = -1;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	id = Rack_Create(playerid, -1);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for weapon racks.");

    ResetEditing(playerid);
    PlayerData[playerid][pEditRack] = id;

	EditDynamicObject(playerid, RackData[id][rackObjects][4]);
	SendServerMessage(playerid, "You have successfully created rack ID: %d.", id);
	return 1;
}

CMD:editrack(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/editrack [rack id]");

	if ((id < 0 || id >= MAX_WEAPON_RACKS) || !RackData[id][rackExists])
	    return SendErrorMessage(playerid, "You have specified an invalid rack ID.");

	ResetEditing(playerid);
	PlayerData[playerid][pEditRack] = id;

	EditDynamicObject(playerid, RackData[id][rackObjects][4]);
	SendServerMessage(playerid, "You are now editing weapon rack ID: %d.", id);
	return 1;
}

CMD:destroyrack(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))	
	    return SendUsageMessage(playerid, "/destroyrack [rack id]");

	if ((id < 0 || id >= MAX_WEAPON_RACKS) || !RackData[id][rackExists])
	    return SendErrorMessage(playerid, "You have specified an invalid rack ID.");

	Rack_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed weapon rack ID: %d.", id);
	return 1;
}

CMD:tracenumber(playerid, params[])
{
	new number;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", number))
	    return SendUsageMessage(playerid, "/tracenumber [phone number]");

	if (number == 0)
	    return SendErrorMessage(playerid, "You have specified an invalid number.");

	if (GetNumberOwner(number) != INVALID_PLAYER_ID)
	    return SendServerMessage(playerid, "The phone number %d is owned by %s.", number, ReturnName(GetNumberOwner(number), 0));

	SendErrorMessage(playerid, "There is no player online with that phone number.");
	return 1;
}

CMD:flipcar(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (vehicleid > 0 && isnull(params))
	{
		FlipVehicle(vehicleid);
		SendServerMessage(playerid, "You have flipped your current vehicle.");
	}
	else
	{
		if (sscanf(params, "d", vehicleid))
	    	return SendUsageMessage(playerid, "/flipcar [vehicle ID]");

		else if (!IsValidVehicle(vehicleid))
	    	return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

		FlipVehicle(vehicleid);
		SendServerMessage(playerid, "You have flipped vehicle ID: %d.", vehicleid);
	}
	return 1;
}

CMD:createspeed(playerid, params[])
{
	static
	    Float:limit,
	    Float:range;

	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ff", limit, range))
		return SendUsageMessage(playerid, "/createspeed [speed limit] [range] (default range: 30)");

	if (limit < 5.0 || limit > 150.0)
	    return SendErrorMessage(playerid, "The speed limit can't be below 5 or above 150.");

	if (range < 5.0 || range > 50.0)
	    return SendErrorMessage(playerid, "The range can't be below 5 or above 50.");

	if (Speed_Nearest(playerid) != -1)
	    return SendErrorMessage(playerid, "You can't do this in range another speed camera.");

	new id = Speed_Create(playerid, limit, range);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for speed cameras.");

	SendServerMessage(playerid, "You have created speed camera ID: %d.", id);
	return 1;
}

CMD:destroyspeed(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyspeed [speed id]");

	if ((id < 0 || id >= MAX_SPEED_CAMERAS) || !SpeedData[id][speedExists])
	    return SendErrorMessage(playerid, "You have specified an invalid speed camera ID.");

	Speed_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed speed camera ID: %d.", id);
	return 1;
}

CMD:admins(playerid, params[])
{
	new count = 0;

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

    foreach (new i : Player) if (PlayerData[i][pAdmin] > 0 && PlayerData[i][pAdminHide] < 1)
	{
		if (PlayerData[i][pAdminDuty])
			SendClientMessageEx(playerid, COLOR_WHITE, "{FFFFFF}* %s ({0045ff}Level: %d{FFFFFF}) {FFFFFF}Status: {FFFFFF}({00ff18}Onduty{FFFFFF})", PlayerData[i][pUsername], PlayerData[i][pAdmin]);

		else
		    SendClientMessageEx(playerid, COLOR_WHITE, "{FFFFFF}* %s ({0045ff}Level: %d{FFFFFF}) {FFFFFF}Status: {FFFFFF}({ff0000}Offduty{FFFFFF})", PlayerData[i][pUsername], PlayerData[i][pAdmin]);

        count++;
	}
	if (!count) {
	    SendClientMessage(playerid, COLOR_WHITE, "* No administrator online.");
	}
	SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
	return 1;
}

CMD:showlicense(playerid, params[])
{
	static
	    userid;

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/showlicense [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
		return SendErrorMessage(playerid, "You can't show your licenses to yourself.");

	SendClientMessage(userid, COLOR_GREY, "-----------------------------------------------------------");

	if (Inventory_HasItem(playerid, "Driving License")) SendClientMessageEx(userid, COLOR_WHITE, "* Driving License {33CC33}(Passed)");
 	else SendClientMessageEx(userid, COLOR_WHITE, "* Driving License {AA3333}(Not Passed)");

	if (Inventory_HasItem(playerid, "Weapon License")) SendClientMessageEx(userid, COLOR_WHITE, "* Weapon License {33CC33}(Passed)");
	else SendClientMessageEx(userid, COLOR_WHITE, "* Weapon License {AA3333}(Not Passed)");

	SendClientMessage(userid, COLOR_GREY, "-----------------------------------------------------------");
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their licenses and shows them to %s.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:stoploading(playerid, params[])
{
	if (PlayerData[playerid][pJob] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (!PlayerData[playerid][pLoading] && !PlayerData[playerid][pLoadType])
	    return SendErrorMessage(playerid, "You are not loading any crates right now.");

	PlayerData[playerid][pLoading] = 0;
	PlayerData[playerid][pLoadType] = 0;
    PlayerData[playerid][pLoadCrate] = 0;

	RemovePlayerAttachedObject(playerid, 4);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	DisablePlayerCheckpoint(playerid);
	SendServerMessage(playerid, "You are no longer loading crates.");

	return 1;
}

CMD:startdelivery(playerid, params[])
{
 	new id = Job_NearestPoint(playerid);

	if (PlayerData[playerid][pJob] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (id == -1 || JobData[id][jobType] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You are not in range of any loading point.");

	if (PlayerData[playerid][pLoadType] > 0)
	    return SendErrorMessage(playerid, "You have already started a delivery.");

    if (IsPlayerInAnyVehicle(playerid))
    	return SendErrorMessage(playerid, "You must exit the vehicle first.");

	Dialog_Show(playerid, StartDelivery, DIALOG_STYLE_LIST, "Select Type", "Retail Supplies\nElectronic\nClothing\nFood Supplies\nGasoline\nFurniture", "Select", "Cancel");
	return 1;
}

CMD:bm(playerid, params[])
{
 	new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));

    if (id == -1 || !Business_IsOwner(playerid, id))
        return SendErrorMessage(playerid, "You are not in range of your business.");

	Dialog_Show(playerid, BusinessManage, DIALOG_STYLE_LIST, "Business Menu", "Info Business\nSet Name\nSet Welcome Message\nShipment\nProduct Menu\nVault", "Select", "Cancel");
	return 1;
}
CMD:cancelshipment(playerid, params[])
{
	if (PlayerData[playerid][pJob] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (PlayerData[playerid][pShipment] == -1)
	    return SendErrorMessage(playerid, "You haven't accepted any shipments yet.");

	CancelShipment(playerid);
	SendServerMessage(playerid, "You have cancelled the accepted shipment.");
	return 1;
}

CMD:shipments(playerid, params[])
{
    if (PlayerData[playerid][pJob] != JOB_COURIER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

	if (PlayerData[playerid][pShipment] != -1)
	    return SendErrorMessage(playerid, "You have already accepted a shipment (type /cancelshipment to cancel it).");

	ShowShipments(playerid);
	return 1;
}

CMD:clearinventory(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/clearinventory [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	Inventory_Clear(userid);

	SendInfoMessage(playerid, "You have cleared %s's inventory from all items.", ReturnName(userid, 0));
	SendInfoMessage(userid, "%s has cleared your inventory from all items.", ReturnName(playerid, 0));

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has cleared %s's inventory.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:warnings(playerid, params[])
{
    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
    SendClientMessageEx(playerid, COLOR_LIGHTRED, "Warnings (%d/3)", PlayerData[playerid][pWarnings]);

    if (PlayerData[playerid][pWarnings] >= 1 && strlen(PlayerData[playerid][pWarn1]))
        SendClientMessageEx(playerid, COLOR_WHITE, "* 1st Warning: \"%s\"", PlayerData[playerid][pWarn1]);

    if (PlayerData[playerid][pWarnings] >= 2 && strlen(PlayerData[playerid][pWarn2]))
        SendClientMessageEx(playerid, COLOR_WHITE, "* 2nd Warning: \"%s\"", PlayerData[playerid][pWarn2]);

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
	return 1;
}

CMD:listwarns(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/listwarns [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
    SendClientMessageEx(playerid, COLOR_LIGHTRED, "%s's Warnings (%d/3)", ReturnName(userid, 0), PlayerData[userid][pWarnings]);

    if (PlayerData[userid][pWarnings] >= 1 && strlen(PlayerData[userid][pWarn1]))
        SendClientMessageEx(playerid, COLOR_WHITE, "* 1st Warning: \"%s\"", PlayerData[userid][pWarn1]);

    if (PlayerData[userid][pWarnings] >= 2 && strlen(PlayerData[userid][pWarn2]))
        SendClientMessageEx(playerid, COLOR_WHITE, "* 2nd Warning: \"%s\"", PlayerData[userid][pWarn2]);

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
	return 1;
}

CMD:warn(playerid, params[])
{
	static
	    userid,
		reason[32];

    if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[32]", userid, reason))
	    return SendUsageMessage(playerid, "/warn [playerid/name] [reason]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	if (PlayerData[userid][pAdmin] > PlayerData[playerid][pAdmin])
	    return SendErrorMessage(playerid, "The specified player has higher authority.");

	switch (++ PlayerData[userid][pWarnings])
	{
	    case 1:
	    {
	        format(PlayerData[userid][pWarn1], 32, reason);

	        SendInfoMessage(userid, "%s has warned you for \"%s\" (first warning).", ReturnName(playerid, 0), reason);

			SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has warned %s (first warning)", ReturnName(playerid, 0), ReturnName(userid, 0));
			SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);
		}
		case 2:
	    {
	        format(PlayerData[userid][pWarn2], 32, reason);

	        SendInfoMessage(userid, "%s has warned you for \"%s\" (second warning).", ReturnName(playerid, 0), reason);
	        
			SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has warned %s (second warning)", ReturnName(playerid, 0), ReturnName(userid, 0));
			SendClientMessageToAllEx(COLOR_GREY, "Reason: %s", reason);
		}
		default:
	    {
	        ResetWarnings(userid);

	        SendInfoMessage(userid, "You've been banned for exceeding your warnings (\"%s\").", reason);

			SendClientMessageToAllEx(COLOR_GREY, "AdmCmd: Admin %s has banned %s", ReturnName(playerid, 0), ReturnName(userid, 0));
			SendClientMessageToAllEx(COLOR_GREY, "Reason: Three total warning", reason);

			Blacklist_Add(PlayerData[userid][pIP], PlayerData[userid][pUsername], PlayerData[playerid][pUsername], reason);
			KickEx(userid);
		}
	}
	Log_Write("logs/warn_log.txt", "[%s] %s has warned %s for %s.", ReturnDate(), ReturnName(playerid, 0), ReturnName(userid, 0), reason);
	return 1;
}

CMD:clearwarns(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/clearwarns [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah memasukkan pemain yang salah.");

	ResetWarnings(userid);

	SendInfoMessage(playerid, "You have cleared %s's warnings.", ReturnName(userid, 0));
	SendInfoMessage(userid, "%s has cleared your warnings.", ReturnName(playerid, 0));

	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has cleared %s's warnings.", ReturnName(playerid, 0), ReturnName(userid, 0));
	return 1;
}

CMD:sorting(playerid, params[])
{
	new id = -1;

	if (PlayerData[playerid][pJob] != JOB_SORTER)
	    return SendErrorMessage(playerid, "You don't have the appropriate job.");

    if ((id = Job_NearestPoint(playerid)) == -1 || JobData[id][jobType] != JOB_SORTER)
		return SendErrorMessage(playerid, "You are not in range of the sorting facility.");
	
 	switch (PlayerData[playerid][pSorting])
 	{
	 	case -1:
 	    {
 	        PlayerData[playerid][pSorting] = id;
 	        PlayerData[playerid][pSortCrate] = 1;

			SendServerMessage(playerid, "You have started sorting. Please make your way to the marker.");

 	        SetPlayerAttachedObject(playerid, 4, 1220, 5, 0.137832, 0.176979, 0.151424, 96.305931, 185.363006, 20.328088, 0.699999, 0.800000, 0.699999);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

			ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
			SetPlayerCheckpoint(playerid, JobData[id][jobDeliver][0], JobData[id][jobDeliver][1], JobData[id][jobDeliver][2], 1.0);
		}
		default:
		{
		    PlayerData[playerid][pSorting] = -1;

		    if (PlayerData[playerid][pSortCrate] != 0)
		    {
		        PlayerData[playerid][pSortCrate] = 0;

		        RemovePlayerAttachedObject(playerid, 4);
		        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
 	        }
 	        DisablePlayerCheckpoint(playerid);
 	        SendServerMessage(playerid, "You have finished sorting packages.");
 	    }
	}
	return 1;
}

CMD:passwep(playerid, params[])
{
	new
	    weaponid = GetWeapon(playerid),
	    ammo = GetPlayerAmmo(playerid),
		userid;

	if (!weaponid)
	    return SendErrorMessage(playerid, "You are not holding any weapon to pass.");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/passwep [playerid/name]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
		return SendErrorMessage(playerid, "You can't give yourself a weapon.");

	if (PlayerData[userid][pGuns][g_aWeaponSlots[weaponid]] != 0)
	    return SendErrorMessage(playerid, "That player has a weapon in the same slot already.");

	ResetWeapon(playerid, weaponid);
	GiveWeaponToPlayer(userid, weaponid, ammo);

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has passed their %s to %s.", ReturnName(playerid, 0), ReturnWeaponName(weaponid), ReturnName(userid, 0));
	Log_Write("logs/give_log.txt", "[%s] %s (%s) has given a %s with %d ammo to %s (%s).", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnWeaponName(weaponid), ammo, ReturnName(userid, 0), PlayerData[userid][pIP]);
	return 1;
}

CMD:vw(playerid, params[]) {
	SendClientMessageEx(playerid, COLOR_CLIENT, "Current Virtual World: %d", GetPlayerVirtualWorld(playerid));

	return 1;
}

CMD:th(playerid, params[])
{
	switch (PlayerData[playerid][pHUD])
	{
	    case 0:
	    {
	        PlayerData[playerid][pHUD] = 1;

	        ShowHungerTextdraw(playerid, 1);
	        SendServerMessage(playerid, "HUD SHOW");

	        if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsSpeedoVehicle(GetPlayerVehicleID(playerid)))
		    {
				PlayerData[playerid][pDisableSpeedo] = 0;
				TextDrawShowForPlayer(playerid, CARMODELUPDATE[playerid]);
				TextDrawShowForPlayer(playerid, CARNAMEUPDATE[playerid]);
				TextDrawShowForPlayer(playerid, PLATEUPDATE[playerid]);
				TextDrawShowForPlayer(playerid, METERUPDATE[playerid]);
		       	for (new i = 0; i < 18; i ++) 
				{
					TextDrawShowForPlayer(playerid, NEWMETER[playerid][i]);
				}
				for (new i = 0; i < 4; i ++) 
				{
					ShowPlayerProgressBar(playerid, MINYAKNHEALTH[playerid][i]);
				}
		    }
		}
	    case 1:
	    {
	        PlayerData[playerid][pDisableSpeedo] = 1;
	        PlayerData[playerid][pHUD] = 0;

	        ShowHungerTextdraw(playerid, 0);
	        SendServerMessage(playerid, "HUD HIDE");

			TextDrawHideForPlayer(playerid, CARMODELUPDATE[playerid]);
			TextDrawHideForPlayer(playerid, CARNAMEUPDATE[playerid]);
			TextDrawHideForPlayer(playerid, PLATEUPDATE[playerid]);
			TextDrawHideForPlayer(playerid, METERUPDATE[playerid]);
			for (new i = 0; i < 18; i ++) 
			{
				TextDrawHideForPlayer(playerid, NEWMETER[playerid][i]);
			}
			for (new i = 0; i < 19; i ++) 
			{
				TextDrawHideForPlayer(playerid, NEWMETERUPDATE[playerid][i]);
			}
			for (new i = 0; i < 4; i ++) 
			{
				HidePlayerProgressBar(playerid, MINYAKNHEALTH[playerid][i]);
			}
		}
	}
	return 1;
}

CMD:healall(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	foreach (new i : Player) 
	{
	    SetPlayerHealthEx(i, 100.0);
	}
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has healed all players online.", ReturnName(playerid, 0));
	return 1;
}

CMD:saveall(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	foreach (new i : Player) {
		SQL_SaveCharacter(i);
	}
	SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"%s has saved all players accounts.", ReturnName(playerid, 0));
	return 1;
}

CMD:w(playerid, params[])
{
	new userid, text[128];

    if (sscanf(params, "us[128]", userid, text))
	    return SendUsageMessage(playerid, "/(w)hisper [playerid/name] [text]");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "That player is disconnected or not near you.");

	if (userid == playerid)
		return SendErrorMessage(playerid, "You can't whisper yourself.");

    if (strlen(text) > 64) {
	    SendClientMessageEx(userid, COLOR_YELLOW, "** Whisper from %s (%d): %.64s", ReturnName(playerid, 0), playerid, text);
	    SendClientMessageEx(userid, COLOR_YELLOW, "...%s **", text[64]);

	    SendClientMessageEx(playerid, COLOR_YELLOW, "** Whisper to %s (%d): %.64s", ReturnName(userid, 0), userid, text);
	    SendClientMessageEx(playerid, COLOR_YELLOW, "...%s **", text[64]);
	}
	else {
	    SendClientMessageEx(userid, COLOR_YELLOW, "** Whisper from %s (%d): %s **", ReturnName(playerid, 0), playerid, text);
	    SendClientMessageEx(playerid, COLOR_YELLOW, "** Whisper to %s (%d): %s **", ReturnName(userid, 0), userid, text);
	}
	return 1;
}

CMD:mask(playerid, params[])
{
	if (!Inventory_HasItem(playerid, "Mask"))
		return SendErrorMessage(playerid, "You don't have any mask.");

	switch (PlayerData[playerid][pMaskOn])
	{
		case 0:
		{
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a mask and puts it on.", ReturnName(playerid, 0));
		    PlayerData[playerid][pMaskOn] = 1;
			new string[64];
			format(string, sizeof(string), "Mask_%d", PlayerData[playerid][pMaskID]);
			SetPlayerName(playerid, string);
		}
		case 1:
		{
		    PlayerData[playerid][pMaskOn] = 0;
			SetPlayerName(playerid, PlayerData[playerid][pName]);
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes their mask off and puts it away.", ReturnName(playerid, 0));
		}
	}
	return 1;
}

CMD:masked(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	static
	    name[24];

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

    foreach (new i : Player) if (PlayerData[i][pMaskOn]) {
        GetPlayerName(i, name, sizeof(name));

        SendClientMessageEx(playerid, COLOR_WHITE, "* %s (#%d)", name, PlayerData[i][pMaskID]);
	}
	SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
	return 1;
}

CMD:listguns(playerid, params[])
{
	new userid;

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/listguns [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "The specified player is disconnected.");

	new
	    weaponid,
	    ammo;

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
    SendClientMessageEx(playerid, COLOR_LIGHTRED, "%s's Weapons:", ReturnName(userid, 0));

	for (new i = 0; i < 13; i ++)
	{
		GetPlayerWeaponData(userid, i, weaponid, ammo);

		if (weaponid > 0)
		    SendClientMessageEx(playerid, COLOR_WHITE, "* %s (%d ammo)", ReturnWeaponName(weaponid), ammo);
	}
	SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
	return 1;
}

CMD:siren(playerid, params[])
{
	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You are not a police officer.");

	new vehicleid = GetPlayerVehicleID(playerid);

	if (!IsPlayerInAnyVehicle(playerid))
	    return SendErrorMessage(playerid, "You must be inside a vehicle.");

	switch (CoreVehicles[vehicleid][vehSirenOn])
	{
	    case 0:
	    {
			static
        		Float:fSize[3],
        		Float:fSeat[3];

		    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, fSize[0], fSize[1], fSize[2]); // need height (z)
    		GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_FRONTSEAT, fSeat[0], fSeat[1], fSeat[2]); // need pos (x, y)

            CoreVehicles[vehicleid][vehSirenOn] = 1;
			CoreVehicles[vehicleid][vehSirenObject] = CreateDynamicObject(18646, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);

		    AttachDynamicObjectToVehicle(CoreVehicles[vehicleid][vehSirenObject], vehicleid, -fSeat[0], fSeat[1], fSize[2] / 2.0, 0.0, 0.0, 0.0);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s attaches a portable siren to the vehicle.", ReturnName(playerid, 0));
		}
		case 1:
		{
		    CoreVehicles[vehicleid][vehSirenOn] = 0;

			DestroyDynamicObject(CoreVehicles[vehicleid][vehSirenObject]);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s detaches a portable siren from the vehicle.", ReturnName(playerid, 0));
		}
	}
	return 1;
}

CMD:setinventory(playerid, params[])
{
	static
	    userid,
		capacity;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "ud", userid, capacity))
	    return SendUsageMessage(playerid, "/setinventory [playerid/name] [amount]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "The specified player is disconnected.");

	if (capacity < 1 || capacity > 120)
	    return SendErrorMessage(playerid, "The specified capacity can't exceed 120 items.");

	PlayerData[userid][pCapacity] = 120;

	SendServerMessage(playerid, "You has set %s's inventory capacity to %d items.", ReturnName(userid, 0), capacity);
	SendServerMessage(userid, "%s has set your inventory capacity to %d items.", ReturnName(playerid, 0), capacity);
	return 1;
}

CMD:breakcuffs(playerid, params[])
{
	static
		userid;

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/breakcuffs [playerid/name]");

	if (!Inventory_HasItem(playerid, "Crowbar"))
	    return SendErrorMessage(playerid, "You don't have a crowbar.");

	if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 6.0))
	    return SendErrorMessage(playerid, "The specified player is disconnected or not near you.");

	if (!PlayerData[userid][pCuffed])
	    return SendErrorMessage(playerid, "The specified player is not cuffed.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You can't pick your own handcuffs.");

	SetTimerEx("BreakCuffs", 3000, false, "dd", playerid, userid);
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s attempts to pick the cuffs with a crowbar.", ReturnName(playerid, 0));
	return 1;
}

CMD:dice(playerid, params[])
{
	new
		number = random(6) + 1;

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s rolls a dice landing on the number %d.", ReturnName(playerid, 0), number);
	return 1;
}

CMD:shakehand(playerid, params[])
{
	static
	    userid,
	    type;

	if (sscanf(params, "ud", userid, type))
	    return SendUsageMessage(playerid, "/shakehand [playerid/name] [type]");

    if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 6.0))
	    return SendErrorMessage(playerid, "The specified player is disconnected or not near you.");

    if (userid == playerid)
		return SendErrorMessage(playerid, "You cannot shake your own hand.");

	if (type < 1 || type > 6)
	    return SendErrorMessage(playerid, "You must specify a type from 1 to 6.");

	PlayerData[userid][pShakeOffer] = playerid;
	PlayerData[userid][pShakeType] = type;

	SendServerMessage(userid, "%s has offered to shake your hand (type \"/approve greet\").", ReturnName(playerid, 0));
	SendServerMessage(playerid, "You have offered to shake %s's hand.", ReturnName(userid, 0));
	return 1;
}

CMD:frisk(playerid, params[])
{
	static
	    userid;

	if (sscanf(params, "u", userid))
	    return SendUsageMessage(playerid, "/frisk [playerid/name]");

    if (userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 6.0))
	    return SendErrorMessage(playerid, "The specified player is disconnected or not near you.");

    if (userid == playerid)
		return SendErrorMessage(playerid, "You cannot frisk yourself.");

	PlayerData[userid][pFriskOffer] = playerid;

	SendServerMessage(userid, "%s has offered to frisk you (type \"/approve frisk\").", ReturnName(playerid, 0));
	SendServerMessage(playerid, "You have offered to frisk %s.", ReturnName(userid, 0));
	return 1;
}

CMD:creategraffiti(playerid, params[])
{
	static
	    id = -1,
		Float:x,
		Float:y,
		Float:z,
		Float:angle;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
 		return SendErrorMessage(playerid, "You can only create graffiti points outside interiors.");

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	id = Graffiti_Create(x, y, z, angle);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for graffiti points.");

	EditDynamicObject(playerid, GraffitiData[id][graffitiObject]);

	PlayerData[playerid][pEditGraffiti] = id;
	SendServerMessage(playerid, "You have successfully created graffiti ID: %d.", id);
	return 1;
}

CMD:destroygraffiti(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroygraffiti [graffiti id]");

	if ((id < 0 || id >= MAX_GRAFFITI_POINTS) || !GraffitiData[id][graffitiExists])
	    return SendErrorMessage(playerid, "You have specified an invalid graffiti ID.");

	Graffiti_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed graffiti ID: %d.", id);
	return 1;
}

CMD:fspray(playerid, params[])
{
	new id = Graffiti_Nearest(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "You are not near any graffiti point.");

	if (GetFactionType(playerid) != FACTION_GANG)
	    return SendErrorMessage(playerid, "You are not a member of an illegal faction.");

	Dialog_Show(playerid, GraffitiColor, DIALOG_STYLE_LIST, "Select Color", "{FFFFFF}White\n{FF0000}Red\n{FFFF00}Yellow\n{33CC33}Green\n{33CCFF}Light Blue\n{FFA500}Orange\n{1394BF}Dark Blue", "Select", "Cancel");
	return 1;
}

CMD:ahide(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	switch (PlayerData[playerid][pAdminHide])
	{
	    case 0:
	    {
	        PlayerData[playerid][pAdminHide] = 1;
	        SendServerMessage(playerid, "You are now hidden from the admin list.");
		}
		case 1:
	    {
	        PlayerData[playerid][pAdminHide] = 0;
	        SendServerMessage(playerid, "You are now visible in the admin list.");
		}
	}
	return 1;
}

CMD:picklock(playerid, params[])
{
	new id = Car_Nearest(playerid);

	if (!Inventory_HasItem(playerid, "Crowbar"))
	    return SendErrorMessage(playerid, "You don't have a crowbar.");

	if (id == -1)
	    return SendErrorMessage(playerid, "You are not in range of any vehicle.");

	if (!CarData[id][carLocked])
	    return SendErrorMessage(playerid, "This vehicle is not locked.");

	PlayerData[playerid][pPicking] = 1;
	PlayerData[playerid][pPickCar] = id;

	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a crowbar and picks the lock.", ReturnName(playerid, 0));
	SendServerMessage(playerid, "Please wait 60 seconds while the lock is picked.");
	return 1;
}

CMD:destroyplant(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyplant [plant id]");

	if ((id < 0 || id >= MAX_DRUG_PLANTS) || !PlantData[id][plantExists])
	    return SendErrorMessage(playerid, "You have specified an invalid plant ID.");

	Plant_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed plant ID: %d.", id);
	return 1;
}

CMD:givecar(playerid, params[])
{
	static
		userid,
	    model[32];

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "us[32]", userid, model))
	    return SendUsageMessage(playerid, "/givecar [playerid/name] [modelid/name]");

	if (Car_GetCount(userid) >= MAX_OWNABLE_CARS)
	    return SendErrorMessage(playerid, "This player already owns the maximum amount of cars.");

    if ((model[0] = GetVehicleModelByName(model)) == 0)
	    return SendErrorMessage(playerid, "Invalid model ID.");

	static
	    Float:x,
		Float:y,
		Float:z,
		Float:angle,
		id = -1;

    GetPlayerPos(userid, x, y, z);
	GetPlayerFacingAngle(userid, angle);

	id = Car_Create(PlayerData[userid][pID], model[0], x, y + 2, z + 1, angle, random(127), random(127));

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for dynamic vehicles.");

	SendServerMessage(playerid, "You have created vehicle ID: %d for %s.", CarData[id][carVehicle], ReturnName(userid, 0));
	return 1;
}

CMD:resetvw(playerid, params[])
{
	if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) > 0)
	{
	    SetPlayerVirtualWorld(playerid, 0);
	    SendServerMessage(playerid, "You have fixed your virtual world.");
	}
	else SendErrorMessage(playerid, "Your virtual world is not bugged right now.");
	return 1;
}

CMD:stopanim(playerid, params[])
{
	if (!AnimationCheck(playerid))
	    return SendErrorMessage(playerid, "You don't need to use this command right now.");

	ClearAnimations(playerid, 1);

	PlayerData[playerid][pLoopAnim] = 0;
	SendServerMessage(playerid, "You have stopped any animations.");
	return 1;
}

CMD:call(playerid, params[])
{
    if (!Inventory_HasItem(playerid, "Cellphone"))
	    return SendErrorMessage(playerid, "You don't have a cellphone on you.");

    if (PlayerData[playerid][pCuffed] || PlayerData[playerid][pInjured] || !IsPlayerSpawned(playerid))
	    return SendErrorMessage(playerid, "You can't use this command now.");

	static
	    targetid,
		number;

	if (sscanf(params, "d", number))
 	   return SendUsageMessage(playerid, "/call [phone number] (1222 for taxi, 911 for emergency)");

	if (!number)
	    return SendErrorMessage(playerid, "The specified phone number is not in service.");

	if (number == 911)
	{
		PlayerData[playerid][pEmergency] = 1;
		PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their cellphone and places a call.", ReturnName(playerid, 0));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]:{FFFFFF} Which service do you require: \"police\" or \"medics\"?");
	}
	else if (number == 1222)
	{
	    PlayerData[playerid][pTaxiCalled] = 1;
	    PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their cellphone and places a call.", ReturnName(playerid, 0));
		SendClientMessage(playerid, COLOR_YELLOW, "[OPERATOR]:{FFFFFF} The taxi department has been notified of your call.");

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has hung up their cellphone.", ReturnName(playerid, 0));
		SendJobMessage(3, COLOR_YELLOW, "** %s is requesting a taxi at %s (use /acceptcall to accept).", ReturnName(playerid, 0), GetPlayerLocation(playerid));
	}
	else if ((targetid = GetNumberOwner(number)) != INVALID_PLAYER_ID)
	{
	    if (targetid == playerid)
	        return SendErrorMessage(playerid, "Anda tidak boleh menelefon diri sendiri!");

		PlayerData[targetid][pIncomingCall] = 1;
		PlayerData[playerid][pIncomingCall] = 1;

		PlayerData[targetid][pCallLine] = playerid;
		PlayerData[playerid][pCallLine] = targetid;

		SendClientMessageEx(playerid, COLOR_YELLOW, "[PHONE]:{FFFFFF} Attempting to dial #%d, please wait for an answer...", number);
		SendClientMessageEx(targetid, COLOR_YELLOW, "[PHONE]:{FFFFFF} Incoming call from #%d (type \"/answer\" to answer the phone).", PlayerData[playerid][pPhone]);

        PlayerPlaySound(playerid, 3600, 0.0, 0.0, 0.0);
        PlayerPlaySoundEx(targetid, 23000);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their cellphone and places a call.", ReturnName(playerid, 0));
	}
	else
	{
	    SendErrorMessage(playerid, "The specified phone number is not in service.");
	}
	return 1;
}

CMD:destroycar(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
 	{
	 	if (IsPlayerInAnyVehicle(playerid))
		 	id = GetPlayerVehicleID(playerid);

		else return SendUsageMessage(playerid, "/destroycar [vehicle id]");
	}
	if (!IsValidVehicle(id) || Car_GetID(id) == -1)
	    return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	Car_Delete(Car_GetID(id));
	SendServerMessage(playerid, "You have successfully destroyed vehicle ID: %d.", id);
	return 1;
}

CMD:version(playerid, params[])
{
	new version[24];
    GetPlayerVersion(playerid, version, sizeof(version));

    new string[64];
    format(string, sizeof(string), "Your version of SA-MP: %s", version);
    SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}

CMD:pl(playerid, params[])
{
	new version[24];
    GetPlayerVersion(playerid, version, sizeof(version));

    new string[64];
    format(string, sizeof(string), "Your packet loss percent: %.1f%%", NetStats_PacketLossPercent(playerid));
    SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}

CMD:playsong(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");
	
	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new songname[128], tmp[512];
	if (sscanf(params, "s[128]", songname))
	{
		SendUsageMessage(playerid, "/playsong <link>");
		return 1;
	}
	
	format(tmp, sizeof(tmp), "%s", songname);
	foreach(new i : Player)
	{
		PlayAudioStreamForPlayer(i, tmp);
	}
	return 1;
}

CMD:shh(playerid, params[])
{
	StopAudioStreamForPlayer(playerid);
	return 1;
}

CMD:uwep(playerid, params[])
{
	SetWeapons(playerid);
	SendServerMessage(playerid, "Anda telah keluarkan semua senjata.");
	return 1;
}

CMD:swep(playerid, params[])
{
	ResetPlayerWeapons(playerid);
	SendServerMessage(playerid, "Anda telah menyimpan semua senjata.");
	return 1;
}

CMD:createrent(playerid, params[])
{
	static
	    id = -1,
		Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	id = Rent_Create(x, y, z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for rent points.");

	SendServerMessage(playerid, "You have successfully created rent point ID: %d.", id);
	return 1;
}

CMD:destroyrent(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 2)
	    return SendErrorMessage(playerid, "Anda tidak mempunyai kebenaran untuk mengakses command ini!");

	if(PlayerData[playerid][pAdminDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	if (sscanf(params, "d", id))
	    return SendUsageMessage(playerid, "/destroyrent [point id]");

	if ((id < 0 || id >= MAX_RENT_POINTS) || !RentData[id][rentExists])
	    return SendErrorMessage(playerid, "You have specified an invalid rent point ID.");

	Rent_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed rent point ID: %d.", id);
	return 1;
}

CMD:calculator(playerid, params[])
{
	new option, Float:value1, Float:value2;

	if(sscanf(params, "fcf", value1, option, value2))
	{
	    SendUsageMessage(playerid, "/calculator [value 1] [ (+) Tambah (-) Tolak (*) Darab (/) Bahagi ] [value 2]");
	    return 1;
	}
	if(option == '/' && value2 == 0)
	{
	    return SendErrorMessage(playerid, "Anda tidak boleh bahagi dengan 0.");
	}

	if(option == '+') {
	    SendServerMessage(playerid, "** Keputusan: %.2f + %.2f = %.2f", value1, value2, value1 + value2);
	} else if(option == '-') {
	    SendServerMessage(playerid, "** Keputusan: %.2f - %.2f = %.2f", value1, value2, value1 - value2);
	} else if(option == '*' || option == 'x') {
		SendServerMessage(playerid, "** Keputusan: %.2f * %.2f = %.2f", value1, value2, value1 * value2);
	} else if(option == '/') {
		SendServerMessage(playerid, "** Keputusan: %.2f / %.2f = %.2f", value1, value2, value1 / value2);
	}

	return 1;
}

CMD:myproperties(playerid, params[])
{
	new string[150 * MAX_HOUSES], header[512], count, status[500];
	header = "";
	strcat(header,"#\tAdress\tLocation\tStatus\n",sizeof(header));

	for (new i = 0; i < MAX_HOUSES; i ++) if (House_IsOwner(playerid, i)) {
		if (HouseData[i][houseLocked])
		{
			status = ""RED_E"Locked"WHITE_E"";
		}
		else
		{
			status = ""GREEN_E"Unlocked"WHITE_E"";
		}
		format(string, sizeof(string), ""WHITE_E"%s%d (House)\t%s\t%s\t%s\n", string, i, HouseData[i][houseAddress], GetLocation(HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]), status);
		count++;
	}
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (Business_IsOwner(playerid, i) && BusinessData[i][bizOwner] != 99999999) {
		if (BusinessData[i][bizLocked])
		{
			status = ""RED_E"Closed"WHITE_E"";
		}
		else
		{
			status = ""GREEN_E"Opened"WHITE_E"";
		}
		format(string, sizeof(string), ""WHITE_E"%s%d (Business)\t%s\t%s\t%s\n", string, i, BusinessData[i][bizName], GetLocation(BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]), status);
		count++;
	}
	if (!count)
		return SendErrorMessage(playerid, "You don't own any properties.");
	
	strcat(header, string);
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, ""WHITE_E"My Properties", header, "Close", "");

	return 1;
}

CMD:salary(playerid, params[])
{
	new query[512];
	mysql_format(g_iHandle, query, sizeof(query), "SELECT * FROM salary WHERE Owner='%d' ORDER BY id ASC LIMIT 30", PlayerData[playerid][pID]);
	mysql_query(g_iHandle, query);
	new rows = cache_num_rows();
	if(rows) 
	{
		new list[2000], date[30], info[46], money, totalsal;

		format(list, sizeof(list), "{FFFFFF}Name\t{FFFFFF}Amount\t{FFFFFF}Date & Time\n");
		for(new i; i < rows; ++i)
		{
			cache_get_field_content(i, "Info", info);
			cache_get_field_content(i, "Date", date);
			money = cache_get_field_int(i, "Money");
			totalsal += money;

			format(list, sizeof(list), "%s{FFFFFF}%s\t{00FF00}%s\t{FFFFFF}%s\n", list, info, FormatNumber(money), date);
		}
		new title[48];
		format(title, sizeof(title), "Total Salary: %s", FormatNumber(totalsal));
		Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Close", "");
	}
	else
	{
		SendErrorMessage(playerid, "Anda tidak mempunyai sebarang salary.");
	}

	return 1;
}

CMD:v(playerid, params[])
{
	new string[256 * MAX_OWNABLE_CARS], header[512], count, status[500];
	header = "";
	strcat(header,"#\tModel\tPlate\tStatus\n",sizeof(header));

	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) if (Car_IsOwner(playerid, i)) 
	{	
		if (CarData[i][carImpounded] == 1)
		{
			status = ""BLUE_E"Impounded"WHITE_E"";
		}
		else if(IsValidVehicle(CarData[i][carVehicle]))
		{
			status = ""GREEN_E"Spawned"WHITE_E"";
		}
		else
		{
			status = ""RED_E"Despawned"WHITE_E"";
		}

		if(CarData[i][carGov] == 1)
		{
			format(string, sizeof(string), ""WHITE_E"%s%d\t%s\t"YELLOW_E"%s"WHITE_E"\t%s\n", string, CarData[i][carVehicle], ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate], status);
		}
		else
		{
			format(string, sizeof(string), ""WHITE_E"%s%d\t%s\t%s\t%s\n", string, CarData[i][carVehicle], ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate], status);
		}
		count++;
	}
	if (!count)
		return SendErrorMessage(playerid, "Anda tidak mempunyai sebarang kenderaan.");

	strcat(header, string);
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, ""WHITE_E"My Vehicle", header, "Close", "");
	return 1;
}

CMD:tune(playerid,params[])
{
	if (GetFactionType(playerid) != FACTION_MECHANIC)
		return SendErrorMessage(playerid, "You must be a mechanic member.");

	if(PlayerData[playerid][pOnDuty] == 0)
		return SendErrorMessage(playerid, "Anda perlu onduty untuk mengakses command ini!");

	new
		id = Mechanic_Nearest(playerid);

	if (id == 0)
		return SendErrorMessage(playerid, "You are not in range of mechanic point.");

	if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to tune a vehicle.");
	Dialog_Show(playerid, TuneVehicle, DIALOG_STYLE_LIST, "Tune", "Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix", "Confirm", "cancel");
	return 1;
}

// --------------------------------- End Commands 