/**
 * @file teltonika_fmu130.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "BufferedSerial.h"

// COMMANDS
const int FMU130_COMMAND           = 65;
const int SERVER_COMMAND           = 64;


int read_fmu130_uart(BufferedSerial *puertoCOM, char m_buffer[1024]) {
    int w = 0;
    while (puertoCOM -> readable()) {
        char incoming_char = puertoCOM -> getc();
        m_buffer[w] = incoming_char;
        w++;
    }
    m_buffer[w] = '\0';
    return(w);
}

int identify_fmu130_payload(char m_buffer[1024]) {
    int type_of_payload = -1;
    char *pch;

    pch = strchr(m_buffer, FMU130_COMMAND);
    if (pch!=NULL) {
        type_of_payload = 1;
    } 

    pch = strchr(m_buffer, SERVER_COMMAND);
    if (pch!=NULL) {
        type_of_payload = 2;
    }
    return(type_of_payload);
}