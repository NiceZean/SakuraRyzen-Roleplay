public OnObjectMoved(objectid)
{
	return 1;
}

public OnQueryError(errorid, error[], callback[], query[], connectionHandle)
{
	foreach (new i : Player)
	{
		if (PlayerData[i][pAdmin] >= 6 && PlayerData[i][pExecute])
		{
	    	PlayerData[i][pExecute] = 0;
	    	Dialog_Show(i, ExecuteQuery, DIALOG_STYLE_INPUT, "Execute Query", "Error: \"%s\"\n\nPlease specify the MySQL query to execute below:", "Execute", "Back", error);
		}
	}
 	printf("** [MySQL]: %s", error);
	Log_Write("logs/mysql_log.txt", "[%s] %s: %s", ReturnDate(), (callback[0]) ? (callback) : ("n/a"), error);
	return 1;
}

public OnVehicleDeath(vehicleid)
{
	for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
	{
		if(vehicleid == CarData[i][carVehicle])
		{
			Car_Save(i);

			if(IsValidVehicle(CarData[i][carVehicle]))
				DestroyVehicle(CarData[i][carVehicle]);

			CarData[i][carVehicle] = 0;
			
			Car_Spawn(i);
		}
	}
	if (CoreVehicles[vehicleid][vehTemporary])
	{
	    CoreVehicles[vehicleid][vehTemporary] = false;
	    DestroyVehicle(vehicleid);
	}
	for (new i = 0; i != MAX_CRATES; i ++) if (CrateData[i][crateExists] && CrateData[i][crateVehicle] == vehicleid) {
	    Crate_Delete(i);
	}
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	SetVehicleColor(vehicleid, color1, color2);
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	SetVehiclePaintjob(vehicleid, paintjobid);
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	new
		id = Car_GetID(vehicleid),
		slot = GetVehicleComponentType(componentid);

	if (id != -1)
	{
	    CarData[id][carMods][slot] = componentid;
	    Car_Save(id);
	}
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	vehiclecallsign[vehicleid] = 0;
    if (CoreVehicles[vehicleid][vehTemporary])
	{
	    CoreVehicles[vehicleid][vehTemporary] = false;
	    DestroyVehicle(vehicleid);
	}
    for (new i = 0; i != MAX_CRATES; i ++) if (CrateData[i][crateExists] && CrateData[i][crateVehicle] == vehicleid) {
	    Crate_Delete(i);
	}
	if (IsValidObject(CoreVehicles[vehicleid][vehCrate]) && GetVehicleModel(vehicleid) == 530)
	    DestroyObject(CoreVehicles[vehicleid][vehCrate]);

	ResetVehicle(vehicleid);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	if (!success)
	{
	    foreach (new i : Player) if (!strcmp(PlayerData[i][pIP], ip, true) && PlayerData[i][pAdmin] < 2) {
	        Kick(i);
	    }
	    SendAdminAlert(COLOR_RED,  "[ADMIN]: "WHITE_E"RCON login attempt failed from \"%s\".", ip);
	    Log_Write("logs/rcon_log.txt", "[%s] RCON login attempt failed from \"%s\".", ReturnDate(), ip);
	}
	else
	{
	    foreach (new i : Player) if (!strcmp(PlayerData[i][pIP], ip, true) && PlayerData[i][pAdmin] < 2) {
	        Blacklist_Add(ip, PlayerData[i][pUsername], "Server", "Unauthorized RCON");

	        SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s was banned for logging into RCON without authorization.", ReturnName(i, 0));
	    	Log_Write("logs/rcon_log.txt", "[%s] %s (%s) was banned for an unauthorized RCON login.", ReturnDate(), ReturnName(i, 0), ip);

			break;
		}
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if (weaponid == 23 && PlayerData[playerid][pTazer] && GetFactionType(playerid) == FACTION_POLICE) {
	    PlayerPlaySoundEx(playerid, 6003);
	}
	if ((weaponid >= 22 && weaponid <= 38) && hittype == BULLET_HIT_TYPE_PLAYER && hitid != INVALID_PLAYER_ID)
	{
		if (PlayerData[hitid][pDrugUsed] == 2)
		{
		    new
				Float:damage = floatdiv(g_arrWeaponDamage[weaponid], 2),
				Float:health;

		    GetPlayerHealth(hitid, health);
		    SetPlayerHealthEx(hitid, floatsub(health, damage));

		    return 0;
		}
	}
	if(hittype == BULLET_HIT_TYPE_VEHICLE)
	{
        if(!IsVehicleOccupied(hitid)) 
		{
            new panels, doors, lights, tires, Float:health;
            GetVehicleDamageStatus(hitid, panels, doors, lights, tires);
            switch(random(3))
			{
				case 0: panels = encode_panels(1, 1, 1, 1, 3, 3, 3);
				case 1: doors = encode_doors(4, 4, 4, 4);
				case 2: lights = encode_lights(1, 1, 1, 1);
            }
            GetVehicleHealth(hitid, health);
            SetVehicleHealth(hitid, health-7);
            UpdateVehicleDamageStatus(hitid, panels, doors, lights, tires);
        }
    }
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
{
	if (PlayerData[playerid][pFirstAid])
	{
	    SendInfoMessage(playerid, "Medkit anda tiada kesan lagi kerana anda telah menerima damage.");

        PlayerData[playerid][pFirstAid] = 0;
		KillTimer(PlayerData[playerid][pAidTimer]);
	}
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
{
	if (damagedid != INVALID_PLAYER_ID)
	{
		PlayerData[damagedid][pLastShot] = playerid;
		PlayerData[damagedid][pShotTime] = gettime();

		if (PlayerData[playerid][pDrugUsed] == 4 && (weaponid >= 0 && weaponid <= 15))
		{
		    SetPlayerHealthEx(damagedid, ReturnHealth(damagedid) - 6);
		}
        if (GetFactionType(playerid) == FACTION_POLICE && PlayerData[playerid][pTazer] && PlayerData[damagedid][pStunned] < 1 && weaponid == 23)
        {
			if (GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
			    return SendErrorMessage(playerid, "Player tersebut mesti berada di lantai untuk di-stunned.");

            if (GetPlayerDistanceFromPlayer(playerid, damagedid) > 10.0)
                return SendErrorMessage(playerid, "Anda mesti berada di dekat player tersebut.");

			SendInfoMessage(damagedid, "You've been stunned by %s.", ReturnName(playerid, 0));

            PlayerData[damagedid][pStunned] = 10;
            TogglePlayerControllable(damagedid, 0);

            ApplyAnimation(damagedid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stunned %s with their tazer.", ReturnName(playerid, 0), ReturnName(damagedid, 0));
        }
        if (GetFactionType(playerid) == FACTION_POLICE && PlayerData[playerid][pBeanBag] && PlayerData[damagedid][pStunned] < 1 && weaponid == 25)
        {
			if (GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
			    return SendErrorMessage(playerid, "Player tersebut mesti berada di lantai untuk di-stunned.");

            if (GetPlayerDistanceFromPlayer(playerid, damagedid) > 10.0)
                return SendErrorMessage(playerid, "You must be closer to shoot the player.");

			SendInfoMessage(damagedid, "You've been stunned by %s.", ReturnName(playerid, 0));

            PlayerData[damagedid][pStunned] = 10;
            TogglePlayerControllable(damagedid, 0);

            ApplyAnimation(damagedid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stunned %s with their beanbag shotgun.", ReturnName(playerid, 0), ReturnName(damagedid, 0));
        }
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if (killerid != INVALID_PLAYER_ID)
	{
	    if (1 <= reason <= 46)
			Log_Write("logs/kill_log.txt", "[%s] %s has killed %s (%s).", ReturnDate(), ReturnName(killerid), ReturnName(playerid), ReturnWeaponName(reason));

		else
			Log_Write("logs/kill_log.txt", "[%s] %s has killed %s (reason %d).", ReturnDate(), ReturnName(killerid), ReturnName(playerid), reason);

		if (reason == 50 && killerid != INVALID_PLAYER_ID)
		    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has killed %s by heli-blading.", ReturnName(killerid, 0), ReturnName(playerid, 0));

        if (reason == 29 && killerid != INVALID_PLAYER_ID && GetPlayerState(killerid) == PLAYER_STATE_DRIVER)
		    SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s has killed %s by driver shooting.", ReturnName(killerid, 0), ReturnName(playerid, 0));
	}
	if(GetPVarInt(playerid, "DroneSpawned") == 1) 
	{
        SetPVarInt(playerid, "DroneSpawned", 0);
        DestroyVehicle(PoliceDrone[playerid]);
        SendInfoMessage(playerid, "Your drone was automatically shut down as you have died.");
    }
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (!IsPlayerSpawned(playerid) || PlayerData[playerid][pCuffed] || PlayerData[playerid][pInjured])
	    return 0;

    if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED && newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP))
		ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.0, 0, 1, 1, 0, 0, 1);

	if (newkeys & KEY_NO && IsPlayerSpawned(playerid))
	{
	    if (PlayerData[playerid][pJailTime] > 0)
			return SendErrorMessage(playerid, "You can't open your inventory whilst jailed.");

		if (PlayerData[playerid][pCuffed] > 0 || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY)
		    return SendErrorMessage(playerid, "You can't open your inventory at the moment.");

		OpenInventory(playerid);
	}

	if (newkeys & KEY_FIRE && PlayerData[playerid][pMining] && IsPlayerNearMine(playerid))
	{
	    if (PlayerData[playerid][pMineTime] > 0 || PlayerData[playerid][pMinedRock])
	        return 1;

		new id = Job_NearestPoint(playerid);

		if (id != -1)
		{
		    PlayerData[playerid][pMineTime] = 1;
		    SetTimerEx("MineTime", 400, false, "d", playerid);

		    if (PlayerData[playerid][pMineCount] < 5)
	    	{
	    	    PlayerData[playerid][pMineCount]++;

	        	ApplyAnimation(playerid, "BASEBALL", "null", 4.0, 0, 1, 1, 0, 0, 1);
            	ApplyAnimation(playerid, "BASEBALL", "BAT_4", 4.0, 0, 1, 1, 0, 0, 1);
			}
			else
			{
			    PlayerData[playerid][pMinedRock] = 1;
			    PlayerData[playerid][pMineCount] = 0;

			    RemovePlayerAttachedObject(playerid, 4);

			    ApplyAnimation(playerid, "BSKTBALL", "null", 4.0, 0, 1, 1, 0, 0, 1);
            	ApplyAnimation(playerid, "BSKTBALL", "BBALL_pickup", 4.0, 0, 1, 1, 0, 0, 1);

			    SetPlayerAttachedObject(playerid, 4, 2936, 5, 0.044377, 0.029049, 0.161334, 265.922912, 9.904896, 21.765972, 0.500000, 0.500000, 0.500000);
				SendServerMessage(playerid, "You have digged up a rock. Deliver it to the marker.");

				SetPlayerCheckpoint(playerid, JobData[id][jobDeliver][0], JobData[id][jobDeliver][1], JobData[id][jobDeliver][2], 2.5);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			}
	    }
	}
	else if (newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
	    static
	        string[320],
			id = -1;

		if ((id = Crate_Nearest(playerid)) != -1 && PlayerData[playerid][pCarryCrate] == -1 && !IsCrateInUse(id))
		{
		    // If the crate is within a stack, this function below
		    // will get the highest crate on the stack.

		    if ((id = Crate_Highest(id)) == -1)
		        id = Crate_Nearest(playerid);

		    ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);

            PlayerData[playerid][pCarryCrate] = id;
            SetPlayerAttachedObject(playerid, 4, 964, 1, -0.157020, 0.413313, 0.000000, 0.000000, 88.000000, 180.000000, 0.500000, 0.500000, 0.500000);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches down and picks up a crate.", ReturnName(playerid, 0));
			SendServerMessage(playerid, "You have picked up a crate. Load it in a vehicle using 'ALT'.");

			DestroyDynamicObject(CrateData[id][crateObject]);
			DestroyDynamic3DTextLabel(CrateData[id][crateText3D]);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			CrateData[id][crateObject] = INVALID_OBJECT_ID;
			return 1;
		}
		if (PlayerData[playerid][pCarryCrate] != -1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY && !PlayerData[playerid][pCrafting])
		{
		    ApplyAnimation(playerid, "CARRY", "null", 4.0, 0, 0, 0, 0, 0);
		    ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

			Crate_Drop(playerid, 1.5);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has dropped the crate.", ReturnName(playerid, 0));

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			return 1;
		}
		if (PlayerData[playerid][pLoadCrate])
		{
		    for (new i = 1; i != MAX_VEHICLES; i ++) if (IsPlayerNearBoot(playerid, i))
			{
			    if (!IsLoadableVehicle(i))
			        return SendErrorMessage(playerid, "You can't load crates into this vehicle.");

			    if (CoreVehicles[i][vehLoadType] != 0 && CoreVehicles[i][vehLoadType] != PlayerData[playerid][pLoadType])
			        return SendErrorMessage(playerid, "This vehicle is already loaded with something else.");

			    if (CoreVehicles[i][vehLoads] >= 6)
			        return SendErrorMessage(playerid, "This vehicle can only hold up to 6 crates.");

				CoreVehicles[i][vehLoads]++;
				CoreVehicles[i][vehLoadType] = PlayerData[playerid][pLoadType];

                ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s drops a crate into the back of the %s.", ReturnName(playerid, 0), ReturnVehicleName(i));

                if (CoreVehicles[i][vehLoads] == 6)
                {
                    DisablePlayerCheckpoint(playerid);

					if (PlayerData[playerid][pShipment] != -1)
					{
					    PlayerData[playerid][pDeliverShipment] = 1;

					    SendServerMessage(playerid, "You have loaded all the crates. Type /unload at the marker.");
					    SetPlayerCheckpoint(playerid, BusinessData[PlayerData[playerid][pShipment]][bizDeliver][0], BusinessData[PlayerData[playerid][pShipment]][bizDeliver][1], BusinessData[PlayerData[playerid][pShipment]][bizDeliver][2], 3.0);
					}
					else switch (PlayerData[playerid][pLoadType])
                    {
                    	case 1: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any retail store.");
                        case 2: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any electronic store.");
                        case 3: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any clothing store.");
                        case 4: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any fast food store.");
                        case 5: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any gas station.");
                        case 6: SendServerMessage(playerid, "You have loaded all the crates. Type /unload at any furniture store.");
					}
					PlayerData[playerid][pLoading] = 0;
					PlayerData[playerid][pLoadType] = 0;
                }
                PlayerData[playerid][pLoadCrate] = 0;

				RemovePlayerAttachedObject(playerid, 4);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				return 1;
			}
		}
		for (new i = 0; i != MAX_BACKPACKS; i ++) if (BackpackData[i][backpackExists] && !BackpackData[i][backpackPlayer] && IsPlayerInRangeOfPoint(playerid, 2.0, BackpackData[i][backpackPos][0], BackpackData[i][backpackPos][1], BackpackData[i][backpackPos][2])) {
		    return Backpack_Items(playerid, i);
		}
        if (PlayerData[playerid][pCarryTrash])
		{
			for (new i = 1; i != MAX_VEHICLES; i ++) if (GetVehicleModel(i) == 408 && IsPlayerNearBoot(playerid, i))
			{
			    if (CoreVehicles[i][vehTrash] >= 10)
			        return SendErrorMessage(playerid, "This vehicle cannot hold anymore trash (limit: 10).");

				CoreVehicles[i][vehTrash]++;

				RemovePlayerAttachedObject(playerid, 4);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has loaded a trash bag into the Trashmaster.", ReturnName(playerid, 0));

				PlayerData[playerid][pCarryTrash] = 0;
				break;
			}
		}

		if (PlayerData[playerid][pCarryCrate] != -1)
		{
			for (new i = 1; i != MAX_VEHICLES; i ++) if (IsLoadableVehicle(i) && IsPlayerNearBoot(playerid, i))
			{
			    if (GetVehicleCrates(i) >= GetMaxCrates(i))
			        return SendErrorMessage(playerid, "This vehicle cannot hold anymore crates (limit: %d).", GetMaxCrates(i));

				CrateData[PlayerData[playerid][pCarryCrate]][crateVehicle] = i;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

				RemovePlayerAttachedObject(playerid, 4);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has loaded a crate into the %s.", ReturnName(playerid, 0), ReturnVehicleName(i));

				PlayerData[playerid][pCarryCrate] = -1;
				ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);
				break;
			}
		}
		else if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
		{
		    new
				count = 0;

		    if ((id = Item_Nearest(playerid)) != -1)
		    {

		        for (new i = 0; i < MAX_DROPPED_ITEMS; i ++) if (count < MAX_LISTED_ITEMS && DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]) && GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld]) {
		            NearestItems[playerid][count++] = i;
		        }
		        if (count == 1)
		        {
				    if (DroppedItems[id][droppedWeapon] != 0)
					{
				        if (PlayerData[playerid][pScore] < 2)
							return SendErrorMessage(playerid, "You must have at least 2 score.");

    	   				GiveWeaponToPlayer(playerid, DroppedItems[id][droppedWeapon], DroppedItems[id][droppedAmmo]);

    	                Item_Delete(id);
						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a %s.", ReturnName(playerid, 0), ReturnWeaponName(DroppedItems[id][droppedWeapon]));
                        Log_Write("logs/droppick.txt", "[%s] %s picked up a %s.", ReturnDate(), ReturnName(playerid, 0), ReturnWeaponName(DroppedItems[id][droppedWeapon]));

					}
					else if (PickupItem(playerid, id))
					{
			    		SendServerMessage(playerid, "%s added to inventory!", DroppedItems[id][droppedItem]);
						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has picked up a \"%s\".", ReturnName(playerid, 0), DroppedItems[id][droppedItem]);
						Log_Write("logs/droppick.txt", "[%s] %s has picked up a \"%s\".", ReturnDate(), ReturnName(playerid, 0), DroppedItems[id][droppedItem]);
					}
					else
						SendErrorMessage(playerid, "You don't have any room in your inventory.");
				}
				else Dialog_Show(playerid, PickupItems, DIALOG_STYLE_LIST, "Pickup Items", string, "Pickup", "Cancel");
			}
		}
	}
	else if (newkeys & KEY_YES)
	{	
		if(IsPlayerInRangeOfPoint(playerid, 1.0, 1847.0599,605.2465,10.9592)) // Sidejob Pengutip Buah Kelapa
		{
			SetPlayerAttachedObject(playerid, 4, 19087, 6, 0.112000, 0.012000, 0.046000, 0.099997, 98.800018, -51.000007, 1.000000, 1.000000, 1.000000);
	
			PlayerData[playerid][pKaitKelapa] = true;
			PlayerData[playerid][pKaitKelapaCP] = 0;

			SetPlayerCheckpoint(playerid, g_arrKaitKelapaCheckpoints[0][0], g_arrKaitKelapaCheckpoints[0][1], g_arrKaitKelapaCheckpoints[0][2], 3.0);
			SendServerMessage(playerid, "Sila ikuti checkpoint merah.");
		} 
		if (IsPlayerInRangeOfPoint(playerid, 2.0, 1435.8970,-2296.4282,13.5469))
		{
			if (!PlayerData[playerid][pStaterpack])
			{
				GiveMoney(playerid, 1000);

				Car_Create(PlayerData[playerid][pID], 462, 1436.3525,-2299.6096,13.1450,98.0557, random(127), random(127));
				
				SendServerMessage(playerid, "Anda telah menebus pek permulaan server. Anda mendapatkan duit RM1,000 dan kenderaan Faggio!");

				PlayerData[playerid][pStaterpack] = 1;
			}
			else
			{
				SendErrorMessage(playerid, "Anda telah menebus pek permulaan sebelum ini!");
			}
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1666.7629,-1261.9624,14.8168))
		{
			Dialog_Show(playerid, BankAccount, DIALOG_STYLE_LIST, "Bank Account", "Withdraw funds\nDeposit funds\nMake a transfer", "Select", "Cancel");
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1669.2451,-1261.9648,14.8162))
		{
			Dialog_Show(playerid, Savings, DIALOG_STYLE_LIST, "Savings Account", "Withdraw funds\nDeposit funds", "Select", "Cancel");
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1674.8635,-1261.9668,14.8159))
		{
			Dialog_Show(playerid, Salary, DIALOG_STYLE_LIST, "Salary Account", "View Salary\nClaim Salary", "Select", "Cancel");
		}
		if (IsPlayerInRangeOfPoint(playerid, 5.0, 2025.4073, -1404.0511, 17.2113))
		{
			if (GetFactionType(playerid) != FACTION_MEDIC)
				return SendErrorMessage(playerid, "You must be part of a medical faction.");

			if(PlayerData[playerid][pOnDuty] == 0)
				return SendErrorMessage(playerid, "You need to onduty to use this!");
				
			Dialog_Show(playerid, DropInjured, DIALOG_STYLE_INPUT, "Patient ID", "Input your patient id:", "Submit", "Cancel");
		}
		if (IsPlayerInRangeOfPoint(playerid, 3.0, -1774.0975,-2012.7534,1500.7853))
		{
			new str[510];
			format(str, sizeof(str), "Anda mempunyai %d insuran badan.\nSila masukkan jumlah insuran yang ingin dibeli.\nHarga insuran: RM250", PlayerData[playerid][pBodyInsurance]);
			Dialog_Show(playerid, BodyInsurance, DIALOG_STYLE_INPUT, "Insuran Badan", str, "Beli","Batal");
		}
		if (IsPlayerInRangeOfPoint(playerid, 3.0, -1770.6677,-2012.7568,1500.7853))
		{
			new str[510];
			format(str, sizeof(str), "Anda mempunyai %d medkit.\nSila masukkan jumlah medkit yang inin dibeli.\nHarga medkit: RM20", Inventory_Count(playerid, "First Aid"));
			Dialog_Show(playerid, BuyMedkit, DIALOG_STYLE_INPUT, "Medkit", str, "Beli","Batal");
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1618.6732,-1894.4911,13.5491))
		{
			if (PlayerData[playerid][pSweeper])
				return SendErrorMessage(playerid, "Anda telah pun memulakan kerja ini!");

			PlayerData[playerid][pSweeperCar] = CreateVehicle(574, 1619.9969,-1884.2590,13.2720,1.0845, 1, 1, -1);

			if (PlayerData[playerid][pSweeperCar] != INVALID_VEHICLE_ID)
			{
				PlayerData[playerid][pSweeper] = true;
				PlayerData[playerid][pSweeperCP] = 0;

				ResetVehicle(PlayerData[playerid][pSweeperCar]);

				PutPlayerInVehicle(playerid, PlayerData[playerid][pSweeperCar], 0);

				SetVehicleNumberPlate(PlayerData[playerid][pSweeperCar], "SIDEJOB");
				SetEngineStatus(PlayerData[playerid][pSweeperCar], true);

				SetPlayerCheckpoint(playerid, g_arrSweeperCheckpoints[0][0], g_arrSweeperCheckpoints[0][1], g_arrSweeperCheckpoints[0][2], 3.0);
				SendServerMessage(playerid, "Sila ikuti checkpoint merah.");
			}
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1564.4639,-1673.8186,14.6641))
		{
			if (PlayerData[playerid][pDrivingTest])
				return SendErrorMessage(playerid, "You have already started the driving test!");

			if (Inventory_HasItem(playerid, "Driving License"))
				return SendErrorMessage(playerid, "You have your driving license already!");

			if (GetMoney(playerid) < 50)
				return SendErrorMessage(playerid, "You don't have RM50 for the driving test.");

			PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
			PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

			GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			GetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

			PlayerData[playerid][pTestCar] = CreateVehicle(410, -2047.1056, -87.7183, 34.8219, 0.1447, 1, 1, -1);

			PlayerData[playerid][pTestWarns] = 0;

			if (PlayerData[playerid][pTestCar] != INVALID_VEHICLE_ID)
			{
				PlayerData[playerid][pDrivingTest] = true;
				PlayerData[playerid][pTestStage] = 0;

				ResetVehicle(PlayerData[playerid][pTestCar]);
				SetPlayerVirtualWorld(playerid, (2000 + playerid));

				SetVehicleVirtualWorld(PlayerData[playerid][pTestCar], (2000 + playerid));
				PutPlayerInVehicle(playerid, PlayerData[playerid][pTestCar], 0);

				SetVehicleNumberPlate(PlayerData[playerid][pTestCar], "TEST");

				SetPlayerCheckpoint(playerid, g_arrDrivingCheckpoints[0][0], g_arrDrivingCheckpoints[0][1], g_arrDrivingCheckpoints[0][2], 3.0);
				SendServerMessage(playerid, "You have started the driving test.");

				SetPlayerInterior(playerid, 0);
			}
		}
		if (IsPlayerInRangeOfPoint(playerid, 1.0, 1570.0446,-1683.7296,14.6641))
		{
			new string[256 * MAX_OWNABLE_CARS], count, header[512];

			header = "";
			strcat(header,"#\tModel\tPlate\tPrice\n",sizeof(header));

			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) if (count < MAX_OWNABLE_CARS && Car_IsOwner(playerid, i) && CarData[i][carImpounded] == 1)
			{
				format(string, sizeof(string), "%s%d\t%s\t%s\t"GREEN_E"%s"WHITE_E"\n", string, count + 1, ReturnVehicleModelName(CarData[i][carModel]), CarData[i][carPlate], FormatNumber(CarData[i][carImpoundPrice]));
				ListedVehicles[playerid][count++] = i;
			}

			if(!count) return SendErrorMessage(playerid, "Anda tidak mempunyai sebarang kenderaan yang di sita.");

			strcat(header, string);
			Dialog_Show(playerid, ReleaseCar, DIALOG_STYLE_TABLIST_HEADERS, "Release Vehicle", header, "Select", "Cancel");
		}
		if (IsNearFactionLocker(playerid))
		{
			new factionid = PlayerData[playerid][pFaction];

			if (FactionData[factionid][factionType] != FACTION_GANG)
				Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Toggle Duty\nArmored Vest\nLocker Skins\nLocker Weapons", "Select", "Cancel");

			else Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Locker Skins\nLocker Weapons\nNormal Skin", "Select", "Cancel");
		}
		if (IsNearFactionLeaderLocker(playerid))
		{
			if (PlayerData[playerid][pFaction] == -1) return 1;
			if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1) return 1;

			Dialog_Show(playerid, LockerLeader, DIALOG_STYLE_LIST, "Leader Faction Locker", "Faction Money\nManage Rank", "Select", "Cancel");
		}
		static
			id = -1;

		if ((id = Business_NearestCaunter(playerid)) != -1)
		{
			if (BusinessData[id][bizSita] != 0)
				return SendErrorMessage(playerid, "Anda tidak boleh membeli barang kerana business ini telah disita.");

			if (BusinessData[id][bizLocked] != 0 || !BusinessData[id][bizOwner])
				return SendErrorMessage(playerid, "This business is closed!");

			if (BusinessData[id][bizType] == 5) {
				Business_CarMenu(playerid, id);
			} else {
				Business_PurchaseMenu(playerid, id);
			}
		}

		if ((id = Rent_Nearest(playerid)) != -1)
		{
			new str[1024];
			format(str, sizeof(str), "Kenderaan\tHarga\tTempoh\n"WHITE_E"%s\t"LG_E"RM14,000\t"WHITE_E"1 Hari\n%s\t"LG_E"RM200\t"WHITE_E"1 Hari",
			ReturnVehicleModelName(475),
			ReturnVehicleModelName(462));
						
			Dialog_Show(playerid, RentVehicle, DIALOG_STYLE_TABLIST_HEADERS, "Sewa Kenderaan", str, "Sewa", "Batal");
		}

		if ((id = Pump_Nearest(playerid)) != -1)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new idd = Car_GetID(vehicleid);

			if (PlayerData[playerid][pRefill] != INVALID_VEHICLE_ID)
			{
				BusinessData[PlayerData[playerid][pGasStation]][bizVault] += PlayerData[playerid][pRefillPrice];
				Business_Save(PlayerData[playerid][pGasStation]);

				GiveMoney(playerid, -PlayerData[playerid][pRefillPrice]);

				SendServerMessage(playerid, "You have refueled your vehicle for %s.", FormatNumber(PlayerData[playerid][pRefillPrice]));
				StopRefilling(playerid);

				return 1;
			}
			if (!vehicleid)
				return 1;

			if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1;

			if (GetEngineStatus(vehicleid))
				return SendErrorMessage(playerid, "You must turn the engine off first.");
			
			if (idd != -1)
			{
				if (CarData[idd][carFuel] > 95)
					return SendErrorMessage(playerid, "This vehicle doesn't need any fuel.");
			}

			if (IsPumpOccupied(id))
				return SendErrorMessage(playerid, "This fuel pump is already occupied.");

			if (PumpData[id][pumpFuel] < 1)
				return SendErrorMessage(playerid, "This pump doesn't have enough fuel.");

			PlayerData[playerid][pGasPump] = id;
			PlayerData[playerid][pGasStation] = PumpData[id][pumpBusiness];

			PlayerData[playerid][pRefill] = vehicleid;
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has started refilling their vehicle.", ReturnName(playerid, 0));
		}
		if ((id = ATM_Nearest(playerid)) != -1)
		{
			Dialog_Show(playerid, Bank, DIALOG_STYLE_LIST, "Bank Account", "Bank Balance: %s", "Select", "Cancel", FormatNumber(PlayerData[playerid][pBankMoney]), FormatNumber(PlayerData[playerid][pSavings]));
		}
		if ((id = Vendor_Nearest(playerid)) != -1)
		{
		    switch (VendorData[id][vendorType])
		    {
		        case 1:
		        {
					if (GetMoney(playerid) < 3)
					    return SendErrorMessage(playerid, "You must have at least RM3.");

					if (PlayerData[playerid][pVendorTime] > 0)
					    return SendErrorMessage(playerid, "Please wait before purchasing from a vendor again.");

					if (Inventory_Count(playerid, "Cooked Burger") >= 5)
					    return SendErrorMessage(playerid, "You have too many burgers in your inventory already.");

					id = Inventory_Add(playerid, "Cooked Burger", 2703);

					if (id != -1)
					{
					    PlayerData[playerid][pVendorTime] = 3;

					    GiveMoney(playerid, -3);
					    ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);

					    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has purchased a burger from the vendor for RM3.", ReturnName(playerid, 0));
						SendServerMessage(playerid, "Your burger was added to your inventory.");
					}
				}
				case 2:
		        {
					if (GetMoney(playerid) < 2)
					    return SendErrorMessage(playerid, "You must have at least RM2.");

					if (PlayerData[playerid][pVendorTime] > 0)
					    return SendErrorMessage(playerid, "Please wait before purchasing from a vendor again.");

					if (Inventory_Count(playerid, "Soda") >= 10)
					    return SendErrorMessage(playerid, "You have too many soda bottles in your inventory already.");

					id = Inventory_Add(playerid, "Soda", 1543);

					if (id != -1)
					{
                        PlayerData[playerid][pVendorTime] = 3;

					    GiveMoney(playerid, -2);
					    ApplyAnimation(playerid, "VENDING", "VEND_USE", 4.0, 0, 0, 0, 0, 0);

					    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has purchased a soda from the vendor for RM2.", ReturnName(playerid, 0));
						SendServerMessage(playerid, "Your soda was added to your inventory.");
					}
				}
			}
		}
	    if ((id = Gate_Nearest(playerid)) != -1)
		{
			if (strlen(GateData[id][gatePass]))
			{
				Dialog_Show(playerid, GatePass, DIALOG_STYLE_INPUT, "Enter Password", "Please enter the password for this gate below:", "Submit", "Cancel");
			}
			else
			{
				if (GateData[id][gateFaction] != -1 && PlayerData[playerid][pFaction] != GetFactionByID(GateData[id][gateFaction]))
					return SendErrorMessage(playerid, "You can't open this gate.");

				Gate_Operate(id);
			}
		}
	}
	else if (newkeys & KEY_SECONDARY_ATTACK)
	{
		static
			id = -1;

		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		GetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

	    if ((id = House_Nearest(playerid)) != -1)
	    {
			if (HouseData[id][houseSita])
	            return SendErrorMessage(playerid, "Rumah ini tidak boleh masuk kerana telah disita.");

	        if (HouseData[id][houseLocked])
	            return SendErrorMessage(playerid, "You cannot enter a locked house.");

			SetPlayerPosEx(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
			SetPlayerFacingAngle(playerid, HouseData[id][houseInt][3]);

			SetPlayerWeather(playerid, 0);
			SetPlayerTime(playerid, 14, 0);

			SetPlayerInterior(playerid, HouseData[id][houseInterior]);
			SetPlayerVirtualWorld(playerid, HouseData[id][houseID] + 5000);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pHouse] = HouseData[id][houseID];
			return 1;
		}
		if ((id = House_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]))
	    {
			SetPlayerPosEx(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
			SetPlayerFacingAngle(playerid, HouseData[id][housePos][3] - 180.0);

			SetPlayerWeather(playerid, WorldWeather);
			SetPlayerTime(playerid, WorldTime, 0);

			SetPlayerInterior(playerid, HouseData[id][houseExterior]);
			SetPlayerVirtualWorld(playerid, HouseData[id][houseExteriorVW]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pHouse] = -1;
			return 1;
		}
        if ((id = Business_Nearest(playerid)) != -1)
	    {
			if (BusinessData[id][bizSita] != 0 )
	            return SendErrorMessage(playerid, "Business ini tidak boleh masuk kerana telah disita.");

			if (BusinessData[id][bizLocked] != 0 || !BusinessData[id][bizOwner])
	            return SendErrorMessage(playerid, "This business is closed.");

			SetPlayerPosEx(playerid, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]);
			SetPlayerFacingAngle(playerid, BusinessData[id][bizInt][3]);

			SetPlayerWeather(playerid, 0);
			SetPlayerTime(playerid, 14, 0);

			SetPlayerInterior(playerid, BusinessData[id][bizInterior]);
			SetPlayerVirtualWorld(playerid, BusinessData[id][bizID] + 6000);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pBusiness] = BusinessData[id][bizID];

			if (strlen(BusinessData[id][bizMessage]) && strcmp(BusinessData[id][bizMessage], "NULL", true)) {
			    SendClientMessage(playerid, COLOR_DARKBLUE, BusinessData[id][bizMessage]);
			}
			return 1;
		}
		if ((id = Business_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]))
	    {
			SetPlayerPosEx(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
			SetPlayerFacingAngle(playerid, BusinessData[id][bizPos][3] - 180.0);

			SetPlayerWeather(playerid, WorldWeather);
			SetPlayerTime(playerid, WorldTime, 0);

			SetPlayerInterior(playerid, BusinessData[id][bizExterior]);
			SetPlayerVirtualWorld(playerid, BusinessData[id][bizExteriorVW]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pBusiness] = -1;
			return 1;
		}
		if ((id = Entrance_Nearest(playerid)) != -1)
	    {
	        if (EntranceData[id][entranceLocked])
	            return SendErrorMessage(playerid, "This entrance is locked at the moment.");

			// Bayaran Masuk Club
			if(IsPlayerInRangeOfPoint(playerid, 2.5, 1836.4076, -1682.3350, 13.7012))
			{
				if (GetMoney(playerid) < 80)
					return SendErrorMessage(playerid, "Anda tidak mempunyai duit yang cukup untuk memasuki club ini.");
					
				GiveMoney(playerid, -80);
				SendInfoMessage(playerid, "Anda telah dikenakan caj RM80 untuk masuk ke club ini.");
			}

			if (EntranceData[id][entranceCustom])
				SetPlayerPosEx(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);

			else
				SetPlayerPos(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
			
			SetPlayerWeather(playerid, 0);
			SetPlayerTime(playerid, 14, 0);

			SetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);

			SetPlayerInterior(playerid, EntranceData[id][entranceInterior]);
			SetPlayerVirtualWorld(playerid, EntranceData[id][entranceWorld]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pEntrance] = EntranceData[id][entranceID];
			return 1;
		}
		for (new i = 0; i != MAX_ENTRANCES; i ++)
		{
			if (GetPlayerInterior(playerid) == EntranceData[i][entranceInterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceWorld] && IsPlayerInRangeOfPoint(playerid, 2.5, EntranceData[i][entranceInt][0], EntranceData[i][entranceInt][1], EntranceData[i][entranceInt][2]))
			{
				if (EntranceData[i][entranceCustom])
					SetPlayerPosEx(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]);

				else
					SetPlayerPos(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]);

				SetPlayerWeather(playerid, WorldWeather);
				SetPlayerTime(playerid, WorldTime, 0);

				SetPlayerFacingAngle(playerid, EntranceData[i][entrancePos][3] - 180.0);

				SetPlayerInterior(playerid, EntranceData[i][entranceExterior]);
				SetPlayerVirtualWorld(playerid, EntranceData[i][entranceExteriorVW]);

				SetCameraBehindPlayer(playerid);
				PlayerData[playerid][pEntrance] = Entrance_GetLink(playerid);
				return 1;
			}
		}
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    if (IsPlayerNPC(playerid))
	    return 1;

	if (PlayerData[playerid][pTaxiDuty])
	{
        foreach (new i : Player) if (PlayerData[i][pTaxiPlayer] == playerid && IsPlayerInVehicle(i, GetPlayerVehicleID(playerid))) {
	        LeaveTaxi(i, playerid);
	    }
	    SetPlayerColor(playerid, DEFAULT_COLOR);

        PlayerData[playerid][pTaxiDuty] = false;
        SendServerMessage(playerid, "You are no longer on taxi duty!");
	}
    if (PlayerData[playerid][pDrivingTest])
	{
	    SetTimerEx("PutInsideVehicle", 500, false, "dd", playerid, vehicleid);
		Dialog_Show(playerid, LeaveTest, DIALOG_STYLE_MSGBOX, "Confirm Test Leave", "Warning: Are you sure you want to exit the driving test?", "Yes", "No");
	}
	if(PlayerData[playerid][pSweeper])
	{
		DestroyVehicle(PlayerData[playerid][pSweeperCar]);
		PlayerData[playerid][pSweeper] = false;
		PlayerData[playerid][pSweeperCP] = 0;
		DisablePlayerCheckpoint(playerid);
		SendInfoMessage(playerid, "Anda telah gagal menyelesaikan kerja ini kerana anda keluar dari kenderaan kerja.");
	}
	if( vehicleid == PoliceDrone[playerid] )
	{
        SendErrorMessage( playerid, "You can't exit the drone! Use '/drone remove' or '/drone detonate'." );
    }
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    if (IsPlayerNPC(playerid))
	    return 1;

	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY || PlayerData[playerid][pInjured] || PlayerData[playerid][pFirstAid]) {
	    ClearAnimations(playerid);

	    return 0;
	}
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(TruckingCheck[playerid] >= 1 && PlayerData[playerid][pUnloading] == -1)
	{
	    if (!IsPlayerInAnyVehicle(playerid))
		{
		    SendErrorMessage(playerid, "You're not in a vehicle");
		    return 1;
		}
		new vehicleid = GetPlayerVehicleID(playerid);
		if (!IsLoadableVehicle(vehicleid))
  		{
  			SendErrorMessage(playerid, "You're not in a delivery vehicle.");
  		}
	    new string[180];
        format(string, sizeof(string), "You have earned %s from the courier mission!", FormatNumber(TruckingCheck[playerid]));
		AddPlayerSalary(playerid, "Courier Mission", TruckingCheck[playerid]);
        TruckingCheck[playerid] = 0;
		SendClientMessageEx(playerid, COLOR_LIGHTYELLOW, string);
		DisablePlayerCheckpoint(playerid);
		RespawnVehicle(vehicleid);
	}
	if (PlayerData[playerid][pCP])
	{
	    DisablePlayerCheckpoint(playerid);
	    PlayerData[playerid][pCP] = 0;
	} 
	if (PlayerData[playerid][pDrivingTest])
	{
	    PlayerData[playerid][pTestStage]++;

	    if (PlayerData[playerid][pTestStage] < sizeof(g_arrDrivingCheckpoints)) {
			SetPlayerCheckpoint(playerid, g_arrDrivingCheckpoints[PlayerData[playerid][pTestStage]][0], g_arrDrivingCheckpoints[PlayerData[playerid][pTestStage]][1], g_arrDrivingCheckpoints[PlayerData[playerid][pTestStage]][2], 3.0);
		}
		else
		{
		    static
		        Float:health;

		    GetVehicleHealth(GetPlayerVehicleID(playerid), health);

		    if (health < 950.0)
				SendErrorMessage(playerid, "Anda telah gagal membuat ujian memandu, kenderaan anda teleh menerima kesan pelanggaran!"); 

		    else
			{
		        GiveMoney(playerid, -50);
		        SendServerMessage(playerid, "Anda telah dikenakan caj RM50 untuk membuat lesen memandu.");

		        Inventory_Add(playerid, "Driving License", 1581);
		        SendServerMessage(playerid, "Anda telah lulus ujian memandu dan anda telah menerima lesen memandu."); 
		    }
  			CancelDrivingTest(playerid);
		}
	}
	else if (PlayerData[playerid][pSweeper]) 
	{
	    PlayerData[playerid][pSweeperCP]++;

	    if (PlayerData[playerid][pSweeperCP] < sizeof(g_arrSweeperCheckpoints)) {
			SetPlayerCheckpoint(playerid, g_arrSweeperCheckpoints[PlayerData[playerid][pSweeperCP]][0], g_arrSweeperCheckpoints[PlayerData[playerid][pSweeperCP]][1], g_arrSweeperCheckpoints[PlayerData[playerid][pSweeperCP]][2], 3.0);
		}
		else
		{
		    AddPlayerSalary(playerid, "Sweeper", 120);
		    SendServerMessage(playerid, "Anda telah mendapat RM120.");

  			DestroyVehicle(PlayerData[playerid][pSweeperCar]);
  			PlayerData[playerid][pSweeper] = false;
			PlayerData[playerid][pSweeperCP] = 0;
			DisablePlayerCheckpoint(playerid);
		}
	}
	else if (PlayerData[playerid][pKaitKelapa])
	{
	    PlayerData[playerid][pKaitKelapaCP]++;

	    if (PlayerData[playerid][pKaitKelapaCP] < sizeof(g_arrKaitKelapaCheckpoints)) 
		{
			SetPlayerCheckpoint(playerid, g_arrKaitKelapaCheckpoints[PlayerData[playerid][pKaitKelapaCP]][0], g_arrKaitKelapaCheckpoints[PlayerData[playerid][pKaitKelapaCP]][1], g_arrKaitKelapaCheckpoints[PlayerData[playerid][pKaitKelapaCP]][2], 3.0);
			TogglePlayerControllable(playerid,0);
			SetTimerEx("UnfreezeJob",5000,0,"i",playerid);
			ApplyAnimation(playerid,"SWORD","sword_block",50.0 ,0,1,0,1,1);
		}
		else
		{
  			PlayerData[playerid][pKaitKelapa] = false;
			PlayerData[playerid][pKaitKelapaCP] = 0;
			DisablePlayerCheckpoint(playerid);
			RemovePlayerAttachedObject(playerid, 4);
			SendServerMessage(playerid, "Anda telah mendapat RM25.");
			AddPlayerSalary(playerid, "Kait Kelapa", 25);
		}
	}
	else
	{
		if (PlayerData[playerid][pWaypoint])
		{
		    PlayerData[playerid][pWaypoint] = 0;

		    DisablePlayerCheckpoint(playerid);
		    PlayerTextDrawHide(playerid, WaypointTD[playerid]);
		}
		else if (PlayerData[playerid][pJob] == JOB_COURIER && !IsPlayerInAnyVehicle(playerid))
		{
			if (PlayerData[playerid][pLoading] && !PlayerData[playerid][pLoadCrate] && Job_NearestPoint(playerid) != -1)
			{
			    PlayerData[playerid][pLoadCrate] = 1;

		        SetPlayerAttachedObject(playerid, 4, 3014, 1, 0.038192, 0.371544, 0.055191, 0.000000, 90.000000, 357.668670, 1.000000, 1.000000, 1.000000);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

				ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
				SendInfoMessage(playerid, "Press "YELLOW_E"ALT "WHITE_E"at near a truck to load the crate.");
			}
			else if (PlayerData[playerid][pUnloading] != -1)
			{
				if (!PlayerData[playerid][pLoadCrate])
				{
				    PlayerData[playerid][pLoadCrate] = 1;
				    ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);

			        SetPlayerAttachedObject(playerid, 4, 3014, 1, 0.038192, 0.371544, 0.055191, 0.000000, 90.000000, 357.668670, 1.000000, 1.000000, 1.000000);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

					SetPlayerCheckpoint(playerid, BusinessData[PlayerData[playerid][pUnloading]][bizPos][0], BusinessData[PlayerData[playerid][pUnloading]][bizPos][1], BusinessData[PlayerData[playerid][pUnloading]][bizPos][2], 1.0);
					SendInfoMessage(playerid, "Deliver the crate to the checkpoint.");

					CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoads]--;
				}
				else
				{
				    static
				        Float:fX,
				        Float:fY,
				        Float:fZ,
						string[64];

				    PlayerData[playerid][pLoadCrate] = 0;
				    ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);

				    RemovePlayerAttachedObject(playerid, 4);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

					switch (CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoadType])
					{
					    case 1:
						{
							TruckingCheck[playerid] += 35;
					        SendServerMessage(playerid, "RM35 has been added to your check.");
					    }
					    case 2:
						{
						    TruckingCheck[playerid] += 40;
					        SendServerMessage(playerid, "RM40 has been added to your check.");
					    }
					    case 3:
						{
						    TruckingCheck[playerid] += 30;
					        SendServerMessage(playerid, "RM30 has been added to your check.");
					    }
					    case 4:
						{
						    TruckingCheck[playerid] += 35;
					        SendServerMessage(playerid, "RM35 has been added to your check.");
					    }
					    case 5:
						{
						    TruckingCheck[playerid] += 40;
					        SendServerMessage(playerid, "RM40 has been added to your check.");
					    }
					    case 6:
						{
						    TruckingCheck[playerid] += 35;
					        SendServerMessage(playerid, "RM35 has been added to your check.");
					    }
					}
					if (CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoadType] == 5)
					{
						for (new i = 0; i < MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && PumpData[i][pumpBusiness] == PlayerData[playerid][pUnloading]) {
						    PumpData[i][pumpFuel] += 100;

			                format(string, sizeof(string), "[GAS PUMP]\n{FFFFFF}Fuel Left: "YELLOW_E"%d"WHITE_E" liters\nPress "GREEN_E"Y"WHITE_E" to refuel the vehicle.", PumpData[i][pumpFuel]);
						    UpdateDynamic3DTextLabelText(PumpData[i][pumpText3D], COLOR_DARKBLUE, string);

						    Pump_Save(i);
						}
					}
					else
					{
						BusinessData[PlayerData[playerid][pUnloading]][bizProducts] += 20;
						Business_Save(PlayerData[playerid][pUnloading]);
					}
					if (CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoads] > 0)
					{
					    GetVehicleBoot(PlayerData[playerid][pUnloadVehicle], fX, fY, fZ);
					    SetPlayerCheckpoint(playerid, fX, fY, fZ, 1.0);
					}
					else
					{
					    CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoads] = 0;
					    CoreVehicles[PlayerData[playerid][pUnloadVehicle]][vehLoadType] = 0;

				     	PlayerData[playerid][pUnloading] = -1;
					    PlayerData[playerid][pUnloadVehicle] = INVALID_VEHICLE_ID;

						DisablePlayerCheckpoint(playerid);
					    SendServerMessage(playerid, "You have delivered all the crates from the vehicle.");
					    SendInfoMessage(playerid, "Deliver your truck to the checkpoint to get paid.");
					    SetPlayerCheckpoint(playerid, 2521.0376, -2090.3279, 13.4125, 5.0);

					    if (PlayerData[playerid][pShipment] != -1)
					    {
					        foreach (new i : Player) if (Business_IsOwner(i, PlayerData[playerid][pShipment])) {
					            SendInfoMessage(playerid, "%s has delivered your shipment to %s.", ReturnName(playerid, 0), BusinessData[PlayerData[playerid][pShipment]][bizName]);
							}
							BusinessData[PlayerData[playerid][pShipment]][bizShipment] = 0;
							Business_Save(PlayerData[playerid][pShipment]);

          					PlayerData[playerid][pShipment] = -1;
          					PlayerData[playerid][pDeliverShipment] = 0;
					    }
					}
				}
			}
		}
		else if (PlayerData[playerid][pJob] == JOB_MINER && PlayerData[playerid][pMinedRock] && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY)
		{
		    new money = random(20) + 5;

			SendServerMessage(playerid, "You have earned %s for the rock.", FormatNumber(money));
			AddPlayerSalary(playerid, "Miner Rock", money);
			PlayerData[playerid][pMinedRock] = 0;
			PlayerData[playerid][pMineCount] = 0;

			DisablePlayerCheckpoint(playerid);
			RemovePlayerAttachedObject(playerid, 4);

			SetPlayerAttachedObject(playerid, 4, 18634, 6, 0.156547, 0.039423, 0.026570, 198.109115, 6.364907, 262.997558, 1.000000, 1.000000, 1.000000);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
		else if (PlayerData[playerid][pJob] == JOB_SORTER && PlayerData[playerid][pSorting] != -1)
		{
		    if (PlayerData[playerid][pSortCrate])
		    {
		        PlayerData[playerid][pSortCrate] = 0;

		        RemovePlayerAttachedObject(playerid, 4);
		        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		        ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
		        SetPlayerCheckpoint(playerid, JobData[PlayerData[playerid][pSorting]][jobPoint][0], JobData[PlayerData[playerid][pSorting]][jobPoint][1], JobData[PlayerData[playerid][pSorting]][jobPoint][2], 1.0);
				AddPlayerSalary(playerid, "Sort Crate", 10);
				SendServerMessage(playerid, "You have earned RM10 for the package.");
			}
			else
			{
                SetPlayerAttachedObject(playerid, 4, 1220, 5, 0.137832, 0.176979, 0.151424, 96.305931, 185.363006, 20.328088, 0.699999, 0.800000, 0.699999);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

				ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
				SetPlayerCheckpoint(playerid, JobData[PlayerData[playerid][pSorting]][jobDeliver][0], JobData[PlayerData[playerid][pSorting]][jobDeliver][1], JobData[PlayerData[playerid][pSorting]][jobDeliver][2], 1.0);

                PlayerData[playerid][pSortCrate] = 1;
				SendInfoMessage(playerid, "Deliver the package to the marker.");
			}
		}
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (IsPlayerNPC(playerid))
	    return 1;

	new vehicleid = GetPlayerVehicleID(playerid);

	if (newstate == PLAYER_STATE_WASTED && PlayerData[playerid][pJailTime] < 1)
	{
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

	    PlayerTextDrawHide(playerid, LoadingCrateTD[playerid]);

	    PlayerData[playerid][pHealth] = 100.0;

	    ResetWeapons(playerid);
	    ResetPlayer(playerid);

	    PlayerData[playerid][pKilled] = 1;

		PlayerData[playerid][pInjured] = 1;
		PlayerData[playerid][pInjuredTime] = 500;

		PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
		PlayerData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		GetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

		if (PlayerData[playerid][pCallLine] != INVALID_PLAYER_ID)
		{ 
		    SendClientMessage(PlayerData[playerid][pCallLine], COLOR_YELLOW, "[PHONE]: The line went dead...");
		    CancelCall(playerid);
		}
		if (PlayerData[playerid][pCarryCrate] != -1)
		{
			Crate_Drop(playerid);
		}
	}
	else if (oldstate == PLAYER_STATE_DRIVER)
	{
	    if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
	        return RemoveFromVehicle(playerid);

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

		PlayerTextDrawHide(playerid, LoadingCrateTD[playerid]);
	}
	else if (newstate == PLAYER_STATE_DRIVER)
	{
		if (PlayerData[playerid][pJob] == JOB_GARBAGE && GetVehicleModel(vehicleid) == 408 && CoreVehicles[vehicleid][vehTrash] > 0)
		{
		    new pointid = -1;

		    if ((pointid = GetClosestJobPoint(playerid, 7)) != -1)
		    {
			    PlayerData[playerid][pCP] = 1;
			    SetPlayerCheckpoint(playerid, JobData[pointid][jobPoint][0], JobData[pointid][jobPoint][1], JobData[pointid][jobPoint][2], 2.5);

		    	SendInfoMessage(playerid, "This vehicle is loaded with %d trash bags (marker set to dump).", CoreVehicles[vehicleid][vehTrash]);
		    }
		}
		if (PlayerData[playerid][pJob] == JOB_COURIER && IsLoadableVehicle(vehicleid) && CoreVehicles[vehicleid][vehLoads] > 0)
		{
		    if (PlayerData[playerid][pLoading])
		    {
				DisablePlayerCheckpoint(playerid);
				PlayerData[playerid][pLoading] = 0;
			}
			static
			    string[64];

		    switch (CoreVehicles[vehicleid][vehLoadType])
			{
				case 1: format(string, sizeof(string), "~b~Loaded:~w~ Retail Supplies~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
		        case 2: format(string, sizeof(string), "~b~Loaded:~w~ Electronic~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
                case 3: format(string, sizeof(string), "~b~Loaded:~w~ Clothing~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
                case 4: format(string, sizeof(string), "~b~Loaded:~w~ Food Supplies~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
                case 5: format(string, sizeof(string), "~b~Loaded:~w~ Gasoline~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
                case 6: format(string, sizeof(string), "~b~Loaded:~w~ Furniture~n~~b~Loaded Crates:~w~ %d/6", CoreVehicles[vehicleid][vehLoads]);
			}
		    PlayerTextDrawShow(playerid, LoadingCrateTD[playerid]);
		    PlayerTextDrawSetString(playerid, LoadingCrateTD[playerid], string);
		}
		else if (!IsEngineVehicle(vehicleid))
		{
			SetEngineStatus(vehicleid, true);
		}
		else
		{
			if (!Inventory_HasItem(playerid, "Driving License") && !PlayerData[playerid][pDrivingTest])
			{
   				SendInfoMessage(playerid, "You are operating a vehicle without a driving license.");
			}
		}
	    if (IsSpeedoVehicle(vehicleid) && !PlayerData[playerid][pDisableSpeedo]) 
		{
			new str[320];
			TextDrawSetPreviewModel(CARMODELUPDATE[playerid], GetVehicleModel(vehicleid));

			format(str, sizeof(str), "%s", ReturnVehicleModelName(GetVehicleModel(vehicleid)));
			ReplaceSpacesWithUnderscore(str);
			for (new i = 0; str[i] != '\0'; i++) { if ('a' <= str[i] && str[i] <= 'z') { str[i] = str[i] - 'a' + 'A'; } }
			TextDrawSetString(CARNAMEUPDATE[playerid], str);

			new id = Car_GetID(vehicleid);

			if (id != -1)  {
				format(str, sizeof(str), "%s", CarData[id][carPlate]);
				ReplaceSpacesWithUnderscore(str);
				TextDrawSetString(PLATEUPDATE[playerid], str);
			} else {
				TextDrawSetString(PLATEUPDATE[playerid], "TIADA");
			}

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
		SetPlayerArmedWeapon(playerid, 0);
	}
	if ((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && PlayerData[playerid][pPlayRadio])
	{
	    PlayerData[playerid][pPlayRadio] = 0;
	    StopAudioStreamForPlayer(playerid);
	}
	if ((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER))
	{
	    PlayerData[playerid][pSeatBelt] = 0;
		for (new i = 0; i < 3; i ++) 
		{
			TextDrawHideForPlayer(playerid, NoSEATBELT[playerid][i]);
		}
	}
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
	{
	    if (PlayerData[playerid][pBoombox] != INVALID_PLAYER_ID)
	    {
	        PlayerData[playerid][pBoombox] = INVALID_PLAYER_ID;
			StopAudioStreamForPlayer(playerid);
	    }
	    if (IsEngineVehicle(vehicleid) && CoreVehicles[vehicleid][vehRadio])
	    {
	        static
	            url[128];

			strunpack(url, CoreVehicles[vehicleid][vehURL]);

			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, url);

			PlayerData[playerid][pPlayRadio] = 1;
		}
	    foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid) {
     		PlayerSpectateVehicle(i, GetPlayerVehicleID(playerid));
		}
		if (PlayerData[playerid][pInjured] == 1)
		{
		    RemoveFromVehicle(playerid);
		}
	}
	if ((newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER))
	{
		if (IsDoorVehicle(GetPlayerVehicleID(playerid)))
		{ 
			SendClientMessage(playerid, COLOR_WHITE, "SEATBELT: "RED_E"OFF");
			for (new i = 0; i < 3; i ++) 
			{
				TextDrawShowForPlayer(playerid, NoSEATBELT[playerid][i]);
			}
		}
	}
	if (newstate == PLAYER_STATE_PASSENGER)
	{
	    switch (GetPlayerWeapon(playerid))
	    {
	        case 22, 25, 28..33:
	    		SetPlayerArmedWeapon(playerid, GetPlayerWeapon(playerid));

			default:
				SetPlayerArmedWeapon(playerid, 0);
		}
	}
	else if (oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	{
	    foreach (new i : Player) if (PlayerData[i][pSpectator] == playerid) {
     		PlayerSpectatePlayer(i, playerid);
		}
	}
	if (newstate == PLAYER_STATE_PASSENGER && IsPlayerInsideTaxi(playerid))
	{
	    new driverid = GetVehicleDriver(GetPlayerVehicleID(playerid));

	    PlayerData[playerid][pTaxiFee] = 5;
	    PlayerData[playerid][pTaxiTime] = 0;
	    PlayerData[playerid][pTaxiPlayer] = driverid;

	    SendInfoMessage(driverid, "%s has entered your taxi as a passenger.", ReturnName(playerid, 0));
		SendServerMessage(playerid, "You have entered %s's taxi.", ReturnName(driverid, 0));
	}
 	if (oldstate == PLAYER_STATE_PASSENGER && PlayerData[playerid][pTaxiTime] != 0 && PlayerData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID)
	{
	    LeaveTaxi(playerid, PlayerData[playerid][pTaxiPlayer]);
	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
	static str[64], id = -1, keys[3], vehicleid;

	if (PlayerData[playerid][pKicked])
		return 0;

	if (GetPlayerWeapon(playerid) > 1 && (PlayerData[playerid][pMining] > 0))
	    SetPlayerArmedWeapon(playerid, 0);

	if (IsPlayerInAnyVehicle(playerid))
		vehicleid = GetPlayerVehicleID(playerid);
	else
	    vehicleid = INVALID_VEHICLE_ID;

	GetPlayerKeys(playerid, keys[0], keys[1], keys[2]);

	if (GetPlayerMoney(playerid) != 0)
	{
		ResetPlayerMoney(playerid);

		Log_Write("logs/cheat_log.txt", "[%s] %s has possibly money hacks.", ReturnDate(), ReturnName(playerid, 0));
		
		SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(playerid, 0));
		SendClientMessageToAllEx(COLOR_GREY, "Reason: Money Hack");

		KickEx(playerid);
	}

	if (GetPlayerScore(playerid) != PlayerData[playerid][pScore])
	{
		SetPlayerScore(playerid, PlayerData[playerid][pScore]);
	}
	if (PlayerData[playerid][pWaypoint])
	{
	    format(str, sizeof(str), "~R~Waypoint:~w~ %s (%.2f meters)", PlayerData[playerid][pLocation], GetPlayerDistanceFromPoint(playerid, PlayerData[playerid][pWaypointPos][0], PlayerData[playerid][pWaypointPos][1], PlayerData[playerid][pWaypointPos][2]));
		PlayerTextDrawSetString(playerid, WaypointTD[playerid], str);
	}

	if(IsPlayerInRangeOfPoint(playerid, 45, -2659.2727,1410.2560,910.1703))
    {
		if(++ PlayerData[playerid][pClubTime] >= 60) {
            if(PlayerData[playerid][pStress] > 0) { 
                PlayerData[playerid][pStress]--;
            }
            else if(PlayerData[playerid][pStress] < 0) {
				PlayerData[playerid][pClubTime] = 0;
				PlayerData[playerid][pStress] = 0;
            }
            PlayerData[playerid][pClubTime] = 0;
        }
    }
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    if (IsSpeedoVehicle(vehicleid) && !PlayerData[playerid][pDisableSpeedo])
	    {
		    static Float:fDamage;

			GetVehicleHealth(vehicleid, fDamage);

			SetPlayerProgressBarValue(playerid, MINYAKNHEALTH[playerid][0], fDamage);

			format(str, sizeof(str), "%.0f", GetPlayerSpeed(playerid));
			TextDrawSetString(METERUPDATE[playerid], str);

			if(GetPlayerSpeed(playerid) == 0) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][0]); HideTDMETER1(playerid);}
			if(GetPlayerSpeed(playerid) > 10) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][1]); HideTDMETER2(playerid);}
			if(GetPlayerSpeed(playerid) > 20) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][2]); HideTDMETER3(playerid);}
			if(GetPlayerSpeed(playerid) > 30) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][3]); HideTDMETER4(playerid);}
			if(GetPlayerSpeed(playerid) > 40) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][4]); HideTDMETER5(playerid);}
			if(GetPlayerSpeed(playerid) > 50) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][5]); HideTDMETER6(playerid);}
			if(GetPlayerSpeed(playerid) > 60) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][6]); HideTDMETER7(playerid);}
			if(GetPlayerSpeed(playerid) > 70) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][7]); HideTDMETER8(playerid);}
			if(GetPlayerSpeed(playerid) > 80) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][8]); HideTDMETER9(playerid);}
			if(GetPlayerSpeed(playerid) > 90) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][9]); HideTDMETER10(playerid);}
			if(GetPlayerSpeed(playerid) > 100) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][10]); HideTDMETER11(playerid);}
			if(GetPlayerSpeed(playerid) > 110) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][11]); HideTDMETER12(playerid);}
			if(GetPlayerSpeed(playerid) > 120) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][12]); HideTDMETER13(playerid);}
			if(GetPlayerSpeed(playerid) > 130) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][13]); HideTDMETER14(playerid);}
			if(GetPlayerSpeed(playerid) > 140) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][14]); HideTDMETER15(playerid);}
			if(GetPlayerSpeed(playerid) > 150) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][15]); HideTDMETER16(playerid);}
			if(GetPlayerSpeed(playerid) > 160) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][16]); HideTDMETER17(playerid);}
			if(GetPlayerSpeed(playerid) > 170) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][17]); HideTDMETER18(playerid);}
			if(GetPlayerSpeed(playerid) > 180) {TextDrawShowForPlayer(playerid, NEWMETERUPDATE[playerid][18]); }

			new carid = Car_GetID(vehicleid);

			if (carid != -1) 
			{
				SetPlayerProgressBarValue(playerid, MINYAKNHEALTH[playerid][1], CarData[carid][carFuel]);

				SetPlayerProgressBarValue(playerid, MINYAKNHEALTH[playerid][2], CarData[carid][carTemperature]);
			}
		}
		for (new i = 0; i != MAX_BARRICADES; i ++) if (BarricadeData[i][cadeExists] && BarricadeData[i][cadeType] == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, BarricadeData[i][cadePos][0], BarricadeData[i][cadePos][1], BarricadeData[i][cadePos][2]))
		{
			static
			    tires[4];

			GetVehicleDamageStatus(vehicleid, tires[0], tires[1], tires[2], tires[3]);

			if (tires[3] != 1111) {
			    UpdateVehicleDamageStatus(vehicleid, tires[0], tires[1], tires[2], 1111);
			}
			break;
		}
	}
	switch (PlayerData[playerid][pHouseLights])
	{
	    case 0:
	    {
	        if ((id = House_Inside(playerid)) != -1 && !HouseData[id][houseLights])
			{
	        	PlayerData[playerid][pHouseLights] = true;
	            PlayerTextDrawShow(playerid, LampTD[playerid]);
	        }
	        else PlayerTextDrawHide(playerid, LampTD[playerid]);
	    }
	    case 1:
	    {
	        if ((id = House_Inside(playerid)) == -1 || (id != -1 && HouseData[id][houseLights]))
			{
	            PlayerData[playerid][pHouseLights] = false;
                PlayerTextDrawHide(playerid, LampTD[playerid]);
	        }
	    }
	}
 	if ((id = Speed_Nearest(playerid)) != -1 && SpeedData[id][speedStatus] == 1 && GetPlayerSpeed(playerid) > SpeedData[id][speedLimit] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsEngineVehicle(vehicleid) && !PlayerData[playerid][pSpeedTime])
	{
	    if (!IsABoat(vehicleid) && !IsAPlane(vehicleid) && !IsAHelicopter(vehicleid))
	    {
			for (new i = 0; i < MAX_DYNAMIC_CARS; i ++) 
			{
				if(vehicleid == CarData[i][carVehicle] && CarData[i][carGov] == 0)
				{
					SendFactionMessageEx(FACTION_POLICE, COLOR_RADIO, ""YELLOW_E"[SpeedTrap]: "WHITE_E"Suspected Vehicle: %s | Plate : "YELLOW_E"[%s]", ReturnVehicleModelName(CarData[i][carModel]),  CarData[i][carPlate]);
					SendFactionMessageEx(FACTION_POLICE, COLOR_RADIO, ""YELLOW_E"[Detail]: "WHITE_E"Location "YELLOW_E"%s "WHITE_E"| Speed: "YELLOW_E"%.0f km/h", GetLocation(SpeedData[id][speedPos][0], SpeedData[id][speedPos][1], SpeedData[id][speedPos][2]), GetPlayerSpeed(playerid));
 
					SendInfoMessage(playerid, "Caught on Speedcamera!");
				}
			}
			PlayerData[playerid][pSpeedTime] = 5;
		}
	}
	return 1;
}

