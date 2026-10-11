#if defined _m_tech_center_included
    #endinput
#endif
#define _m_tech_center_included

#define UI_TECH_CENTER 87

// Categories
#define TECH_CAT_STAGE 0
#define TECH_CAT_MODE 1
#define TECH_CAT_WHEEL_DRIVE 2
#define TECH_CAT_BRAKING 3
#define TECH_CAT_LAUNCH_CONTROL 4

stock bool:tech_center_is_personal_vehicle(playerid, vehicleid)
{
    if (!vehicleid || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return false;
    if (veh_info[vehicleid - 1][v_type] != vehicle_type_player) return false;
    if (veh_info[vehicleid - 1][v_owner] != p_info[playerid][id]) return false;
    return true;
}

stock show_packet_tech_center(playerid, action_id, packet[])
{
    if(action_id == 0) // SEND_REQ_BASKET
    {
        // empty basket
    }
    else if(action_id == 2) // SEND_REQ_BUY_DETAIL
    {
        new Node: json = JSON_Object();
        JSON_Parse(packet, json);
        
        new item_id, category;
        JSON_GetInt(json, "id", item_id);
        JSON_GetInt(json, "category", category);
        JSON_Cleanup(json);

        new current_vehicle_id = GetPlayerVehicleID(playerid);
        if (!tech_center_is_personal_vehicle(playerid, current_vehicle_id))
            return SendClientMessage(playerid, -1, "{FF0000}[Error] {FFFFFF}Tuning is available only for your personal vehicle.");
        
        new price = 50000;
        if(category == TECH_CAT_MODE) price = 100000;
        else if(category == TECH_CAT_WHEEL_DRIVE) price = 200000;
        else if(category == TECH_CAT_BRAKING) price = 75000;
        else if(category == TECH_CAT_LAUNCH_CONTROL) price = 150000;
        
        if (p_info[playerid][money] < price) return SendClientMessage(playerid, -1, "{FF0000}[Ошибка] {FFFFFF}Недостаточно средств.");
        
        // Take money
        p_info[playerid][money] -= price;
        update_int_sql(playerid, "u_money", p_info[playerid][money]);
        
        new veh_id = GetPlayerVehicleID(playerid);
        if (veh_id)
        {
            new ownable_id = veh_id - 1;
            if(category == TECH_CAT_STAGE)
            {
                veh_info[ownable_id][v_stage_speed] = item_id;
                SendClientMessage(playerid, -1, "{00FF00}[Тюнинг] {FFFFFF}Вы успешно установили Stage!");
            }
            else if(category == TECH_CAT_MODE)
            {
                // Drift, Sport, Sport+
                veh_info[ownable_id][V_HP_MAX_SPEED] += 10;
                SendClientMessage(playerid, -1, "{00FF00}[Тюнинг] {FFFFFF}Вы успешно изменили режим езды!");
            }
            else if(category == TECH_CAT_WHEEL_DRIVE)
            {
                veh_info[ownable_id][V_HP_TRACTION_MULTIPLIER] += 5;
                SendClientMessage(playerid, -1, "{00FF00}[Тюнинг] {FFFFFF}Вы успешно изменили привод!");
            }
            else if(category == TECH_CAT_BRAKING)
            {
                veh_info[ownable_id][v_stage_brake] = item_id;
                SendClientMessage(playerid, -1, "{00FF00}[Тюнинг] {FFFFFF}Вы успешно установили спортивные тормоза!");
            }
            else if(category == TECH_CAT_LAUNCH_CONTROL)
            {
                veh_info[ownable_id][V_HP_ACCELERATION] += 5;
                SendClientMessage(playerid, -1, "{00FF00}[Тюнинг] {FFFFFF}Вы успешно установили Launch Control!");
            }
        }
        else
        {
            SendClientMessage(playerid, -1, "{FF0000}[Ошибка] {FFFFFF}Вы должны находиться в транспорте.");
        }
        
        ShowPlayerTechCenter(playerid);
    }
    return 1;
}

stock ShowPlayerTechCenter(playerid)
{
    new string[2048];
    new money = p_info[playerid][money];
    new donate = p_info[playerid][donate];
    
    // 0: BALANCE_INFO
    format(string, sizeof(string), "{\"money\": %d, \"donate\": %d}", money, donate);
    onServerSendData(playerid, UI_TECH_CENTER, 0, string);
    
    // 1: BASKET_ITEMS
    onServerSendData(playerid, UI_TECH_CENTER, 3, "[]");
    
    // 3: PARAMETER_ITEMS - STAGE (0)
    format(string, sizeof(string), "[{\"category\": 0, \"id\": 1, \"name\": \"Stage 1\", \"priceType\": 0, \"price\": 50000, \"params\": [{\"type\": 0, \"progress\": 10, \"secondProgress\": 20, \"max\": 100}], \"isInstalled\": false, \"isBought\": false}]");
    onServerSendData(playerid, UI_TECH_CENTER, 2, string);
    
    // 3: PARAMETER_ITEMS - MODE (1)
    format(string, sizeof(string), "[{\"category\": 1, \"id\": 1, \"name\": \"Drift Mode\", \"priceType\": 0, \"price\": 100000, \"params\": [{\"type\": 3, \"progress\": 50, \"secondProgress\": 80, \"max\": 100}], \"isInstalled\": false, \"isBought\": false}]");
    onServerSendData(playerid, UI_TECH_CENTER, 2, string);
    
    // 3: PARAMETER_ITEMS - WHEEL_DRIVE (2)
    format(string, sizeof(string), "[{\"category\": 2, \"id\": 1, \"name\": \"AWD\", \"priceType\": 0, \"price\": 200000, \"params\": [{\"type\": 1, \"progress\": 50, \"secondProgress\": 60, \"max\": 100}], \"isInstalled\": false, \"isBought\": false}]");
    onServerSendData(playerid, UI_TECH_CENTER, 2, string);
    
    // 3: PARAMETER_ITEMS - BRAKING (3)
    format(string, sizeof(string), "[{\"category\": 3, \"id\": 1, \"name\": \"Sport Brakes\", \"priceType\": 0, \"price\": 75000, \"params\": [{\"type\": 2, \"progress\": 30, \"secondProgress\": 50, \"max\": 100}], \"isInstalled\": false, \"isBought\": false}]");
    onServerSendData(playerid, UI_TECH_CENTER, 2, string);
    
    // 3: PARAMETER_ITEMS - LAUNCH_CONTROL (4)
    format(string, sizeof(string), "[{\"category\": 4, \"id\": 1, \"name\": \"Launch Control v1\", \"priceType\": 0, \"price\": 150000, \"params\": [{\"type\": 1, \"progress\": 70, \"secondProgress\": 90, \"max\": 100}], \"isInstalled\": false, \"isBought\": false}]");
    onServerSendData(playerid, UI_TECH_CENTER, 2, string);
    
    return 1;
}

CMD:vmode(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if (!tech_center_is_personal_vehicle(playerid, vehicleid))
        return SendClientMessage(playerid, -1, "{FF0000}[Error] {FFFFFF}Drive modes are unavailable for rented or non-personal vehicles.");
    new ownable_id = vehicleid - 1;
    new modelid = getVehicleOrdinalNumber(vehicleid);

    if(!strcmp(params, "comfort", true))
    {
        veh_info[ownable_id][V_HP_MAX_SPEED] = veh_handling[modelid][VEHICLE_HP_MAX_SPEED];
        veh_info[ownable_id][V_HP_ACCELERATION] = veh_handling[modelid][VEHICLE_HP_ACCELERATION];
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен режим КОМФОРТ.");
    }
    else if(!strcmp(params, "sport", true))
    {
        veh_info[ownable_id][V_HP_MAX_SPEED] = veh_handling[modelid][VEHICLE_HP_MAX_SPEED] + 20;
        veh_info[ownable_id][V_HP_ACCELERATION] = veh_handling[modelid][VEHICLE_HP_ACCELERATION] + 10;
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен режим СПОРТ.");
    }
    else if(!strcmp(params, "drift", true))
    {
        veh_info[ownable_id][V_HP_MAX_SPEED] = veh_handling[modelid][VEHICLE_HP_MAX_SPEED] + 5;
        veh_info[ownable_id][V_HP_ACCELERATION] = veh_handling[modelid][VEHICLE_HP_ACCELERATION] + 25;
        veh_info[ownable_id][V_HP_TRACTION_MULTIPLIER] = veh_handling[modelid][VEHICLE_HP_TRACTION_MULTIPLIER] - 2;
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен режим ДРИФТ.");
    }

    sc_AddHandling(vehicleid);
    return 1;
}

CMD:vdrive(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if (!tech_center_is_personal_vehicle(playerid, vehicleid))
        return SendClientMessage(playerid, -1, "{FF0000}[Error] {FFFFFF}Drivetrain control is unavailable for rented or non-personal vehicles.");
    new ownable_id = vehicleid - 1;

    if(!strcmp(params, "fwd", true))
    {
        veh_info[ownable_id][V_HP_TRACTION_BIAS] = 100;
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен ПЕРЕДНИЙ привод.");
    }
    else if(!strcmp(params, "rwd", true))
    {
        veh_info[ownable_id][V_HP_TRACTION_BIAS] = 0;
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен ЗАДНИЙ привод.");
    }
    else if(!strcmp(params, "awd", true))
    {
        veh_info[ownable_id][V_HP_TRACTION_BIAS] = 50;
        SendClientMessage(playerid, -1, "{00FF00}[Управление] {FFFFFF}Включен ПОЛНЫЙ привод.");
    }

    sc_AddHandling(vehicleid);
    return 1;
}
