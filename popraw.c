#include "dane.h"
#include <ctype.h>
void popraw(Mhan *Main){
	int tryb;
	int szukana;
	printf("Ktora dana chcesz zmienic: 1-Nazwa, 2-Przebieg, 3-Numer: ");
	scanf("%d",&tryb);
	if(tryb<1 || tryb>3){
		printf("Podano nieprawidlowa wartosc");
		return;
	}
	getc(stdin);
	printf("\nProsze o podanie numeru samochodu ktorego dane maja zostac zmodyfikowane: ");
	scanf("%d",&szukana);
	getc(stdin);
	Kraj *tmp=Main->first;
	while(tmp!=NULL){
		E *rekord=tmp->beg;
		if(rekord!=NULL){
			if(atoi(rekord->dane.numer)==szukana){
				if(tryb==1){
					tmp->beg=rekord->next;
					Nazwa(tmp,rekord);
					return;
				}
				if(tryb==2){
					Przebieg(rekord);
					return;
				}
				if(tryb==3){
					Numer(Main,rekord);
					return;
				}
			}
		}
		while(rekord->next!=NULL){
			if(atoi(rekord->next->dane.numer)==szukana){
				E *chwila=rekord->next;
				if(tryb==1){
					rekord->next=rekord->next->next;
					Nazwa(tmp,chwila);
					return;
				}
				if(tryb==2){
					Przebieg(chwila);
					return;
				}
				if(tryb==3){
					Numer(Main,chwila);
					return;
				}
			}
			rekord=rekord->next;
		}
		tmp=tmp->nast;
	}
	printf("Nie ma samochodu o takim numerze\n");
	return;
}
void przenies(Mhan *Main){
	int x,rozmiar=0,czy=0,ile;
	printf("\nIle rekordow ma zostac przeniesionych?\n");
	scanf("%d",&ile);
	if(ile<1 || ile>50){
		printf("Nie ma takiej mozliwosci\n");
		return;
	}
	/*FOLDER*/
	getc(stdin);
	printf("\nProsze o podanie nazwy folderu, do ktorego rekordy maja zostac przeniesione: ");
	char folder[16];
	char tmp2=getc(stdin);
	while(tmp2!='\n'){
		if(rozmiar>14){
			printf("\nNie ma takiego folderu?\n");
			return;
		}
		folder[rozmiar]=tmp2;
		rozmiar++;
		tmp2=getc(stdin);
	}
	int i;
	for(i=rozmiar;i<16;i++)
		folder[i]='\0';
	folder[0]=toupper(folder[0]);
	Kraj *tym3=Main->first;
	while(tym3!=NULL){
		if(!strcmp(tym3->kraj,folder))
			break;
		tym3=tym3->nast;
	}
	if(tym3==NULL){
		printf("\nNie ma takiego folderu\n");
		return;
	}
	int licznik=0;
	/*Samochod*/
	while(licznik<ile){
		czy=0;
		printf("\nProsze o podanie numeru samochodu, ktory ma zostac przeniesiony: ");
		scanf("%d",&x);
		getc(stdin);
		Kraj *tmp=Main->first;
		E *rekord;
		while(tmp!=NULL){
			rekord=tmp->beg;
			if(rekord!=NULL){
				if(atoi(rekord->dane.numer)==x){
					czy=1;
					tmp->beg=rekord->next;
					break;
				}
			}
			if(rekord!=NULL)/*To moze byc trzeba wstawic funkcje wyzej !*/
			while(rekord->next!=NULL){
				if(atoi(rekord->next->dane.numer)==x){
					czy=1;
					E* chwilowy=rekord->next;
					rekord->next=chwilowy->next;
					rekord=chwilowy;
					break;
				}
				rekord=rekord->next;
			}
			if(czy==1)
				break;
			tmp=tmp->nast;
		}
		if(czy==0){
			printf("Nie ma samochodu o takim numerze\n");
			return;
		}
		/*Wlasciwa czesc funkcji*/
		E *przekaz=rekord;
		if(tym3->beg==NULL){
			przekaz->next=NULL;
			tym3->beg=przekaz;
		}
		else{
			E *tym;
			tym=tym3->beg;
			if(strcmp(tym->dane.nazwa,przekaz->dane.nazwa)>0){
				tym3->beg=przekaz;
				przekaz->next=tym;
			}
			else{
				while(tym->next!=NULL){
					if(strcmp(tym->next->dane.nazwa,przekaz->dane.nazwa)>0){
						przekaz->next=tym->next;
						tym->next=przekaz;
						break;
					}
					tym=tym->next;
				}
				if(tym->next==NULL){
					tym->next=przekaz;
					przekaz->next=NULL;
				}
			}
		}
		licznik++;
	}
}
