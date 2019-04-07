#ifndef _DANE_H
#define _DANE_H
#define naz nazwanie[i] 
#define prz bieg[i] 
#define num mer[i]
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct samochody{
	char nazwa[16],przebieg[8],numer[6];
} auta;
typedef struct Element{
	auta dane;
	struct Element *next;
}E;
typedef struct Handler{
	char kraj[16];
	E *beg;
	struct Handler *nast;
}Kraj;
typedef struct MainHandler{
	Kraj *first;
}Mhan;
void wpisz(Mhan *Main);
void wypisz(Mhan Main);
void Przebieg(E *sam);
void Nazwa(Kraj *tym3,E *przekaz);
void Numer(Mhan *Main,E *sam);
void stworz(Mhan *Main);
void usun(Mhan *Main);
void zmien_nazwe(Mhan *Main);
void popraw(Mhan *Main);
void przenies(Mhan *Main);
void wyswietlnazwy(Mhan *Main);
void wyswietlkatalog(Mhan *Main);
void pliki(Mhan *Main);
void zapisztxt(Mhan *Main,char *plik);
void wczytajtxt(Mhan *Main,char *plik);
void zapiszula(Mhan *Main,char *plik);
void wczytajbin(Mhan *Main,char *plik);
void haslo(char *klucz);
#endif
