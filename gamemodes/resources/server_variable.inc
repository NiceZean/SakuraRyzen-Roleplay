enum MYSQL_SETTINGS
{
    DOOME_HOST,
    DOOME_USERNAME,
    DOOME_PASSWORD,
    DOOME_DATABASE
}

enum playerData {
	pID,
	pLogged,
	pIP[16],
	pLoginDate[36],
	pUsername[MAX_PLAYER_NAME + 1],
	pName[MAX_PLAYER_NAME + 1],
	pCreated,
	pLastLogin,
	pGender,
	pStaterpack,
	pBirthdate[24],
	pOrigin[32], 
	pSkin,
	pEditType,
	pGlasses,
	pHat,
	pBandana,
	Float:pPos[4],
	Float:pHealth,
	pInterior,
	pWorld,
	pVest,
	pCharacter,
	pRepairTime,
	pKilled,
	pMoney,
	pBankMoney,
	pSavings,
	pAdmin,
	pReportTime,
	pHelpTime,
	pSpectator,
	pJailTime,
	pKicked,
	pMuted,
	pCharacterMenu,
	pToggleGlasses,
	pToggleHat,
	pToggleBandana,
	pToggleArmor,
	pLastShot,
	pShotTime,
	pInventoryItem,
	pStorageItem,
	pStorageSelect,
	pProductModify,
	pGuns[13],
	pAmmo[13],
	pHouse,
	pBusiness,
	pEntrance,
	pDealership,
	pContact,
	pGasPump,
	pGasStation,
	pEditPump,
	pEditFurniture,
	pEditGate,
	pEditRack, 
	pSelectFurniture,
	pRefill,
	pRefillPrice,
	pDealerCar,
	pEditingItem[32 char],
	pHouseSeller,
	pHouseOffered,
	pHouseValue,
	pBusinessSeller,
	pBusinessOffered,
	pBusinessValue,
	pCarSeller,
	pCarOffered,
	pCarValue,
	pShakeOffer,
	pShakeType,
	pSeatBelt,
	pFriskOffer,
	pFoodSeller,
	pFoodType,
	pFoodPrice,
	pFactionOffer,
	pFactionOffered,
	pHouseLights,
	pPhone,
	pLottery,
	pLotteryB,
	pClubTime,
	pBodyInsurance,
	pUraine,
	pHunger,
	pThirst,
	pHungerTime,
	pThirstTime,
	pStress,
	pStressTime,
	pCooking,
	pCookingTime,
	pCookingHouse,
	pScore,
	pMinutes,
	Float:pArmorStatus,
	pArmorShown,
	pAcWarn,
	pClothesType,
	pDrivingTest,
	pTestStage,
	pTestCar,
	pTestWarns,
	pFurnitureType,
	pJob,
	pTaxiFee,
	pTaxiTime,
	pTaxiPlayer,
	pTaxiDuty,
	pFirstAid,
	pHelmet,
	pAidTimer,
	pIncomingCall,
	pCallLine,
	pMining,
	pMineTime,
	pMineCount,
	pMinedRock,
	pCarryTrash,
	pCarryCrate,
	pCrateVehicle,
	pCrafting,
	pOpeningCrate,
	pHarvesting,
	pFaction,
	pFactionID,
	pFactionRank,
	pFactionEdit,
	pSelectedSlot,
	pOnDuty,
	pFacSkin,
	pTazer,
	pBeanBag,
	pStunned,
	pCuffed,
	pDragged,
	pDraggedBy,
	pDragTimer,
	pWarrants,
	pMDCPlayer,
	pTrackTime,
	pCP,
	pPrisoned,
	pInjured,
	pInjuredTime,
	pSpamCount,
	pCommandCount,
	pMuteTime,
	pTransfer,
	pWaypoint,
	pLocation[32],
	Float:pWaypointPos[3],
	pFuelCan,
	pDisableSpeedo,
	pDrugUsed,
	pDrugTime,
	pFingerTime,
	pFingerItem,
	pHealthTime,
	pWeapon,
	pBackpackLoot,
	pGiveItem,
	pChannel,
	pEmergency,
	pPlaceAd,
	pAdTime,
	pTargets,
	pTargetLevel,
	pVendorTime,
	pLoopAnim,
	pExecute,
	pBoombox,
	pDrinkTime,
	pAdvertise[128 char],
	pTaxiCalled,
	pLoadType,
	pLoadCrate,
	pLoading,
	pUnloading,
	pUnloadVehicle,
	pShipment,
	pDeliverShipment,
	pWarnings,
 	pWarn1[32],
	pWarn2[32],
	pSorting,
	pSortCrate,
	pAdminDuty,
	pSeekHelp,
	pHUD,
	pMaskID,
	pMaskOn,
	pHideTags,
	pFactionMod,
	pCapacity,
	pPlayRadio,
	pLeaveIP[16],
	pGraffiti,
	pGraffitiTime,
	pGraffitiColor,
	pGraffitiText[64 char],
	pEditGraffiti,
	pAdminHide,
	pPicking,
	pPickCar,
	pPickTime,
	pJetpack,
	pFreeze,
	pFreezeTimer,
	pSpawnPoint,
	pSpeedTime,
	pCarColor1,
	pCarColor2, 
	pKaitKelapa,
	pKaitKelapaCP,
	pPassword[120],
	pPin,
	pSweeper,
	pSweeperCar,
	pSweeperCP,
	Text3D:pDisconnectLabel,
	pAdminCode
};

enum reportData {
	rExists,
	rType,
	rPlayer,
	rText[128 char]
};

enum inventoryData {
	invExists,
	invID,
	invItem[32 char],
	invModel,
	invQuantity
};

enum houseData {
	houseID,
	houseExists,
	houseOwner,
	housePrice,
	houseAddress[32],
	Float:housePos[4],
	Float:houseInt[4],
	houseInterior,
	houseExterior,
	houseExteriorVW,
	houseLocked,
	houseSita,
	houseMoney,
	houseMapIcon,
	Text3D:houseText3D,
	housePickupExt,
	housePickupInt,
	houseLights,
	houseWeapons[10],
	houseAmmo[10]
};

enum houseStorage {
	hItemID,
	hItemExists,
	hItemName[32 char],
	hItemModel,
	hItemQuantity
};

enum businessData {
	bizID,
	bizExists,
 	bizName[32],
	bizMessage[128],
	bizOwner,
	bizType,
	bizPrice,
	Float:bizPos[4],
	Float:bizInt[4],
	Float:bizSpawn[4],
	Float:bizDeliver[3],
	Float:bizCaunter[3],
	Float:bizActor[4],
	bizInterior,
	bizExterior,
	bizExteriorVW,
	bizLocked,
	bizSita,
	bizVault,
	bizProducts,
	bizPickupExt,
	bizPickupInt,
	bizShipment,
	bizActorr,
	bizPrices[20],
	Text3D:bizText3D,
	Text3D:bizDeliverText3D,
	bizDeliverPickup,
	Text3D:bizCaunterText3D,
	bizCaunterPickup
};

enum droppedItems {
	droppedID,
	droppedItem[32],
	droppedPlayer[24],
	droppedModel,
	droppedQuantity,
	Float:droppedPos[3],
	droppedWeapon,
	droppedAmmo,
	droppedInt,
	droppedWorld,
	droppedObject,
	Text3D:droppedText3D
};

enum entranceData {
	entranceID,
	entranceExists,
	entranceName[32],
	entrancePass[32],
	entranceIcon,
	entranceLocked,
	Float:entrancePos[4],
	Float:entranceInt[4],
	entranceInterior,
	entranceExterior,
	entranceExteriorVW,
	entranceCustom,
	entranceWorld,
	entrancePickupExt,
	entrancePickupInt,
	entranceMapIcon,
	Text3D:entranceText3D
};

enum dealershipCars {
	vehID,
	vehModel,
	vehPrice
};

enum carData {
	carID,
	carExists,
	carModel, 
	carOwner,
	carPlate[15],
	Float:carHealth,
	Float:carPos[4],
	carFuel,
	carSiren,
	carColor1,
	carColor2,
	carPaintjob,
	carLocked,
	carRent,
	carMods[14],
	carImpounded,
	carImpoundPrice,
	carWeapons[5],
	carAmmo[5],
	carVehicle,
	carGov,
	carTemperature
};

