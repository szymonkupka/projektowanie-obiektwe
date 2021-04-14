#include <iostream>
#include <ctime>

using namespace std;

float roundTwoDigitsMinPay(float& numb); //Deklaracja funkcji, kt�ra b�dzie oblicza�a wysoko�� wynagrodzenia, po uzyskaniu mno�nika jako i argument, a nast�pnie zwraca�a warto�� pensji z dok�adno�cia dw�ch miejsc po przecinku.

class Osoba {
public:
	Osoba(string Imie, string Nazwisko, int rok_ur) : imie(Imie), nazwisko(Nazwisko), rok_urodzenia(rok_ur) {}	//Konstruktor parametryzuj�cy, otrzymane parametry przypisuje odpowiednim polom chroniomym dzi�ki li�cie inicjalizacyjnej.
	Osoba(Osoba& os) : imie(os.imie), nazwisko(os.nazwisko), rok_urodzenia(os.rok_urodzenia) {}		//Konstruktor kopiuj�cy, kopiuje warto�ci przes�anego obiektu do p�l chronionych dzi�ki li�cie inicjalizacyjnej.
	int wiek() {	//Metoda zwracaj�ca wiek rocznikowy danego obiektu, wykonuje to dzi�ki pobraniu obecnego czasu z systemu.
		time_t curr_time = time(NULL);	//Utworzenie zmiennej typu time_t kt�ra przechowuje liczb� od 1 stycznia 1970 roku i przypisanie jej warto�ci time(NULL) kt�ra zwraca obecny czas.
		tm date;	//Utworzenie obiektu struktury tm, kt�ra b�dzie przechowywa�a obecn� dat� kalendarzow�.
		localtime_s(&date, &curr_time);	//Konwersja zmiennej typu time_t do obiektu struktury tm.
		return date.tm_year + 1900 - rok_urodzenia;	//Zwrot wieku rocznikowego czyli dodanie do pola tm_year obiektu date 1900 poniewa� rok jest w tej strukturze liczony od 1900, a nast�pnie odj�cie roku urodzenia.
	}
	virtual ostream& out(ostream& output) {	//Definicja wirtualnej metody, kt�ra pos�u�y nam do prawid�owego wy�wietlenia danych obiekt�w klasy podstawowej jak i klas pochodnych dzi�ki operatorowi przeci��onemu operatorowi << dla klasy bazowej Osoba.
		output << imie << " " << nazwisko << " " << rok_urodzenia <<"r.";	//Przes�anie danych do strumienia.
		return output;	//Zwrot strumienia output.
	}
	friend ostream& operator<<(ostream& ostr, Osoba& os); //Deklaracja przyja�ni klasy Osoba z przeci��eniem operatora <<.

protected: //Pola chronione zadeklarowane w tre�ci zadania.
	string imie;
	string nazwisko;
	int rok_urodzenia;
};

class Pracownik : public Osoba { //Klasa pochodna Pracownik, kt�ra dziedziczy publicznie po klasie Osoba.
public:
	Pracownik(string Imie, string Nazwisko, int rok_ur, string woj) : Osoba(Imie, Nazwisko, rok_ur), wojewodztwo(woj) {} //Konstruktor parametryzuj�cy, przypisuj�cy przes�ane warto�ci polom chronionym dzi�ki li�cie parametryzuj�cej wykorzystuj�c konstruktor klasy podstawowej.
	static float getPlacaMin() {	//Metoda statyczna zwracaj�ca warto�� statycznego pola chronionego placa_minimalna, dzi�ki byciu statyczn� metoda ta mo�e zosta� wywo�ana bez inicjalizacji obiektu klasy Pracownik.
		return placa_minimalna;
	}
protected: //Pola chronione zadeklarowane w tre�ci zadania.
	string wojewodztwo;
	static const float placa_minimalna;
};

