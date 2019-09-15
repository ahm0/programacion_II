/*
 * habitacion.h
 *
 *  Created on: Apr 11, 2019
 *  Author: alejandro
 */

#ifndef INCLUDES_HABITACION_H_
#define INCLUDES_HABITACION_H_

#include <stdio.h>

// Cantidad de habitaciones
#define ROOM_COUNT 10

// Longitud del nombre del cliente.
#define NAME_LONG 50

// Modos de apertura del archivo
typedef enum {FILE_CREATE, FILE_EDIT, FILE_READ} FILE_MODE ;

typedef enum {AUTOMATIC, MANUAL} ADD_MODE;

typedef enum  {NOT_RESERVED, RESERVED} STATUS;

typedef enum  {ERR_FULL_OCUPPATION, ERR_ROOM_NOT_FOUND, ERR_RESERVED, ERR_OK} ERRORS;


typedef struct {
    int dni;
    char name[NAME_LONG + 1];
} ST_CLIENT;

// Estructura para gestionar los datos de una reserva.
typedef struct {
    short int roomId;
    STATUS status;
    ST_CLIENT client;
} ST_BOOKING;

/**
 * Crea o abre un archivo binario en el path y fileName indicado.
 * Se asume que el path existe y es válido. Si path es cadena vacía, el archivo se genera en el directorio del ejecutable.
 * No se verifica la existencia del archivo.
 *
 * @param path string que indica el path donde generar o abrir el archivo. Sin barra al final.
 * @param filename string nombre del archivo sin extensión.
 * @param mode FILE_MODE el modo de apertura del archivo.
 * @return puntero al archivo.
 */
FILE *openFile(const char *path, const char *fileName, FILE_MODE mode);

/**
 * Inicializa el archivo, cargando ROOM_COUNT habiationes.
 * Genera un archivo PUP utilizando como clave el id de cada habitación.
 * Las habitaciones se marcaran como libres.
 *
 * @param pFile puntero al archivo.
 */
void initializeRooms(FILE *pFile);

/**
 * Agrega una reserva de habitación al archivo.
 * La reserva se agrega en la primer habitación desocupada.
 *
 * @param pFile puntero al archivo.
 * @param booking reserva a agregar en el archivo.
 */
ERRORS addBooking(FILE *pFile, ADD_MODE mode);

/**
 * Elimina una reserva de habitación del archivo. La eliminación es lógica.
 *
 * @param pFile puntero al archivo.
 * @param roomId id de la habitación buscada
 * @param booking reserva eliminada del archivo.
 * @return reserva eliminada.
 */
ERRORS delBooking(FILE *pFile);

/**
 * Imprime por pantalla los datos de una habitación
 *
 * @param booking la reserva a imprimir.
 */
void showBooking(ST_BOOKING booking);

/**
 * Imprime por pantalla un listado con los datos las habitaciones
 *
 * @param pFile puntero al archivo.
 */
void listBooking(FILE *pFile);

#endif /* INCLUDES_HABITACION_H_ */