enum carStorage {
	cItemID,
	cItemExists,
	cItemName[32 char],
	cItemModel,
	cItemQuantity
};

enum e_FurnitureData {
	e_FurnitureType,
	e_FurnitureName[32],
	e_FurnitureModel
};

enum pumpData {
	pumpID,
	pumpExists,
	pumpBusiness,
	Float:pumpPos[4],
	pumpFuel,
	pumpObject,
	Text3D:pumpText3D
};

enum furnitureData {
	furnitureID,
	furnitureHouse,
	furnitureExists,
	furnitureModel,
	furnitureName[32],
	Float:furniturePos[3],
	Float:furnitureRot[3],
	furnitureObject
};

enum jobData {
	jobID,
	jobExists,
	jobType,
	Float:jobPos[3],
	Float:jobPoint[3],
	Float:jobDeliver[3],
	jobInterior,
	jobWorld,
	jobPointInt,
	jobPointWorld,
	jobPickups[3],
	Text3D:jobText3D[3]
};

enum contactData {
	contactID,
	contactExists,
	contactName[32],
	contactNumber
};

enum locationData {
	locationID,
	locationExists,
	locationName[32],
	Float:locationPos[3],
};

enum crateData {
	crateID,
	crateExists,
	crateType,
 	Float:cratePos[4],
	crateInterior,
	crateWorld,
	crateObject,
	crateVehicle,
	Text3D:crateText3D
};

enum plantData {
	plantID,
	plantExists,
	plantType,
	plantDrugs,
	Float:plantPos[4],
	plantInterior,
	plantWorld,
	plantObject,
	Text3D:plantText3D
};

enum factionData {
	factionID,
	factionExists,
	factionName[32],
	factionColor,
	factionType,
	factionRanks,
	Float:factionLockerPos[3],
	factionLockerInt,
	factionLockerWorld,
	Float:factionLeaderLockerPos[3],
	factionSkins[14],
	factionWeapons[10],
	factionAmmo[10],
	factionMoney,
	Text3D:factionLockerText3D,
	factionLockerPickup,
	Text3D:factionLeaderLockerText3D,
	factionLeaderLockerPickup,
	Float:SpawnX,
	Float:SpawnY,
	Float:SpawnZ,
	SpawnInterior,
	SpawnVW
};

enum prisonData {
	prisonDoors[3],
	prisonCells[24],
	prisonDoorOpened[3],
	prisonCellOpened[24]
};

enum ticketData {
	ticketID,
	ticketExists,
	ticketFee,
	ticketFaction,
	ticketDate[36],
	ticketReason[64]
};

enum barricadeData {
	cadeExists,
	cadeType,
	Float:cadePos[3],
	cadeObject
};

enum gateData {
	gateID,
	gateExists,
	gateOpened,
	gateModel,
	Float:gateSpeed,
	Float:gateRadius,
	gateTime,
	Float:gatePos[6],
	gateInterior,
	gateWorld,
	Float:gateMove[6],
	gateLinkID,
	gateFaction,
	gatePass[32],
	gateTimer,
	gateObject
};

enum backpackData {
	backpackID,
	backpackExists,
	backpackPlayer,
	backpackHouse,
	backpackVehicle,
	Float:backpackPos[3],
	backpackInterior,
	backpackWorld,
	Text3D:backpackText3D,
	backpackObject
};

enum backpackItems {
	bItemID,
	bItemBackpack,
	bItemExists,
	bItemName[32],
	bItemModel,
	bItemQuantity
};

enum atmData {
	atmID,
	atmExists,
	Float:atmPos[4],
	atmInterior,
	atmWorld,
	atmObject,
	Text3D:atmText3D
};

enum garbageData {
	garbageID,
	garbageExists,
 	garbageModel,
	garbageCapacity,
	Float:garbagePos[4],
	garbageInterior,
	garbageWorld,
	Text3D:garbageText3D,
	garbageObject
};

enum vendorData {
	vendorID,
	vendorExists,
	vendorType,
	Float:vendorPos[4],
	vendorInterior,
	vendorWorld,
	Text3D:vendorText3D,
	vendorObject
};

enum boomboxData {
	boomboxPlaced,
	Float:boomboxPos[3],
	boomboxInterior,
	boomboxWorld,
	boomboxObject,
	boomboxURL[128 char],
	Text3D:boomboxText3D
};

enum rackData {
	rackID,
	rackExists,
	rackHouse,
	Float:rackPos[4],
	rackInterior,
	rackWorld,
	rackWeapons[4],
	rackAmmo[4],
	rackObjects[5],
	Text3D:rackText3D
};

enum speedData {
	speedID,
	speedExists,
	Float:speedPos[4],
	Float:speedRange,
	Float:speedLimit,
	speedObject,
	speedStatus,
	Text3D:speedText3D
};

enum graffitiData {
	graffitiID,
	graffitiExists,
	Float:graffitiPos[4],
	graffitiIcon,
	graffitiObject,
	graffitiColor,
	graffitiText[64]
};

enum rentPoints {
	rentID,
	rentExists,
	Float:rentPos[3],
	rentInterior,
	rentWorld,
	Text3D:rentText3D,
	rentPickup
};

enum coreVehicles {
	vehWindowsDown,
	vehTemporary,
	vehLoads,
	vehLoadType,
	vehCrate,
	vehTrash,
	vehRepairing,
	vehSirenOn,
	vehSirenObject,
	vehRadio,
	vehURL[128 char],
	Float:vehLoadHealth,
 	Float:vehLoadPos[3]
};

enum e_InventoryItems {
	e_InventoryItem[32],
	e_InventoryModel
};

enum houseInteriors {
	eHouseInterior,
	Float:eHouseX,
	Float:eHouseY,
	Float:eHouseZ,
	Float:eHouseAngle
};

enum e_InteriorData {
	e_InteriorName[32],
	e_InteriorID,
	Float:e_InteriorX,
	Float:e_InteriorY,
	Float:e_InteriorZ
};

enum actorData {
	actorSweeper
};

new up_days,
	up_hours,
	up_minutes,
	up_seconds,
	WorldWeather = 24,
	WorldTime = 14;

new g_iHandle;
new g_StatusOOC = 1;
new g_ServerLocked;

new ActorData[actorData];

new GraffitiData[MAX_GRAFFITI_POINTS][graffitiData];
new BarricadeData[MAX_BARRICADES][barricadeData];

new VendorData[MAX_VENDORS][vendorData];
new SpeedData[MAX_SPEED_CAMERAS][speedData];

new BoomboxData[MAX_PLAYERS][boomboxData];
new RackData[MAX_WEAPON_RACKS][rackData];

new ATMData[MAX_ATM_MACHINES][atmData];
new GarbageData[MAX_GARBAGE_BINS][garbageData];

new BackpackData[MAX_BACKPACKS][backpackData];
new BackpackItems[MAX_BACKPACK_ITEMS][backpackItems];

new BackpackListed[MAX_PLAYERS][MAX_BACKPACK_CAPACITY];

new PlayerData[MAX_PLAYERS][playerData];
new Float:AccessoryData[MAX_PLAYERS][3][9];
new TicketData[MAX_PLAYERS][MAX_PLAYER_TICKETS][ticketData];
new ListedVehicles[MAX_PLAYERS][MAX_OWNABLE_CARS];

// Textdraws
new Text:LAPARHAUS[MAX_PLAYERS][9];
new Text:PLAYERONLINE[MAX_PLAYERS][4];
new PlayerBar:LAPARHAUSBAR[MAX_PLAYERS][3];
new PlayerText: WaypointTD[MAX_PLAYERS];
new PlayerText: LampTD[MAX_PLAYERS];
new PlayerText: LoadingCrateTD[MAX_PLAYERS];
new PlayerText: DrugTD[MAX_PLAYERS];
new PlayerBar:MINYAKNHEALTH[MAX_PLAYERS][4];
new Text:NEWMETER[MAX_PLAYERS][18];
new Text:NEWMETERUPDATE[MAX_PLAYERS][19];
new Text:METERUPDATE[MAX_PLAYERS];
new Text:PLATEUPDATE[MAX_PLAYERS];
new Text:CARNAMEUPDATE[MAX_PLAYERS];
new Text:CARMODELUPDATE[MAX_PLAYERS];
new Text:LOGINTD[28];
new Text:LOGINTDNAME[MAX_PLAYERS];
new Text:NoSEATBELT[MAX_PLAYERS][3];

