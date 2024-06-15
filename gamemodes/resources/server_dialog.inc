Dialog:ShowOnly(playerid, response, listitem, inputtext[]) {
	playerid = INVALID_PLAYER_ID;
	response = 0;
	listitem = 0;
	inputtext[0] = '\0';
}

Dialog:GraffitiColor(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = Graffiti_Nearest(playerid);

		if (id == -1)
		    return 0;

	    if (IsSprayingInProgress(id))
	        return SendErrorMessage(playerid, "There is another player spraying at this point already.");

	    switch (listitem)
	    {
	        case 0:
	            PlayerData[playerid][pGraffitiColor] = 0xFFFFFFFF;

	        case 1:
	            PlayerData[playerid][pGraffitiColor] = 0xFFFF0000;

	        case 2:
	            PlayerData[playerid][pGraffitiColor] = 0xFFFFFF00;

	        case 3:
	            PlayerData[playerid][pGraffitiColor] = 0xFF33CC33;

	        case 4:
	            PlayerData[playerid][pGraffitiColor] = 0xFF33CCFF;

	        case 5:
	            PlayerData[playerid][pGraffitiColor] = 0xFFFFA500;

	        case 6:
	            PlayerData[playerid][pGraffitiColor] = 0xFF1394BF;
	    }
	    Dialog_Show(playerid, GraffitiText, DIALOG_STYLE_INPUT, "Graffiti Text", "Please enter the text you wish to spray below.\n\nNote: Your text input cannot exceed over 64 characters.", "Submit", "Cancel");
	}
	return 1;
}

Dialog:GraffitiText(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = Graffiti_Nearest(playerid);

		if (id == -1)
		    return 0;

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, GraffitiText, DIALOG_STYLE_INPUT, "Graffiti Text", "Please enter the text you wish to spray below.\n\nNote: Your text input cannot exceed over 64 characters.", "Submit", "Cancel");

		if (strlen(inputtext) > 64)
		    return Dialog_Show(playerid, GraffitiText, DIALOG_STYLE_INPUT, "Graffiti Text", "Error: Your input can't exceed 64 characters.\n\nPlease enter the text you wish to spray below.\n\nNote: Your text input cannot exceed over 64 characters.", "Submit", "Cancel");

        if (IsSprayingInProgress(id))
	        return SendErrorMessage(playerid, "There is another player spraying at this point already.");

        PlayerData[playerid][pGraffiti] = id;
        PlayerData[playerid][pGraffitiTime] = 15;

		strpack(PlayerData[playerid][pGraffitiText], inputtext, 64 char);
		ApplyAnimationEx(playerid, "GRAFFITI", "spraycan_fire", 4.1, 1, 0, 0, 0, 0, 1);

		SendServerMessage(playerid, "You are now spraying your graffiti.");
		GameTextForPlayer(playerid, "~b~Spraying...~w~ please wait!", 15000, 3);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a can of spray paint and sprays the wall.", ReturnName(playerid, 0));
	}
	return 1;
}

Dialog:PickupItems(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = NearestItems[playerid][listitem];

		if (id != -1 && DroppedItems[id][droppedModel])
		{
		    if (DroppedItems[id][droppedWeapon] != 0)
			{
  				if (PlayerData[playerid][pScore] < 2)
					return SendErrorMessage(playerid, "You must have at least 2 score.");

				GiveWeaponToPlayer(playerid, DroppedItems[id][droppedWeapon], DroppedItems[id][droppedAmmo]);

				Item_Delete(id);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a %s.", ReturnName(playerid, 0), ReturnWeaponName(DroppedItems[id][droppedWeapon]));
			}
			else if (PickupItem(playerid, id))
			{
				SendServerMessage(playerid, "Item %s added to inventory!", DroppedItems[id][droppedItem]);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a \"%s\".", ReturnName(playerid, 0), DroppedItems[id][droppedItem]);
			}
			else
				SendErrorMessage(playerid, "You don't have any room in your inventory.");
		}
		else SendErrorMessage(playerid, "This item was already picked up.");
	}
	return 1;
}

Dialog:StartDelivery(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = Job_NearestPoint(playerid);

	    if (id == -1)
	        return 0;

		PlayerData[playerid][pLoadType] = listitem + 1;
		PlayerData[playerid][pLoadCrate] = 1;
		PlayerData[playerid][pLoading] = 1;

		SendServerMessage(playerid, "You have selected \"%s\". Load the crates into a truck to begin.", inputtext);
		SetPlayerCheckpoint(playerid, JobData[id][jobPoint][0], JobData[id][jobPoint][1], JobData[id][jobPoint][2], 1.0);

        SetPlayerAttachedObject(playerid, 4, 3014, 1, 0.038192, 0.371544, 0.055191, 0.000000, 90.000000, 357.668670, 1.000000, 1.000000, 1.000000);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

		ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
		SendInfoMessage(playerid, "Press "YELLOW_E"ALT"WHITE_E" to load the crate.");
	}
	return 1;
}

Dialog:GatePass(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = Gate_Nearest(playerid);

	    if (id == -1)
	        return 0;

        if (isnull(inputtext))
        	return Dialog_Show(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "Please enter the password for this gate below:", "Submit", "Cancel");

		if (strcmp(inputtext, GateData[id][gatePass]) != 0)
  			return Dialog_Show(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "Error: Incorrect password specified.\n\nPlease enter the password for this gate below:", "Submit", "Cancel");

		Gate_Operate(id);
	}
	return 1;
}

Dialog:EditRanks(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!FactionData[PlayerData[playerid][pFactionEdit]][factionExists])
			return 0;

		PlayerData[playerid][pSelectedSlot] = listitem;
		Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);
	}
	return 1;
}

Dialog:SetRankName(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

	    if (strlen(inputtext) > 32)
	        return Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Error: The rank can't exceed 32 characters.\n\nRank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

		format(FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], 32, inputtext);
		Faction_SaveRanks(PlayerData[playerid][pFactionEdit]);

		Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
		SendServerMessage(playerid, "You have set the name of rank %d to \"%s\".", PlayerData[playerid][pSelectedSlot] + 1, inputtext);
	}
	else Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
	return 1;
}

Dialog:AcceptTaxi(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new targetid = strval(inputtext);

	    if (!IsPlayerConnected(targetid))
	        return SendErrorMessage(playerid, "The specified player has disconnected.");

		if (!PlayerData[targetid][pTaxiCalled])
		    return SendErrorMessage(playerid, "That player's call was accepted by another taxi driver.");

		static
			Float:x,
			Float:y,
			Float:z;

		GetPlayerLocationEx(targetid, x, y, z);

		PlayerData[targetid][pTaxiCalled] = 0;
		Waypoint_Set(playerid, GetPlayerLocation(targetid), x, y, z);

        SendServerMessage(playerid, "You have accepted %s's taxi call.", ReturnName(targetid, 0));
        SendServerMessage(targetid, "%s has accepted your taxi call and is on their way.", ReturnName(playerid, 0));
	}
	return 1;
}

Dialog:AcceptShipment(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new bizid = strval(inputtext);

		if (!BusinessData[bizid][bizExists])
		    return 0;

	    if (!BusinessData[bizid][bizShipment])
	        return SendErrorMessage(playerid, "This business is no longer requesting a shipment.");

		if (IsShipmentAccepted(bizid))
		    return SendErrorMessage(playerid, "This shipment was already accepted.");

		foreach (new i : Player) if (Business_IsOwner(i, bizid)) {
		    SendServerMessage(i, "%s has accepted your shipment request.", ReturnName(playerid, 0));
		}
		PlayerData[playerid][pShipment] = bizid;
		SendServerMessage(playerid, "You have accepted the shipment. Type /startdelivery to start a delivery.");
	}
	return 1;
}

Dialog:RackWeapons(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = Rack_Nearest(playerid);

	    if (id == -1)
	        return 0;

	    if (!RackData[id][rackWeapons][listitem])
	    {
			if (!GetWeapon(playerid))
			    return SendErrorMessage(playerid, "You must be holding a weapon to store it.");

			RackData[id][rackWeapons][listitem] = GetWeapon(playerid);
			RackData[id][rackAmmo][listitem] = GetPlayerAmmo(playerid);

			ResetWeapon(playerid, GetWeapon(playerid));

			Rack_RefreshGuns(id);
			Rack_Save(id);

			ApplyAnimation(playerid, "WEAPONS", "SHP_Ar_Lift", 4.1, 0, 0, 0, 0, 0, 1);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a %s on the weapon rack.", ReturnName(playerid, 0), ReturnWeaponName(RackData[id][rackWeapons][listitem]));
	    }
	    else
	    {
	        GiveWeaponToPlayer(playerid, RackData[id][rackWeapons][listitem], RackData[id][rackAmmo][listitem]);
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a %s from the weapon rack.", ReturnName(playerid, 0), ReturnWeaponName(RackData[id][rackWeapons][listitem]));

            RackData[id][rackWeapons][listitem] = 0;
			RackData[id][rackAmmo][listitem] = 0;

			Rack_RefreshGuns(id);
			Rack_Save(id);

			ApplyAnimation(playerid, "WEAPONS", "SHP_Tray_Out", 4.1, 0, 0, 0, 0, 0, 1);
	    }
	}
	return 1;
}

Dialog:ServerPanel(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
			case 0:
			{
				if (g_ServerLocked)
				{
				    g_ServerLocked = false;

				    SendRconCommand("password 0");
				    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has unlocked the server.", ReturnName(playerid, 0));
				}
				else Dialog_Show(playerid, LockServer, DIALOG_STYLE_PASSWORD, "Lock Server", "Please enter the specified password below to lock the server with:", "Lock", "Back");
			}
			case 1:
			    Dialog_Show(playerid, SetHostname, DIALOG_STYLE_INPUT, "Set Hostname", "Please enter the new server hostname below:", "Submit", "Back");

			case 2:
			    Dialog_Show(playerid, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Please specify the MySQL query to execute below:", "Execute", "Back");
	    }
	}
	return 1;
}

Dialog:LockServer(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext) || !strcmp(inputtext, "0"))
	        return Dialog_Show(playerid, LockServer, DIALOG_STYLE_PASSWORD, "Lock Server", "Please enter the specified password below to lock the server with:", "Lock", "Back");

		if (strlen(inputtext) > 32)
		    return Dialog_Show(playerid, LockServer, DIALOG_STYLE_PASSWORD, "Lock Server", "Error: Please type a password shorter than 32 characters.\n\nPlease enter the specified password below to lock the server with:", "Lock", "Back");

		static
		    str[48];

	    format(str, sizeof(str), "password %s", inputtext);
		g_ServerLocked = true;

		SendRconCommand(str);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has locked the server.", ReturnName(playerid, 0));
	}
	else cmd_panel(playerid, "\1");
	return 1;
}

Dialog:SetHostname(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
	        return Dialog_Show(playerid, SetHostname, DIALOG_STYLE_INPUT, "Set Hostname", "Please enter the new server hostname below:", "Submit", "Back");

		static
		    str[128];

	    format(str, sizeof(str), "hostname %s", inputtext);

		SendRconCommand(str);
	    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has set the hostname to \"%s\".", ReturnName(playerid, 0), inputtext);
	}
	else cmd_panel(playerid, "\1");
	return 1;
}

Dialog:ExecuteQuery(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        if (isnull(inputtext))
            return Dialog_Show(playerid, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Please specify the MySQL query to execute below:", "Execute", "Back");

        if (strfind(inputtext, "DELETE", true) != -1 || strfind(inputtext, "DROP", true) != -1)
            return Dialog_Show(playerid, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Error: You can't execute \"DROP\" or \"DELETE\" queries.\n\nPlease specify the MySQL query to execute below:", "Execute", "Back");

		PlayerData[playerid][pExecute] = 1;
		mysql_tquery(g_iHandle, inputtext, "OnQueryExecute", "ds", playerid, inputtext);
	}
	else cmd_panel(playerid, "\1");
	return 1;
}

Dialog:EntrancePass(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Entrance_Inside(playerid) == -1) ? (Entrance_Nearest(playerid)) : (Entrance_Inside(playerid));

		if (id == -1)
		    return SendErrorMessage(playerid, "You are not in range of any entrance.");

		if (strcmp(EntranceData[id][entrancePass], inputtext) != 0)
            return SendErrorMessage(playerid, "Invalid password specified.");

	    if (!EntranceData[id][entranceLocked])
		{
			EntranceData[id][entranceLocked] = true;
			Entrance_Save(id);

			SendServerMessage(playerid, "You have locked the entrance!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		else
		{
			EntranceData[id][entranceLocked] = false;
			Entrance_Save(id);

			SendServerMessage(playerid, "You have unlocked the entrance!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}

Dialog:ReleaseCar(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			carid = ListedVehicles[playerid][listitem];

	    if (carid != -1 && CarData[carid][carExists] && CarData[carid][carImpounded] != -1)
	    {
	        if (GetMoney(playerid) < CarData[carid][carImpoundPrice])
	            return SendErrorMessage(playerid, "You can't afford to release this vehicle.");

            GiveMoney(playerid, -CarData[carid][carImpoundPrice]);

			Car_Spawn(carid);

            CarData[carid][carPos][0] = 1535.9126;
            CarData[carid][carPos][1] = -1678.1501;
            CarData[carid][carPos][2] = 13.0877;
            CarData[carid][carPos][3] = 178.2638;

			SetVehiclePos(CarData[carid][carVehicle], CarData[carid][carPos][0], CarData[carid][carPos][1], CarData[carid][carPos][2]);
			SetVehicleZAngle(CarData[carid][carVehicle], CarData[carid][carPos][3]);

			SendServerMessage(playerid, "You have released your %s for %s.", ReturnVehicleModelName(CarData[carid][carModel]), FormatNumber(CarData[carid][carImpoundPrice]));

            CarData[carid][carImpounded] = 0;
            CarData[carid][carImpoundPrice] = 0;

            Car_Save(carid);
	    }
	}
	return 1;
}

Dialog:GiveItem(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        userid = -1,
			itemid = -1,
			string[32];

		if (sscanf(inputtext, "u", userid))
		    return Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "Give Item", "Please enter the name or the ID of the player:", "Submit", "Cancel");

		if (userid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "Give Item", "Error: Invalid player specified.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

	    if (!IsPlayerNearPlayer(playerid, userid, 6.0))
			return Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "Give Item", "Error: You are not near that player.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

	    if (userid == playerid)
			return Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "Give Item", "Error: You can't give items to yourself.\n\nPlease enter the name or the ID of the player:", "Submit", "Cancel");

		itemid = PlayerData[playerid][pInventoryItem];

		if (itemid == -1)
		    return 0;

		strunpack(string, InventoryData[playerid][itemid][invItem]);

		if (InventoryData[playerid][itemid][invQuantity] == 1)
		{
			if (!strcmp(string, "Backpack") && Inventory_HasItem(userid, "Backpack"))
			    return SendErrorMessage(playerid, "That player is already carrying a backpack.");

		    new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel]);

		    if (id == -1)
				return SendErrorMessage(playerid, "That player doesn't have anymore inventory slots.");

			if (!strcmp(string, "Backpack") && (id = GetPlayerBackpack(playerid)) != -1)
			{
			    BackpackData[id][backpackPlayer] = PlayerData[userid][pID];
				Backpack_Save(id);

				SetAccessories(userid);
			    Inventory_Remove(playerid, "Backpack");
			}
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a \"%s\" and gives it to %s.", ReturnName(playerid, 0), string, ReturnName(userid, 0));
		    SendServerMessage(userid, "%s has given you \"%s\" (added to inventory).", ReturnName(playerid, 0), string);

			Inventory_Remove(playerid, string);
		    Log_Write("logs/give_log.txt", "[%s] %s (%s) has given a %s to %s (%s).", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], string, ReturnName(userid, 0), PlayerData[userid][pIP]);
  		}
		else
		{
		    Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Give Item", "Item: %s (Quantity: %d)\n\nPlease enter the amount of this item you wish to give %s:", "Give", "Cancel", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid, 0));
		    PlayerData[playerid][pGiveItem] = userid;
		}
	}
	return 1;
}

Dialog:GiveQuantity(playerid, response, listitem, inputtext[])
{
	if (response && PlayerData[playerid][pGiveItem] != INVALID_PLAYER_ID)
	{
	    new
	        userid = PlayerData[playerid][pGiveItem],
	        itemid = PlayerData[playerid][pInventoryItem],
			string[32];

		strunpack(string, InventoryData[playerid][itemid][invItem]);

		if (isnull(inputtext))
			return Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Give Item", "Item: %s (Quantity: %d)\n\nPlease enter the amount of this item you wish to give %s:", "Give", "Cancel", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid, 0));

		if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
		    return  Dialog_Show(playerid, GiveQuantity, DIALOG_STYLE_INPUT, "Give Item", "Error: You don't have that much.\n\nItem: %s (Quantity: %d)\n\nPlease enter the amount of this item you wish to give %s:", "Give", "Cancel", string, InventoryData[playerid][itemid][invQuantity], ReturnName(userid, 0));

        new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel], strval(inputtext));

	    if (id == -1)
			return SendErrorMessage(playerid, "That player doesn't have anymore inventory slots.");

	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a \"%s\" and gives it to %s.", ReturnName(playerid, 0), string, ReturnName(userid, 0));
	    SendServerMessage(userid, "%s has given you \"%s\" (added to inventory).", ReturnName(playerid, 0), string);

		Inventory_Remove(playerid, string, strval(inputtext));
	    Log_Write("logs/give_log.txt", "[%s] %s (%s) has given %d %s to %s (%s).", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], strval(inputtext), string, ReturnName(userid, 0), PlayerData[userid][pIP]);
	}
	return 1;
}

Dialog:TakeItem(playerid, response, listitem, inputtext[])
{
	if (response && PlayerData[playerid][pGiveItem] != INVALID_PLAYER_ID)
	{
	    new
	        userid = PlayerData[playerid][pGiveItem],
	        itemid = PlayerData[PlayerData[playerid][pGiveItem]][pInventoryItem],
			string[32];

		strunpack(string, InventoryData[PlayerData[playerid][pGiveItem]][itemid][invItem]);

		if (isnull(inputtext))
			return Dialog_Show(playerid, TakeItem, DIALOG_STYLE_INPUT, "Take Item", "Item: %s (Quantity: %d)\n\nPlease enter the amount of this item you want to take:", "Take", "Cancel", string, InventoryData[PlayerData[playerid][pGiveItem]][itemid][invQuantity]);

		if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[PlayerData[playerid][pGiveItem]][itemid][invQuantity])
		    return  Dialog_Show(playerid, TakeItem, DIALOG_STYLE_INPUT, "Take Item", "Error: This player don't have that much.\n\nItem: %s (Quantity: %d)\n\nPlease enter the amount of this item you want to take:", "Take", "Cancel", string, InventoryData[PlayerData[playerid][pGiveItem]][itemid][invQuantity]);
		
        new id = Inventory_Add(playerid, string, InventoryData[PlayerData[playerid][pGiveItem]][itemid][invModel], strval(inputtext));

	    if (id == -1)
			return SendErrorMessage(playerid, "You doesn't have anymore inventory slots.");

	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a \"%s\" from %s.", ReturnName(playerid, 0), string, ReturnName(userid, 0));
	    SendServerMessage(playerid, "You have take item from %s. Item: \"%s\" (added to inventory).", ReturnName(userid, 0), string);

		Inventory_Remove(userid, string, strval(inputtext));
	}
	return 1;
}

Dialog:BackpackLoot(playerid, response, listitem, inputtext[])
{
	static id = -1;

	if (response)
	{
	    if (!strcmp(inputtext, "Take Backpack"))
	    {
	        if (Inventory_HasItem(playerid, "Backpack"))
	            return SendErrorMessage(playerid, "You can only have one backpack.");

	        id = PlayerData[playerid][pBackpackLoot];

	        BackpackData[id][backpackPlayer] = PlayerData[playerid][pID];
	        BackpackData[id][backpackPos][0] = 0.0;
	        BackpackData[id][backpackPos][1] = 0.0;
	        BackpackData[id][backpackPos][2] = 0.0;

	        DestroyDynamic3DTextLabel(BackpackData[id][backpackText3D]);
	        DestroyDynamicObject(BackpackData[id][backpackObject]);

			Backpack_Save(id);
			Inventory_Add(playerid, "Backpack", 3026);

			SetAccessories(playerid);
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a backpack.", ReturnName(playerid, 0));
		}
		else if ((id = BackpackListed[playerid][listitem]) != -1)
		{
			new
			    string[32];

			strcat(string, BackpackItems[id][bItemName]);

			Inventory_Add(playerid, string, BackpackItems[id][bItemModel], BackpackItems[id][bItemQuantity]);
			Backpack_Remove(BackpackItems[id][bItemBackpack], string, BackpackItems[id][bItemQuantity]);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the backpack and takes a \"%s\".", ReturnName(playerid, 0), string);
		}
	}
	return 1;
}

Dialog:BackpackDeposit(playerid, response, listitem, inputtext[])
{
	static
	    string[32];

	strunpack(string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invItem]);

	if (response)
	{
		new amount = strval(inputtext);

		if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity])
		    return Dialog_Show(playerid, BackpackDeposit, DIALOG_STYLE_INPUT, "Backpack Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);

		Backpack_Add(GetPlayerBackpack(playerid), string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invModel], amount);
		Inventory_Remove(playerid, string, amount);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their backpack.", ReturnName(playerid, 0), string);
		Backpack_Open(playerid);
	}
	else Backpack_Open(playerid);
	return 1;
}

