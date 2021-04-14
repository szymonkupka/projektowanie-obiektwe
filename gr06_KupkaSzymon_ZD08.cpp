#include <iostream>
#include <ctime>

using namespace std;

float roundTwoDigitsMinPay(float& numb); //Deklaracja funkcji, która bêdzie oblicza³a wysokoœæ wynagrodzenia, po uzyskaniu mno¿nika jako i argument, a nastêpnie zwraca³a wartoœæ pensji z dok³adnoœcia dwóch miejsc po przecinku.

class Osoba {
public:
	Osoba(string Imie, string Nazwisko, int rok_ur) : imie(Imie), nazwisko(Nazwisko), rok_urodzenia(rok_ur) {}	//Konstruktor parametryzuj¹cy, otrzymane parametry przypisuje odpowiednim polom chroniomym dziêki liœcie inicjalizacyjnej.
	Osoba(Osoba& os) : imie(os.imie), nazwisko(os.nazwisko), rok_urodzenia(os.rok_urodzenia) {}		//Konstruktor kopiuj¹cy, kopiuje wartoœci przes³anego obiektu do pól chronionych dziêki liœcie inicjalizacyjnej.
	int wiek() {	//Metoda zwracaj¹ca wiek rocznikowy danego obiektu, wykonuje to dziêki pobraniu obecnego czasu z systemu.
		time_t curr_time = time(NULL);	//Utworzenie zmiennej typu time_t która przechowuje liczbê od 1 stycznia 1970 roku i przypisanie jej wartoœci time(NULL) która zwraca obecny czas.
		tm date;	//Utworzenie obiektu struktury tm, która bêdzie przechowywa³a obecn¹ datê kalendarzow¹.
		localtime_s(&date, &curr_time);	//Konwersja zmiennej typu time_t do obiektu struktury tm.
		return date.tm_year + 1900 - rok_urodzenia;	//Zwrot wieku rocznikowego czyli dodanie do pola tm_year obiektu date 1900 poniewa¿ rok jest w tej strukturze liczony od 1900, a nastêpnie odjêcie roku urodzenia.
	}
	virtual ostream& out(ostream& output) {	//Definicja wirtualnej metody, która pos³u¿y nam do prawid³owego wyœwietlenia danych obiektów klasy podstawowej jak i klas pochodnych dziêki operatorowi przeci¹¿onemu operatorowi << dla klasy bazowej Osoba.
		output << imie << " " << nazwisko << " " << rok_urodzenia <<"r.";	//Przes³anie danych do strumienia.
		return output;	//Zwrot strumienia output.
	}
	friend ostream& operator<<(ostream& ostr, Osoba& os); //Deklaracja przyjaŸni klasy Osoba z przeci¹¿eniem operatora <<.

protected: //Pola chronione zadeklarowane w treœci zadania.
	string imie;
	string nazwisko;
	int rok_urodzenia;
};

class Pracownik : public Osoba { //Klasa pochodna Pracownik, która dziedziczy publicznie po klasie Osoba.
public:
	Pracownik(string Imie, string Nazwisko, int rok_ur, string woj) : Osoba(Imie, Nazwisko, rok_ur), wojewodztwo(woj) {} //Konstruktor parametryzuj¹cy, przypisuj¹cy przes³ane wartoœci polom chronionym dziêki liœcie parametryzuj¹cej wykorzystuj¹c konstruktor klasy podstawowej.
	static float getPlacaMin() {	//Metoda statyczna zwracaj¹ca wartoœæ statycznego pola chronionego placa_minimalna, dziêki byciu statyczn¹ metoda ta mo¿e zostaæ wywo³ana bez inicjalizacji obiektu klasy Pracownik.
		return placa_minimalna;
	}
protected: //Pola chronione zadeklarowane w treœci zadania.
	string wojewodztwo;
	static const float placa_minimalna;
};

