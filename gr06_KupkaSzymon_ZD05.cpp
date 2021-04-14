#include <iostream>

using namespace std;

struct Film {		//Struktura o odpowiednich polach zadeklarowanych w tre�ci zadania. Konstruktor nie zosta� zadeklarowany jawnie poniewa� nie jest on potrzebny do wykonania zadania.
	string tytul;
	string glowni_aktorzy[2];
	int rok_produkcji;
	int czas_trwania;
	void wypisz() {		//Metoda wypisuj�ca dane struktury na ekran.
		cout << '"' << tytul << '"' << " staring: " << glowni_aktorzy[0] << " and " << glowni_aktorzy[1] << " Rok produkcji: " << rok_produkcji << "r. " << czas_trwania << " min" << endl;
	}
};
class Klient {
public:
	Klient() = delete;	//Konstruktor domy�lny zosta� usuni�ty, nie jest on potrzebny do wykonania zadania.
	Klient(string Imie, string Nazwisko, int Limit_min, int L_wyp_film) : imie(Imie), nazwisko(Nazwisko), limit_minut(Limit_min), limit_wypozyczonych_filmow(L_wyp_film) { //Konstruktor parametryzuj�cy, przypisuj�cy przes�ane argumenty odpowiednim polom prywatnym.
		wypozyczone_filmy = new Film * [limit_wypozyczonych_filmow];	//Utworzenie nowej tablicy dynamicznej wska�nik�w struktury Film o wielko�ci limitu wypo�yczonych film�w.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)
		{
			wypozyczone_filmy[i] = nullptr;		//P�tla iteruj�ca po ka�dym elemencie tablicy wypozyczone_filmy, przypisuj�c warto�� nullptr.
		}
	}
	~Klient() {
		delete[] wypozyczone_filmy;		//Destruktor odpowiedzialny za dealokacje pami�ci przeznaczonej dla dynamicznej tablicy wska�nik�w wypozyczone_filmy.
		wypozyczone_filmy = nullptr;	//Ustawienie warto�ci wska�nika wypozyczone_filmy na nullptr.
	}

