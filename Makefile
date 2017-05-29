all: clean
	gcc -c -std=c11 -o jpg_loader.o jpg_loader.c
	ar rcs lib/libjpg_loader.a jpg_loader.o
clean:
	rm -f lib/*.a *.o