class Informatyk : public Pracownik { //Klasa pochodna, która dziedziczy publicznie po klasie Pracownik, jest to dziedziczenie wielokrotne, poniewa¿ klasa Pracownik jest ju¿ klas¹ pochodn¹ od klasy Osoba.
public:
	//Konstruktor parametryzuj¹cy, przypisuje wartoœci odpowiednim polom prywatnym i chronionym dziêki liœcie parametryzuj¹cej oraz konstruktorowi klasy nadrzêdnej Pracownik. Równie¿ do zainicjalizowania wartoœci pola pensja jest u¿ywana 
	//funkcja roundTwoDigitsMinPay(float&) dziêki której obliczone wynagrodzenie pracownika bêdzie zaokr¹glone do dwóch miejsc po przecinku.
	Informatyk(string Imie, string Nazwisko, int rok_ur, string woj, string spec, float Mnoznik) : Pracownik(Imie, Nazwisko, rok_ur, woj), specjalizacja(spec), mnoznik(Mnoznik), pensja(roundTwoDigitsMinPay(Mnoznik)) {}
	//Konstruktor kopiuj¹cy, który kopiuje odpowiednie wartoœci dziêki liœcie parametryzuj¹cej i konstruktorowi klasy nadrzêdnej, nie jest konieczne u¿ycie funkcji roundTwoDigitsMinPay(float&), poniewa¿ obiekt przes³any jako parametr posiada ju¿ wartoœæ zaokr¹glon¹.
	Informatyk(Informatyk& i) : Pracownik(i.imie, i.nazwisko, i.rok_urodzenia, i.wojewodztwo), specjalizacja(i.specjalizacja), mnoznik(i.mnoznik), pensja(i.pensja) {}
	//Konstruktor kopiuj¹cy, który poza obiektem swojego typu ma trzy inne parametry, które pozwol¹ zainicjowaæ pola imie, nazwisko i rok_urodzenia innymi wartoœciami ni¿ obiektu przes³anego jako argument. Inicjalizacja odbywa siê za pomoc¹ listy parametryzuj¹cej.
	//Ponowne u¿ycie funkcji zaokr¹glaj¹cej nie jest konieczne, poniewa¿ przes³any obiekt posiada ju¿ zaokr¹glon¹ wartoœæ.
	Informatyk(Informatyk& i, string Imie, string Nazwisko, int rok_ur) : Pracownik(Imie, Nazwisko, rok_ur, i.wojewodztwo), specjalizacja(i.specjalizacja), mnoznik(i.mnoznik), pensja(i.pensja) {}
	virtual ostream& out(ostream& output) { //Redefinicja metody out dla klasy pochodnej Informatyk, która jest potrzebna do wyœwietlenia danych dziêki przeci¹¿eniu operatora <<.
		Osoba::out(output);	//Wywo³anie metody out dla klasy bazowej Osoba.
		output<<" "<< specjalizacja << " " << pensja << " zl. " << wojewodztwo; //Przekazanie do strumienia dodatkowych danych dostêpnych tylko w klasie pochodnej.
		return output;	//Zwrot strumienia.
	}
	void setWoj(string woj) {	//Metoda, która przyjmuje argument typu string i przypisuje go polu prywatnemu wojewodztwo.
		wojewodztwo = woj;
	}
private: //Pola prywatne zadeklarowane w treœci zadania.
	string specjalizacja;
	float mnoznik;
	float pensja;
};

class Emeryt : public Osoba { //Klasa pochodna Emeryt, która dziedziczy publicznie po klasie Osoba.
public:
	//Konstruktor parametryzuj¹cy przyjmuj¹cy wartoœci domyœlne, inicjalizuje wartoœci polom chroniomym i prywatnym dziêki liœcie parametryzuj¹cej i konstruktowi klasy nadrzêdnej Osoba.
	Emeryt(string Imie = "Ferdynand", string Nazwisko="Kiepski", int rok_ur=1950, float Emerytura = 1026) : Osoba(Imie, Nazwisko, rok_ur), emerytura(Emerytura) {}
	//Konstruktor parametryzuj¹cy, który dziêki liœcie parametryzuj¹cej i konstruktorowi kopiuj¹cemu klasy nadrzêdnej Osoba kopiuje wartoœci obiektu klasy Osoba i inicjalizuje pole emerytura.
	Emeryt(Osoba& os, float emeryt = 1026) : Osoba(os), emerytura(emeryt) {}
	virtual ostream& out(ostream& output) { //Redefinicja metody out dla klasy pochodnej Emeryt, która jest potrzebna do wyœwietlenia danych dziêki przeci¹¿eniu operatora <<.
		Osoba::out(output); //Wywo³anie metody out dla klasy bazowej Osoba.
		output << " Emerytura: " << emerytura << " zl.";	//Przekazanie do strumienia dodatkowych danych dostêpnych tylko w klasie pochodnej.
		return output;	//Zwrot strumienia.
	}
private:	//Pole prywatne zadeklarowane w treœci zadania.
	float emerytura;
};

const float Pracownik::placa_minimalna = 2250;	//Zainicjowanie zmiennej statycznej placa_minimalna klasy Pracownik.

