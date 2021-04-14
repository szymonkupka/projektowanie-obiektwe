#include <iostream>
using namespace std;

namespace Name {		//Deklaracja przestrzenii nazw Name.
	namespace Space {	//Deklaracja przestrzeni nazw Space.
		class Biblioteka {		//Klasa Biblioteka znajduj¹ca siê przestrzeni nazw Name::Space.
		public:
			Biblioteka() = delete;	//Usuniêcie konstruktora domyœlnego, nie jest potrzebny do wykonania zadania.
			Biblioteka(string Nazwa, char* lok_miast ) : nazwa(Nazwa) {			//Konstruktor parametryzuj¹cy przypisuj¹cy polu nazwa wartoœæ za pomoc¹ listy parametryzuj¹cej oraz przyjmuj¹cy wskaŸnik do tablicy znaków (nazwê tablicy).
				lokalizacja_miasto = new char [strlen(lok_miast)+1];			//Utworzenie dynamicznej tablicy znaków o takiej samej d³ugoœci jak tablica wys³ana jako parametr.
				strcpy_s(lokalizacja_miasto, strlen(lok_miast)+1, lok_miast);	//Kopiowanie tekstu z tablicy przes³anej jako parametr do tablicy bêd¹cej polem klasy. 
				cout <<"Utworzono obiekt biblioteka: " << nazwa << ",  " << lokalizacja_miasto << endl;	//Wypisanie danych klasy na ekran.
			}
			~Biblioteka() {
				delete[] lokalizacja_miasto;		//Dealokacja pamiêci tablicy utworzonej w konstruktorze.
				lokalizacja_miasto = nullptr;		//Ustawienie wartoœci wskaŸnika na nullptr.
			}
			struct Ksiazka {	//Struktura Ksiazka bêd¹ca sk³adow¹ klasy Biblioteka.
				string tytul;	//Pola publiczne zadeklarowane w zadaniu.
				string autor;
				int liczba_stron;
				static int licznik;	//Statyczne pole licznik odpowiadaj¹ce za zliczanie iloœci obiektów utworzonych.

				Ksiazka() = delete;	//Usuniêcie domyœlnego konstruktora, nie jest potrzebny do wykonania zadania.
				Ksiazka(string Tytul, string Autor, int L_str) : tytul(Tytul), autor(Autor), liczba_stron(L_str) {		//Konstruktor parametryzuj¹cy, przypisuj¹ce wszystkie zmienne jako lista parametryzuj¹ca. 
					cout<< "Utworzono obiekt ksiazka: " << '"' << tytul << '"' << ' ' << autor << ", liczba stron: " << liczba_stron << endl;	//Wypisanie danych struktury na ekran.
					licznik++;	//Zwiêkszenie wartoœci licznika o jeden podczas tworzenia obiektu. 
				}
				~Ksiazka() {
					licznik--;	//Zmiejszenie wartoœci licznika o jeden podczas destrukcji obiektu.
				}
				void wypisz() {	//Funkcja wypisz() wypisuje na ekran wszystkie dane struktury. 
					cout << '"' << tytul << '"' << ' ' << autor << ", liczba stron: " << liczba_stron << endl; 
				}
			};
			//Statyczna metoda wypisuje element tablicy obiektów typu Ksiazka, który posiada posiada najwiêksz¹ liczbê stron. Metoda przyjmuje jako argumenty wskaŸnik do tablicy oraz jej rozmiar. Metoda niewykorzystuje ¿adnych pól klasy Biblioteka
			//w której zosta³a utworzona, korzysta tylko ze zmiennych, które zosta³y wys³ane jako argumenty, wiêc dziêki temu ¿e jest statyczna mo¿e zostaæ wywo³ana bez u¿ycia obiektu typu Biblioteka.
			static void wypiszNajwiecejStron(Ksiazka* tab, int licznik) {	
				int max_indeks = 0;		//Zmienna pomocnicza, przechowuje indeks elementu tablicy, dla którego liczba stron jest najwiêksza.
				for (int i = 1; i < licznik; i++)	//Pêtla iteruj¹ca ka¿dy element tablicy.
				{
					if (tab[i].liczba_stron > tab[max_indeks].liczba_stron)		//Porównywanie liczby stron i-tego elementu tablicy z liczb¹ stron elementu, który aktualnie posiada najwiêksz¹ liczbê stron
						max_indeks = i;											//Gdy liczba stron i-tego elementu jest wiêksza to za max_indeks podstawiamy obecn¹ wartoœæ i.
				}
				cout << "Najwiecej stron posiada ksiazka: " << endl;
				for (int i = 0; i < licznik; i++)			//Ta pêtla jest potrzebna w przypadku wystêpowania wiêcej ni¿ jednej ksi¹¿ki o takiej samej najwiêkszej iloœci stron, wtedy ka¿da z nich zostanie wypisana na ekran.
				{
					if(tab[max_indeks].liczba_stron == tab[i].liczba_stron)
						tab[i].wypisz();
				}
			}
			
