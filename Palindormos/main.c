/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alejandro
 *
 * Created on August 29, 2019, 10:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "palindromo.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int cantPalindromos = 0;
    char *palindromos[64]; // numero mágico :(
    
    char linea[LONG_PALABRA+1];
    printf("Ingrese palabras separadas por espacio:\n");
    gets(linea);
    
    if((cantPalindromos = obtenerPalindromos(linea, palindromos)) == ERR_MEM){
        printf("Error en la reserva de memoria\n");
        exit(EXIT_FAILURE);
    }
    
    if(cantPalindromos > 0){
        printf("Se encontraron %d palindromos\nEstos son:\n", cantPalindromos);
        for(int i=0; i<cantPalindromos; i++){
            printf("%d)_ %s\n", i+1, palindromos[i]);
        }
    }
    else{
        printf("No se encontraron palíndromos\n");
    }
    
    
    exit (EXIT_SUCCESS);
}

