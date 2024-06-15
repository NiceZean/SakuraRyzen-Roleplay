#include <discord-cmd>

DCMD:restart(user, channel, params[])
{
	if(channel != DCC_FindChannelById("1214497498903748608")) return 1;
	SendRconCommand("gmx");
	return 1;
}

DCMD:off(user, channel, params[])
{
	if(channel != DCC_FindChannelById("1214497498903748608")) return 1;
	SendRconCommand("exit");
	return 1;
}

function DiscordInfoOn()
{
	DCC_SendChannelMessage(DCC_FindChannelById("1246893988330606633"), "**Sakura Ryzen Roleplay** is starting.");
	return 1;
}

function DiscordInfoOff()
{
	DCC_SendChannelMessage(DCC_FindChannelById("1246893988330606633"), "**Sakura Ryzen Roleplay** is shutting down.");
	return 1;
}

function BotDiscord()
{
	DCC_SetBotPresenceStatus(DCC_BotPresenceStatus:DO_NOT_DISTURB);
	return 1;
}

DCMD:daftar(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1242864816067051521")) return 1;

	new 
        id[21],
		str[128];

	if(isnull(params)) 
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!daftar [nama]");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1242864816067051521"), embed);
	}
	DCC_GetUserId(user, id, sizeof id);

	format(str, sizeof(str), "SELECT * FROM `accounts` WHERE `DiscordID` = '%s'", id);
	mysql_tquery(g_iHandle, str, "DiscordWhitelistCheckDiscord", "ss", params, id);
	return 1;
}

function DiscordWhitelistCheckDiscord(UcpName[], DiscordID[])
{
	new rows = cache_num_rows();
	if(rows > 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Akaun Discord ini telah mempunyai rekod mendaftar!");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		new str[178];
	    format(str, sizeof(str), "SELECT * FROM `accounts` WHERE `Username` = '%s'", UcpName);
	    mysql_tquery(g_iHandle, str, "DiscordWhitelistCheckName", "ss", UcpName, DiscordID);
	}
	return 1;
}

function DiscordWhitelistCheckName(UcpName[], DiscordID[])
{
	new rows = cache_num_rows();
	new token = RandomEx(111111, 988888);
	new DCC_User: user;
	if(rows > 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama ini telah digunakan! Sila guna nama lain");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		user = DCC_FindUserById(DiscordID);
		DCC_SetGuildMemberNickname(DCC_FindGuildById("928901667552919562"), user, UcpName);
		DCC_AddGuildMemberRole(DCC_FindGuildById("928901667552919562"), user, DCC_FindRoleById("1152587716635140218"));
		DCC_CreatePrivateChannel(user, "DiscordRegisterPM", "sds", UcpName, token, DiscordID);
	}
	return 1;
}

