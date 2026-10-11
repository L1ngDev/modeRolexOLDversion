stock show_ui_passport ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_passport] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;
	
    new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, ITEM_PASSPORT ), s_year, s_month, s_day, s_hour, s_minute, s_second, _str [ 12 ] ;
	timestamp_to_date (
		USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_GIVE_DATE ] + CONVERT_TIME_TO_MOSCOW, 
		s_year, 
		s_month, 
		s_day, 
		s_hour, 
		s_minute, 
		s_second
	) ;
	format ( _str, sizeof _str, "%02d.%02d.%d", s_day, s_month, s_year ) ;

   	new Node: node = JSON_Object (
		"serialNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"familyStatus",			JSON_Int ( 0 ), // 0 - холост / не замужем, 1 - женат / за мужем
		"sex",					JSON_Int ( p_info [ playerid ] [ gender ] ),
		"militaryId",			JSON_Int ( GetInventoryFindItem ( playerid, SUB_INVENTORY, ITEM_MILITARY_ID ) ),
		"issueDate",			JSON_String ( _str ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, 12, 0, global_string ) ;
}

stock show_ui_mvd ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_mvd] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;

   	new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, 2220 ), _str [ 32 ], _f_id = p_info [ playerid ] [ member ] ;
   	format ( _str, sizeof _str, "Сотрудник %s", f_info [ _f_id - 1 ] [ f_letter_name ] ) ;
   	new Node: node = JSON_Object (
		"idNumber",				JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_REGION ] ),
		"selfNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"rank",					JSON_String ( f_rank [ _f_id - 1 ] [ p_info [ playerid ] [ rank ] - 1 ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"jobTitle",				JSON_String ( _str ),
		"issueDate",			JSON_String ( p_info [ playerid ] [ fraction_date ] ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, UI_DOCUMENT, 1, global_string ) ;
}

stock show_ui_army ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_army] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;

	new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, ITEM_MILITARY_ID ) ;
   	new Node: node = JSON_Object (
		"serialNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"familyStatus",			JSON_Int ( 0 ), // 0 - холост / не замужем, 1 - женат / за мужем
		"sex",					JSON_Int ( p_info [ playerid ] [ gender ] ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, UI_DOCUMENT, 2, global_string ) ;
}

stock show_ui_med ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_med] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;

	new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, 2221 ), s_year, s_month, s_day, s_hour, s_minute, s_second, _str [ 12 ] ;
	timestamp_to_date (
		USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_GIVE_DATE ] + CONVERT_TIME_TO_MOSCOW, 
		s_year, 
		s_month, 
		s_day, 
		s_hour, 
		s_minute, 
		s_second
	) ;
	format ( _str, sizeof _str, "%02d.%02d.%d", s_day, s_month, s_year ) ;
   
   	new Node: node = JSON_Object (
		"serialNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"date",					JSON_String ( _str ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, UI_DOCUMENT, 3, global_string ) ;
}

stock show_ui_gibdd ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_gibdd] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;
   
	new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, 2222 ) ;
   	new Node: node = JSON_Object (
		"serialNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"rank",					JSON_String ( f_rank [ p_info [ playerid ] [ member ] - 1 ] [ p_info [ playerid ] [ rank ] - 1 ] ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, UI_DOCUMENT, 4, global_string ) ;
}

stock show_ui_fsb ( playerid, targetid = INVALID_PLAYER_ID )
{
	#if defined debug_packet
		printf ( "[show_ui_fsb] playerid: %d", playerid ) ;
	#endif

	if ( targetid == INVALID_PLAYER_ID )
		targetid = playerid ;
   
	new _slot = GetInventoryFindSlot ( playerid, SUB_INVENTORY, 2223 ) ;
   	new Node: node = JSON_Object (
		"serialNumber",			JSON_String ( USERS_INVENTORY [ playerid ] [ _slot ] [ INV_ITEM_PLATE ] ),
		"nickname",				JSON_String ( p_info [ playerid ] [ name ] ),
		"rank",					JSON_String ( f_rank [ p_info [ playerid ] [ member ] - 1 ] [ p_info [ playerid ] [ rank ] - 1 ] ),
		"skinId",				JSON_Int ( getNewSkinModel ( playerid ) )
    ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( targetid, UI_DOCUMENT, 5, global_string ) ;
}