#include <iostream>

using namespace std;

struct Film {		//Struktura o odpowiednich polach zadeklarowanych w treœci zadania. Konstruktor nie zosta³ zadeklarowany jawnie poniewa¿ nie jest on potrzebny do wykonania zadania.
	string tytul;
	string glowni_aktorzy[2];
	int rok_produkcji;
	int czas_trwania;
	void wypisz() {		//Metoda wypisuj¹ca dane struktury na ekran.
		cout << '"' << tytul << '"' << " staring: " << glowni_aktorzy[0] << " and " << glowni_aktorzy[1] << " Rok produkcji: " << rok_produkcji << "r. " << czas_trwania << " min" << endl;
	}
};
class Klient {
public:
	Klient() = delete;	//Konstruktor domyœlny zosta³ usuniêty, nie jest on potrzebny do wykonania zadania.
	Klient(string Imie, string Nazwisko, int Limit_min, int L_wyp_film) : imie(Imie), nazwisko(Nazwisko), limit_minut(Limit_min), limit_wypozyczonych_filmow(L_wyp_film) { //Konstruktor parametryzuj¹cy, przypisuj¹cy przes³ane argumenty odpowiednim polom prywatnym.
		wypozyczone_filmy = new Film * [limit_wypozyczonych_filmow];	//Utworzenie nowej tablicy dynamicznej wskaŸników struktury Film o wielkoœci limitu wypo¿yczonych filmów.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)
		{
			wypozyczone_filmy[i] = nullptr;		//Pêtla iteruj¹ca po ka¿dym elemencie tablicy wypozyczone_filmy, przypisuj¹c wartoœæ nullptr.
		}
	}
	~Klient() {
		delete[] wypozyczone_filmy;		//Destruktor odpowiedzialny za dealokacje pamiêci przeznaczonej dla dynamicznej tablicy wskaŸników wypozyczone_filmy.
		wypozyczone_filmy = nullptr;	//Ustawienie wartoœci wskaŸnika wypozyczone_filmy na nullptr.
	}

