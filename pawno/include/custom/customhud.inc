#define PACKET_CUSTOMRPC    			251
#define RPC_TIMEOUT_CHAT 				0x20
#define CUSTOM_RPC_TOGGLE_HUD_ELEMENT	0x22
#define RPC_CUSTOM_AIM 					0x23
#define RPC_CHECK_HUD					0x26

#define RPC_LABEL_CUSTOM 				0x101

#define RPC_FINGER_PRINT				0x140

#define RPC_CHECK_ANDROID				0x160

#define RPC_MOBILE_CLIENT				0x280

#define HUD_ELEMENT_CHAT    			0
#define HUD_ELEMENT_MAP     			1
#define HUD_ELEMENT_TAGS    			2
#define HUD_ELEMENT_WIDGETS 			3
#define HUD_ELEMENT_HUD     			4
#define HUD_ELEMENT_VOICE				5
#define HUD_ELEMENT_TEXTLABELS			6
#define HUD_ELEMENT_BUTTONS				7
#define HUD_ELEMENT_KILL_LIST			8

#define HUD_MAX							9

stock TogglePlayerHudElement ( playerid, hud_element, bool: status_element )
{
	#if defined debug_packet
		printf ( "[TogglePlayerHudElement] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(
		bitstream, 
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, CUSTOM_RPC_TOGGLE_HUD_ELEMENT,
	
		PR_UINT8, hud_element,
		PR_BOOL, status_element);
	
	PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock SendChangeAim ( playerid, texture_name [ ] )
{
	#if defined debug_packet
		printf ( "[SendChangeAim] playerid: %d", playerid ) ;
	#endif
	new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_CUSTOM_AIM);
	
    BS_WriteValue(bitstream, PR_UINT8, strlen ( texture_name ));
    BS_WriteValue(bitstream, PR_STRING, texture_name);

    PR_SendPacket(bitstream, playerid);

    BS_Delete(bitstream);
}

stock SendCheckHud ( playerid )
{
	#if defined debug_packet
		printf ( "[SendCheckHud] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_CHECK_HUD);
    
	BS_WriteValue(bitstream, PR_UINT8, p_info [ playerid ] [ hunger ]);
    
	BS_WriteValue(bitstream, PR_UINT32, server_bonus [ 1 ]);
	
	BS_WriteValue(bitstream, PR_UINT32, 0); // kol-vo valentinok (эвент удалён)
	BS_WriteValue(bitstream, PR_BOOL, false); // otobrazhenie menu valention (эвент удалён)
	
	new bool: _b_gz = false ;
	if ( used_area [ playerid ] != -1 && area_info [ used_area [ playerid ] ] [ a_type ] == area_type_antidm ) _b_gz = true ;
	BS_WriteValue(bitstream, PR_BOOL, _b_gz); // green zone
	
	// e2y information (эвент удалён)
	BS_WriteValue(bitstream, PR_BOOL, false);
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

stock setLabelCustom ( playerid, _labelId, bool: _showBg, bool: _showIcon, _str [ ], _str2 [ ] )
{
	#if defined debug_packet
		printf ( "[setLabelCustom] playerid: %d", playerid ) ;
	#endif
	
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_LABEL_CUSTOM);
    
	BS_WriteValue(bitstream, PR_UINT16, _labelId );
	
	BS_WriteValue(bitstream, PR_BOOL, _showBg ) ;
	BS_WriteValue(bitstream, PR_BOOL, _showIcon ) ;
	if ( _showIcon )
	{
		BS_WriteValue(bitstream, PR_UINT16, strlen ( _str ) ) ;
		BS_WriteValue(bitstream, PR_STRING, _str ) ;
		
		BS_WriteValue(bitstream, PR_UINT16, strlen ( _str2 ) ) ;
		BS_WriteValue(bitstream, PR_STRING, _str2 ) ;
	}
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

stock ShowFingerPrint ( playerid, _id, _text [ ] )
{
	#if defined debug_packet
		printf ( "[ShowFingerPrint] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_FINGER_PRINT);
    
	BS_WriteValue(bitstream, PR_UINT8, _id);
	
	BS_WriteValue(bitstream, PR_UINT8, strlen ( _text ) ) ;
	BS_WriteValue(bitstream, PR_STRING, _text);
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

stock CheckAndroidID ( playerid, _id )
{
	#if defined debug_packet
		printf ( "[CheckAndroidID] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_CHECK_ANDROID);
	
    BS_WriteValue(bitstream, PR_INT8, _id);
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

stock SetMobileClient ( playerid )
{
	#if defined debug_packet
		printf ( "[SetMobileClient] playerid: %d", playerid ) ;
	#endif

    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_MOBILE_CLIENT);
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}