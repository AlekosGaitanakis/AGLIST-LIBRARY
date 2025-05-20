FLAGS = -ansi -Wall

all: aglist

aglist: main.o aglist.o
	gcc main.o aglist.o -o aglist

main.o: main.c aglist.h
	gcc $(FLAGS) -c main.c

aglist.o: aglist.c aglist.h
	gcc $(FLAGS) -c aglist.c

clean:
	rm -f *.o aglist