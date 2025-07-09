/*
Name : Nestin Gregorios Sunny

Date : 09.07.2025

Description :
Project 2 - Implement code for controlling the retraction and extension of Airplane's Landing Gears
*/

#include "gears.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

State_Type current_state;
volatile Switch_status squat_switch;
volatile Switch_status limit_switch;
volatile pilot_lever pl;
volatile hydraulic_mechanism hm;

void (*statetable[])(void) = 
{
    GearDown,
    CheckingBeforeTakeOFF,
    RaisingGear,
    GearUp,
    CheckBeforeLanding,
    LoweringGear
};

State_Table State_Machine[6] = 
{
    {"GearDown", "Green", "Down", "Enabled", {"Disabled", "Disabled"}},
    {"CheckingBeforeTakeOFF", "Green", "Down", "Enabled", {"Disabled", "Disabled"}},
    {"RaisingGear", "Red", "Up", "Enabled", {"Enabled", "Disabled"}},
    {"GearUp", "Off", "Up", "Disabled", {"Enabled", "Disabled"}},
    {"CheckBeforeLanding", "Red", "Down", "Enabled", {"Disabled", "Enabled"}},
    {"LoweringGear", "Green", "Down", "Enabled", {"Disabled", "Enabled"}}
};

//function definitions
void GearDown(void) 
{
    current_state = GEAR_DOWN;      //enum = GEAR_DOWN
    printf("\nEnter the status of pilot's lever (0 for Raising, 1 for falling): ");
    int input;
    if (scanf("%d", &input) != 1)       // 0 
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input;
    if(pl == Raising) 
    {
        current_state = CHECKING_BEFORE_TAKEOFF;        //enum = CHECKING_BEFORE_TAKEOFF
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nLanding Gear Hydraulic Control : %s", State_Machine[current_state].landing_gear_hydraulic_control);
    } 
    else 
    {
        GearDown();
    }
}

void CheckingBeforeTakeOFF(void) 
{
    current_state = CHECKING_BEFORE_TAKEOFF;        //enum = CHECKING_BEFORE_TAKEOFF 
    printf("\nEnter the status of pilot's lever (0 for Raising, 1 for falling), squat switch (0 for on, 1 for off) and hydraulic mechanism (0 for working, 1 for not working): ");
    int input_pl, input_squat_switch, input_hm;
    if (scanf("%d %d %d", &input_pl, &input_squat_switch, &input_hm) != 3)      //0 0 0 
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input_pl;
    squat_switch = (Switch_status)input_squat_switch;
    hm = (hydraulic_mechanism)input_hm;
    if(pl == falling && squat_switch == off) 
    {
        current_state = GEAR_DOWN;      //enum = GEAR_DOWN
        GearDown(); 
    } 
    else if(pl == Raising && squat_switch == on && hm == working) 
    {
        current_state = RAISING_GEAR;       //enum = RAISING_GEAR
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nStatus of Direction valve : %s", State_Machine[current_state].direction_valve_status);
    } 
    else if(pl == Raising && squat_switch == on && hm == not_working) 
    {
        current_state = RAISING_GEAR;       //enum = RAISING_GEAR 
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nStatus of Direction valve : %s", State_Machine[current_state].direction_valve_status);
        printf("\nStatus of gas pressurised Spring System : %s", State_Machine[current_state].Gas_Pressurized_Spring_system_status[0]);
    }
}

void RaisingGear(void) 
{
    current_state = RAISING_GEAR;       //enum = RAISING_GEAR
    printf("\nEnter the status of pilot's lever (0 for Raising, 1 for falling) and limit switch (0 for on, 1 for off): ");
    int input_pl, input_limit_switch;
    if (scanf("%d %d", &input_pl, &input_limit_switch) != 2)        //0 1
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input_pl;
    limit_switch = (Switch_status)input_limit_switch;
    if(pl == falling && limit_switch == on) 
    {
        current_state = CHECK_BEFORE_LANDING;   //enum = CHECKING_BEFORE_LANDING 
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nLanding Gear Hydraulic Control : %s", State_Machine[current_state].landing_gear_hydraulic_control);
    } 
    else if(pl == Raising && limit_switch == off) 
    {
        current_state = GEAR_UP;        //enum = GEAR_UP
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nLanding Gear Hydraulic Control : %s", State_Machine[current_state].landing_gear_hydraulic_control);
    } 
    else 
    {
        RaisingGear();
    }
}

