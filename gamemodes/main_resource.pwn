/*
		   _____       _                    _____                     
		  / ____|     | |                  |  __ \                    
		 | (___   __ _| | ___   _ _ __ __ _| |__) |   _ _______ _ __  
		  \___ \ / _` | |/ / | | | '__/ _` |  _  / | | |_  / _ \ '_ \ 
		  ____) | (_| |   <| |_| | | | (_| | | \ \ |_| |/ /  __/ | | |
		 |_____/ \__,_|_|\_\\__,_|_|  \__,_|_|  \_\__, /___\___|_| |_|
		                                           __/ | ROLEPLAY SAMP
		                                          |___/

		======================== » Gamemode Credits ========================

        »  Scripter	        : Caer, Ravin7, Zean
		»  Mapper			: xTranZK, Xian
        »  Version          : 3.7.9
        »  Ip & Port		: 51.79.144.255:7771
        »  Link             : dsc.gg/sakura-ryzen
			
			* Gamemode Sakura Ryzen Roleplay shared by Zean.
			* Beberapa map & sistem telah dibuang.
		=====================================================================

*/

#pragma compress 0
#pragma dynamic 500000
#pragma tabsize 1
#pragma SAMPCTL

// --------------------------------- Includes

#include <a_samp> 
#define SSCANF_NO_NICE_FEATURES
#undef MAX_PLAYERS
#define MAX_PLAYERS (500)

#include <a_mysql> 
#include <foreach>
#include <eSelection> 
#include <easyDialog> 
#include <a_players>
#include <a_actor> 
#include <gvar>
#include <progress2>
#include <sscanf2>
#include <streamer>
#include <fixobject> 
#include <zcmd>
#include <YSI\y_hooks>
#include <Gettime> 
#include <Teleport>

// --------------------------------- Resources

#include "resources\server_Define.inc" 
#include "resources\server_variable.inc" 
#include "resources\server_hook.inc" 
#include "resources\server_native.inc"
#include "resources\server_stock.inc"
#include "resources\server_function.inc"
#include "resources\server_public.inc"
#include "resources\server_discord.inc" 
#include "resources\server_dialog.inc"
#include "resources\server_command.inc"