Dialog:BackpackTake(playerid, response, listitem, inputtext[])
{
	static
	    string[32],
		id = -1;

	if (response)
	{
		new amount = strval(inputtext);

		id = PlayerData[playerid][pStorageItem];

		strunpack(string, BackpackItems[id][bItemName]);

		if (amount < 1 || amount > BackpackItems[id][bItemQuantity])
		    return Dialog_Show(playerid, BackpackTake, DIALOG_STYLE_INPUT, "Backpack Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, BackpackItems[id][bItemQuantity]);

		Inventory_Add(playerid, string, BackpackItems[id][bItemModel], amount);
        Backpack_Remove(GetPlayerBackpack(playerid), string, amount);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their backpack.", ReturnName(playerid, 0), string);
		Backpack_Open(playerid);
	}
	else Backpack_Open(playerid);
	return 1;
}

Dialog:BackpackOptions(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pStorageItem], string[32];

	    switch (listitem)
	    {
	        case 0:
	        {
	            strcat(string, BackpackItems[id][bItemName]);

	            if (BackpackItems[id][bItemQuantity] == 1)
	            {
	                Inventory_Add(playerid, string, BackpackItems[id][bItemModel]);
					Backpack_Remove(GetPlayerBackpack(playerid), string);

					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their backpack.", ReturnName(playerid, 0), string);
					Backpack_Open(playerid);
	            }
	            else
	            {
	                Dialog_Show(playerid, BackpackTake, DIALOG_STYLE_INPUT, "Backpack Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, BackpackItems[id][bItemQuantity]);
	            }
			}
	        case 1:
	        {
	            new itemid = Inventory_GetItemID(playerid, BackpackItems[id][bItemName]);

	            if (itemid == -1)
					return SendErrorMessage(playerid, "You don't have anymore of this item to store!");

                strunpack(string, InventoryData[playerid][itemid][invItem]);

				if (IsFurnitureItem(string))
				    return SendErrorMessage(playerid, "You can't store furniture in your backpack.");

				if (InventoryData[playerid][itemid][invQuantity] == 1)
	            {
	                Backpack_Add(GetPlayerBackpack(playerid), string, InventoryData[playerid][itemid][invModel]);
					Inventory_Remove(playerid, string);

					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their backpack.", ReturnName(playerid, 0), string);
					Backpack_Open(playerid);
	            }
	            else
	            {
	                PlayerData[playerid][pInventoryItem] = itemid;
	                Dialog_Show(playerid, BackpackDeposit, DIALOG_STYLE_INPUT, "Backpack Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);
	            }
			}
   		}
	}
	else Backpack_Open(playerid);
	return 1;
}

Dialog:Backpack(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = -1, string[48];

	    if (!listitem)
		{
	        if (Backpack_GetItems(GetPlayerBackpack(playerid)) >= MAX_BACKPACK_CAPACITY)
	            return SendErrorMessage(playerid, "The backpack has reached it's capacity of %d items.", MAX_BACKPACK_CAPACITY);

	        OpenInventory(playerid);

	        PlayerData[playerid][pStorageSelect] = 3;
	    }
	    else if ((id = BackpackListed[playerid][listitem-1]) != -1) {
	        PlayerData[playerid][pStorageItem] = id;

			format(string, sizeof(string), "%s (Quantity: %d)", BackpackItems[id][bItemName], BackpackItems[id][bItemQuantity]);
	        Dialog_Show(playerid, BackpackOptions, DIALOG_STYLE_LIST, string, "Take Item\nStore Item\nDrop Item", "Select", "Back");
		}
	}
	return 1;
}

Dialog:MyTickets(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!TicketData[playerid][listitem][ticketExists])
	        return SendErrorMessage(playerid, "There is no ticket in the selected slot.");

		if (PlayerData[playerid][pBankMoney] < TicketData[playerid][listitem][ticketFee])
		    return SendErrorMessage(playerid, "You can't afford to pay this ticket.");

		PlayerData[playerid][pBankMoney] -= TicketData[playerid][listitem][ticketFee];
		FactionData[TicketData[playerid][listitem][ticketFaction]][factionMoney] += TicketData[playerid][listitem][ticketFee];
		Faction_Save(TicketData[playerid][listitem][ticketFaction]);

		SendFactionMessage(TicketData[playerid][listitem][ticketFaction], COLOR_RADIO, "[INVOICE] "WHITE_E"%s telah membayar invoice "YELLOW_E"%s "WHITE_E"sebanyak "GREEN_E"%s"WHITE_E".", ReturnName(playerid, 0), TicketData[playerid][listitem][ticketReason], FormatNumber(TicketData[playerid][listitem][ticketFee]));

		SendServerMessage(playerid, "You have paid off a %s ticket for \"%s\".", FormatNumber(TicketData[playerid][listitem][ticketFee]), TicketData[playerid][listitem][ticketReason]);
		Ticket_Remove(playerid, listitem);
	}
	else
	{
		Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
	}
	return 1;
}

Dialog:MainGPS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
			case 0:
	            Dialog_Show(playerid, GeneralLocation, DIALOG_STYLE_LIST, "General Location", "Ibu Pejabat Polis\nIbu Pejabat JPJ\nHospital Besar\nDealer Mechanic Los Santos\nPejabat Istana Negara\nLos Santos Bank\nDataran Merdeka\nAuto Garage Service", "Submit", "Cancel");

	        case 1:
	            Dialog_Show(playerid, FindHouse, DIALOG_STYLE_INPUT, "Find House", "Please enter the address of the house below:", "Submit", "Cancel");

			case 2:
			    Dialog_Show(playerid, FindBusiness, DIALOG_STYLE_LIST, "Find Business", "Retail Store\nElectronic Store\nClothing Store\nFast Food\nDealership\nGas Station\nFurniture Store", "Submit", "Cancel");

			case 3:
			    Dialog_Show(playerid, FindJob, DIALOG_STYLE_LIST, "Find Job", "", "Select", "Cancel");

			case 4:
				Dialog_Show(playerid, FindSidejob, DIALOG_STYLE_LIST, "Find Sidejob", "Kait Buah Kelapa\nPembersih Jalan Raya", "Select", "Cancel");

			case 5:
			{
				static
				    string[MAX_GPS_LOCATIONS * 32];

				string = "Add Location\n";

				for (new i = 0; i != MAX_GPS_LOCATIONS; i ++) if (LocationData[playerid][i][locationExists]) {
				    format(string, sizeof(string), "%s%s\n", string, LocationData[playerid][i][locationName]);
				}
				Dialog_Show(playerid, CustomLocations, DIALOG_STYLE_LIST, "Custom Locations", string, "Select", "Back");
			}
		}
	}
	return 1;
}

Dialog:FindSidejob(playerid, response, listitem, inputtext[])
{
	if (response) 
	{
		switch(listitem)
		{
			case 0:
			{
				Waypoint_Set(playerid, "Ladang Kelapa", 1847.0599,605.2465,10.9592);
	        	SendServerMessage(playerid, "Waypoint set to Sidejob Kait Buah Kelapa.");
			}
			case 1:
			{
				Waypoint_Set(playerid, "Sanitary HQ", 1618.6732,-1894.4911,13.5491);
	        	SendServerMessage(playerid, "Waypoint set to Sidejob Pembersih Jalan Raya.");
			}
		}
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:GeneralLocation(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch(listitem)
		{
			case 0:
			{
				Waypoint_Set(playerid, "Ibu Pejabat Polis", 1535.0446,-1672.2507,13.3828);
	        	SendServerMessage(playerid, "Waypoint set to Ibu Pejabat Polis.");
			}
			case 1:
			{
				Waypoint_Set(playerid, "Ibu Pejabat JPJ", 642.0698,-1496.3688,14.6660);
	        	SendServerMessage(playerid, "Waypoint set to Ibu Pejabat JPJ.");
			}
			case 2:
			{
				Waypoint_Set(playerid, "Hospital Besar", 2031.2904,-1407.9396,17.1704);
	        	SendServerMessage(playerid, "Waypoint set to Hospital Besar.");
			}
			case 3:
			{
				Waypoint_Set(playerid, "Dealer Mechanic LS", 1548.2467,-2182.2749,13.6898);
	        	SendServerMessage(playerid, "Waypoint set to Dealer Mechanic Los Santos.");
			}
			case 4:
			{
				Waypoint_Set(playerid, "Pejabat Istana Negara", 1243.4689,-2036.2070,59.8996);
	        	SendServerMessage(playerid, "Waypoint set to Pejabat Istana Negara.");
			}
			case 5:
			{
				Waypoint_Set(playerid, "LS Bank", 1670.3691,-1285.3745,14.6038);
	        	SendServerMessage(playerid, "Waypoint set to Los Santos Bank.");
			}
			case 6:
			{
				Waypoint_Set(playerid, "Dataran Merdeka", 2247.2935,1389.3848,10.7991);
	        	SendServerMessage(playerid, "Waypoint set to Dataran Merdeka.");
			}
			case 7:
			{
				Waypoint_Set(playerid, "Auto Garage Service", 1860.1914,823.3962,9.4228);
	        	SendServerMessage(playerid, "Waypoint set to Auto Grage Service.");
			}
		}
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:FindHouse(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if (isnull(inputtext) || strlen(inputtext) > 32)
		    return Dialog_Show(playerid, FindHouse, DIALOG_STYLE_INPUT, "Find House", "Please enter the address of the house below:", "Submit", "Cancel");

		for (new i = 0; i != MAX_HOUSES; i ++)
		{
			if (HouseData[i][houseExists] && !strcmp(HouseData[i][houseAddress], inputtext, true))
	    	{
         		Waypoint_Set(playerid, HouseData[i][houseAddress], HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]);
	        	return SendServerMessage(playerid, "Waypoint set to \"%s\" (marked on radar).", HouseData[i][houseAddress]);
			}
		}
        Dialog_Show(playerid, FindHouse, DIALOG_STYLE_INPUT, "Find House", "Error: No results found for \"%s\".\n\nPlease enter the address of the house below:", "Submit", "Cancel", inputtext);
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:FindBusiness(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new bizid = GetClosestBusiness(playerid, listitem + 1);

		if (bizid != -1)
		{
		    Waypoint_Set(playerid, BusinessData[bizid][bizName], BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2]);
	        SendServerMessage(playerid, "Waypoint set to closest %s (marked on radar).", inputtext);
		}
		else
		{
			SendErrorMessage(playerid, "The GPS was unable to locate any business.");
		}
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:FindJob(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		//
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:CustomLocations(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!listitem) {
			Dialog_Show(playerid, AddLocation, DIALOG_STYLE_INPUT, "Add Location", "Please enter the desired name of the location below:", "Submit", "Cancel");
	    }
	    else
		{
		    new id = Location_GetID(playerid, inputtext);

		    if (id != -1) {
		        PlayerData[playerid][pSelectedSlot] = id;

		        Dialog_Show(playerid, LocationInfo, DIALOG_STYLE_LIST, inputtext, "Set Waypoint\nDelete Location", "Select", "Back");
			}
		}
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:AddLocation(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
	        return Dialog_Show(playerid, AddLocation, DIALOG_STYLE_INPUT, "Add Location", "Please enter the desired name of the location below:", "Submit", "Cancel");

		if (strlen(inputtext) > 32)
		    return Dialog_Show(playerid, AddLocation, DIALOG_STYLE_INPUT, "Add Location", "Error: The name can't exceed 32 characters.\n\nPlease enter the desired name of the location below:", "Submit", "Cancel");

		static
		    Float:fX,
		    Float:fY,
		    Float:fZ,
			id = -1;

		if ((id = House_Inside(playerid)) != -1) {
		    fX = HouseData[id][housePos][0];
		    fY = HouseData[id][housePos][1];
		    fZ = HouseData[id][housePos][2];
		}
		else if ((id = Business_Inside(playerid)) != -1) {
		    fX = BusinessData[id][bizPos][0];
		    fY = BusinessData[id][bizPos][1];
		    fZ = BusinessData[id][bizPos][2];
		}
        else if ((id = Entrance_Inside(playerid)) != -1) {
		    fX = EntranceData[id][entrancePos][0];
		    fY = EntranceData[id][entrancePos][1];
		    fZ = EntranceData[id][entrancePos][2];
		}
		else GetPlayerPos(playerid, fX, fY, fZ);

		Location_Add(playerid, inputtext, fX, fY, fZ);
		SendServerMessage(playerid, "You have added \"%s\" to your GPS.", inputtext);
	}
	else cmd_gps(playerid, "\1");
	return 1;
}

Dialog:LocationInfo(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pSelectedSlot];

	    switch (listitem)
	    {
	        case 0:
	        {
	            Waypoint_Set(playerid, LocationData[playerid][id][locationName], LocationData[playerid][id][locationPos][0], LocationData[playerid][id][locationPos][1], LocationData[playerid][id][locationPos][2]);
				SendServerMessage(playerid, "Waypoint set to \"%s\" (marked on radar).", LocationData[playerid][id][locationName]);
			}
			case 1:
			{
			    SendServerMessage(playerid, "You have removed \"%s\" from your GPS.", LocationData[playerid][id][locationName]);

				Location_Delete(playerid, LocationData[playerid][id][locationName]);
				dialog_MainGPS(playerid, 1, 4, "\1");
			}
	    }
	}
	else dialog_MainGPS(playerid, 1, 4, "\1");
	return 1;
}

Dialog:Warrants(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)))
	    return 0;

	if (response)
	{
	    static
	        name[64],
			targetid = INVALID_PLAYER_ID;

		strmid(name, inputtext, 0, strfind(inputtext, "(") - 1);

		if ((targetid = GetPlayerID(name, 0)) == INVALID_PLAYER_ID)
		    return SendErrorMessage(playerid, "The player is no longer connected.");

		if (PlayerData[targetid][pWarrants] < 1)
		    return SendErrorMessage(playerid, "The player no longer has any warrants.");

		PlayerData[playerid][pMDCPlayer] = targetid;

		format(name, sizeof(name), "MDC: %s", name);
		Dialog_Show(playerid, WarrantList, DIALOG_STYLE_LIST, name, "Track Player\nClear Warrants", "Select", "Back");
	}
	else cmd_mdc(playerid, "\1");
	return 1;
}

Dialog:WarrantList(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)) || PlayerData[playerid][pMDCPlayer] == INVALID_PLAYER_ID)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            SendServerMessage(playerid, "The MDC Satellite System is now trying to track %s...", ReturnName(PlayerData[playerid][pMDCPlayer], 0));
	            PlayerData[playerid][pTrackTime] = 3;
			}
			case 1:
			{
			    PlayerData[PlayerData[playerid][pMDCPlayer]][pWarrants] = 0;

			    SendServerMessage(playerid, "You have cleared %s's warrants.", ReturnName(PlayerData[playerid][pMDCPlayer], 0));
			    SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has cleared %s's active warrants.", ReturnName(playerid, 0), ReturnName(PlayerData[playerid][pMDCPlayer], 0));

			    PlayerData[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
			}
	    }
	}
	else
	{
	    PlayerData[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
	    dialog_MainMDC(playerid, 1, 0, "\1");
	}
	return 1;
}

Dialog:ChargeName(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)))
	    return 0;

	if (response)
	{
	    new targetid;

	    if (sscanf(inputtext, "u", targetid))
	        return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Place Charges", "Error: Please enter a valid user.\n\nPlease enter the name or ID of the player:", "Submit", "Back");

		if (targetid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Place Charges", "Error: Invalid user specified.\n\nPlease enter the name or ID of the player:", "Submit", "Back");

        if (PlayerData[targetid][pWarrants] > 14)
		    return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Place Charges", "Error: The user already has 15 active warrants.\n\nPlease enter the name or ID of the player:", "Submit", "Back");

		PlayerData[playerid][pMDCPlayer] = targetid;
		Dialog_Show(playerid, PlaceCharge, DIALOG_STYLE_INPUT, "Place Charge", "Please enter the description of the crime committed by %s:", "Submit", "Back", ReturnName(PlayerData[playerid][pMDCPlayer], 0));
	}
	else cmd_mdc(playerid, "\1");
	return 1;
}

Dialog:PlaceCharge(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)) || PlayerData[playerid][pMDCPlayer] == INVALID_PLAYER_ID)
	    return 0;

	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, PlaceCharge, DIALOG_STYLE_INPUT, "Place Charge", "Please enter the description of the crime committed by %s:", "Submit", "Back", ReturnName(PlayerData[playerid][pMDCPlayer], 0));

	    PlayerData[PlayerData[playerid][pMDCPlayer]][pWarrants]++;

	    AddWarrant(PlayerData[playerid][pMDCPlayer], playerid, inputtext);
	    SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has placed a charge on %s for \"%s\".", ReturnName(playerid, 0), ReturnName(PlayerData[playerid][pMDCPlayer], 0), inputtext);

	    cmd_mdc(playerid, "\1");
	}
	else
	{
	    PlayerData[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
	    cmd_mdc(playerid, "\1");
	}
	return 1;
}

Dialog:MainMDC(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)))
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            static
	                string[512];

				string[0] = 0;

				foreach (new i : Player) if (PlayerData[i][pWarrants] > 0) {
				    format(string, sizeof(string), "%s%s (%d warrants)\n", string, ReturnName(i, 0), PlayerData[i][pWarrants]);
				}
				if (!strlen(string))
				    return SendErrorMessage(playerid, "There are no active warrants.");

				Dialog_Show(playerid, Warrants, DIALOG_STYLE_LIST, "Active Warrants", string, "Select", "Back");
    		}
    		case 1:
    		{
    		    Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Place Charges", "Please enter the name or ID of the player:", "Submit", "Back");
			}
			case 2:
    		{
    		    Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "View Charges", "Please enter the name or ID of the player:", "Submit", "Back");
			}
	    }
	}
	return 1;
}

Dialog:ViewCharges(playerid, response, listitem, inputtext[])
{
	if (GetFactionType(playerid) != FACTION_POLICE || !IsACruiser(GetPlayerVehicleID(playerid)))
	    return 0;

	if (response)
	{
		if (isnull(inputtext) || strlen(inputtext) > 24)
		    return Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "View Charges", "Please enter the name or ID of the player:", "Submit", "Back");

		if (IsNumeric(inputtext) && IsPlayerConnected(strval(inputtext))) {
	        ViewCharges(playerid, ReturnName(strval(inputtext)));
		}
	    else if (!IsNumeric(inputtext)) {
	        ViewCharges(playerid, inputtext);
		}
		else {
		    Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "View Charges", "Error: Invalid user specified.\n\nPlease enter the name or ID of the player:", "Submit", "Back");
		}
	}
	else cmd_mdc(playerid, "\1");
	return 1;
}

Dialog:Locker(playerid, response, listitem, inputtext[])
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1 || !IsNearFactionLocker(playerid))
		return 0;

	if (response)
	{
	    static
	        skins[14],
	        string[512];

		string[0] = 0;

	    if (FactionData[factionid][factionType] != FACTION_GANG)
	    {
	        switch (listitem)
	        {
	            case 0:
	            {
	                if (!PlayerData[playerid][pOnDuty])
	                {
	                    PlayerData[playerid][pOnDuty] = true;
	                    SetPlayerArmourEx(playerid, 100.0);

	                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has clocked in and is now on duty.", ReturnName(playerid, 0));
	                }
	                else
	                {
	                    PlayerData[playerid][pOnDuty] = false;
	                    SetPlayerArmourEx(playerid, 0.0);

	                    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

	                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has clocked out and is now off duty.", ReturnName(playerid, 0));

						PlayerData[playerid][pFacSkin] = 0;
	                }
				}
				case 1:
				{
					if(PlayerData[playerid][pOnDuty] == 0)
						return SendErrorMessage(playerid, "You need to onduty to use this item!");

				    SetPlayerArmourEx(playerid, 100.0);
				    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches into the locker and takes out a vest.", ReturnName(playerid, 0));
				}
				case 2:
				{
					if(PlayerData[playerid][pOnDuty] == 0)
						return SendErrorMessage(playerid, "You need to onduty to use this item!");

					for (new i = 0; i < sizeof(skins); i ++)
					    skins[i] = (FactionData[factionid][factionSkins][i]) ? (FactionData[factionid][factionSkins][i]) : (19300);

					ShowModelSelectionMenu(playerid, "Choose Skin", MODEL_SELECTION_FACTION_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
				}
				case 3:
				{
					if(PlayerData[playerid][pOnDuty] == 0)
						return SendErrorMessage(playerid, "You need to onduty to use this item!");
						
				    for (new i = 0; i < 10; i ++)
					{
				        if (FactionData[factionid][factionWeapons][i])
							format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

						else format(string, sizeof(string), "%sEmpty Slot\n", string);
				    }
				    Dialog_Show(playerid, LockerWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
				}
			}
	    }
	    else
	    {
	        switch (listitem)
	        {
				case 0:
				{
					for (new i = 0; i < sizeof(skins); i ++)
					    skins[i] = (FactionData[factionid][factionSkins][i]) ? (FactionData[factionid][factionSkins][i]) : (19300);

					ShowModelSelectionMenu(playerid, "Choose Skin", MODEL_SELECTION_FACTION_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
				}
				case 1:
				{
				    for (new i = 0; i < 10; i ++)
					{
				        if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) != FACTION_GANG)
							format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

						else if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) == FACTION_GANG)
							format(string, sizeof(string), "%sWeapon %d: %s (%d ammo)\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]), FactionData[factionid][factionAmmo][i]);

						else format(string, sizeof(string), "%sEmpty Slot\n", string);
				    }
				    Dialog_Show(playerid, LockerWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
				}
				case 2:
				{
	                SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has clocked out the skin.", ReturnName(playerid, 0));
					PlayerData[playerid][pFacSkin] = 0;
				}
			}
	    }
	}
	return 1;
}

Dialog:LockerWeapons(playerid, response, listitem, inputtext[])
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1 || !IsNearFactionLocker(playerid))
		return 0;

	if (response)
	{
	    new
	        weaponid = FactionData[factionid][factionWeapons][listitem],
	        ammo = FactionData[factionid][factionAmmo][listitem];

	    if (weaponid)
		{
	        if (PlayerHasWeapon(playerid, weaponid))
	            return SendErrorMessage(playerid, "You have this weapon equipped already.");

	        GiveWeaponToPlayer(playerid, weaponid, ammo);
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));

			if (GetFactionType(playerid) == FACTION_GANG)
		    {
		        FactionData[factionid][factionWeapons][listitem] = 0;
		        FactionData[factionid][factionAmmo][listitem] = 0;

		        Faction_Save(factionid);
			}
		}
		else
		{
		    if (GetFactionType(playerid) == FACTION_GANG)
		    {
		        if ((weaponid = GetWeapon(playerid)) == 0)
		            return SendErrorMessage(playerid, "You are not holding any weapon.");

		        FactionData[factionid][factionWeapons][listitem] = weaponid;
		        FactionData[factionid][factionAmmo][listitem] = GetPlayerAmmo(playerid);

		        Faction_Save(factionid);

                ResetWeapon(playerid, weaponid);
		        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a %s and stores it in the locker.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));
			}
			else
			{
			    SendErrorMessage(playerid, "The selected weapon slot is empty.");
			}
	    }
	}
	else {
	    if (FactionData[factionid][factionType] != FACTION_GANG)
			Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Toggle Duty\nArmored Vest\nLocker Skins\nLocker Weapons", "Select", "Cancel");

		else Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Locker Skins\nLocker Weapons", "Select", "Cancel");
	}
	return 1;
}

Dialog:FactionLocker(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
			    static
			        Float:x,
			        Float:y,
			        Float:z;

				GetPlayerPos(playerid, x, y, z);

				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][0] = x;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][1] = y;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][2] = z;

				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerInt] = GetPlayerInterior(playerid);
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerWorld] = GetPlayerVirtualWorld(playerid);

				Faction_Refresh(PlayerData[playerid][pFactionEdit]);
				Faction_Save(PlayerData[playerid][pFactionEdit]);
				SendServerMessage(playerid, "You have adjusted the locker position of faction ID: %d.", PlayerData[playerid][pFactionEdit]);
			}
			case 1:
	        {
			    static
			        Float:x,
			        Float:y,
			        Float:z;

				GetPlayerPos(playerid, x, y, z);

				FactionData[PlayerData[playerid][pFactionEdit]][factionLeaderLockerPos][0] = x;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLeaderLockerPos][1] = y;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLeaderLockerPos][2] = z;

				Faction_Refresh(PlayerData[playerid][pFactionEdit]);
				Faction_Save(PlayerData[playerid][pFactionEdit]);
				SendServerMessage(playerid, "You have adjusted the leader locker position of faction ID: %d.", PlayerData[playerid][pFactionEdit]);
			}
			case 2:
			{
				static
				    string[512];

				string[0] = 0;

			    for (new i = 0; i < 10; i ++)
				{
			        if (FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i])
						format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i]));

					else format(string, sizeof(string), "%sEmpty Slot\n", string);
			    }
			    Dialog_Show(playerid, FactionWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
			}
		}
	}
	return 1;
}

