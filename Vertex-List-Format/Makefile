a.out: main.o vertexListFormat.o 3d.o drawline.o
	gcc main.o vertexListFormat.o 3d.o drawline.o -lm
main.o: main.c
	gcc -c main.c -Wall
vertexListFormat.o: vertexListFormat.c
	gcc -c vertexListFormat.c -Wall
3d.o: 3d.c
	gcc -c 3d.c -Wall
drawline.o: drawline.c
	gcc -c drawline.c -Wall
indent: main.c vertexListFormat.c vertexListFormat.h 3d.c 3d.h drawline.c drawline.h
	indent main.c vertexListFormat.c vertexListFormat.h 3d.c 3d.h drawline.c drawline.h
clear:
	rm main.o vertexListFormat.o 3d.o drawline.o a.out
run: a.out
	./a.out
