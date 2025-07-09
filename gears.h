#ifndef GEARS_H_
#define GEARS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for State_Type
typedef enum State 
{
    GEAR_DOWN,
    CHECKING_BEFORE_TAKEOFF,
    RAISING_GEAR,
    GEAR_UP,
    CHECK_BEFORE_LANDING,
    LOWERING_GEAR,
} State_Type;

// Enum for Switch_status
typedef enum Switch 
{
    on,
    off // plane is on ground
} Switch_status;

// Enum for pilot_lever
typedef enum pilot_lever 
{
    Raising,
    falling
} pilot_lever;

// Enum for hydraulic_mechanism
typedef enum hydraulic_mechanism 
{
    working,
    not_working
} hydraulic_mechanism;

// Function declarations
void GearDown(void);
void CheckingBeforeTakeOFF(void);
void RaisingGear(void);
void GearUp(void);
void CheckBeforeLanding(void);
void LoweringGear(void);
void Initiate_State_Machine(void);

// Function pointer array
extern void (*statetable[])(void);

// Declaring variables as volatile for Switch_status, pilot_lever, hydraulic_mechanism
extern volatile Switch_status squat_switch;
extern volatile Switch_status limit_switch;
extern volatile pilot_lever pl;
extern volatile hydraulic_mechanism hm;

// Declaring a variable to access State_type
extern State_Type current_state;

// Structure for State_Table
typedef struct State_Table 
{
    char* current_state_indication;
    char* light;
    char* direction_valve_status;
    char* landing_gear_hydraulic_control;
    char* Gas_Pressurized_Spring_system_status[2];
} State_Table;

// Initialize State_Machine array
extern State_Table State_Machine[6];

#endif /* GEARS_H_ */


