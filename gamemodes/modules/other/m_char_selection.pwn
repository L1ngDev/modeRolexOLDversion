
#define CHAR_SEL_ACTION_SELECT          1
#define CHAR_SEL_ACTION_PLAY            2

#define CHAR_CREATE_ACTION_PREV_SKIN    0
#define CHAR_CREATE_ACTION_NEXT_SKIN    1
#define CHAR_CREATE_ACTION_CREATE       2
#define CHAR_CREATE_ACTION_GENDER       3

new cs_male_skins[] = { 1, 2, 23, 29, 30 };
new cs_female_skins[] = { 9, 10, 12, 13, 56 };

new char_create_skin_index[MAX_PLAYERS];
new char_create_gender[MAX_PLAYERS];
new bool:cs_in_char_selection[MAX_PLAYERS];

stock hide_game_load_screen(playerid)
{
	onServerDestroy(playerid, 13);
	onServerDestroy(playerid, 15);
}

stock show_char_selection_ui(playerid)
{
	cs_in_char_selection[playerid] = true;
	p_t_info[playerid][p_logged] = false;
	player_loaded{playerid} = 0;

	// Destroy loading screens
	hide_game_load_screen(playerid);
	onServerDestroy(playerid, UI_RECONNECT);

	TogglePlayerHudElement(playerid, HUD_ELEMENT_CHAT, false);
	TogglePlayerHudElement(playerid, HUD_ELEMENT_HUD, false);
	TogglePlayerHudElement(playerid, HUD_ELEMENT_KILL_LIST, false);
	TogglePlayerHudElement(playerid, HUD_ELEMENT_TEXTLABELS, false);

	// Exit spectating & spawn model in clothing shop
	TogglePlayerSpectating(playerid, false);
	TogglePlayerControllable(playerid, false);

	set_world(playerid, playerid + 1);
	set_interior(playerid, registration_interior);

	SetPlayerPos(playerid, registration_skin_position[0], registration_skin_position[1], registration_skin_position[2]);
	SetPlayerFacingAngle(playerid, registration_skin_position[3]);

	SetPlayerCameraPos(playerid, registration_camera_pos[0], registration_camera_pos[1], registration_camera_pos[2]);
	SetPlayerCameraLookAt(playerid, registration_camera_pos[3], registration_camera_pos[4], registration_camera_pos[5]);

	new _lid = GetPVarInt(playerid, "launcherId");
	new pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pname, sizeof(pname));

	new query_string[1024];
	if (_lid > 0)
	{
		mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT u_id, u_name, u_level, u_skin, u_vip, u_money, IFNULL((SELECT u_b_date FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_until, IFNULL((SELECT u_b_ndate FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_from, IFNULL((SELECT u_b_admin FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_admin, IFNULL((SELECT u_b_reason FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_reason FROM users WHERE u_launcher = '%d' LIMIT 3", _lid);
	}
	else
	{
		mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT u_id, u_name, u_level, u_skin, u_vip, u_money, IFNULL((SELECT u_b_date FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_until, IFNULL((SELECT u_b_ndate FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_from, IFNULL((SELECT u_b_admin FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_admin, IFNULL((SELECT u_b_reason FROM users_bans WHERE u_b_name=users.u_name AND u_b_date>NOW() ORDER BY u_b_ndate DESC LIMIT 1),'') ban_reason FROM users WHERE u_name = '%e' LIMIT 3", pname);
	}
	mysql_tquery(sql_connection, query_string, "OnCharSelectionDataLoaded", "i", playerid);
}

forward OnCharSelectionDataLoaded(playerid);
public OnCharSelectionDataLoaded(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	new json_string[2048];

	if (!rows)
	{
		format(json_string, sizeof(json_string), "[]");
		SetPVarInt(playerid, "selected_char_id", 0);
		SetPVarString(playerid, "selected_char_name", "");
		SetPlayerSkin(playerid, 1);
		SetPlayerPos(playerid, registration_skin_position[0], registration_skin_position[1], registration_skin_position[2]);
		SetPlayerFacingAngle(playerid, registration_skin_position[3]);
	}
	else
	{
		new char_db_id[3], c_skin[3], c_lvl[3], c_vip[3], c_name[3][MAX_PLAYER_NAME], c_ban[3][256], c_ban_until[3][32], c_ban_from[3][32], c_ban_admin[3][MAX_PLAYER_NAME], c_ban_reason[3][96];

		for (new i = 0; i < rows && i < 3; i++)
		{
			char_db_id[i] = cache_get_field_content_int(i, "u_id", sql_connection);
			c_skin[i] = cache_get_field_content_int(i, "u_skin", sql_connection);
			c_lvl[i] = cache_get_field_content_int(i, "u_level", sql_connection);
			c_vip[i] = cache_get_field_content_int(i, "u_vip", sql_connection);
			cache_get_field_content(i, "u_name", c_name[i], sql_connection, MAX_PLAYER_NAME);
			cache_get_field_content(i, "ban_until", c_ban_until[i], sql_connection, 32);
			cache_get_field_content(i, "ban_from", c_ban_from[i], sql_connection, 32);
			cache_get_field_content(i, "ban_admin", c_ban_admin[i], sql_connection, MAX_PLAYER_NAME);
			cache_get_field_content(i, "ban_reason", c_ban_reason[i], sql_connection, 96);
			if (strlen(c_ban_until[i]) > 0) format(c_ban[i], 256, "%s|%s|%s|%s", c_ban_until[i], c_ban_from[i], c_ban_admin[i], c_ban_reason[i]);
		}

		if (rows == 1)
		{
			format(json_string, sizeof(json_string),
				"[{\"number\":1,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":true,\"current\":true}]",
				c_name[0], c_lvl[0], c_vip[0], c_ban[0]
			);
		}
		else if (rows == 2)
		{
			format(json_string, sizeof(json_string),
				"[{\"number\":1,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":true,\"current\":true},{\"number\":2,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":false,\"current\":false}]",
				c_name[0], c_lvl[0], c_vip[0], c_ban[0],
				c_name[1], c_lvl[1], c_vip[1], c_ban[1]
			);
		}
		else
		{
			format(json_string, sizeof(json_string),
				"[{\"number\":1,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":true,\"current\":true},{\"number\":2,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":false,\"current\":false},{\"number\":3,\"name\":\"%s\",\"level\":%d,\"premiumType\":%d,\"ban\":\"%s\",\"isCurrent\":false,\"current\":false}]",
				c_name[0], c_lvl[0], c_vip[0], c_ban[0],
				c_name[1], c_lvl[1], c_vip[1], c_ban[1],
				c_name[2], c_lvl[2], c_vip[2], c_ban[2]
			);
		}

		SetPVarInt(playerid, "selected_char_id", char_db_id[0]);
		SetPVarString(playerid, "selected_char_name", c_name[0]);

		if (c_skin[0] <= 0) c_skin[0] = 1;
		SetPlayerSkin(playerid, c_skin[0]);
		SetPlayerPos(playerid, registration_skin_position[0], registration_skin_position[1], registration_skin_position[2]);
		SetPlayerFacingAngle(playerid, registration_skin_position[3]);
	}

	onServerSendData(playerid, UI_CHAR_SELECTION, 0, json_string);
	return 1;
}

stock show_char_create_ui(playerid)
{
	onServerDestroy(playerid, UI_CHAR_SELECTION);
	onServerSendData(playerid, UI_CHAR_CREATE, 0, "{}");

	char_create_skin_index[playerid] = 0;
	char_create_gender[playerid] = 0;
	SetPlayerSkin(playerid, cs_male_skins[0]);

	set_world(playerid, playerid + 1);
	set_interior(playerid, registration_interior);

	SetPlayerPos(playerid, registration_skin_position[0], registration_skin_position[1], registration_skin_position[2]);
	SetPlayerFacingAngle(playerid, registration_skin_position[3]);

	SetPlayerCameraPos(playerid, registration_camera_pos[0], registration_camera_pos[1], registration_camera_pos[2]);
	SetPlayerCameraLookAt(playerid, registration_camera_pos[3], registration_camera_pos[4], registration_camera_pos[5]);
}

stock show_packet_char_selection(playerid, actionId, data[])
{
	if (actionId == CHAR_SEL_ACTION_SELECT)
	{
		new slot = strval(data);
		new _lid = GetPVarInt(playerid, "launcherId");
		new pname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, pname, sizeof(pname));

		new query_string[1024];
		if (_lid > 0)
		{
			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT u_id, u_name, u_skin FROM users WHERE u_launcher = '%d' LIMIT %d, 1", _lid, slot - 1);
		}
		else
		{
			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT u_id, u_name, u_skin FROM users WHERE u_name = '%e' LIMIT %d, 1", pname, slot - 1);
		}
		mysql_tquery(sql_connection, query_string, "OnCharSlotSelectCallback", "ii", playerid, slot);
	}
	else if (actionId == CHAR_SEL_ACTION_PLAY)
	{
		new selected_name[MAX_PLAYER_NAME];
		GetPVarString(playerid, "selected_char_name", selected_name, sizeof(selected_name));
		if (strlen(selected_name) > 1) {
			SetPlayerName(playerid, selected_name);
		}
		
		onServerDestroy(playerid, UI_CHAR_SELECTION);
		show_spawn_selection_ui(playerid);
	}
	return 1;
}

forward OnCharSlotSelectCallback(playerid, slot);
public OnCharSlotSelectCallback(playerid, slot)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if (rows > 0)
	{
		new char_id = cache_get_field_content_int(0, "u_id", sql_connection);
		new char_skin = cache_get_field_content_int(0, "u_skin", sql_connection);
		new char_name[MAX_PLAYER_NAME];
		cache_get_field_content(0, "u_name", char_name, sql_connection, sizeof(char_name));

		SetPVarInt(playerid, "selected_char_id", char_id);
		SetPVarString(playerid, "selected_char_name", char_name);

		if (char_skin <= 0) char_skin = 1;
		SetPlayerSkin(playerid, char_skin);
		SetPlayerPos(playerid, registration_skin_position[0], registration_skin_position[1], registration_skin_position[2]);
		SetPlayerFacingAngle(playerid, registration_skin_position[3]);
	}
	else
	{
		show_char_create_ui(playerid);
	}
	return 1;
}

stock show_spawn_selection_ui(playerid)
{
	new bool:has_house = (Iter_Count(player_houses[playerid]) > 0 || p_info[playerid][house] != -1);
	new bool:has_flat = (p_info[playerid][house] != -1);
	new bool:has_org = (p_info[playerid][member] > 0 || p_info[playerid][leader] > 0);
	new bool:has_family = (p_info[playerid][family] > 0);
	new bool:has_exit = (p_info[playerid][exit_pos][0] != 0.0);

	new json_string[512];
	format(json_string, sizeof(json_string),
		"[{\"type\":0,\"isAvailable\":true},{\"type\":1,\"isAvailable\":%s},{\"type\":2,\"isAvailable\":%s},{\"type\":3,\"isAvailable\":%s},{\"type\":4,\"isAvailable\":%s},{\"type\":5,\"isAvailable\":%s}]",
		has_house ? "true" : "false",
		has_flat ? "true" : "false",
		has_org ? "true" : "false",
		has_family ? "true" : "false",
		has_exit ? "true" : "false"
	);

	onServerSendData(playerid, 84, 0, json_string);
	onServerSendData(playerid, 86, 0, json_string);
	return 1;
}

stock show_packet_spawn_selection(playerid, actionId, data[])
{
	if (actionId == 0 || actionId == 1)
	{
		new spawnType = strval(data);

		onServerDestroy(playerid, 84);
	onServerDestroy(playerid, 86);
		hide_game_load_screen(playerid);

		cs_in_char_selection[playerid] = false;
		p_t_info[playerid][p_logged] = true;
		SetPVarInt(playerid, "spawnType", spawnType);
		player_device{playerid} = 2;

		// Restore HUD & controls when spawned
		TogglePlayerControllable(playerid, true);
		TogglePlayerHudElement(playerid, HUD_ELEMENT_CHAT, true);
		TogglePlayerHudElement(playerid, HUD_ELEMENT_HUD, true);
		TogglePlayerHudElement(playerid, HUD_ELEMENT_KILL_LIST, true);
		TogglePlayerHudElement(playerid, HUD_ELEMENT_TEXTLABELS, true);

		new selected_id = GetPVarInt(playerid, "selected_char_id");
		new query_string[1024];

		if (selected_id > 0)
		{
			new selected_name[MAX_PLAYER_NAME];
			GetPVarString(playerid, "selected_char_name", selected_name, sizeof(selected_name));
			format(p_info[playerid][name], MAX_PLAYER_NAME, "%s", selected_name);

			format(query_string, sizeof(query_string), "SELECT * FROM users WHERE u_id = '%d' LIMIT 1", selected_id);
			mysql_tquery(sql_connection, query_string, "load_user", "i", playerid);
		}
		else
		{
			new pname[MAX_PLAYER_NAME];
			GetPlayerName(playerid, pname, sizeof(pname));
			format(p_info[playerid][name], MAX_PLAYER_NAME, "%s", pname);

			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT * FROM users WHERE u_name = '%e' LIMIT 1", pname);
			mysql_tquery(sql_connection, query_string, "OnSpawnUserCheck", "i", playerid);
		}
	}
	return 1;
}

forward OnSpawnUserCheck(playerid);
public OnSpawnUserCheck(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if (rows > 0)
	{
		load_user(playerid);
	}
	else
	{
		new pname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, pname, sizeof(pname));

		new query_string[512];
		mysql_format(sql_connection, query_string, sizeof(query_string),
			"INSERT INTO users (u_name, u_password, u_ip_registration, u_date_registration, u_gender, u_skin, u_launcher, u_level, u_money) VALUES ('%e', 'pass123', '%s', NOW(), '0', '1', '%d', '1', '5000')",
			pname, p_t_info[playerid][p_ip], GetPVarInt(playerid, "launcherId")
		);
		mysql_tquery(sql_connection, query_string, "OnSpawnUserCreated", "i", playerid);
	}
	return 1;
}

forward OnSpawnUserCreated(playerid);
public OnSpawnUserCreated(playerid)
{
	new insert_id = cache_insert_id();
	if (insert_id > 0)
	{
		p_info[playerid][id] = insert_id;
		new query_string[1024];
		format(query_string, sizeof(query_string), "SELECT * FROM users WHERE u_id = '%d' LIMIT 1", insert_id);
		mysql_tquery(sql_connection, query_string, "load_user", "i", playerid);
	}
	else
	{
		spawn_info(playerid);
	}
	return 1;
}

stock show_packet_char_create(playerid, actionId, data[])
{
	new _gender;
	switch (actionId)
	{
		case CHAR_CREATE_ACTION_PREV_SKIN:
		{
			_gender = strval(data);
			char_create_gender[playerid] = _gender;

			if (_gender == 0)
			{
				char_create_skin_index[playerid]--;
				if (char_create_skin_index[playerid] < 0)
					char_create_skin_index[playerid] = sizeof(cs_male_skins) - 1;
				SetPlayerSkin(playerid, cs_male_skins[char_create_skin_index[playerid]]);
			}
			else
			{
				char_create_skin_index[playerid]--;
				if (char_create_skin_index[playerid] < 0)
					char_create_skin_index[playerid] = sizeof(cs_female_skins) - 1;
				SetPlayerSkin(playerid, cs_female_skins[char_create_skin_index[playerid]]);
			}
		}
		case CHAR_CREATE_ACTION_NEXT_SKIN:
		{
			_gender = strval(data);
			char_create_gender[playerid] = _gender;

			if (_gender == 0)
			{
				char_create_skin_index[playerid]++;
				if (char_create_skin_index[playerid] >= sizeof(cs_male_skins))
					char_create_skin_index[playerid] = 0;
				SetPlayerSkin(playerid, cs_male_skins[char_create_skin_index[playerid]]);
			}
			else
			{
				char_create_skin_index[playerid]++;
				if (char_create_skin_index[playerid] >= sizeof(cs_female_skins))
					char_create_skin_index[playerid] = 0;
				SetPlayerSkin(playerid, cs_female_skins[char_create_skin_index[playerid]]);
			}
		}
		case CHAR_CREATE_ACTION_CREATE:
		{
			new nickname[MAX_PLAYER_NAME];

			new pos = strfind(data, "\"nickName\":\"", true);
			if (pos != -1)
			{
				pos += 12;
				new end_pos = strfind(data, "\"", true, pos);
				if (end_pos != -1)
				{
					strmid(nickname, data, pos, end_pos, MAX_PLAYER_NAME);
				}
			}

			if (strlen(nickname) < 3) return 1;

			new query_string[128];
			mysql_format(sql_connection, query_string, sizeof(query_string), "SELECT u_id FROM users WHERE u_name = '%e' LIMIT 1", nickname);

			format(reg_info[playerid][reg_referal], MAX_PLAYER_NAME, "%s", nickname);
			mysql_tquery(sql_connection, query_string, "OnCharCreateCheck", "i", playerid);
		}
		case CHAR_CREATE_ACTION_GENDER:
		{
			_gender = strval(data);
			char_create_gender[playerid] = _gender;
			char_create_skin_index[playerid] = 0;

			if (_gender == 0)
				SetPlayerSkin(playerid, cs_male_skins[0]);
			else
				SetPlayerSkin(playerid, cs_female_skins[0]);
		}
	}
	return 1;
}

callback: OnCharCreateCheck(playerid)
{
	new rows, fields;
	cache_get_data(rows, fields);

	if (rows > 0) return 1;

	new _cskin;
	if (char_create_gender[playerid] == 0)
		_cskin = cs_male_skins[char_create_skin_index[playerid]];
	else
		_cskin = cs_female_skins[char_create_skin_index[playerid]];

	new nickname[MAX_PLAYER_NAME];
	format(nickname, MAX_PLAYER_NAME, "%s", reg_info[playerid][reg_referal]);

	if ( strlen ( reg_info[playerid][reg_password] ) < 1 )
	{
		new _rnd_pass[13];
		format(_rnd_pass, sizeof(_rnd_pass), "m%d%d", gettime(), random(9999));
		format(reg_info[playerid][reg_password], 24, "%s", _rnd_pass);
	}

	new query_string[512];
	new launcher_id_value = GetPVarInt(playerid, "launcherId");
	mysql_format(sql_connection, query_string, sizeof(query_string), "INSERT INTO users (u_name, u_password, u_ip_registration, u_date_registration, u_gender, u_skin, u_launcher, u_level, u_money) VALUES ('%e', '%e', '%s', NOW(), '%d', '%d', '%d', '1', '5000')", nickname, reg_info[playerid][reg_password], p_t_info[playerid][p_ip], char_create_gender[playerid], _cskin, launcher_id_value);
	mysql_tquery(sql_connection, query_string, "OnCharCreated", "i", playerid);
	return 1;
}

callback: OnCharCreated(playerid)
{
	new insert_id = cache_insert_id();
	if (insert_id > 0)
	{
		SetPVarInt(playerid, "selected_char_id", insert_id);
		new nickname[MAX_PLAYER_NAME];
		format(nickname, MAX_PLAYER_NAME, "%s", reg_info[playerid][reg_referal]);
		SetPVarString(playerid, "selected_char_name", nickname);

		onServerDestroy(playerid, UI_CHAR_CREATE);
		show_char_selection_ui(playerid);
	}
	return 1;
}

stock char_selection_on_disconnect(playerid)
{
	char_create_skin_index[playerid] = 0;
	char_create_gender[playerid] = 0;
}
