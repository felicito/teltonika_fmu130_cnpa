/**
 * @file fingerprint_frame.hpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __FINGERPRINT_FRAME_HPP
#define __FINGERPRINT_FRAME_HPP

    extern const char SERVER_SEPARATOR[2];
    extern const char FINGER_CMD_BEGIN[2];
    extern const char FINGER_CMD_EOF[2];
    extern const char ADD_CMD[4];
    extern const char DEL_CMD[4];
    extern const char DIS_CMD[4]; 
    extern const char ENA_CMD[4]; 
    extern const char QRY_CMD[4]; 
    extern const int FINGER_CMD_START;
    extern const int FINGER_CMD_END;
    extern const int FINGER_ID_BEGIN;
    extern const int FINGER_ID_END;
    extern const int FINGER_PAYLOAD;

    int strID_to_intID(char cadena[5]);
    bool verify_finger_payload(char payload[1011]);
    bool parse_finger_payload(char payload[1011], char comando[4], int *id_huella, char huella_hex[997]);
    bool convertir_huella(char huella_hex[997], char huella_ascii[499]);
    int identify_cmd_finger(char comando[4]);

#endif // __FINGERPRINT_FRAME_HPP