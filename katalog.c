#include "dane.h"
#include <ctype.h>
void stworz(Mhan *Main){
	int i=0,j=0;
	printf("Prosze wprowadzic nazwe folderu do utworzeniu: ");
	char tmp=' ';
	char dzial[16];
	while(tmp!='\n')
	{
		tmp=getc(stdin);
		if(tmp!='\n')
			dzial[j]=tmp;
		j++;
		if(j==16){
			printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu od nowa\n");
			stworz(Main);
			return;
		}
	}
	for(i=j-1;i<16;i++)
		dzial[i]='\0';
	i=0;
	dzial[i]=toupper(dzial[i]);
	if(dzial[i]<'A'||dzial[i]>'Z'){	
		printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu  od nowa\n");
		stworz(Main);
		return;
	}
	for(i=1;i<j-1;i++)
	{
		if(((dzial[i]<'a'||dzial[i]>'z')&& (dzial[i]!=' ')&&(dzial[i]<'A'||dzial[i]>'Z'))||((dzial[i-1]!=' '&&(dzial[i]>'A'&&dzial[i]<'Z')))){
		printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu  od nowa\n");
			stworz(Main);
			return;
		}
	}
	Kraj *tym3=malloc(sizeof *tym3);
	for(i=0;i<16;i++)
		tym3->kraj[i]=dzial[i];
	Kraj *tym2;
	tym2=Main->first;
	if(tym2==NULL){
		Main->first=tym3;
		tym3->nast=tym2;
	}
	else{
		if(strcmp(tym2->kraj,tym3->kraj)==0){
			printf("Istnieje juz katalog o tej nazwie");
			return;
		}
		if(strcmp(tym2->kraj,tym3->kraj)>0){
			Main->first=tym3;
			tym3->nast=tym2;
		}
		else{
			while(tym2->nast!=NULL){
				if(strcmp(tym2->nast->kraj,tym3->kraj)==0){
					printf("Istnieje juz katalog o tej nazwie");
					return;
				}
				if(strcmp(tym2->nast->kraj,tym3->kraj)>0){
					tym3->nast=tym2->nast;
					tym2->nast=tym3;
					break;
				}
				tym2=tym2->nast;
			}
			if(tym2->nast==NULL){
				tym2->nast=tym3;
				tym3->nast=NULL;
			}
		}
		tym3->beg=NULL;
	}
}
void usun(Mhan *Main){
	printf("Prosze wpisac nazwe folderu do usuniecia: ");
	char tmp2=getc(stdin);
	int rozmiar=0;
	char folder[16];
	while(tmp2!='\n'){
		if(rozmiar>14){
			printf("\nNie ma takiego folderu?\n");
			return;
		}
		folder[rozmiar]=tmp2;
		rozmiar++;
		tmp2=getc(stdin);
	}
	folder[0]=toupper(folder[0]);
	int i;
	for(i=rozmiar;i<16;i++)
		folder[i]='\0';
	Kraj *tym;
	if(Main->first==NULL){
		printf("Brak folderow do usuniecia\n");
		return;
	}
	tym=Main->first;
	if(!strcmp(tym->kraj,folder)){
		Main->first=tym->nast;
		free(tym);
		return;
	}
	while(tym->nast!=NULL){
		if(!strcmp(tym->nast->kraj,folder)){
			tym->nast=tym->nast->nast;
			return;
		}
		tym=tym->nast;
	}
}
void zmien_nazwe(Mhan *Main){
	char folder[16];
	int rozmiar=0;
	printf("Prosze o wpisanie nazwy folderu, ktora ma zostac zmieniona: ");
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
	folder[0]=toupper(folder[0]);
	int i;
	for(i=rozmiar;i<16;i++)
		folder[i]='\0';
	int j=0;
	char tmp=' ';
	char *dzial=malloc(16*sizeof(char));
	printf("\nProsze o wpisanie nowej nazwy folderu: ");
	while(tmp!='\n')
	{
		tmp=getc(stdin);
		if(tmp!='\n')
			dzial[j]=tmp;
		j++;
		if(j==17){
			printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu od nowa\n");
			return;
		}
	}
	printf("\n");
	dzial[j]='\0';
	i=0;
	dzial[i]=toupper(dzial[i]);
	if(dzial[i]<'A'||dzial[i]>'Z'){	
		printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu  od nowa\n");
		return;
	}
	for(i=1;i<j-1;i++)
	{
		if(((dzial[i]<'a'||dzial[i]>'z')&& (dzial[i]!=' ')&&(dzial[i]<'A'||dzial[i]>'Z'))||((dzial[i-1]!=' '&&(dzial[i]>'A'&&dzial[i]<'Z')))){
		printf("Wczytano nieprawidlowy napis. Wpisz nazwe folderu  od nowa\n");
			return;
		}
	}
	Kraj *tym;
	if(Main->first==NULL){
		printf("W bazie ma zadnego katalogu\n");
		return;
	}
	tym=Main->first;
	if(!strcmp(tym->kraj,folder))
		Main->first=tym->nast;
	else{
		while(tym->nast!=NULL){
			if(!strcmp(tym->nast->kraj,folder)){
				Kraj *tym3=tym->nast;
				tym->nast=tym3->nast;
				tym=tym3;
				break;
			}
			tym=tym->nast;
		}
	}
	if(tym==NULL){
		printf("Nie ma takiego folderu\n");
		return;
	}
	for(i=0;i<strlen(dzial);i++)
		tym->kraj[i]=dzial[i];
	for(i=strlen(dzial);i<strlen(tym->kraj);i++)
		tym->kraj[i]='\0';
	if(Main->first==NULL){
		Main->first=tym;
		tym->nast=NULL;
		return;
	}
	Kraj *tym2=Main->first;
	if(strcmp(tym->kraj,tym2->kraj)<0){
		Main->first=tym;
		tym->nast=tym2;
		return;
	}
	while(tym2->nast!=NULL){
		if(strcmp(tym->kraj,tym2->nast->kraj)<0){
			tym->nast=tym2->nast;
			tym2->nast=tym;
			return;
		}
		tym2=tym2->nast;
	}
	tym2->nast=tym;
	tym->nast=NULL;
}
void wyswietlnazwy(Mhan *Main){
	Kraj *tmp=Main->first;
	while(tmp!=NULL){
		printf("%s\n",tmp->kraj);
		tmp=tmp->nast;
	}
}


void wyswietlkatalog(Mhan *Main){
	printf("Prosze o podanie nazwy katalogu, ktorego zawartosc ma byc wyswietlona: ");
	char folder[16];
	int rozmiar=0;
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
	folder[0]=toupper(folder[0]);
	int i;
	for(i=rozmiar;i<16;i++)
		folder[i]='\0';
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
	E *rekord=tym3->beg;
	printf("Nazwa\t\tNumer\t\tPrzebieg\n");
	while(rekord!=NULL){
		printf("%s\t",rekord->dane.nazwa);
		if(strlen(rekord->dane.nazwa)<8)
			printf("\t");
		printf("%s\t\t",rekord->dane.numer);
		printf("%s",rekord->dane.przebieg);
		printf("\n");
		rekord=rekord->next;
	}
}
