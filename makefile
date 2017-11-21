all: pipe.c
	gcc -o pipe.exe pipe.c

run: all
	./pipe.exe