class Informatyk : public Pracownik { //Klasa pochodna, kt�ra dziedziczy publicznie po klasie Pracownik, jest to dziedziczenie wielokrotne, poniewa� klasa Pracownik jest ju� klas� pochodn� od klasy Osoba.
public:
	//Konstruktor parametryzuj�cy, przypisuje warto�ci odpowiednim polom prywatnym i chronionym dzi�ki li�cie parametryzuj�cej oraz konstruktorowi klasy nadrz�dnej Pracownik. R�wnie� do zainicjalizowania warto�ci pola pensja jest u�ywana 
	//funkcja roundTwoDigitsMinPay(float&) dzi�ki kt�rej obliczone wynagrodzenie pracownika b�dzie zaokr�glone do dw�ch miejsc po przecinku.
	Informatyk(string Imie, string Nazwisko, int rok_ur, string woj, string spec, float Mnoznik) : Pracownik(Imie, Nazwisko, rok_ur, woj), specjalizacja(spec), mnoznik(Mnoznik), pensja(roundTwoDigitsMinPay(Mnoznik)) {}
	//Konstruktor kopiuj�cy, kt�ry kopiuje odpowiednie warto�ci dzi�ki li�cie parametryzuj�cej i konstruktorowi klasy nadrz�dnej, nie jest konieczne u�ycie funkcji roundTwoDigitsMinPay(float&), poniewa� obiekt przes�any jako parametr posiada ju� warto�� zaokr�glon�.
	Informatyk(Informatyk& i) : Pracownik(i.imie, i.nazwisko, i.rok_urodzenia, i.wojewodztwo), specjalizacja(i.specjalizacja), mnoznik(i.mnoznik), pensja(i.pensja) {}
	//Konstruktor kopiuj�cy, kt�ry poza obiektem swojego typu ma trzy inne parametry, kt�re pozwol� zainicjowa� pola imie, nazwisko i rok_urodzenia innymi warto�ciami ni� obiektu przes�anego jako argument. Inicjalizacja odbywa si� za pomoc� listy parametryzuj�cej.
	//Ponowne u�ycie funkcji zaokr�glaj�cej nie jest konieczne, poniewa� przes�any obiekt posiada ju� zaokr�glon� warto��.
	Informatyk(Informatyk& i, string Imie, string Nazwisko, int rok_ur) : Pracownik(Imie, Nazwisko, rok_ur, i.wojewodztwo), specjalizacja(i.specjalizacja), mnoznik(i.mnoznik), pensja(i.pensja) {}
	virtual ostream& out(ostream& output) { //Redefinicja metody out dla klasy pochodnej Informatyk, kt�ra jest potrzebna do wy�wietlenia danych dzi�ki przeci��eniu operatora <<.
		Osoba::out(output);	//Wywo�anie metody out dla klasy bazowej Osoba.
		output<<" "<< specjalizacja << " " << pensja << " zl. " << wojewodztwo; //Przekazanie do strumienia dodatkowych danych dost�pnych tylko w klasie pochodnej.
		return output;	//Zwrot strumienia.
	}
	void setWoj(string woj) {	//Metoda, kt�ra przyjmuje argument typu string i przypisuje go polu prywatnemu wojewodztwo.
		wojewodztwo = woj;
	}
private: //Pola prywatne zadeklarowane w tre�ci zadania.
	string specjalizacja;
	float mnoznik;
	float pensja;
};

class Emeryt : public Osoba { //Klasa pochodna Emeryt, kt�ra dziedziczy publicznie po klasie Osoba.
public:
	//Konstruktor parametryzuj�cy przyjmuj�cy warto�ci domy�lne, inicjalizuje warto�ci polom chroniomym i prywatnym dzi�ki li�cie parametryzuj�cej i konstruktowi klasy nadrz�dnej Osoba.
	Emeryt(string Imie = "Ferdynand", string Nazwisko="Kiepski", int rok_ur=1950, float Emerytura = 1026) : Osoba(Imie, Nazwisko, rok_ur), emerytura(Emerytura) {}
	//Konstruktor parametryzuj�cy, kt�ry dzi�ki li�cie parametryzuj�cej i konstruktorowi kopiuj�cemu klasy nadrz�dnej Osoba kopiuje warto�ci obiektu klasy Osoba i inicjalizuje pole emerytura.
	Emeryt(Osoba& os, float emeryt = 1026) : Osoba(os), emerytura(emeryt) {}
	virtual ostream& out(ostream& output) { //Redefinicja metody out dla klasy pochodnej Emeryt, kt�ra jest potrzebna do wy�wietlenia danych dzi�ki przeci��eniu operatora <<.
		Osoba::out(output); //Wywo�anie metody out dla klasy bazowej Osoba.
		output << " Emerytura: " << emerytura << " zl.";	//Przekazanie do strumienia dodatkowych danych dost�pnych tylko w klasie pochodnej.
		return output;	//Zwrot strumienia.
	}
private:	//Pole prywatne zadeklarowane w tre�ci zadania.
	float emerytura;
};

const float Pracownik::placa_minimalna = 2250;	//Zainicjowanie zmiennej statycznej placa_minimalna klasy Pracownik.

