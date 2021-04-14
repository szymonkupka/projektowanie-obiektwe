#include <iostream>

using namespace std;

class Pasazer {
public:
	Pasazer(string Imie, string Nazwisko, int Wiek) : imie(Imie), nazwisko(Nazwisko), wiek(Wiek) {}	//Konstruktor parametryzuj�cy przypisuj�cy warto�ci argument�w odpowiednim polom prywatnym.
	friend ostream& operator<<(ostream&, const Pasazer&);	//Deklaracja przyja�ni klasy z przeci��eniem operatora <<.
	friend void insert_sort(Pasazer*, int size);			//Deklaracja przyja�ni klasy z funkcj� sortuj�c� tablic� klasy Pasazer malej�co wed�ug wieku poszczeg�lnego obiektu klasy Pasazer.
private:	//Pola prywatne zadeklarowane w tre�ci zadania.
	string imie;
	string nazwisko;
	int wiek;
};
class Autokar {
public:
	Autokar(string Cel, float Cena, int Limit) : cel_podrozy(Cel), cena_biletu(Cena), limit_miejsc(Limit) {	//Konstruktor parametryzuj�cy przypisuj�cy warto�ci argument�w odpowiednim polom prywatnym oraz tworz�cy tablice dynamiczn� wska�nik�w na obiekty klasy Pasazer.
		pasazerowie = new Pasazer * [limit_miejsc];	//Utworzenie tablicy dynamicznej wska�nik�w na obiekty klasy Pasazer o rozmiarze limit_miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//P�tla iteruj�ca po ka�dym elemencie tablicy pasazerowie.
			pasazerowie[i] = nullptr;			//Przypisanie warto�ci nullptr ka�demu elementowi tablicy.
	}
	Autokar(const Autokar& a1) : cel_podrozy(a1.cel_podrozy), cena_biletu(a1.cena_biletu), limit_miejsc(a1.limit_miejsc) {	//Konstruktor kopiuj�cy, kt�ry kopiuje warto�ci p�l prywatnych oraz tworzy now� tablic� dynamiczn� i wtedy przypisuje jej psozczeg�lne elementy.
		pasazerowie = new Pasazer * [limit_miejsc];	//Utworzenie nowej tablicy dynamicznej o rozmiarze limit_miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//P�tla iteruj�ca po ka�dym elemencie tablicy pasazerowie.
			pasazerowie[i] = a1.pasazerowie[i];	//Kopiowanie warto�ci z tablicy argumentu konstruktora do tablicy danego obiektu.
	}
	~Autokar() {	//Destruktor odpowiedzialny za dealokacj� pami�ci przyznanej tablicy pasazerowanie.
		delete[] pasazerowie;	//Dealokacja pami�ci przypisanej wska�nikowi pasazerowanie w konstruktorze operatorem delete.
		pasazerowie = nullptr;	//Ustawienie warto�ci nullptr wska�nikowi na wska�nik pasazerowie.
	}
	void wyswietlCel() {	//Metoda wy�wietlaj�ca pola cel_podrozy, cena_biletu oraz limit_miejsc.
		cout << cel_podrozy << " cena: " << cena_biletu << " pesos, limit osob: " << limit_miejsc << endl;
	}
	void wyswietlPas() {	//Metoda wypisuj�ca wszystkie elementy tablicy pasazerowie - dane poszczeg�lnych obiekt�w zawartych w tej tablicy.
		wyswietlCel();	//Wywo�anie metody wyswietlCel() w celu wypisania celu, ceny biletu oraz limitu miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//P�tla iteruj�ca po ka�dym elemencie tablicy pasazerowie.
		{
			if (pasazerowie[i] != nullptr)		//Je�eli wska�nik b�dzie mia� inn� warto�� ni� nullptr wtedy wypisywane s� dane obiektu na kt�rego wska�nik pokazuje dzi�ki przeci��eniu operatora <<.
				cout << (*pasazerowie[i]);
		}
	}
	Autokar& operator++() {		//Przeci��enie operatora preinkrementacji, zwi�ksza cen� biletu o 1 i zwraca sam siebie.
		cena_biletu++;
		return (*this); //Zwrot obiektu na kt�rym wykonywana jest ta operacja.
	}
	Autokar operator++(int) {	//Przeci��enie operatora postinkrementacji.
		Autokar temp(*this);	//Utworzenie kopii obiektu na kt�rym jest wykonywana jest operacja.
		cena_biletu++;			//Zwi�kszenie ceny biletu o jeden pierwotnego obiektu.
		return temp;			//Zwr�cenie kopii obiektu utworzonej na pocz�tku dzia�ania funkcji.
	}
	Autokar& operator+=(Pasazer& pas) {	//Przeci��enie operatora += kt�ry b�dzie odpowiada� za przypisanie wska�nika do obiektu przes�anego jako argument funkcji.
		int first_free_index = -1;		//Zmienna pomocnicza, kt�ra b�dzie przechowywa�a indeks pierwszego wolnego elementu tablicy pasazerowie, warto�� domy�lna to -1, poniewa� �aden indeks tablicy nie mo�e mie� warto�ci ujemnych.
		for (int i = 0; i < limit_miejsc; i++) //P�tla iteruj�ca po ka�dym elemencie tablicy pasazerowie.
		{
			if (pasazerowie[i] != nullptr) {	//Je�eli element tablicy nie jest pusty czyli jego warto�� nie r�wna si� nullptr
				if (pasazerowie[i] == &pas) {	//i je�li wska�nik na kt�ry pokazuje ten element jest r�wny adresowi przes�anego argumentu to wtedy nie jest przypisywany podany argument, wypisywany jest b��d, a funkcja ko�czy si� zwracaj�c 
					cout << "Podany pasazer zostal juz przypisany, nie przypisano ponownie" << endl; //obiekt na kt�rym wykonywana jest operacja. Warunek ten uniemo�liwia przypisanie wielokrotnie tego samego pasa�era do tablicy.
					return (*this);
				}
			}
			else {	//W przeciwnym wypadku je�li element jest pusty i warto�� zmiennej pomocniczej jest nadal r�wna -1 to przypisywana jest mu warto�� i.
				if (first_free_index == -1)
					first_free_index = i;
			}
		}
		if (first_free_index != -1) { //Je�eli funkcja si� ci�gle wykonuje i zmienna pomocnicza ma warto�� r�n� od -1 to nast�puje przypisanie argumentu do tablicy pasazerowie o indeksie first_free_index.
			pasazerowie[first_free_index] = &pas;
			cout << "Przypisanie pasazera: " << pas;	//Wypisywany jest r�wnie� stosowny komunikat.
		}
		else	//Je�li warto�� zmiennej pomocniczej wynosi -1 to znaczy �e tablica nie posiada �adnego pustego elementu czyli takiego, kt�rego warto�� wynosi nullptr wi�c tablica jest pe�na. Wypisywany jest odpowiedni b��d oraz nie nast�puje przypisanie.
			cout << "Limit osob zostal przekroczony, nie przypisano pasazera" << endl;
		return (*this); //Zwrot obiektu na kt�rym wykonywana jest operacja.
	}
	friend Autokar& operator-=(Autokar& autokar, Pasazer& pas); //Deklaracja przyja�ni klasy z przeci��eniem operatora -=
private:	//Pola prywatne zadeklarowane w tre�ci zadania.
	string cel_podrozy;
	float cena_biletu;
	int limit_miejsc;
	Pasazer** pasazerowie;	//Wska�nik do wska�nika klasy Pasazer potrzebny do utworzenia tablicy dynamicznej wska�nik�w klasy Pasazer.
};
ostream& operator<<(ostream& out, const Pasazer& pas) {	//Definicja przeci��enia operatora << dla obiektu klasu Pasazer.
	out << pas.imie << " " << pas.nazwisko << " " << pas.wiek << " lat" << endl;	//Przes�anie do strumienia danych p�l prywatnych obiektu klasy Pasazer.
	return out;	//Zwrot strumienia.
}
Autokar& operator-=(Autokar& autokar, Pasazer& pas) {	//Przeci��enie operatora -= dla klasy Autokar i Pasazer, kt�ry b�dzie odpowiada� za usuni�cie wska�nika do klasy Pasazer z tablicy pasazerowie obiektu klasy Autokar, je�li taki wyst�puje w tablicy.
	for (int i = 0; i < autokar.limit_miejsc; i++)	//P�tla iteruj�ca po ka�dym elemencie tablicy pasazerowie obiektu klasy Autokar.
	{
		if (autokar.pasazerowie[i] == &pas) {	//Je�eli element tablicy jest r�wny adresowi argumentu to wtedy temu elementowi przypisywana jest warto�� nullptr, wypisywany jest komunikat, a funkcja ko�czy si� poniewa� w przeci��eniu operatora +=
			autokar.pasazerowie[i] = nullptr;	//zapewnili�my �e elementy tablicy nie mog� si� powtarza� wi�c nie jest konieczne dalsze przeszukiwanie tablicy. 
			cout << "Usunieto pasazera" << endl;
			return autokar;	//Zwrot obiektu klasy Autokar.
		}
	}
	cout << "Podany pasazer nie byl na liscie" << endl; //Je�li funkcja dalej si� wykonuje to oznacza �e przes�any argument nie by� cz�ci� tablicy pasazerowie, wypisywany jest odpowiedni komunikat.
	return autokar; //Zwrot obiektu klasy Autokar.
}

