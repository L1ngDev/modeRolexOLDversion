#define PACKET_CUSTOMRPC    			251
#define RPC_SPEEDOMETR					0x27

/*

	Отправляется при создании спидометра (посадки в тачку)

*/

stock SendSpeedometr ( playerid, _v_id, bool: _open = false )
{
	#if defined debug_packet
		printf ( "[SendSpeedometr] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_SPEEDOMETR);
    
	new Float: _fuel = 0.03 ;
	if ( veh_info [ _v_id - 1 ] [ v_millage ] > 100 ) _fuel = _fuel + ( veh_info [ _v_id - 1 ] [ v_millage ] / 100000 ) ;

	new _millage = floatround ( veh_info [ _v_id - 1 ] [ v_millage ] ) ;
	BS_WriteValue(
		bitstream,
		PR_INT8, 0, // не трогать
		
		PR_FLOAT, veh_info [ _v_id - 1 ] [ v_fuel ], // количество бензина
		PR_FLOAT, _fuel, // расход
		
		PR_UINT32, _millage, // пробег
		PR_BOOL, _open); // показать или не показывать. Если true - будет отображён
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}

/*

	нумерация поворотников

*/

enum eTurnState
{
	TURN_OFF = 0,
	TURN_LEFT,
	TURN_RIGHT,
	TURN_ALL
};

stock TurnSpeedometr ( playerid, vehicleId, _id )
{
	#if defined debug_packet
		printf ( "[TurnSpeedometr] playerid: %d", playerid ) ;
	#endif
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_SPEEDOMETR);
	
	BS_WriteValue(
		bitstream,
		PR_INT8, 1,
		PR_UINT16, vehicleId, // номер машины (в переменных всё идёт от GetPlayerVehicleID ( playerid ))
		PR_INT8, _id); // из eTurnState. Чтоб выключить ВСЁ TURN_OFF
	
    PR_SendPacket(bitstream, playerid);

	BS_Delete(bitstream);
}