public OnPlayerConnect(playerid) 
{
	if (IsPlayerNPC(playerid))
	    return 1;

	new
		str[128];

	SetPVarInt(playerid, "DroneSpawned", 0);
    SetPVarFloat(playerid, "OldPosX", 0);
    SetPVarFloat(playerid, "OldPosY", 0);
    SetPVarFloat(playerid, "OldPosZ", 0);

	SendClientMessageToAllEx(COLOR_GREY, "{ff0000}<!>"YELLOW_E" %s "GREEN_E"telah mendarat di negara SakuraRyzen!", ReturnName(playerid, 0));

	ResetPlayerWeapons(playerid);
	SetPlayerArmedWeapon(playerid, 0);
	RemoveDisconnectLabel(playerid);

	SetPlayerInterior(playerid, 0); SetPlayerVirtualWorld(playerid, 0); SetPlayerHealth(playerid, 100); SetPlayerPos(playerid,1445.1062,-2287.3020,13.5469);

	PreloadAnimations(playerid);

	for (new i = 0; i != MAX_PLAYER_ATTACHED_OBJECTS; i ++) {
	    RemovePlayerAttachedObject(playerid, i);
	}

	GetPlayerIp(playerid, PlayerData[playerid][pIP], 16);
	GetPlayerName(playerid, PlayerData[playerid][pUsername], MAX_PLAYER_NAME + 1);

	ResetStatistics(playerid);

	format(str, sizeof(str), "SELECT * FROM `blacklist` WHERE `Username` = '%s' OR `IP` = '%s'", ReturnName(playerid), PlayerData[playerid][pIP]);
	mysql_tquery(g_iHandle, str, "OnQueryFinished", "dd", playerid, THREAD_BAN_LOOKUP);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	format(PlayerData[playerid][pLeaveIP], 16, PlayerData[playerid][pIP]);
 	TerminateConnection(playerid);
	AddDisconnectLabel(playerid, reason);
	return 1;
}