Dialog:FactionWeapons(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    PlayerData[playerid][pSelectedSlot] = listitem;
	    Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);
	}
	return 1;
}

Dialog:FactionWeapon(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        	Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 1:
	            Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 2:
			{
			    FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = 0;
				FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = 0;

				Faction_Save(PlayerData[playerid][pFactionEdit]);

				dialog_FactionLocker(playerid, 1, 1, "\1");
				SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
	    }
	}
	else {
	    dialog_FactionLocker(playerid, 1, 1, "\1");
	}
	return 1;
}

Dialog:FactionWeaponID(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new weaponid = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (weaponid < 0 || weaponid > 46)
		    return Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Error: The weapon ID can't be below 0 or above 46.\n\nCurrent Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = weaponid;
        Faction_Save(PlayerData[playerid][pFactionEdit]);

		Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);

	    if (weaponid) {
		    SendServerMessage(playerid, "You have set the weapon in slot %d to %s.", PlayerData[playerid][pSelectedSlot] + 1, ReturnWeaponName(weaponid));
		}
		else {
		    SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
		}
	}
	return 1;
}

Dialog:FactionWeaponAmmo(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new ammo = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (ammo < 1 || ammo > 15000)
		    return Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Error: The ammo can't be below 1 or above 15,000.\n\nCurrent Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = ammo;
        Faction_Save(PlayerData[playerid][pFactionEdit]);

		Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);
		SendServerMessage(playerid, "You have set the ammunition in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, ammo);
	}
	return 1;
}

Dialog:FactionSkin(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    static
	        skins[299];

		switch (listitem)
		{
		    case 0:
		        Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-299):", "Add", "Cancel");

			case 1:
			{
			    for (new i = 0; i < sizeof(skins); i ++)
			        skins[i] = i + 1;

				ShowModelSelectionMenu(playerid, "Add Skin", MODEL_SELECTION_ADD_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
			}
			case 2:
			{
			    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = 0;

			    Faction_Save(PlayerData[playerid][pFactionEdit]);
			    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
		}
	}
	return 1;
}

Dialog:FactionModel(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new skin = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-299):", "Add", "Cancel");

		if (skin < 0 || skin > 299)
		    return Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Error: The skin ID can't be below 0 or above 299.\n\nPlease enter the model ID of the skin below (0-299):", "Add", "Cancel");

        FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = skin;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		if (skin) {
		    SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, skin);
		}
		else {
		    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
		}
	}
	return 1;
}

Dialog:Crates(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (PlayerData[playerid][pCarryCrate] != -1)
	        return SendErrorMessage(playerid, "You are already carrying a crate.");

	    new id = strfind(inputtext, "#");

	    if (id != -1) {
	        id = strval(inputtext[id + 1]);

	        CrateData[id][crateVehicle] = INVALID_VEHICLE_ID;
	        PlayerData[playerid][pCarryCrate] = id;

            SetPlayerAttachedObject(playerid, 4, 964, 1, -0.157020, 0.413313, 0.000000, 0.000000, 88.000000, 180.000000, 0.500000, 0.500000, 0.500000);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a crate out of the vehicle.", ReturnName(playerid, 0));
			SendServerMessage(playerid, "You have taken a %s crate out of the vehicle.", Crate_GetType(CrateData[id][crateType]));
		}
	}
	return 1;
}

Dialog:AddVehicleModel(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
	        if (isnull(inputtext))
	            return Dialog_Show(playerid, AddVehicleModel, DIALOG_STYLE_INPUT, "Add Vehicle", "Please enter the name or the ID of the vehicle model:", "Add", "Cancel");

			new model = GetVehicleModelByName(inputtext);

			if (!model)
			    return Dialog_Show(playerid, AddVehicleModel, DIALOG_STYLE_INPUT, "Add Vehicle", "Error: Invalid model specified.\n\nPlease enter the name or the ID of the vehicle model:", "Add", "Cancel");

        	for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
			{
				if (DealershipCars[id][i][vehModel] == model)
	            	return Dialog_Show(playerid, AddVehicleModel, DIALOG_STYLE_INPUT, "Add Vehicle", "Error: This model is already sold at this dealership.\n\nPlease enter the name or the ID of the vehicle model:", "Add", "Cancel");
			}
			PlayerData[playerid][pDealerCar] = model;
			Dialog_Show(playerid, DealerCarPrice, DIALOG_STYLE_INPUT, "Enter Price", "Please enter a price for '%s':", "Submit", "Cancel", ReturnVehicleModelName(PlayerData[playerid][pDealerCar]));
	    }
	}
	return 1;
}

Dialog:AddVehicle(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
			if (!listitem)
			{
				Dialog_Show(playerid, AddVehicleModel, DIALOG_STYLE_INPUT, "Add Vehicle", "Please enter the name or the ID of the vehicle model:", "Add", "Cancel");
			}
		    else
			{
				static
					cars[212];

				for (new i = 0; i < sizeof(cars); i ++)
  					cars[i] = i + 400;

				ShowModelSelectionMenu(playerid, "Add Vehicle", MODEL_SELECTION_DEALER_ADD, cars, sizeof(cars), -16.0, 0.0, -55.0);
			}
		}
	}
	return 1;
}

Dialog:EnterNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        name[32],
			string[128];

		strunpack(name, PlayerData[playerid][pEditingItem]);

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, EnterNumber, DIALOG_STYLE_INPUT, "Contact Number", "Contact Name: %s\n\nPlease enter the phone number for this contact:", "Submit", "Back", name);

		for (new i = 0; i != MAX_CONTACTS; i ++)
		{
			if (!ContactData[playerid][i][contactExists])
			{
            	ContactData[playerid][i][contactExists] = true;
            	ContactData[playerid][i][contactNumber] = strval(inputtext);

				format(ContactData[playerid][i][contactName], 32, name);

				format(string, sizeof(string), "INSERT INTO `contacts` (`ID`, `contactName`, `contactNumber`) VALUES('%d', '%s', '%d')", PlayerData[playerid][pID], SQL_ReturnEscaped(name), ContactData[playerid][i][contactNumber]);
				mysql_tquery(g_iHandle, string, "OnContactAdd", "dd", playerid, i);

				SendServerMessage(playerid, "You have added \"%s\" to your contacts.", name);
                return 1;
			}
	    }
	    SendErrorMessage(playerid, "There is no room left for anymore contacts.");
	}
	else {
		ShowContacts(playerid);
	}
	return 1;
}

Dialog:NewContact(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Error: Please enter a contact name.\n\nPlease enter the name of the contact below:", "Submit", "Back");

	    if (strlen(inputtext) > 32)
	        return Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Error: The contact name can't exceed 32 characters.\n\nPlease enter the name of the contact below:", "Submit", "Back");

		strpack(PlayerData[playerid][pEditingItem], inputtext, 32);

	    Dialog_Show(playerid, EnterNumber, DIALOG_STYLE_INPUT, "Contact Number", "Contact Name: %s\n\nPlease enter the phone number for this contact:", "Submit", "Back", inputtext);
	}
	else {
		ShowContacts(playerid);
	}
	return 1;
}

Dialog:ContactInfo(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			id = PlayerData[playerid][pContact],
			string[72];

		switch (listitem)
		{
		    case 0:
		    {
		        format(string, 16, "%d", ContactData[playerid][id][contactNumber]);
				cmd_call(playerid, string);
		    }
		    case 1:
		    {
		        format(string, sizeof(string), "DELETE FROM `contacts` WHERE `ID` = '%d' AND `contactID` = '%d'", PlayerData[playerid][pID], ContactData[playerid][id][contactID]);
		        mysql_tquery(g_iHandle, string);

		        SendServerMessage(playerid, "You have deleted \"%s\" from your contacts.", ContactData[playerid][id][contactName]);

		        ContactData[playerid][id][contactExists] = false;
		        ContactData[playerid][id][contactNumber] = 0;
		        ContactData[playerid][id][contactID] = 0;

		        ShowContacts(playerid);
		    }
		}
	}
	else {
	    ShowContacts(playerid);
	}
	return 1;
}

Dialog:Contacts(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!listitem) {
	        Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Please enter the name of the contact below:", "Submit", "Back");
	    }
	    else {
		    PlayerData[playerid][pContact] = ListedContacts[playerid][listitem - 1];

	        Dialog_Show(playerid, ContactInfo, DIALOG_STYLE_LIST, ContactData[playerid][PlayerData[playerid][pContact]][contactName], "Call Contact\nDelete Contact", "Select", "Back");
	    }
		for (new i = 0; i != MAX_CONTACTS; i ++) 
		{
			ListedContacts[playerid][i] = -1;
		}
	}
	else
	{
		Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
	}
	return 1;
}

Dialog:DialNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
	        string[16];

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, DialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");

        format(string, 16, "%d", strval(inputtext));
		cmd_call(playerid, string);
	}
	else
	{
		Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
	}
	return 1;
}

Dialog:SendText(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new number = strval(inputtext);

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");

        if (GetNumberOwner(number) == INVALID_PLAYER_ID)
            return Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Error: That number is not online right now.\n\nPlease enter the number that you wish to send a text message to:", "Dial", "Back");

		PlayerData[playerid][pContact] = GetNumberOwner(number);
		Dialog_Show(playerid, TextMessage, DIALOG_STYLE_INPUT, "Text Message", "Please enter the message to send to %s:", "Send", "Back", ReturnName(PlayerData[playerid][pContact], 0));
	}
	else
	{
		Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
	}
	return 1;
}

Dialog:TextMessage(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if (isnull(inputtext))
			return Dialog_Show(playerid, TextMessage, DIALOG_STYLE_INPUT, "Text Message", "Error: Please enter a message to send.\n\nPlease enter the message to send to %s:", "Send", "Back", ReturnName(PlayerData[playerid][pContact], 0));

		new targetid = PlayerData[playerid][pContact];

		if (!IsPlayerConnected(targetid) || !PlayerData[targetid][pPhone])
		    return SendErrorMessage(playerid, "The specified phone number went offline.");

		GiveMoney(playerid, -1);
		SendInfoMessage(playerid, "You've been charged RM1 to send a text.");

		SendClientMessageEx(targetid, COLOR_YELLOW, "[TEXT]: %s - %s (%d)", inputtext, ReturnName(playerid, 0), PlayerData[playerid][pPhone]);
		SendClientMessageEx(playerid, COLOR_YELLOW, "[TEXT]: %s - %s (%d)", inputtext, ReturnName(playerid, 0), PlayerData[playerid][pPhone]);

        PlayerPlaySoundEx(targetid, 21001);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out their phone and sends a text.", ReturnName(playerid, 0));
	}
	else {
        Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Submit", "Back");
	}
	return 1;
}

Dialog:PhoneBank(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new string[1124];

				format(string,sizeof(string),"Total Balance: %s | Savings: %s", FormatNumber(PlayerData[playerid][pBankMoney]), FormatNumber(PlayerData[playerid][pSavings]));

				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Bank Balance", string, "Back", "");
			}
			case 1:
			{
				Dialog_Show(playerid, PhoneTransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
		}
	}
	else
	{
		Dialog_Show(playerid, MainPhone, DIALOG_STYLE_LIST, "Cellphone", "Contact\nCall\nSMS\neTicket\nBank", "Select", "Close");
	}
	return 1;
}

Dialog:ListedFurniture(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = House_Inside(playerid);

	    if (id != -1 && House_IsOwner(playerid, id))
	    {
	        PlayerData[playerid][pEditFurniture] = ListedFurniture[playerid][listitem];

			Dialog_Show(playerid, FurnitureList, DIALOG_STYLE_LIST, FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName], "Edit Position\nPickup Furniture\nDestroy Furniture", "Select", "Cancel");
	    }
	}
	for (new i = 0; i != MAX_FURNITURE; i ++) {
	    ListedFurniture[playerid][i] = -1;
	}
	return 1;
}

Dialog:FurnitureList(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        new id = House_Inside(playerid);

	    if (id != -1 && House_IsOwner(playerid, id))
	    {
	   		switch (listitem)
		    {
		        case 0:
				{
					EditDynamicObject(playerid, FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureObject]);
					SendServerMessage(playerid, "You are now editing the position of item \"%s\".", FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName]);
				}
				case 1:
				{
				    new item = Inventory_Add(playerid, FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName], FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureModel]);

				    if (item == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

				    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up \"%s\".", ReturnName(playerid, 0), FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName]);
				    SendServerMessage(playerid, "You have picked up your \"%s\". The item was added to your inventory.", FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName]);

				    Furniture_Delete(PlayerData[playerid][pEditFurniture]);
					CancelEdit(playerid);

				    PlayerData[playerid][pEditFurniture] = -1;
				}
				case 2:
				{
				    Furniture_Delete(PlayerData[playerid][pEditFurniture]);
				    SendServerMessage(playerid, "You have destroyed furniture \"%s\".", FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName]);

				    CancelEdit(playerid);
				    PlayerData[playerid][pEditFurniture] = -1;
				}
			}
		}
		else {
			PlayerData[playerid][pEditFurniture] = -1;
		}
	}
	else {
	    PlayerData[playerid][pEditFurniture] = -1;
	}
	return 1;
}

Dialog:Trunk(playerid, response, listitem, inputtext[])
{
    new carid = Car_Nearest(playerid);

	if (CarData[carid][carImpounded] != 0)
    	return SendErrorMessage(playerid, "This vehicle is impounded and you can't use it.");

	if (carid != -1 && !CarData[carid][carLocked])
 	{
		if (response)
		{
			if (!CarData[carid][carWeapons][listitem])
			{
			    if (!GetWeapon(playerid))
			        return SendErrorMessage(playerid, "You aren't holding any weapon.");

       			if (GetWeapon(playerid) == 23 && PlayerData[playerid][pTazer])
	    			return SendErrorMessage(playerid, "You can't store a tazer into your trunk.");

                if (GetWeapon(playerid) == 25 && PlayerData[playerid][pBeanBag])
	    			return SendErrorMessage(playerid, "You can't store a beanbag shotgun into your trunk.");

				if (!Car_IsOwner(playerid, carid) && GetFactionType(playerid) == FACTION_POLICE)
        			return SendErrorMessage(playerid, "You can't store weapons since you're a police officer.");

	   			CarData[carid][carWeapons][listitem] = GetWeapon(playerid);
	            CarData[carid][carAmmo][listitem] = GetPlayerAmmo(playerid);

	            ResetWeapon(playerid, CarData[carid][carWeapons][listitem]);
	            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s stored a %s into the trunk.", ReturnName(playerid, 0), ReturnWeaponName(CarData[carid][carWeapons][listitem]));

	            Car_Save(carid);
				Car_WeaponStorage(playerid, carid);
			}
			else
			{
			    GiveWeaponToPlayer(playerid, CarData[carid][carWeapons][listitem], CarData[carid][carAmmo][listitem]);
	            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes a %s from the trunk.", ReturnName(playerid, 0), ReturnWeaponName(CarData[carid][carWeapons][listitem]));

	            CarData[carid][carWeapons][listitem] = 0;
	            CarData[carid][carAmmo][listitem] = 0;

	            Car_Save(carid);
	            Car_WeaponStorage(playerid, carid);
			}
	    }
		else {
		    Car_ShowTrunk(playerid, carid);
		}
	}
	return 1;
}

Dialog:ConfirmCarBuy(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			bizid = Business_Inside(playerid),
			carid = PlayerData[playerid][pDealerCar],
			price = DealershipCars[bizid][carid][vehPrice];

		if (bizid != -1 && BusinessData[bizid][bizExists] && BusinessData[bizid][bizType] == 5)
		{
			if (GetMoney(playerid) < price)
			    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

			if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS)
			    return SendErrorMessage(playerid, "You already have %d vehicles (server limit).", MAX_OWNABLE_CARS);

			new id = Car_Create(PlayerData[playerid][pID], DealershipCars[bizid][carid][vehModel], BusinessData[bizid][bizSpawn][0], BusinessData[bizid][bizSpawn][1], BusinessData[bizid][bizSpawn][2], BusinessData[bizid][bizSpawn][3], 1, 1);

			if (id != -1)
			{
			    BusinessData[bizid][bizVault] += price;
			    Business_Save(bizid);

				SendServerMessage(playerid, "You have bought a %s for %s!", ReturnVehicleModelName(DealershipCars[bizid][carid][vehModel]), FormatNumber(price));
				GiveMoney(playerid, -price);

				Log_Write("logs/car_log.txt", "[%s] %s has purchased a %s for %s.", ReturnDate(), ReturnName(playerid, 0), ReturnVehicleModelName(DealershipCars[bizid][carid][vehModel]), FormatNumber(price));
			}
		}
	}
	return 1;
}

Dialog:DealerCarPrice(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
		    if (isnull(inputtext) || strval(inputtext) < 1)
		        return Dialog_Show(playerid, DealerCarPrice, DIALOG_STYLE_INPUT, "Enter Price", "Please enter a price for '%s':", "Submit", "Cancel", ReturnVehicleModelName(PlayerData[playerid][pDealerCar]));

		    Business_AddVehicle(id, PlayerData[playerid][pDealerCar], strval(inputtext));
	        Business_EditCars(playerid, id);

		    SendServerMessage(playerid, "You have added a '%s' to the dealership.", ReturnVehicleModelName(PlayerData[playerid][pDealerCar]));
		    return 1;
		}
	}
	return 1;
}

Dialog:CarPrice(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
		    if (isnull(inputtext) || strval(inputtext) < 1)
		        return Dialog_Show(playerid, CarPrice, DIALOG_STYLE_INPUT, "Set Price", "The current price for '%s' is %s.\n\nPlease enter the new price for this vehicle model below:", "Submit", "Cancel", ReturnVehicleModelName(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehModel]), FormatNumber(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehPrice]));

			new
			    string[128];

			DealershipCars[id][PlayerData[playerid][pDealerCar]][vehPrice] = strval(inputtext);

			format(string, sizeof(string), "UPDATE `dealervehicles` SET `vehPrice` = '%d' WHERE `ID` = '%d' AND `vehID` = '%d'", strval(inputtext), BusinessData[id][bizID], DealershipCars[id][PlayerData[playerid][pDealerCar]][vehID]);
			mysql_tquery(g_iHandle, string);

			SendServerMessage(playerid, "You have set the price of '%s' to %s.", ReturnVehicleModelName(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehModel]), FormatNumber(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehPrice]));
			Business_EditCars(playerid, id);
		}
		return 1;
	}
	return 1;
}

Dialog:CarOptions(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
		    if (listitem == 0)
		    {
		        Dialog_Show(playerid, CarPrice, DIALOG_STYLE_INPUT, "Set Price", "The current price for '%s' is %s.\n\nPlease enter the new price for this vehicle model below:", "Submit", "Cancel", ReturnVehicleModelName(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehModel]), FormatNumber(DealershipCars[id][PlayerData[playerid][pDealerCar]][vehPrice]));
		    }
		    else if (listitem == 1)
		    {
			    new model = DealershipCars[id][PlayerData[playerid][pDealerCar]][vehModel];
			    Business_RemoveVehicle(id, model); 

				SendServerMessage(playerid, "You have removed the '%s' from the dealership.", ReturnVehicleModelName(model));
				Business_EditCars(playerid, id);
			}
		}
	}
	return 1;
}

Dialog:BankAccount(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_Show(playerid, Withdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
	        case 1:
	        {
				Dialog_Show(playerid, Deposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
			case 2:
			{
			    Dialog_Show(playerid, Transfer, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
			}
	    }
	}
	return 1;
}

Dialog:Transfer(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        userid;

		if (sscanf(inputtext, "u", userid))
		    return Dialog_Show(playerid, Transfer, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, Transfer, DIALOG_STYLE_INPUT, "Make a transfer", "Error: Invalid player specified.\n\nYour bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == playerid)
		    return Dialog_Show(playerid, Transfer, DIALOG_STYLE_INPUT, "Make a transfer", "Error: You can't transfer funds to yourself.\n\nYour bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pTransfer] = userid;
		Dialog_Show(playerid, TransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));
	}
    else {
	    Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Back");
	}
	return 1;
}

Dialog:TransferCash(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, TransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney])
			return Dialog_Show(playerid, TransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Error: Insufficient funds!\n\nYour bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));

		if (!strcmp(PlayerData[playerid][pIP], PlayerData[PlayerData[playerid][pTransfer]][pIP])) {
		    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s (%s) has transferred %s to %s (%s).", ReturnName(playerid, 0), PlayerData[playerid][pIP], FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer], 0), PlayerData[playerid][pIP]);
		}
		PlayerData[playerid][pBankMoney] -= amount;
		PlayerData[PlayerData[playerid][pTransfer]][pBankMoney] += amount;

	    SendServerMessage(playerid, "You have transferred %s to %s's bank account.", FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer], 0));
	    SendServerMessage(PlayerData[playerid][pTransfer], "%s has transferred %s into your bank account.", ReturnName(playerid, 0), FormatNumber(amount));

        Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Back");
        Log_Write("logs/transfer_log.txt", "[%s] %s (%s) has transferred %s to %s (%s).", ReturnDate(), ReturnName(playerid), PlayerData[playerid][pIP], FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]), PlayerData[PlayerData[playerid][pTransfer]][pIP]);
	}
	else {
	    Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Back");
	}
	return 1;
}

Dialog:PhoneTransfer(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        userid;

		if (sscanf(inputtext, "u", userid))
		    return Dialog_Show(playerid, PhoneTransfer, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, PhoneTransfer, DIALOG_STYLE_INPUT, "Make a transfer", "Error: Invalid player specified.\n\nYour bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (userid == playerid)
		    return Dialog_Show(playerid, PhoneTransfer, DIALOG_STYLE_INPUT, "Make a transfer", "Error: You can't transfer funds to yourself.\n\nYour bank account's balance: %s\n\nPlease enter the name or ID of the player below:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pTransfer] = userid;
		Dialog_Show(playerid, PhoneTransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));
	}
	return 1;
}

Dialog:PhoneTransferCash(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, PhoneTransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Your bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney])
			return Dialog_Show(playerid, PhoneTransferCash, DIALOG_STYLE_INPUT, "Make a transfer", "Error: Insufficient funds!\n\nYour bank account's balance: %s\n\nPlease enter the amount of money to transfer to %s:", "Continue", "Back", FormatNumber(PlayerData[playerid][pBankMoney]), ReturnName(PlayerData[playerid][pTransfer], 0));

		if (!strcmp(PlayerData[playerid][pIP], PlayerData[PlayerData[playerid][pTransfer]][pIP])) {
		    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s (%s) has transferred %s to %s (%s).", ReturnName(playerid, 0), PlayerData[playerid][pIP], FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer], 0), PlayerData[playerid][pIP]);
		}
		PlayerData[playerid][pBankMoney] -= amount;
		PlayerData[PlayerData[playerid][pTransfer]][pBankMoney] += amount;

	    SendServerMessage(playerid, "You have transferred %s to %s's bank account.", FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer], 0));
	    SendServerMessage(PlayerData[playerid][pTransfer], "%s has transferred %s into your bank account.", ReturnName(playerid, 0), FormatNumber(amount));

        Log_Write("logs/transfer_log.txt", "[%s] %s (%s) has transferred %s to %s (%s).", ReturnDate(), ReturnName(playerid), PlayerData[playerid][pIP], FormatNumber(amount), ReturnName(PlayerData[playerid][pTransfer]), PlayerData[PlayerData[playerid][pTransfer]][pIP]);
	}
	return 1;
}

