/*
Name : Nestin Gregorios Sunny

Date : 09.07.2025

Description :
Project 2 - Implement code for controlling the retraction and extension of Airplane's Landing Gears
*/

#include"gears.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() 
{
    Initiate_State_Machine();       //function call
    while (1) 
    {
        statetable[current_state]();        
    }
    return 0;
}


