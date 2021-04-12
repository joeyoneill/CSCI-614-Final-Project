CC = gcc
CFLAGS = -Wall -g

projectfinal.o: projectfinal.c
	${CC} ${CFLAGS} projectfinal.c -o projectfinal.o

clean:
	rm *.o