Dialog:Savings(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_Show(playerid, SavingsWithdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pSavings]));
			}
	        case 1:
	        {
				Dialog_Show(playerid, SavingsDeposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pSavings]));
			}
	    }
	}
	return 1;
}

Dialog:Withdraw(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, Withdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (amount < 1 || amount > PlayerData[playerid][pBankMoney])
			return Dialog_Show(playerid, Withdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Error: Insufficient funds!\n\nYour bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pBankMoney] -= amount;
	    GiveMoney(playerid, amount);

	    SendServerMessage(playerid, "You have withdrawn %s from your bank account.", FormatNumber(amount));
        Dialog_Show(playerid, Withdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
	}
	else {
	    Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Back");
	}
	return 1;
}

Dialog:Deposit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, Deposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		if (amount < 1 || amount > GetMoney(playerid))
			return Dialog_Show(playerid, Deposit, DIALOG_STYLE_INPUT, "Deposit funds", "Error: You don't have that much.\n\nYour bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));

		PlayerData[playerid][pBankMoney] += amount;
	    GiveMoney(playerid, -amount);

	    SendServerMessage(playerid, "You have deposited %s into your bank account.", FormatNumber(amount));
        Dialog_Show(playerid, Deposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pBankMoney]));
	}
	else {
	    Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Back");
	}
	return 1;
}

Dialog:SavingsWithdraw(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, SavingsWithdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pSavings]));

		if (amount < 1 || amount > PlayerData[playerid][pSavings])
			return Dialog_Show(playerid, SavingsWithdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Error: Insufficient funds!\n\nYour savings account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pSavings]));

		PlayerData[playerid][pSavings] -= amount;
	    GiveMoney(playerid, amount);

	    SendServerMessage(playerid, "You have withdrawn %s from your savings account.", FormatNumber(amount));
        Dialog_Show(playerid, SavingsWithdraw, DIALOG_STYLE_INPUT, "Withdraw funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(PlayerData[playerid][pSavings]));
	}
	else {
	    Dialog_Show(playerid, Savings, DIALOG_STYLE_LIST, "Savings Account", "Withdraw funds\nDeposit funds", "Select", "Back");
	}
	return 1;
}

Dialog:SavingsDeposit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, SavingsDeposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pSavings]));

		if (amount < 1 || amount > GetMoney(playerid))
			return Dialog_Show(playerid, SavingsDeposit, DIALOG_STYLE_INPUT, "Deposit funds", "Error: You don't have that much.\n\nYour savings account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pSavings]));

		PlayerData[playerid][pSavings] += amount;
	    GiveMoney(playerid, -amount);

	    SendServerMessage(playerid, "You have deposited %s into your savings account.", FormatNumber(amount));
        Dialog_Show(playerid, SavingsDeposit, DIALOG_STYLE_INPUT, "Deposit funds", "Your savings account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(PlayerData[playerid][pSavings]));
	}
	else {
	    Dialog_Show(playerid, Savings, DIALOG_STYLE_LIST, "Savings Account", "Withdraw funds\nDeposit funds", "Select", "Back");
	}
	return 1;
}
Dialog:Salary(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
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
					SendErrorMessage(playerid, "You do not have any salary.");
				}
			}
			case 1:
			{
				new query[512];
				mysql_format(g_iHandle, query, sizeof(query), "SELECT * FROM salary WHERE Owner='%d' ORDER BY id ASC LIMIT 30", PlayerData[playerid][pID]);
				mysql_query(g_iHandle, query);
				new rows = cache_num_rows();
				if(rows) 
				{
					new money, totalsal;

					for(new i; i < rows; ++i)
					{
						money = cache_get_field_int(i, "Money");
						totalsal += money;
					}

					SendServerMessage(playerid, "The total salary that insert into your bank account is "LG_E"%s"WHITE_E".", FormatNumber(totalsal));
					PlayerData[playerid][pBankMoney] += totalsal;
					mysql_format(g_iHandle, query, sizeof(query), "DELETE FROM salary WHERE Owner='%d'", PlayerData[playerid][pID]);
					mysql_query(g_iHandle, query);
				}
				else
				{
					SendErrorMessage(playerid, "You do not have any salary!");
				}
			}
		}
	}
	return 1;
}

Dialog:TeleportInterior(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    SetPlayerInterior(playerid, g_arrInteriorData[listitem][e_InteriorID]);
	    SetPlayerPos(playerid, g_arrInteriorData[listitem][e_InteriorX], g_arrInteriorData[listitem][e_InteriorY], g_arrInteriorData[listitem][e_InteriorZ]);
	}
	return 1;
}

Dialog:LeaveTest(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    CancelDrivingTest(playerid);

	    SendErrorMessage(playerid, "You have failed the driving test since you quit.");
	}
	else
	{
	    PutPlayerInVehicle(playerid, PlayerData[playerid][pTestCar], 0);
	}
	return 1;
}

Dialog:Inventory(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			itemid = PlayerData[playerid][pInventoryItem],
			string[64];

	    strunpack(string, InventoryData[playerid][itemid][invItem]);

	    switch (listitem)
	    {
	        case 0:
	        {
	            CallLocalFunction("OnPlayerUseItem", "dds", playerid, itemid, string);
	        }
	        case 1:
	        {
				PlayerData[playerid][pInventoryItem] = itemid;
				Dialog_Show(playerid, GiveItem, DIALOG_STYLE_INPUT, "Give Item", "Please enter the name or the ID of the player:", "Submit", "Cancel");
	        }
	        case 2:
	        {
	            new id = -1;

	            if (IsPlayerInAnyVehicle(playerid) || !IsPlayerSpawned(playerid))
	                return SendErrorMessage(playerid, "You can't drop items right now.");

				else if (!strcmp(string, "Backpack"))
					return cmd_dropbackpack(playerid, "\1");

				else if ((id = Garbage_Nearest(playerid)) != -1)
				{
				    if (GarbageData[id][garbageCapacity] >= 20)
				        return SendErrorMessage(playerid, "This garbage bin is full of trash.");

                    GarbageData[id][garbageCapacity]++;
                    Garbage_Save(id);

					ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
					
					Inventory_Remove(playerid, string);
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s throws a \"%s\" into the garbage bin.", ReturnName(playerid, 0), string);

                    format(string, sizeof(string), "[GARBAGE]\n{FFFFFF}Trash Capacity: "YELLOW_E"%d/20", GarbageData[id][garbageCapacity]);
                    UpdateDynamic3DTextLabelText(GarbageData[id][garbageText3D], COLOR_DARKBLUE, string);
				}
				else if (InventoryData[playerid][itemid][invQuantity] == 1)
					DropPlayerItem(playerid, itemid);

				else
					Dialog_Show(playerid, DropItem, DIALOG_STYLE_INPUT, "Drop Item", "Item: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", "Drop", "Cancel", string, InventoryData[playerid][itemid][invQuantity]);
	        }
	    }
	}
	return 1;
}

Dialog:DropItem(playerid, response, listitem, inputtext[])
{
	new
	    itemid = PlayerData[playerid][pInventoryItem],
	    string[32];

	strunpack(string, InventoryData[playerid][itemid][invItem]);

	if (response)
	{
	    if (isnull(inputtext))
	        return Dialog_Show(playerid, DropItem, DIALOG_STYLE_INPUT, "Drop Item", "Item: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", "Drop", "Cancel", string, InventoryData[playerid][itemid][invQuantity]);

		if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
		    return Dialog_Show(playerid, DropItem, DIALOG_STYLE_INPUT, "Drop Item", "Error: Insufficient amount specified.\n\nItem: %s - Quantity: %d\n\nPlease specify how much of this item you wish to drop:", "Drop", "Cancel", string, InventoryData[playerid][itemid][invQuantity]);

		DropPlayerItem(playerid, itemid, strval(inputtext));
	}
	return 1;
}

Dialog:BusinessBuy(playerid, response, listitem, inputtext[])
{
	static
	    bizid = -1,
		price;

    if ((bizid = Business_Inside(playerid)) != -1 && response)
    {
        price = BusinessData[bizid][bizPrices][listitem];

        if (GetMoney(playerid) < price)
            return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

		if (BusinessData[bizid][bizProducts] < 1)
		    return SendErrorMessage(playerid, "This business is out of stock.");

		if (BusinessData[bizid][bizType] == 1 || BusinessData[bizid][bizType] == 6)
		{
		    switch (listitem)
		    {
		        case 0:
		        {
		            if (Inventory_Count(playerid, "Frozen Pizza") >= 3)
		                return SendErrorMessage(playerid, "You have 3 frozen pizzas, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Frozen Pizza", 2814);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a box of frozen pizza.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
				}
				case 1:
		        {
		            if (PlayerHasWeapon(playerid, 5))
		                return SendErrorMessage(playerid, "You have this item already.");

					GiveWeaponToPlayer(playerid, 5, 1);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a baseball bat.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 2:
		        {
		            if (Inventory_Count(playerid, "Frozen Burger") >= 5)
		                return SendErrorMessage(playerid, "You have 5 frozen burgers, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Frozen Burger", 2768);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a frozen burger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 3:
			    {
			        if (Inventory_HasItem(playerid, "Backpack"))
		                return SendErrorMessage(playerid, "You have this item already.");

					new id = Inventory_Add(playerid, "Backpack", 3026);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					if (Backpack_Create(playerid) == -1)
					    return SendErrorMessage(playerid, "The server has reached the internal limit for backpacks.");

					SetAccessories(playerid);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a backpack.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 4:
		        {
		            if (Inventory_Count(playerid, "Water Bottle") >= 10)
		                return SendErrorMessage(playerid, "You have 10 bottles of water, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Water Bottle", 2958);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a bottle of water.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 5:
		        {
              		if (Inventory_Count(playerid, "Soda") >= 5)
		                return SendErrorMessage(playerid, "You have 5 bottles of soda, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Soda", 1543);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a bottle of soda.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 6:
				{
				    if (PlayerData[playerid][pLottery])
				        return SendErrorMessage(playerid, "You have a lottery ticket already.");

					Dialog_Show(playerid, LotteryNumber, DIALOG_STYLE_INPUT, "Lottery Number", "Please enter your desired lottery number below (from 1-60):", "Submit", "Cancel");
				}
				case 7:
		        {
		        	new id = Inventory_Add(playerid, "Lighter", 19998);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a lighter.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 8:
		        {
		            if (Inventory_Count(playerid, "Fuel Can") >= 3)
		                return SendErrorMessage(playerid, "You have 3 cans of fuel, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Fuel Can", 1650);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a can of fuel.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 9:
		        {
		            if (Inventory_HasItem(playerid, "Crowbar"))
		                return SendErrorMessage(playerid, "You have a crowbar already.");

					new id = Inventory_Add(playerid, "Crowbar", 18634);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a crowbar.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 10:
		        {
		            if (Inventory_Count(playerid, "Repair Kit") >= 3)
		                return SendErrorMessage(playerid, "You have 3 repair kits, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Repair Kit", 920);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a repair kit.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 11:
		        {
		            if (Inventory_HasItem(playerid, "Mask"))
		                return SendErrorMessage(playerid, "You have a mask already.");

					if (PlayerData[playerid][pScore] < 5)
					    return SendErrorMessage(playerid, "You must have at least 5 score.");

					new id = Inventory_Add(playerid, "Mask", 19036);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a mask.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			}
		}
		else if (BusinessData[bizid][bizType] == 2)
		{
		    switch (listitem)
	    	{
		        case 0:
		        {
		            if (Inventory_HasItem(playerid, "Cellphone"))
		                return SendErrorMessage(playerid, "You have a cellphone already.");

					new id = Inventory_Add(playerid, "Cellphone", 330);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					PlayerData[playerid][pPhone] = random(90000) + 10000;

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a cellphone.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);

					SendInfoMessage(playerid, "Your new number is %d.", PlayerData[playerid][pPhone]);

					SendServerMessage(playerid, "Your new number is %d.", PlayerData[playerid][pPhone]);
			    }
                case 1:
		        {
					if (Inventory_HasItem(playerid, "GPS System"))
		                return SendErrorMessage(playerid, "You have a GPS system already.");

					new id = Inventory_Add(playerid, "GPS System", 18875);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a GPS System.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 2:
		        {
					if (Inventory_HasItem(playerid, "Portable Radio"))
		                return SendErrorMessage(playerid, "You have this item already.");

					new id = Inventory_Add(playerid, "Portable Radio", 18868);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a portable radio.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
				case 3:
				{
				    if (Inventory_HasItem(playerid, "Boombox"))
		                return SendErrorMessage(playerid, "You have a boombox already.");

					new id = Inventory_Add(playerid, "Boombox", 2226);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a boombox.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
		    }
		}
		else if (BusinessData[bizid][bizType] == 3)
		{
		    switch (listitem)
		    {
		        case 0:
				{
				    PlayerData[playerid][pClothesType] = 1;

					switch (PlayerData[playerid][pGender])
                    {
                        case 1:
                        	ShowModelSelectionMenu(playerid, "Clothes", MODEL_SELECTION_CLOTHES, g_aMaleSkins, sizeof(g_aMaleSkins), -16.0, 0.0, -55.0);

						case 2:
                       		ShowModelSelectionMenu(playerid, "Clothes", MODEL_SELECTION_CLOTHES, g_aFemaleSkins, sizeof(g_aFemaleSkins), -16.0, 0.0, -55.0);
                    }
				}
		        case 1:
				{
				    PlayerData[playerid][pClothesType] = 2;
					ShowModelSelectionMenu(playerid, "Glasses", MODEL_SELECTION_CLOTHES, {19006, 19007, 19008, 19009, 19010, 19011, 19012, 19013, 19014, 19015, 19016, 19017, 19018, 19019, 19020, 19021, 19022, 19023, 19024, 19025, 19026, 19027, 19028, 19029, 19030, 19031, 19032, 19033, 19034, 19035}, 30, 0.0, 0.0, 90.0);
				}
			    case 2:
				{
				    PlayerData[playerid][pClothesType] = 3;
					ShowModelSelectionMenu(playerid, "Hats", MODEL_SELECTION_CLOTHES, {18926, 18927, 18928, 18929, 18930, 18931, 18932, 18933, 18934, 18935, 18944, 18945, 18946, 18947, 18948, 18949, 18950, 18951}, 18, -20.0, -90.0, 0.0);
				}
				case 3:
				{
				    PlayerData[playerid][pClothesType] = 4;
					ShowModelSelectionMenu(playerid, "Bandanas", MODEL_SELECTION_CLOTHES, {18911, 18912, 18913, 18914, 18915, 18916, 18917, 18918, 18919, 18920}, 10, 80.0, -173.0, 0.0);
				}
				case 4:
				{
				    if (Inventory_HasItem(playerid, "Helmet"))
		                return SendErrorMessage(playerid, "You have a helmet already.");

					new id = Inventory_Add(playerid, "Helmet", 18977);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a helmet.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
		    }
		}
		else if (BusinessData[bizid][bizType] == 4)
		{
			switch (listitem)
			{
			    case 0:
			    {
			        if (PlayerData[playerid][pThirst] > 90)
			            return SendErrorMessage(playerid, "You are not thirsty right now.");

					PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 10 > 100) ? (100) : (PlayerData[playerid][pThirst] + 10);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some water.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 1:
			    {
			        if (PlayerData[playerid][pThirst] > 90)
			            return SendErrorMessage(playerid, "You are not thirsty right now.");

					PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 20 > 100) ? (100) : (PlayerData[playerid][pThirst] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some soda.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 2:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 20 > 100) ? (100) : (PlayerData[playerid][pHunger] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some french fries.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 3:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 25 > 100) ? (100) : (PlayerData[playerid][pHunger] + 25);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a cheeseburger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 4:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 30 > 100) ? (100) : (PlayerData[playerid][pHunger] + 30);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a chicken burger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 5:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 25 > 100) ? (100) : (PlayerData[playerid][pHunger] + 25);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some chicken nuggets.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			    case 6:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 20 > 100) ? (100) : (PlayerData[playerid][pHunger] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a salad.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += price;

					Business_Save(bizid);
			    }
			}
		}
		else if (BusinessData[bizid][bizType] == 7)
		{
		    new
				items[50] = {-1, ...},
				count;

		    for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (g_aFurnitureData[i][e_FurnitureType] == listitem + 1) {
				items[count++] = g_aFurnitureData[i][e_FurnitureModel];
		    }
		    PlayerData[playerid][pFurnitureType] = listitem;

			if (listitem == 3) {
				ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count, -12.0, 0.0, 0.0);
			}
			else {
			    ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count);
			}
		}
	}
    return 1;
}

Dialog:LotteryNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new bizid = Business_Inside(playerid);

	    if (bizid != -1)
	    {
	        if (isnull(inputtext) || (strval(inputtext) < 1 || strval(inputtext) > 60)) {
	            return Dialog_Show(playerid, LotteryNumber, DIALOG_STYLE_INPUT, "Lottery Number", "Please enter your desired lottery number below (from 1-60):", "Submit", "Cancel");
			}
	        PlayerData[playerid][pLottery] = strval(inputtext);
	        PlayerData[playerid][pLotteryB] = 1;

		    GiveMoney(playerid, -BusinessData[bizid][bizPrices][6]);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a lottery ticket.", ReturnName(playerid, 0), FormatNumber(BusinessData[bizid][bizPrices][6]));

			BusinessData[bizid][bizProducts]--;
			BusinessData[bizid][bizVault] += BusinessData[bizid][bizPrices][6];

			Business_Save(bizid);
		}
	}
	return 1;
}

Dialog:EditProduct(playerid, response, listitem, inputtext[])
{
	static
	    bizid = -1;

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid))
	{
		if (response)
		{
		    static
		        item[24];

		    strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
		    strpack(PlayerData[playerid][pEditingItem], item, 32 char);

            PlayerData[playerid][pProductModify] = listitem;
      		Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\":", "Modify", "Back", item);
		}
	}
	return 1;
}

Dialog:PriceSet(playerid, response, listitem, inputtext[])
{
    static
	    bizid = -1,
		item[32];

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid))
	{
		if (response)
		{
		    strunpack(item, PlayerData[playerid][pEditingItem]);

			if (isnull(inputtext))
			    return Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\":", "Modify", "Back", item);

			if (strval(inputtext) < 1 || strval(inputtext) > 2000)
			    return Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\" (RM1 to RM2,000):", "Modify", "Back", item);

			BusinessData[bizid][bizPrices][PlayerData[playerid][pProductModify]] = strval(inputtext);
			Business_Save(bizid);

			SendServerMessage(playerid, "You have adjusted the price of \"%s\" to: %s!", item, FormatNumber(strval(inputtext)));
			Business_ProductMenu(playerid, bizid);
		}
		else
		{
		    Business_ProductMenu(playerid, bizid);
		}
	}
	return 1;
}

Dialog:CarDeposit(playerid, response, listitem, inputtext[])
{
	static
	    carid = -1,
	    string[32];

    if ((carid = Car_Nearest(playerid)) != -1 && !CarData[carid][carLocked])
	{
	    strunpack(string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invItem]);

		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity])
			    return Dialog_Show(playerid, CarDeposit, DIALOG_STYLE_INPUT, "Car Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);

			Car_AddItem(carid, string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invModel], amount);
			Inventory_Remove(playerid, string, amount);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into the trunk.", ReturnName(playerid, 0), string);
			Car_ShowTrunk(playerid, carid);
		}
		else Car_ShowTrunk(playerid, carid);
	}
	return 1;
}

Dialog:CarTake(playerid, response, listitem, inputtext[])
{
	static
	    carid = -1,
	    string[32];

    if ((carid = Car_Nearest(playerid)) != -1 && !CarData[carid][carLocked])
	{
	    strunpack(string, CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemName]);

		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemQuantity])
			    return Dialog_Show(playerid, CarTake, DIALOG_STYLE_INPUT, "Car Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, CarStorage[carid][PlayerData[playerid][pInventoryItem]][cItemQuantity]);

			new id = Inventory_Add(playerid, string, CarStorage[carid][PlayerData[playerid][pStorageItem]][cItemModel], amount);

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			Car_RemoveItem(carid, string, amount);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from the trunk.", ReturnName(playerid, 0), string);
			Car_ShowTrunk(playerid, carid);
		}
		else Car_ShowTrunk(playerid, carid);
	}
	return 1;
}

