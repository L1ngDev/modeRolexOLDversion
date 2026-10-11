stock SetInventoryCache ( playerid )
{
	#if defined debug_packet
		printf ( "[SetInventoryCache] playerid: %d", playerid ) ;
	#endif

	new Node: node = JSON_Array ( ), itemsLoaded = 0, modelId ;
	for ( new i = 0, Node: invNode ; i < MAX_INVENTORY_SLOTS ; i ++ )
	{
		modelId = GetUsersInventory ( playerid, INV_ITEM, i ) ;
		if ( modelId < 1 )
		{
			invNode = JSON_Array (
				JSON_Object (
					"position",         JSON_Int ( i ),
					"type",         	JSON_Int ( -1 ),
					"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, i ) + 1 ),
					"model",  			JSON_Int ( -1 ),
					"color1",  			JSON_Int ( 1 ),
					"color2",      		JSON_Int ( 1 ),
					"rotX",				JSON_Float ( 20.0 ),
					"rotY",				JSON_Float ( 180.0 ),
					"rotZ",				JSON_Float ( 45.0 ),
					"zoom",				JSON_Float ( 0.78 ),
					"name",				JSON_String ( "" ),
					"count",			JSON_Int ( 0 ),
					"region",			JSON_String ( "" ),
					"plate",			JSON_String ( "" ),
					"plateType",		JSON_Int ( 0 )
				)
			) ;
			node = JSON_Append ( node, invNode ) ;
		}
		else
		{
			if ( modelId == ITEM_SIM_CARD || modelId == 255 )
			{
				new _str [ 64 ] ;
				format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), GetUsersInventory ( playerid, INV_ITEM_GIVE_DATE, i ) ) ;

				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, i ) + 1 ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( _str ),
						"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, i ) ),
						"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, i ) ),
						"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, i ) ),
						"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, i ) )
					)
				) ;
			}
			else
			{
				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, i ) + 1 ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( item_name ( modelId ) ),
						"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, i ) ),
						"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, i ) ),
						"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, i ) ),
						"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, i ) )
					)
				) ;
			}
			node = JSON_Append ( node, invNode ) ;
		}

		if ( ++ itemsLoaded == 5 || i == MAX_INVENTORY_SLOTS - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendCacheData ( playerid, 0, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock SetInventoryCacheItem ( playerid, slotId )
{
	#if defined debug_packet
		printf ( "[SetInventoryCacheItem] playerid: %d", playerid ) ;
	#endif

	new Node: node, modelId = GetUsersInventory ( playerid, INV_ITEM, slotId ) ;
	if ( modelId < 1 )
	{
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( -1 ),
			"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
			"model",  			JSON_Int ( -1 ),
			"color1",  			JSON_Int ( 1 ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( "" ),
			"count",			JSON_Int ( 0 ),
			"region",			JSON_String ( "" ),
			"plate",			JSON_String ( "" ),
			"plateType",		JSON_Int ( 0 )
		) ;
	}
	else
	{
		if ( modelId == ITEM_SIM_CARD || modelId == 255 )
		{
			new _str [ 64 ] ;
			format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), GetUsersInventory ( playerid, INV_ITEM_GIVE_DATE, slotId ) ) ;

			node = JSON_Object (
				"position",         JSON_Int ( slotId ),
				"type",         	JSON_Int ( item_render_type ( modelId ) ),
				"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
				"model",  			JSON_Int ( item_object_id ( modelId ) ),
				"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
				"color2",      		JSON_Int ( 1 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( _str ),
				"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, slotId ) ),
				"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, slotId ) ),
				"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, slotId ) ),
				"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, slotId ) )
			) ;

			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendCacheData ( playerid, 0, global_string ) ;
			return 1 ;
		}
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( item_render_type ( modelId ) ),
			"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
			"model",  			JSON_Int ( item_object_id ( modelId ) ),
			"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( item_name ( modelId ) ),
			"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, slotId ) ),
			"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, slotId ) ),
			"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, slotId ) ),
			"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, slotId ) )
		) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendCacheData ( playerid, 0, global_string ) ;
	return 1 ;
}

stock SetInventoryCacheAcs ( playerid )
{
	#if defined debug_packet
		printf ( "[SetInventoryCacheAcs] playerid: %d", playerid ) ;
	#endif

	new Node:node = JSON_Array ( ), modelId, itemsLoaded = 0 ;
	for ( new i = 0, Node: accNode ; i < MAX_ACCESORIES ; i ++ )
	{
		modelId = GetUserAccessories ( playerid, ACS_MODEL, i ) ;
		if ( modelId < 1 )
		{
			accNode = JSON_Array (
				JSON_Object (
					"position",         JSON_Int ( i ),
					"type",         	JSON_Int ( -1 ),
					"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
					"model",  			JSON_Int ( -1 ),
					"color1",  			JSON_Int ( 1 ),
					"color2",      		JSON_Int ( 1 ),
					"rotX",				JSON_Float ( 20.0 ),
					"rotY",				JSON_Float ( 180.0 ),
					"rotZ",				JSON_Float ( 45.0 ),
					"zoom",				JSON_Float ( 0.78 ),
					"name",				JSON_String ( "" ),
					"count",			JSON_Int ( 0 )
				)
			) ;
			node = JSON_Append ( node, accNode ) ;
		}
		else
		{
			if ( modelId == ITEM_SIM_CARD || modelId == 255 )
			{
				new _str [ 64 ] ;
				format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), GetUserAccessories ( playerid, ACS_COUNT, i ) ) ;

				accNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( _str ),
						"count",			JSON_Int ( 1 )
					)
				) ;
			}
			else
			{
				accNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( item_name ( modelId ) ),
						"count",			JSON_Int ( 1 )
					)
				) ;
			}
			node = JSON_Append ( node, accNode ) ;
		}

		if ( ++ itemsLoaded == 5 || i == MAX_ACCESORIES - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendCacheData ( playerid, 1, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock SetInventoryCacheAcsItem ( playerid, slotId )
{
	#if defined debug_packet
		printf ( "[SetInventoryCacheAcsItem] playerid: %d", playerid ) ;
	#endif

	new Node: node, modelId = GetUserAccessories ( playerid, ACS_MODEL, slotId ) ;
	if ( modelId == 0 )
	{
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( -1 ),
			"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
			"model",  			JSON_Int ( -1 ),
			"color1",  			JSON_Int ( 1 ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( "" ),
			"count",			JSON_Int ( 0 )
		) ;
	}
	else
	{
		if ( modelId == ITEM_SIM_CARD || modelId == 255 )
		{
			new _str [ 64 ] ;
			format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), GetUserAccessories ( playerid, ACS_COUNT, slotId ) ) ;

			node = JSON_Object (
				"position",         JSON_Int ( slotId ),
				"type",         	JSON_Int ( item_render_type ( modelId ) ),
				"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
				"model",  			JSON_Int ( item_object_id ( modelId ) ),
				"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
				"color2",      		JSON_Int ( 1 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( _str ),
				"count",			JSON_Int ( 1 )
			) ;

			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendCacheData ( playerid, 3, global_string ) ;
			return 1 ;
		}
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( item_render_type ( modelId ) ),
			"typeInv",         	JSON_Int ( ( modelId < 1 ) ? 0 : ( ( modelId == ITEM_SIM_CARD || modelId == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
			"model",  			JSON_Int ( item_object_id ( modelId ) ),
			"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( item_name ( modelId ) ),
			"count",			JSON_Int ( 1 )
		) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendCacheData ( playerid, 3, global_string ) ;
	return 1 ;
}
































stock SetInventoryItem ( playerid )
{
	#if defined debug_packet
		printf ( "[SetInventoryItem] playerid: %d", playerid ) ;
	#endif

	new Node: node = JSON_Object (
		"money", JSON_Int ( p_info [ playerid ] [ money ] ),
		"donate", JSON_Int ( p_info [ playerid ] [ donate ] )
	) ;
	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 0, global_string ) ;
}

stock SetInventoryItemID ( playerid, slotId )
{
	#if defined debug_packet
		printf ( "[SetInventoryItemID] playerid: %d", playerid ) ;
	#endif

	new Node: node, _id = GetUsersInventory ( playerid, INV_ITEM, slotId ) ;
	if ( _id < 1 )
	{
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( -1 ),
			"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
			"model",  			JSON_Int ( -1 ),
			"color1",  			JSON_Int ( 1 ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( "" ),
			"count",			JSON_Int ( 0 ),
			"region",			JSON_String ( "" ),
			"plate",			JSON_String ( "" ),
			"plateType",		JSON_Int ( 0 )
		) ;
	}
	else
	{
		if ( _id == ITEM_SIM_CARD || _id == 255 )
		{
			new _str [ 64 ] ;
			format ( _str, sizeof _str, "%s\t%d", item_name ( _id ), GetUsersInventory ( playerid, INV_ITEM_GIVE_DATE, slotId ) ) ;

			node = JSON_Object (
				"position",         JSON_Int ( slotId ),
				"type",         	JSON_Int ( item_render_type ( _id ) ),
				"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
				"model",  			JSON_Int ( item_object_id ( _id ) ),
				"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
				"color2",      		JSON_Int ( 1 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( _str ),
				"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, slotId ) ),
				"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, slotId ) ),
				"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, slotId ) ),
				"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, slotId ) )
			) ;

			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_INVENTORY, 7, global_string ) ;
			return 1 ;
		}
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( item_render_type ( _id ) ),
			"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : GetUsersInventory ( playerid, INV_ITEM_TYPE, slotId ) + 1 ),
			"model",  			JSON_Int ( item_object_id ( _id ) ),
			"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( item_name ( _id ) ),
			"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, slotId ) ),
			"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, slotId ) ),
			"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, slotId ) ),
			"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, slotId ) )
		) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 7, global_string ) ;
	return 1 ;
}

stock SetInventoryAcs ( playerid )
{
	onServerSendData ( playerid, UI_INVENTORY, 1, "" ) ;
}

stock SetInventoryAcsID ( playerid, slotId )
{
	#if defined debug_packet
		printf ( "[SetInventoryAcsID] playerid: %d", playerid ) ;
	#endif

	new Node: node, _id = GetUserAccessories ( playerid, ACS_MODEL, slotId ) ;
	if ( _id == 0 )
	{
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( -1 ),
			"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : ( ( _id == ITEM_SIM_CARD || _id == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
			"model",  			JSON_Int ( -1 ),
			"color1",  			JSON_Int ( 1 ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( "" ),
			"count",			JSON_Int ( 0 )
		) ;
	}
	else
	{
		if ( _id == ITEM_SIM_CARD || _id == 255 )
		{
			new _str [ 64 ] ;
			format ( _str, sizeof _str, "%s\t%d", item_name ( _id ), GetUserAccessories ( playerid, ACS_COUNT, slotId ) ) ;

			node = JSON_Object (
				"position",         JSON_Int ( slotId ),
				"type",         	JSON_Int ( item_render_type ( _id ) ),
				"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : ( ( _id == ITEM_SIM_CARD || _id == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
				"model",  			JSON_Int ( item_object_id ( _id ) ),
				"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
				"color2",      		JSON_Int ( 1 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( _str ),
				"count",			JSON_Int ( 1 )
			) ;

			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_INVENTORY, 4, global_string ) ;
			return 1 ;
		}
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( item_render_type ( _id ) ),
			"typeInv",         	JSON_Int ( ( _id < 1 ) ? 0 : ( ( _id == ITEM_SIM_CARD || _id == 255 ) ? INVENTORY_TYPE_SIMCARD + 1 : INVENTORY_TYPE_ACCESSORIES + 1 ) ),
			"model",  			JSON_Int ( item_object_id ( _id ) ),
			"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( item_name ( _id ) ),
			"count",			JSON_Int ( 1 )
		) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 4, global_string ) ;
	return 1 ;
}

stock setInventoryWarehouse ( playerid, inventoryType, _id )
{
	#if defined debug_packet
		printf ( "[setInventoryWarehouse] playerid: %d", playerid ) ;
	#endif

	new maxItems ;
	if ( inventoryType == SUB_INV_VEHICLE ) maxItems = getTrunkCapacity ( _id ) ;
	else if ( inventoryType == SUB_INV_HOUSE ) maxItems = MAX_WAREHOUSE_SLOT ;
	else if ( inventoryType == SUB_INV_FAMILY ) maxItems = MAX_FAMILY_WAREHOUSE ;
	else if ( inventoryType == SUB_INV_FRACTION ) maxItems = MAX_FRACTION_WAREHOUSE ;
	else if ( inventoryType == SUB_INV_MARKET_PLACE ) maxItems = MAX_MARKET_PLACE_ITEMS ;

	new Node: node = JSON_Array ( ), modelId, modelCount, itemsLoaded = 0, giveDate ;
	for ( new i = 0, Node: invNode ; i < maxItems ; i ++ )
	{
		if ( inventoryType == SUB_INV_VEHICLE )
		{
			modelId = GetVehicleInventory ( _id, INV_ITEM, i ) ;
			modelCount = GetVehicleInventory ( _id, INV_ITEM_COUNT, i ) ;
			giveDate = GetVehicleInventory ( _id, INV_ITEM_GIVE_DATE, i ) ;
		}
		else if ( inventoryType == SUB_INV_HOUSE )
		{
			modelId = GetHouseInventory ( _id, INV_ITEM, i ) ;
			modelCount = GetHouseInventory ( _id, INV_ITEM_COUNT, i ) ;
			giveDate = GetHouseInventory ( _id, INV_ITEM_GIVE_DATE, i ) ;
		}
		else if ( inventoryType == SUB_INV_FAMILY )
		{
			modelId = GetFamilyInventory ( _id, INV_ITEM, i ) ;
			modelCount = GetFamilyInventory ( _id, INV_ITEM_COUNT, i ) ;
			giveDate = GetFamilyInventory ( _id, INV_ITEM_GIVE_DATE, i ) ;
		}
		else if ( inventoryType == SUB_INV_FRACTION )
		{
			modelId = GetFractionInventory ( _id, INV_ITEM, i ) ;
			modelCount = GetFractionInventory ( _id, INV_ITEM_COUNT, i ) ;
			giveDate = GetFractionInventory ( _id, INV_ITEM_GIVE_DATE, i ) ;
		}
		else if ( inventoryType == SUB_INV_MARKET_PLACE )
		{
			modelId = GetMarketPlaceInventory ( playerid, INV_ITEM, i ) ;
			modelCount = GetMarketPlaceInventory ( playerid, INV_ITEM_COUNT, i ) ;
			giveDate = GetMarketPlaceInventory ( playerid, INV_ITEM_GIVE_DATE, i ) ;
		}

		if ( modelId < 1 )
		{
			invNode = JSON_Array (
				JSON_Object (
					"position",         JSON_Int ( i ),
					"type",         	JSON_Int ( -1 ),
					"model",  			JSON_Int ( -1 ),
					"color1",  			JSON_Int ( 1 ),
					"color2",      		JSON_Int ( 1 ),
					"rotX",				JSON_Float ( 20.0 ),
					"rotY",				JSON_Float ( 180.0 ),
					"rotZ",				JSON_Float ( 45.0 ),
					"zoom",				JSON_Float ( 0.78 ),
					"name",				JSON_String ( "" ),
					"count",			JSON_Int ( 0 )
				)
			) ;
			node = JSON_Append ( node, invNode ) ;
		}
		else
		{
			
			if ( modelId == ITEM_SIM_CARD || modelId == 255 )
			{
				new _str [ 64 ] ;
				format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), giveDate ) ;

				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( _str ),
						"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, i ) ),
						"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, i ) ),
						"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, i ) ),
						"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, i ) )
					)
				) ;
			}
			else
			{
				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( i ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( item_name ( modelId ) ),
						"count",			JSON_Int ( modelCount )
					)
				) ;
			}
			node = JSON_Append ( node, invNode ) ;
		}

		if ( ++ itemsLoaded == 5 || i == maxItems - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_INVENTORY, 7, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock SetWarehouseItemID ( playerid, inventoryType, _id, slotId )
{
	#if defined debug_packet
		printf ( "[SetWarehouseItemID] playerid: %d", playerid ) ;
	#endif

	new Node: node, modelId, modelCount, giveDate ;
	if ( inventoryType == SUB_INV_VEHICLE )
	{
		modelId = GetVehicleInventory ( _id, INV_ITEM, slotId ) ;
		modelCount = GetVehicleInventory ( _id, INV_ITEM_COUNT, slotId ) ;
		giveDate = GetVehicleInventory ( _id, INV_ITEM_GIVE_DATE, slotId ) ;
	}
	else if ( inventoryType == SUB_INV_HOUSE )
	{
		modelId = GetHouseInventory ( _id, INV_ITEM, slotId ) ;
		modelCount = GetHouseInventory ( _id, INV_ITEM_COUNT, slotId ) ;
		giveDate = GetHouseInventory ( _id, INV_ITEM_GIVE_DATE, slotId ) ;
	}
	else if ( inventoryType == SUB_INV_FAMILY )
	{
		modelId = GetFamilyInventory ( _id, INV_ITEM, slotId ) ;
		modelCount = GetFamilyInventory ( _id, INV_ITEM_COUNT, slotId ) ;
		giveDate = GetFamilyInventory ( _id, INV_ITEM_GIVE_DATE, slotId ) ;
	}
	else if ( inventoryType == SUB_INV_FRACTION )
	{
		modelId = GetFractionInventory ( _id, INV_ITEM, slotId ) ;
		modelCount = GetFractionInventory ( _id, INV_ITEM_COUNT, slotId ) ;
		giveDate = GetFractionInventory ( _id, INV_ITEM_GIVE_DATE, slotId ) ;
	}
	else if ( inventoryType == SUB_INV_MARKET_PLACE )
	{
		modelId = GetMarketPlaceInventory ( playerid, INV_ITEM, slotId ) ;
		modelCount = GetMarketPlaceInventory ( playerid, INV_ITEM_COUNT, slotId ) ;
		giveDate = GetMarketPlaceInventory ( playerid, INV_ITEM_GIVE_DATE, slotId ) ;
	}

	if ( modelId < 1 )
	{
		node = JSON_Object (
			"position",			JSON_Int ( slotId ),
			"type",         	JSON_Int ( -1 ),
			"model",  			JSON_Int ( -1 ),
			"color1",  			JSON_Int ( 1 ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( "" ),
			"count",			JSON_Int ( 0 )
		) ;
	}
	else
	{
		if ( _id == ITEM_SIM_CARD || _id == 255 )
		{
			new _str [ 64 ] ;
			format ( _str, sizeof _str, "%s\t%d", item_name ( _id ), giveDate ) ;

			node = JSON_Object (
				"position",         JSON_Int ( slotId ),
				"type",         	JSON_Int ( item_render_type ( _id ) ),
				"model",  			JSON_Int ( item_object_id ( _id ) ),
				"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
				"color2",      		JSON_Int ( 1 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( _str ),
				"count",			JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_COUNT, slotId ) ),
				"region",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_REGION, slotId ) ),
				"plate",			JSON_String ( GetUsersInventory ( playerid, INV_ITEM_PLATE, slotId ) ),
				"plateType",		JSON_Int ( GetUsersInventory ( playerid, INV_ITEM_PLATE_TYPE, slotId ) )
			) ;

			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_INVENTORY, 3, global_string ) ;
			return 1 ;
		}
		node = JSON_Object (
			"position",         JSON_Int ( slotId ),
			"type",         	JSON_Int ( item_render_type ( modelId ) ),
			"model",  			JSON_Int ( item_object_id ( modelId ) ),
			"color1",  			JSON_Int ( item_color ( _id, 1 ) ),
			"color2",      		JSON_Int ( 1 ),
			"rotX",				JSON_Float ( 20.0 ),
			"rotY",				JSON_Float ( 180.0 ),
			"rotZ",				JSON_Float ( 45.0 ),
			"zoom",				JSON_Float ( 0.78 ),
			"name",				JSON_String ( item_name ( modelId ) ),
			"count",			JSON_Int ( modelCount )
		) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 8, global_string ) ;
	return 1 ;
}