public OnGameModeInit()
{
	LoadMySQLSettings();
	LoadServerSettings();
	DiscordInfoOn();
	ManualVehicleEngineAndLights();
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	SetNameTagDrawDistance(20.0);
	ShowPlayerMarkers(0);
	ShowNameTags(1);

	if (mysql_errno(g_iHandle) != 0)
	    return 0;
 
	mysql_tquery(g_iHandle, "SELECT * FROM `houses`", "House_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `businesses`", "Business_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `dropped`", "Dropped_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `entrances`", "Entrance_Load", "");
	mysql_tquery(g_iHandle, "SELECT * FROM `jobs`", "Job_Load", "");
	mysql_tquery(g_iHandle, "SELECT * FROM `crates`", "Crate_Load", "");
	mysql_tquery(g_iHandle, "SELECT * FROM `plants`", "Plant_Load", "");
	mysql_tquery(g_iHandle, "SELECT * FROM `factions`", "Faction_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `gates`", "Gate_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `backpacks`", "Backpack_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `atm`", "ATM_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `garbage`", "Garbage_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `vendors`", "Vendor_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `gunracks`", "Rack_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `speedcameras`", "Speed_Load", "");
    mysql_tquery(g_iHandle, "SELECT * FROM `graffiti`", "Graffiti_Load", "");
	mysql_tquery(g_iHandle, "SELECT * FROM `rentpoints`", "Rent_Load", "");

	SetWeather(WorldWeather);
	SetWorldTime(WorldTime);

    SetModelPreviewRotation(18875, 90.0, 180.0, 0.0);
    SetModelPreviewRotation(2703, -105.0, 0.0, -15.0);
    SetModelPreviewRotation(2702, 90.0, 90.0, 0.0);
    SetModelPreviewRotation(2814, -90.0, 0.0, -90.0);
    SetModelPreviewRotation(2768, -15.0, 0.0, -160.0);
    SetModelPreviewRotation(19142, -20.0, -90.0, 0.0);
    SetModelPreviewRotation(1581, 0.0, 0.0, 180.0);
    SetModelPreviewRotation(2958, -10.0, -15.0, 0.0);
    SetModelPreviewRotation(1575, 0.0, 0.0, 180.0);
    SetModelPreviewRotation(1577, 0.0, 0.0, 180.0);
    SetModelPreviewRotation(1578, 0.0, 0.0, 180.0);
    SetModelPreviewRotation(18634, 90.0, 90.0, 0.0);
    SetModelPreviewRotation(2043, 0.0, 0.0, 90.0);
    SetModelPreviewRotation(1484, -15.0, 30.0, 0.0);
    SetModelPreviewRotation(2226, 0.0, 0.0, 180.0);

	// Timer
	SetTimer("BotDiscord", 1000, true);
	SetTimer("PlayerCheck", 1000, true);
	SetTimer("VehicleCheck", 1000, true);
	SetTimer("CarDataUpdate", 50000, true);
	SetTimer("RefuelCheck", 500, true);
	SetTimer("LotteryUpdate", 2700000, true);
	SetTimer("MinuteCheck", 60000, true);
	SetTimer("OnlineTimer", 1000, true);

	printf("** Sakura Ryzen resources successfully loaded!");

	return 1;
}