void GearUp(void) 
{
    current_state = GEAR_UP;        //enum = GEAR_UP
    printf("\nEnter the status of pilot's lever (0 for Raising, 1 for falling): ");
    int input;
    if (scanf("%d", &input) != 1)       //1
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input;
    if(pl == falling) 
    {
        current_state = CHECK_BEFORE_LANDING;       //enum = CHECK_BEFORE_LANDING 
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nLanding Gear Hydraulic Control : %s", State_Machine[current_state].landing_gear_hydraulic_control);
    } 
    else 
    {
        GearUp();
    }
}

void CheckBeforeLanding(void) 
{
    current_state = CHECK_BEFORE_LANDING;       //enum = CHECKING_BEFORE_LANDING 
    printf("\nEnter the status of pilot's lever (0 for Raising, 1 for falling) and hydraulic mechanism (0 for working, 1 for not working): ");
    int input_pl, input_hm;
    if (scanf("%d %d", &input_pl, &input_hm) != 2)      //1 0 
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input_pl;
    hm = (hydraulic_mechanism)input_hm;
    if(pl == falling && hm == working) 
    {
        current_state = LOWERING_GEAR;      //enum = LOWERING_GEAR
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nStatus of Direction valve : %s", State_Machine[current_state].direction_valve_status);
    } 
    else if(pl == falling && hm == not_working) 
    {
        current_state = LOWERING_GEAR;      //enum = LOWERING_GEAR
        printf("\nCurrent State : %s", State_Machine[current_state].current_state_indication);
        printf("\nLight is : %s", State_Machine[current_state].light);
        printf("\nStatus of Direction valve : %s", State_Machine[current_state].direction_valve_status);
        printf("\nStatus of gas pressurised Spring System : %s", State_Machine[current_state].Gas_Pressurized_Spring_system_status[1]);
    } 
    else if(pl == Raising) 
    {
        CheckBeforeLanding();
    }
}

void LoweringGear(void) 
{
    current_state = LOWERING_GEAR;      //enum = LOWERING_GEAR
    printf("Enter the status of pilot's lever (0 for Raising, 1 for falling) and limit switch (0 for on, 1 for off): ");
    int input_pl, input_limit_switch;
    if (scanf("%d %d", &input_pl, &input_limit_switch) != 2)        //1 0 
    {
        printf("Invalid input\n");
        return;
    }
    
    pl = (pilot_lever)input_pl;
    limit_switch = (Switch_status)input_limit_switch;
    if(pl == falling && limit_switch == on) 
    {
        current_state = CHECKING_BEFORE_TAKEOFF;        //enum = CHECKING_BEFORE_TAKEOFF
        printf("Current State : %s\n", State_Machine[current_state].current_state_indication);
        printf("Light is : %s\n", State_Machine[current_state].light);
    } 
    else if(pl == Raising && limit_switch == off)
    {
        current_state = GEAR_DOWN;      //enum = GEAR_DOWN
        printf("Current State : %s\n", State_Machine[current_state].current_state_indication);
        printf("Light is : %s\n", State_Machine[current_state].light);
        printf("Landing Gear Hydraulic Control : %s\n", State_Machine[current_state].landing_gear_hydraulic_control);
    } 
    else if(limit_switch == off) 
    {
        LoweringGear();
    }
}

void Initiate_State_Machine() 
{
    current_state = GEAR_DOWN;      //enum = GEAR_DOWN 
    printf("The Finite State Machine is Intialized and current the program is in GearDown State & Light is : %s\n",State_Machine[current_state].light);
}