stock SetGuardsInfo ( playerid )
{
	new Node: node = JSON_Array ( ) ;
	for ( new idx = 0 ; idx < MAX_GUARDS ; idx ++ )
	{
		new Node: json = JSON_Array ( ) ;
		JSON_Parse ( SetGuardsInv ( playerid, idx ), json ) ;

		node = JSON_Array (
			JSON_Object (
				"id",			JSON_Int ( 0 ),
				"guardName",	JSON_String ( GetGuardInfo ( playerid, GUARD_NAME, idx ) ),
				"level",		JSON_Int ( GetGuardInfo ( playerid, GUARD_LEVEL, idx ) ),
				"skinId",		JSON_Int ( GetGuardInfo ( playerid, GUARD_SKIN, idx ) ),
				"color1",  		JSON_Int ( 1 ),
				"color2",      	JSON_Int ( 1 ),
				"rotX",			JSON_Float ( 20.0 ),
				"rotY",			JSON_Float ( 180.0 ),
				"rotZ",			JSON_Float ( 45.0 ),
				"zoom",			JSON_Float ( 0.78 ),
				"guardItems",	json
			)
		) ;

		global_string [ 0 ] = EOS ;
		JSON_Stringify ( node, global_string, sizeof global_string ) ;
		onServerSendData ( playerid, UI_INVENTORY, 18, global_string ) ;
	}
	return true ;
}