Dialog:CarStorage(playerid, response, listitem, inputtext[])
{
	static
	    carid = -1,
		string[64];

	new vehicleid = GetNearestVehicle(playerid);

	if ((carid = Car_Nearest(playerid)) != -1 && !CarData[carid][carLocked])
	{
		if (response)
		{
		    if (listitem == MAX_CAR_STORAGE) {
    			Car_WeaponStorage(playerid, carid);
		    }
		    else if (CarStorage[carid][listitem][cItemExists])
			{
   				PlayerData[playerid][pStorageItem] = listitem;
   				PlayerData[playerid][pInventoryItem] = listitem;

				strunpack(string, CarStorage[carid][listitem][cItemName]);

				format(string, sizeof(string), "%s (Quantity: %d)", string, CarStorage[carid][listitem][cItemQuantity]);
				Dialog_Show(playerid, TrunkOptions, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
			}
			else {
   				OpenInventory(playerid);

				PlayerData[playerid][pStorageSelect] = 2;
			}
		}
		else
		{
			SetTrunkStatus(vehicleid, false);
		}
	}
	return 1;
}

Dialog:TrunkOptions(playerid, response, listitem, inputtext[])
{
    static
	    carid = -1,
		itemid = -1,
		backpack = -1,
		string[32];

	if ((carid = Car_Nearest(playerid)) != -1 && !CarData[carid][carLocked])
	{
	    itemid = PlayerData[playerid][pStorageItem];

	    strunpack(string, CarStorage[carid][itemid][cItemName]);

		if (response)
		{
			switch (listitem)
			{
			    case 0:
			    {
			        if (CarStorage[carid][itemid][cItemQuantity] == 1)
			        {
			            if (!strcmp(string, "Backpack") && Inventory_HasItem(playerid, "Backpack"))
			                return SendErrorMessage(playerid, "You already have a backpack in your inventory.");

			            new id = Inventory_Add(playerid, string, CarStorage[carid][itemid][cItemModel], 1);

						if (id == -1)
        					return SendErrorMessage(playerid, "You don't have any inventory slots left.");

                        if (!strcmp(string, "Backpack") && (backpack = GetVehicleBackpack(carid)) != -1)
						{
						    BackpackData[backpack][backpackVehicle] = 0;
						    BackpackData[backpack][backpackPlayer] = PlayerData[playerid][pID];

						    Backpack_Save(backpack);
						    SetAccessories(playerid);
						}
			            Car_RemoveItem(carid, string);

			            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from the trunk.", ReturnName(playerid, 0), string);
						Car_ShowTrunk(playerid, carid);
			        }
			        else
			        {
			            Dialog_Show(playerid, CarTake, DIALOG_STYLE_INPUT, "Car Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, CarStorage[carid][itemid][cItemQuantity]);
			        }
			    }
				case 1:
				{
					new id = Inventory_GetItemID(playerid, string);

					if (!strcmp(string, "Backpack")) {
					    Car_ShowTrunk(playerid, carid);

						return SendErrorMessage(playerid, "You can only store one backpack in your trunk.");
					}
					else if (id == -1) {
						Car_ShowTrunk(playerid, carid);

						return SendErrorMessage(playerid, "You don't have anymore of this item to store!");
					}
					else if (InventoryData[playerid][id][invQuantity] == 1)
					{
					    Car_AddItem(carid, string, InventoryData[playerid][id][invModel], 1);
						Inventory_Remove(playerid, string);

						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into the trunk.", ReturnName(playerid, 0), string);
						Car_ShowTrunk(playerid, carid);
					}
					else if (InventoryData[playerid][id][invQuantity] > 1) {
					    PlayerData[playerid][pInventoryItem] = id;

                        Dialog_Show(playerid, CarDeposit, DIALOG_STYLE_INPUT, "Car Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][id][invQuantity]);
					}
				}
			}
		}
		else
		{
		    Car_ShowTrunk(playerid, carid);
		}
	}
	return 1;
}

Dialog:HouseWeapons(playerid, response, listitem, inputtext[])
{
	static
	    houseid = -1;

    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
		if (response)
		{
		    if (HouseData[houseid][houseWeapons][listitem] != 0)
		    {
				GiveWeaponToPlayer(playerid, HouseData[houseid][houseWeapons][listitem], HouseData[houseid][houseAmmo][listitem]);

				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid, 0), ReturnWeaponName(HouseData[houseid][houseWeapons][listitem]));
                Log_Write("logs/storage_log.txt", "[%s] %s has taken a \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid, 0), ReturnWeaponName(HouseData[houseid][houseWeapons][listitem]), HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));

				HouseData[houseid][houseWeapons][listitem] = 0;
				HouseData[houseid][houseAmmo][listitem] = 0;

				House_Save(houseid);
				House_WeaponStorage(playerid, houseid);
			}
			else
			{
			    new
					weaponid = GetWeapon(playerid),
					ammo = GetPlayerAmmo(playerid);

			    if (!weaponid)
			        return SendErrorMessage(playerid, "You are not holding any weapon!");

       			if (weaponid == 23 && PlayerData[playerid][pTazer])
	    			return SendErrorMessage(playerid, "You can't store a tazer into your safe.");

                if (weaponid == 25 && PlayerData[playerid][pBeanBag])
	    			return SendErrorMessage(playerid, "You can't store a beanbag shotgun into your safe.");

                ResetWeapon(playerid, weaponid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));

				HouseData[houseid][houseWeapons][listitem] = weaponid;
				HouseData[houseid][houseAmmo][listitem] = ammo;

				House_Save(houseid);
				House_WeaponStorage(playerid, houseid);
			}
		}
		else
		{
		    House_OpenStorage(playerid, houseid);
		}
	}
	return 1;
}

Dialog:HouseDeposit(playerid, response, listitem, inputtext[])
{
	static
	    houseid = -1,
	    string[32];

    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
	    strunpack(string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invItem]);

		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity])
			    return Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "House Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);

			House_AddItem(houseid, string, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invModel], amount);
			Inventory_Remove(playerid, string, amount);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid, 0), string);
			House_ShowItems(playerid, houseid);
		}
		else House_OpenStorage(playerid, houseid);
	}
	return 1;
}

Dialog:HouseTake(playerid, response, listitem, inputtext[])
{
	static
	    houseid = -1,
	    string[32];

    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
	    strunpack(string, HouseStorage[houseid][PlayerData[playerid][pStorageItem]][hItemName]);

		if (response)
		{
			new amount = strval(inputtext);

			if (amount < 1 || amount > HouseStorage[houseid][PlayerData[playerid][pStorageItem]][hItemQuantity])
			    return Dialog_Show(playerid, HouseTake, DIALOG_STYLE_INPUT, "House Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, HouseStorage[houseid][PlayerData[playerid][pInventoryItem]][hItemQuantity]);

			new id = Inventory_Add(playerid, string, HouseStorage[houseid][PlayerData[playerid][pStorageItem]][hItemModel], amount);

			if (id == -1)
				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			House_RemoveItem(houseid, string, amount);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their house storage.", ReturnName(playerid, 0), string);

			House_ShowItems(playerid, houseid);
			Log_Write("logs/storage_log.txt", "[%s] %s has taken %d \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid, 0), amount, string, HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));
		}
		else House_OpenStorage(playerid, houseid);
	}
	return 1;
}

Dialog:HouseWithdrawCash(playerid, response, listitem, inputtext[])
{
    static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1 && House_IsOwner(playerid, houseid))
	{
		if (response)
		{
		    new amount = strval(inputtext);

		    if (isnull(inputtext))
		        return Dialog_Show(playerid, HouseWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));

			if (amount < 1 || amount > HouseData[houseid][houseMoney])
			    return Dialog_Show(playerid, HouseWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));

			HouseData[houseid][houseMoney] -= amount;
			GiveMoney(playerid, amount);

			House_Save(houseid);
			House_OpenStorage(playerid, houseid);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s from their house safe.", ReturnName(playerid, 0), FormatNumber(amount));
		}
		else Dialog_Show(playerid, HouseMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
	}
	return 1;
}

Dialog:HouseDepositCash(playerid, response, listitem, inputtext[])
{
    static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1 && House_IsOwner(playerid, houseid))
	{
		if (response)
		{
		    new amount = strval(inputtext);

		    if (isnull(inputtext))
		        return Dialog_Show(playerid, HouseDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));

			if (amount < 1 || amount > GetMoney(playerid))
			    return Dialog_Show(playerid, HouseDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));

			HouseData[houseid][houseMoney] += amount;
			GiveMoney(playerid, -amount);

			House_Save(houseid);
			House_OpenStorage(playerid, houseid);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s into their house safe.", ReturnName(playerid, 0), FormatNumber(amount));
		}
		else Dialog_Show(playerid, HouseMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
	}
	return 1;
}

Dialog:HouseMoney(playerid, response, listitem, inputtext[])
{
    static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1 && House_IsOwner(playerid, houseid))
	{
		if (response)
		{
			switch (listitem)
			{
			    case 0: {
					Dialog_Show(playerid, HouseWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));
				}
				case 1: {
				    Dialog_Show(playerid, HouseDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Withdraw", "Back", FormatNumber(HouseData[houseid][houseMoney]));
				}
			}
		}
		else House_OpenStorage(playerid, houseid);
	}
	return 1;
}

Dialog:HouseItems(playerid, response, listitem, inputtext[])
{
    static
	    houseid = -1,
		string[64];

	if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
		if (response)
		{
    		if (HouseStorage[houseid][listitem][hItemExists])
			{
   				PlayerData[playerid][pStorageItem] = listitem;
   				PlayerData[playerid][pInventoryItem] = listitem;

				strunpack(string, HouseStorage[houseid][listitem][hItemName]);

				format(string, sizeof(string), "%s (Quantity: %d)", string, HouseStorage[houseid][listitem][hItemQuantity]);
				Dialog_Show(playerid, StorageOptions, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
			}
			else {
   				OpenInventory(playerid);

				PlayerData[playerid][pStorageSelect] = 1;
			}
		}
		else House_OpenStorage(playerid, houseid);
	}
	return 1;
}

Dialog:HouseStorage(playerid, response, listitem, inputtext[])
{
	static
	    houseid = -1;

	if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
		if (response)
		{
		    if (listitem == 0) {
		        House_ShowItems(playerid, houseid);
		    }
      		else if (listitem == 1) {
				House_WeaponStorage(playerid, houseid);
		    }
		    else if (listitem == 2) {
		        Dialog_Show(playerid, HouseMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
		}
	}
	return 1;
}

Dialog:StorageOptions(playerid, response, listitem, inputtext[])
{
    static
	    houseid = -1,
		itemid = -1,
		backpack = -1,
		string[32];

	if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE))
	{
	    itemid = PlayerData[playerid][pStorageItem];

	    strunpack(string, HouseStorage[houseid][itemid][hItemName]);

		if (response)
		{
			switch (listitem)
			{
			    case 0:
			    {
			        if (HouseStorage[houseid][itemid][hItemQuantity] == 1)
			        {
			            if (!strcmp(string, "Backpack") && Inventory_HasItem(playerid, "Backpack"))
           					return SendErrorMessage(playerid, "You already have a backpack in your inventory.");

			            new id = Inventory_Add(playerid, string, HouseStorage[houseid][itemid][hItemModel], 1);

						if (id == -1)
        					return SendErrorMessage(playerid, "You don't have any inventory slots left.");

                        if (!strcmp(string, "Backpack") && (backpack = GetHouseBackpack(houseid)) != -1)
						{
						    BackpackData[backpack][backpackHouse] = 0;
						    BackpackData[backpack][backpackPlayer] = PlayerData[playerid][pID];

						    Backpack_Save(backpack);
						    SetAccessories(playerid);
						}
			            House_RemoveItem(houseid, string);
			            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their house storage.", ReturnName(playerid, 0), string);

						House_ShowItems(playerid, houseid);
						Log_Write("logs/storage_log.txt", "[%s] %s has taken \"%s\" from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid, 0), string, HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));
			        }
			        else
			        {
			            Dialog_Show(playerid, HouseTake, DIALOG_STYLE_INPUT, "House Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, HouseStorage[houseid][itemid][hItemQuantity]);
			        }
			    }
				case 1:
				{
					new id = Inventory_GetItemID(playerid, string);

					if (!strcmp(string, "Backpack")) {
					    House_ShowItems(playerid, houseid);

						return SendErrorMessage(playerid, "You can only store one backpack in your house.");
					}
					else if (id == -1) {
						House_ShowItems(playerid, houseid);

						return SendErrorMessage(playerid, "You don't have anymore of this item to store!");
					}
					else if (InventoryData[playerid][id][invQuantity] == 1)
					{
					    House_AddItem(houseid, string, InventoryData[playerid][id][invModel]);
						Inventory_Remove(playerid, string);

						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid, 0), string);
						House_ShowItems(playerid, houseid);
					}
					else if (InventoryData[playerid][id][invQuantity] > 1) {
					    PlayerData[playerid][pInventoryItem] = id;

                        Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "House Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][id][invQuantity]);
					}
				}
			}
		}
		else
		{
		    House_ShowItems(playerid, houseid);
		}
	}
	return 1;
}

Dialog:EditGlasses(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            if (!IsPlayerAttachedObjectSlotUsed(playerid, 0))
	            {
	                PlayerData[playerid][pToggleGlasses] = 0;
	                SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pGlasses], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
					SendServerMessage(playerid, "You have attached your glasses.");
				}
				else
				{
				    PlayerData[playerid][pToggleGlasses] = 1;
	                RemovePlayerAttachedObject(playerid, 0);
					SendServerMessage(playerid, "You have detached your glasses.");
				}
			}
			case 1:
			{
			    PlayerData[playerid][pToggleGlasses] = 0;
       			SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pGlasses], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);

			    EditAttachedObject(playerid, 0);
			    PlayerData[playerid][pEditType] = 1;
			}
			case 2:
			{
			    RemovePlayerAttachedObject(playerid, 0);
			    PlayerData[playerid][pGlasses] = 0;
			    SendServerMessage(playerid, "You have deleted your glasses.");
			}
		}
	}
	return 1;
}

Dialog:EditHat(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            if (!IsPlayerAttachedObjectSlotUsed(playerid, 1))
            	{
	                PlayerData[playerid][pToggleHat] = 0;
	                SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pHat], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
					SendServerMessage(playerid, "You have attached your hat.");
				}
				else
				{
				    PlayerData[playerid][pToggleHat] = 1;
	                RemovePlayerAttachedObject(playerid, 1);
					SendServerMessage(playerid, "You have detached your hat.");
				}
			}
			case 1:
			{
			    PlayerData[playerid][pToggleHat] = 0;
	            SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pHat], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);

			    EditAttachedObject(playerid, 1);
			    PlayerData[playerid][pEditType] = 2;
			}
			case 2:
			{
			    RemovePlayerAttachedObject(playerid, 1);
			    PlayerData[playerid][pHat] = 0;
			    SendServerMessage(playerid, "You have deleted your hat.");
			}
		}
	}
	return 1;
}

Dialog:EditBandana(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            if (!IsPlayerAttachedObjectSlotUsed(playerid, 2))
	            {
	                PlayerData[playerid][pToggleBandana] = 0;
	                SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pBandana], 2, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
					SendServerMessage(playerid, "You have attached your bandana.");
				}
				else
				{
				    PlayerData[playerid][pToggleBandana] = 1;
	                RemovePlayerAttachedObject(playerid, 2);
					SendServerMessage(playerid, "You have detached your bandana.");
				}
			}
			case 1:
			{
			    PlayerData[playerid][pToggleBandana] = 0;
       			SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pBandana], 2, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);

			    EditAttachedObject(playerid, 2);
			    PlayerData[playerid][pEditType] = 3;
			}
			case 2:
			{
			    RemovePlayerAttachedObject(playerid, 2);
			    PlayerData[playerid][pBandana] = 0;
			    SendServerMessage(playerid, "You have deleted your bandana.");
			}
		}
	}
	return 1;
}

Dialog:Accessory(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            if (!PlayerData[playerid][pGlasses])
	                return SendErrorMessage(playerid, "You don't own a pair of glasses.");

	            Dialog_Show(playerid, EditGlasses, DIALOG_STYLE_LIST, "Glasses", "Toggle Glasses\nEdit Glasses\nDelete Glasses", "Select", "Cancel");
			}
			case 1:
			{
			    if (!PlayerData[playerid][pHat])
	                return SendErrorMessage(playerid, "You don't own a hat.");

			    Dialog_Show(playerid, EditHat, DIALOG_STYLE_LIST, "Hat", "Toggle Hat\nEdit Hat\nDelete Hat", "Select", "Cancel");
			}
			case 2:
			{
			    if (!PlayerData[playerid][pBandana])
	                return SendErrorMessage(playerid, "You don't own a bandana.");

			    Dialog_Show(playerid, EditBandana, DIALOG_STYLE_LIST, "Bandana", "Toggle Bandana\nEdit Bandana\nDelete Bandana", "Select", "Cancel");
			}
		}
	}
	return 1;
}

Dialog:PinAccount(playerid, response, listitem, inputtext[])
{
	if (!response)
	    return Kick(playerid);
	
	else if (isnull(inputtext))
	{
		return Dialog_Show(playerid, PinAccount, DIALOG_STYLE_INPUT, ""WHITE_E"Pin Akaun", "Sila masukkan pin anda dibawah:", "Masuk", "Keluar");
	}
	else 
	{
		if(strval(inputtext) == PlayerData[playerid][pPin])
		{
			for (new i = 0; i < 28; i ++) 
			{
				TextDrawHideForPlayer(playerid, LOGINTD[i]);
				TextDrawHideForPlayer(playerid, LOGINTDNAME[playerid]);
			}
			CancelSelectTextDraw(playerid);

			Dialog_Show(playerid, RegisterPassword, DIALOG_STYLE_PASSWORD, "Kata Laluan", "Pin telah disahkan!\n\nSila masukkan kata laluan anda dibawah:", "Serah", "Keluar");	
			return 1;
		}
		else 
		{
			Dialog_Show(playerid, PinAccount, DIALOG_STYLE_INPUT, ""WHITE_E"Pin Akaun", "Pin yang anda masukkan salah!\n\nSila masukkan pin anda dibawah:", "Masuk", "Keluar");
		}
	}
	return 1;
}

Dialog:RegisterPassword(playerid, response, listitem, inputtext[])
{
	if (!response)
		return Kick(playerid);

	else if (isnull(inputtext))
	    return Dialog_Show(playerid, RegisterPassword, DIALOG_STYLE_PASSWORD, "Kata Laluan", "Pin telah disahkan!\n\nSila masukkan kata laluan anda dibawah:", "Serah", "Keluar");	

	else
	{	
		static
			query[128];

		format(PlayerData[playerid][pPassword], 120, "%s", inputtext);

		// Set Password
		format(query, sizeof(query), "UPDATE `accounts` SET `Password` = '%s', `Token` = '0' WHERE `Username` = '%s'", inputtext, PlayerData[playerid][pUsername]);
		mysql_tquery(g_iHandle, query);

		// Update the last login date.
		format(query, sizeof(query), "UPDATE `accounts` SET `IP` = '%s', `LoginDate` = '%s' WHERE `Username` = '%s'", PlayerData[playerid][pIP], ReturnDate(), PlayerData[playerid][pUsername]);
		mysql_tquery(g_iHandle, query);

		// Load the character data.
		format(query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%s' LIMIT 3", PlayerData[playerid][pUsername]);
		mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", playerid, THREAD_CHARACTERS);
	}
	return 1;
}

Dialog:LoginScreen(playerid, response, listitem, inputtext[])
{
	if (!response)
	    return Kick(playerid);
	
	else if (isnull(inputtext))
	{
		return Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, ""WHITE_E"Log Masuk", "Sila masukkan kata laluan anda dibawah:", "Masuk", "Keluar");
	}
	else 
	{
		if (!strcmp(inputtext, PlayerData[playerid][pPassword], true))
		{ 
			for (new i = 0; i < 28; i ++) 
			{
				TextDrawHideForPlayer(playerid, LOGINTD[i]);
				TextDrawHideForPlayer(playerid, LOGINTDNAME[playerid]);
			}
			CancelSelectTextDraw(playerid);

			static
				query[128];

			// Update the last login date.
			format(query, sizeof(query), "UPDATE `accounts` SET `IP` = '%s', `LoginDate` = '%s' WHERE `Username` = '%s'", PlayerData[playerid][pIP], ReturnDate(), PlayerData[playerid][pUsername]);
			mysql_tquery(g_iHandle, query);

			// Load the character data.
			format(query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%s' LIMIT 3", PlayerData[playerid][pUsername]);
			mysql_tquery(g_iHandle, query, "OnQueryFinished", "dd", playerid, THREAD_CHARACTERS);
		}
		else
		{
			Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, ""WHITE_E"Log Masuk", "Kata laluan yang anda masukkan salah!\n\nSila masukkan kata laluan anda dibawah:", "Masuk", "Keluar");
		}
	}
	return 1;
}

Dialog:DeleteChar(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new query[128];

	    format(query, sizeof(query), "DELETE FROM `characters` WHERE `Username` = '%s' AND `Character` = '%s'", PlayerData[playerid][pUsername], PlayerCharacters[playerid][PlayerData[playerid][pCharacter] - 1]);
		mysql_tquery(g_iHandle, query);

		SendServerMessage(playerid, "You have deleted \"%s\" from your account.", PlayerCharacters[playerid][PlayerData[playerid][pCharacter] - 1]);
        PlayerCharacters[playerid][PlayerData[playerid][pCharacter] - 1][0] = 0;

        ShowCharacterMenu(playerid);
	}
	return 1;
}
Dialog:CreateChar(playerid, response, listitem, inputtext[])
{
	if (!response)
	    return PlayerData[playerid][pCharacter] = 0;

	else if (isnull(inputtext) || strlen(inputtext) > 20)
        return Dialog_Show(playerid, CreateChar, DIALOG_STYLE_INPUT, "Buat Watak", "Sila masukkan nama watak baharu anda di bawah:\n\nAmaran: Nama anda mestilah dalam format Firstname_Lastname dan tidak melebihi 20 aksara.", "Buat", "Batal");

	else if (!IsValidRoleplayName(inputtext))
	    return Dialog_Show(playerid, CreateChar, DIALOG_STYLE_INPUT, "Buat Watak", "Ralat: Anda telah memasukkan nama watak yang tidak sah.\n\nSila masukkan nama watak baharu anda di bawah:\n\nAmaran: Nama anda mestilah dalam format Firstname_Lastname dan tidak melebihi 20 aksara.", "Buat", "Batal");
	
	else
	{
	    static
	        query[128];

		format(query, sizeof(query), "SELECT `ID` FROM `characters` WHERE `Character` = '%s'", inputtext);
		mysql_tquery(g_iHandle, query, "OnCharacterCheck", "ds", playerid, inputtext);
	}
	return 1; 
}

Dialog:SelectChar(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem) {
	        case 0: {
				SelectCharacter(playerid, 1);
			}
	        case 1: {
				SelectCharacter(playerid, 2);
			}
			case 2: {
				//SelectCharacter(playerid, 3);
				SendServerMessage(playerid, "Slot ini akan datang.");
				ShowCharacterMenu(playerid);
			}
		}
	}
	else
	{
		Kick(playerid);
	}
	return 1;
}


Dialog:PersonalIdentification(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    switch (listitem) {
	        case 0: {
				Dialog_Show(playerid, Gender, DIALOG_STYLE_LIST, "Jantina", "Lelaki\nPerempuan", "Pilih", "Kembali");
			}
	        case 1: {
				Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Tarikh Lahir", "Sila masukkan tarikh lahir anda di bawah (HH/BB/TTTT):", "Pilih", "Kembali");
			}
			case 2: {
				Dialog_Show(playerid, Origin, DIALOG_STYLE_INPUT, "Asal", "Sila masukkan asal watak anda di bawah:", "Pilih", "Kembali");
			}
		}
	}
	else
	{
		if (!strlen(PlayerData[playerid][pBirthdate]))
		{
			SendErrorMessage(playerid, "Anda perlu memasukkan tarikh lahir.");
			Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
			return 1;
		}
		else if (!strlen(PlayerData[playerid][pOrigin]))
		{
			SendErrorMessage(playerid, "Anda perlu memasukkan asal.");
			Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
			return 1;
		}

		else
		{
			switch (PlayerData[playerid][pGender])
			{
				case 1:
					ShowModelSelectionMenu(playerid, "Select Skin", MODEL_SELECTION_SKIN, g_aMaleSkins, sizeof(g_aMaleSkins), -16.0, 0.0, -55.0);

				case 2:
					ShowModelSelectionMenu(playerid, "Select Skin", MODEL_SELECTION_SKIN, g_aFemaleSkins, sizeof(g_aFemaleSkins), -16.0, 0.0, -55.0);
			}
		}
	}
	return 1;
}

Dialog:Gender(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    PlayerData[playerid][pGender] = listitem + 1;

		SendServerMessage(playerid, "Jantina telah ditetapkan ke "YELLOW_E"%s"WHITE_E".", (PlayerData[playerid][pGender] == 2) ? ("Perempuan") : ("Lelaki"));
	    Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");

		PlayerData[playerid][pSkin] = (listitem) ? (233) : (98);
	}
	else
	{
		Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
	}
	return 1;
}