		private:	//Pola zadeklarowane w zadaniu.
			string nazwa;
			char *lokalizacja_miasto;	//WskaŸnik potrzebny do inicjalizacji tablicy znaków.
		};
	}
	class Czytelnik {
		friend void wypiszWypozyczone(Czytelnik&);	//Dekalaracja przyjaŸni funkcji wypiszWypozyczone(Czytelnik&) z klas¹ Czytelnik. 
	public:
		//Konstruktor domyœlny i parametryzuj¹cy, przypisuje wartoœci polom za pomoc¹ listy parametryzuj¹cej, gdy argumenty nie zostaj¹ przes³ane wtedy u¿ywane s¹ wartoœci domyœlne dla ka¿dego parametru.
		Czytelnik(string Imie = "Jan", string Nazwisko = "Kowalski", int licz_ksiaz = 0) : imie(Imie), nazwisko(Nazwisko), liczba_wypozyczonych_ksiazek(licz_ksiaz) { 
			cout << "Utworzono obiekt czytelnik: " << imie << " " << nazwisko << " " << liczba_wypozyczonych_ksiazek << endl; //Wypisanie danych obiektu na ekran.
			wypozyczone_ksiazki = new Space::Biblioteka::Ksiazka* [liczba_wypozyczonych_ksiazek];	//Utworzenie nowej tablicy dynamicznej wskaŸników typu Ksiazka o wielkoœci liczby wypozyczonych ksiazek wyslanej jako parametr.
			for (int i = 0; i < liczba_wypozyczonych_ksiazek; i++)	//"Wyzerowanie" tablicy czyli ustalenie wartoœci ka¿dego elementu jako nullptr
			{
				wypozyczone_ksiazki[i] = nullptr;
			}
		}
		void wypozyczKsiazke(Space::Biblioteka::Ksiazka& ksiazka) {	//Funckja potrzebna do przypisania ksi¹¿ki do danego czytelnika.
			bool przypisanie=false;		//Zmienna pomocnicza typu logicznego, która przechowuje informacjê czy przypisano dan¹ ksi¹¿kê do czytelnika.
			for (int i = 0; i < liczba_wypozyczonych_ksiazek; i++) //Pêtla, która przypisuje dla pierwszego znalezionego pustego elementu tablicy adres do obiektu typu Ksiazka, pêtla jest przerywana gdy warunek siê spe³ni, poniewa¿ u¿ytkownik wypo¿ycza tylko jedn¹ ksi¹¿kê. 
			{
				if (wypozyczone_ksiazki[i] == nullptr) {
					wypozyczone_ksiazki[i] = &ksiazka;
					przypisanie = true;		//Zmiana wartoœci logicznej na true jeœli nast¹pi³o przypisanie.
					break;
				}
			}
			if (!przypisanie)	//Jeœli nie nast¹pi³o przypisanie, czyli tablica jest pe³na wtedy wypisywany jest b³¹d.
				cout << "Nieprzypisano ksiazki do czytelnika" << endl;
		}
		~Czytelnik() {
			delete[] wypozyczone_ksiazki;	//Dealokacja pamiêci tablicy wskaŸników utworzonej w konstruktorze.
			wypozyczone_ksiazki = nullptr;	//Przypisanie wartoœci nullptr wskaŸnikowi wypozyczone_ksiazki.
		}
	private:	//Zmienne zadeklarowane w zadaniu.
		string imie;
		string nazwisko;
		int liczba_wypozyczonych_ksiazek;
		Space::Biblioteka::Ksiazka** wypozyczone_ksiazki;	//WskaŸnik do wskaŸnika typu Ksiazka potrzebny do alokacji tablicy dynamicznej wskaŸników.
	};
	void wypiszWypozyczone(Czytelnik& cz) {		//Funkcja zaprzyjaŸniona z klas¹ Czytelnik, wypisuje wszystkie elementy tablicy dynamicznej wypozyczone_ksiazki.
		cout << "Wypozyczone ksiazki: " << endl;
		for (int i = 0; i < cz.liczba_wypozyczonych_ksiazek; i++)
		{
			cz.wypozyczone_ksiazki[i]->wypisz();
		}
	}
}