new InventoryData[MAX_PLAYERS][MAX_INVENTORY][inventoryData];
new ContactData[MAX_PLAYERS][MAX_CONTACTS][contactData];
new LocationData[MAX_PLAYERS][MAX_GPS_LOCATIONS][locationData];

new ListedFurniture[MAX_PLAYERS][MAX_HOUSE_FURNITURE];
new NearestItems[MAX_PLAYERS][MAX_LISTED_ITEMS];
new ListedContacts[MAX_PLAYERS][MAX_CONTACTS];

new ReportData[MAX_REPORTS][reportData];

new BusinessData[MAX_BUSINESSES][businessData];
new PumpData[MAX_GAS_PUMPS][pumpData];
new DealershipCars[MAX_BUSINESSES][MAX_DEALERSHIP_CARS][dealershipCars];

new DroppedItems[MAX_DROPPED_ITEMS][droppedItems];
new EntranceData[MAX_ENTRANCES][entranceData];

new CarData[MAX_DYNAMIC_CARS][carData];

new CarStorage[MAX_DYNAMIC_CARS][MAX_CAR_STORAGE][carStorage];

new HouseData[MAX_HOUSES][houseData];
new HouseStorage[MAX_HOUSES][MAX_HOUSE_STORAGE][houseStorage];
new FurnitureData[MAX_FURNITURE][furnitureData];
new RentData[MAX_RENT_POINTS][rentPoints];

new JobData[MAX_DYNAMIC_JOBS][jobData];
new CrateData[MAX_CRATES][crateData];
new PlantData[MAX_DRUG_PLANTS][plantData];

new FactionData[MAX_FACTIONS][factionData];
new FactionRanks[MAX_FACTIONS][15][32];
new GateData[MAX_GATES][gateData];

new PlayerCharacters[MAX_PLAYERS][3][MAX_PLAYER_NAME + 1];

new CoreVehicles[MAX_VEHICLES][coreVehicles];

new const g_aInventoryItems[][e_InventoryItems] = {
	{"Marijuana", 1578},
	{"Cocaine", 1575},
	{"Heroin", 1577},
	{"Steroids", 1241},
	{"Marijuana Seeds", 1578},
	{"Cocaine Seeds", 1575},
	{"Heroin Opium Seeds", 1577},
	{"Cooked Burger", 2703},
	{"Cooked Pizza", 2702},
	{"Driving License", 1581},
	{"Weapon License", 1581},
	{"Cellphone", 330},
	{"GPS System", 18875},
	{"Water Bottle", 2958},
	{"Soda", 1543},
    {"Fuel Can", 1650},
	{"Crowbar", 18634},
	{"Boombox", 2226},
	{"Mask", 19036},
	{"First Aid", 1580},
	{"Repair Kit", 920},
	{"Frozen Pizza", 2814},
	{"Frozen Burger", 2768},
	{"Armored Vest", 19142},
	{"Empty Bottle", 1484},
	{"Cardboard", 928},
	{"Chicken", 2663},
	{"Portable Radio", 18868},
	{"Cigarette", 19897},
	{"Alcohol", 19823},
	{"Lighter", 19998},
	{"Helmet", 18977},
	{"Cuff", 11749},
	{"Cuff Key", 11746},

	// Weapon
	{"Brass Knuckles", 331},
	{"Golf CLub", 333},
	{"Nightstick",334},
	{"Knife", 335},
	{"Baseball Bat", 336},
	{"Shovel",337},
	{"Pool Cue", 338},
	{"Katana", 339},
	{"Chainsaw", 341},
	{"Purple Dildo", 321},
	{"Dildo", 322},
	{"Vibrator", 323},
	{"Silver Vibrator", 324},
	{"Flowers", 325},
	{"Cane", 326},
	{"Grenade", 342},
	{"Tear Gas", 343},
	{"Molotov Cocktail", 344},
	{"9mm", 346},
	{"Silenced 9mm", 347},
	{"Desert Eagle", 348},
	{"Shotgun", 349},
	{"Sawnoff Shotgun", 350},
	{"Combat Shotgun", 351},
	{"Uzi", 352},
	{"MP5", 352},
	{"AK-47", 353},
	{"M4", 356},
	{"Tec-9", 372},
	{"Country Rifle", 357},
	{"Sniper Rifle", 358},
	{"RPG", 359},
	{"HS Rocket", 360},
	{"Flamethrower", 361},
	{"Minigun", 362},
	{"Satchel Charge", 363},
	{"Detonator", 364},
	{"Spraycan", 365},
	{"Fire Extinguisher", 366},
	{"Camera", 367},
	{"Night Vision Goggles", 368},
	{"Thermal Goggles", 369},
	{"Parachute", 371}
};

new const Float:g_arrWeaponDamage[] = {
	1.32, 1.32, 4.62, 4.62, 2.64, 4.62, 4.62, 4.62, 2.64, 13.53,
	4.62, 2.64, 4.62, 2.64, 4.62, 2.64, 0.00, 0.00, 0.00, 0.00,
	0.00, 0.00, 8.25, 13.2, 46.2, 49.5, 49.5, 39.6, 6.60, 8.25,
	9.90, 9.90, 6.60, 24.75, 41.25, 0.00, 0.00, 0.00, 46.2, 0.00,
	0.00, 2.64, 2.64, 0.00, 0.00, 0.00, 1.32
};

new const g_aWeaponSlots[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 8, 8, 8, 0, 0, 0, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 4, 6, 6, 7, 7, 7, 7, 8, 12, 9, 9, 9, 11, 11, 11
};

new const g_aPreloadLibs[][] =
{
	"AIRPORT",      "ATTRACTORS",   "BAR",          "BASEBALL",     "BD_FIRE",
	"BEACH",        "BENCHPRESS",   "BF_INJECTION", "BIKE_DBZ",     "BIKED",
	"BIKEH",        "BIKELEAP",     "BIKES",        "BIKEV",        "BLOWJOBZ",
	"BMX",          "BOMBER",       "BOX",          "BSKTBALL",     "BUDDY",
	"BUS",          "CAMERA",       "CAR",          "CAR_CHAT",     "CARRY",
	"CASINO",       "CHAINSAW",     "CHOPPA",       "CLOTHES",      "COACH",
	"COLT45",       "COP_AMBIENT",  "COP_DVBYZ",    "CRACK",        "CRIB",
	"DAM_JUMP",     "DANCING",      "DEALER",       "DILDO",        "DODGE",
	"DOZER",        "DRIVEBYS",     "FAT",          "FIGHT_B",      "FIGHT_C", 
	"FIGHT_D",      "FIGHT_E",      "FINALE",       "FINALE2",      "FLAME",
	"FLOWERS",      "FOOD",         "FREEWEIGHTS",  "GANGS",        "GFUNK",
	"GHANDS",       "GHETTO_DB",    "GOGGLES",      "GRAFFITI",     "GRAVEYARD",
	"GRENADE",      "GYMNASIUM",    "HAIRCUTS",     "HEIST9",       "INT_HOUSE",
	"INT_OFFICE",   "INT_SHOP",     "JST_BUISNESS", "KART",         "KISSING",
	"KNIFE",        "LAPDAN1",      "LAPDAN2",      "LAPDAN3",      "LOWRIDER",
	"MD_CHASE",     "MD_END",       "MEDIC",        "MISC",         "MTB",
	"MUSCULAR",     "NEVADA",       "ON_LOOKERS",   "OTB",          "PARACHUTE",
	"PARK",         "PAULNMAC",     "PED",          "PLAYER_DVBYS", "PLAYIDLES",
	"POLICE",       "POOL",         "POOR",         "PYTHON",       "QUAD",
	"QUAD_DBZ",     "RAPPING",      "RIFLE",        "RIOT",         "ROB_BANK",
	"ROCKET",       "RUNNINGMAN",   "RUSTLER",      "RYDER",        "SCRATCHING",
	"SEX",          "SHAMAL",       "SHOP",         "SHOTGUN",      "SILENCED",
	"SKATE",        "SMOKING",      "SNIPER",       "SNM",          "SPRAYCAN",
	"STRIP",        "SUNBATHE",     "SWAT",         "SWEET",        "SWIM",
	"SWORD",        "TANK",         "TATTOOS",      "TEC",          "TRAIN",
	"TRUCK",        "UZI",          "VAN",          "VENDING",      "VORTEX",
	"WAYFARER",     "WEAPONS",      "WOP",          "WUZI"
};

