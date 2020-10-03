/**
 * @file fingerprint_frame.cpp
 * @author Felícito Manzano (felicito.manzano@detektor.com.sv)
 * @brief 
 * @version 0.1
 * @date 2020-09-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "mbed.h" 

/**
 * @brief 
 * 
 */
const char SERVER_SEPARATOR[]   = ";";
const char FINGER_CMD_BEGIN[]   = "@";
const char FINGER_CMD_EOF[]     = "#";
const char ADD_CMD[]            = "ADD"; // AGREGAR HUELLA
const char DEL_CMD[]            = "DEL"; // ELIMINAR HUELLA
const char DIS_CMD[]            = "OFF"; // DESHABILITAR HUELLA
const char ENA_CMD[]            = "ON1"; // HABILITAR HUELLA
const char QRY_CMD[]            = "ASK"; // INTERROGAR HUELLA
const int FINGER_CMD_START      = 1;
const int FINGER_CMD_END        = 3;
const int FINGER_ID_BEGIN       = 5;
const int FINGER_ID_END         = 8;
const int FINGER_PAYLOAD        = 9;

/**
 * @brief 
 * 
 * @param cadena 
 * @return int 
 */
int strID_to_intID(char cadena[5]) {
    /*
    Esta función recibe una cadena de 5 posiciones
    multiplica cada posición de la cadena por su peso
    decimal y lo acumula en una variable de tipo long.
    La posición 5 no se opera por tratarse del caracter
    de fin de cadena \0.
    */
    int result = 0;
    int temp = 0;
 
    temp = (int) cadena[0];
    temp = temp - 48.0;
    temp = temp * 1000;
    result = result + temp;
 
    temp = (int) cadena[1];
    temp = temp - 48.0;
    temp = temp * 100;
    result = result + temp;
 
    temp = (int) cadena[2];
    temp = temp - 48.0;
    temp = temp * 10;
    result = result + temp;
 
    temp = (int) cadena[3];
    temp = temp - 48.0;
    result = result + temp;
 
    return(result);
}

/**
 * @brief 
 * 
 * @param payload 
 * @return true 
 * @return false 
 */
bool verify_finger_payload(char payload[1011]) {
    bool inicio_encontrado = false;  // Tipo Bool
    bool fin_encontrado = false;     // Tipo Bool
    char *ret;

    // Verificar si se encuentra el inicio del comando @
    ret = strchr(payload, FINGER_CMD_BEGIN[0]);
    if (ret!=NULL) {
        inicio_encontrado = true;
    }

    // Verificar si se encuentra el fin de comando #
    ret = strchr(payload, FINGER_CMD_EOF[0]);
    if (ret!=NULL) {
        fin_encontrado = 1;
    }

    if (inicio_encontrado && fin_encontrado) { // Trama para procesar
        return(true);
    } else  { // Trama para ignorar
        return(false);  
    }
}

/**
 * @brief 
 * 
 * @param payload 
 * @param comando 
 * @param id_huella 
 * @param huella_hex 
 * @return true 
 * @return false 
 */
bool parse_finger_payload(char payload[1011], char comando[4], int *id_huella, char huella_hex[997]) {
    int x;          // Variable para moverse en el array de trama entrante
    int i = 0;      // Variable para moverse en el array de las sub cadenas
    char id_txt[5]; // Almacenar temporalmente el ID a procesar.

    // Extraer el comando
    for (x = FINGER_CMD_START; x <= FINGER_CMD_END; x++) {
        comando[i] = payload[x];
        i++;
    }
    comando[i] = '\0';
    i=0;
 
    // Extraer el ID
    for (x = FINGER_ID_BEGIN;  x <= FINGER_ID_END; x++) {
        id_txt[i] = payload[x];
        i++;
    }
    id_txt[i] = '\0';
    *id_huella = strID_to_intID(id_txt);
    i=0;
 
    char * pch;
    pch = strrchr(payload, SERVER_SEPARATOR[0]);
    int posicion_puntoycoma = pch - payload + 1; 
    // El segmento anterior busca la ultima posición del separador ";"
    // Documentación de las últimas líneas de código en:
    // http://www.cplusplus.com/reference/cstring/strrchr/
    
    if (posicion_puntoycoma > FINGER_PAYLOAD) {
        int longitud_trama = strlen(payload);
        for (x = FINGER_PAYLOAD; x <= longitud_trama; x++) {
            huella_hex[i] = payload[x];
            i++;
        }
        huella_hex[i] = '\0';
    }

    if (i > 1) { // indica que entró en el lazo FOR porque es trama ADD
        return(true);
    } else { // no entro a lazo FOR y último valor de "i" fue 0.
        return(false);
    }
}

/**
 * @brief 
 * 
 * @param huella_hex 
 * @param huella_ascii 
 * @return true 
 * @return false 
 */
bool fingerprint_HEX2CHAR(char huella_hex[997], char huella_ascii[499]) {
    /*
    Esta función se encarga de analisar el payload de una
    huella que es enviada dentro de una cadena (char array)
    expresada de manera hexadecimal. en su equivalente de código
    ASCII que es guardado en otra cadena.
    */
 
    int i = 0;
    int j = 0;
    int k = 0;
    int limite = strlen(huella_hex);
    char pre_buffer[] = "--\0";
 
    for (i=0; i<limite; i++) {
        pre_buffer[j] = huella_hex[i];
        j++;
 
        if ((i%2)&&(i>=1)) { // Si es impar.
            j=0;
            huella_ascii[k] =  (int)strtol(pre_buffer, NULL, 16);
            k++;
        }
    }
    return(true);
}

/**
 * @brief 
 * 
 * @param comando 
 * @return int 
 */
int identify_cmd_finger(char comando[4]) {
    /*
       Esta función se encarga de verificar que el comando a ejecutar es soportado
       por el código y que no se ha generado una mala interpretación de la trama
       al momento de extraer los caracteres correspondientes al comando.
       Esta función retorna 1 si el comando es ADD. Retorna 2 para el comando DEL.
       Retorna 0 si no es ninguno de los dos.
    */
    char* p; 
    int comand_int = 0;

    p = strstr(comando, ADD_CMD);
    if (p!=NULL) {
        comand_int = 1;
    } 

    p = strstr(comando, DEL_CMD);
    if (p!=NULL) {
        comand_int = 2;
    }


    return(comand_int);
}