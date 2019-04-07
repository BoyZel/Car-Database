#include "dane.h"

void pliki(Mhan *Main){
	printf("UWAGA. Po wpisaniu komendy wczytaj dotychczasowa baza zostanie usunieta\n");
	char tmp;
	char komenda[11];
	char plik[16];
	char rozszerzenie[4];
	int i=0;
	tmp=getc(stdin);
	while(tmp!=' '){
		if(i>9){
			printf("Podano zbyt wiele znakow\n");
			return;
		}
		komenda[i]=tmp;
		i++;
		tmp=getc(stdin);
	}
	komenda[i]='\0';
	i=0;
	tmp=getc(stdin);
	while(tmp!='.'){
		if(i>14){
			printf("Podano zbyt wiele znakow\n");
			return;
		}
		plik[i]=tmp;
		i++;
		tmp=getc(stdin);
	}
	int j=0;
	plik[i]='.';
	i++;
	tmp=getc(stdin);
	while(tmp!='\n'){
		if(j>2){
			printf("podano zbyt wiele znakowa\n");
			return;
		}
		plik[i]=tmp;
		rozszerzenie[j]=tmp;
		i++;
		j++;
		tmp=getc(stdin);
	}
	plik[i]='\0';
	rozszerzenie[j]='\0';
	if(!strcmp(komenda,"zapisz")){
		if(!strcmp(rozszerzenie,"txt")){
			zapisztxt(Main,plik);
			return;
		}
		if(!strcmp(rozszerzenie,"ula")){
			zapiszula(Main,plik);
			return;
		}
	}
	if(!strcmp(komenda,"wczytaj")){
		if(!strcmp(rozszerzenie,"txt")){
			wczytajtxt(Main,plik);
			return;
		}
		if(!strcmp(rozszerzenie,"ula")){
			wczytajbin(Main,plik);
			return;
		}
	}
	printf("Nierozpoznana komenda\n");
}
void zapisztxt(Mhan *Main,char *plik){
	FILE *out;
	out=fopen(plik,"w");
	Kraj *tmp=Main->first;
	while(tmp!=NULL){
		E *rekord=tmp->beg;
		while(rekord!=NULL){
			fprintf(out,"%s\t",rekord->dane.nazwa);
			fprintf(out,"%s\t",rekord->dane.numer);
			fprintf(out,"%s\t",rekord->dane.przebieg);
			fprintf(out,"%s\n",tmp->kraj);
			rekord=rekord->next;
		}
		tmp=tmp->nast;
	}
	fclose(out);
}
void wczytajtxt(Mhan *Main,char *plik){
	FILE *in;
	in=fopen(plik,"r");
	if(in==NULL){
		printf("Nie ma takiego pliku\n");
		return;
	}
	Kraj *tmp=Main->first;
	Kraj *tmp2;
	if(tmp!=NULL)
		tmp2=tmp->nast;
	while(tmp!=NULL){
		free(tmp);
		tmp=tmp2;
		if(tmp!=NULL)
			tmp2=tmp->nast;
	}
	Main->first=NULL;
	char znak;
	znak=getc(in);
	Kraj *tmp3=malloc(sizeof *tmp3);
	while(znak!=EOF){
		E *rekord=malloc(sizeof *rekord);
		rekord->next=NULL;
		char dzl[16];
		int i=0;
		while(znak!='\t'){
			rekord->dane.nazwa[i]=znak;
			i++;
			znak=getc(in);
		}
		rekord->dane.nazwa[i]='\0';
		fscanf(in,"%s\t%s\t",rekord->dane.numer,rekord->dane.przebieg);
		znak=getc(in);
		i=0;
		while(znak!='\n'){
			dzl[i]=znak;
			i++;
			znak=getc(in);
		}
		znak=getc(in);
		while(i<16){
			dzl[i]='\0';
			i++;
		}
		int sp=0;
		if(Main->first==NULL){
			for(i=0;i<strlen(dzl);i++)
				tmp3->kraj[i]=dzl[i];
			Main->first=tmp3;
			tmp3->beg=rekord;
			sp=1;
		}
		else
			if(strcmp(dzl,tmp3->kraj)){
				Kraj *tmp2=malloc(sizeof *tmp2);
				tmp3->nast=tmp2;
				tmp3=tmp2;
				sp=1;
				for(i=0;i<strlen(dzl);i++)
					tmp3->kraj[i]=dzl[i];
				tmp3->beg=rekord;
			}
		tmp3->nast=NULL;
		if(sp==0){
			E *chwila=tmp3->beg;
			while(chwila->next!=NULL)
				chwila=chwila->next;
			chwila->next=rekord;
		}
	}
	fclose(in);
}
void haslo(char *klucz){
	char tmp;
	tmp=getc(stdin);
	int i=0;
	while(tmp!='\n'){
		if(i>15)
			return;
		klucz[i]=tmp-31;
		tmp=getc(stdin);
		i++;
	}
	while(i<16){
		klucz[i]='\0';
		i++;
	}
}


