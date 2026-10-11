#define PACKET_CUSTOMRPC    			251
#define RPC_DONATE						0x90

stock setUpdateBalance ( playerid, _balance )
{
	// setUpdateBalance
	#if defined debug_packet
		printf ( "[setUpdateBalance] playerid: %d", playerid ) ;
	#endif

	global_string [ 0 ] = EOS ;
	format ( global_string, 100, "%d", _balance ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 0, global_string ) ;

	new Node: node = JSON_Array ( ), Node: nodeInsert ;

	global_string [ 0 ] = EOS ;
	format ( global_string, 100, "%s {"#cGRDialog"}(Основной)", GetPlayerCashValueToSmile ( p_info [ playerid ] [ donate ] ) ) ;
	nodeInsert = JSON_Array (
		JSON_Object (
			"name",			JSON_String ( global_string )
		)
	) ;
	node = JSON_Append ( node, nodeInsert ) ;

	global_string [ 0 ] = EOS ;
	format ( global_string, 100, "%s {"#cGRDialog"}(Бонусный)", GetPlayerCashValueToSmile ( p_info [ playerid ] [ donate_bonus ] ) ) ;
	nodeInsert = JSON_Array (
		JSON_Object (
			"name",			JSON_String ( global_string )
		)
	) ;
	node = JSON_Append ( node, nodeInsert ) ;

	global_string [ 0 ] = EOS ;
	format ( global_string, 100, "%s {"#cGRDialog"}("family_title")", GetPlayerCashValueToSmile ( GetInventoryFindItem ( playerid, SUB_INVENTORY, ITEM_FAMILY_TALON ) ) ) ;
	nodeInsert = JSON_Array (
		JSON_Object (
			"name",			JSON_String ( global_string )
		)
	) ;
	node = JSON_Append ( node, nodeInsert ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 12, global_string ) ;
}

stock setExchangeRate ( playerid )
{
	#if defined debug_packet
		printf ( "[setExchangeRate] playerid: %d", playerid ) ;
	#endif

	global_string [ 0 ] = EOS ;
	new Node: node = JSON_Object (
		"rate",					JSON_Int ( convertion_price ),
		"currency",				JSON_Int ( 1 ),
		"rateFamily",			JSON_Int ( 1 ),
		"currencyFamily",		JSON_Int ( convertion_fam_price )
	) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 1, global_string ) ;
}

stock setAddSkins ( playerid )
{
	new Node: node = JSON_Array ( ), itemsLoaded = 0, _model, donate_skins_item = sizeof donate_skins, _str [ 32 ] ;
	for ( new i = 0, Node: donateNode ; i < donate_skins_item ; i ++ )
	{
		format ( _str, sizeof _str , "%d "donate_title_abb"", donate_skins [ i ] [ Cost ] ) ;
		_model = donate_skins [ i ] [ ModelId ] ;
		donateNode = JSON_Array (
			JSON_Object (
				"position",         JSON_Int ( i ),
				"type",         	JSON_Int ( item_render_type ( _model ) ),
				"model",  			JSON_Int ( item_object_id ( _model ) ),
				"color1",  			JSON_Int ( item_color ( _model, 0 ) ),
				"color2",      		JSON_Int ( 0 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( item_name ( _model ) ),
				"price",			JSON_String ( _str )
			)
		) ;
		node = JSON_Append ( node, donateNode ) ;

		if ( ++ itemsLoaded == 5 || i == donate_skins_item - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 2, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock setAddCars ( playerid )
{
	new Node: node = JSON_Array ( ), itemsLoaded = 0, donate_vehicles_items = sizeof donate_vehicles, _model, _str [ 32 ] ;
	for ( new i = 0, Node: donateNode ; i < donate_vehicles_items ; i ++ )
	{
		_model = donate_vehicles [ i ] [ ModelId ] ;
		format ( _str, sizeof _str , "%d "donate_title_abb"", donate_vehicles [ i ] [ Cost ] ) ;
		donateNode = JSON_Array (
			JSON_Object (
				"position",         JSON_Int ( i ),
				"type",         	JSON_Int ( item_render_type ( _model ) ),
				"model",  			JSON_Int ( item_object_id ( _model ) ),
				"color1",  			JSON_Int ( item_color ( _model, 0 ) ),
				"color2",      		JSON_Int ( 0 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( item_name ( _model ) ),
				"price",			JSON_String ( _str ),
				"speed",			JSON_Int ( max_veh_speed ( _model ) ),
				"tankCapacity",		JSON_Int ( 100 )
			)
		) ;
		node = JSON_Append ( node, donateNode ) ;

		if ( ++ itemsLoaded == 5 || i == donate_vehicles_items - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 3, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock setAddActions ( playerid )
{
	new _count = 0 ;
	for ( new i = 0, Node: donateNode ; i < MAX_DISCOUNT ; i ++ )
	{
		if ( donate_discount_id [ i ] == -1 ) continue ;

		_count ++ ;
	}

	new Node: node = JSON_Array ( ), itemsLoaded = 0, _model, _str [ 32 ], _str2 [ 32 ], _str3 [ 32 ],
		_id, _n_price, _hierarchy, _def_price ;
	for ( new i = 0, Node: donateNode ; i < MAX_DISCOUNT ; i ++ )
	{
		if ( donate_discount_id [ i ] == -1 ) continue ;

		_hierarchy = donate_discount_hierarchy [ i ] ;
		_id = find_donate ( _hierarchy, donate_discount_id [ i ] ) ;
		_model = donate_discount_model [ i ] ;
		
		if ( donate_discount_hierarchy [ i ] == 1 )
		{
			_def_price = _n_price = donate_skins [ _id ] [ Cost ] ;
			format ( _str3, sizeof _str3, "%s", item_name ( _model ) ) ;
		}
		else if ( donate_discount_hierarchy [ i ] == 2 )
		{
			_def_price = _n_price = donate_vehicles [ _id ] [ Cost ] ;
			format ( _str3, sizeof _str3, "%s", item_name ( _model ) ) ;
		}
		else if ( donate_discount_hierarchy [ i ] == 3 )
		{
			_def_price = _n_price = donate_acs [ _id ] [ Cost ] ;
			format ( _str3, sizeof _str3, "%s", item_name ( _model ) ) ;
		}
		else 
		{
			_def_price = _n_price = donate_services [ _id ] [ Cost ] ;
			format ( _str3, sizeof _str3, "%s", donate_services [ _id ] [ d_Name ] ) ;
		}

		_n_price = _def_price - ( floatround ( _def_price * donate_discount_percent [ i ] ) / 100 ) ;
		format ( _str, sizeof _str , "%d "donate_title_abb"", _n_price ) ;
		format ( _str2, sizeof _str2 , "%d "donate_title_abb"", _def_price ) ;
		donateNode = JSON_Array (
			JSON_Object (
				"id",         			JSON_Int ( i ),
				"name",					JSON_String ( _str3 ),
				"price",				JSON_String ( _str ),
				"beforeDiscountPrice",	JSON_String ( _str2 ),
				"discount",				JSON_Int ( donate_discount_percent [ i ] ),
				"type",         		JSON_Int ( item_render_type ( _model ) ),
				"model",  				JSON_Int ( item_object_id ( _model ) ),
				"color1",  				JSON_Int ( item_color ( _model, 0 ) ),
				"color2",      			JSON_Int ( 0 ),
				"rotX",					JSON_Float ( 20.0 ),
				"rotY",					JSON_Float ( 180.0 ),
				"rotZ",					JSON_Float ( 45.0 ),
				"zoom",					JSON_Float ( 0.78 )
			)
		) ;
		node = JSON_Append ( node, donateNode ) ;

		if ( ++ itemsLoaded == 5 || i == _count - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 7, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock setAddServices ( playerid )
{
	new Node: node = JSON_Array ( ), _str [ 32 ], _count = sizeof donate_services, itemsLoaded = 0 ;
    for ( new i = 0, Node: serviceNode ; i < _count ; i ++ )
    {
		if ( donate_services [ i ] [ ItemBG ] ) format ( _str, sizeof _str, "%d "donate_title_abb" | Основной", donate_services [ i ] [ Cost ] ) ;
        else format ( _str, sizeof _str, "%d "donate_title_abb" | Бонусный", donate_services [ i ] [ Cost ] ) ;
		serviceNode = JSON_Array (
            JSON_Object (
                "title",                JSON_String ( donate_services [ i ] [ d_Name ] ),
                "description",          JSON_String ( donate_services [ i ] [ Subname ] ),
                "price",          		JSON_String ( _str ),
                "isPriceFrom",  		JSON_Int ( donate_services [ i ] [ ItemBG ] ),
                "needDialog",           JSON_Int ( 0 )
            )
        ) ;
        node = JSON_Append ( node, serviceNode ) ;

		if ( ++ itemsLoaded == 5 || i == _count - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 5, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
    }
}

stock showDonateVip ( playerid )
{
    new Node: node = JSON_Array ( ), _str [ 12 ], _str2 [ 12 ] ;
    for ( new i = 0, Node: vipNode, Float: discountValue ; i < sizeof donateVip ; i ++ )
    {
        if ( donateVip [ i ] [ VIP_PRICE ] != donateVip [ i ] [ VIP_FULL_PRICE ] ) {
            discountValue = float ( ( donateVip [ i ] [ VIP_FULL_PRICE ] - donateVip [ i ] [ VIP_PRICE ] ) ) / float ( donateVip [ i ] [ VIP_FULL_PRICE ] ) * 100.0 ;
        }

		format ( _str, sizeof _str, "%d "donate_title_abb"", donateVip [ i ] [ VIP_PRICE ] ) ;
		format ( _str2, sizeof _str2, "%d "donate_title_abb"", donateVip [ i ] [ VIP_FULL_PRICE ] ) ;
        vipNode = JSON_Array (
            JSON_Object (
                "type",                 JSON_String ( donateVip [ i ] [ VIP_TYPE ] ),
                "price",                JSON_String ( _str ),
                "priceBeforeDiscount",  JSON_String ( _str2 ),
                "discount",             JSON_Int ( floatround ( discountValue ) ),
                "offers",               JSON_String ( donateVip [ i ] [ VIP_OFFERS ] )
            )
        ) ;
        node = JSON_Append ( node, vipNode ) ;
    }

	global_string [ 0 ] = EOS ;
    JSON_Stringify ( node, global_string, sizeof global_string ) ;
    onServerSendData ( playerid, UI_DONATE_MENU, 4, global_string ) ;
}

stock setAddCases ( playerid )
{
	new Node: node = JSON_Array ( ), _case_count = 0 ;
	for ( new i = 0, Node: caseNode ; i < sizeof donate_cases ; i ++ )
	{
		_case_count = users_donate_cases [ playerid ] [ donate_cases [ i ] [ ItemBG ] ] ;

		caseNode = JSON_Array (
			JSON_Object (
				"id",         		JSON_Int ( donate_cases [ i ] [ ItemBG ] ),
				"caseId",         	JSON_Int ( donate_cases [ i ] [ ModelId ] ),
				"title",         	JSON_String ( donate_cases [ i ] [ d_Name ] ),
				"price",  			JSON_Int ( donate_cases [ i ] [ Cost ] ),
				"count",  			JSON_Int ( _case_count ),
				"isOpened",      	JSON_Bool ( true )
			)
		) ;
		node = JSON_Append ( node, caseNode ) ;
	}

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 8, global_string ) ;
}

stock setCasesItems ( playerid, _type )
{
	new Node: node = JSON_Array ( ), itemsLoaded = 0, donate_cases_items, _model, _rare, _renderType ;
	switch ( _type )
	{
		case 0: donate_cases_items = sizeof donate_free_case ;
		case 1: donate_cases_items = sizeof donate_bmw_case ;
		case 2: donate_cases_items = sizeof donate_mercedes_case ;
		case 3: donate_cases_items = sizeof donate_major_case ;
		case 4: donate_cases_items = sizeof donate_lambo_case ;
		case 5: donate_cases_items = sizeof bezumie_haosa_case ;
		case 6: donate_cases_items = sizeof legends_sand_case ;
	}
	for ( new i = 0, Node: donateNode ; i < donate_cases_items ; i ++ )
	{
		switch ( _type )
		{
			case 0:
			{
				_model = donate_free_case [ i ] [ bp_model ] ;
				_rare = donate_free_case [ i ] [ bp_rare ] ;
				_renderType = donate_free_case [ i ] [ bp_render ] ;
			}
			case 1:
			{
				_model = donate_bmw_case [ i ] [ bp_model ] ;
				_rare = donate_bmw_case [ i ] [ bp_rare ] ;
				_renderType = donate_bmw_case [ i ] [ bp_render ] ;
			}
			case 2:
			{
				_model = donate_mercedes_case [ i ] [ bp_model ] ;
				_rare = donate_mercedes_case [ i ] [ bp_rare ] ;
				_renderType = donate_mercedes_case [ i ] [ bp_render ] ;
			}
			case 3:
			{
				_model = donate_major_case [ i ] [ bp_model ] ;
				_rare = donate_major_case [ i ] [ bp_rare ] ;
				_renderType = donate_major_case [ i ] [ bp_render ] ;
			}
			case 4:
			{
				_model = donate_lambo_case [ i ] [ bp_model ] ;
				_rare = donate_lambo_case [ i ] [ bp_rare ] ;
				_renderType = donate_lambo_case [ i ] [ bp_render ] ;
			}
			case 5:
			{
				_model = bezumie_haosa_case [ i ] [ bp_model ] ;
				_rare = bezumie_haosa_case [ i ] [ bp_rare ] ;
				_renderType = bezumie_haosa_case [ i ] [ bp_render ] ;
			}
			case 6:
			{
				_model = legends_sand_case [ i ] [ bp_model ] ;
				_rare = legends_sand_case [ i ] [ bp_rare ] ;
				_renderType = legends_sand_case [ i ] [ bp_render ] ;
			}
		}
		
		donateNode = JSON_Array (
			JSON_Object (
				"position",         JSON_Int ( i ),
				"type",         	JSON_Int ( _renderType ),
				"model",  			JSON_Int ( item_object_id ( _model ) ),
				"color1",  			JSON_Int ( item_color ( _model, 0 ) ),
				"color2",      		JSON_Int ( 0 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( item_name ( _model ) ),
				"rare",				JSON_Int ( _rare )
			)
		) ;
		node = JSON_Append ( node, donateNode ) ;

		if ( ++ itemsLoaded == 5 || i == donate_cases_items - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 9, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}

stock setCasesResult ( playerid, _multiply )
{
	new Node: node = JSON_Array ( ), itemIdx, modelPrice,
		caseId = get_player_use_listitem ( playerid ), _model, query_string [ 128 ] ;
	for ( new i = 0, Node: itemNode ; i < _multiply ; i ++ )
	{
		switch ( caseId )
		{
			case 0:
			{
				itemIdx = GetCaseRandomRarity ( 0 ) ;
				_model = donate_free_case [ itemIdx ] [ bp_model ] ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(FREE ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 1:
			{
				itemIdx = GetCaseRandomRarity ( 1 ) ;
				_model = donate_bmw_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( donate_bmw_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( donate_bmw_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(BMW ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 2:
			{
				itemIdx = GetCaseRandomRarity ( 2 ) ;
				_model = donate_mercedes_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( donate_mercedes_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( donate_mercedes_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(MERCEDES ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 3:
			{
				itemIdx = GetCaseRandomRarity ( 3 ) ;
				_model = donate_major_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( donate_major_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( donate_major_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(MAJOR ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 4:
			{
				itemIdx = GetCaseRandomRarity ( 4 ) ;
				_model = donate_lambo_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( donate_lambo_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( donate_lambo_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(LAMBO ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 5:
			{
				itemIdx = GetCaseRandomRarity ( 5 ) ;
				_model = bezumie_haosa_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( bezumie_haosa_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( bezumie_haosa_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(CHAOS ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
			case 6:
			{
				itemIdx = GetCaseRandomRarity ( 6 ) ;
				_model = legends_sand_case [ itemIdx ] [ bp_model ] ;

				modelPrice = getDonateModelPrice ( legends_sand_case [ itemIdx ] [ bp_render ], _model ) ;
				if ( ! modelPrice ) modelPrice = floatround ( legends_sand_case [ itemIdx ] [ bp_donate_price ] / 10 ) ;
				playerDonateSellItem [ playerid ] += modelPrice ;

				query_string [ 0 ] = EOS ;
				format ( query_string, sizeof query_string, "(SAND ROULETTE) %s открыл рулетку и получил %s",
				p_info [ playerid ] [ name ], item_name ( _model ) ) ;
				WriteLog ( playerid, TYPE_LOG_CASE, query_string ) ;
			}
		}

		playerMultiplyItem [ playerid ] [ i ] = _model ;

		itemNode = JSON_Array (
            JSON_Int ( itemIdx )
        ) ;
        node = JSON_Append ( node, itemNode ) ;
	}

	global_string [ 0 ] = EOS ;
	format ( global_string, 24, "%d "donate_title_abb"", playerDonateSellItem [ playerid ] ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 18, global_string ) ;

	global_string [ 0 ] = EOS ;
	JSON_Stringify ( node, global_string, sizeof global_string ) ;
	onServerSendData ( playerid, UI_DONATE_MENU, 10, global_string ) ;
}

stock setAddAcs ( playerid )
{
	new Node: node = JSON_Array ( ), itemsLoaded = 0, _model, donate_acs_item = sizeof donate_acs, _str [ 32 ] ;
	for ( new i = 0, Node: donateNode ; i < donate_acs_item ; i ++ )
	{
		format ( _str, sizeof _str , "%d "donate_title_abb"", donate_acs [ i ] [ Cost ] ) ;
		_model = donate_acs [ i ] [ ModelId ] ;
		donateNode = JSON_Array (
			JSON_Object (
				"position",         JSON_Int ( i ),
				"type",         	JSON_Int ( item_render_type ( _model ) ),
				"model",  			JSON_Int ( item_object_id ( _model ) ),
				"color1",  			JSON_Int ( item_color ( _model, 0 ) ),
				"color2",      		JSON_Int ( 0 ),
				"rotX",				JSON_Float ( 20.0 ),
				"rotY",				JSON_Float ( 180.0 ),
				"rotZ",				JSON_Float ( 45.0 ),
				"zoom",				JSON_Float ( 0.78 ),
				"name",				JSON_String ( item_name ( _model ) ),
				"price",			JSON_String ( _str )
			)
		) ;
		node = JSON_Append ( node, donateNode ) ;

		if ( ++ itemsLoaded == 5 || i == donate_acs_item - 1 )
		{
			global_string [ 0 ] = EOS ;
			JSON_Stringify ( node, global_string, sizeof global_string ) ;
			onServerSendData ( playerid, UI_DONATE_MENU, 11, global_string ) ;

			node = JSON_Array ( ) ;
			itemsLoaded = 0 ;
		}
	}
}
