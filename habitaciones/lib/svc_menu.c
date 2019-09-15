/*
 * menu.c
 *
 *  Created on: Apr 13, 2019
 *      Author: alejandro
 */

#include "svc_menu.h"
#include <string.h>
#include <stdio.h>

MENU_ERRORS validOption(OPTIONS option){
    if(option < INITIALIZE || option > LIST_BOOKING){
        return ERR_INVALID_OPTION;
    }
    else{
        return ERR_OPTION_OK;
    }
}

void printLineWithText(const char* text){
	char line1[80+1];
	memset(line1, '\0', 81);
	*line1='#';
	*(line1+79) = '#';

	strncat(line1+1, text, strlen(text));

	int i=0;
	while(i<80){
		if(*(line1+i) == '\0'){
			*(line1+i) = ' ';
		}
		i++;
	}

	printf("%s\n", line1);
}

void printHastagLine(){
	char line[80+1];
	memset(line, '\0', 81);
	memset(line, '#', 80);

	printf("%s\n", line);
}

void showMenu(){

	printHastagLine();
	printLineWithText("    Ingrese la opción deseada");
	printLineWithText("");
	printLineWithText("        1 - Inicailizar el archivo");
	printLineWithText("        2 - Agregar una reserva automatica");
        printLineWithText("        3 - Agregar una reserva manual");
	printLineWithText("        4 - Eliminar una reserva");
	printLineWithText("        5 - Mostrar una reserva");
	printLineWithText("        6 - Listar reservas");
	printLineWithText("        0 - Para finalizar");

}

OPTIONS getOption(){
	int option = INITIALIZE;
	scanf("%d", &option);
	printHastagLine();
	return option;
}
