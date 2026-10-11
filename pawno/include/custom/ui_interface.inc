#define PACKET_CUSTOMRPC    			251
#define RPC_UI_INTERFACE				0x90

stock onServerDestroy ( playerid, uiElementId )
{
	#if defined debug_packet
		printf ( "[onServerDestroy] playerid: %d", playerid ) ;
	#endif

    new BitStream:bitstream = BS_New();
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_UI_INTERFACE,
		PR_INT8, 0,
		
		PR_INT32, uiElementId);

    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

stock onServerSendData ( playerid, uiElementId, actionId, data [ ] )
{
	#if defined debug_packet
		printf ( "[onServerSendData] playerid: %d", playerid ) ;
	#endif

    new BitStream:bitstream = BS_New();
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_UI_INTERFACE,
		PR_INT8, 1,
		
		PR_INT32, uiElementId,
		PR_INT32, actionId,
		
		PR_UINT32, strlen ( data ),
		PR_STRING, data);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock onServerSendCacheData ( playerid, cacheId, data [ ] )
{
	#if defined debug_packet
		printf ( "[onServerSendCacheData] playerid: %d", playerid ) ;
	#endif

    new BitStream:bitstream = BS_New();
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_UI_INTERFACE,
		PR_INT8, 2,
		
		PR_INT32, cacheId,
		
		PR_UINT32, strlen ( data ),
		PR_STRING, data);

    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}