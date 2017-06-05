# Simple Makefile
 
# Vars
CC= gcc
CPPFLAGS= -MMD                     # Flags for preprocessor
CFLAGS= -Wall -Wextra -std=c99 -O2 # Flags for the compiler
LDFLAGS=                           # Flags for the linker, usually empty
LDLIBS=                            # Listings libs

SRC= file1.c main.c                # Source files
OBJ= ${SRC:.c=.o}                  # object files
DEP= ${SRC:.c=.d}                  # dependency files

# Default rule: just ask for bin main
all: main

# main depends on object files, that's all we need
main: ${OBJ}

# cleaning rule
clean:
	${RM} ${OBJ} ${DEP} main

# includes deps
-include ${DEP}

# END of Makefile

