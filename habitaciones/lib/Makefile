CC	:= gcc
C_FLAGS := -Wall -Wextra -fPIC 

BIN	:= ../bin
SRC	:= src
INCLUDE	:= ../include
LIB	:= lib

CHAB := svc_habitacion.c
CMENU := svc_menu.c
HFILES := $(INCLUDE)/svc_habitacion.h $(INCLUDE)/svc_menu.h

all: 
	make habitacion menu

habitacion: $(CHAB) $(HFILES)
	$(CC) $(C_FLAGS) -I$(INCLUDE) $(CHAB) -shared -o svc_habitacion.so
	
menu: $(CMENU) $(HFILES)
	$(CC) $(C_FLAGS) -I$(INCLUDE) $(CMENU) -shared -o svc_menu.so

install: 
	mv *.so $(BIN)/$(LIB)

clean:
	-$(RM) $(BIN)/$(LIB)/*.so