void zapiszula(Mhan *Main,char *plik){
	FILE *out;
	printf("Prosze o wpisanie hasla: ");
	out=fopen(plik,"wb");
	char klucz[16];
	haslo(klucz);
	fwrite(klucz,sizeof(char),16,out);
	printf("\n");
	int j;
	Kraj *tmp=Main->first;
	while(tmp!=NULL){
		char dzl[16];
		for(j=0;j<16;j++)
			dzl[j]=tmp->kraj[j]+4;
		E *rekord=tmp->beg;
		while(rekord!=NULL){
			char nzw[16],przbg[8],nmr[6];
			for(j=0;j<16;j++)
				nzw[j]=rekord->dane.nazwa[j]+4;
			for(j=0;j<8;j++)
				przbg[j]=rekord->dane.przebieg[j]+4;
			for(j=0;j<6;j++)
				nmr[j]=rekord->dane.numer[j]+4;
			fwrite(nzw,sizeof(char),16,out);
			fwrite(nmr,sizeof(char),6,out);
			fwrite(przbg,sizeof(char),8,out);
			fwrite(dzl,sizeof(char),16,out);
			rekord=rekord->next;
		}
		tmp=tmp->nast;
	}
	fclose(out);
}
void wczytajbin(Mhan *Main,char *plik){
	char nmr2[6];
	FILE *in;
	int licznik=0;
	int j;
	in=fopen(plik,"r");
	if(in==NULL){
		printf("Nie ma takiego pliku\n");
		return;
	}
	char klucz1[16],klucz2[16];
	printf("Ten plik jest zabezpieczony haslem. Prosze o jego podanie: ");
	haslo(klucz1);
	fread(klucz2,sizeof(char),16,in);
	if(strcmp(klucz1,klucz2)){
		printf("Nieprawidlowe haslo");
		return;
	}
	Kraj *tmp=Main->first;
	Kraj *tmp2;
	if(tmp!=NULL)
		tmp2=tmp->nast;
	while(tmp!=NULL){
		free(tmp);
		tmp=tmp2;
		if(tmp!=NULL)
			tmp2=tmp->nast;
	}
	Main->first=NULL;
	Kraj *tmp3=malloc(sizeof *tmp3);
	while(!feof(in)){
		E *rekord=malloc(sizeof *rekord);
		rekord->next=NULL;
		char dzl[16];
		int i=0;
		char nzw[16],przbg[8],nmr[6];
		fread(nzw,sizeof(char),16,in);
		fread(nmr,sizeof(char),6,in);
		fread(przbg,sizeof(char),8,in);
		fread(dzl,sizeof(char),16,in);
		for(j=0;j<16;j++)
			rekord->dane.nazwa[j]=nzw[j]-4;
		for(j=0;j<8;j++)
			rekord->dane.przebieg[j]=przbg[j]-4;
		for(j=0;j<6;j++)
			rekord->dane.numer[j]=nmr[j]-4;
		if(licznik!=0)
		if(!strncmp(rekord->dane.numer,nmr2,5))
			return;
		for(j=0;j<16;j++)
			dzl[j]=dzl[j]-4;
		for(j=0;j<6;j++)
			nmr2[j]=rekord->dane.numer[j];
		int sp=0;
		if(Main->first==NULL){
			for(i=0;i<strlen(dzl);i++)
				tmp3->kraj[i]=dzl[i];
			Main->first=tmp3;
			tmp3->beg=rekord;
			sp=1;
		}
		else
			if(strcmp(dzl,tmp3->kraj)){
				Kraj *tmp2=malloc(sizeof *tmp2);
				tmp3->nast=tmp2;
				tmp3=tmp2;
				sp=1;
				for(i=0;i<strlen(dzl);i++)
					tmp3->kraj[i]=dzl[i];
				tmp3->beg=rekord;
			}
		tmp3->nast=NULL;
		if(sp==0){
			E *chwila=tmp3->beg;
			while(chwila->next!=NULL)
				chwila=chwila->next;
			chwila->next=rekord;
		}
		licznik++;
	}
	fclose(in);
}