void insert_sort(Pasazer* tab, int size) {	//Funkcja zaprzyja�niona z klas� Pasazer, sortuj�ca malej�co wed�ug wieku tablic� obiekt�w typu Pasa�er.
	int j = 0;		//Deklaracja zmiennych pomocniczych.
	Pasazer temp = tab[1];
	for (int i = 1; i < size; i++)	//Algorytm sortowania przez wstawianie.
	{
		temp = tab[i];
		for (j = i - 1; j >= 0 && tab[j].wiek < temp.wiek; j--)
			tab[j + 1] = tab[j];
		tab[j + 1] = temp;
	}
}

int main() {
	//Utworzenie tablicy pi�cioelementowej obiekt�w klasy Pasazer i zainicjalizowanie warto�ci.
	Pasazer tab_pas[] = { {"Tytus", "Bomba", 39}, {"Michal", "Glus", 21}, {"Boguslaw","Lecina", 37}, {"Tomislaw", "Apoloniusz Curus Bachleda Farell", 70}, {"Domino", "Jachas", 44} };
	//Wy�wietlenie wszystkich element�w dzi�ki p�tli for oraz przeci��eniu operatora <<.
	for (int i = 0; i < 5; i++)
		cout << tab_pas[i];
	cout << endl;
	//Posortowanie tablicy tab_pas dzi�ki funkcji insert_sort().
	insert_sort(tab_pas, 5);
	//Ponowne wy�wietlenie danych wszystkich obiekt�w tablicy tab_pas.
	for (int i = 0; i < 5; i++)
		cout << tab_pas[i];
	cout << endl;
	//Utworzenie obiektu klasy Autokar i zainicjowanie warto�ci.
	Autokar przewoz_osob("Planeta Wojny", 3.99, 10);
	//Wy�wietlenie danych obiektu przewoz_osob dzi�ki metodzie wyswietlCel().
	przewoz_osob.wyswietlCel();
	cout << endl;
	//Zwi�kszenie ceny bilety ��cznie o 3 dzi�ki przeci��eniu operator�w pre- i post- ikrementacji.
	przewoz_osob++; ++przewoz_osob; przewoz_osob++;
	//Ponowne wy�wietlenie danych obiektu przewoz_osob w tym r�wnie� zmienionej ceny biletu dzi�ki metodzie wyswietlCel().
	przewoz_osob.wyswietlCel();
	cout << endl;
	//Dodanie do tablicy pasazerowanie obiektu przewoz_osob czterech element�w tablicy tab_pas dzi�ki przeci��onemu operatorowi +=.
	przewoz_osob += tab_pas[0]; przewoz_osob += tab_pas[1]; przewoz_osob += tab_pas[2]; przewoz_osob += tab_pas[3];
	cout << endl;
	//Wyswietlenie listy pasazerow obiektu przewoz_osob dzi�ki metodzie wyswietlPas().
	przewoz_osob.wyswietlPas();
	cout << endl;
	//Usuni�cie z tablicy pasazerowie obiektu przewoz_osob elementu tablicy tab_pas dzi�ki przeci�zonemu operatorowi -=.
	przewoz_osob -= tab_pas[0];
	//Ponowne wy�wietlenie listy pasazerow obiektu przewoz_osob dzi�ki metodzie wyswietlPas().
	przewoz_osob.wyswietlPas();
	return 0;
}