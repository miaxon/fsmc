default: fsm.o main.o
	gcc -o fsm fsm.o main.o
fsm.o:
	gcc -c fsm.c
main.o:
	gcc -c main.c