public OnGameModeExit()
{
	DiscordInfoOff();
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    if (IsPlayerNPC(playerid))
	    return 1;

	TogglePlayerSpectating(playerid, 1);
	InterpolateCameraPos(playerid, 1434.8920, -2286.6963, 14.0000, 1375.8654, -2286.0576, 29.4124, 5000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, 1434.8920, -2286.6963, 14.0000, 1375.8654, -2286.0576, 29.4124, 5000, CAMERA_MOVE);

	SetTimerEx("SQL_CheckAccount", 5000, false, "i", playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
    // Skill levels
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 0);

    Streamer_ToggleIdleUpdate(playerid, true);

	SetPlayerColor(playerid, DEFAULT_COLOR);

	if(PlayerData[playerid][pFacSkin] > 0)
	{
		SetPlayerSkin(playerid, PlayerData[playerid][pFacSkin]);
	}
	else
	{
		SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	}

	PlayerData[playerid][pKilled] = 0;

	if (PlayerData[playerid][pJailTime] > 0)
	{
	    if (PlayerData[playerid][pPrisoned])
	    {
	        SetPlayerInPrison(playerid);
	    }
	    else
	    {
		    SetPlayerPosEx(playerid, 197.6346, 175.3765, 1003.0234);
		    SetPlayerInterior(playerid, 3);

		    SetPlayerVirtualWorld(playerid, (playerid + 100));
		    SetPlayerFacingAngle(playerid, 0.0);

		    SetCameraBehindPlayer(playerid);
		}
		ResetWeapons(playerid);

	    SendInfoMessage(playerid, "Anda mempunyai %d saat baki masa penjara admin.", PlayerData[playerid][pJailTime]);
	}
	else if (!PlayerData[playerid][pCreated])
	{
		SetDefaultSpawn(playerid);
		ShowHungerTextdraw(playerid, 1);

		SetPlayerHealthEx(playerid, 100);
		SetPlayerArmourEx(playerid, 0);

		PlayerData[playerid][pCreated] = 1;

		SendServerMessage(playerid, "Anda telah berjaya menyediakan watak! Selamat bermain.");
	}
	else
	{
		SetPlayerFacingAngle(playerid, PlayerData[playerid][pPos][3]);

	    SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);

		SetCameraBehindPlayer(playerid);
		SetAccessories(playerid);

		if (PlayerData[playerid][pInjured])
		{
		    SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

			SendInfoMessage(playerid, "Anda telah pengsan dan memerlukan rawatan perubatan (/call 911).");

			ApplyAnimation(playerid, "CRACK", "null", 4.0, 0, 0, 0, 1, 0, 1);
			ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
		}
		else
		{
			ShowHungerTextdraw(playerid, 1);

			SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
			SetPlayerArmour(playerid, PlayerData[playerid][pArmorStatus]);
		}
	}
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if (!success) {
        return SendErrorMessage(playerid, "Command yang dimasukkan tidak ditemui.");
    }
	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if (!SQL_IsLogged(playerid) || (PlayerData[playerid][pKilled] > 0))
	    return 0;

	if (PlayerData[playerid][pMuted] && strfind(cmdtext, "/unmute", true) != 0)
 	{
	    SendErrorMessage(playerid, "Anda kini di mute. Command tidak dapat di-gunakan.");
	    return 0;
	}
	if (PlayerData[playerid][pCommandCount] < 6)
	{
	    PlayerData[playerid][pCommandCount]++;

	    if (PlayerData[playerid][pCommandCount] == 6) {
	        PlayerData[playerid][pCommandCount] = 0;

	        PlayerData[playerid][pMuted] = 1;
	        PlayerData[playerid][pMuteTime] = 5;

	        SendInfoMessage(playerid, "Anda telah di mute kerana spam command (5 saat).");
	        SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s telah di mute oleh bot kerana spam command.", ReturnName(playerid, 0));

	        return 0;
		}
	}
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if (!PlayerData[playerid][pLogged] && !PlayerData[playerid][pCharacter])
	    return 0;

	if (PlayerData[playerid][pMuted])
	{
	    SendErrorMessage(playerid, "Anda kini di mute. Chat tidak dapat di-gunakan.");
	    return 0;
	}
	if (PlayerData[playerid][pSpamCount] < 5)
	{
	    PlayerData[playerid][pSpamCount]++;

	    if (PlayerData[playerid][pSpamCount] == 5) {
	        PlayerData[playerid][pSpamCount] = 0;

	        PlayerData[playerid][pMuted] = 1;
	        PlayerData[playerid][pMuteTime] = 5;

	        SendInfoMessage(playerid, "Anda telah di mute kerana spam di chat (5 saat).");
	        SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s telah di mute oleh bot kerana spam di chat.", ReturnName(playerid, 0));
	        return 0;
		}
	}
	new
		targetid = PlayerData[playerid][pCallLine];

	SetPlayerChatBubble(playerid, text, COLOR_WHITE, 10.0, 6000);

	if (IsPlayerInAnyVehicle(playerid) && IsWindowedVehicle(GetPlayerVehicleID(playerid)) && !CoreVehicles[GetPlayerVehicleID(playerid)][vehWindowsDown])
		SendVehicleMessage(GetPlayerVehicleID(playerid), 0xBBFFEEFF, "[INCAR] {c99718}%s: {33ff00}%s", ReturnName(playerid, 0), text);

	else
	{
		if (!IsPlayerOnPhone(playerid))
		{
			if(PlayerData[playerid][pAdminDuty] >= 1)
			{
				SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "{1cc7aa}[TALK] "RED_E"%s: {33ff00}%s", ReturnName(playerid, 0), text);
			}
			else
			{
				SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "{1cc7aa}[TALK] {c99718}%s: {33ff00}%s", ReturnName(playerid, 0), text);
			}
		}
		else 
		{
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, ""YELLOW_E"[PHONE] {c99718}%s: {33ff00}%s", ReturnName(playerid, 0), text);
		}
	}
	switch (PlayerData[playerid][pEmergency])
	{
		case 1:
		{
			if (!strcmp(text, "police", true))
			{
				PlayerData[playerid][pEmergency] = 2;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]: You've been dispatched to police HQ. Please describe the crime.");
			}
			else if (!strcmp(text, "medics", true))
			{
				PlayerData[playerid][pEmergency] = 3;
				SendClientMessage(playerid, COLOR_HOSPITAL, "[OPERATOR]: You've been dispatched to medical HQ. Please describe the emergency.");
			}
			else SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]: Sorry, I don't understand. Do you require \"police\" or \"medics\"?");
		}
		case 2:
		{
			SendFactionMessageEx(FACTION_POLICE, COLOR_RADIO, "911 CALL: %s (%s)", ReturnName(playerid, 0), GetPlayerLocation(playerid));
			SendFactionMessageEx(FACTION_POLICE, COLOR_RADIO, "DESCRIPTION: %s", text);

			SendClientMessage(playerid, COLOR_LIGHTBLUE, "[OPERATOR]: We have alerted all units in the area.");
			cmd_hangup(playerid, "\1");
		}
		case 3:
		{
			SendFactionMessageEx(FACTION_MEDIC, COLOR_HOSPITAL, "911 CALL: %s (%s)", ReturnName(playerid, 0), GetPlayerLocation(playerid));
			SendFactionMessageEx(FACTION_MEDIC, COLOR_HOSPITAL, "DESCRIPTION: %s", text);

			SendClientMessage(playerid, COLOR_HOSPITAL, "[OPERATOR]: We have alerted all units in the area.");
			cmd_hangup(playerid, "\1");
		}
	}
	switch (PlayerData[playerid][pPlaceAd])
	{
		case 1:
		{
			if (!strcmp(text, "yes", true))
			{
				if (GetMoney(playerid) < 500)
				{
					SendClientMessage(playerid, COLOR_CYAN, "[OPERATOR]: Sorry, you have insufficient funds to advertise right now.");
					cmd_hangup(playerid, "\1");
				}
				else
				{
					PlayerData[playerid][pPlaceAd] = 2;
					SendClientMessage(playerid, COLOR_CYAN, "[OPERATOR]: Please specify your advertisement and we'll advertise it.");
				}
			}
		}
		case 2:
		{
			if (GetMoney(playerid) < 500)
			{
				SendClientMessage(playerid, COLOR_CYAN, "[OPERATOR]: Sorry, you have insufficient funds to advertise right now.");
				cmd_hangup(playerid, "\1");
			}
			else
			{
				GiveMoney(playerid, -500);
				SetTimerEx("Advertise", 3000, false, "d", playerid);

				PlayerData[playerid][pAdTime] = 120;
				strpack(PlayerData[playerid][pAdvertise], text, 128 char);

				SendClientMessage(playerid, COLOR_CYAN, "[OPERATOR]: Your advertisement will be published shortly.");
				cmd_hangup(playerid, "\1");
			}
		}
	}
	if (targetid != INVALID_PLAYER_ID && !PlayerData[playerid][pIncomingCall])
	{
		SendClientMessageEx(targetid, COLOR_YELLOW, ""YELLOW_E"[PHONE] {c99718}%s: {33ff00}%s", ReturnName(playerid, 0), text);
	}
	return 0;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (response == EDIT_RESPONSE_FINAL)
	{
	    if (PlayerData[playerid][pEditGraffiti] != -1 && GraffitiData[PlayerData[playerid][pEditGraffiti]][graffitiExists])
	    {
			GraffitiData[PlayerData[playerid][pEditGraffiti]][graffitiPos][0] = x;
			GraffitiData[PlayerData[playerid][pEditGraffiti]][graffitiPos][1] = y;
			GraffitiData[PlayerData[playerid][pEditGraffiti]][graffitiPos][2] = z;
			GraffitiData[PlayerData[playerid][pEditGraffiti]][graffitiPos][3] = rz;

			Graffiti_Refresh(PlayerData[playerid][pEditGraffiti]);
			Graffiti_Save(PlayerData[playerid][pEditGraffiti]);
		}
	    else if (PlayerData[playerid][pEditRack] != -1 && RackData[PlayerData[playerid][pEditRack]][rackExists])
	    {
			RackData[PlayerData[playerid][pEditRack]][rackPos][0] = x;
			RackData[PlayerData[playerid][pEditRack]][rackPos][1] = y;
			RackData[PlayerData[playerid][pEditRack]][rackPos][2] = z;
			RackData[PlayerData[playerid][pEditRack]][rackPos][3] = rz;

			Rack_Refresh(PlayerData[playerid][pEditRack]);
			Rack_Save(PlayerData[playerid][pEditRack]);
		}
	    else if (PlayerData[playerid][pEditPump] != -1 && PumpData[PlayerData[playerid][pEditPump]][pumpExists])
	    {
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][0] = x;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][1] = y;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][2] = z;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][3] = rz;

			Pump_Refresh(PlayerData[playerid][pEditPump]);
			Pump_Save(PlayerData[playerid][pEditPump]);

			SendServerMessage(playerid, "You have edited the position of pump ID: %d.", PlayerData[playerid][pEditPump]);
	    }
	    else if (PlayerData[playerid][pEditFurniture] != -1 && FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureExists])
	    {
	        new id = House_Inside(playerid);

	        if (id != -1 && House_IsOwner(playerid, id))
			{
			    FurnitureData[PlayerData[playerid][pEditFurniture]][furniturePos][0] = x;
			    FurnitureData[PlayerData[playerid][pEditFurniture]][furniturePos][1] = y;
			    FurnitureData[PlayerData[playerid][pEditFurniture]][furniturePos][2] = z;
                FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureRot][0] = rx;
                FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureRot][1] = ry;
                FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureRot][2] = rz;

				Furniture_Refresh(PlayerData[playerid][pEditFurniture]);
				Furniture_Save(PlayerData[playerid][pEditFurniture]);

				SendServerMessage(playerid, "You have edited the position of item \"%s\".", FurnitureData[PlayerData[playerid][pEditFurniture]][furnitureName]);
			}
	    }
	    else if (PlayerData[playerid][pEditGate] != -1 && GateData[PlayerData[playerid][pEditGate]][gateExists])
	    {
	        switch (PlayerData[playerid][pEditType])
	        {
	            case 1:
	            {
	                new id = PlayerData[playerid][pEditGate];

	                GateData[PlayerData[playerid][pEditGate]][gatePos][0] = x;
	                GateData[PlayerData[playerid][pEditGate]][gatePos][1] = y;
	                GateData[PlayerData[playerid][pEditGate]][gatePos][2] = z;
	                GateData[PlayerData[playerid][pEditGate]][gatePos][3] = rx;
	                GateData[PlayerData[playerid][pEditGate]][gatePos][4] = ry;
	                GateData[PlayerData[playerid][pEditGate]][gatePos][5] = rz;

	                DestroyDynamicObject(GateData[id][gateObject]);
					GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);

					Gate_Save(id);
                    SendServerMessage(playerid, "You have edited the position of gate ID: %d.", id);
				}
				case 2:
	            {
	                new id = PlayerData[playerid][pEditGate];

	                GateData[PlayerData[playerid][pEditGate]][gateMove][0] = x;
	                GateData[PlayerData[playerid][pEditGate]][gateMove][1] = y;
	                GateData[PlayerData[playerid][pEditGate]][gateMove][2] = z;
	                GateData[PlayerData[playerid][pEditGate]][gateMove][3] = rx;
	                GateData[PlayerData[playerid][pEditGate]][gateMove][4] = ry;
	                GateData[PlayerData[playerid][pEditGate]][gateMove][5] = rz;

	                DestroyDynamicObject(GateData[id][gateObject]);
					GateData[id][gateObject] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gatePos][0], GateData[id][gatePos][1], GateData[id][gatePos][2], GateData[id][gatePos][3], GateData[id][gatePos][4], GateData[id][gatePos][5], GateData[id][gateWorld], GateData[id][gateInterior]);

					Gate_Save(id);
                    SendServerMessage(playerid, "You have edited the moving position of gate ID: %d.", id);
				}
			}
		}
	}
	if (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	{
	    if (PlayerData[playerid][pEditFurniture] != -1)
			Furniture_Refresh(PlayerData[playerid][pEditFurniture]);

	    if (PlayerData[playerid][pEditPump] != -1)
			Pump_Refresh(PlayerData[playerid][pEditPump]);

        if (PlayerData[playerid][pEditRack] != -1)
			Rack_Refresh(PlayerData[playerid][pEditRack]);

        if (PlayerData[playerid][pEditGraffiti] != -1)
			Graffiti_Refresh(PlayerData[playerid][pEditGraffiti]);

	    PlayerData[playerid][pEditType] = 0;
	    PlayerData[playerid][pEditGate] = -1;
		PlayerData[playerid][pEditPump] = -1;
		PlayerData[playerid][pGasStation] = -1;
		PlayerData[playerid][pEditFurniture] = -1;
		PlayerData[playerid][pEditGraffiti] = -1;
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if (response)
	{
		if (PlayerData[playerid][pEditType] != 0)
 		{
 		    AccessoryData[playerid][PlayerData[playerid][pEditType]-1][0] = fOffsetX;
       		AccessoryData[playerid][PlayerData[playerid][pEditType]-1][1] = fOffsetY;
         	AccessoryData[playerid][PlayerData[playerid][pEditType]-1][2] = fOffsetZ;

          	AccessoryData[playerid][PlayerData[playerid][pEditType]-1][3] = fRotX;
           	AccessoryData[playerid][PlayerData[playerid][pEditType]-1][4] = fRotY;
           	AccessoryData[playerid][PlayerData[playerid][pEditType]-1][5] = fRotZ;

            AccessoryData[playerid][PlayerData[playerid][pEditType]-1][6] = (fScaleX > 3.0) ? (3.0) : (fScaleX);
            AccessoryData[playerid][PlayerData[playerid][pEditType]-1][7] = (fScaleY > 3.0) ? (3.0) : (fScaleY);
			AccessoryData[playerid][PlayerData[playerid][pEditType]-1][8] = (fScaleZ > 3.0) ? (3.0) : (fScaleZ);

			switch (PlayerData[playerid][pEditType])
			{
	  			case 1:
	    		{
		            PlayerData[playerid][pEditType] = 0;
		            PlayerData[playerid][pGlasses] = modelid;

		            SendServerMessage(playerid, "You have confirmed your glasses.");
				}
				case 2:
	    		{
	                PlayerData[playerid][pEditType] = 0;
		            PlayerData[playerid][pHat] = modelid;

		            SendServerMessage(playerid, "You have confirmed your hat.");
				}
				case 3:
	    		{
	                PlayerData[playerid][pEditType] = 0;
		            PlayerData[playerid][pBandana] = modelid;

		            SendServerMessage(playerid, "You have confirmed your bandana.");
				}
			}
	    }
	}
	return 1;
}

public OnModelSelectionResponse(playerid, extraid, index, modelid, response)
{
	if ((extraid == MODEL_SELECTION_INVENTORY && response) && InventoryData[playerid][index][invExists])
	{
	    new
	        name[48],
			id = -1,
			backpack = GetPlayerBackpack(playerid);

		strunpack(name, InventoryData[playerid][index][invItem]);
	    PlayerData[playerid][pInventoryItem] = index;

		switch (PlayerData[playerid][pStorageSelect])
		{
		    case 1:
		    {
		    	if ((id = House_Inside(playerid)) != -1 && House_IsOwner(playerid, id))
				{
					if (InventoryData[playerid][index][invQuantity] == 1)
					{
					    if (!strcmp(name, "Backpack") && GetHouseBackpack(id) != -1)
					        return SendErrorMessage(playerid, "You can only store one backpack in your house.");

		        		House_AddItem(id, name, InventoryData[playerid][index][invModel], 1);
		        		Inventory_Remove(playerid, name);

		        		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their house storage.", ReturnName(playerid, 0), name);
				 		House_ShowItems(playerid, id);

				 		if (!strcmp(name, "Backpack") && backpack != -1)
						{
					        BackpackData[backpack][backpackPlayer] = 0;
					        BackpackData[backpack][backpackHouse] = HouseData[id][houseID];

							Backpack_Save(backpack);
							SetAccessories(playerid);
					    }
		        	}
		        	else Dialog_Show(playerid, HouseDeposit, DIALOG_STYLE_INPUT, "House Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", name, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);
				}
				PlayerData[playerid][pStorageSelect] = 0;
			}
			case 2:
		    {
		    	if ((id = Car_Nearest(playerid)) != -1 && !CarData[id][carLocked])
				{
					if (InventoryData[playerid][index][invQuantity] == 1)
					{
					    if (!strcmp(name, "Backpack") && GetVehicleBackpack(id) != -1)
					        return SendErrorMessage(playerid, "You can only store one backpack in your trunk.");

		        		Car_AddItem(id, name, InventoryData[playerid][index][invModel], 1);
		        		Inventory_Remove(playerid, name);

		        		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into the trunk.", ReturnName(playerid, 0), name);
				 		Car_ShowTrunk(playerid, id);

				 		if (!strcmp(name, "Backpack") && backpack != -1)
						{
					        BackpackData[backpack][backpackPlayer] = 0;
					        BackpackData[backpack][backpackVehicle] = CarData[id][carID];

							Backpack_Save(backpack);
							SetAccessories(playerid);
					    }
		        	}
		        	else Dialog_Show(playerid, CarDeposit, DIALOG_STYLE_INPUT, "Car Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", name, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);
				}
				PlayerData[playerid][pStorageSelect] = 0;
			}
			case 3:
		    {
		        if (!strcmp(name, "Backpack"))
		            return SendErrorMessage(playerid, "This item cannot be stored.");

		    	if (InventoryData[playerid][index][invQuantity] == 1)
				{
					Backpack_Add(GetPlayerBackpack(playerid), name, InventoryData[playerid][index][invModel], 1);
   					Inventory_Remove(playerid, name);

					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their backpack.", ReturnName(playerid, 0), name);
					Backpack_Open(playerid);
				}
   				else
	   			{
				   	Dialog_Show(playerid, BackpackDeposit, DIALOG_STYLE_INPUT, "Backpack Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", name, InventoryData[playerid][PlayerData[playerid][pInventoryItem]][invQuantity]);
				}
				PlayerData[playerid][pStorageSelect] = 0;
			}
			default:
			{
			    format(name, sizeof(name), "%s (%d)", name, InventoryData[playerid][index][invQuantity]);

		    	if (Garbage_Nearest(playerid) != -1) {
					Dialog_Show(playerid, Inventory, DIALOG_STYLE_LIST, name, "Use Item\nGive Item\nThrow Out", "Select", "Cancel");
				}
				else {
				    Dialog_Show(playerid, Inventory, DIALOG_STYLE_LIST, name, "Use Item\nGive Item\nDrop Item", "Select", "Cancel");
				}
			}
		}
	}
	if ((extraid == MODEL_SELECTION_FRISK && response) && InventoryData[playerid][index][invExists])
	{
	    new
	        name[48];

		strunpack(name, InventoryData[PlayerData[playerid][pGiveItem]][index][invItem]);
	    PlayerData[PlayerData[playerid][pGiveItem]][pInventoryItem] = index;

		Dialog_Show(playerid, TakeItem, DIALOG_STYLE_INPUT, "Take Item", "Item: %s (Quantity: %d)\n\nPlease enter the amount of this item you want to take:", "Take", "Cancel", name, InventoryData[PlayerData[playerid][pGiveItem]][index][invQuantity]);
	}
	if ((response) && (extraid == MODEL_SELECTION_SKIN))
	{
	    PlayerData[playerid][pSkin] = modelid;
	
		SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1684.4392, 1771.6658, 10.8203, 270.0000, 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, 0);
	}
	if ((response) && (extraid == MODEL_SELECTION_CLOTHES))
	{
	    new
			bizid = -1,
			price;

	    if ((bizid = Business_Inside(playerid)) == -1 || BusinessData[bizid][bizType] != 3)
	        return 0;

		if (BusinessData[bizid][bizProducts] < 1)
		    return SendErrorMessage(playerid, "This business is out of stock.");

	    price = BusinessData[bizid][bizPrices][PlayerData[playerid][pClothesType] - 1];

	    if (GetMoney(playerid) < price)
	        return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

		GiveMoney(playerid, -price);

		BusinessData[bizid][bizProducts]--;
		BusinessData[bizid][bizVault] += price;

		Business_Save(bizid);

	    switch (PlayerData[playerid][pClothesType])
	    {
	        case 1:
	        {
	            PlayerData[playerid][pSkin] = modelid;
	            SetPlayerSkin(playerid, modelid);

	            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some clothes.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 2:
			{
			    PlayerData[playerid][pEditType] = 1;
                PlayerData[playerid][pGlasses] = modelid;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some glasses.", ReturnName(playerid, 0), FormatNumber(price));
				RemovePlayerAttachedObject(playerid, 0);

                SetPlayerAttachedObject(playerid, 0, modelid, 2, 0.094214, 0.044044, -0.007274, 89.675476, 83.514060, 0.000000);
				EditAttachedObject(playerid, 0);
			}
			case 3:
			{
			    PlayerData[playerid][pHat] = modelid;
			    PlayerData[playerid][pEditType] = 2;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a hat.", ReturnName(playerid, 0), FormatNumber(price));
                RemovePlayerAttachedObject(playerid, 1);

				SetPlayerAttachedObject(playerid, 1, modelid, 2, 0.1565, 0.0273, -0.0002, -7.9245, -1.3224, 15.0999);
				EditAttachedObject(playerid, 1);
			}
			case 4:
			{
			    PlayerData[playerid][pBandana] = modelid;
			    PlayerData[playerid][pEditType] = 3;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a bandana.", ReturnName(playerid, 0), FormatNumber(price));
			    RemovePlayerAttachedObject(playerid, 2);

			    SetPlayerAttachedObject(playerid, 2, modelid, 2, 0.099553, 0.044356, -0.000285, 89.675476, 84.277572, 0.000000);
				EditAttachedObject(playerid, 2);
			}
	    }
	}
	if ((response) && (extraid == MODEL_SELECTION_DEALER))
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
 	    {
	        if (!DealershipCars[id][index][vehModel])
	        {
	            Dialog_Show(playerid, AddVehicle, DIALOG_STYLE_LIST, "Add Vehicle", "Add by Name\nAdd by Thumbnail", "Select", "Cancel");
			}
			else
			{
			    PlayerData[playerid][pDealerCar] = index;
			    Dialog_Show(playerid, CarOptions, DIALOG_STYLE_LIST, "Dealership Vehicle", "Set Price (%s)\nRemove Vehicle", "Select", "Cancel", FormatNumber(DealershipCars[id][index][vehPrice]));
			}
	    }
	}
	if ((response) && (extraid == MODEL_SELECTION_DEALER_ADD))
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
	        for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
			{
				if (DealershipCars[id][i][vehModel] == modelid)
	            	return SendErrorMessage(playerid, "This vehicle is already sold at this dealership.");
			}
			PlayerData[playerid][pDealerCar] = modelid;
			Dialog_Show(playerid, DealerCarPrice, DIALOG_STYLE_INPUT, "Enter Price", "Please enter a price for '%s':", "Submit", "Cancel", ReturnVehicleModelName(PlayerData[playerid][pDealerCar]));
		}
	}
	if ((response) && (extraid == MODEL_SELECTION_BUY_CAR))
	{
	    new id = Business_Inside(playerid);

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
		    if (!DealershipCars[id][index][vehModel])
		        return SendErrorMessage(playerid, "There is no model in the selected slot.");

		    if (GetMoney(playerid) < DealershipCars[id][index][vehPrice])
	    	    return SendErrorMessage(playerid, "You can't afford this vehicle (%s).", FormatNumber(DealershipCars[id][index][vehPrice]));

			PlayerData[playerid][pDealerCar] = index;
			Dialog_Show(playerid, ConfirmCarBuy, DIALOG_STYLE_MSGBOX, "Confirm Purchase", "Are you sure you want to buy this '%s'?\n\nNote: This vehicle costs %s at this dealership.", "Yes", "No", ReturnVehicleModelName(modelid), FormatNumber(DealershipCars[id][index][vehPrice]));
		}
	}
	if ((response) && (extraid == MODEL_SELECTION_FURNITURE))
	{
        new
			id = Business_Inside(playerid),
			type = PlayerData[playerid][pFurnitureType],
			price;

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 7)
	    {
	        price = BusinessData[id][bizPrices][type];

	        if (GetMoney(playerid) < price)
	            return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

			if (BusinessData[id][bizProducts] < 1)
		    	return SendErrorMessage(playerid, "This business is out of stock.");

			new item = Inventory_Add(playerid, GetFurnitureNameByModel(modelid), modelid);

            if (item == -1)
   	        	return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			GiveMoney(playerid, -price);
			SendServerMessage(playerid, "You have purchased a \"%s\" for %s.", GetFurnitureNameByModel(modelid), FormatNumber(price));

			BusinessData[id][bizProducts]--;
			BusinessData[id][bizVault] += price;

			Business_Save(id);
	    }
	}
	if ((response) && (extraid == MODEL_SELECTION_SKINS))
	{
	    Dialog_Show(playerid, FactionSkin, DIALOG_STYLE_LIST, "Edit Skin", "Add by Model ID\nAdd by Thumbnail\nClear Slot", "Select", "Cancel");
	    PlayerData[playerid][pSelectedSlot] = index;
	}
	if ((response) && (extraid == MODEL_SELECTION_ADD_SKIN))
	{
	    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = modelid;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot], modelid);
	}
	if ((response) && (extraid == MODEL_SELECTION_FACTION_SKIN))
	{
	    new factionid = PlayerData[playerid][pFaction];

		if (factionid == -1 || !IsNearFactionLocker(playerid))
	    	return 0;

		if (modelid == 19300)
		    return SendErrorMessage(playerid, "There is no model in the selected slot.");

  		SetPlayerSkin(playerid, modelid);
		PlayerData[playerid][pFacSkin] = modelid,
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has changed their uniform.", ReturnName(playerid, 0));
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(PlayerData[playerid][pAdminDuty] >= 1)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid > 0)
        {
            SetVehiclePos(vehicleid, fX, fY, fZ+10);
        }
        else
        {
            SetPlayerPosFindZ(playerid, fX, fY, fZ+100);
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
        }
    }
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    if(PlayerData[playerid][pAdminDuty] >= 1)
	{
	    SendPlayerToPlayer(playerid, clickedplayerid);
    }
    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == LOGINTD[11])
	{
		if (PlayerData[playerid][pPin] == 0) 
		{
			Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, ""WHITE_E"Log Masuk", "Sila masukkan kata laluan anda dibawah:", "Masuk", "Keluar");
		}
		else 
		{
			Dialog_Show(playerid, PinAccount, DIALOG_STYLE_INPUT, ""WHITE_E"Pin Akaun", "Sila masukkan pin anda dibawah:", "Masuk", "Keluar");
		}
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	return 1;
}