stock SetGuardsInv ( playerid, guardNum )
{
	new Node: node = JSON_Array ( ), modelId ;
	for ( new idx = 0, Node: invNode ; idx < MAX_GUARDS_SLOT ; idx ++ )
	{
		modelId = GetGuardInventory ( playerid, guardNum, INV_ITEM, idx ) ;
		if ( modelId < 1 )
		{
			invNode = JSON_Array (
				JSON_Object (
					"position",         JSON_Int ( idx ),
					"type",         	JSON_Int ( -1 ),
					"model",  			JSON_Int ( -1 ),
					"color1",  			JSON_Int ( 1 ),
					"color2",      		JSON_Int ( 1 ),
					"rotX",				JSON_Float ( 20.0 ),
					"rotY",				JSON_Float ( 180.0 ),
					"rotZ",				JSON_Float ( 45.0 ),
					"zoom",				JSON_Float ( 0.78 ),
					"name",				JSON_String ( "" ),
					"count",			JSON_Int ( 0 )
				)
			) ;
		}
		else
		{
			if ( modelId == ITEM_SIM_CARD || modelId == 255 )
			{
				new _str [ 64 ] ;
				format ( _str, sizeof _str, "%s\t%d", item_name ( modelId ), GetGuardInventory ( playerid, guardNum, INV_ITEM_GIVE_DATE, idx ) ) ;

				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( idx ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( _str ),
						"count",			JSON_Int ( GetGuardInventory ( playerid, guardNum, INV_ITEM_COUNT, idx ) ),
						"region",			JSON_String ( GetGuardInventory ( playerid, guardNum, INV_ITEM_REGION, idx ) ),
						"plate",			JSON_String ( GetGuardInventory ( playerid, guardNum, INV_ITEM_PLATE, idx ) ),
						"plateType",		JSON_Int ( GetGuardInventory ( playerid, guardNum, INV_ITEM_PLATE_TYPE, idx ) )
					)
				) ;
			}
			else
			{
				invNode = JSON_Array (
					JSON_Object (
						"position",         JSON_Int ( idx ),
						"type",         	JSON_Int ( item_render_type ( modelId ) ),
						"model",  			JSON_Int ( item_object_id ( modelId ) ),
						"color1",  			JSON_Int ( item_color ( modelId, 1 ) ),
						"color2",      		JSON_Int ( 1 ),
						"rotX",				JSON_Float ( 20.0 ),
						"rotY",				JSON_Float ( 180.0 ),
						"rotZ",				JSON_Float ( 45.0 ),
						"zoom",				JSON_Float ( 0.78 ),
						"name",				JSON_String ( item_name ( modelId ) ),
						"count",			JSON_Int ( GetGuardInventory ( playerid, guardNum, INV_ITEM_COUNT, idx ) )
					)
				) ;
			}
		}
		node = JSON_Append ( node, invNode ) ;
	}
	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	return global_string ;
}

