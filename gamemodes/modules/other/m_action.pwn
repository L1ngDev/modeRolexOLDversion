stock actionShow ( playerid, description [ ], duration )
{
	new Node: node = JSON_Object (
		"duration",		JSON_Int ( duration ),
		"description",	JSON_String ( description )
	) ;
	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_ACTION, 0, global_string ) ;
	return true ;
}

stock actionClickShow ( playerid, percent )
{
	global_string [ 0 ] = EOS ;
	format ( global_string, sizeof global_string, "%d", percent ) ;
	onServerSendData ( playerid, UI_ACTION_CLICK, 0, global_string ) ;
	return true ;
}

stock packetActionClickDestroy ( playerid )
{
	if ( action_type { playerid } != 0 )
	{
		checking_action_type ( playerid, action_type { playerid } ) ;
	}
	else
	{
		new vehicleid = INVALID_VEHICLE_ID ;
		if ( IsPlayerInAnyVehicle ( playerid ) )
		{
			vehicleid = GetPlayerVehicleID ( playerid ) ;
		}
		else
		{
			vehicleid = GetPlayerSurfingVehicleID ( playerid ) ;
			if ( vehicleid == INVALID_VEHICLE_ID )
			{
				new Float: x, Float: y, Float: z ;
				GetPlayerPos ( playerid, x, y, z ) ;
				for ( new v = 1; v < MAX_VEHICLES; v++ )
				{
					if ( ! IsVehicleStreamedIn ( v, playerid ) ) continue ;
					new Float: vx, Float: vy, Float: vz ;
					GetVehiclePos ( v, vx, vy, vz ) ;
					if ( GetDistanceBetweenPoints ( x, y, z, vx, vy, vz ) < 10.0 )
					{
						vehicleid = v ;
						break ;
					}
				}
			}
		}

		if ( vehicleid != INVALID_VEHICLE_ID )
		{
			show_game_action_menu ( playerid, 2, vehicleid ) ;
		}
	}
	return true ;
}

stock packetActionDestroy ( playerid )
{
	checking_action_type ( playerid, action_type { playerid } ) ;
	return true ;
}

stock show_game_action_menu ( playerid, selectedType, selectedId )
{
	new fractionId = p_info [ playerid ] [ member ] ;
	new jobId = p_info [ playerid ] [ job ] ;
	new famId = p_info [ playerid ] [ family ] ;
	new inVehicle = IsPlayerInAnyVehicle ( playerid ) ? 1 : 0 ;

	global_string [ 0 ] = EOS ;
	format ( global_string, sizeof global_string, "{\"selectedId\":%d,\"selectedType\":%d,\"inVehicle\":%s,\"fractionId\":%d,\"jobId\":%d,\"family\":%d}",
		selectedId, selectedType, inVehicle ? "true" : "false", fractionId, jobId, famId ) ;

	onServerSendData ( playerid, 76, 1, global_string ) ;
	return true ;
}

CMD:actionmenu ( playerid, params [ ] )
{
	new targetid, type ;
	if ( sscanf ( params, "dd", type, targetid ) )
	{
		new vehicleid = GetPlayerSurfingVehicleID ( playerid ) ;
		if ( vehicleid == INVALID_VEHICLE_ID )
		{
			new Float: x, Float: y, Float: z ;
			GetPlayerPos ( playerid, x, y, z ) ;
			for ( new v = 1; v < MAX_VEHICLES; v++ )
			{
				if ( ! IsVehicleStreamedIn ( v, playerid ) ) continue ;
				new Float: vx, Float: vy, Float: vz ;
				GetVehiclePos ( v, vx, vy, vz ) ;
				if ( GetDistanceBetweenPoints ( x, y, z, vx, vy, vz ) < 5.0 )
				{
					vehicleid = v ;
					break ;
				}
			}
		}
		if ( vehicleid != INVALID_VEHICLE_ID )
		{
			show_game_action_menu ( playerid, 2, vehicleid ) ;
			return 1 ;
		}
		return SendClientMessage ( playerid, col_gray, !"Использование: /actionmenu [тип: 1-игрок, 2-авто] [id]" ) ;
	}
	show_game_action_menu ( playerid, type, targetid ) ;
	return 1 ;
}