public OnPlayerTeleport(playerid, Float:distance)
{
	if(PlayerData[playerid][pAdminDuty] == 0)
	{
	    if(!IsPlayerInRangeOfPoint(playerid, 3.0, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]))
	    {
		    PlayerData[playerid][pAcWarn]++;

		    if(PlayerData[playerid][pAcWarn] < 3)
		    {
				SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s is possibly teleport hacking (distance: %.1f).", ReturnName(playerid, 0), distance);
			}
			else
			{
				Log_Write("logs/cheat_log.txt", "[%s] %s has possibly teleport hacks.", ReturnDate(), ReturnName(playerid, 0));
				
				SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(playerid, 0));
				SendClientMessageToAllEx(COLOR_GREY, "Reason: Teleport Hack");

		    	KickEx(playerid);
			}
		}
	}

	return 1;
}

public OnPlayerAirbreak(playerid)
{
	if(PlayerData[playerid][pAdminDuty] == 0)
	{
	    PlayerData[playerid][pAcWarn]++;

	    if(PlayerData[playerid][pAcWarn] < 3)
	    {
	        SendAdminAlert(COLOR_RED,  "[ADMIN]:"WHITE_E" %s is possibly airbreak hacking.", ReturnName(playerid, 0));
		}
		else
		{
			Log_Write("logs/cheat_log.txt", "[%s] %s has possibly airbreak hacks.", ReturnDate(), ReturnName(playerid, 0));
			
			SendClientMessageToAllEx(COLOR_GREY, "BotSys: Bot has kicked %s", ReturnName(playerid, 0));
			SendClientMessageToAllEx(COLOR_GREY, "Reason: Airbreak Hack");
 
			KickEx(playerid);
		}
	}
	return 1;
}

// --------------------------------- End Callbacks