stock setCharacterInfo ( playerid )
{
	#if defined debug_packet
		printf ( "[setCharacterInfo] playerid: %d", playerid ) ;
	#endif

	new Node: node = JSON_Object (
		"satiety", JSON_Int ( p_info [ playerid ] [ hunger ] ),
		"playerId", JSON_Int ( playerid ),
		"playerName", JSON_String ( p_info [ playerid ] [ name ] ),
		"level", JSON_Int ( p_info [ playerid ] [ level ] ),
		"exp", JSON_Int ( p_info [ playerid ] [ exp ] ),
		"expMax", JSON_Int ( ( p_info [ playerid ] [ level ] + 1 ) * 4 ),
		"premiumType", JSON_Int ( p_info [ playerid ] [ vip ] ),
		"premiumDate", JSON_Int ( p_info [ playerid ] [ vip_day ] ),
		"skinId", JSON_Int ( getNewSkinModel ( playerid ) ),
		"color1", JSON_Int ( 1 ),
		"color2", JSON_Int ( 1 ),
		"rotX", JSON_Float ( 20.0 ),
		"rotY", JSON_Float ( 180.0 ),
		"rotZ", JSON_Float ( 45.0 ),
		"isInv", JSON_Bool ( true ),
		"zoom", JSON_Float ( 0.78 )
	) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 1, global_string ) ;

	SendPlayerStatistic ( playerid ) ;
}

