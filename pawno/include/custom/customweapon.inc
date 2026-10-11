#define PACKET_CUSTOMRPC    			251

#define RPC_CUSTOM_WEAPONS          	0x5

stock SetPlayerWeaponTexture ( playerid, targetid )
{
	#if defined debug_packet
		printf ( "[SetPlayerWeaponTexture] playerid: %d", playerid ) ;
	#endif
	
	new modelId, _count = 0 ;
	for ( new i = 0 ; i < MAX_ACCESORIES ; i ++ )
	{
		modelId = GetUserAccessories ( playerid, ACS_MODEL, i ) ;
		if ( ! weapon_skins ( modelId ) ) continue ;

		_count ++ ;
	}

	if ( _count > 0 )
	{
		new BitStream:bitstream = BS_New();
		BS_WriteValue(
			bitstream, 
			PR_UINT8, PACKET_CUSTOMRPC,
			PR_UINT32, RPC_CUSTOM_WEAPONS,
		
			PR_UINT16, playerid,
			PR_INT8, _count);

		for ( new i = 0 ; i < MAX_ACCESORIES ; i ++ )
		{
			modelId = GetUserAccessories ( playerid, ACS_MODEL, i ) ;
			if ( ! weapon_skins ( modelId ) ) continue ;

			BS_WriteValue(
				bitstream,
				PR_INT32, item_weapon ( modelId ),
				PR_INT32, item_color ( modelId, 1 ) ) ;
		}

		PR_SendPacket(bitstream, targetid);

		BS_Delete(bitstream);
	}
}

stock ClearPlayerWeaponTexture ( playerid, targetid )
{
	#if defined debug_packet
		printf ( "[ClearPlayerWeaponTexture] playerid: %d", playerid ) ;
	#endif

	new BitStream:bitstream = BS_New();

	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_CUSTOM_WEAPONS,
		
		PR_UINT16, playerid,
		PR_INT8, 7,

		PR_INT32, 24,
		PR_INT32, 0,

		PR_INT32, 25,
		PR_INT32, 0,

		PR_INT32, 29,
		PR_INT32, 0,

		PR_INT32, 30,
		PR_INT32, 0,

		PR_INT32, 31,
		PR_INT32, 0,

		PR_INT32, 33,
		PR_INT32, 0,

		PR_INT32, 34,
		PR_INT32, 0
	);

	PR_SendPacket(bitstream, targetid);

	BS_Delete(bitstream);
}