function DiscordRegisterPM(name[], pin, id[])
{
    new DCC_Channel:PM;
	PM = DCC_GetCreatedPrivateChannel();

	new DCC_Embed:embed = DCC_CreateEmbed(.title="Sakura Ryzen Roleplay");
	new str[320];

	DCC_SetEmbedDescription(embed, "```Hai! Akaun anda telah berjaya di daftarkan. Sila gunakan pin dibawah ini untuk pengesahan akaun di dalam permainan.```");
	format(str, sizeof str, "\n```%s```", name);
	DCC_AddEmbedField(embed, "AKAUN", str, bool:1);
	format(str, sizeof str, "\n```%d```", pin);
	DCC_AddEmbedField(embed, "PIN", str, bool:1);
	DCC_AddEmbedField(embed, "IP/PORT", "\n```51.79.144.255:7771```", bool:1);
	DCC_SetEmbedColour(embed, 0xFF0000);  
	DCC_SendChannelEmbedMessage(PM, embed);

	new string[200];
	format(string, sizeof(string),"INSERT INTO `accounts` (`Username`, `Token`, `DiscordID`, `RegisterDate`) VALUES ('%s', '%d', '%s', '%s')", name, pin, id, ReturnDate());
	mysql_tquery(g_iHandle, string);

	new strr[200];
	format(strr, sizeof(strr),  "Akaun '%s' telah berjaya di daftarkan! Sila semak mesej peribadi anda.", name);
	new DCC_Embed:embed4 = DCC_CreateEmbed("INFO!");
	DCC_SetEmbedDescription(embed4, strr);
	DCC_SetEmbedColour(embed4, 0xFF0000);
	DCC_SetEmbedImage(embed4, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
	DCC_SendChannelEmbedMessage(DCC_FindChannelById("1242864816067051521"), embed4);
	return 1;
}

DCMD:setpass(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758")) return 1;

	new name[128], pass[200];

    if(sscanf(params, "s[128]s[200]", name, pass))
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!setpass [nama] [kata laluan baru]\n\nNota: Sila masukkan nama akaun, bukan nama karakter.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `accounts` WHERE `Username` = '%s'", name);
    mysql_tquery(g_iHandle, str, "DiscordSetPassCheck", "ss", name, pass);
    return 1;
}


function DiscordSetPassCheck(name[], newpass[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama akaun tersebut tiada di database.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		static
			query[256];

		format(query, sizeof(query), "UPDATE `accounts` SET `Password` = '%s' WHERE `Username` = '%s'", newpass, name);
		mysql_tquery(g_iHandle, query);

		new str[240];
		format(str, sizeof(str), "Anda telah menetapkan kata laluan baharu untuk akaun '%s'.", name);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	return 1;
}


DCMD:unbl(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758"))
		return 1;
		
    if(isnull(params)) 
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!unbl [nama]");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `blacklist` WHERE `Username` = '%s'", params);
    mysql_tquery(g_iHandle, str, "DiscordUnBlacklistCheck", "s", params);
	return 1;
}

function DiscordUnBlacklistCheck(name[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama akaun tersebut tiada di database ban.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		Blacklist_Remove(name);

		Log_Write("logs/ban_log.txt", "[%s] SakuraRyzen Bot has unblacklisted account \"%s\".", ReturnDate(), name);

		new str[240];
		format(str, sizeof(str), "Akaun '%s' tidak dibuang dari senarai hitam.", name);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	return 1;
}

DCMD:bl(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758")) return 1;

	new name[128], reason[200];

    if(sscanf(params, "s[128]s[200]", name, reason))
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!bl [nama] [reason]\n\nNota: Sila masukkan nama akaun, bukan nama karakter.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `accounts` WHERE `Username` = '%s'", name);
    mysql_tquery(g_iHandle, str, "DiscordBlacklistCheck", "ss", name, reason);
    return 1;
}

function DiscordBlacklistCheck(name[], reason[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama akaun tersebut tiada di database.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		new str[290];

		Blacklist_Add("0.0.0.0", name, "SakuraRyzen Bot", reason);

		format(str, sizeof(str), "Akaun '%s' telah disenarai hitam dengan sebab %s.", name, reason);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);

		Log_Write("logs/ban_log.txt", "[%s] SakuraRyzen Bot has banned \"%s\" reason %s.", ReturnDate(), name, reason);
	}
	return 1;
}

DCMD:checkchar(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758"))
		return 1;
		
    if(isnull(params)) 
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!checkchar [nama]\n\nNota: Sila masukkan nama karakter, bukan nama akaun.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `characters` WHERE `Character` = '%s'", params);
    mysql_tquery(g_iHandle, str, "DiscordCharacterCheck", "s", params);
	return 1;
}

function DiscordCharacterCheck(params[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama karakter tersebut tiada di database.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	} 
	else 
	{
		new ucp[20], str[150];

		cache_get_field_content(0, "Username", ucp);

		format(str, sizeof(str), "Nama Karakter: %s\nNama Akaun: %s", params, ucp);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO KARAKTER!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	return 1;
}

DCMD:checkacc(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758"))
		return 1;
		
    if(isnull(params)) 
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!checkacc [nama]\n\nNota: Sila masukkan nama akaun, bukan nama karakter.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `characters` WHERE `Username` = '%s'", params);
    mysql_tquery(g_iHandle, str, "DiscordAccountCheck", "s", params);
	return 1;
}

function DiscordAccountCheck(params[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama akaun tersebut tiada di database.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		new ucp[20], str[150];

		cache_get_field_content(0, "Character", ucp);

		format(str, sizeof(str), "Nama Akaun: %s\nNama Karakter: %s", params, ucp);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO AKAUN!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	return 1;
}

DCMD:deletechar(user, channel, params[])
{
    if(channel != DCC_FindChannelById("1246381260247666758"))
		return 1;
		
    if(isnull(params)) 
	{
		new DCC_Embed:embed = DCC_CreateEmbed("PENGGUNAAN!");
		DCC_SetEmbedDescription(embed, "!deletechar [nama]\n\nNota: Sila masukkan nama karakter, bukan nama akaun.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}

	new str[560];
	format(str, sizeof(str), "SELECT * FROM `characters` WHERE `Character` = '%s'", params);
    mysql_tquery(g_iHandle, str, "DiscordDeleteCharCheck", "s", params);
	return 1;
}

function DiscordDeleteCharCheck(params[])
{
	new rows = cache_num_rows();
	if(rows == 0)
	{
		new DCC_Embed:embed = DCC_CreateEmbed("RALAT!");
		DCC_SetEmbedDescription(embed, "Nama karakter tersebut tiada di database.");
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		return DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	else 
	{
		new id = -1, str[150], query[500];

        id = cache_get_field_int(0, "ID");

        if (id) {
            format(query, sizeof(query), "DELETE FROM `contacts` WHERE `ID` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `gps` WHERE `ID` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `inventory` WHERE `ID` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `tickets` WHERE `ID` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `characters` WHERE `ID` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `cars` WHERE `carOwner` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `backpacks` WHERE `backpackPlayer` = '%d'", id);
            mysql_tquery(g_iHandle, query);

            format(query, sizeof(query), "DELETE FROM `salary` WHERE `Owner` = '%d'", id);
            mysql_tquery(g_iHandle, query);
        }

		format(str, sizeof(str), "Anda telah memadam karakter '%s' dari database.", params);
		new DCC_Embed:embed = DCC_CreateEmbed("INFO!");
		DCC_SetEmbedDescription(embed, str);
		DCC_SetEmbedColour(embed, 0xFF0000);
		DCC_SetEmbedImage(embed, "https://www.animatedimages.org/data/media/562/animated-line-image-0015.gif");
		DCC_SendChannelEmbedMessage(DCC_FindChannelById("1246381260247666758"), embed);
	}
	return 1;
}

// --------------------------------- End Discords