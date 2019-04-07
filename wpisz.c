#include "dane.h"
#include <ctype.h>
void wpisz(Mhan *Main){
	printf("Prosze podawac dane dotyczace samochodow w kolejnosci:\n1.Folder, do ktorego dany rekord ma zostac zapisany\n2.Nazwa(z wielkiej litery)\n3.Przebieg silnika w km\n4.Pieciocyfrowy numer\n\n");
	printf("Zeby zakonczyc wpisywanie nalezy wpisac pusta nazwe folderu(skladajaca sie z jednej spacji)\n\n");
	int j;
	char tmp;
	int i;
	while(1){
		i=0;
		printf("Folder: ");
		tmp=' ';
		j=0;
		char *dzial=malloc(16*sizeof(char));
		for(i=0;i<16;i++)
			dzial[i]='\0';
		while(tmp!='\n')
		{
			tmp=getc(stdin);
			if(j==0 && tmp==' ')
				return;
			if(tmp!='\n')
				dzial[j]=tmp;
			j++;
			if(j==17){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				wpisz(Main);
				return;
			}
		}
		dzial[j]='\0';
		i=0;
		dzial[i]=toupper(dzial[i]);
		if(dzial[i]<'A'||dzial[i]>'Z'){
			printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
			wpisz(Main);
			return;
		}
		for(i=1;i<j-1;i++)
		{
			if(((dzial[i]<'a'||dzial[i]>'z')&& (dzial[i]!=' ')&&(dzial[i]<'A'||dzial[i]>'Z'))||((dzial[i-1]!=' '&&(dzial[i]>'A'&&dzial[i]<'Z')))){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				wpisz(Main);
				return;
			}
		}
		Kraj *tym;
		tym=Main->first;
		while(tym!=NULL){
				if(!strcmp(tym->kraj,dzial))
						break;
				tym=tym->nast;
		}
		if(tym==NULL){
			printf("Nie ma takiego folderu. Prosze o ponowne wpisanie");
			wpisz(Main);
			return;
		}
		E *przekaz=malloc(sizeof *przekaz);
		Nazwa(tym,przekaz);
		Przebieg(przekaz);
		Numer(Main,przekaz);
}
}

		/*Wczytanie nazw*/ 
	
	void Nazwa(Kraj *tym3, E *przekaz){
		int j;
		char tmp;
		int i;
		char nazwanie[16];
		for(i=0;i<16;i++)
			nazwanie[i]='\0';
		printf("Nazwa: ");
		tmp=' ';
		j=0;
		while(tmp!='\n')
		{
			tmp=getc(stdin);
			if(tmp!='\n')
				nazwanie[j]=tmp;
			j++;
			if(j==17){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Nazwa(tym3,przekaz);
				return;
			}

		}
		nazwanie[j]='\0';
		nazwanie[0]=toupper(nazwanie[0]);
		if(nazwanie[0]<'A' || nazwanie[0]>'Z'){
			printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Nazwa(tym3,przekaz);
			return;
		}
		i=1;
		int spacja=0;
	/*zmienna do sprawdzania czy w nazwie wystapila juz spacja*/
		for(i=1;i<j-1;i++){
			if(naz==' ')
				spacja=1;
			if(spacja==0){
				if((naz<'A'||naz>'Z')&&(naz<'a'||naz>'z')&&(naz!=' ')){
					printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Nazwa(tym3,przekaz);
					return;
				}
			}
			else{
				if((naz<'A'||naz>'Z')&&(naz<'a'||naz>'z')&&(naz!=' ')&&(naz<'0'||naz>'9')){
					printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Nazwa(tym3,przekaz);
					return;
				}
			}
		}
		if(tym3->beg==NULL){
			przekaz->next=NULL;
			tym3->beg=przekaz;
		}
		else{
			E *tym;
			tym=tym3->beg;
			if(strcmp(tym->dane.nazwa,nazwanie)>0){
				tym3->beg=przekaz;
				przekaz->next=tym;
			}
			else{
				while(tym->next!=NULL){
					if(strcmp(tym->next->dane.nazwa,nazwanie)>0){
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
		for(i=0;i<strlen(nazwanie);i++)
			przekaz->dane.nazwa[i]=nazwanie[i];
		for(i=strlen(nazwanie);i<16;i++)
			przekaz->dane.nazwa[i]='\0';
	}
	
	/*Wczytywanie przebiegow*/
void Przebieg(E *sam){
		int j;
		char tmp;
		int i;
		char bieg[8];
		for(i=0;i<8;i++)
			bieg[i]='\0';
		printf("Przebieg: ");
		tmp=' ';
		j=0;
		while(tmp!='\n')
		{
			tmp=getc(stdin);
			if(tmp!='\n')
				bieg[j]=tmp;
			j++;
			if(j==8){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Przebieg(sam);
				return;
			}
		}
		bieg[j]='\0';
		i=0;
		if(prz=='0'){
			printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
			Przebieg(sam);
			return;
		}
		for(i=0;i<j-1;i++)
		{
			if(prz<'0'||prz>'9'){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Przebieg(sam);
				return;
			}
		}
		for(i=0;i<strlen(bieg);i++)
			sam->dane.przebieg[i]=bieg[i];
		for(i=strlen(bieg);i<8;i++)
			sam->dane.przebieg[i]='\0';
}
		/*Wczytanie numerow*/ /*Nie zawsze znajduje ze juz byl*/
void Numer(Mhan *Main,E *sam){
		int j;
		char tmp;
		int i;
		char mer[6];
		printf("Numer: ");
		tmp=' ';
		j=0;
		while(tmp!='\n')
		{
			tmp=getc(stdin);
			if(tmp!='\n')
				mer[j]=tmp;
			j++;
			if(j==7){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Numer(Main,sam);
				return;
			}
		}
		mer[j]='\0';
		i=0;
		for(i=0;i<j-1;i++)
		{
			if(num<'0'||num>'9' || j!=6){
				printf("Wczytano nieprawidlowy napis. Wpisz dane tego pojazdu od nowa\n");
				Numer(Main,sam);
				return;
			}
		}
		Kraj *spr;
		spr=Main->first;
		while(spr!=NULL){
				E *rek;
				rek=spr->beg;
				while(rek!=NULL){
					if(strncmp(rek->dane.numer,mer,5)==0){
							printf("Ten numer został juz wczytany. Prosze o ponowne wpisanie.\n");
							Numer(Main,sam);
							return;
					}
					rek=rek->next;
				}
				spr=spr->nast;
		}
	for(i=0;i<5;i++)
		sam->dane.numer[i]=mer[i];
	sam->dane.numer[5]='\0';
}
