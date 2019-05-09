all: prog
.PHONY: all
prog: functions.o main.o
	gcc -o prog functions.o main.o
functions.o: functions.asm 
	nasm -f elf32 -o functions.o functions.asm 
main.o: main.c
	gcc -c -o main.o main.c
clean:
	rm *.o prog.exe