stock setInventoryLayout ( playerid, idx )
{
	#if defined debug_packet
		printf ( "[setInventoryLayout] playerid: %d, idx: %d", playerid, idx ) ;
	#endif
	return 1 ;
}

stock setWarehouseInfo ( playerid, _str [ ], _str2 [ ], _str3 [ ], _str4 [ ], _str5 [ ], _str6 [ ] )
{
	#if defined debug_packet
		printf ( "[setWarehouseInfo] playerid: %d", playerid ) ;
	#endif

	new Node: node = JSON_Object (
		"header", JSON_String ( _str ),
		"desc", JSON_String ( _str2 ),
		"name", JSON_String ( _str3 ),
		"subName", JSON_String ( _str4 ),
		"nameName", JSON_String ( _str5 ),
		"nameSubName", JSON_String ( _str6 )
	) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 6, global_string ) ;
}

stock SendPlayerStatistic ( playerid )
{
	new driveStr [ 16 ], gunStr [ 16 ], boatStr [ 16 ], flyStr [ 16 ], expStr [ 32 ], levelStr [ 16 ], hourStr [ 16 ], warnStr [ 16 ], lawStr [ 16 ] ;
	
	format ( expStr, sizeof expStr, "%d / %d", p_info [ playerid ] [ exp ], ( p_info [ playerid ] [ level ] + 1 ) * 4 ) ;
	format ( levelStr, sizeof levelStr, "%d", p_info [ playerid ] [ level ] ) ;
	format ( hourStr, sizeof hourStr, "%d", p_info [ playerid ] [ hour_played ] ) ;
	format ( warnStr, sizeof warnStr, "%d / 3", p_info [ playerid ] [ p_warn ] ) ;
	format ( lawStr, sizeof lawStr, "%d", p_info [ playerid ] [ law_obedience ] ) ;
	
	format ( driveStr, sizeof driveStr, "%s", ( p_info [ playerid ] [ drive_lic ] == 1 || p_info [ playerid ] [ drive_lic ] == 2 ) ? "Есть" : "Нет" ) ;
	format ( gunStr, sizeof gunStr, "%s", ( p_info [ playerid ] [ gun_lic ] == 1 || p_info [ playerid ] [ gun_lic ] == 2 ) ? "Есть" : "Нет" ) ;
	format ( boatStr, sizeof boatStr, "%s", ( p_info [ playerid ] [ boat_lic ] == 1 || p_info [ playerid ] [ boat_lic ] == 2 ) ? "Есть" : "Нет" ) ;
	format ( flyStr, sizeof flyStr, "%s", ( p_info [ playerid ] [ fly_lic ] == 1 || p_info [ playerid ] [ fly_lic ] == 2 ) ? "Есть" : "Нет" ) ;

	new Node: categories = JSON_Array ( ) ;

	new Node: mainStats = JSON_Array ( ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 0 ), "name", JSON_String ( "Имя" ), "value", JSON_String ( p_info [ playerid ] [ name ] ) ) ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 1 ), "name", JSON_String ( "Уровень" ), "value", JSON_String ( levelStr ) ) ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 2 ), "name", JSON_String ( "EXP" ), "value", JSON_String ( expStr ) ) ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 3 ), "name", JSON_String ( "Наиграно часов" ), "value", JSON_String ( hourStr ) ) ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 5 ), "name", JSON_String ( "Предупреждений" ), "value", JSON_String ( warnStr ) ) ) ;
	mainStats = JSON_Append ( mainStats, JSON_Object ( "icon", JSON_Int ( 6 ), "name", JSON_String ( "Законопослушность" ), "value", JSON_String ( lawStr ) ) ) ;

	new Node: catMain = JSON_Object (
		"name", JSON_String ( "Основное" ),
		"stats", mainStats
	) ;
	categories = JSON_Append ( categories, catMain ) ;

	new Node: licStats = JSON_Array ( ) ;
	licStats = JSON_Append ( licStats, JSON_Object ( "icon", JSON_Int ( 0 ), "name", JSON_String ( "Вождение" ), "value", JSON_String ( driveStr ) ) ) ;
	licStats = JSON_Append ( licStats, JSON_Object ( "icon", JSON_Int ( 1 ), "name", JSON_String ( "Оружие" ), "value", JSON_String ( gunStr ) ) ) ;
	licStats = JSON_Append ( licStats, JSON_Object ( "icon", JSON_Int ( 2 ), "name", JSON_String ( "Водный транспорт" ), "value", JSON_String ( boatStr ) ) ) ;
	licStats = JSON_Append ( licStats, JSON_Object ( "icon", JSON_Int ( 3 ), "name", JSON_String ( "Воздушный транспорт" ), "value", JSON_String ( flyStr ) ) ) ;

	new Node: catLic = JSON_Object (
		"name", JSON_String ( "Лицензии" ),
		"stats", licStats
	) ;
	categories = JSON_Append ( categories, catLic ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( categories, global_string, sizeof global_string ) ;
	onServerSendCacheData ( playerid, 2, global_string ) ;
}

