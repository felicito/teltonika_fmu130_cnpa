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
const char FM1U30_SEPARATOR[]        = ",";
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
const char FMU130_START[]           = "A";
const int IMEI_LENGHT               = 15;

bool verify_fmu130_payload(char payload[1011]) {
    bool a_encontrada = false;  // Tipo Bool
    bool coma_encontrada = false;     // Tipo Bool
    char *ret;

    // Verificar si se encuentra el inicio del comando A
    ret = strchr(payload, FMU130_START[0]);
    if (ret!=NULL) {
        a_encontrada = true;
    }

    // Verificar si se encuentra el separador "," 
    ret = strchr(payload, FM1U30_SEPARATOR[0]);
    if (ret!=NULL) {
        coma_encontrada = true;
    }

    // a_encontrada el tamaño de la trama
    if (a_encontrada && coma_encontrada) { // Trama para procesar
        return(true);
    } else  { // Trama para ignorar
        return(false);  
    }
}

bool parse_fmu130_payload(char payload[1011], char header[2], char imei[16], int *cmd_fmu, int *param_fmu) {
    int i = 0;
    char *avl_id;
    char *status;
    char *p;


    p = strtok(payload, FM1U30_SEPARATOR[0]);
    strcpy(header,p);

    while (p != NULL) {
        i++;
        p = strtok(NULL, FM1U30_SEPARATOR[0]);
        switch(i) {
            case 1:
                strcpy(imei,p);
                break;
            
            case 2:
                strcpy(avl_id,p);
                *cmd_fmu = atoi(avl_id);
                break;

            case 3:
                strcpy(status,p)
                *param_fmu = atoi(status);
                break;
        }
    }
return(true);
}
