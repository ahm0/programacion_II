CC	    	:= gcc
C_FLAGS	    	:= -Wall -Wextra -fPIC 

BIN	    	:= bin
SRC	    	:= src
INCLUDE	    	:= include
LIB	    	:= lib

LIBRARY_PATH   	:= ./bin/lib
LIBRARIES   	:= $(LIBRARY_PATH)/svc_habitacion.so $(LIBRARY_PATH)/svc_menu.so

APP_NAME	:= habapp

EXECUTABLE  	:= $(APP_NAME)

CFILES		:= $(SRC)/main.c

all: $(CFILES)
	$(CC) $(C_FLAGS) -I$(INCLUDE) $(CFILES) $(LIBRARIES) -o $(APP_NAME)

libs: 
	cd $(LIB) && make && make install
	
install:
	mv $(APP_NAME) $(BIN)/$(APP_NAME) 

run: 
	./$(BIN)/$(APP_NAME)

clean:
	rm $(BIN)/$(APP_NAME) $(BIN)/$(LIB)/*.so 

