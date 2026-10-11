#define PACKET_CUSTOMRPC    			251
#define RPC_PLAYER_TAG					0x141
#define RPC_PLAYER_INFO					0x143

stock SetPlayerTag ( playerid, targetid, bool: status, _str [ ], _type, _color, _colorBox )
{
	#if defined debug_packet
		printf ( "[SetPlayerTag] playerid: %d", playerid ) ;
	#endif
    new BitStream: bitstream = BS_New ( ) ;
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_PLAYER_TAG);
	
	BS_WriteValue(
		bitstream,
		PR_UINT16, targetid,
		PR_BOOL, status,
	
		PR_UINT8, strlen ( _str ),
		PR_STRING, _str,
	
		PR_UINT8, _type,
		PR_UINT32, _color,
		PR_UINT32, _colorBox ) ;

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock SetPlayerInfo ( playerid, forplayerid )
{
	#if defined debug_packet
		printf ( "[SetPlayerInfo] playerid: %d, forplayerid: %d", playerid, forplayerid ) ;
	#endif

    new BitStream: bitstream = BS_New ( ), familyName [ 64 ], familyId = p_info [ playerid ] [ family ] ;

	if ( familyId )
		format ( familyName, sizeof familyName, "{%s}%s", family_info [ familyId - 1 ] [ fam_chat_color ], family_info [ familyId - 1 ] [ fam_name ] ) ;

	else
		format ( familyName, sizeof familyName, "" ) ;

	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_PLAYER_INFO,

		PR_UINT16, playerid,
		PR_INT32, p_info [ playerid ] [ level ],
		PR_BOOL, p_info [ playerid ] [ vip ] ? true : false,
		PR_UINT8, strlen ( familyName ),
		PR_STRING, familyName
	);

    PR_SendPacket(bitstream, forplayerid);
	BS_Delete(bitstream);
}
