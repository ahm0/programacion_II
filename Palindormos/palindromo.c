/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "palindromo.h"
#include <stdlib.h> // malloc


/**
 * Simil memset, carga el buffer con el caracter \0
 * 
 * @param char * buffer
 */
void resetPalabra(char *buffer){
    for(int i=0; i<LONG_PALABRA+1; i++){
        *(buffer+i) = '\0';
    }
}

/**
 * Devuelve la longitud de una palabra.
 * 
 * @param char *palabra
 * @return int cantidad de caracteres.
 */
int longitudPalabra(const char *palabra){
    int cantidad = 0;
    while(*palabra){
        cantidad++;
        palabra++;
    }
    return cantidad;
}

/**
 * Obtiene del parametro linea una palabra y la devuelve. Una palabra esta 
 * definida entre 2 espacios. Se asume que no hay más de 1 espacio entre palabras.
 * 
 * @param char *linea 
 * @param char * const palabra
 * @param int indice devuelve la posicion del puntero sobre el parametro linea.
 */
void obtenerPalabra(const char *linea, char * const palabra, int *indice){
    int i=0;
    while(*linea && *linea != ' '){
        *(palabra + i) = *linea;
        linea++;
        i++;
        *indice = *indice + 1;
    }
    *indice = *indice + 1;
}

/**
 * Devuelve TRUE en caso de que la palabra pasada por parametro sea un palindromo.
 * 
 * @param char * palabra
 * @return BOOL TRUE en caso de que sea palindromo. FALSE en otro caso.
 */
BOOL esPalindromo(const char *palabra){
    int cantidad = longitudPalabra(palabra);
    
    int inicio = 0;
    int final = cantidad - 1;
    
    while (*palabra && (*(palabra + inicio) == *(palabra + final)) && inicio < final) {
        inicio++;
        final--;
    }
    
    return inicio == final || inicio > final;
}

/**
 * Copia el parametro origen en el parametro destino
 * 
 * @param char * origen 
 * @param char * destino
 */
void copiaPalabra(const char *origen, char * const destino){
    int i = 0;
    while(*origen){
        *(destino+i) = *origen;
        origen++;
        i++;
    }
}

ERROR obtenerPalindromos(const char *linea, char **palindromos){
    int cantPalindromos = 0;
    char *palabra;
    int posPalindromo=0;
    int indice = 0;
    
    if( (palabra = (char*) malloc(sizeof(char)*LONG_PALABRA+1)) == NULL ){
      return ERR_MEM;  
    }
    
    while(*linea){
        resetPalabra(palabra);
        indice = 0;
        obtenerPalabra(linea, palabra, &indice);
        
        if(esPalindromo(palabra)){
            cantPalindromos++;
            int longPalabra = longitudPalabra(palabra)+1;
            if( (palindromos[posPalindromo] = 
                            (char*) malloc(sizeof(char)*longPalabra)) == NULL ){
                return ERR_MEM;  
            }
            
            copiaPalabra(palabra, palindromos[posPalindromo++]);
        }
        linea = linea + indice;
    }
    
    
    return cantPalindromos;
}