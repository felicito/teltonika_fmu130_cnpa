/**
 * @file teltonika_fmu130.hpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __TELTONIKA_FMU130_HPP
#define __TELTONIKA_FMU130_HPP

    // COMMANDS
    extern const int FMU130_COMMAND;
    extern const int SERVER_COMMAND;  

    int read_fmu130_uart(BufferedSerial *puertoCOM, char m_buffer[1024]);

#endif // __TELTONIKA_FMU130_HPP