ostream& operator<<(ostream& output, Osoba& os) { //Definicja przeci¹¿enia operatora << dla klasy Osoba, który wypisuje jej pola chronione.
	if (&os != nullptr)	//Sprawdzenie czy referencja do obiektu nie jest równa nullptr, czyli czy dany obiekt jest zainicjalizowany. Potrzebne przy póŸniejszym wypisywaniu tablicy obiektów.
		os.out(output);	//Je¿eli referencja nie równa siê nullptr to wywo³ywana jest metoda out(ostream&) na przes³anym obiekcie, która przeœle dane do strumienia w zale¿noœci od klasy obiektu.
	return output;	//Zwrot strumienia.
}

float roundTwoDigitsMinPay(float& numb) {	//Funkcja która przyjmuje mno¿nik pensji minimalnej, a nastêpnie zwraca wartoœæ pensji zaokr¹glon¹ do dwóch miejsc po przecinku zgodnie z zasadami zaokr¹glania.
	//Pomno¿enie wartoœci p³acy minimalnej przez mno¿nik co daje nam wartoœæ dok³adn¹, pomno¿enie przez 100 aby przesun¹æ dwie cyfry po przecinku do przodu, nastêpnie dodanie 0.5 które pomo¿e nam zaokr¹gliæ zgodnie z zasadami zaokr¹glenia. 
	//Liczba ta jest konwertowana z float do int wiêc obcinane s¹ cyfry po przecinku.
	int pom_i = static_cast <int> ((Pracownik::getPlacaMin() * numb * 100) + 0.5);	
	//Liczbê tê konwertujemy do wartoœci float i dzielimy j¹ przez 100, przez co zwracana wartoœæ jest zaokr¹glona do dwóch miejsc po przecinku.
	return static_cast <float> (pom_i) / 100;
}
//Definicja funkcji, która przyjmuje tablicê wskaŸników do klasy Osoba oraz jej rozmiar, sprawdza iloœæ osób których wiek jest powy¿ej 65 lat i kopiuje ich wartoœci do nowej tablicy dynamicznej, a z przes³anej tablicy usuwa ich. Funkcja zwraca wskaŸnik do 
//utworzonej tablicy dynamicznej. Równie¿ zmieniana jest wartoœæ przes³anego argumentu n, który po zakoñczeniu funkcji bêdzie przechowywa³ rozmiar utworzonej tablicy obiektów klasy Emeryt.
Emeryt* stworzEmerytow(Osoba** tab, int& n) {	 
	int sum_em = 0; //Zmienna pomocnicza, która zliczy iloœæ osób których wiek jest powy¿ej 65 lat.
	for (int i = 0; i < n; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do klasy Osoba tab.
	{
		if ((*tab[i]).wiek() > 65)	//Je¿eli wiek danego elementu tablicy jest wiêkszy od 65 to wtedy iterowana jest zmienna sum_em o 1.
			sum_em++;
	}
	if (sum_em == 0) {	//Je¿eli sum_em jest równy 0 to oznacza ¿e ¿aden element tablicy powy¿ej 65 lat. Wtedy wypisywany jest odpowiedni komunikat b³êdu, n jest przypisywana wartoœæ 0, poniewa¿ ma on zwracaæ rozmiar utworzonej tablicy. 
		cout << "W podanej tablicy nie znaleziono ¿adnych emerytów, b³¹d" << endl;
		n = 0;
		return nullptr; //Zwracana jest wartoœæ nullptr, czyli pusty wskaŸnik.
	}
	Emeryt* tab_em = new Emeryt[sum_em];	//Je¿eli funckja nie zosta³a zakoñczona to tworzona jest nowa dynamiczna tablica obiektów klasy Emeryt o rozmiarze sum_em.
	int i_newtable = 0;	//Zmienna pomocnicza potrzebna do iteracji tablicy tab_em w pêtli, która iteruje po tablicy tab.
	for (int i = 0; i < n; i++) //Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do klasy Osoba tab.
	{
		if ((*tab[i]).wiek() > 65) {	//Je¿eli wiek danego elementu jest wiêkszy od wiêkszy od 65 to elementowi i_newtable tablicy obiektów typu Emeryt jest przypisywana wartoœæ na któr¹ wskazuje i-ty element tablicy tab
			tab_em[i_newtable] = Emeryt((*tab[i]), 1200 + i); //oraz wartoœæ 1200 (minimalna emerytura wg strony ZUSu) powiêkszona o wartoœæ i.
			tab[i] = nullptr;	//Przypisanie nullptr i-temu elementowi tablicy wskaŸników typu Osoba tab.
			i_newtable++;		//Zwiêkszenie wartoœci i_newtable o jeden.
		}
	}
	n = sum_em;		//Zwrot rozmiaru utworzonej tablicy tab_em poprzez przypisanie tej wartoœci do zmiennej n która jest referencj¹ przes³an¹ jako argument.
	return tab_em;	//Zwrot wskaŸnika do utworzonej tablicy dynamicznej obiektów klasy Emeryt.

}
int main() {
	//Utworzonie obiektu i zainicjalizowanie jego wartoœci konstruktorem parametryzuj¹cym klasy Osoba.
	cout << "Dane obiektu klasy Osoba: " << endl;
	Osoba o1("Mariusz", "Pudzianowski", 1977);
	//Wypisanie danych obiektu o1 dziêki przeci¹¿eniu operatora <<.
	cout << o1 << endl;
	cout << endl;
	//Utworzonie obiektu i zainicjalizowanie jego wartoœci konstruktorem parametryzuj¹cym klasy Informatyk. 
	cout << "Dane pierwszego obiektu klasy Informatyk:" << endl;
	Informatyk i1("Adam", "Malysz", 1977, "slaskie", "skoczek", 1.5555);
	//Wypisanie danych obiektu i1 dziêki przeci¹¿eniu operatora << oraz wypisanie jego wieku rocznikowego dziêki metodzie wiek().
	cout << i1 << " Wiek: " << i1.wiek() << endl;
	cout << endl;
	//Utworzenie obiektu klasy Informatyk i zainicjowanie jego wartoœci poprzez konstruktor kopiuj¹cy jednak zmieniaj¹c pola imie, nazwisko i rok_urodzenia. Obiekt kopiuje wartoœci obiektu i1.
	cout << "Dane drugiego obiektu klasy Informatyk oraz jego wiek:" << endl;
	Informatyk i2(i1, "Chuck", "Norris", 1940);
	//Wypisanie danych obiektu i2 dziêki przeci¹¿eniu operatora << oraz wypisanie jego wieku rocznikowego dziêki metodzie wiek().
	cout << i2 << " Wiek: " << i2.wiek() << endl;
	cout << endl;
	//Zmiana wartoœci pola wojewodztwo dziêki metodzie setWoj(string) na obiekcie i2 a nastêpnie wypisanie jego danych dziêki przeci¹¿eniu operatora <<.
	cout << "Dane drugiego obiektu klasy Informatyk po zmianie wojewodztwa:" << endl;
	i2.setWoj("Oklahoma");
	cout << i2 << endl;
	cout << endl;
	//Utworzenie zmiennych pomocniczych, które bêd¹ przechowywa³y rozmiary tablic dynamicznych.
	int n_os = 3, n_em = n_os;
	//Utworzenie dynamicznej tablicy wskaŸników klasy Osoba o rozmiarze n_os.
	Osoba** tab_os = new Osoba* [n_os];
	//Przypisanie elementom tablicy referencji do obiektów klas Osoba o1 oraz Informatyk i1 i i2.
	tab_os[0] = &o1; tab_os[1] = &i1; tab_os[2] = &i2;
	//Wypisanie danych tab_os dziêki pêtli for i przeci¹¿eniu operatora <<.
	cout << "Dane tablicy osob: " << endl;
	for (int i = 0; i < n_os; i++)
	{
		cout << (*tab_os[i]) << endl;
	}	
	cout << endl;
	//Utworzenie nowej tablicy dynamicznej obiektów typu Emeryt i przypisanie jej do wskaŸnika tab_em poprzez funkcjê stworzEmerytow(Osoba**,int&). Zmienna n_em zawiera rozmiar tablicy tab_os czyli argumentu funkcji, ale po jej zakoñczeniu bêdzie przechowywaæ
	//rozmiar nowo utworzonej tablicy.
	cout << "Dane tablicy emerytow, po jej utworzeniu:" << endl;
	Emeryt* tab_em = stworzEmerytow(tab_os, n_em);
	//Wypisanie danych tab_em dziêki pêtli for i przeci¹¿eniu operatora <<.
	for (int i = 0; i < n_em; i++)
	{
		cout << tab_em[i] << endl;
	}
	cout << endl;
	cout << "Dane tablicy osob po utworzeniu tablicy emerytow:" << endl;
	//Wypisanie danych tab_os po zakoñczeniu funkcji stworzEmerytow(Osoba**, int&), której ta tablica by³a argumentem.
	for (int i = 0; i < n_os; i++)
	{
		 cout << (*tab_os[i]) << endl;
	}
	//Dealokacja pamiêci przyznanej tablicom dynamicznym tab_os i tab_em.
	delete[] tab_os;
	delete[] tab_em;
	//Przypisanie wartoœci nullptr wskaŸnikom tab_os i tab_em.
	tab_os = nullptr;
	tab_em = nullptr;
	return 0;
}