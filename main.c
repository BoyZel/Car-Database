#include "dane.h"
int main()
{
	/*int n=0;
	int i=0;
	int j=0;*/
	Mhan Main;
	Main.first=NULL;
	char wybor=' ';
	int licznik=0;
	while(wybor!='9'){
		wybor=' ';
		licznik++;
		printf("\n");
		if(licznik==1)
		/*qsort(t,n,sizeof(auta), comparator1);*/
		printf("Prosze wybrac jedna z opcji wpisujac cyfre jej odpowiadajaca:\n");
		printf("0 - Wyswietlenie zawartosci wybranego katalogu\n");
		printf("1 - Wprowadzenie danych\n");
		printf("2 - Utworzenie nowego katalogu\n");
		printf("3 - Wyswietlenie rekordow wg wybranego klucza\n");
		printf("4 - Usuniecie wybranego katalogu\n");
		printf("5 - Zmiana nazwy wybranego katalogu\n");
		printf("6 - Poprawa danych juz wprowadzonych rekordow\n");
		printf("7 - Przeniesienie rekordow do wybranego katalogu\n");
		printf("8 - Wyswietlenie listy katalogow\n");
		printf("9 - Wyjscie z programu\n");
		printf("p - Przejscie do trybu wpisywania komend dotyczacych manipulacji na plikach\n");
		while((wybor<'0' || wybor>'9')&&wybor!='p')
			scanf("%c",&wybor);
		getc(stdin);
		if(wybor=='0')
			wyswietlkatalog(&Main);
		if(wybor=='1'){
			wpisz(&Main);
		}
		if(wybor=='2'){
			stworz(&Main);
		}
		if(wybor=='3'){
			wypisz(Main);
		}
		if(wybor=='4'){
			usun(&Main);
		}
		if(wybor=='5')
			zmien_nazwe(&Main);
		if(wybor=='6'){
			popraw(&Main);
		}
		if(wybor=='7')
			przenies(&Main);
		if(wybor=='8')
			wyswietlnazwy(&Main);
		if(wybor=='p')
			pliki(&Main);
		if(wybor=='9'){
			printf("Czy na pewno chcesz wyjsc? y/n ");
			char tmp2=getc(stdin);
			if(tmp2=='y')
				break;
			else
				wybor=' ';

		}
	}
	return 0;
}
