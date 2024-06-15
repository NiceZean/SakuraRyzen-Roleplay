#define COLOR_CLIENT      (0xAAC4E5FF)
#define COLOR_WHITE       (0xFFFFFFFF)
#define COLOR_RED         (0xFF0000FF)
#define COLOR_CYAN        (0x33CCFFFF)
#define COLOR_LIGHTRED    (0xFF6347FF)
#define COLOR_LIGHTGREEN  (0x9ACD32FF)
#define COLOR_YELLOW      (0xFFFF00FF)
#define COLOR_GREY        (0xAFAFAFFF)
#define COLOR_HOSPITAL    (0xFF8282FF)
#define COLOR_PURPLE      (0xD0AEEBFF)
#define COLOR_LIGHTYELLOW (0xF5DEB3FF)
#define COLOR_DARKBLUE    (0x1394BFFF) 
#define COLOR_ORANGE      (0xFFA500FF)
#define COLOR_LIME        (0x00FF00FF)
#define COLOR_GREEN       (0x33CC33FF)
#define COLOR_BLUE        (0x2641FEFF)
#define COLOR_FACTION     (0xBDF38BFF)
#define COLOR_RADIO       (0x8D8DFFFF)
#define COLOR_LIGHTBLUE   (0x007FFFFF)
#define COLOR_SERVER      (0xFFFF90FF)
#define COLOR_DEPARTMENT  (0xF0CC00FF)
#define DEFAULT_COLOR     (0xFFFFFFFF)

#define function%0(%1) forward %0(%1); public %0(%1)

#define PURPLE_E2	"{7348EB}"
#define RED_E 		"{FF0000}"
#define BLUE_E 		"{004BFF}"
#define SBLUE_E 	"{56A4E4}"
#define PINK_E 		"{FFB6C1}"
#define YELLOW_E 	"{FFFF00}"
#define LG_E 		"{00FF00}"
#define LB_E 		"{15D4ED}"
#define LB2_E 		"{87CEFA}"
#define GREY_E 		"{BABABA}"
#define GREY2_E 	"{778899}"
#define GREY3_E 	"{C8C8C8}"
#define DARK_E 		"{7A7A7A}"
#define WHITE_E 	"{FFFFFF}"
#define WHITEP_E 	"{FFE4C4}"
#define IVORY_E 	"{FFFF82}"
#define ORANGE_E 	"{DB881A}"
#define ORANGE_E2	"{FF5000}"
#define GREEN_E 	"{3BBD44}"
#define PURPLE_E 	"{5A00FF}"
#define LIME_E 		"{D2D2AB}"
#define LRED_E		"{E65555}"

#define NT_DISTANCE (25.0)

#define THREAD_CREATE_CHAR (1)
#define THREAD_FIND_ACCOUNT (2)
#define THREAD_SHOW_CHARACTER (3)
#define THREAD_CHARACTERS (4)
#define THREAD_LOAD_CHARACTER (5)
#define THREAD_LOAD_CAR (6)
#define THREAD_LOAD_TICKETS (7)
#define THREAD_LOAD_INVENTORY (8)
#define THREAD_BAN_LOOKUP (9)
#define THREAD_LOAD_CONTACTS (10)
#define THREAD_LOAD_LOCATIONS (11)

#define MODEL_SELECTION_GLASSES (1)
#define MODEL_SELECTION_HATS (2)
#define MODEL_SELECTION_BANDANAS (3)
#define MODEL_SELECTION_SKIN (4)
#define MODEL_SELECTION_INVENTORY (5)
#define MODEL_SELECTION_CLOTHES (6)
#define MODEL_SELECTION_DEALER (7)
#define MODEL_SELECTION_DEALER_ADD (8)
#define MODEL_SELECTION_BUY_CAR (9)
#define MODEL_SELECTION_FURNITURE (10)
#define MODEL_SELECTION_COLOR (11)
#define MODEL_SELECTION_SKINS (12)
#define MODEL_SELECTION_ADD_SKIN (13)
#define MODEL_SELECTION_FACTION_SKIN (14)
#define MODEL_SELECTION_FRISK (15)

#define FACTION_POLICE (1)
#define FACTION_MEDIC (2)
#define FACTION_MECHANIC (3)
#define FACTION_GANG (4)

#define JOB_COURIER (1)
#define JOB_SORTER (2)
#define JOB_TAXI (3)
#define JOB_WEAPON_SMUGGLER (4)
#define JOB_MINER (5)
#define JOB_FOOD_VENDOR (6)
#define JOB_GARBAGE (7)

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GREEN, "[SERVER]: "WHITE_E""%1)

#define SendInfoMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_LIGHTBLUE, "{9a03ff}[INFO]: "WHITE_E""%1)

#define SendUsageMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_SERVER, "[USAGE]: "WHITE_E""%1)

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_RED, "[ERROR]: "WHITE_E""%1) 

#define MAX_REPORTS (50)
#define MAX_INVENTORY (120)
#define MAX_HOUSES (500)
#define MAX_HOUSE_STORAGE (10)
#define MAX_BUSINESSES (500) 
#define MAX_DROPPED_ITEMS (5000)
#define MAX_ENTRANCES (100)
#define MAX_DEALERSHIP_CARS (40)
#define MAX_DYNAMIC_CARS (1500)
#define MAX_GAS_PUMPS (100)
#define MAX_FURNITURE (2000)
#define MAX_HOUSE_FURNITURE (30)
#define MAX_DYNAMIC_JOBS (25)
#define MAX_CONTACTS (20)
#define MAX_GPS_LOCATIONS (20)
#define MAX_CAR_STORAGE (5)
#define MAX_CRATES (200)
#define MAX_DRUG_PLANTS (200)
#define MAX_FACTIONS (15)
#define MAX_PLAYER_TICKETS (10)
#define MAX_BARRICADES (25)
#define MAX_BOOTHS (8)
#define MAX_GATES (100)
#define MAX_ATM_MACHINES (50)
#define MAX_GARBAGE_BINS (50)
#define MAX_VENDORS (50)
#define MAX_WEAPON_RACKS (500)
#define MAX_SPEED_CAMERAS (100)
#define MAX_LISTED_ITEMS (10)
#define MAX_GRAFFITI_POINTS (20)
#define MAX_METAL_DETECTORS (20)
#define MAX_RENT_POINTS (50)

#define MAX_OWNABLE_CARS (8)
#define MAX_OWNABLE_HOUSES (1)
#define MAX_OWNABLE_BUSINESSES (3)

#define MAX_BACKPACKS (2000)
#define MAX_BACKPACK_ITEMS (4000)
#define MAX_BACKPACK_CAPACITY (10)

#define VEHICLE_RESPAWN 7200

// --------------------------------- End Defins