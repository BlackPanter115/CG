a.out: main.o drawline.o 3d.o
	gcc main.o drawline.o 3d.o  -lm
main.o: main.c
	gcc -c main.c -Wall
drawline.o: drawline.c
	gcc -c drawline.c -Wall
3d.o: 3d.c
	gcc -c 3d.c -Wall
indent: main.c drawline.c drawline.h 3d.c 3d.h
	indent main.c drawline.c drawline.h 3d.c 3d.h
clear:
	rm main.o drawline.o 3d.o a.out
run:
	./a.out