new const Float:arrHouseInteriors[20][houseInteriors] = {
	{10, 2269.8772, -1210.3240, 1047.5625, 90.0000},
    {2, 2468.2576, -1698.2361, 1013.5078, 90.0000},
	{3, 2495.8711, -1693.0996, 1014.7422, 180.0000},
	{5, 2233.7888, -1114.2689, 1050.8828, 0.0000},
	{9, 2317.8015, -1026.2113, 1050.2178, 0.0000},
	{3, 235.2923, 1187.3684, 1080.2578, 0.0000},
	{2, 226.2912, 1240.0554, 1082.1406, 90.0000},
	{1, 223.1618, 1287.5175, 1082.1406, 0.0000},
	{5, 226.9281, 1114.2813, 1080.9962, 270.0000},
	{15, 295.1485, 1473.1080, 1080.2578, 0.0000},
	{10, 23.9584, 1340.6075, 1084.3750, 0.0000}, 
	{4, 222.0425, 1140.7565, 1082.6094, 0.0000},
	{12, 2324.4209, -1148.9365, 1050.7101, 0.0000},
	{4, -261.1430, 1456.6396, 1084.3672, 90.0000},
	{5, 22.9676, 1403.8368, 1084.4297, 0.0000},
	{5, 140.3088, 1366.8196, 1083.8594, 0.0000},
	{6, 234.3149, 1064.2772, 1084.2114, 0.0000},
	{7, 225.7000, 1022.0012, 1084.0161, 0.0000},
	{5, 1298.9750, -796.4567, 1084.0078, 0.0000},
	{15, -283.8687, 1471.1174, 1084.3750, 90.0000}
};

new stock g_arrVehicleNames[][] = {
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster",
    "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer",
    "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach",
    "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow",
    "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
    "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic",
    "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",
    "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
    "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick",
    "Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher",
    "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt", "Tanker", "Roadtrain",
    "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck",
    "Fortune", "Cadrona", "SWAT Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan",
    "Blade", "Streak", "Freight", "Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder",
    "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster",
    "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30",
    "Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
    "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "LSPD Car", "SFPD Car", "LVPD Car",
    "Police Rancher", "Picador", "S.W.A.T", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs",
    "Boxville", "Tiller", "Utility Trailer"
};

new const g_arrInteriorData[][e_InteriorData] = {
	{"24/7 1", 17, -25.884498, -185.868988, 1003.546875},
    {"24/7 2", 10, 6.091179, -29.271898, 1003.549438},
    {"24/7 3", 18, -30.946699, -89.609596, 1003.546875},
    {"24/7 4", 16, -25.132598, -139.066986, 1003.546875},
    {"24/7 5", 4, -27.312299, -29.277599, 1003.557250},
    {"24/7 6", 6, -26.691598, -55.714897, 1003.546875},
    {"Airport Ticket", 14, -1827.147338, 7.207417, 1061.143554},
    {"Airport Baggage", 14, -1861.936889, 54.908092, 1061.143554},
    {"Shamal", 1, 1.808619, 32.384357, 1199.593750},
    {"Andromada", 9, 315.745086, 984.969299, 1958.919067},
    {"Ammunation 1", 1, 286.148986, -40.644397, 1001.515625},
    {"Ammunation 2", 4, 286.800994, -82.547599, 1001.515625},
    {"Ammunation 3", 6, 296.919982, -108.071998, 1001.515625},
    {"Ammunation 4", 7, 314.820983, -141.431991, 999.601562},
    {"Ammunation 5", 6, 316.524993, -167.706985, 999.593750},
    {"Ammunation Booths", 7, 302.292877, -143.139099, 1004.062500},
    {"Ammunation Range", 7, 298.507934, -141.647048, 1004.054748},
    {"Blastin Fools Hallway", 3, 1038.531372, 0.111030, 1001.284484},
    {"Budget Inn Motel Room", 12, 444.646911, 508.239044, 1001.419494},
    {"Jefferson Motel", 15, 2215.454833, -1147.475585, 1025.796875},
    {"Off Track Betting Shop", 3, 833.269775, 10.588416, 1004.179687},
    {"Sex Shop", 3, -103.559165, -24.225606, 1000.718750},
    {"Meat Factory", 1, 963.418762, 2108.292480, 1011.030273},
    {"Zero's RC shop", 6, -2240.468505, 137.060440, 1035.414062},
    {"Dillimore Gas", 0, 663.836242, -575.605407, 16.343263},
    {"Catigula's Basement", 1, 2169.461181, 1618.798339, 999.976562},
    {"FC Janitor Room", 10, 1889.953369, 1017.438293, 31.882812},
    {"Woozie's Office", 1, -2159.122802, 641.517517, 1052.381713},
    {"Binco", 15, 207.737991, -109.019996, 1005.132812},
    {"Didier Sachs", 14, 204.332992, -166.694992, 1000.523437},
    {"Prolaps", 3, 207.054992, -138.804992, 1003.507812},
    {"Suburban", 1, 203.777999, -48.492397, 1001.804687},
    {"Victim", 5, 226.293991, -7.431529, 1002.210937},
    {"Zip", 18, 161.391006, -93.159156, 1001.804687},
    {"Club", 17, 493.390991, -22.722799, 1000.679687},
    {"Bar", 11, 501.980987, -69.150199, 998.757812},
    {"Lil' Probe Inn", 18, -227.027999, 1401.229980, 27.765625},
    {"Jay's Diner", 4, 457.304748, -88.428497, 999.554687},
    {"Gant Bridge Diner", 5, 454.973937, -110.104995, 1000.077209},
    {"Secret Valley Diner", 6, 435.271331, -80.958938, 999.554687},
    {"World of Coq", 1, 452.489990, -18.179698, 1001.132812},
    {"Welcome Pump", 1, 681.557861, -455.680053, -25.609874},
    {"Burger Shot", 10, 375.962463, -65.816848, 1001.507812},
    {"Cluckin' Bell", 9, 369.579528, -4.487294, 1001.858886},
    {"Well Stacked Pizza", 5, 373.825653, -117.270904, 1001.499511},
    {"Rusty Browns Donuts", 17, 381.169189, -188.803024, 1000.632812},
    {"Denise's Room", 1, 244.411987, 305.032989, 999.148437},
    {"Katie's Room", 2, 271.884979, 306.631988, 999.148437},
    {"Helena's Room", 3, 291.282989, 310.031982, 999.148437},
    {"Michelle's Room", 4, 302.180999, 300.722991, 999.148437},
    {"Barbara's Room", 5, 322.197998, 302.497985, 999.148437},
    {"Millie's Room", 6, 346.870025, 309.259033, 999.155700},
    {"Sherman Dam", 17, -959.564392, 1848.576782, 9.000000},
    {"Planning Dept", 3, 384.808624, 173.804992, 1008.382812},
    {"Area 51", 0, 223.431976, 1872.400268, 13.734375},
    {"LS Gym", 5, 772.111999, -3.898649, 1000.728820},
    {"SF Gym", 6, 774.213989, -48.924297, 1000.585937},
    {"LV Gym", 7, 773.579956, -77.096694, 1000.655029},
    {"B-Dup's House", 3, 1527.229980, -11.574499, 1002.097106},
    {"B-Dup's Crack Pad", 2, 1523.509887, -47.821197, 1002.130981},
    {"CJ's House", 3, 2496.049804, -1695.238159, 1014.742187},
    {"Madd Doggs Mansion", 5, 1267.663208, -781.323242, 1091.906250},
    {"OG Loc's House", 3, 513.882507, -11.269994, 1001.565307},
    {"Ryders House", 2, 2454.717041, -1700.871582, 1013.515197},
    {"Sweet's House", 1, 2527.654052, -1679.388305, 1015.498596},
    {"Crack Factory", 2, 2543.462646, -1308.379882, 1026.728393},
    {"Big Spread Ranch", 3, 1212.019897, -28.663099, 1000.953125},
    {"Fanny batters", 6, 761.412963, 1440.191650, 1102.703125},
    {"Strip Club", 2, 1204.809936, -11.586799, 1000.921875},
    {"Strip Club (Private Room)", 2, 1204.809936, 13.897239, 1000.921875},
    {"Unnamed Brothel", 3, 942.171997, -16.542755, 1000.929687},
    {"Tiger Skin Brothel", 3, 964.106994, -53.205497, 1001.124572},
    {"Pleasure Domes", 3, -2640.762939, 1406.682006, 906.460937},
    {"Liberty City Outside", 1, -729.276000, 503.086944, 1371.971801},
    {"Liberty City Inside", 1, -794.806396, 497.738037, 1376.195312},
    {"Gang House", 5, 2350.339843, -1181.649902, 1027.976562},
    {"Colonel Furhberger's", 8, 2807.619873, -1171.899902, 1025.570312},
    {"Crack Den", 5, 318.564971, 1118.209960, 1083.882812},
    {"Warehouse 1", 1, 1412.639892, -1.787510, 1000.924377},
    {"Warehouse 2", 18, 1302.519897, -1.787510, 1001.028259},
    {"Sweet's Garage", 0, 2522.000000, -1673.383911, 14.866223},
    {"Lil' Probe Inn Toilet", 18, -221.059051, 1408.984008, 27.773437},
    {"Unused Safe House", 12, 2324.419921, -1145.568359, 1050.710083},
    {"RC Battlefield", 10, -975.975708, 1060.983032, 1345.671875},
    {"Barber 1", 2, 411.625976, -21.433298, 1001.804687},
    {"Barber 2", 3, 418.652984, -82.639793, 1001.804687},
    {"Barber 3", 12, 412.021972, -52.649898, 1001.898437},
    {"Tatoo Parlor 1", 16, -204.439987, -26.453998, 1002.273437},
    {"Tatoo Parlor 2", 17, -204.439987, -8.469599, 1002.273437},
    {"Tatoo Parlor 3", 3, -204.439987, -43.652496, 1002.273437},
    {"LS Police HQ", 6, 246.783996, 63.900199, 1003.640625},
    {"SF Police HQ", 10, 246.375991, 109.245994, 1003.218750},
    {"LV Police HQ", 3, 288.745971, 169.350997, 1007.171875},
    {"Driving School", 3, -2029.798339, -106.675910, 1035.171875},
    {"8-Track", 7, -1398.065307, -217.028900, 1051.115844},
    {"Bloodbowl", 15, -1398.103515, 937.631164, 1036.479125},
    {"Dirt Track", 4, -1444.645507, -664.526000, 1053.572998},
    {"Kickstart", 14, -1465.268676, 1557.868286, 1052.531250},
    {"Vice Stadium", 1, -1401.829956, 107.051300, 1032.273437},
    {"SF Garage", 0, -1790.378295, 1436.949829, 7.187500},
    {"LS Garage", 0, 1643.839843, -1514.819580, 13.566620},
    {"SF Bomb Shop", 0, -1685.636474, 1035.476196, 45.210937},
    {"Blueberry Warehouse", 0, 76.632553, -301.156829, 1.578125},
    {"LV Warehouse 1", 0, 1059.895996, 2081.685791, 10.820312},
    {"LV Warehouse 2 (hidden part)", 0, 1059.180175, 2148.938720, 10.820312},
    {"Caligula's Hidden Room", 1, 2131.507812, 1600.818481, 1008.359375},
    {"Bank", 0, 2315.952880, -1.618174, 26.742187},
    {"Bank (Behind Desk)", 0, 2319.714843, -14.838361, 26.749565},
    {"LS Atrium", 18, 1710.433715, -1669.379272, 20.225049}
};

