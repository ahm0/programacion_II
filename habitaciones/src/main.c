/*
 * main.c
 *
 *  Created on: Apr 11, 2019
 *  Author: alejandro
 */

#include "svc_habitacion.h"
#include "svc_menu.h"
#include <stdlib.h>
#include <string.h>


int main(){
    ERRORS result;
    FILE *pFile = NULL;

    showMenu();

    OPTIONS option = getOption();
    while(option != END_PROGRAM){

            switch(option){
                    case INITIALIZE:
                        pFile = openFile("", "prueba", FILE_CREATE);
                        initializeRooms(pFile);
                        fclose(pFile);
                        break;
                    case ADD_BOOKING_AUTO:
                        pFile = openFile("", "prueba", FILE_EDIT);
                        result = addBooking(pFile, AUTOMATIC);
                        if(result == ERR_FULL_OCUPPATION){
                            printf("No hay habitaciones disponibles\n");
                        }
                        fclose(pFile);
                        break;
                    case ADD_BOOKING_MAN:
                        pFile = openFile("", "prueba", FILE_EDIT);
                        result = addBooking(pFile, MANUAL);
                        if(result == ERR_RESERVED){
                            printf("Habitación ya reservada. Elija otra.\n");
                        }
                        if(result == ERR_ROOM_NOT_FOUND){
                            printf("Habitación no existente. Elija otra.\n");
                        }
                        if(result == ERR_FULL_OCUPPATION){
                            printf("No hay habitaciones disponibles\n");
                        }
                        fclose(pFile);
                        break;
                    case DEL_BOOKING:
                        pFile = openFile("", "prueba", FILE_EDIT);
                        if(delBooking(pFile) != ERR_OK){
                            exit(EXIT_FAILURE);
                        }
                        fclose(pFile);
                        break;
                    case SHOW_BOOKING:
                        break;
                    case LIST_BOOKING:
                        pFile = openFile("", "prueba", FILE_READ);
                        listBooking(pFile);
                        fclose(pFile);
                        break;
                    default:
                        printf("Opción no válida\n");
                        break;
            }

            printf("\n\n------0------\n\n");
            showMenu();
            printf("\nIngrese opción:\n");
            option = getOption();
    }

    return 0;

}

