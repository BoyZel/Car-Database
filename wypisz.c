#include "dane.h"
#include <ctype.h>
void wypisz(Mhan Main){
	printf("Wedlug ktorego parametru samochody maja zostac wyswietlone?0- Nazwa 1- Przebieg 2-Numer: ");
	char adin;
	adin=getc(stdin);
	getc(stdin);
	int tryb;
	tryb=adin-48;
	char folder[16];
	int rozmiar=0;
	if(tryb==0){
		printf("\nProsze o wpisanie nazwy, wedlug ktorej samochody maja zostac wyswietlone: ");
		char tmp2=getc(stdin);
		while(tmp2!='\n'){
			if(rozmiar>14){
				printf("\nNie ma zadnego samochodu o takim parametrze\n");
				return;
			}
			folder[rozmiar]=tmp2;
			rozmiar++;
			tmp2=getc(stdin);
		}
	}
	if(tryb==1){
		printf("\nProsze o wpisanie przebiegu, wedlug ktorego samochody maja zostac wyswietlone: ");
		char tmp2=getc(stdin);
		while(tmp2!='\n'){
			if(rozmiar>6){
				printf("\nNie ma zadnego samochodu o takim parametrze\n");
				return;
			}
			folder[rozmiar]=tmp2;
			rozmiar++;
			tmp2=getc(stdin);
		}
	}
	if(tryb==2){
		printf("\nProsze o wpisanie numeru, o ktorym samochod ma zostac wyswietlony: ");
		char tmp2=getc(stdin);
		while(tmp2!='\n'){
			if(rozmiar>4){
				printf("\nNie ma zadnego samochodu o takim parametrze\n");
				return;
			}
			folder[rozmiar]=tmp2;
			rozmiar++;
			tmp2=getc(stdin);
		}
	}
	int i;
	for(i=rozmiar;i<16;i++)
		folder[i]='\0';
	folder[0]=toupper(folder[0]);
	printf("Dzial		nazwa samochodu 	numer		przebieg silnika[km]\n");
	Kraj *tmp;
	tmp=Main.first;
	while(tmp!=NULL){
		E *rekord;
		rekord=tmp->beg;
		while(rekord!=NULL){
			if((tryb==0&&strncmp(rekord->dane.nazwa,folder,rozmiar)==0)||(tryb==1&&strncmp(rekord->dane.przebieg,folder,rozmiar)==0)||(tryb==2&&strncmp(rekord->dane.numer,folder,rozmiar)==0)){
				printf("%s\t",tmp->kraj);
				if(strlen(tmp->kraj)<8)
					printf("\t");
				printf("%s\t\t",rekord->dane.nazwa);
				if(strlen(rekord->dane.nazwa)<8)
					printf("\t");
				printf("%s\t\t",rekord->dane.numer);
				printf("%s",rekord->dane.przebieg);
				printf("\n");
			}
			rekord=rekord->next;
		}
		tmp=tmp->nast;
	}
}