	void pokazInfo(){	//Metoda wypisuj�ca na ekran dane obiektu klasy Klient.
		cout << imie << " " << nazwisko << " Limit minut: " << limit_minut <<"min, Limit wypozyczonych filmow: "<<limit_wypozyczonych_filmow<< ", Wypozyczone filmy: " << endl;
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)
		{
			if (wypozyczone_filmy[i] != nullptr) {	//P�tla iteruj�ca po ka�dym elemencie tablicy wypozyczone_filmy, w przypadku natrafienia na element kt�rego wska�nik nie jest ustawiony na nullptr, wypisuje dane takiego elementu za pomoc� metody wypisz() struktury Film.
				wypozyczone_filmy[i]->wypisz();
			}
		}
	}
	//Metoda zmieniaj�ca pola imie i nazwisko. Nazwisko jest pierwszym argumentem, a imie drugim posiadaj�cym warto�� domy�ln� dzi�ki temu mo�emy zmieni� nazwisko klienta przesy�aj�c tylko jeden argument do metody, bez konieczno�ci nadpisywania imienia
	//co jest przydatne, poniewa� zazwyczaj zmieniane jest nazwisko a nie imi� klienta np w przypadku zmiany nazwiska po �lubie.
	void zmienDane(string Nazwisko, string Imie="") {	
		if (Imie.length() >= 3)	//Dodatkowe zabezpieczenie, argument zostanie przypisany tylko gdy d�ugo�� imienia b�dzie niekr�tsza od trzech - nie ma polskiego imienia kr�tszego od 3 liter.
			imie = Imie;
		if (Nazwisko.length()>=2)	//Dodatkowe zabezpieczenie, argument zostanie przypisany tylko gdy d�ugo�� nazwiska b�dzie niekr�tsza od dw�ch - nie ma polskiego nazwiska kr�tszego ni� 2 litery.
			nazwisko = Nazwisko;
	}
	void wypozyczFilm(Film& f) {	//Metoda przypisuj�ca wska�nik na obiekt struktury Film do tablicy dynamicznej wypozyczone_filmy.
		bool tab_free = false;		//Zmienna pomocnicza, kt�ra pos�u�y nam do okre�lenia czy tablica nie jest przepe�niona i czy istnieje element kt�rego warto�� jest ustalona na nullptr.
		bool movie_already_rented = false;	//Zmienna pomocnicza, potrzebna do okre�lenia czy dany argument przes�any do metody jest ju� elementem tablicy, co zapobiega dublowaniu si� tych samych element�w w tablicy.
		int tab_free_index = 0;		//Zmienna pomocnicza, kt�ra b�dzie przechowywa�a indeks ostatniego wolnego elementu tablicy wypozyczone_filmy.
		int suma_minut = f.czas_trwania;	//Zmienna pomocnicza, kt�ra b�dzie zlicza�a liczb� czas trwania obiekt�w w tablicy wypozyczone_filmy, warto�� pocz�tkowa to czas trwania przes�anego argumentu.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wypozyczone_filmy.
		{
			if (wypozyczone_filmy[i] == nullptr) {	//Je�eli dany element jest "pusty" czyli warto�� wska�nika to nullptr to wtedy ustawiamy warto�� tab_free na true oraz przypisujemy warto�� i zmiennej tab_free_index.
				tab_free = true;
				tab_free_index = i;
			}
			else if (wypozyczone_filmy[i] == &f) {	//Je�eli referencja na argument przes�any do funkcji jest r�wna wska�nikowi, kt�ry jest elementem tablicy, czyli gdy jest pr�ba wypo�yczenia tego samego filmu to wtedy 
				movie_already_rented = true;		//warto�� movie_already_rented jest zmieniana na true i przerywana jest p�tla.
				break;
			}
			else	//Gdy �adne z powy�szych warunk�w nie jest spe�niona to jest do sumy_minut dodawana warto�� czas_trwania elementu tablicy. 
				suma_minut += wypozyczone_filmy[i]->czas_trwania;
		}
		if (movie_already_rented)	//Je�eli dany film zosta� ju� wypo�yczony to zwracany jest komunikat i film nie zostaje wypo�yczony po raz kolejny.
			cout << "Ten film zostal juz wypozyczony" << endl;
		else if (tab_free) {	//W przeciwnym wypadku gdy tablica wypozyczone_filmy zawiera "puste" elementy to:
			if (suma_minut <= limit_minut) {	//Je�li suma_minut nie przekracza limitu_minut to przypisywany jest wska�nik na obiekt ostatniemu wolnemu elementowi tablicy.
				wypozyczone_filmy[tab_free_index] = &f;
			}
			else	//Przeciwnym przypadku wy�wietlany jest komunikat o przekroczeniu limitu minut oraz podawana jest warto�� tego przekroczenia.
				cout << "Przekroczono limit minut o: " << suma_minut - limit_minut << "min, nie wypozyczono filmu" << endl;
		}
		else	//Je�li tablica nie jest pusta to wy�wietlany jest komunikat o przekroczeniu limitu wypo�yczonych film�w.
			cout << "Przekroczono liczbe wypozyczonych filmow" << endl;
	}
	void zwrotFilmu(Film& f) {
		bool deleted = false;	//Zmienna pomocnicza, kt�ra pozwala sprawdzi� czy element wys�any jako argument zosta� usuni�ty z tablicy.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wypozyczone_filmy.
		{
			if (wypozyczone_filmy[i] == &f) {	//Je�eli element wska�nik w tablicy jest r�wny referencji argumentu to wtedy warto�� tego elementu jest ustawiana na nullptr, a zmiennej delete warto�� true.
				wypozyczone_filmy[i] = nullptr;	
				deleted = true;
				break;	//Gdy to jest prawda p�tla jest przerywana, poniewa� w metodzie wypozyczFilm() zosta�y zawarte warunki przez kt�re elementy tablicy nie mog� si� dublowa�, czyli w przypadku znalezienia jednego elementu mamy pewno�� �e nie ma nast�pnego elementu o tej samej warto�ci.
			}
		}
		if (deleted)	//Je�eli film zosta� usuni�ty z tablicy to wypisywany jest komunikat o pomy�lnym zwrocie filmu.
			cout << "Zwrocono film " << '"' << f.tytul << '"' << endl;
		else		//W przeciwnym wypadku zostaje wy�wietlony komunikat o nieudanej pr�bie zwr�cenia filmu, poniewa� dany film nie by� elementem tablicy wypozyczone_filmy.
			cout << "Podany film nie byl wypozyczony" << endl;
	}
