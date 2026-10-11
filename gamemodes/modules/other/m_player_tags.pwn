#include <custom/playertags>

new player_tag_text [ MAX_PLAYERS ] [ 32 ] ;
new player_tag_color [ MAX_PLAYERS ] [ 8 ] ;
new player_tag_color_box [ MAX_PLAYERS ] [ 8 ] ;
new player_tag_style [ MAX_PLAYERS ] ;
new player_tags_sync_timer ;

CMD:tags ( playerid )
{
    if ( player_tag_style [ playerid ] < 1 )
    {
        new _tag_query [ 160 ] ;
        mysql_format ( sql_connection, _tag_query, sizeof _tag_query, "SELECT `u_tag_style`,`u_tag_text`,`u_tag_color`,`u_tag_color_box` FROM `users` WHERE `u_id` = '%d' LIMIT 1", p_info [ playerid ] [ id ] ) ;
        mysql_tquery ( sql_connection, _tag_query, "player_tags_reload", "i", playerid ) ;
        SendClientMessage ( playerid, col_gray, !"{"#cRInfo"}* Загружаем Ваш персональный тэг..." ) ;
        return 1 ;
    }

	if ( player_tag_style [ playerid ] < 1 ) return SendClientMessage ( playerid, col_gray, !"{"#cRInfo"}* {"#cGRInfo"}У Вас нет персонального тэга!" ) ;
	
	global_string [ 0 ] = EOS ;
	format ( global_string, 144, "{"#cWH"}Ваш персональный тэг {%s}%s{"#cWH"}.\n{"#cWH"}Цвет Вашей обводки подчёркнут на слове '{%s}обводка{"#cWH"}'.",
	player_tag_color [ playerid ], player_tag_text [ playerid ], player_tag_color_box [ playerid ] ) ;
	show_dialog ( playerid, d_none, DIALOG_STYLE_MSGBOX, "{"#cBHD"}Тэг", global_string, "Передать", "Закрыть" ) ;
	return 1 ;
}

/*stock tags_OnDialogResponse ( playerid, dialogid, response, listitem, inputtext [ ] )
{
	switch ( dialogid )
	{
		case d_tags:
		{
			if ( ! response ) return 1 ;
			
			
			return 1 ;
		}
	}
	return 0 ;
}*/

forward player_tags_reload ( playerid ) ;
public player_tags_reload ( playerid )
{
    if ( ! IsPlayerConnected ( playerid ) ) return 1 ;
    player_tag_style [ playerid ] = cache_get_field_content_int ( 0, "u_tag_style", sql_connection ) ;
    cache_get_field_content ( 0, "u_tag_text", player_tag_text [ playerid ], sql_connection, 32 ) ;
    cache_get_field_content ( 0, "u_tag_color", player_tag_color [ playerid ], sql_connection, 8 ) ;
    cache_get_field_content ( 0, "u_tag_color_box", player_tag_color_box [ playerid ], sql_connection, 8 ) ;
    if ( player_tag_color [ playerid ] [ 0 ] == '#' ) strdel ( player_tag_color [ playerid ], 0, 1 ) ;
    if ( player_tag_color_box [ playerid ] [ 0 ] == '#' ) strdel ( player_tag_color_box [ playerid ], 0, 1 ) ;
    if ( player_tag_style [ playerid ] > 0 )
    {
        show_player_tags ( playerid ) ;
        for ( new viewer = 0 ; viewer < MAX_PLAYERS ; viewer ++ )
            if ( IsPlayerConnected ( viewer ) && viewer != playerid ) show_player_tags ( playerid, viewer ) ;
        SetTimerEx ( "player_tags_delayed_send", 1500, false, "i", playerid ) ;
        if ( ! player_tags_sync_timer ) player_tags_sync_timer = SetTimer ( "player_tags_broadcast", 5000, true ) ;
    }
    else SendClientMessage ( playerid, col_gray, !"{"#cRInfo"}* {"#cGRInfo"}У Вас нет персонального тэга!" ) ;
    return 1 ;
}

forward player_tags_broadcast ( ) ;
public player_tags_broadcast ( )
{
    for ( new target = 0 ; target < MAX_PLAYERS ; target ++ )
    {
        if ( ! IsPlayerConnected ( target ) || player_tag_style [ target ] < 1 ) continue ;
        for ( new viewer = 0 ; viewer < MAX_PLAYERS ; viewer ++ )
            if ( IsPlayerConnected ( viewer ) ) show_player_tags ( target, viewer ) ;
    }
    return 1 ;
}
forward player_tags_delayed_send ( playerid ) ;
public player_tags_delayed_send ( playerid )
{
    if ( IsPlayerConnected ( playerid ) && player_tag_style [ playerid ] > 0 ) show_player_tags ( playerid ) ;
    return 1 ;
}

stock show_player_tags ( targetid, recipientid = -1 )
{
	new colorText, colorBox, _str [ 32 ], bool: _accept = false, _style = 2 ;
	switch ( p_info [ targetid ] [ vip ] )
	{
		/*case 1:
		{
			colorText = 0xcd7f32FF ;
			colorBox = 0xcd7f32FF ;
			
			format ( _str, sizeof _str, "VIP" ) ;
			_accept = true ;
		}
		case 2:
		{
			colorText = 0xc8c8c8FF ;
			colorBox = 0xc8c8c8FF ;
			
			format ( _str, sizeof _str, "VIP" ) ;
			_accept = true ;
		}*/
		case 3:
		{
			colorText = 0xc3900aFF ;
			colorBox = 0xc3900aFF ;
			
			format ( _str, sizeof _str, "VIP" ) ;
			_accept = true ;
		}
	}
	
	if ( p_info [ targetid ] [ leader ] > 0 && p_info [ targetid ] [ rank ] > 0 )
	{
		colorText = f_info [ p_info [ targetid ] [ member ] - 1 ] [ f_radar_color ] ;
		colorBox = colorText ;
			
		format ( _str, sizeof _str, "Лидер" ) ;
		_accept = true ;
	}
	
	if ( admin_info [ targetid ] [ admin ] > 0 )
	{
		colorText = 0xAA3333FF ;
		colorBox = 0xAA3333FF ;
			
		format ( _str, sizeof _str, "Admin" ) ;
		_accept = true ;
	}
	
	if ( player_tag_style [ targetid ] > 0 )
	{
		format ( _str, sizeof _str, "0x%sFF", player_tag_color [ targetid ] ) ;
		colorText = StrToHex ( _str ) ;
		format ( _str, sizeof _str, "0x%sFF", player_tag_color_box [ targetid ] ) ;
		colorBox = StrToHex ( _str ) ;
			
		format ( _str, sizeof _str, "%s", player_tag_text [ targetid ] ) ;
		_style = player_tag_style [ targetid ] ;
		_accept = true ;
	}
	
	if ( _accept == true )
	{
		SetPlayerTag ( recipientid, targetid, true, _str, _style, colorText, colorBox ) ;
		// Keep family and personal tag as independent client layers.
		SetPlayerInfo ( targetid, recipientid ) ;
	}
	return 1 ;
}