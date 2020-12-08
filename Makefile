# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = 

EXE = main

all: $(EXE)

clean:
	${RM} $(EXE)
	${RM} *.o
	${RM} *.d
# END