new const Float:g_arrDrivingCheckpoints[][] = {
    {-2064.9561, -67.7125, 34.8247},
    {-2110.5261, -67.8857, 34.8247},
    {-2154.2473, -67.6854, 34.8231},
    {-2169.3850, -82.5202, 34.8302},
    {-2169.8767, -114.5743, 34.8188},
    {-2170.6482, -162.7804, 34.8249},
    {-2215.5796, -187.5162, 34.8745},
    {-2244.0376, -187.6771, 34.8235},
    {-2259.1860, -202.9163, 34.9007},
    {-2259.7864, -253.0544, 39.7875},
    {-2260.3638, -300.5378, 48.1640},
    {-2259.5361, -339.2552, 50.5190},
    {-2258.4385, -371.1333, 50.5193},
    {-2236.2454, -416.2657, 50.5155},
    {-2195.2356, -459.0606, 49.3517},
    {-2155.1711, -497.7458, 41.1217},
    {-2117.1301, -536.1792, 34.2394},
    {-2059.1565, -577.5410, 29.0998},
    {-1984.6453, -582.2720, 25.5633},
    {-1925.5862, -583.2345, 24.0926},
    {-1885.5591, -583.6432, 24.0940},
    {-1821.1207, -583.9514, 15.9855},
    {-1816.3672, -559.6774, 15.8619},
    {-1821.3180, -527.9517, 14.6263},
    {-1819.6934, -462.3056, 14.6151},
    {-1809.8923, -396.5690, 16.1884},
    {-1798.9331, -317.3351, 24.3122},
    {-1796.9186, -239.6917, 17.8804},
    {-1797.0546, -168.9667, 9.4126},
    {-1797.6467, -125.6053, 5.1712},
    {-1811.8171, -114.1203, 5.1504},
    {-1841.5179, -114.4944, 5.1483},
    {-1882.5660, -106.9792, 14.5634},
    {-1911.3077, -79.0253, 24.6949},
    {-1938.0209, -62.3110, 25.2069},
    {-1975.7996, -64.1764, 27.7167},
    {-2014.0769, -67.5033, 34.8182},
    {-2040.5736, -67.4500, 34.8250},
    {-2046.2883, -84.8129, 34.8103},
    {-2068.5259, -84.6942, 34.8201}
};

new const Float:g_arrKaitKelapaCheckpoints[][] = { 
    {1823.1415,588.1070,10.8203},
    {1807.8085,610.6229,10.8203},
    {1834.2102,611.2767,10.8203},
    {1823.3059,600.3861,10.8203},
    {1844.8053,607.6719,10.8203}
};

new const Float:g_arrSweeperCheckpoints[][] = { 
    {1565.9089, -1870.1763, 13.3906},
    {1466.3488, -1869.8799, 13.3828},
    {1370.5444, -1868.0171, 13.3828},
    {1309.6659, -1804.6422, 13.3828},
    {1310.0188, -1700.7787, 13.3828},
    {1310.0278, -1579.7556, 13.3828},
    {1374.0242, -1588.3567, 13.3657},
    {1431.6289, -1582.4417, 13.3696},
    {1453.1980, -1483.4410, 13.3614},
    {1457.6289, -1444.8488, 13.3906},
    {1519.9335, -1443.3844, 13.3828},
    {1590.9464, -1443.1311, 13.3906},
    {1608.2594, -1407.2974, 13.7143},
    {1610.4702, -1331.3899, 17.2978},
    {1620.7671, -1304.6553, 17.2140},
    {1698.3265, -1304.4382, 13.4830},
    {1759.9325, -1296.4730, 13.4764},
    {1816.7234, -1264.5221, 13.4688},
    {1846.1211, -1311.3358, 13.3911},
    {1845.5707, -1437.9178, 13.3987},
    {1825.5148, -1559.9943, 13.3668},
    {1819.5133, -1637.5967, 13.3828},
    {1818.9880, -1735.0427, 13.3828},
    {1818.8059, -1829.6947, 13.4141},
    {1748.6187, -1817.8027, 13.3855},
    {1700.1180, -1810.1871, 13.3687},
    {1685.0061, -1851.6204, 13.3906},
    {1645.1611, -1869.7051, 13.3828},
    {1624.4315, -1889.1863, 13.5492}
};