typedef Name::Space::Biblioteka Lib;	//Utworzenie aliasu do klasy Biblioteka znajduj¹cej siê w przestrzeni nazw Name::Space.
int Lib::Ksiazka::licznik = 0;			//Zainicjowanie wartoœci statycznej zmiennej licznik znajduj¹cej siê w strukturze Ksi¹¿ka.

int main() {
	//Utworzenie obiektu klasy Biblioteka i przypisanie mu wartoœci konstruktorem.
	Lib Jag("Biblioteka Jagiellonska", (char*)"Krakow");	
	cout << endl;
	//Utworzenie czteroelementowej tablicy obiektów typu Ksiazka i przypisanie im wartoœci.
	Lib::Ksiazka tab_ksiaz[4]  { {"Chlopi, czesc pierwsza - Jesien", "Wladyslaw Reymont", 114}, {"Chlopi, czesc druga - Zima", "Wladyslaw Reymont", 123},
									{"Chlopi, czesc trzecia - Wiosna", "Wladyslaw Reymont", 149}, {"Chlopi, czesc czwarta - Lato", "Wladyslaw Reymont", 170} };
	cout << endl;
	//Utworzenie obiektu typu Czytelnik i przypisanie mu wartoœci konstruktorem.
	Name::Czytelnik Maciek("Maciej", "Boryna", 3);
	//Przypisanie trzech ksi¹¿ek, które s¹ elementami tablicy tab_ksiaz, obiektowi Maciek za pomoc¹ funkcji wypozyczKsiazke(Ksiazka&).
	Maciek.wypozyczKsiazke(tab_ksiaz[0]); Maciek.wypozyczKsiazke(tab_ksiaz[2]); Maciek.wypozyczKsiazke(tab_ksiaz[1]);
	cout << endl;
	//Wypisanie wypo¿yczonych ksi¹¿ek dziêki funkcji wypiszWypozyczone(Czytelnik&).
	Name::wypiszWypozyczone(Maciek);
	cout << endl;
	//Wypisanie ksi¹zki (ksi¹¿ek) o najwiêkszej iloœci stron, dziêki statycznej metodzie wypiszNajwiecejStron(Ksiazka*, int) klasy Biblioteka.
	Lib::wypiszNajwiecejStron(tab_ksiaz, 4);
	//Wypisanie iloœci obiektów struktry Ksiazka.
	cout << endl << "Liczba obiektow typu ksiazka: " << Lib::Ksiazka::licznik << endl;

	return 0;
}