	void pokazInfo(){	//Metoda wypisuj¹ca na ekran dane obiektu klasy Klient.
		cout << imie << " " << nazwisko << " Limit minut: " << limit_minut <<"min, Limit wypozyczonych filmow: "<<limit_wypozyczonych_filmow<< ", Wypozyczone filmy: " << endl;
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)
		{
			if (wypozyczone_filmy[i] != nullptr) {	//Pêtla iteruj¹ca po ka¿dym elemencie tablicy wypozyczone_filmy, w przypadku natrafienia na element którego wskaŸnik nie jest ustawiony na nullptr, wypisuje dane takiego elementu za pomoc¹ metody wypisz() struktury Film.
				wypozyczone_filmy[i]->wypisz();
			}
		}
	}
	//Metoda zmieniaj¹ca pola imie i nazwisko. Nazwisko jest pierwszym argumentem, a imie drugim posiadaj¹cym wartoœæ domyœln¹ dziêki temu mo¿emy zmieniæ nazwisko klienta przesy³aj¹c tylko jeden argument do metody, bez koniecznoœci nadpisywania imienia
	//co jest przydatne, poniewa¿ zazwyczaj zmieniane jest nazwisko a nie imiê klienta np w przypadku zmiany nazwiska po œlubie.
	void zmienDane(string Nazwisko, string Imie="") {	
		if (Imie.length() >= 3)	//Dodatkowe zabezpieczenie, argument zostanie przypisany tylko gdy d³ugoœæ imienia bêdzie niekrótsza od trzech - nie ma polskiego imienia krótszego od 3 liter.
			imie = Imie;
		if (Nazwisko.length()>=2)	//Dodatkowe zabezpieczenie, argument zostanie przypisany tylko gdy d³ugoœæ nazwiska bêdzie niekrótsza od dwóch - nie ma polskiego nazwiska krótszego ni¿ 2 litery.
			nazwisko = Nazwisko;
	}
	void wypozyczFilm(Film& f) {	//Metoda przypisuj¹ca wskaŸnik na obiekt struktury Film do tablicy dynamicznej wypozyczone_filmy.
		bool tab_free = false;		//Zmienna pomocnicza, która pos³u¿y nam do okreœlenia czy tablica nie jest przepe³niona i czy istnieje element którego wartoœæ jest ustalona na nullptr.
		bool movie_already_rented = false;	//Zmienna pomocnicza, potrzebna do okreœlenia czy dany argument przes³any do metody jest ju¿ elementem tablicy, co zapobiega dublowaniu siê tych samych elementów w tablicy.
		int tab_free_index = 0;		//Zmienna pomocnicza, która bêdzie przechowywa³a indeks ostatniego wolnego elementu tablicy wypozyczone_filmy.
		int suma_minut = f.czas_trwania;	//Zmienna pomocnicza, która bêdzie zlicza³a liczbê czas trwania obiektów w tablicy wypozyczone_filmy, wartoœæ pocz¹tkowa to czas trwania przes³anego argumentu.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wypozyczone_filmy.
		{
			if (wypozyczone_filmy[i] == nullptr) {	//Je¿eli dany element jest "pusty" czyli wartoœæ wskaŸnika to nullptr to wtedy ustawiamy wartoœæ tab_free na true oraz przypisujemy wartoœæ i zmiennej tab_free_index.
				tab_free = true;
				tab_free_index = i;
			}
			else if (wypozyczone_filmy[i] == &f) {	//Je¿eli referencja na argument przes³any do funkcji jest równa wskaŸnikowi, który jest elementem tablicy, czyli gdy jest próba wypo¿yczenia tego samego filmu to wtedy 
				movie_already_rented = true;		//wartoœæ movie_already_rented jest zmieniana na true i przerywana jest pêtla.
				break;
			}
			else	//Gdy ¿adne z powy¿szych warunków nie jest spe³niona to jest do sumy_minut dodawana wartoœæ czas_trwania elementu tablicy. 
				suma_minut += wypozyczone_filmy[i]->czas_trwania;
		}
		if (movie_already_rented)	//Je¿eli dany film zosta³ ju¿ wypo¿yczony to zwracany jest komunikat i film nie zostaje wypo¿yczony po raz kolejny.
			cout << "Ten film zostal juz wypozyczony" << endl;
		else if (tab_free) {	//W przeciwnym wypadku gdy tablica wypozyczone_filmy zawiera "puste" elementy to:
			if (suma_minut <= limit_minut) {	//Jeœli suma_minut nie przekracza limitu_minut to przypisywany jest wskaŸnik na obiekt ostatniemu wolnemu elementowi tablicy.
				wypozyczone_filmy[tab_free_index] = &f;
			}
			else	//Przeciwnym przypadku wyœwietlany jest komunikat o przekroczeniu limitu minut oraz podawana jest wartoœæ tego przekroczenia.
				cout << "Przekroczono limit minut o: " << suma_minut - limit_minut << "min, nie wypozyczono filmu" << endl;
		}
		else	//Jeœli tablica nie jest pusta to wyœwietlany jest komunikat o przekroczeniu limitu wypo¿yczonych filmów.
			cout << "Przekroczono liczbe wypozyczonych filmow" << endl;
	}
	void zwrotFilmu(Film& f) {
		bool deleted = false;	//Zmienna pomocnicza, która pozwala sprawdziæ czy element wys³any jako argument zosta³ usuniêty z tablicy.
		for (int i = 0; i < limit_wypozyczonych_filmow; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wypozyczone_filmy.
		{
			if (wypozyczone_filmy[i] == &f) {	//Je¿eli element wskaŸnik w tablicy jest równy referencji argumentu to wtedy wartoœæ tego elementu jest ustawiana na nullptr, a zmiennej delete wartoœæ true.
				wypozyczone_filmy[i] = nullptr;	
				deleted = true;
				break;	//Gdy to jest prawda pêtla jest przerywana, poniewa¿ w metodzie wypozyczFilm() zosta³y zawarte warunki przez które elementy tablicy nie mog¹ siê dublowaæ, czyli w przypadku znalezienia jednego elementu mamy pewnoœæ ¿e nie ma nastêpnego elementu o tej samej wartoœci.
			}
		}
		if (deleted)	//Je¿eli film zosta³ usuniêty z tablicy to wypisywany jest komunikat o pomyœlnym zwrocie filmu.
			cout << "Zwrocono film " << '"' << f.tytul << '"' << endl;
		else		//W przeciwnym wypadku zostaje wyœwietlony komunikat o nieudanej próbie zwrócenia filmu, poniewa¿ dany film nie by³ elementem tablicy wypozyczone_filmy.
			cout << "Podany film nie byl wypozyczony" << endl;
	}
private:	//Pola prywatne zdefiniowane w zadaniu.
	string imie;		
	string nazwisko;
	int limit_minut;
	const int limit_wypozyczonych_filmow;
	Film** wypozyczone_filmy;	//WskaŸnik do wskaŸnika obiektu struktury Film potrzebny do zainicjowania dynamicznej tablicy.
};

