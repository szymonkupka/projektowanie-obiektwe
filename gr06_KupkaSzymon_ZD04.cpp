#include <iostream>
using namespace std;

namespace Name {		//Deklaracja przestrzenii nazw Name.
	namespace Space {	//Deklaracja przestrzeni nazw Space.
		class Biblioteka {		//Klasa Biblioteka znajduj�ca si� przestrzeni nazw Name::Space.
		public:
			Biblioteka() = delete;	//Usuni�cie konstruktora domy�lnego, nie jest potrzebny do wykonania zadania.
			Biblioteka(string Nazwa, char* lok_miast ) : nazwa(Nazwa) {			//Konstruktor parametryzuj�cy przypisuj�cy polu nazwa warto�� za pomoc� listy parametryzuj�cej oraz przyjmuj�cy wska�nik do tablicy znak�w (nazw� tablicy).
				lokalizacja_miasto = new char [strlen(lok_miast)+1];			//Utworzenie dynamicznej tablicy znak�w o takiej samej d�ugo�ci jak tablica wys�ana jako parametr.
				strcpy_s(lokalizacja_miasto, strlen(lok_miast)+1, lok_miast);	//Kopiowanie tekstu z tablicy przes�anej jako parametr do tablicy b�d�cej polem klasy. 
				cout <<"Utworzono obiekt biblioteka: " << nazwa << ",  " << lokalizacja_miasto << endl;	//Wypisanie danych klasy na ekran.
			}
			~Biblioteka() {
				delete[] lokalizacja_miasto;		//Dealokacja pami�ci tablicy utworzonej w konstruktorze.
				lokalizacja_miasto = nullptr;		//Ustawienie warto�ci wska�nika na nullptr.
			}
			struct Ksiazka {	//Struktura Ksiazka b�d�ca sk�adow� klasy Biblioteka.
				string tytul;	//Pola publiczne zadeklarowane w zadaniu.
				string autor;
				int liczba_stron;
				static int licznik;	//Statyczne pole licznik odpowiadaj�ce za zliczanie ilo�ci obiekt�w utworzonych.

				Ksiazka() = delete;	//Usuni�cie domy�lnego konstruktora, nie jest potrzebny do wykonania zadania.
				Ksiazka(string Tytul, string Autor, int L_str) : tytul(Tytul), autor(Autor), liczba_stron(L_str) {		//Konstruktor parametryzuj�cy, przypisuj�ce wszystkie zmienne jako lista parametryzuj�ca. 
					cout<< "Utworzono obiekt ksiazka: " << '"' << tytul << '"' << ' ' << autor << ", liczba stron: " << liczba_stron << endl;	//Wypisanie danych struktury na ekran.
					licznik++;	//Zwi�kszenie warto�ci licznika o jeden podczas tworzenia obiektu. 
				}
				~Ksiazka() {
					licznik--;	//Zmiejszenie warto�ci licznika o jeden podczas destrukcji obiektu.
				}
				void wypisz() {	//Funkcja wypisz() wypisuje na ekran wszystkie dane struktury. 
					cout << '"' << tytul << '"' << ' ' << autor << ", liczba stron: " << liczba_stron << endl; 
				}
			};
			//Statyczna metoda wypisuje element tablicy obiekt�w typu Ksiazka, kt�ry posiada posiada najwi�ksz� liczb� stron. Metoda przyjmuje jako argumenty wska�nik do tablicy oraz jej rozmiar. Metoda niewykorzystuje �adnych p�l klasy Biblioteka
			//w kt�rej zosta�a utworzona, korzysta tylko ze zmiennych, kt�re zosta�y wys�ane jako argumenty, wi�c dzi�ki temu �e jest statyczna mo�e zosta� wywo�ana bez u�ycia obiektu typu Biblioteka.
			static void wypiszNajwiecejStron(Ksiazka* tab, int licznik) {	
				int max_indeks = 0;		//Zmienna pomocnicza, przechowuje indeks elementu tablicy, dla kt�rego liczba stron jest najwi�ksza.
				for (int i = 1; i < licznik; i++)	//P�tla iteruj�ca ka�dy element tablicy.
				{
					if (tab[i].liczba_stron > tab[max_indeks].liczba_stron)		//Por�wnywanie liczby stron i-tego elementu tablicy z liczb� stron elementu, kt�ry aktualnie posiada najwi�ksz� liczb� stron
						max_indeks = i;											//Gdy liczba stron i-tego elementu jest wi�ksza to za max_indeks podstawiamy obecn� warto�� i.
				}
				cout << "Najwiecej stron posiada ksiazka: " << endl;
				for (int i = 0; i < licznik; i++)			//Ta p�tla jest potrzebna w przypadku wyst�powania wi�cej ni� jednej ksi��ki o takiej samej najwi�kszej ilo�ci stron, wtedy ka�da z nich zostanie wypisana na ekran.
				{
					if(tab[max_indeks].liczba_stron == tab[i].liczba_stron)
						tab[i].wypisz();
				}
			}
			
