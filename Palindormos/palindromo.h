/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   palindromo.h
 * Author: alejandro
 *
 * Created on August 29, 2019, 10:57 PM
 */

#ifndef PALINDROMO_H
#define PALINDROMO_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define LONG_PALABRA 256
    
    typedef enum {ERR_OK=-1, ERR_MEM=-2, ERR_GEN=-3} ERROR;

    typedef enum {FALSE=0, TRUE} BOOL;

    /**
     * Devuelve la cantidad y los palíndromos existentes en el parametro linea.
     * 
     * @param char *linea
     * @param char **palindromos
     * @return ERROR
     */    
    int obtenerPalindromos(const char *linea, char **palindromos);


#ifdef __cplusplus
}
#endif

#endif /* PALINDROMO_H */