Dialog:DateBirth(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			iDay,
			iMonth,
			iYear;

	    static const
	        arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	    if (sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
	        Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Tarikh Lahir", "Ralat: Format tidak sah dinyatakan!\n\nSila masukkan tarikh lahir anda di bawah (HH/BB/TTTT):", "Serah", "Kembali");
		}
		else if (iYear < 1900 || iYear > 2014) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Tarikh Lahir", "Ralat: Tahun tidak sah dinyatakan!\n\nSila masukkan tarikh lahir anda di bawah (HH/BB/TTTT):", "Serah", "Kembali");
		}
		else if (iMonth < 1 || iMonth > 12) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Tarikh Lahir", "Ralat: Bulan tidak sah dinyatakan!\n\nSila masukkan tarikh lahir anda di bawah (HH/BB/TTTT):", "Serah", "Kembali");
		}
		else if (iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Tarikh Lahir", "Ralat: Hari tidak sah dinyatakan!\n\nSila masukkan tarikh lahir anda di bawah (HH/BB/TTTT):", "Serah", "Kembali");
		}
		else {
			format(PlayerData[playerid][pBirthdate], 24, inputtext);
			SendServerMessage(playerid, "Tarikh lahir telah ditetapkan ke "YELLOW_E"%s"WHITE_E".", inputtext);
		    Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
		}
	}
	else
	{
		Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
	}
	return 1;
}

Dialog:Origin(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext) || strlen(inputtext) > 32) {
	        Dialog_Show(playerid, Origin, DIALOG_STYLE_INPUT, "Asal", "Sila masukkan asal watak anda di bawah:", "Serah", "Kembali");
		}
		else for (new i = 0, len = strlen(inputtext); i != len; i ++) {
		    if ((inputtext[i] >= 'A' && inputtext[i] <= 'Z') || (inputtext[i] >= 'a' && inputtext[i] <= 'z') || (inputtext[i] >= '0' && inputtext[i] <= '9') || (inputtext[i] == ' ') || (inputtext[i] == ',') || (inputtext[i] == '.'))
				continue;

			else return Dialog_Show(playerid, Origin, DIALOG_STYLE_INPUT, "Asal", "Ralat: Hanya huruf dan nombor diterima dalam asal.\n\nSila masukkan asal watak anda di bawah:", "Serah", "Kembali");
		}
		format(PlayerData[playerid][pOrigin], 32, inputtext);
		SendServerMessage(playerid, "Asal telah ditetapkan ke "YELLOW_E"%s"WHITE_E".", inputtext);
		Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
	}
	else
	{
		Dialog_Show(playerid, PersonalIdentification, DIALOG_STYLE_LIST, ""WHITE_E"Maklumat Watak", ""WHITE_E"Jantina\nTarikh Lahir\nAsal", "Pilih", "Seterunsya");
	}
	return 1;
}

Dialog:DropInjured(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		static
	        userid = -1;

		if (sscanf(inputtext, "u", userid))
			return Dialog_Show(playerid, DropInjured, DIALOG_STYLE_INPUT, "Patient ID", "Input your patient id:", "Submit", "Cancel");

		if (userid == INVALID_PLAYER_ID || !IsPlayerInVehicle(playerid, GetPlayerVehicleID(playerid)))
			return SendErrorMessage(playerid, "That player is disconnected or not near you.");

		if (userid == playerid)
			return SendErrorMessage(playerid, "You can't deliver yourself to the hospital.");

		if (!PlayerData[userid][pInjured])
			return SendErrorMessage(playerid, "That player is not injured.");

		ClearAnimations(userid);

		SendServerMessage(playerid, "You have delivered %s to the hospital.", ReturnName(userid, 0));

		SetPlayerPos(playerid, 1187.3882, -1323.5475, 13.5590);
		SetPlayerFacingAngle(playerid, 271.5479);

		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);

		TogglePlayerControllable(playerid, 1);
		SetCameraBehindPlayer(playerid);

		SendServerMessage(playerid, "You have recovered at hospital.");

		GameTextForPlayer(playerid, " ", 1, 3);

		PlayerData[playerid][pInjured] = 0;
	}
	return 1;
}

Dialog:Report(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new i = listitem;
		SetPVarInt(playerid, "ClickedReport", i);
		new tstr[64], mstr[128], lstr[512];

		strunpack(mstr, ReportData[i][rText]);
		format(tstr, sizeof(tstr), ""GREEN_E"Report Id: #%d", i);
		format(lstr,sizeof(lstr),""WHITE_E"Player: "GREEN_E"%s\n"WHITE_E"Reported: "RED_E"%s",  ReturnName(ReportData[i][rPlayer], 0), mstr);
		Dialog_Show(playerid, Reports, DIALOG_STYLE_INPUT, tstr, lstr, "Respond","Close");
	}
	return 1;
}

Dialog:Reports(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new reportid = GetPVarInt(playerid, "ClickedReport");
		
		SendInfoMessage(ReportData[reportid][rPlayer], "Your report has been accepted by admin %s.",  ReturnName(playerid, 0));
		SendInfoMessage(ReportData[reportid][rPlayer], "Respond: %s", inputtext);

		SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has responded %s's report.", ReturnName(playerid, 0), ReturnName(ReportData[reportid][rPlayer], 0));

		PlayerData[ReportData[reportid][rPlayer]][pReportTime] = 0;

		Report_Remove(reportid);
	}
	return 1;
}

Dialog:BodyInsurance(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new amount = floatround(strval(inputtext));
		new total = PlayerData[playerid][pBodyInsurance] + amount;
		new value = amount * 250;

		if(amount < 0 || amount > 20) return SendErrorMessage(playerid, "Maksimum insuran adalah 20.");

		if(total > 20) return SendErrorMessage(playerid, "Anda telah mempunyai 20 insuran badan, anda tidak boleh membeli lebih.");

		if(GetMoney(playerid) < value) return SendErrorMessage(playerid, "Anda tidak mempunyai duit yang cukup untuk membeli insuran badan.");

		GiveMoney(playerid, -value);
		PlayerData[playerid][pBodyInsurance] += amount;
		SendServerMessage(playerid, "Anda telah membeli "YELLOW_E"%d "WHITE_E"insuran badan dengan harga "GREEN_E"%s"WHITE_E".", amount, FormatNumber(value));
	}
	return 1;
}

Dialog:BuyMedkit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new amount = floatround(strval(inputtext));
		new total = Inventory_Count(playerid, "First Aid") + amount;
		new value = amount * 20;

		if(amount < 0 || amount > 20) return SendErrorMessage(playerid, "Maksimum medkit adalah 20.");

		if(total > 20) return SendErrorMessage(playerid, "Anda telah mempunyai 20 medkit, anda tidak boleh membeli lebih");

		if(GetMoney(playerid) < value) return SendErrorMessage(playerid, "Anda tidak mempunyai duit yang cukup untuk membeli medkit.");
		
		GiveMoney(playerid, -value);
		Inventory_Add(playerid, "First Aid", 1580, amount);
		SendServerMessage(playerid, "Anda telah membeli "YELLOW_E"%d "WHITE_E"medkit dengan harga "GREEN_E"%s"WHITE_E".", amount, FormatNumber(value));
	}
	return 1;
}

Dialog:RentVehicle(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS)
					return SendErrorMessage(playerid, "You have already owns the maximum amount of cars.");

				static
					Float:x,
					Float:y,
					Float:z,
					Float:angle;

				GetPlayerPos(playerid, x, y, z);
				GetPlayerFacingAngle(playerid, angle);

				Car_Create(PlayerData[playerid][pID], 475, x, y + 2, z + 1, angle, random(127), random(127), gettime() + (1 * 86400));

				SendServerMessage(playerid, "Anda telah menyewa kenderaan ini untuk 1 hari.");
				GiveMoney(playerid, -14000);
			}
			case 1:
			{
				if (Car_GetCount(playerid) >= MAX_OWNABLE_CARS)
					return SendErrorMessage(playerid, "You have already owns the maximum amount of cars.");

				static
					Float:x,
					Float:y,
					Float:z,
					Float:angle;

				GetPlayerPos(playerid, x, y, z);
				GetPlayerFacingAngle(playerid, angle);

				Car_Create(PlayerData[playerid][pID], 462, x, y + 2, z + 1, angle, random(127), random(127), gettime() + (1 * 86400));

				SendServerMessage(playerid, "Anda telah menyewa kenderaan ini untuk 1 hari.");
				GiveMoney(playerid, -200);
			}
		}
	}
	return 1;
}

Dialog:Help(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new str[9500];
				strcat(str, "Command\tPerincian\n/b\tLocal OOC chat\n");
				strcat(str, "/me\t-\n");
				strcat(str, "/do\t-\n");
				strcat(str, "/ame\t-\n");
				strcat(str, "/ado\t-\n");
				strcat(str, "/s\tJerit\n");
				strcat(str, "/l\tCakap perlahan\n");
				strcat(str, "/o\tGobal OOC chat.\n");
				strcat(str, "/lastlogged\tPeriksa tarikh terakhir login pemain\n");
				strcat(str, "/report\tReport\n");
				strcat(str, "/username\tPeriksa akaun pemain\n");
				strcat(str, "/stats\tLihat statistik\n");
				strcat(str, "/acc\tMenu aksesori\n");
				strcat(str, "/clearchat\tBersihkan chat\n");
				strcat(str, "/buy\tBeli sesuatu\n");
				strcat(str, "/approve\t-\n");
				strcat(str, "/takejob\tAmbil job\n");
				strcat(str, "/sms\tMesej\n");
				strcat(str, "/answer\tJawab panggilan\n");
				strcat(str, "/hangup\tTutup panggilan\n");
				strcat(str, "/opencrate\tBuka crate\n");
				strcat(str, "/plant\tTanam drugs\n");
				strcat(str, "/harvest\tHarvest drugs\n");
				strcat(str, "/drop\tDrop senjata\n");
				strcat(str, "/joblist\tLihat senarai job\n");
				strcat(str, "/spawnpoint\tSet spawn point\n");
				strcat(str, "/drag\tAngkat pemain\n");
				strcat(str, "/pay\tBeri duit kepada pemain\n");
				strcat(str, "/gps\tBuka GPS\n");
				strcat(str, "/dropbackpack\tDrop backpack\n");
				strcat(str, "/channel\tSet channel walkie talkie\n");
				strcat(str, "/r\tChat walkie talkie\n");
				strcat(str, "/disablecp\tTutup checkpoint\n");
				strcat(str, "/animcmds\tSenarai command animation\n");
				strcat(str, "/boombox\tGuna boombox\n");
				strcat(str, "/search\tCari barang illegal pemain\n");
				strcat(str, "/gunrack\tLihat senjata di dalam rack\n");
				strcat(str, "/admins\tLihat admin online\n");
				strcat(str, "/showlicense\tTunjuk lesen\n");
				strcat(str, "/warnings\tLihat senarai warning\n");
				strcat(str, "/passwep\tBeri senjata\n");
				strcat(str, "/th\tHide/ show hide\n");
				strcat(str, "/w\tBerbisik\n");
				strcat(str, "/mask\tGuna mask\n");
				strcat(str, "/breakcuffs\tBuka cuff pemain\n");
				strcat(str, "/shakehand\tShake hand\n");
				strcat(str, "/frisk\tCheck inventory pemain\n");
				strcat(str, "/call\tPanggilan\n");
				strcat(str, "/shh\tMute lagu\n");
				strcat(str, "/uwep\tKeluarkan senjata\n");
				strcat(str, "/swep\tSimpan senjata\n");
				strcat(str, "/calculator\tGuna kalkulator\n");
				strcat(str, "/myproperties\tLihat senarai hartanah\n");
				strcat(str, "/salary\tLihat senarai salary\n");
				strcat(str, "/v\tLihat senarai kenderaan\n");
				strcat(str, "/settime\tSet time\n");
				strcat(str, "/setweather\tSet cuaca\n");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "General Commands", str, "Tutup", "");
			}
			case 1:
			{
				new str[9500];
				strcat(str, "Command\tPerincian\n/engine\tStart enjin kenderaan\n");
				strcat(str, "/lights\tOn/ off lampu kenderaan\n");
				strcat(str, "/hood\tBuka/ tutup hood kenderaan\n");
				strcat(str, "/windows\tBuka/ tutup tingkap kenderaan\n");
				strcat(str, "/abandon\tBuang kenderaan\n");
				strcat(str, "/lock\tKunci kenderaan\n");
				strcat(str, "/sell\tJual kenderaan kepada pemain\n");
				strcat(str, "/unmod\tBuang modifikasi kenderaan\n");
				strcat(str, "/trunk\tBuka trunk\n");
				strcat(str, "/crates\tSemak crate pada kenderaan\n");
				strcat(str, "/sb\tPakai/ buang seatbelt\n");
				strcat(str, "/tow\tTowing kenderaan\n");
				strcat(str, "/untow\tUntowing kenderaan\n");
				strcat(str, "/picklock\tBuka kunci kenderaan\n");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Commands", str, "Tutup", "");
			}
			case 2:
			{
				if (PlayerData[playerid][pFaction] != -1)
				{
					if (GetFactionType(playerid) == FACTION_POLICE)
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/rr\tRadio\n");
						strcat(str, "/online\tLihat faction member online\n");
						strcat(str, "/fquit\tKeluar dari faction\n");
						strcat(str, "/finvite\tInvite masuk faction\n");
						strcat(str, "/fremove\tKeluarkan dari faction\n");
						strcat(str, "/frank\tSet rank faction\n");
						strcat(str, "/fspawn\tSet posisi spawn faction\n");
						strcat(str, "/gr\tGovernment radio\n");
						strcat(str, "/m\tMegaphone\n");
						strcat(str, "/gov\tGovernment announcement\n");
						strcat(str, "/ticket\tBeri invoice kepada player\n");
						strcat(str, "/callsign\tTambah/ buang callsign pada kenderaan\n");
						strcat(str, "/tazer\tKeluarkan/ simpan tazer\n"); 
						strcat(str, "/beanbag\tKeluarkan/ simpan beanbag\n");
						strcat(str, "/cuff\tCuff pemain\n");
						strcat(str, "/uncuff\tUncuff pemain\n");
						strcat(str, "/detain\tKeluarkan/ masukkan dari kenderaan\n");
						strcat(str, "/mdc\tMobile data computer\n");
						strcat(str, "/arrest\tMsukkan pemain ke dalam penjara\n");
						strcat(str, "/seizeplant\tRampas tanaman drugs\n");
						strcat(str, "/drone\tDrone system\n");
						strcat(str, "/spike\tSpike system\n");
						strcat(str, "/roadblock\tRoadblock system\n"); 
						strcat(str, "/checkbelt\tCek seatbelt status\n");
						strcat(str, "/fingerprint\tCek barang\n");
						strcat(str, "/impound\tImpound kenderaan\n");
						strcat(str, "/cekbadan\tCek badan pemain\n");
						strcat(str, "/kickdoor\tTendang pintu\n");
						strcat(str, "/revokeweapon\tRampas lesen senjata\n");
						strcat(str, "/siren\tAttach siren pada kenderaan\n");
						strcat(str, "/sita\tSita rumah/ business\n");
						strcat(str, "/togglespeed\tOn/ off speedtrap\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Faction Police Commands", str, "Tutup", "");
					}
					else if (GetFactionType(playerid) == FACTION_MEDIC) 
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/rr\tRadio\n");
						strcat(str, "/online\tLihat faction member online\n");
						strcat(str, "/fquit\tKeluar dari faction\n");
						strcat(str, "/finvite\tInvite masuk faction\n");
						strcat(str, "/fremove\tKeluarkan dari faction\n");
						strcat(str, "/frank\tSet rank faction\n");
						strcat(str, "/fspawn\tSet posisi spawn faction\n");
						strcat(str, "/gr\tGovernment radio\n");
						strcat(str, "/m\tMegaphone\n");
						strcat(str, "/gov\tGovernment announcement\n");
						strcat(str, "/ticket\tBeri invoice kepada player\n");
						strcat(str, "/loadinjured\tMasukkan patient ke dalam ambulance\n");
						strcat(str, "/heal\tHeal pemain\n");
						strcat(str, "/checkurine\tCek urine status\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Faction Medic Commands", str, "Tutup", "");
					}
					else if (GetFactionType(playerid) == FACTION_MECHANIC)
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/rr\tRadio\n");
						strcat(str, "/online\tLihat faction member online\n");
						strcat(str, "/fquit\tKeluar dari faction\n");
						strcat(str, "/finvite\tInvite masuk faction\n");
						strcat(str, "/fremove\tKeluarkan dari faction\n");
						strcat(str, "/frank\tSet rank faction\n");
						strcat(str, "/fspawn\tSet posisi spawn faction\n");
						strcat(str, "/gr\tGovernment radio\n");
						strcat(str, "/m\tMegaphone\n");
						strcat(str, "/gov\tGovernment announcement\n");
						strcat(str, "/ticket\tBeri invoice kepada player\n");
						strcat(str, "/tune\tTune a vehicle\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Faction Mechanic Commands", str, "Tutup", "");
					}
					else if (GetFactionType(playerid) == FACTION_GANG)
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/rr\tRadio\n");
						strcat(str, "/online\tLihat faction member online\n");
						strcat(str, "/fquit\tKeluar dari faction\n");
						strcat(str, "/finvite\tInvite masuk faction\n");
						strcat(str, "/fremove\tKeluarkan dari faction\n");
						strcat(str, "/frank\tSet rank faction\n");
						strcat(str, "/fspawn\tSet posisi spawn faction\n");
						strcat(str, "/fspray\tSpray graffiti\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Faction Gang Commands", str, "Tutup", "");
					}
				}
				else
				{
					SendErrorMessage(playerid, "Anda bukan faction member.");
				}
			}
			case 3:
			{
				switch (PlayerData[playerid][pJob])
				{
					case 1:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/unload\tUnload crate\n");
						strcat(str, "/stoploading\tHenti loading crate\n");
						strcat(str, "/startdelivery\tMula delivery\n");
						strcat(str, "/cancelshipment\tBatal shipment\n");
						strcat(str, "/shipments\tSenarai shipments\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Courier Commands", str, "Tutup", "");
					}
					case 2:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/sorting\tMula sorting\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Sorter Commands", str, "Tutup", "");
					}
					case 3:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/acceptcall\tTerima panggilan\n");
						strcat(str, "/taxi\tOnduty/ offduty taxi\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Taxi Commands", str, "Tutup", "");
					}
					case 4:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/craftparts\tCraft part\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Weapon Smuggler Commands", str, "Tutup", "");
					}
					case 5:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/mine\tStart/ henti mining\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Miner Commands", str, "Tutup", "");
					}
					case 6:
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/sellfood\tJual makanan/ minuman\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Vendor Commands", str, "Tutup", "");
					}
					case 7: 
					{
						new str[9500];
						strcat(str, "Command\tPerincian\n/takebag\tAmbil sampah\n");
						strcat(str, "/dumpgarbage\tLupus sampah\n");
						strcat(str, "/findgarbage\tCar tong sampah\n");
						Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Job Garbage Commands", str, "Tutup", "");
					}
				}
			}
			case 4:
			{
				new str[9500];
				strcat(str, "Command\tPerincian\n/abandon\tBuang kedai\n");
				strcat(str, "/lock\tKunci kedai\n");
				strcat(str, "/sell\tJual kedai kepada pemain\n");
				strcat(str, "/bm\tBusiness menu\n");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Business Commands", str, "Tutup", "");
			}
			case 5:
			{
				new str[9500];
				strcat(str, "Command\tPerincian\n/abandon\tBuang rumah\n");
				strcat(str, "/switch\tO/ off lampu rumah\n");
				strcat(str, "/lock\tKunci rumah\n");
				strcat(str, "/sell\tJual rumah kepada pemain\n");
				strcat(str, "/storage\tAkses storage rumah\n");
				strcat(str, "/cook\tMasak\n");
				strcat(str, "/furniture\tAkses perabot rumah\n");
				strcat(str, "/doorbell\tTekan loceng rumah\n");
				strcat(str, "/buyrack\tBeli rack senjata \n");
				strcat(str, "/deleterack\tBuang rack\n");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "House Commands", str, "Tutup", "");
			}
		}
	}
	return 1;
}