		private:	//Pola zadeklarowane w zadaniu.
			string nazwa;
			char *lokalizacja_miasto;	//Wska�nik potrzebny do inicjalizacji tablicy znak�w.
		};
	}
	class Czytelnik {
		friend void wypiszWypozyczone(Czytelnik&);	//Dekalaracja przyja�ni funkcji wypiszWypozyczone(Czytelnik&) z klas� Czytelnik. 
	public:
		//Konstruktor domy�lny i parametryzuj�cy, przypisuje warto�ci polom za pomoc� listy parametryzuj�cej, gdy argumenty nie zostaj� przes�ane wtedy u�ywane s� warto�ci domy�lne dla ka�dego parametru.
		Czytelnik(string Imie = "Jan", string Nazwisko = "Kowalski", int licz_ksiaz = 0) : imie(Imie), nazwisko(Nazwisko), liczba_wypozyczonych_ksiazek(licz_ksiaz) { 
			cout << "Utworzono obiekt czytelnik: " << imie << " " << nazwisko << " " << liczba_wypozyczonych_ksiazek << endl; //Wypisanie danych obiektu na ekran.
			wypozyczone_ksiazki = new Space::Biblioteka::Ksiazka* [liczba_wypozyczonych_ksiazek];	//Utworzenie nowej tablicy dynamicznej wska�nik�w typu Ksiazka o wielko�ci liczby wypozyczonych ksiazek wyslanej jako parametr.
			for (int i = 0; i < liczba_wypozyczonych_ksiazek; i++)	//"Wyzerowanie" tablicy czyli ustalenie warto�ci ka�dego elementu jako nullptr
			{
				wypozyczone_ksiazki[i] = nullptr;
			}
		}
		void wypozyczKsiazke(Space::Biblioteka::Ksiazka& ksiazka) {	//Funckja potrzebna do przypisania ksi��ki do danego czytelnika.
			bool przypisanie=false;		//Zmienna pomocnicza typu logicznego, kt�ra przechowuje informacj� czy przypisano dan� ksi��k� do czytelnika.
			for (int i = 0; i < liczba_wypozyczonych_ksiazek; i++) //P�tla, kt�ra przypisuje dla pierwszego znalezionego pustego elementu tablicy adres do obiektu typu Ksiazka, p�tla jest przerywana gdy warunek si� spe�ni, poniewa� u�ytkownik wypo�ycza tylko jedn� ksi��k�. 
			{
				if (wypozyczone_ksiazki[i] == nullptr) {
					wypozyczone_ksiazki[i] = &ksiazka;
					przypisanie = true;		//Zmiana warto�ci logicznej na true je�li nast�pi�o przypisanie.
					break;
				}
			}
			if (!przypisanie)	//Je�li nie nast�pi�o przypisanie, czyli tablica jest pe�na wtedy wypisywany jest b��d.
				cout << "Nieprzypisano ksiazki do czytelnika" << endl;
		}
		~Czytelnik() {
			delete[] wypozyczone_ksiazki;	//Dealokacja pami�ci tablicy wska�nik�w utworzonej w konstruktorze.
			wypozyczone_ksiazki = nullptr;	//Przypisanie warto�ci nullptr wska�nikowi wypozyczone_ksiazki.
		}
	private:	//Zmienne zadeklarowane w zadaniu.
		string imie;
		string nazwisko;
		int liczba_wypozyczonych_ksiazek;
		Space::Biblioteka::Ksiazka** wypozyczone_ksiazki;	//Wska�nik do wska�nika typu Ksiazka potrzebny do alokacji tablicy dynamicznej wska�nik�w.
	};
	void wypiszWypozyczone(Czytelnik& cz) {		//Funkcja zaprzyja�niona z klas� Czytelnik, wypisuje wszystkie elementy tablicy dynamicznej wypozyczone_ksiazki.
		cout << "Wypozyczone ksiazki: " << endl;
		for (int i = 0; i < cz.liczba_wypozyczonych_ksiazek; i++)
		{
			cz.wypozyczone_ksiazki[i]->wypisz();
		}
	}
}

typedef Name::Space::Biblioteka Lib;	//Utworzenie aliasu do klasy Biblioteka znajduj�cej si� w przestrzeni nazw Name::Space.
int Lib::Ksiazka::licznik = 0;			//Zainicjowanie warto�ci statycznej zmiennej licznik znajduj�cej si� w strukturze Ksi��ka.

int main() {
	//Utworzenie obiektu klasy Biblioteka i przypisanie mu warto�ci konstruktorem.
	Lib Jag("Biblioteka Jagiellonska", (char*)"Krakow");	
	cout << endl;
	//Utworzenie czteroelementowej tablicy obiekt�w typu Ksiazka i przypisanie im warto�ci.
	Lib::Ksiazka tab_ksiaz[4]  { {"Chlopi, czesc pierwsza - Jesien", "Wladyslaw Reymont", 114}, {"Chlopi, czesc druga - Zima", "Wladyslaw Reymont", 123},
									{"Chlopi, czesc trzecia - Wiosna", "Wladyslaw Reymont", 149}, {"Chlopi, czesc czwarta - Lato", "Wladyslaw Reymont", 170} };
	cout << endl;
	//Utworzenie obiektu typu Czytelnik i przypisanie mu warto�ci konstruktorem.
	Name::Czytelnik Maciek("Maciej", "Boryna", 3);
	//Przypisanie trzech ksi��ek, kt�re s� elementami tablicy tab_ksiaz, obiektowi Maciek za pomoc� funkcji wypozyczKsiazke(Ksiazka&).
	Maciek.wypozyczKsiazke(tab_ksiaz[0]); Maciek.wypozyczKsiazke(tab_ksiaz[2]); Maciek.wypozyczKsiazke(tab_ksiaz[1]);
	cout << endl;
	//Wypisanie wypo�yczonych ksi��ek dzi�ki funkcji wypiszWypozyczone(Czytelnik&).
	Name::wypiszWypozyczone(Maciek);
	cout << endl;
	//Wypisanie ksi�zki (ksi��ek) o najwi�kszej ilo�ci stron, dzi�ki statycznej metodzie wypiszNajwiecejStron(Ksiazka*, int) klasy Biblioteka.
	Lib::wypiszNajwiecejStron(tab_ksiaz, 4);
	//Wypisanie ilo�ci obiekt�w struktry Ksiazka.
	cout << endl << "Liczba obiektow typu ksiazka: " << Lib::Ksiazka::licznik << endl;

	return 0;
}