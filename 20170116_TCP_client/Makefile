CC=gcc
CFLAGS= -g -Wall -Werror -Wextra -std=c99 
 
SRC= get_page.c
OBJ= ${SRC:.c=.o}
BIN= testing

all: $(BIN)
	gcc $(OBJ) -o get_page
$(BIN): $(OBJ)
	  
clean:
		rm -f *.o *.d get_page
				 
