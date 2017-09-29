a.out: main.o drawline.o
	gcc main.o drawline.o
main.o: main.c
	gcc -c main.c -Wall
drawline.o: drawline.c
	gcc -c drawline.c -Wall
indent: main.c drawline.c drawline.h
	indent main.c drawline.c drawline.h
clear:
	rm main.o drawline.o a.out