stock SendFightStyleInfo ( playerid )
{
	new Node: list = JSON_Array ( ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 0 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 2 ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 1 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 1 ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 2 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 1 ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 3 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 1 ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 4 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 1 ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "style", JSON_Int ( 5 ), "price", JSON_Int ( 0 ), "status", JSON_Int ( 1 ) ) ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( list, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 4, global_string ) ;
}

stock SendWeaponSkillInfo ( playerid )
{
	new Node: list = JSON_Array ( ) ;
	// 0: Silenced Pistol (weaponId = 1)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 1 ), "id", JSON_Int ( 1 ), "weapon", JSON_Int ( 1 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 0 ] ), "price", JSON_Int ( 100 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 1: Deagle (weaponId = 2)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 2 ), "id", JSON_Int ( 2 ), "weapon", JSON_Int ( 2 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 1 ] ), "price", JSON_Int ( 150 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 2: Shotgun (weaponId = 3)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 3 ), "id", JSON_Int ( 3 ), "weapon", JSON_Int ( 3 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 2 ] ), "price", JSON_Int ( 120 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 3: MP5 (weaponId = 7)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 7 ), "id", JSON_Int ( 7 ), "weapon", JSON_Int ( 7 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 3 ] ), "price", JSON_Int ( 200 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 4: AK-47 (weaponId = 8)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 8 ), "id", JSON_Int ( 8 ), "weapon", JSON_Int ( 8 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 4 ] ), "price", JSON_Int ( 250 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 5: M4A1 (weaponId = 9)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 9 ), "id", JSON_Int ( 9 ), "weapon", JSON_Int ( 9 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 5 ] ), "price", JSON_Int ( 250 ), "isOnApprove", JSON_Bool ( false ) ) ) ;
	// 6: Rifle (weaponId = 10)
	list = JSON_Append ( list, JSON_Object ( "weaponId", JSON_Int ( 10 ), "id", JSON_Int ( 10 ), "weapon", JSON_Int ( 10 ), "progress", JSON_Int ( p_info [ playerid ] [ gun_skills ] [ 6 ] ), "price", JSON_Int ( 300 ), "isOnApprove", JSON_Bool ( false ) ) ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( list, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 6, global_string ) ;
}

stock SendUpgradeInfo ( playerid )
{
	new Node: list = JSON_Array ( ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 0 ), "price", JSON_Int ( 50 ), "isActive", JSON_Bool ( false ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 1 ), "price", JSON_Int ( 50 ), "isActive", JSON_Bool ( false ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 2 ), "price", JSON_Int ( 100 ), "isActive", JSON_Bool ( false ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 3 ), "price", JSON_Int ( 150 ), "isActive", JSON_Bool ( false ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 4 ), "price", JSON_Int ( 200 ), "isActive", JSON_Bool ( false ) ) ) ;
	list = JSON_Append ( list, JSON_Object ( "skill", JSON_Int ( 5 ), "price", JSON_Int ( 250 ), "isActive", JSON_Bool ( false ) ) ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( list, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_INVENTORY, 5, global_string ) ;
}
