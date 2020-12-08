# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = 

EXE = main neuralnetwork IAtoolsbox

all: $(EXE)

clean:
	${RM} $(EXE)
	${RM} *.o
	${RM} *.d
# END