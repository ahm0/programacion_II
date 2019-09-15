/*
 * habitación.c
 *
 *  Created on: Apr 11, 2019
 *      Author: alejandro
 */


#include "svc_habitacion.h"
#include <string.h>
#include <stdlib.h>

char * getFullPath(const char *path, const char *fileName){
    if(strcmp(fileName, "")==0){
                    return NULL;
    }

    // el +1 es para la barra
    int nameLength = strlen(path) != 0 ? (strlen(path) + 1) : 2;

    // fileName + .dat + \0
    nameLength += strlen(fileName) + 4 + 1;

    char *fullPath = (char*)(malloc(sizeof(char)*nameLength));

    //memset se utiliza para inicializar un puntero
    memset(fullPath, '\0', nameLength);

    if(strcmp(path, "")==0){
            strncpy(fullPath, "./", 2);
    }
    else{
            strncpy(fullPath, path, strlen(path));
            *(fullPath+(strlen(fullPath))) = '/';
    }

    strncat(fullPath, fileName, strlen(fileName));
    strncat(fullPath, ".dat", 5);
    return fullPath;
}

char * getFileModeAsString(FILE_MODE mode){

    switch(mode){
    case FILE_CREATE:
            return "w+b";
            break;
    case FILE_EDIT:
            return "r+b";
            break;
    case FILE_READ:
            return "rb";
            break;
    default:
            return "";
            break;
    }
}

FILE *openFile(const char *path, const char *fileName, FILE_MODE mode){

    char *fullpath = getFullPath(path, fileName);
    return fopen(fullpath, getFileModeAsString(mode));
}

/**
 * Crea una reserva a partir de los datos.
 *
 * @param dni dni del cliente
 * @param clientName nombre del cliente
 * @param status estado de la reserva
 * @return ST_BOOKING
 */
ST_BOOKING createBooking(int dni, char clientName[NAME_LONG+1], STATUS status){
    ST_BOOKING booking;

    booking.client.dni = dni;
    memset(booking.client.name, '\0', NAME_LONG+1);
    strncpy(booking.client.name, clientName, strlen(clientName));
    booking.status = status;
    return booking;
}

/**
 * Obtiene el desplazamiento, en cantidad de bytes, que debe moverse el puntero del archivo para
 * posicionarse en una habitación. El desplazamiento se considera desde el inicio del archivo.
 *
 * @param roomId id de la habitación buscada
 * @return cantidad de bytes a desplazarse.
 */
long getOffset(const int roomId){
    
    return (roomId > 0 && roomId < ROOM_COUNT) ? (roomId - 1) * sizeof(ST_BOOKING) : -1;
}

void clearBuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}


void initializeRooms(FILE *pFile){
	ST_BOOKING booking = createBooking(0, "", NOT_RESERVED);
	for(int i=0; i < ROOM_COUNT; i++){
            booking.roomId = i+1;
            fwrite(&booking, sizeof(booking), 1, pFile);
	}
}


ERRORS addAutomaticBooking(FILE *pFile, ST_BOOKING booking){ 
    rewind(pFile);
    ST_BOOKING emptyBooking;
    fread(&emptyBooking, sizeof(ST_BOOKING), 1, pFile);

    while(!feof(pFile) && emptyBooking.status == RESERVED){
        fread(&emptyBooking, sizeof(ST_BOOKING), 1, pFile);
    }

    if(feof(pFile)){
        return ERR_FULL_OCUPPATION;
    }

    fseek(pFile, getOffset(emptyBooking.roomId), SEEK_SET);
    booking.roomId = emptyBooking.roomId;
    fwrite(&booking, sizeof(ST_BOOKING), 1, pFile);
    return ERR_OK;
}

ERRORS addManualBooking(FILE *pFile, ST_BOOKING booking){ 

    // mueve el puntero del archivo a la posición del registro
    int result = fseek(pFile, getOffset(booking.roomId), SEEK_SET);
    if(result != 0){
        return ERR_ROOM_NOT_FOUND;
    }
    
    // leo el registro
    ST_BOOKING emptyBooking;
    fread(&emptyBooking, sizeof(ST_BOOKING), 1, pFile);
    if(emptyBooking.status == RESERVED) {
        return ERR_RESERVED;
    }

    // vuelve a poner el puntero del archivo en la posición del registro
    fseek(pFile, getOffset(booking.roomId), SEEK_SET);
    
    // escribo el nuevo valor del registro
    fwrite(&booking, sizeof(ST_BOOKING), 1, pFile);
    return ERR_OK;
}

ERRORS addBooking(FILE *pFile, ADD_MODE mode){
    char nombre[NAME_LONG+1];
    int dni;
    printf("Ingrese nombre del cliente: ");
    clearBuffer();
    fgets(nombre, NAME_LONG, stdin);
    printf("Ingrese DNI: ");
    scanf("%d", &dni);
    ST_BOOKING newBooking = createBooking(dni, nombre, RESERVED);
    
    ERRORS result;
    if(mode == AUTOMATIC){
        result = addAutomaticBooking(pFile, newBooking);
    } 
    else {
        printf("Ingrese Id de la habitación: ");
        scanf("%hd", &newBooking.roomId);
        result = addManualBooking(pFile, newBooking);
    }
    
    return result;
}



ERRORS doDeleteBooking(FILE *pFile, short int roomId, ST_BOOKING *booking){
    if(roomId < 0 || roomId > ROOM_COUNT){
            return ERR_ROOM_NOT_FOUND;
    }

    long offset = getOffset(roomId);
    fseek(pFile, offset, SEEK_SET);
    fread(booking, sizeof(ST_BOOKING), 1, pFile);

    ST_BOOKING blankBooking = createBooking(0, "", NOT_RESERVED);
    blankBooking.roomId = roomId;
    fseek(pFile, offset, SEEK_SET);
    fwrite(&blankBooking, sizeof(ST_BOOKING), 1, pFile);
    return ERR_OK;
}


ERRORS delBooking(FILE *pFile){
    int roomId = -1;
    printf("Ingrese ID de habitación: ");
    scanf("%d", &roomId);
    ST_BOOKING deleted;
    ERRORS retVal = doDeleteBooking(pFile, roomId, &deleted);
    if(retVal == ERR_OK){
        printf("\n\nDatos de la Reserva eliminada\n");
        showBooking(deleted);
        printf("\n\n");
    }
    return retVal;
}


void getStatusAsText(const STATUS status, char *buffer, int bufLength){

	memset(buffer, '\0', bufLength);
	if(status == RESERVED){
		strncpy(buffer, "Reservada", 10);
	}
	else{
		strncpy(buffer, "Libre", 5);
	}

	return;
}

void showBooking(ST_BOOKING booking){
    char line[80+1];
    memset(line, '\0', 81);
    memset(line, '-', 80);
    char status[10];
    getStatusAsText(booking.status, status, 10);

    printf("RoomId: %d\tCliente: %s\tDNI: %d\tEstado: %s\n",
                booking.roomId, booking.client.name, booking.client.dni, status);
    printf("%s\n", line);
}

void listBooking(FILE *pFile){
    ST_BOOKING readBooking;
    fread(&readBooking, sizeof(readBooking), 1, pFile);
    while(!feof(pFile)){
        showBooking(readBooking);
        fread(&readBooking, sizeof(readBooking), 1, pFile);
    }
}