Dialog:aHelp(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
                if (PlayerData[playerid][pAdmin] >= 1) 
                {
                    new str[9500];
                    strcat(str, "Command\tPerincian\n/aremovecall\tBuang callsign kenderaan\n");
                    strcat(str, "/a\tChat admin\n");
                    strcat(str, "/aduty\tOnduty/ offduty admin\n");
                    strcat(str, "/reports\tLihat senarai report aktif\n");
                    strcat(str, "/spectate\tSpectate pemain\n");
                    strcat(str, "/ajail\tJail pemain\n");
                    strcat(str, "/release\tKeluarkan pemain dari penjara\n");
                    strcat(str, "/kick\tKick pemain\n");
                    strcat(str, "/mute\tMute pemain\n");
                    strcat(str, "/unmute\tUnmute pemain\n");
                    strcat(str, "/freeze\tBekukan pemain\n");
                    strcat(str, "/unfreeze\tCairkan pemain\n");
                    strcat(str, "/revive\tRevive pemain\n");
                    strcat(str, "/respawn\tRespawn pemain\n");
                    strcat(str, "/refill\tRefill data pemain\n");
                    strcat(str, "/skin\tSet skin pemain\n");
                    strcat(str, "/checkstats\tPeriksa stats pemain\n");
                    strcat(str, "/shooter\tPeriksa killer terakhir pemain\n");
                    strcat(str, "/ann\tPengumuman\n");
                    strcat(str, "/aslap\tTampar pemain\n");
                    strcat(str, "/playervehicle\tPeriksa kenderaan pemain\n");
                    strcat(str, "/playerproperties\tPeriksa hartanah pemain\n");
                    strcat(str, "/bring\tTarik pemain ke posisi\n");
                    strcat(str, "/gotoco\tPergi ke koordinat\n");
                    strcat(str, "/goto\tPergi ke lokasi tertentu\n");
                    strcat(str, "/send\tHantar pemain\n");
                    strcat(str, "/setinterior\tSet interior pemain\n");
                    strcat(str, "/setvw\tSet virtual world pemain\n");
                    strcat(str, "/atalk\tPM pemain\n");
                    strcat(str, "/sendto\tHantar pemain ke pemain lain\n");
                    strcat(str, "/unban\tUnblacklist akaun\n");
                    strcat(str, "/blacklist\tBlacklist akaun\n");
                    strcat(str, "/togooc\tBuka/ tutup OOC global chat\n");
                    strcat(str, "/health\tSet health pemain\n");
                    strcat(str, "/armor\tSet armor pemain\n");
                    strcat(str, "/resetweps\tReset senjata pemain\n");
                    strcat(str, "/arepair\tBaiki kenderaan\n");
                    strcat(str, "/respawncar\tRespawn kenderaan\n");
                    strcat(str, "/setplate\tSet nombor plate kenderaan\n");
					strcat(str, "/setgovcar\tSet status kenderaan kerajaan\n");
                    strcat(str, "/setsiren\tSet siren status kenderaan\n");
                    strcat(str, "/bringcar\tTarik kenderaan\n");
                    strcat(str, "/entercar\tMasuk ke dalam kenderaan\n");
                    strcat(str, "/respawncars\tRespawn semua kenderaan\n");
                    strcat(str, "/respawnnear\tRespawn kenderaan disekitar\n");
                    strcat(str, "/aojail\tJail offline pemain\n");
                    strcat(str, "/asetfaction\tSet faction player\n");
                    strcat(str, "/asetrank\tSet rank faction player\n");
                    strcat(str, "/tracenumber\tSemak no telefone pemain\n");
                    strcat(str, "/flipcar\tFlip kenderaan\n");
                    strcat(str, "/listwarns\tSemak warning pemain\n");
                    strcat(str, "/warn\tWarning pemain\n");
                    strcat(str, "/healall\tHeall semua pemain\n");
                    strcat(str, "/masked\tLihat pemain yg memakai mask\n");
                    strcat(str, "/listguns\tSemak senarai senjata pemain\n");
                    strcat(str, "/playsong\tMainkan lagu\n");
                    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Admin Level 1 Commands", str, "Tutup", "");
                }
            }
            case 1:
            {
                if (PlayerData[playerid][pAdmin] >= 2) 
                {
                    new str[9500];
                    strcat(str, "Command\tPerincian\n/makeadmin\tSet level admin\n");
                    strcat(str, "/getip\tDapatkan IP pemain\n");
                    strcat(str, "/veh\tMunculkan kenderaan admin\n");
                    strcat(str, "/destroyveh\tBuang kenderaan admin\n");
                    strcat(str, "/givewep\tBeri senjata\n");
                    strcat(str, "/setplayer\tSet data pemain\n");
                    strcat(str, "/baninfo\tSemak informasi ban pemain\n");
                    strcat(str, "/factionmod\tSet faction moderator\n");
                    strcat(str, "/setname\tSet nama pemain\n");
                    strcat(str, "/createhouse\tBuat rumah\n");
                    strcat(str, "/destroyhouse\tBuang rumah\n");
                    strcat(str, "/edithouse\tEdit rumah\n");
                    strcat(str, "/near\tDapatkan ID point\n");
                    strcat(str, "/createbiz\tBuat kedai\n");
                    strcat(str, "/editbiz\tEdit kedai\n");
                    strcat(str, "/destroybiz\tBuang kedai\n");
                    strcat(str, "/createentrance\tBuat pintu\n");
                    strcat(str, "/editentrance\tEdit pintu\n");
                    strcat(str, "/destroyentrance\tBuang pintu\n");
                    strcat(str, "/createpump\tBuat pump\n");
                    strcat(str, "/destroypump\tBuang pump\n");
                    strcat(str, "/setpump\tSet liter minyak pump\n");
                    strcat(str, "/createjob\tBuat job\n");
                    strcat(str, "/destroyjob\tBuang job\n");
                    strcat(str, "/editjob\tEdit job\n");
                    strcat(str, "/createcrate\tBuat crate\n");
                    strcat(str, "/destroycrate\tBuang crate\n");
                    strcat(str, "/createfaction\tBuat faction\n");
                    strcat(str, "/destroyfaction\tBuang faction\n");
                    strcat(str, "/editfaction\tEdit faction\n");
                    strcat(str, "/setleader\tSet leader faction\n");
                    strcat(str, "/deleteaccount\tDelete akaun\n");
                    strcat(str, "/creategate\tBuat gate\n");
                    strcat(str, "/destroygate\tDestroy gate\n");
                    strcat(str, "/editgate\tEdit gate\n");
                    strcat(str, "/givecash\tBeri duit admin\n");
                    strcat(str, "/setitem\tSet item pemain\n");
                    strcat(str, "/createatm\tBuat atm\n");
                    strcat(str, "/destroyatm\tBuang atm\n");
                    strcat(str, "/asellhouse\tJual rumah pemain\n");
                    strcat(str, "/asellbiz\tJual kedai pemain\n");
                    strcat(str, "/jetpack\tGuna jetpack\n");
                    strcat(str, "/setworldweather\tSet cuaca server\n");
					strcat(str, "/setworldtime\tSet time server\n");
                    strcat(str, "/setfuel\tSet minyak kenderaan\n");
                    strcat(str, "/setcarhp\tSet health kenderaan\n");
                    strcat(str, "/creategarbage\tBuat garbage\n");
                    strcat(str, "/destroygarbage\tBuang garbage\n");
                    strcat(str, "/createvendor\tBuat vendor\n");
                    strcat(str, "/destroyvendor\tBuang vendor\n");
                    strcat(str, "/spawnitem\tSpawn item\n");
                    strcat(str, "/setquantity\tSet quantity item\n");
                    strcat(str, "/destroyitem\tBuang item\n");
                    strcat(str, "/adestroybox\tBuang boombox\n");
                    strcat(str, "/createrack\tBuang rack\n");
                    strcat(str, "/editrack\tEdit rack\n");
                    strcat(str, "/destroyrack\tBuang rack\n");
                    strcat(str, "/createspeed\tBuat speedcam\n");
                    strcat(str, "/destroyspeed\tBuang speed\n");
                    strcat(str, "/deletechar\tDelete karakter\n");
                    strcat(str, "/clearinventory\tClear inventory\n");
                    strcat(str, "/clearwarns\tClear warning pemain\n");
                    strcat(str, "/saveall\tSave semua akaun pemain\n");
                    strcat(str, "/setinventory\tSet kapasiti inventory pemain\n");
                    strcat(str, "/creategraffiti\tBuat graffiti\n");
                    strcat(str, "/destroygraffiti\tBuang graffiti\n");
                    strcat(str, "/destroyplant\tBuang plant\n");
                    strcat(str, "/givecar\tBeri kenderaan\n");
                    strcat(str, "/destroycar\tBuang kenderaan\n");
                    strcat(str, "/createrent\tBuat rent\n");
                    strcat(str, "/destroyrent\tBuang rent\n");
                    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Admin Level 2 Commands", str, "Tutup", "");
                }
            }
            case 2:
            {
                if (PlayerData[playerid][pAdmin] >= 3) 
                {
                    new str[9500];
                    strcat(str, "Command\tPerincian\n/od\tSilent onduty/ offduty\n");
                    strcat(str, "/panel\tPanel server\n");
                    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Admin Level 3 Commands", str, "Tutup", "");
                }
            }
        }
    }
    return 1;
}

Dialog:MainPhone(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				ShowContacts(playerid);
			}
			case 1:
			{
				Dialog_Show(playerid, DialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");
			}
			case 2:
			{
				Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");
			}
			case 3:
			{
				static
					string[MAX_PLAYER_TICKETS * 64], header[512];

				header = "";
				strcat(header,"Reason\tFee\tDate\n",sizeof(header));

				string[0] = 0;

				for (new i = 0; i < MAX_PLAYER_TICKETS; i ++)
				{
					if (TicketData[playerid][i][ticketExists])
					{
						format(string, sizeof(string), "%s%s\t"GREEN_E"%s\t"WHITE_E"%s\n", string, TicketData[playerid][i][ticketReason], FormatNumber(TicketData[playerid][i][ticketFee]), TicketData[playerid][i][ticketDate]);
					}
					else 
					{
						format(string, sizeof(string), "%sEmpty Slot\n", string);
					}
				}
				strcat(header, string);
				Dialog_Show(playerid, MyTickets, DIALOG_STYLE_TABLIST_HEADERS, "My Tickets", header, "Pay", "Back");
			}
			case 4:
			{
				Dialog_Show(playerid, PhoneBank, DIALOG_STYLE_LIST, "Bank", "Check Balance\nMake A Transfer", "Select", "Back");
			}
		}
	}
	return 1;
}

Dialog:LockerLeader(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new factionid = PlayerData[playerid][pFaction]; 
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_Show(playerid, FactionMoney, DIALOG_STYLE_LIST, "Faction Money", "Withdraw Money\nDeposit Money", "Select", "Back");
			}
			case 1:
			{
				Faction_ShowRanks(playerid, factionid);
			}
	    }
	}
	return 1;
}

Dialog:FactionMoney(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new factionid = PlayerData[playerid][pFaction]; 
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_Show(playerid, FactionMoneyWithdraw, DIALOG_STYLE_INPUT, "Faction Money > Withdraw Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(FactionData[factionid][factionMoney]));
			}
	        case 1:
	        {
				Dialog_Show(playerid, FactionMoneyDeposit, DIALOG_STYLE_INPUT, "Faction Money > Deposit Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(FactionData[factionid][factionMoney]));
			}
	    }
	}
	else {
		Dialog_Show(playerid, LockerLeader, DIALOG_STYLE_LIST, "Leader Faction Locker", "Faction Money\nManage Rank", "Select", "Cancel");
	}
	return 1;
}

Dialog:FactionMoneyWithdraw(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new factionid = PlayerData[playerid][pFaction];
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionMoneyWithdraw, DIALOG_STYLE_INPUT, "Faction Money > Withdraw Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(FactionData[factionid][factionMoney]));

		if (amount < 1 || amount > FactionData[factionid][factionMoney])
			return Dialog_Show(playerid, FactionMoneyWithdraw, DIALOG_STYLE_INPUT, "Faction Money > Withdraw Money", "Error: Insufficient funds!\n\nYour faction bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(FactionData[factionid][factionMoney]));

		FactionData[factionid][factionMoney] -= amount;
	    GiveMoney(playerid, amount);

	    SendServerMessage(playerid, "You have withdrawn %s from your faction bank account.", FormatNumber(amount));
		Faction_Save(factionid);
        Dialog_Show(playerid, FactionMoneyWithdraw, DIALOG_STYLE_INPUT, "Faction Money > Withdraw Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(FactionData[factionid][factionMoney]));
	}
	else {
	    Dialog_Show(playerid, FactionMoney, DIALOG_STYLE_LIST, "Faction Money", "Withdraw Money\nDeposit Money", "Select", "Back");
	}
	return 1;
}

Dialog:FactionMoneyDeposit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new factionid = PlayerData[playerid][pFaction];
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionMoneyDeposit, DIALOG_STYLE_INPUT, "Faction Money > Deposit Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(FactionData[factionid][factionMoney]));

		if (amount < 1 || amount > GetMoney(playerid))
			return Dialog_Show(playerid, FactionMoneyDeposit, DIALOG_STYLE_INPUT, "Faction Money > Deposit Money", "Error: You don't have that much.\n\nYour faction bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(FactionData[factionid][factionMoney]));

		FactionData[factionid][factionMoney] += amount;
	    GiveMoney(playerid, -amount);

	    SendServerMessage(playerid, "You have deposited %s into your faction bank account.", FormatNumber(amount));
		Faction_Save(factionid);
        Dialog_Show(playerid, FactionMoneyDeposit, DIALOG_STYLE_INPUT, "Faction Money > Deposit Money", "Your faction bank account's balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(FactionData[factionid][factionMoney]));
	}
	else {
	    Dialog_Show(playerid, FactionMoney, DIALOG_STYLE_LIST, "Faction Money", "Withdraw Money\nDeposit Money", "Select", "Back");
	}
	return 1;
}

Dialog:BusinessManage(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));

		switch(listitem)
		{
			case 0:
			{
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""WHITE_E"Business Info", ""WHITE_E"Business ID: "YELLOW_E"%d\n"WHITE_E"Business Name: "YELLOW_E"%s\n"WHITE_E"Business Product: "YELLOW_E"%d product\n"WHITE_E"Business Vault: "YELLOW_E"%s", "Close", "", id, BusinessData[id][bizName], BusinessData[id][bizProducts], FormatNumber(BusinessData[id][bizVault]));
			}
			case 1:
			{
				Dialog_Show(playerid, SetBizName, DIALOG_STYLE_INPUT, "Manage Biz > Set Name", "Masukkan nama business yang ingin ditukar:", "Enter", "Cancel");
			}
			case 2:
			{
				Dialog_Show(playerid, SetBizWM, DIALOG_STYLE_INPUT, "Manage Biz > Set Welcome Message", "Masukkan \"None\" untuk disable.\n\nMasukkan teks yang ingin di set:", "Enter", "Cancel");
			}
			case 3:
			{
				if (BusinessData[id][bizType] == 5)
					return SendErrorMessage(playerid, "You can't request shipment for this business type.");

				if (BusinessData[id][bizShipment])
				{
					foreach (new i : Player) if (PlayerData[i][pShipment] == id)
					{
						CancelShipment(i);
						SendServerMessage(i, "The shipment request has been cancelled.");
					}
					BusinessData[id][bizShipment] = 0;
					Business_Save(id);

					SendServerMessage(playerid, "Your business is no longer requesting a shipment.");
					SendJobMessage(1, COLOR_YELLOW, "** %s is no longer requesting a shipment for %s. **", ReturnName(playerid, 0), BusinessData[id][bizName]);
				}
				else
				{
					if (BusinessData[id][bizDeliver][0] == 0.0 && BusinessData[id][bizDeliver][1] == 0.0 && BusinessData[id][bizDeliver][2] == 0.0)
						return SendErrorMessage(playerid, "The delivery point for your business is not set.");

					BusinessData[id][bizShipment] = 1;
					Business_Save(id);

					SendServerMessage(playerid, "Your have requested a shipment for your business.");
					SendJobMessage(1, COLOR_YELLOW, "** %s is requesting a shipment for %s (/shipments to accept). **", ReturnName(playerid, 0), BusinessData[id][bizName]);
				}
			}
			case 4:
			{
				Business_ProductMenu(playerid, id);
			}
			case 5:
			{
				Dialog_Show(playerid, BizVault, DIALOG_STYLE_LIST, "Mange Biz > Vault", "Withdraw Money\nDeposit Money", "Select", "Back");
			}
		}
	}
	return 1;
}

Dialog:SetBizName(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));
		
	    if (isnull(inputtext)) return Dialog_Show(playerid, SetBizName, DIALOG_STYLE_INPUT, "Manage Biz > Set Name", "Masukkan nama business yang ingin ditukar:", "Enter", "Cancel");

		if (strlen(inputtext) > 32) return Dialog_Show(playerid, SetBizName, DIALOG_STYLE_INPUT, "Manage Biz > Set Name", "Ralat: The business name can't exceed 32 characters.\n\nMasukkan nama business yang ingin ditukar:", "Enter", "Cancel");
			
		format(BusinessData[id][bizName], 32, inputtext);

		Business_Refresh(id);
		Business_Save(id);

		SendServerMessage(playerid, "Business name set to: \"%s\".", inputtext);
	}
	return 1;
}

Dialog:SetBizWM(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));

	    if (isnull(inputtext)) return Dialog_Show(playerid, SetBizWM, DIALOG_STYLE_INPUT, "Manage Biz > Set Welcome Message", "Masukkan \"None\" untuk disable.\n\nMasukkan teks yang ingin di set:", "Enter", "Cancel");

		if (!strcmp(inputtext, "none", true))
		{
		    BusinessData[id][bizMessage][0] = '\0';

			Business_Save(id);
			SendServerMessage(playerid, "You have removed the business message.");
		}
		else
		{
			format(BusinessData[id][bizMessage], 128, inputtext);

			Business_Save(id);
			SendServerMessage(playerid, "Business message set to: \"%s\".", inputtext);
		}
	}
	return 1;
}

Dialog:BizVault(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));
	    switch (listitem)
	    {
	        case 0:
	        {
				Dialog_Show(playerid, BizVaultWithDraw, DIALOG_STYLE_INPUT, "Biz Vault > Withdraw Money", "Your business vault balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(BusinessData[id][bizVault]));
			}
	        case 1:
	        {
				Dialog_Show(playerid, BizVaultDeposit, DIALOG_STYLE_INPUT, "Biz Vault  > Deposit Money", "Your business vault balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(BusinessData[id][bizVault]));
			}
	    }
	}
	return 1;
}

Dialog:BizVaultWithDraw(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, BizVaultWithDraw, DIALOG_STYLE_INPUT, "Biz Vault > Withdraw Money", "Your business vault balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(BusinessData[id][bizVault]));

		if (amount < 1 || amount > BusinessData[id][bizVault])
			return Dialog_Show(playerid, BizVaultWithDraw, DIALOG_STYLE_INPUT, "Biz Vault > Withdraw Money", "Error: Insufficient funds!\n\nYour business vault balance: %s\n\nPlease enter the amount of money you wish to withdraw:", "Withdraw", "Back", FormatNumber(BusinessData[id][bizVault]));

		BusinessData[id][bizVault] -= amount;
	    GiveMoney(playerid, amount);

	    SendServerMessage(playerid, "You have withdrawn %s from your business vault.", FormatNumber(amount));
		Business_Save(id);
	}
	return 1;
}

Dialog:BizVaultDeposit(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid));
	    new amount = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, BizVaultDeposit, DIALOG_STYLE_INPUT, "Biz Vault  > Deposit Money", "Your business vault balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(BusinessData[id][bizVault]));

		if (amount < 1 || amount > GetMoney(playerid))
			return Dialog_Show(playerid, BizVaultDeposit, DIALOG_STYLE_INPUT, "Biz Vault > Deposit Money", "Error: You don't have that much.\n\nYour business vault balance: %s\n\nPlease enter the amount of money you wish to deposit:", "Deposit", "Back", FormatNumber(BusinessData[id][bizVault]));

		BusinessData[id][bizVault] += amount;
	    GiveMoney(playerid, -amount);

	    SendServerMessage(playerid, "You have deposited %s into your business vault.", FormatNumber(amount));
		Business_Save(id);
	}
	return 1;
}