private:	//Pola prywatne zdefiniowane w zadaniu.
	string imie;		
	string nazwisko;
	int limit_minut;
	const int limit_wypozyczonych_filmow;
	Film** wypozyczone_filmy;	//Wska�nik do wska�nika obiektu struktury Film potrzebny do zainicjowania dynamicznej tablicy.
};

int main() {
	//Utworzenie obiektu struktury Film i zanicjowanie jego warto�ci.
	Film f1 = { "Znachor", {"Jerzy Binczycki", "Anna Dymna"}, 1981, 128 };
	//Utworzenie 4 elementowej tablicy obiekt�w struktury Film i zanicjowanie jego warto�ci.
	Film tab_f[] = { {"Kapitan Bomba: Kutapokalipsa", {"Kapitan Bomba", "Sultan Kosmitow"}, 2012, 54},{"Kapitan Bomba: Zemsta Faraona", {"Kapitan Bomba", "Boguslaw Lecina"}, 2012, 90},
						{ "Wsciekle piesci weza", { "Bartosz Walaszek", "Lukasz Walaszek" }, 2006, 72 }, {"Zenek", {"Krzysztof Czeczot", "Jakub Zajac"}, 2020, 120}};
	//Wypisanie danych obiektu f1 za pomoc� metody wypisz().
	f1.wypisz();
	for (int i = 0; i < 4; i++)
	{
		tab_f[i].wypisz(); //Wypisanie danych wszystkich obiekt�w tablicy tab_f za pomoc� metody wypisz() i p�tli for iteruj�cej po ka�dym elemencie tablicy.
	}
	cout << endl;
	//Utworzenie 2 elementowej tablicy obiekt�w klasy Klient i zainicjowanie ich warto�ci.
	Klient tab_k[] = { {"Rafal", "Wilczur", 500, 5}, {"Ferdynand", "Lipski", 360, 3} };
	//Wy�wietlenie na ekran informacji obiekt�w tablicy tab_k za pomoc� metody pokazInfo().
	tab_k[0].pokazInfo();
	tab_k[1].pokazInfo();
	//Zmiana nazwiska drugiego elementu tablicy za pomoc� metody zmienDane(), a nest�pnie wy�wietlenie na ekranie informacji obiektu.
	tab_k[1].zmienDane("Kiepski");
	tab_k[1].pokazInfo();
	cout << endl;
	//Wypo�yczenie 3 film�w drugiemu klientowi w tablicy tab_k poprzez funckj� wypozyczFilm(), a nast�pnie wy�wietlenie informacji klienta na ekran.
	tab_k[1].wypozyczFilm(f1); tab_k[1].wypozyczFilm(tab_f[1]); tab_k[1].wypozyczFilm(tab_f[3]);
	tab_k[1].pokazInfo();
	cout << endl;
	//Zwrot filmu f1, na obiekcie drugim tablicy Klient�w za pomoc� funkcji zwrotFilmu(), a nast�pnie wy�wietlenie informacji klienta na ekran.
	tab_k[1].zwrotFilmu(f1);
	tab_k[1].pokazInfo();
	return 0;
}