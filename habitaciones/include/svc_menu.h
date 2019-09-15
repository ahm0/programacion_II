/*
 * menu.h
 *
 *  Created on: Apr 13, 2019
 *      Author: alejandro
 */

#ifndef MENU_H_
#define MENU_H_

typedef enum {END_PROGRAM, INITIALIZE, ADD_BOOKING_AUTO, ADD_BOOKING_MAN, DEL_BOOKING, SHOW_BOOKING, LIST_BOOKING} OPTIONS; 

typedef enum {ERR_OPTION_OK, ERR_INVALID_OPTION} MENU_ERRORS;

MENU_ERRORS validOption(OPTIONS option);

void showMenu();

OPTIONS getOption();

#endif /* MENU_H_ */
