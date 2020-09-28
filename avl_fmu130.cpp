/**
 * @file avl_fmu130.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */


// Teltonika AVL ID Events
const char FM130_SEPARATOR[]        = ",";
const char AVLID_IDLING[]           = "251";
const char AVLID_WARNING_SPEED[]    = "24";
const char AVLID_OVERSPEED[]        = "255";
const char AVLID_CRASH[]            = "317";
const char AVLID_JAMMING[]          = "249";
const char AVLID_TOWING[]           = "246";
const char AVLID_GREEN_DRIVING[]    = "253";
const char AVLID_ACCELERATION[]     = "1";
const char AVLID_BREAKING[]         = "2";
const char AVLID_CORNERING[]        = "3";
const char AVLID_EVENT_START[]      = "1";
const char AVLID_EVENT_STOP[]       = "0";
const int IMEI_LENGHT               = 15;