Dialog:TuneVehicle(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to change the vehicle color.");
			Dialog_Show(playerid,TuneColor,DIALOG_STYLE_LIST,"Colors","Use pre-made colors\nEnter manually","confirm","back");
		}
		if(listitem == 1)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add paintjob on this vehicle.");
			Dialog_Show(playerid,TunePaintjob, DIALOG_STYLE_LIST,"Choose paint job","paint job1\npaint job2\npaint job3\n","Confirm","back");
		}
		if(listitem == 2)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add spoiler on this vehicle.");
			Dialog_Show(playerid,TuneSpoiler,DIALOG_STYLE_LIST,"Choose below","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n","Choose","back");
		}
		if(listitem == 3)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add hood on this vehicle.");
			Dialog_Show(playerid, TuneHood, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
		}
		if(listitem == 4)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add vents on this vehicle.");
			Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n", "Confirm", "back");
		}
		if(listitem == 5)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add lights on this vehicle.");
			Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n", "Confirm", "back");
		}
		if(listitem == 6)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add exhaust on this vehicle.");
			Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust", "Confirm", "back");
		}
		if(listitem == 7)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add front bumpers on this vehicle.");
			Dialog_Show(playerid, TuneFrontBumper, DIALOG_STYLE_LIST, "Front bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
		}
		if(listitem == 8)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add rear bumpers on this vehicle.");
			Dialog_Show(playerid, TuneRearBumper, DIALOG_STYLE_LIST, "Rear bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
		}
		if(listitem == 9)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add roofs on this vehicle.");
			Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop", "Confirm", "back");
		}
		if(listitem == 10)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add sideskirts on this vehicle.");
			Dialog_Show(playerid, TuneSideSkirt, DIALOG_STYLE_LIST, "Side skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt", "Confirm", "back");
		}
		if(listitem == 11)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add bullbars on this vehicle.");
			Dialog_Show(playerid, TuneBullbar, DIALOG_STYLE_LIST, "Bull bars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
		}
		if(listitem == 12)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add wheels on this vehicle.");
			Dialog_Show(playerid, TuneWheel, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar", "Confirm", "back");
		}
		if(listitem == 13)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add stereo on this vehicle.");
			Dialog_Show(playerid, TuneStereo, DIALOG_STYLE_LIST, "Car Stereo", "BassBoost", "Confirm", "Close");
		}
		if(listitem == 14)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add hydraulics on this vehicle.");
			Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Car hydraulics", "Hydaulics", "Confirm", "back");
		}
		if(listitem == 15)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to add nitros.");
			new vehicleid = GetPlayerVehicleID(playerid);
			AddComponent(vehicleid, 1010);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Nitros has been added to the %s.",ReturnVehicleName(vehicleid));
			Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
		}
		if(listitem == 16)
		{
			if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendErrorMessage(playerid, "You need to be in vehicle to fix your vehicle.");
			new vehicleid = GetPlayerVehicleID(playerid);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			RepairVehicle(vehicleid);
			RepairVehicle(vehicleid);
			SetVehicleHealth(vehicleid, 1000);
			SendServerMessage(playerid,"%s is fixed.",ReturnVehicleName(vehicleid));
			Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
		}
	}
	return 1;
}
Dialog:TuneColor(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 1)
		{
			Dialog_Show(playerid,TuneColorManual1,DIALOG_STYLE_INPUT,"color1","Enter color1 (between 0 - 255)","confirm","back");
		}
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneColorPremade(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,1,1);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to White.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 1)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,0,0);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Black.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 2)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,3,3);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Red.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 3)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,128,128);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Green.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 4)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,6,6);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Yellow.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 5)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,79,79);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Blue.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 6)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,126,126);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Pink.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
		if(listitem == 7)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleColor(vehicleid,30,30);
			PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			SendServerMessage(playerid,"Vehicle color changed to Brown.");
			Dialog_Show(playerid,TuneColorPremade,DIALOG_STYLE_LIST,"choose the color","White\nBlack\nRed\nGreen\nYellow\nBlue\nPink\nBrown","confirm","back");
		}
	}
	else
	{
		Dialog_Show(playerid,TuneColor,DIALOG_STYLE_LIST,"Colors","Use pre-made colors\nEnter manually","confirm","back");
	}
	return 1;
}
Dialog:TuneColorManual1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strval(inputtext) < 0 || strval(inputtext) > 255) return Dialog_Show(playerid,TuneColorManual1,DIALOG_STYLE_INPUT,"color1","Enter correct value of color1 (between 0 - 255)","confirm","back");
		Dialog_Show(playerid,TuneColorManual2,DIALOG_STYLE_INPUT,"color2","Enter color2 (between 0 - 255)","confirm","back");
		PlayerData[playerid][pCarColor1] = strval(inputtext);
	}
	else
	{
		Dialog_Show(playerid,TuneColor,DIALOG_STYLE_LIST,"Colors","Use pre-made colors\nEnter manually","confirm","back");
	}
	return 1;
}
Dialog:TuneColorManual2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strval(inputtext) < 0 || strval(inputtext) > 255) return Dialog_Show(playerid,TuneColorManual1,DIALOG_STYLE_INPUT,"color2","Enter correct value of color2 (between 0 - 255)","confirm","back");
		PlayerData[playerid][pCarColor2] = strval(inputtext);
		new vehicleid = GetPlayerVehicleID(playerid);
		SetVehicleColor(vehicleid,PlayerData[playerid][pCarColor1],PlayerData[playerid][pCarColor2]);
		SendServerMessage(playerid, "Color changed. color1: %d color2: %d.",PlayerData[playerid][pCarColor1],PlayerData[playerid][pCarColor2]);
	}
	else
	{
		Dialog_Show(playerid,TuneColorManual1,DIALOG_STYLE_INPUT,"color1","Enter color1 (between 0 - 255)","confirm","back");
	}
	return 1;
}
Dialog:TuneSpoiler(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Wheel Arc. Alien Spoiler");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1147);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1049);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1162);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1058);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1138);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1164);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 1)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Wheel Arc. X-Flow Spoiler");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1146);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1050);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1158);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1060);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1139);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1163);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 2)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Win Spoiler");
			if(VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 527 ||
			VehicleModel == 415 ||
			VehicleModel == 546 ||
			VehicleModel == 603 ||
			VehicleModel == 426 ||
			VehicleModel == 436 ||
			VehicleModel == 405 ||
			VehicleModel == 477 ||
			VehicleModel == 580 ||
			VehicleModel == 550 ||
			VehicleModel == 549)
			{
				if(VehicleModel == 401)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 518)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 527)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 415)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 546)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 603)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 426)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 436)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 405)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 477)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 580)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 550)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 549)
				{
					AddComponent(vehicleid,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [401,518,527,415,546,603,426,436,405,477,580,550,549]");
			}
		}
		if(listitem == 3)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Fury Spoiler");
			if(VehicleModel == 518 ||
			VehicleModel == 415 ||
			VehicleModel == 546 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 405 ||
			VehicleModel == 477 ||
			VehicleModel == 580 ||
			VehicleModel == 550 ||
			VehicleModel == 549)
			{
				if(VehicleModel == 518)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 415)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 546)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 517)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 603)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 405)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 477)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 580)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 550)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 549)
				{
					AddComponent(vehicleid,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [518,415,546,517,603,405,477,580,550,549]");
			}
		}
		if(listitem == 4)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256," Transfender Alpha Spoiler ");
			if(VehicleModel == 518 ||
			VehicleModel == 415 ||
			VehicleModel == 401 ||
			VehicleModel == 517 ||
			VehicleModel == 426 ||
			VehicleModel == 436 ||
			VehicleModel == 477 ||
			VehicleModel == 547 ||
			VehicleModel == 550 ||
			VehicleModel == 549)
			{
				if(VehicleModel == 518)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 415)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 401)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 517)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 426)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 436)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 477)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 547)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 550)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 549)
				{
					AddComponent(vehicleid,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [518,415,401,517,426,436,477,547,550,549]");
			}
		}
		if(listitem == 5)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Pro Spoiler");
			if(VehicleModel == 589 ||
			VehicleModel == 492 ||
			VehicleModel == 547 ||
			VehicleModel == 405)
			{
				if(VehicleModel == 589)
				{
					AddComponent(vehicleid,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 492)
				{
					AddComponent(vehicleid,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the {FFFFFF}%s",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 547)
				{
					AddComponent(vehicleid,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 405)
				{
					AddComponent(vehicleid,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [589,492,547,405]");
			}
		}
		if(listitem == 6)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Champ Spoiler");
			if(VehicleModel == 527 ||
			VehicleModel == 542 ||
			VehicleModel == 405)
			{
				if(VehicleModel == 527)
				{
					AddComponent(vehicleid,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 542)
				{
					AddComponent(vehicleid,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 405)
				{
					AddComponent(vehicleid,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [405,542,527]");
			}
		}
		if(listitem == 7)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Race Spoiler");
			if(VehicleModel == 527 ||
			VehicleModel == 542)
			{
				if(VehicleModel == 527)
				{
					AddComponent(vehicleid,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 542)
				{
					AddComponent(vehicleid,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [542,527]");
			}
		}
		if(listitem == 8)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new SpoilerName[256];
			format(SpoilerName,256,"Transfender Drag Spoiler");
			if(VehicleModel == 546 ||
			VehicleModel == 517)
			{
				if(VehicleModel == 546)
				{
					AddComponent(vehicleid,1002);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 517)
				{
					AddComponent(vehicleid,1002);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"%s added to the %s.",SpoilerName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this spoiler to this vehicle. Available on vehicle [546,517]");
			}
		}
		Dialog_Show(playerid,TuneSpoiler,DIALOG_STYLE_LIST,"Choose below","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n","Choose","back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TunePaintjob(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 560 ||
			VehicleModel == 575 ||
			VehicleModel == 534 || 
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 535 ||
			VehicleModel == 576 ||
			VehicleModel == 558)
			{
				SetVehiclePaintjob(vehicleid,0);
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully applied paint job 1 to the %s.",ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot apply this paint job to this vehicle. Available on vehicle [562,565,559,561,560,575,534,567,536,535,576,558]");
			}
		}
		if(listitem == 1)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 560 ||
			VehicleModel == 575 ||
			VehicleModel == 534 || 
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 535 ||
			VehicleModel == 576 ||
			VehicleModel == 558)
			{
				SetVehiclePaintjob(vehicleid,1);
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully applied paint job 2 to the %s.",ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot apply this paint job to this vehicle. Available on vehicle [562,565,559,561,560,575,534,567,536,535,576,558]");
			}
		}
		if(listitem == 2)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 560 ||
			VehicleModel == 575 ||
			VehicleModel == 534 || 
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 535 ||
			VehicleModel == 576 ||
			VehicleModel == 558)
			{
				SetVehiclePaintjob(vehicleid,2);
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully applied paint job 3 to the %s.",ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot apply this paint job to this vehicle. Available on vehicle [562,565,559,561,560,575,534,567,536,535,576,558]");
			}
		}
		Dialog_Show(playerid,TunePaintjob, DIALOG_STYLE_LIST,"Choose paint job","paint job1\npaint job2\npaint job3\n","Confirm","back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneHood(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(listitem == 0)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new HoodName[256];
			format(HoodName,255,"Fury");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 589 ||
			VehicleModel == 492 ||
			VehicleModel == 426 ||
			VehicleModel == 550)
			{
				AddComponent(vehicleid,1005);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added hood %s to the %s",HoodName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this hood to this vehicle. Available on vehicle [401,518,589,492,426,550]");
			}
		}
		if(listitem == 1)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new HoodName[256];
			format(HoodName,255,"Champ");
			if(
			VehicleModel == 401 ||
			VehicleModel == 402 ||
			VehicleModel == 546 ||
			VehicleModel == 426 ||
			VehicleModel == 550)
			{
				AddComponent(vehicleid,1004);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added hood %s to the %s",HoodName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this hood to this vehicle. Available on vehicle [401,402,546,426,550]");
			}
		}
		if(listitem == 2)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new HoodName[256];
			format(HoodName,255,"Race");
			if(VehicleModel == 401)
			{
				AddComponent(vehicleid,1011);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added hood %s to the %s",HoodName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this hood to this vehicle. Available on vehicle [401]");
			}
		}
		if(listitem == 3)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new VehicleModel = GetVehicleModel(vehicleid);
			new HoodName[256];
			format(HoodName,255,"Worx");
			if(VehicleModel == 549)
			{
				AddComponent(vehicleid,1012);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added hood %s to the %s",HoodName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this hood to this vehicle. Available on vehicle [401]");
			}
		}
		Dialog_Show(playerid, TuneHood, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneVents(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new VentName[256];
			format(VentName,255,"Oval");
			if(VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 546 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 547 ||
			VehicleModel == 439 ||
			VehicleModel == 550 ||
			VehicleModel == 549)
			{
				AddComponent(vehicleid,1142);
				AddComponent(vehicleid,1143);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added vent %s to the %s",VentName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Vent to this vehicle. Available on vehicle [401,518,546,517,603,547,439,550,549]");
			}
		}
		if(listitem == 1)
		{
			new VentName[256];
			format(VentName,255,"Square");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 589 ||
			VehicleModel == 546 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 439 ||
			VehicleModel == 550 ||
			VehicleModel == 549)
			{
				AddComponent(vehicleid,1144);
				AddComponent(vehicleid,1145);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added vent %s to the %s",VentName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Vent to this vehicle. Available on vehicle [401,518,589,546,517,603,439,550,549]");
			}
		}
		Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneLight(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new LightName[256];
			format(LightName,255,"Round");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 589 ||
			VehicleModel == 400 ||
			VehicleModel == 436 ||
			VehicleModel == 439)
			{
				AddComponent(vehicleid,1013);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added Light %s to the %s",LightName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Light to this vehicle. Available on vehicle [401,518,589,400,436,439]");
			}
		}
		if(listitem == 1)
		{
			new LightName[256];
			format(LightName,255,"Square");
			if(
			VehicleModel == 589 ||
			VehicleModel == 603 ||
			VehicleModel == 400)
			{
				AddComponent(vehicleid,1024);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added Light %s to the %s",LightName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Light to this vehicle. Available on vehicle [589,603,400]");
			}
		}
		Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
}
Dialog:TuneExhaust(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Wheel Arc. Alien exhaust");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 558 ||
			VehicleModel == 561 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1034);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1046);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1065);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1064);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1028);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1089);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [562,565,559,558,561,560]");
			}
		}
		if(listitem == 1)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Wheel Arc. X-Flow exhaust");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1037);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1045);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1066);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1059);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1029);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1092);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [562,565,559,558,561,560]");
			}
		}
		if(listitem == 2)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Low Co. Chromer exhaust");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1044);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1126);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1129);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1104);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1113);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1136);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [575,534,567,536,576,535]");
			}
		}
		if(listitem == 3)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Low Co. Slamin exhaust");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1043);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1127);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1132);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1105);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1114);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1135);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [575,534,567,536,576,535]");
			}
		}
		if(listitem == 4)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Transfender Large exhaust");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 527 ||
			VehicleModel == 542 ||
			VehicleModel == 589 ||
			VehicleModel == 400 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 426 ||
			VehicleModel == 547 ||
			VehicleModel == 405 ||
			VehicleModel == 580 ||
			VehicleModel == 550 ||
			VehicleModel == 549 ||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1020);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [401,518,527,542,589,400,517,603,426,547,405,580,550,549,477]");
			}
		}
		if(listitem == 5)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Transfender Medium exhaust");
			if(
			VehicleModel == 527 ||
			VehicleModel == 542 ||
			VehicleModel == 400 ||
			VehicleModel == 426 ||
			VehicleModel == 436 ||
			VehicleModel == 547 ||
			VehicleModel == 405 ||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1021);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [527,542,400,426,436,547,405,477]");
			}
		}
		if(listitem == 6)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Transfender Small exhaust");
			if(VehicleModel == 436)
			{
				AddComponent(vehicleid,1022);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [436]");
			}
		}
		if(listitem == 7)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Transfender Twin exhaust");
			if(
			VehicleModel == 518 ||
			VehicleModel == 415 ||
			VehicleModel == 542 ||
			VehicleModel == 546 ||
			VehicleModel == 400 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 426 ||
			VehicleModel == 436 ||
			VehicleModel == 547 ||
			VehicleModel == 405 ||
			VehicleModel == 550 ||
			VehicleModel == 549 ||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1019);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [518,415,542,546,400,517,603,426,436,547,405,550,549,477]");
			}
		}
		if(listitem == 8)
		{
			new ExhaustName[256];
			format(ExhaustName,255,"Transfender Upswept exhaust");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 415 ||
			VehicleModel == 542 ||
			VehicleModel == 546 ||
			VehicleModel == 400 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 426 ||
			VehicleModel == 415 ||
			VehicleModel == 547 ||
			VehicleModel == 405 ||
			VehicleModel == 550 ||
			VehicleModel == 549 ||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1018);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",ExhaustName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Exhaust to this vehicle. Available on vehicle [401,518,415,542,546,400,517,603,426,415,547,405,550,549,477]");
			}
		}
		Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneFrontBumper(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new BumperName[256];
			format(BumperName,256,"Wheel Arc. Alien Bumper");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1171);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1153);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1160);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1155);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1169);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1166);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 1)
		{
			new BumperName[256];
			format(BumperName,256,"Wheel Arc. X-Flow Bumper");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1172);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1152);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1173);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1157);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1170);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1165);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 2)
		{
			new BumperName[256];
			format(BumperName,256,"Low co. Chromer Bumper");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1174);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1179);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1189);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1182);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1115);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1191);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [567,535,575,534,576,536]");
			}
		}
		if(listitem == 3)
		{
			new BumperName[256];
			format(BumperName,256,"Low co. Slamin Bumper");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1175);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1185);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1188);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1181);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1116);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1190);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [567,535,575,534,576,536]");
			}
		}
		Dialog_Show(playerid, TuneFrontBumper, DIALOG_STYLE_LIST, "Front bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneRearBumper(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new BumperName[256];
			format(BumperName,256,"Wheel Arc. Alien Bumper");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1149);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1150);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1159);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1154);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1141);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1168);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 1)
		{
			new BumperName[256];
			format(BumperName,256,"Wheel Arc. X-Flow Bumper");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1148);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1151);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1161);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1156);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1140);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1167);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 2)
		{
			new BumperName[256];
			format(BumperName,256,"Low co. Chromer Bumper");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1176);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1180);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1187);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1184);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1109);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1192);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [567,535,575,534,576,536]");
			}
		}
		if(listitem == 3)
		{
			new BumperName[256];
			format(BumperName,256,"Low co. Slamin Bumper");
			if(VehicleModel == 575 ||
			VehicleModel == 534 ||
			VehicleModel == 567 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 535)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1177);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 534)
				{
					AddComponent(vehicleid,1178);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1186);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1183);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 535)
				{
					AddComponent(vehicleid,1110);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1193);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",BumperName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bumper to this vehicle. Available on vehicle [567,535,575,534,576,536]");
			}
		}
		Dialog_Show(playerid, TuneRearBumper, DIALOG_STYLE_LIST, "Rear bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneHydraulic(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(listitem == 0)
		{
			new StereoName[256];
			format(StereoName,256,"Hydraulics");
			SendServerMessage(playerid,"You have successfully added %s to the %s",StereoName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1087);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Car hydraulics", "Hydaulics", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneStereo(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(listitem == 0)
		{
			new StereoName[256];
			format(StereoName,256,"BassBoost Stereo");
			SendServerMessage(playerid,"You have successfully added %s to the %s",StereoName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1086);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		Dialog_Show(playerid, TuneStereo, DIALOG_STYLE_LIST, "Car Stereo", "BassBoost", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneWheel(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(listitem == 0)
		{
			new WheelName[256];
			format(WheelName,256,"Offroad wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1025);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 1)
		{
			new WheelName[256];
			format(WheelName,256,"Mega wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1074);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 2)
		{
			new WheelName[256];
			format(WheelName,256,"Wires wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1076);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 3)
		{
			new WheelName[256];
			format(WheelName,256,"Twist wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1078);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 4)
		{
			new WheelName[256];
			format(WheelName,256,"Grove wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1081);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 5)
		{
			new WheelName[256];
			format(WheelName,256,"Import wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1082);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 6)
		{
			new WheelName[256];
			format(WheelName,256,"Atomic wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1085);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 7)
		{
			new WheelName[256];
			format(WheelName,256,"Ahab wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1096);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 8)
		{
			new WheelName[256];
			format(WheelName,256,"Virtual wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1097);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 9)
		{
			new WheelName[256];
			format(WheelName,256,"Access wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1098);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 10)
		{
			new WheelName[256];
			format(WheelName,256,"Trance wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1084);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 11)
		{
			new WheelName[256];
			format(WheelName,256,"Shadow wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1073);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 12)
		{
			new WheelName[256];
			format(WheelName,256,"Rimishine wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1075);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 13)
		{
			new WheelName[256];
			format(WheelName,256,"Classic wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1077);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 14)
		{
			new WheelName[256];
			format(WheelName,256,"Cutter wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1079);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 15)
		{
			new WheelName[256];
			format(WheelName,256,"Switch wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1080);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		if(listitem == 16)
		{
			new WheelName[256];
			format(WheelName,256,"Dollar wheels");
			SendServerMessage(playerid,"You have successfully added %s to the %s",WheelName,ReturnVehicleName(vehicleid));
			AddComponent(vehicleid,1083);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		Dialog_Show(playerid, TuneWheel, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneBullbar(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new BullBarName[256];
			format(BullBarName,256,"Locos Chrome Grill bar");
			if(VehicleModel == 534)
			{
				AddComponent(vehicleid,1100);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",BullBarName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bull bars to this vehicle. Available on vehicle [534]");
			}
		}
		if(listitem == 1)
		{
			new BullBarName[256];
			format(BullBarName,256,"Locos Chrome bar");
			if(VehicleModel == 534)
			{
				AddComponent(vehicleid,1123);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",BullBarName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bull bars to this vehicle. Available on vehicle [534]");
			}
		}
		if(listitem == 2)
		{
			new BullBarName[256];
			format(BullBarName,256,"Locos Chrome Lights bar");
			if(VehicleModel == 534)
			{
				AddComponent(vehicleid,1125);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",BullBarName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bull bars to this vehicle. Available on vehicle [534]");
			}
		}
		if(listitem == 3)
		{
			new BullBarName[256];
			format(BullBarName,256,"Locos Chrome bullbar");
			if(VehicleModel == 535)
			{
				AddComponent(vehicleid,1117);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",BullBarName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Bull bars to this vehicle. Available on vehicle [535]");
			}
		}
		Dialog_Show(playerid, TuneBullbar, DIALOG_STYLE_LIST, "Bull bars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","Close");
	}
	return 1;
}
Dialog:TuneSideSkirt(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new SkirtName[256];
			format(SkirtName,256,"Wheel Arc. Alien Side Skirt");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1036);
					AddComponent(vehicleid,1040);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1047);
					AddComponent(vehicleid,1051);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1069);
					AddComponent(vehicleid,1071);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1056);
					AddComponent(vehicleid,1062);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1026);
					AddComponent(vehicleid,1027);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1090);
					AddComponent(vehicleid,1094);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 1)
		{
			new SkirtName[256];
			format(SkirtName,256,"Wheel Arc. X-Flow Side Skirt");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1039);
					AddComponent(vehicleid,1041);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1048);
					AddComponent(vehicleid,1052);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1070);
					AddComponent(vehicleid,1072);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1057);
					AddComponent(vehicleid,1063);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1031);
					AddComponent(vehicleid,1030);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1093);
					AddComponent(vehicleid,1095);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [562,565,559,561,558,560]");
			}
		}
		if(listitem == 2)
		{
			new SkirtName[256];
			format(SkirtName,256,"Locos Chrome Strip Skirt");
			if(VehicleModel == 575 ||
			VehicleModel == 536 ||
			VehicleModel == 576 ||
			VehicleModel == 567)
			{
				if(VehicleModel == 575)
				{
					AddComponent(vehicleid,1042);
					AddComponent(vehicleid,1099);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1102);
					AddComponent(vehicleid,1133);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 576)
				{
					AddComponent(vehicleid,1134);
					AddComponent(vehicleid,1137);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1108);
					AddComponent(vehicleid,1107);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [575,536,576,567]");
			}
		}
		if(listitem == 3)
		{
			new SkirtName[256];
			format(SkirtName,256,"Locos Chrome Flames Skirt");
			if(VehicleModel == 534)
			{
				AddComponent(vehicleid,1102);
				AddComponent(vehicleid,1101);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [534]");
			}
		}
		if(listitem == 4)
		{
			new SkirtName[256];
			format(SkirtName,256,"Locos Chrome Arches Skirt");
			if(VehicleModel == 534)
			{
				AddComponent(vehicleid,1106);
				AddComponent(vehicleid,1124);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [534]");
			}
		}
		if(listitem == 5)
		{
			new SkirtName[256];
			format(SkirtName,256,"Locos Chrome Trim Skirt");
			if(VehicleModel == 535)
			{
				AddComponent(vehicleid,1118);
				AddComponent(vehicleid,1120);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [535]");
			}
		}
		if(listitem == 6)
		{
			new SkirtName[256];
			format(SkirtName,256,"Locos Wheelcovers Skirt");
			if(VehicleModel == 535)
			{
				AddComponent(vehicleid,1119);
				AddComponent(vehicleid,1121);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [535]");
			}
		}
		if(listitem == 7)
		{
			new SkirtName[256];
			format(SkirtName,256,"Transfender Side Skirt");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 527 ||
			VehicleModel == 415 ||
			VehicleModel == 589 ||
			VehicleModel == 546 ||
			VehicleModel == 517 ||
			VehicleModel == 603 ||
			VehicleModel == 436 ||
			VehicleModel == 439 ||
			VehicleModel == 580 ||
			VehicleModel == 549 ||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1007);
				AddComponent(vehicleid,1017);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",SkirtName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Skirts to this vehicle. Available on vehicle [401,518,527,415,589,546,517,603,436,439,580,549,477]");
			}
		}
		Dialog_Show(playerid, TuneSideSkirt, DIALOG_STYLE_LIST, "Side skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}
Dialog:TuneRoof(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new VehicleModel = GetVehicleModel(vehicleid);
		if(listitem == 0)
		{
			new RoofName[256];
			format(RoofName,256,"Wheel Arc. Alien roof");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1038);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1054);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1067);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1055);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1032);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1088);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Roofs to this vehicle. Available on vehicle [562,565,559,561,560,558]");
			}
		}
		if(listitem == 1)
		{
			new RoofName[256];
			format(RoofName,256,"Wheel Arc. X-Flow roof");
			if(VehicleModel == 562 ||
			VehicleModel == 565 ||
			VehicleModel == 559 ||
			VehicleModel == 561 ||
			VehicleModel == 558 ||
			VehicleModel == 560)
			{
				if(VehicleModel == 562)
				{
					AddComponent(vehicleid,1035);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 565)
				{
					AddComponent(vehicleid,1053);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 559)
				{
					AddComponent(vehicleid,1068);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 561)
				{
					AddComponent(vehicleid,1061);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 560)
				{
					AddComponent(vehicleid,1033);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 558)
				{
					AddComponent(vehicleid,1091);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Roofs to this vehicle. Available on vehicle [562,565,559,561,560,558]");
			}
		}
		if(listitem == 2)
		{
			new RoofName[256];
			format(RoofName,256,"Low Co. Hardtop Roof");
			if(VehicleModel == 567 ||
			VehicleModel == 536)
			{
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1130);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1128);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Roofs to this vehicle. Available on vehicle [567,536]");
			}
		}
		if(listitem == 3)
		{
			new RoofName[256];
			format(RoofName,256,"Low Co. Softtop Roof");
			if(VehicleModel == 567 ||
			VehicleModel == 536)
			{
				if(VehicleModel == 567)
				{
					AddComponent(vehicleid,1131);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
				if(VehicleModel == 536)
				{
					AddComponent(vehicleid,1103);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
				}
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Roofs to this vehicle. Available on vehicle [567,536]");
			}
		}
		if(listitem == 4)
		{
			new RoofName[256];
			format(RoofName,256,"Transfender Roof Scoop");
			if(
			VehicleModel == 401 ||
			VehicleModel == 518 ||
			VehicleModel == 589 ||
			VehicleModel == 492 ||
			VehicleModel == 546 ||
			VehicleModel == 603 ||
			VehicleModel == 426 ||
			VehicleModel == 436 ||
			VehicleModel == 580 ||
			VehicleModel == 550||
			VehicleModel == 477)
			{
				AddComponent(vehicleid,1006);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendServerMessage(playerid,"You have successfully added %s to the %s",RoofName,ReturnVehicleName(vehicleid));
			}
			else
			{
				SendErrorMessage(playerid,"You cannot add this Roofs to this vehicle. Available on vehicle [567,536]");
			}
		}
		Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop", "Confirm", "back");
	}
	else
	{
		Dialog_Show(playerid,TuneVehicle,DIALOG_STYLE_LIST,"Tune","Color\nPaint job\nSpoilers\nHood\nVents\nLights\nExhaust\nFront bumpers\nRear Bumpers\nRoofs\nSide skirts\nBullbars\nWheels\nStereo\nHydraulics\nNitros\nFix","Confirm","cancel");
	}
	return 1;
}

// --------------------------------- End Dialogs