new const g_aLegalMods[][] = {
    {400, 1024, 1021, 1020, 1019, 1018, 1013, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {401, 1145, 1144, 1143, 1142, 1020, 1019, 1017, 1013, 1007, 1006, 1005, 1004, 1003, 1001, 0000, 0000, 0000, 0000},
    {404, 1021, 1020, 1019, 1017, 1016, 1013, 1007, 1002, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {405, 1023, 1021, 1020, 1019, 1018, 1014, 1001, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {410, 1024, 1023, 1021, 1020, 1019, 1017, 1013, 1007, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {415, 1023, 1019, 1018, 1017, 1007, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {418, 1021, 1020, 1016, 1006, 1002, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {420, 1021, 1019, 1005, 1004, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {421, 1023, 1021, 1020, 1019, 1018, 1016, 1014, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {422, 1021, 1020, 1019, 1017, 1013, 1007, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {426, 1021, 1019, 1006, 1005, 1004, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {436, 1022, 1021, 1020, 1019, 1017, 1013, 1007, 1006, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {439, 1145, 1144, 1143, 1142, 1023, 1017, 1013, 1007, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {477, 1021, 1020, 1019, 1018, 1017, 1007, 1006, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {478, 1024, 1022, 1021, 1020, 1013, 1012, 1005, 1004, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {489, 1024, 1020, 1019, 1018, 1016, 1013, 1006, 1005, 1004, 1002, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {491, 1145, 1144, 1143, 1142, 1023, 1021, 1020, 1019, 1018, 1017, 1014, 1007, 1003, 0000, 0000, 0000, 0000, 0000},
    {492, 1016, 1006, 1005, 1004, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {496, 1143, 1142, 1023, 1020, 1019, 1017, 1011, 1007, 1006, 1003, 1002, 1001, 0000, 0000, 0000, 0000, 0000, 0000},
    {500, 1024, 1021, 1020, 1019, 1013, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {516, 1021, 1020, 1019, 1018, 1017, 1016, 1015, 1007, 1004, 1002, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {517, 1145, 1144, 1143, 1142, 1023, 1020, 1019, 1018, 1017, 1016, 1007, 1003, 1002, 0000, 0000, 0000, 0000, 0000},
    {518, 1145, 1144, 1143, 1142, 1023, 1020, 1018, 1017, 1013, 1007, 1006, 1005, 1003, 1001, 0000, 0000, 0000, 0000},
    {527, 1021, 1020, 1018, 1017, 1015, 1014, 1007, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {529, 1023, 1020, 1019, 1018, 1017, 1012, 1011, 1007, 1006, 1003, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {534, 1185, 1180, 1179, 1178, 1127, 1126, 1125, 1124, 1123, 1122, 1106, 1101, 1100, 0000, 0000, 0000, 0000, 0000},
    {535, 1121, 1120, 1119, 1118, 1117, 1116, 1115, 1114, 1113, 1110, 1109, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {536, 1184, 1183, 1182, 1181, 1128, 1108, 1107, 1105, 1104, 1103, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {540, 1145, 1144, 1143, 1142, 1024, 1023, 1020, 1019, 1018, 1017, 1007, 1006, 1004, 1001, 0000, 0000, 0000, 0000},
    {542, 1145, 1144, 1021, 1020, 1019, 1018, 1015, 1014, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {546, 1145, 1144, 1143, 1142, 1024, 1023, 1019, 1018, 1017, 1007, 1006, 1004, 1002, 1001, 0000, 0000, 0000, 0000},
    {547, 1143, 1142, 1021, 1020, 1019, 1018, 1016, 1003, 1000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {549, 1145, 1144, 1143, 1142, 1023, 1020, 1019, 1018, 1017, 1012, 1011, 1007, 1003, 1001, 0000, 0000, 0000, 0000},
    {550, 1145, 1144, 1143, 1142, 1023, 1020, 1019, 1018, 1006, 1005, 1004, 1003, 1001, 0000, 0000, 0000, 0000, 0000},
    {551, 1023, 1021, 1020, 1019, 1018, 1016, 1006, 1005, 1003, 1002, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {558, 1168, 1167, 1166, 1165, 1164, 1163, 1095, 1094, 1093, 1092, 1091, 1090, 1089, 1088, 0000, 0000, 0000, 0000},
    {559, 1173, 1162, 1161, 1160, 1159, 1158, 1072, 1071, 1070, 1069, 1068, 1067, 1066, 1065, 0000, 0000, 0000, 0000},
    {560, 1170, 1169, 1141, 1140, 1139, 1138, 1033, 1032, 1031, 1030, 1029, 1028, 1027, 1026, 0000, 0000, 0000, 0000},
    {561, 1157, 1156, 1155, 1154, 1064, 1063, 1062, 1061, 1060, 1059, 1058, 1057, 1056, 1055, 1031, 1030, 1027, 1026},
    {562, 1172, 1171, 1149, 1148, 1147, 1146, 1041, 1040, 1039, 1038, 1037, 1036, 1035, 1034, 0000, 0000, 0000, 0000},
    {565, 1153, 1152, 1151, 1150, 1054, 1053, 1052, 1051, 1050, 1049, 1048, 1047, 1046, 1045, 0000, 0000, 0000, 0000},
    {567, 1189, 1188, 1187, 1186, 1133, 1132, 1131, 1130, 1129, 1102, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {575, 1177, 1176, 1175, 1174, 1099, 1044, 1043, 1042, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {576, 1193, 1192, 1191, 1190, 1137, 1136, 1135, 1134, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {580, 1023, 1020, 1018, 1017, 1007, 1006, 1001, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {589, 1145, 1144, 1024, 1020, 1018, 1017, 1016, 1013, 1007, 1006, 1005, 1004, 1000, 0000, 0000, 0000, 0000, 0000},
    {600, 1022, 1020, 1018, 1017, 1013, 1007, 1006, 1005, 1004, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000},
    {603, 1145, 1144, 1143, 1142, 1024, 1023, 1020, 1019, 1018, 1017, 1007, 1006, 1001, 0000, 0000, 0000, 0000, 0000}
};

new g_aMaleSkins[185] = {
	1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 32, 33, 34, 35, 36, 37, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 57, 58, 59, 60,
	61, 62, 66, 68, 72, 73, 78, 79, 80, 81, 82, 83, 84, 94, 95, 96, 97, 98, 99, 100, 101, 102,
	103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
	121, 122, 123, 124, 125, 126, 127, 128, 132, 133, 134, 135, 136, 137, 142, 143, 144, 146,
	147, 153, 154, 155, 156, 158, 159, 160, 161, 162, 167, 168, 170, 171, 173, 174, 175, 176,
	177, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 200, 202, 203, 204, 206,
	208, 209, 210, 212, 213, 217, 220, 221, 222, 223, 228, 229, 230, 234, 235, 236, 239, 240,
	241, 242, 247, 248, 249, 250, 253, 254, 255, 258, 259, 260, 261, 262, 268, 272, 273, 289,
	290, 291, 292, 293, 294, 295, 296, 297, 299
};

new g_aFemaleSkins[77] = {
    9, 10, 11, 12, 13, 31, 38, 39, 40, 41, 53, 54, 55, 56, 63, 64, 65, 69,
    75, 76, 77, 85, 88, 89, 90, 91, 92, 93, 129, 130, 131, 138, 140, 141,
    145, 148, 150, 151, 152, 157, 169, 178, 190, 191, 192, 193, 194, 195,
    196, 197, 198, 199, 201, 205, 207, 211, 214, 215, 216, 219, 224, 225,
    226, 231, 232, 233, 237, 238, 243, 244, 245, 246, 251, 256, 257, 263,
    298
};

new const g_aFurnitureTypes[][] = {
	{"Frames"},
	{"Tables"},
	{"Chairs"},
	{"Beds"},
	{"Cabinets"},
	{"Television Sets"},
	{"Kitchen Appliances"},
	{"Bathroom Appliances"},
	{"Misc Furniture"}
};

new const g_aFurnitureData[][e_FurnitureData] = {
	{1, "Frame 1", 2289},
	{1, "Frame 2", 2288},
	{1, "Frame 3", 2287},
	{1, "Frame 4", 2286},
	{1, "Frame 5", 2285},
	{1, "Frame 6", 2284},
    {1, "Frame 7", 2283},
    {1, "Frame 8", 2282},
    {1, "Frame 9", 2281},
    {1, "Frame 10", 2280},
    {1, "Frame 11", 2279},
	{1, "Frame 12", 2278},
	{1, "Frame 13", 2277},
	{1, "Frame 14", 2276},
	{1, "Frame 15", 2275},
	{1, "Frame 16", 2274},
    {1, "Frame 17", 2273},
    {1, "Frame 18", 2272},
    {1, "Frame 19", 2271},
    {1, "Frame 20", 2270},
    {2, "Table 1", 1433},
	{2, "Table 2", 1998},
	{2, "Table 3", 2008},
	{2, "Table 4", 2180},
	{2, "Table 5", 2185},
    {2, "Table 6", 2205},
    {2, "Table 7", 2314},
    {2, "Table 8", 2635},
    {2, "Table 9", 2637},
    {2, "Table 10", 2644},
	{2, "Table 11", 2747},
	{2, "Table 12", 2764},
	{2, "Table 13", 2763},
	{2, "Table 14", 2762},
	{2, "Table 15", 936},
	{2, "Table 16", 937},
	{2, "Table 17", 941},
	{2, "Table 18", 2115},
	{2, "Table 19", 2116},
	{2, "Table 20", 2112},
	{2, "Table 21", 2111},
	{2, "Table 22", 2110},
	{2, "Table 23", 2109},
	{2, "Table 24", 2085},
	{2, "Table 25", 2032},
	{2, "Table 26", 2031},
	{2, "Table 27", 2030},
	{2, "Table 28", 2029},
    {3, "Chair 1", 1671},
    {3, "Chair 2", 1704},
    {3, "Chair 3", 1705},
    {3, "Chair 4", 1708},
    {3, "Chair 5", 1711},
    {3, "Chair 6", 1715},
    {3, "Chair 7", 1721},
    {3, "Chair 8", 1724},
    {3, "Chair 9", 1727},
    {3, "Chair 10", 1729},
    {3, "Chair 11", 1735},
    {3, "Chair 12", 1739},
    {3, "Chair 13", 1805},
    {3, "Chair 14", 1806},
    {3, "Chair 15", 1810},
    {3, "Chair 16", 1811},
    {3, "Chair 17", 2079},
    {3, "Chair 18", 2120},
    {3, "Chair 19", 2124},
    {3, "Chair 20", 2356},
    {3, "Chair 21", 1768},
    {3, "Chair 22", 1766},
    {3, "Chair 23", 1764},
    {3, "Chair 24", 1763},
    {3, "Chair 25", 1761},
    {3, "Chair 26", 1760},
    {3, "Chair 27", 1757},
    {3, "Chair 28", 1756},
    {3, "Chair 29", 1753},
    {3, "Chair 30", 1713},
    {3, "Chair 31", 1712},
    {3, "Chair 32", 1706},
    {3, "Chair 33", 1703},
    {3, "Chair 34", 1702},
    {3, "Chair 35", 1754},
    {3, "Chair 36", 1755},
    {3, "Chair 37", 1758},
    {3, "Chair 38", 1759},
    {3, "Chair 39", 1762},
    {3, "Chair 40", 1765},
    {3, "Chair 41", 1767},
    {3, "Chair 42", 1769},
	{4, "Bed 1", 1700},
	{4, "Bed 2", 1701},
	{4, "Bed 3", 1725},
	{4, "Bed 4", 1745},
	{4, "Bed 5", 1793},
	{4, "Bed 6", 1794},
	{4, "Bed 7", 1795},
	{4, "Bed 8", 1796},
	{4, "Bed 9", 1797},
	{4, "Bed 10", 1771},
	{4, "Bed 11", 1798},
	{4, "Bed 12", 1799},
    {4, "Bed 13", 1800},
    {4, "Bed 14", 1801},
    {4, "Bed 15", 1802},
    {4, "Bed 16", 1812},
    {4, "Bed 17", 2090},
    {4, "Bed 18", 2299},
    {5, "Cabinet 1", 1416},
	{5, "Cabinet 2", 1417},
	{5, "Cabinet 3", 1741},
	{5, "Cabinet 4", 1742},
	{5, "Cabinet 5", 1743},
	{5, "Cabinet 6", 2025},
	{5, "Cabinet 7", 2065},
	{5, "Cabinet 8", 2066},
	{5, "Cabinet 9", 2067},
	{5, "Cabinet 10", 2087},
    {5, "Cabinet 11", 2088},
    {5, "Cabinet 12", 2094},
    {5, "Cabinet 13", 2095},
    {5, "Cabinet 14", 2306},
    {5, "Cabinet 15", 2307},
	{5, "Cabinet 16", 2323},
	{5, "Cabinet 17", 2328},
	{5, "Cabinet 18", 2329},
	{5, "Cabinet 19", 2330},
	{5, "Cabinet 20", 2708},
	{6, "Television 1", 1518},
	{6, "Television 2", 1717},
	{6, "Television 3", 1747},
	{6, "Television 4", 1748},
	{6, "Television 5", 1749},
	{6, "Television 6", 1750},
	{6, "Television 7", 1752},
	{6, "Television 8", 1781},
	{6, "Television 9", 1791},
	{6, "Television 10", 1792},
    {6, "Television 11", 2312},
	{6, "Television 12", 2316},
	{6, "Television 13", 2317},
	{6, "Television 14", 2318},
	{6, "Television 15", 2320},
	{6, "Television 16", 2595},
	{6, "Television 17", 16377},
	{7, "Kitchen 1", 2013},
	{7, "Kitchen 2", 2017},
	{7, "Kitchen 3", 2127},
	{7, "Kitchen 4", 2130},
	{7, "Kitchen 5", 2131},
	{7, "Kitchen 6", 2132},
	{7, "Kitchen 7", 2135},
	{7, "Kitchen 8", 2136},
	{7, "Kitchen 9", 2144},
	{7, "Kitchen 10", 2147},
    {7, "Kitchen 11", 2149},
    {7, "Kitchen 12", 2150},
    {7, "Kitchen 13", 2415},
    {7, "Kitchen 14", 2417},
    {7, "Kitchen 15", 2421},
    {7, "Kitchen 16", 2426},
    {7, "Kitchen 17", 2014},
    {7, "Kitchen 18", 2015},
    {7, "Kitchen 19", 2016},
    {7, "Kitchen 20", 2018},
    {7, "Kitchen 21", 2019},
    {7, "Kitchen 22", 2022},
    {7, "Kitchen 23", 2133},
    {7, "Kitchen 24", 2134},
	{7, "Kitchen 25", 2137},
	{7, "Kitchen 26", 2138},
	{7, "Kitchen 27", 2139},
	{7, "Kitchen 28", 2140},
	{7, "Kitchen 29", 2141},
	{7, "Kitchen 30", 2142},
	{7, "Kitchen 31", 2143},
	{7, "Kitchen 32", 2145},
	{7, "Kitchen 33", 2148},
	{7, "Kitchen 34", 2151},
	{7, "Kitchen 35", 2152},
	{7, "Kitchen 36", 2153},
	{7, "Kitchen 37", 2154},
	{7, "Kitchen 38", 2155},
	{7, "Kitchen 39", 2156},
	{7, "Kitchen 40", 2157},
	{7, "Kitchen 41", 2158},
	{7, "Kitchen 42", 2159},
	{7, "Kitchen 43", 2160},
	{7, "Kitchen 44", 2134},
	{7, "Kitchen 45", 2135},
	{7, "Kitchen 46", 2338},
	{7, "Kitchen 47", 2341},
	{8, "Bathroom 1", 2514},
	{8, "Bathroom 2", 2516},
	{8, "Bathroom 3", 2517},
	{8, "Bathroom 4", 2518},
	{8, "Bathroom 5", 2520},
	{8, "Bathroom 6", 2521},
	{8, "Bathroom 7", 2522},
	{8, "Bathroom 8", 2523},
	{8, "Bathroom 9", 2524},
	{8, "Bathroom 10", 2525},
    {8, "Bathroom 11", 2526},
    {8, "Bathroom 12", 2527},
    {8, "Bathroom 13", 2528},
    {8, "Bathroom 14", 2738},
    {8, "Bathroom 15", 2739},
	{9, "Washer", 1208},
	{9, "Ceiling Fan", 1661},
	{9, "Moose Head", 1736},
	{9, "Radiator", 1738},
	{9, "Mop and Pail", 1778},
	{9, "Water Cooler", 1808},
	{9, "Water Cooler 2", 2002},
	{9, "Money Safe", 1829},
	{9, "Printer", 2186},
	{9, "Computer", 2190},
	{9, "Treadmill", 2627},
	{9, "Bench Press", 2629},
	{9, "Exercise Bike", 2630},
	{9, "Mat 1", 2631},
	{9, "Mat 2", 2632},
	{9, "Mat 3", 2817},
	{9, "Mat 4", 2818},
	{9, "Mat 5", 2833},
	{9, "Mat 6", 2834},
	{9, "Mat 7", 2835},
	{9, "Mat 8", 2836},
	{9, "Mat 9", 2841},
	{9, "Mat 10", 2842},
	{9, "Mat 11", 2847},
	{9, "Book Pile 1", 2824},
	{9, "Book Pile 2", 2826},
	{9, "Book Pile 3", 2827},
	{9, "Basketball", 2114},
	{9, "Lamp 1", 2108},
	{9, "Lamp 2", 2106},
	{9, "Lamp 3", 2069},
	{9, "Dresser 1", 2569},
	{9, "Dresser 2", 2570},
	{9, "Dresser 3", 2573},
	{9, "Dresser 4", 2574},
	{9, "Dresser 5", 2576},
	{9, "Book", 2894}
};

new Float:HelmetPos[300][9] =
{
    {0.07, 0.0, 0.0, 88.0, 75.0, 0.0}, //skin 0
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 1
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 2
	{0.082272, 0.012175, 0.000000, 88.573463, 83.217987, 0.571479, 1.037069}, //skin 3
	{0.106029, 0.020526, 0.000000, 88.573463, 83.217987, 0.571479, 1.011797}, //skin 4
	{0.065514, 0.029894, 0.000000, 88.573463, 83.217987, 0.571479, 1.067914}, //skin 5
	{0.081949, 0.035309, 0.000000, 88.573463, 83.217987, 0.571479, 1.037069}, //skin 6
	{0.09, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 7
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 8
	{0.059999, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 9
	{0.090000, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 10
	{0.07, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 11
	{0.07, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 12
	{0.07, 0.019999, 0.0, 88.0, 90.0, 0.0}, //skin 13
	{0.071141, 0.033483, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 14
	{0.059999, 0.0, 0.0, 88.0, 82.0, 0.0}, //skin 15
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 16
	{0.059999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 17
	{0.059999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 18
	{0.071141, 0.033483, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 19
	{0.071141, 0.012607, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 20
	{0.059999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 21
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 22
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 23
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 24
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 25
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 26
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 27
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 28
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 29
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 30
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 31
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 32
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 33
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 34
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 35
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 36
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 37
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 38
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 39
	{0.050000, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 40
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 41
	{0.065985, 0.011633, 0.000000, 88.573463, 83.217987, 0.571479, 1.002084}, //skin 42
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 43
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 44
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 45
	{0.071141, 0.026406, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 46
	{0.071141, 0.026406, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 47
	{0.071141, 0.026406, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 48
	{0.07, 0.0, 0.0, 88.0, 77.0, 0.0}, //skin 49
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 50
	{0.100000, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 51
	{0.100000, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 52
	{0.071141, 0.048094, 0.000000, 89.899635, 82.456283, 0.000000}, //skin 53
	{0.100000, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 54
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 55
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 56
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 57
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 58
	{0.079999, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 59
	{0.079999, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 60
	{0.079999, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 61
	{0.079999, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 62
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 63
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 64
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 65
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 66
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 67
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 68
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 69
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 70
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 71
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 72
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 73
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 74
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 75
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 76
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 77
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 78
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 79
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 80
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 81
	{0.097840, 0.029344, 0.000000, 89.899635, 82.456283, 0.000000, 1.134920, 1.002417, 1.045661}, //skin 82
	{0.097840, 0.029344, 0.000000, 89.899635, 82.456283, 0.000000, 1.134920, 1.002417, 1.045661}, //skin 83
	{0.097840, 0.029344, 0.000000, 89.899635, 82.456283, 0.000000, 1.134920, 1.002417, 1.045661}, //skin 84
	{0.075789, 0.029344, 0.000000, 89.899635, 82.456283, 0.000000, 1.134920, 1.005379, 0.995997}, //skin 85
	{0.060571, 0.013831, 0.000000, 88.573463, 83.217987, 0.571479, 1.002084}, //skin 86
	{0.086140, 0.033741, 0.000000, 89.899635, 82.456283, 0.000000, 1.134920, 1.002417, 1.045661}, //skin 87
	{0.07, 0.039999, 0.0, 88.0, 82.0, 0.0}, //skin 88
	{0.086140, 0.004411, 0.000000, 89.899635, 82.456283, 0.000000, 1.012524, 1.000668, 0.999287}, //skin 89
	{0.054694, 0.021682, 0.007682, 90.191528, 75.430236, 0.296153}, //skin 90
	{0.054694, 0.021682, 0.007682, 90.191528, 75.430236, 0.296153}, //skin 91
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 92
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 93
	{0.050000, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 94
	{0.050000, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 95
	{0.050000, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 96
	{0.050000, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 97
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 98
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 99
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 100
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 101
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 102
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 103
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 104
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 105
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 106
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 107
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 108
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 109
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 110
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 111
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 112
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 113
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 114
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 115
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 116
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 117
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 118
	{0.065985, 0.011633, 0.000000, 88.573463, 83.217987, 0.571479, 1.002084}, //skin 119
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 120
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 121
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 122
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 123
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 124
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 125
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 126
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 127
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 128
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 129
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 130
	{0.079999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 131
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 132
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 133
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 134
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 135
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 136
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 137
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 138
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 139
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 140
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 141
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 142
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 143
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 144
	{0.090000, 0.0, 0.0, 88.0, 82.0, 0.0}, //skin 145
	{0.090000, 0.0, 0.0, 88.0, 82.0, 0.0}, //skin 146
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 147
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 148
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 149
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 150
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 151
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 152
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 153
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 154
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 155
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 156
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 157
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 158
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 159
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 160
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 161
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 162
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 163
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 164
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 165
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 166
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 167
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 168
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 169
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 170
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 171
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 172
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 173
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 174
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 175
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 176
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 177
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 178
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 179
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 180
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 181
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 182
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 183
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 184
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 185
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 186
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 187
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 188
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 189
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 190
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 191
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 192
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 193
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 194
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 195
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 196
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 197
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 198
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 199
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 200
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 201
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 202
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 203
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 204
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 205
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 206
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 207
	{0.060571, 0.013831, 0.000000, 88.573463, 83.217987, 0.571479, 1.002084}, //skin 208
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 209
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 210
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 211
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 212
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 213
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 214
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 215
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 216
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 217
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 218
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 219
	{0.029999, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 220
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 221
	{0.07, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 222
	{0.07, 0.050000, 0.0, 88.0, 82.0, 0.0}, //skin 223
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 224
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 225
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 226
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 227
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 228
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 229
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 230
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 231
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 232
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 233
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 234
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 235
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 236
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 237
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 238
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 239
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 240
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 241
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 242
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 243
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 244
	{0.07, 0.029999, 0.0, 88.0, 82.0, 0.0}, //skin 245
	{0.07, 0.050000, 0.0, 88.0, 82.0, 0.0}, //skin 246
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 247
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 248
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 249
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 250
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 251
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 252
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 253
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 254
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 255
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 256
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 257
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 258
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 259
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 260
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 261
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 262
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 263
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 264
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 265
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 266
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 267
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 268
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 269
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 270
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 271
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 272
	{0.060571, 0.013831, 0.000000, 88.573463, 83.217987, 0.571479, 1.002084}, //skin 273
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 274
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 275
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 276
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 277
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 278
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 279
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 280
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 281
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 282
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 283
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 284
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 285
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 286
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 287
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 288
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, //skin 289
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 290
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 291
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 292
	{0.07, 0.019999, 0.0, 88.0, 82.0, 0.0}, //skin 293
	{0.07, 0.019999, 0.0, 91.0, 84.0, 0.0}, //skin 294
	{0.050000, 0.019998, 0.0, 86.0, 82.0, 0.0}, //skin 295
	{0.064999, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 296
	{0.064999, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 297
	{0.064999, 0.009999, 0.0, 88.0, 82.0, 0.0}, //skin 298
	{0.064998, 0.019999, 0.0, 88.0, 82.0, 0.0} //skin 299
};

new TruckingCheck[MAX_PLAYERS];
new Text3D:vehicle3Dtext[MAX_VEHICLES];
new vehiclecallsign[MAX_VEHICLES];
new PoliceDrone[MAX_PLAYERS];

// --------------------------------- End Variables