int main() {
	//Utworzenie obiektu struktury Film i zanicjowanie jego wartoœci.
	Film f1 = { "Znachor", {"Jerzy Binczycki", "Anna Dymna"}, 1981, 128 };
	//Utworzenie 4 elementowej tablicy obiektów struktury Film i zanicjowanie jego wartoœci.
	Film tab_f[] = { {"Kapitan Bomba: Kutapokalipsa", {"Kapitan Bomba", "Sultan Kosmitow"}, 2012, 54},{"Kapitan Bomba: Zemsta Faraona", {"Kapitan Bomba", "Boguslaw Lecina"}, 2012, 90},
						{ "Wsciekle piesci weza", { "Bartosz Walaszek", "Lukasz Walaszek" }, 2006, 72 }, {"Zenek", {"Krzysztof Czeczot", "Jakub Zajac"}, 2020, 120}};
	//Wypisanie danych obiektu f1 za pomoc¹ metody wypisz().
	f1.wypisz();
	for (int i = 0; i < 4; i++)
	{
		tab_f[i].wypisz(); //Wypisanie danych wszystkich obiektów tablicy tab_f za pomoc¹ metody wypisz() i pêtli for iteruj¹cej po ka¿dym elemencie tablicy.
	}
	cout << endl;
	//Utworzenie 2 elementowej tablicy obiektów klasy Klient i zainicjowanie ich wartoœci.
	Klient tab_k[] = { {"Rafal", "Wilczur", 500, 5}, {"Ferdynand", "Lipski", 360, 3} };
	//Wyœwietlenie na ekran informacji obiektów tablicy tab_k za pomoc¹ metody pokazInfo().
	tab_k[0].pokazInfo();
	tab_k[1].pokazInfo();
	//Zmiana nazwiska drugiego elementu tablicy za pomoc¹ metody zmienDane(), a nestêpnie wyœwietlenie na ekranie informacji obiektu.
	tab_k[1].zmienDane("Kiepski");
	tab_k[1].pokazInfo();
	cout << endl;
	//Wypo¿yczenie 3 filmów drugiemu klientowi w tablicy tab_k poprzez funckjê wypozyczFilm(), a nastêpnie wyœwietlenie informacji klienta na ekran.
	tab_k[1].wypozyczFilm(f1); tab_k[1].wypozyczFilm(tab_f[1]); tab_k[1].wypozyczFilm(tab_f[3]);
	tab_k[1].pokazInfo();
	cout << endl;
	//Zwrot filmu f1, na obiekcie drugim tablicy Klientów za pomoc¹ funkcji zwrotFilmu(), a nastêpnie wyœwietlenie informacji klienta na ekran.
	tab_k[1].zwrotFilmu(f1);
	tab_k[1].pokazInfo();
	return 0;
}