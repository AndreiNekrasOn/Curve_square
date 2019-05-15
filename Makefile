all: prog.out
.PHONY: all
prog.out: functions.o main.o
	gcc -m32 -o prog.out functions.o main.o
functions.o: functions.asm 
	nasm -f elf32 -o functions.o functions.asm 
main.o: main.c
	gcc -m32 -c -o main.o main.c
clean:
	rm *.o prog.out