ostream& operator<<(ostream& output, Osoba& os) { //Definicja przeci��enia operatora << dla klasy Osoba, kt�ry wypisuje jej pola chronione.
	if (&os != nullptr)	//Sprawdzenie czy referencja do obiektu nie jest r�wna nullptr, czyli czy dany obiekt jest zainicjalizowany. Potrzebne przy p�niejszym wypisywaniu tablicy obiekt�w.
		os.out(output);	//Je�eli referencja nie r�wna si� nullptr to wywo�ywana jest metoda out(ostream&) na przes�anym obiekcie, kt�ra prze�le dane do strumienia w zale�no�ci od klasy obiektu.
	return output;	//Zwrot strumienia.
}

float roundTwoDigitsMinPay(float& numb) {	//Funkcja kt�ra przyjmuje mno�nik pensji minimalnej, a nast�pnie zwraca warto�� pensji zaokr�glon� do dw�ch miejsc po przecinku zgodnie z zasadami zaokr�glania.
	//Pomno�enie warto�ci p�acy minimalnej przez mno�nik co daje nam warto�� dok�adn�, pomno�enie przez 100 aby przesun�� dwie cyfry po przecinku do przodu, nast�pnie dodanie 0.5 kt�re pomo�e nam zaokr�gli� zgodnie z zasadami zaokr�glenia. 
	//Liczba ta jest konwertowana z float do int wi�c obcinane s� cyfry po przecinku.
	int pom_i = static_cast <int> ((Pracownik::getPlacaMin() * numb * 100) + 0.5);	
	//Liczb� t� konwertujemy do warto�ci float i dzielimy j� przez 100, przez co zwracana warto�� jest zaokr�glona do dw�ch miejsc po przecinku.
	return static_cast <float> (pom_i) / 100;
}
//Definicja funkcji, kt�ra przyjmuje tablic� wska�nik�w do klasy Osoba oraz jej rozmiar, sprawdza ilo�� os�b kt�rych wiek jest powy�ej 65 lat i kopiuje ich warto�ci do nowej tablicy dynamicznej, a z przes�anej tablicy usuwa ich. Funkcja zwraca wska�nik do 
//utworzonej tablicy dynamicznej. R�wnie� zmieniana jest warto�� przes�anego argumentu n, kt�ry po zako�czeniu funkcji b�dzie przechowywa� rozmiar utworzonej tablicy obiekt�w klasy Emeryt.
Emeryt* stworzEmerytow(Osoba** tab, int& n) {	 
	int sum_em = 0; //Zmienna pomocnicza, kt�ra zliczy ilo�� os�b kt�rych wiek jest powy�ej 65 lat.
	for (int i = 0; i < n; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do klasy Osoba tab.
	{
		if ((*tab[i]).wiek() > 65)	//Je�eli wiek danego elementu tablicy jest wi�kszy od 65 to wtedy iterowana jest zmienna sum_em o 1.
			sum_em++;
	}
	if (sum_em == 0) {	//Je�eli sum_em jest r�wny 0 to oznacza �e �aden element tablicy powy�ej 65 lat. Wtedy wypisywany jest odpowiedni komunikat b��du, n jest przypisywana warto�� 0, poniewa� ma on zwraca� rozmiar utworzonej tablicy. 
		cout << "W podanej tablicy nie znaleziono �adnych emeryt�w, b��d" << endl;
		n = 0;
		return nullptr; //Zwracana jest warto�� nullptr, czyli pusty wska�nik.
	}
	Emeryt* tab_em = new Emeryt[sum_em];	//Je�eli funckja nie zosta�a zako�czona to tworzona jest nowa dynamiczna tablica obiekt�w klasy Emeryt o rozmiarze sum_em.
	int i_newtable = 0;	//Zmienna pomocnicza potrzebna do iteracji tablicy tab_em w p�tli, kt�ra iteruje po tablicy tab.
	for (int i = 0; i < n; i++) //P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do klasy Osoba tab.
	{
		if ((*tab[i]).wiek() > 65) {	//Je�eli wiek danego elementu jest wi�kszy od wi�kszy od 65 to elementowi i_newtable tablicy obiekt�w typu Emeryt jest przypisywana warto�� na kt�r� wskazuje i-ty element tablicy tab
			tab_em[i_newtable] = Emeryt((*tab[i]), 1200 + i); //oraz warto�� 1200 (minimalna emerytura wg strony ZUSu) powi�kszona o warto�� i.
			tab[i] = nullptr;	//Przypisanie nullptr i-temu elementowi tablicy wska�nik�w typu Osoba tab.
			i_newtable++;		//Zwi�kszenie warto�ci i_newtable o jeden.
		}
	}
	n = sum_em;		//Zwrot rozmiaru utworzonej tablicy tab_em poprzez przypisanie tej warto�ci do zmiennej n kt�ra jest referencj� przes�an� jako argument.
	return tab_em;	//Zwrot wska�nika do utworzonej tablicy dynamicznej obiekt�w klasy Emeryt.

}
int main() {
	//Utworzonie obiektu i zainicjalizowanie jego warto�ci konstruktorem parametryzuj�cym klasy Osoba.
	cout << "Dane obiektu klasy Osoba: " << endl;
	Osoba o1("Mariusz", "Pudzianowski", 1977);
	//Wypisanie danych obiektu o1 dzi�ki przeci��eniu operatora <<.
	cout << o1 << endl;
	cout << endl;
	//Utworzonie obiektu i zainicjalizowanie jego warto�ci konstruktorem parametryzuj�cym klasy Informatyk. 
	cout << "Dane pierwszego obiektu klasy Informatyk:" << endl;
	Informatyk i1("Adam", "Malysz", 1977, "slaskie", "skoczek", 1.5555);
	//Wypisanie danych obiektu i1 dzi�ki przeci��eniu operatora << oraz wypisanie jego wieku rocznikowego dzi�ki metodzie wiek().
	cout << i1 << " Wiek: " << i1.wiek() << endl;
	cout << endl;
	//Utworzenie obiektu klasy Informatyk i zainicjowanie jego warto�ci poprzez konstruktor kopiuj�cy jednak zmieniaj�c pola imie, nazwisko i rok_urodzenia. Obiekt kopiuje warto�ci obiektu i1.
	cout << "Dane drugiego obiektu klasy Informatyk oraz jego wiek:" << endl;
	Informatyk i2(i1, "Chuck", "Norris", 1940);
	//Wypisanie danych obiektu i2 dzi�ki przeci��eniu operatora << oraz wypisanie jego wieku rocznikowego dzi�ki metodzie wiek().
	cout << i2 << " Wiek: " << i2.wiek() << endl;
	cout << endl;
	//Zmiana warto�ci pola wojewodztwo dzi�ki metodzie setWoj(string) na obiekcie i2 a nast�pnie wypisanie jego danych dzi�ki przeci��eniu operatora <<.
	cout << "Dane drugiego obiektu klasy Informatyk po zmianie wojewodztwa:" << endl;
	i2.setWoj("Oklahoma");
	cout << i2 << endl;
	cout << endl;
	//Utworzenie zmiennych pomocniczych, kt�re b�d� przechowywa�y rozmiary tablic dynamicznych.
	int n_os = 3, n_em = n_os;
	//Utworzenie dynamicznej tablicy wska�nik�w klasy Osoba o rozmiarze n_os.
	Osoba** tab_os = new Osoba* [n_os];
	//Przypisanie elementom tablicy referencji do obiekt�w klas Osoba o1 oraz Informatyk i1 i i2.
	tab_os[0] = &o1; tab_os[1] = &i1; tab_os[2] = &i2;
	//Wypisanie danych tab_os dzi�ki p�tli for i przeci��eniu operatora <<.
	cout << "Dane tablicy osob: " << endl;
	for (int i = 0; i < n_os; i++)
	{
		cout << (*tab_os[i]) << endl;
	}	
	cout << endl;
	//Utworzenie nowej tablicy dynamicznej obiekt�w typu Emeryt i przypisanie jej do wska�nika tab_em poprzez funkcj� stworzEmerytow(Osoba**,int&). Zmienna n_em zawiera rozmiar tablicy tab_os czyli argumentu funkcji, ale po jej zako�czeniu b�dzie przechowywa�
	//rozmiar nowo utworzonej tablicy.
	cout << "Dane tablicy emerytow, po jej utworzeniu:" << endl;
	Emeryt* tab_em = stworzEmerytow(tab_os, n_em);
	//Wypisanie danych tab_em dzi�ki p�tli for i przeci��eniu operatora <<.
	for (int i = 0; i < n_em; i++)
	{
		cout << tab_em[i] << endl;
	}
	cout << endl;
	cout << "Dane tablicy osob po utworzeniu tablicy emerytow:" << endl;
	//Wypisanie danych tab_os po zako�czeniu funkcji stworzEmerytow(Osoba**, int&), kt�rej ta tablica by�a argumentem.
	for (int i = 0; i < n_os; i++)
	{
		 cout << (*tab_os[i]) << endl;
	}
	//Dealokacja pami�ci przyznanej tablicom dynamicznym tab_os i tab_em.
	delete[] tab_os;
	delete[] tab_em;
	//Przypisanie warto�ci nullptr wska�nikom tab_os i tab_em.
	tab_os = nullptr;
	tab_em = nullptr;
	return 0;
}