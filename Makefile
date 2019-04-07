clean: test
	rm -f *.o
test: main.o wpisz.o popraw.o wypisz.o katalog.o pliki.o
	cc -ansi -Wall main.o wpisz.o popraw.o wypisz.o katalog.o pliki.o -o test
main.o: main.c
	cc -c -ansi -Wall main.c -o main.o
wpisz.o: wpisz.c
	cc -c -ansi -Wall wpisz.c -o wpisz.o
popraw.o: popraw.c
	cc -c -ansi -Wall popraw.c -o popraw.o
wypisz.o: wypisz.c
	cc -c -ansi -Wall wypisz.c -o wypisz.o
katalog.o: katalog.c
	cc -c -ansi -Wall katalog.c -o katalog.o
pliki.o: pliki.c
	cc -c -ansi -Wall pliki.c -o pliki.o
