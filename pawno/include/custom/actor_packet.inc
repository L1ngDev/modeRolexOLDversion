#define PACKET_CUSTOMRPC    			251
#define RPC_ACTOR_ACTION				0x161

stock actorPutInVeh ( playerid, actorId, vehicleId, seatId )
{
	#if defined debug_packet
		printf ( "[actorPutInVeh] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();

	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 0,
		
		PR_UINT16, actorId,
		PR_UINT16, vehicleId,
		PR_UINT8, seatId);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorRemoveFromVeh ( playerid, actorId, vehicleId, toAnim )
{
	#if defined debug_packet
		printf ( "[actorRemoveFromVeh] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	// _anim = 1 - not used anim
	// _anim = 0 - used anim exit
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 1,
		
		PR_UINT16, actorId,
		PR_UINT16, vehicleId,
		PR_UINT8, toAnim);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorEnterCarPass ( playerid, actorId, vehicleId, seatId )
{
	#if defined debug_packet
		printf ( "[actorEnterCarPass] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 2,
		
		PR_UINT16, actorId,
		PR_UINT16, vehicleId,
		PR_UINT8, seatId);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorSetArmour ( playerid, actorId, Float: armour )
{
	#if defined debug_packet
		printf ( "[actorSetArmour] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 3,
		
		PR_UINT16, actorId,
		PR_FLOAT, armour);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorSetName ( playerid, actorId, actorName [ ] )
{
	#if defined debug_packet
		printf ( "[actorSetName] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 4,
		
		PR_UINT16, actorId,
		
		PR_UINT8, strlen ( actorName ),
		PR_STRING, actorName);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorShootTo ( playerid, actorId, Float: x, Float: y, Float: z, shootTime )
{
	#if defined debug_packet
		printf ( "[actorShootTo] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 5,
		
		PR_UINT16, actorId,
		
		PR_FLOAT, x,
		PR_FLOAT, y,
		PR_FLOAT, z,
		
		PR_UINT32, shootTime);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorSetPosFindZ ( playerid, actorId, Float: x, Float: y, Float: z )
{
	#if defined debug_packet
		printf ( "[actorSetPosFindZ] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 6,
		
		PR_UINT16, actorId,
		
		PR_FLOAT, x,
		PR_FLOAT, y,
		PR_FLOAT, z);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorGoto ( playerid, actorId, Float: x, Float: y, Float: z, Float: a )
{
	#if defined debug_packet
		printf ( "[actorGoto] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 7,
		
		PR_UINT16, actorId,
		
		PR_FLOAT, x,
		PR_FLOAT, y,
		PR_FLOAT, z,
		PR_FLOAT, a);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorGuardGoto ( playerid, ownerId, actorId, Float: x, Float: y, Float: z, Float: a )
{
	#if defined debug_packet
		printf ( "[actorGuardGoto] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 12,
		
		PR_UINT16, ownerId,
		PR_UINT16, actorId,
		
		PR_FLOAT, x,
		PR_FLOAT, y,
		PR_FLOAT, z,
		PR_FLOAT, a);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorGiveWeapon ( playerid, actorId, weaponId, totalAmmo )
{
	#if defined debug_packet
		printf ( "[actorGiveWeapon] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 8,
		
		PR_UINT16, actorId,
		PR_UINT32, weaponId,
		PR_UINT32, totalAmmo);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorAttack ( playerid, actorId, issuerId )
{
	#if defined debug_packet
		printf ( "[actorAttack] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 9,
		
		PR_UINT16, actorId,
		PR_UINT16, issuerId);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorClearTasks ( playerid, actorId )
{
	#if defined debug_packet
		printf ( "[actorClearTasks] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 10,
		
		PR_UINT16, actorId);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorInvulnerable ( playerid, actorId, bool: status )
{
	#if defined debug_packet
		printf ( "[actorInvulnerable] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 11,
		
		PR_UINT16, actorId,
		PR_BOOL, status);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock actorGiveWeaponSkill ( playerid, actorId, weaponId, skillLevel )
{
	#if defined debug_packet
		printf ( "[actorGiveWeaponSkill] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 13,
		
		PR_UINT16, actorId,
		PR_UINT32, weaponId,
		PR_UINT32, skillLevel);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock DisableRemoteActorCollisions ( playerid, actorId, bool: status )
{
	#if defined debug_packet
		printf ( "[DisableRemoteActorCollisions] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 14,
		
		PR_UINT16, actorId,
		PR_BOOL, status);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}

stock SetActorChatBubble ( playerid, actorId, text [ ], color, Float: drawdistance, expiretime )
{
	#if defined debug_packet
		printf ( "[SetActorChatBubble] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
	
	BS_WriteValue(
		bitstream,
		PR_UINT8, PACKET_CUSTOMRPC,
		PR_UINT32, RPC_ACTOR_ACTION,

		PR_INT8, 15,
		
		PR_UINT16, actorId,
		PR_UINT8, strlen ( text ),
		PR_STRING, text,
		PR_UINT32, color,
		PR_FLOAT, drawdistance,
		expiretime, drawdistance);

    PR_SendPacket(bitstream, playerid);
	BS_Delete(bitstream);
}