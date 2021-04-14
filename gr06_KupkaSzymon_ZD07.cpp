#include <iostream>

using namespace std;

class Pasazer {
public:
	Pasazer(string Imie, string Nazwisko, int Wiek) : imie(Imie), nazwisko(Nazwisko), wiek(Wiek) {}	//Konstruktor parametryzuj¹cy przypisuj¹cy wartoœci argumentów odpowiednim polom prywatnym.
	friend ostream& operator<<(ostream&, const Pasazer&);	//Deklaracja przyjaŸni klasy z przeci¹¿eniem operatora <<.
	friend void insert_sort(Pasazer*, int size);			//Deklaracja przyjaŸni klasy z funkcj¹ sortuj¹c¹ tablicê klasy Pasazer malej¹co wed³ug wieku poszczególnego obiektu klasy Pasazer.
private:	//Pola prywatne zadeklarowane w treœci zadania.
	string imie;
	string nazwisko;
	int wiek;
};
class Autokar {
public:
	Autokar(string Cel, float Cena, int Limit) : cel_podrozy(Cel), cena_biletu(Cena), limit_miejsc(Limit) {	//Konstruktor parametryzuj¹cy przypisuj¹cy wartoœci argumentów odpowiednim polom prywatnym oraz tworz¹cy tablice dynamiczn¹ wskaŸników na obiekty klasy Pasazer.
		pasazerowie = new Pasazer * [limit_miejsc];	//Utworzenie tablicy dynamicznej wskaŸników na obiekty klasy Pasazer o rozmiarze limit_miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//Pêtla iteruj¹ca po ka¿dym elemencie tablicy pasazerowie.
			pasazerowie[i] = nullptr;			//Przypisanie wartoœci nullptr ka¿demu elementowi tablicy.
	}
	Autokar(const Autokar& a1) : cel_podrozy(a1.cel_podrozy), cena_biletu(a1.cena_biletu), limit_miejsc(a1.limit_miejsc) {	//Konstruktor kopiuj¹cy, który kopiuje wartoœci pól prywatnych oraz tworzy now¹ tablicê dynamiczn¹ i wtedy przypisuje jej psozczególne elementy.
		pasazerowie = new Pasazer * [limit_miejsc];	//Utworzenie nowej tablicy dynamicznej o rozmiarze limit_miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//Pêtla iteruj¹ca po ka¿dym elemencie tablicy pasazerowie.
			pasazerowie[i] = a1.pasazerowie[i];	//Kopiowanie wartoœci z tablicy argumentu konstruktora do tablicy danego obiektu.
	}
	~Autokar() {	//Destruktor odpowiedzialny za dealokacjê pamiêci przyznanej tablicy pasazerowanie.
		delete[] pasazerowie;	//Dealokacja pamiêci przypisanej wskaŸnikowi pasazerowanie w konstruktorze operatorem delete.
		pasazerowie = nullptr;	//Ustawienie wartoœci nullptr wskaŸnikowi na wskaŸnik pasazerowie.
	}
	void wyswietlCel() {	//Metoda wyœwietlaj¹ca pola cel_podrozy, cena_biletu oraz limit_miejsc.
		cout << cel_podrozy << " cena: " << cena_biletu << " pesos, limit osob: " << limit_miejsc << endl;
	}
	void wyswietlPas() {	//Metoda wypisuj¹ca wszystkie elementy tablicy pasazerowie - dane poszczególnych obiektów zawartych w tej tablicy.
		wyswietlCel();	//Wywo³anie metody wyswietlCel() w celu wypisania celu, ceny biletu oraz limitu miejsc.
		for (int i = 0; i < limit_miejsc; i++)	//Pêtla iteruj¹ca po ka¿dym elemencie tablicy pasazerowie.
		{
			if (pasazerowie[i] != nullptr)		//Je¿eli wskaŸnik bêdzie mia³ inn¹ wartoœæ ni¿ nullptr wtedy wypisywane s¹ dane obiektu na którego wskaŸnik pokazuje dziêki przeci¹¿eniu operatora <<.
				cout << (*pasazerowie[i]);
		}
	}
	Autokar& operator++() {		//Przeci¹¿enie operatora preinkrementacji, zwiêksza cenê biletu o 1 i zwraca sam siebie.
		cena_biletu++;
		return (*this); //Zwrot obiektu na którym wykonywana jest ta operacja.
	}
	Autokar operator++(int) {	//Przeci¹¿enie operatora postinkrementacji.
		Autokar temp(*this);	//Utworzenie kopii obiektu na którym jest wykonywana jest operacja.
		cena_biletu++;			//Zwiêkszenie ceny biletu o jeden pierwotnego obiektu.
		return temp;			//Zwrócenie kopii obiektu utworzonej na pocz¹tku dzia³ania funkcji.
	}
	Autokar& operator+=(Pasazer& pas) {	//Przeci¹¿enie operatora += który bêdzie odpowiada³ za przypisanie wskaŸnika do obiektu przes³anego jako argument funkcji.
		int first_free_index = -1;		//Zmienna pomocnicza, która bêdzie przechowywa³a indeks pierwszego wolnego elementu tablicy pasazerowie, wartoœæ domyœlna to -1, poniewa¿ ¿aden indeks tablicy nie mo¿e mieæ wartoœci ujemnych.
		for (int i = 0; i < limit_miejsc; i++) //Pêtla iteruj¹ca po ka¿dym elemencie tablicy pasazerowie.
		{
			if (pasazerowie[i] != nullptr) {	//Je¿eli element tablicy nie jest pusty czyli jego wartoœæ nie równa siê nullptr
				if (pasazerowie[i] == &pas) {	//i jeœli wskaŸnik na który pokazuje ten element jest równy adresowi przes³anego argumentu to wtedy nie jest przypisywany podany argument, wypisywany jest b³¹d, a funkcja koñczy siê zwracaj¹c 
					cout << "Podany pasazer zostal juz przypisany, nie przypisano ponownie" << endl; //obiekt na którym wykonywana jest operacja. Warunek ten uniemo¿liwia przypisanie wielokrotnie tego samego pasa¿era do tablicy.
					return (*this);
				}
			}
			else {	//W przeciwnym wypadku jeœli element jest pusty i wartoœæ zmiennej pomocniczej jest nadal równa -1 to przypisywana jest mu wartoœæ i.
				if (first_free_index == -1)
					first_free_index = i;
			}
		}
		if (first_free_index != -1) { //Je¿eli funkcja siê ci¹gle wykonuje i zmienna pomocnicza ma wartoœæ ró¿n¹ od -1 to nastêpuje przypisanie argumentu do tablicy pasazerowie o indeksie first_free_index.
			pasazerowie[first_free_index] = &pas;
			cout << "Przypisanie pasazera: " << pas;	//Wypisywany jest równie¿ stosowny komunikat.
		}
		else	//Jeœli wartoœæ zmiennej pomocniczej wynosi -1 to znaczy ¿e tablica nie posiada ¿adnego pustego elementu czyli takiego, którego wartoœæ wynosi nullptr wiêc tablica jest pe³na. Wypisywany jest odpowiedni b³¹d oraz nie nastêpuje przypisanie.
			cout << "Limit osob zostal przekroczony, nie przypisano pasazera" << endl;
		return (*this); //Zwrot obiektu na którym wykonywana jest operacja.
	}
	friend Autokar& operator-=(Autokar& autokar, Pasazer& pas); //Deklaracja przyjaŸni klasy z przeci¹¿eniem operatora -=
private:	//Pola prywatne zadeklarowane w treœci zadania.
	string cel_podrozy;
	float cena_biletu;
	int limit_miejsc;
	Pasazer** pasazerowie;	//WskaŸnik do wskaŸnika klasy Pasazer potrzebny do utworzenia tablicy dynamicznej wskaŸników klasy Pasazer.
};
ostream& operator<<(ostream& out, const Pasazer& pas) {	//Definicja przeci¹¿enia operatora << dla obiektu klasu Pasazer.
	out << pas.imie << " " << pas.nazwisko << " " << pas.wiek << " lat" << endl;	//Przes³anie do strumienia danych pól prywatnych obiektu klasy Pasazer.
	return out;	//Zwrot strumienia.
}
Autokar& operator-=(Autokar& autokar, Pasazer& pas) {	//Przeci¹¿enie operatora -= dla klasy Autokar i Pasazer, który bêdzie odpowiada³ za usuniêcie wskaŸnika do klasy Pasazer z tablicy pasazerowie obiektu klasy Autokar, jeœli taki wystêpuje w tablicy.
	for (int i = 0; i < autokar.limit_miejsc; i++)	//Pêtla iteruj¹ca po ka¿dym elemencie tablicy pasazerowie obiektu klasy Autokar.
	{
		if (autokar.pasazerowie[i] == &pas) {	//Je¿eli element tablicy jest równy adresowi argumentu to wtedy temu elementowi przypisywana jest wartoœæ nullptr, wypisywany jest komunikat, a funkcja koñczy siê poniewa¿ w przeci¹¿eniu operatora +=
			autokar.pasazerowie[i] = nullptr;	//zapewniliœmy ¿e elementy tablicy nie mog¹ siê powtarzaæ wiêc nie jest konieczne dalsze przeszukiwanie tablicy. 
			cout << "Usunieto pasazera" << endl;
			return autokar;	//Zwrot obiektu klasy Autokar.
		}
	}
	cout << "Podany pasazer nie byl na liscie" << endl; //Jeœli funkcja dalej siê wykonuje to oznacza ¿e przes³any argument nie by³ czêœci¹ tablicy pasazerowie, wypisywany jest odpowiedni komunikat.
	return autokar; //Zwrot obiektu klasy Autokar.
}

void insert_sort(Pasazer* tab, int size) {	//Funkcja zaprzyjaŸniona z klas¹ Pasazer, sortuj¹ca malej¹co wed³ug wieku tablicê obiektów typu Pasa¿er.
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
	//Utworzenie tablicy piêcioelementowej obiektów klasy Pasazer i zainicjalizowanie wartoœci.
	Pasazer tab_pas[] = { {"Tytus", "Bomba", 39}, {"Michal", "Glus", 21}, {"Boguslaw","Lecina", 37}, {"Tomislaw", "Apoloniusz Curus Bachleda Farell", 70}, {"Domino", "Jachas", 44} };
	//Wyœwietlenie wszystkich elementów dziêki pêtli for oraz przeci¹¿eniu operatora <<.
	for (int i = 0; i < 5; i++)
		cout << tab_pas[i];
	cout << endl;
	//Posortowanie tablicy tab_pas dziêki funkcji insert_sort().
	insert_sort(tab_pas, 5);
	//Ponowne wyœwietlenie danych wszystkich obiektów tablicy tab_pas.
	for (int i = 0; i < 5; i++)
		cout << tab_pas[i];
	cout << endl;
	//Utworzenie obiektu klasy Autokar i zainicjowanie wartoœci.
	Autokar przewoz_osob("Planeta Wojny", 3.99, 10);
	//Wyœwietlenie danych obiektu przewoz_osob dziêki metodzie wyswietlCel().
	przewoz_osob.wyswietlCel();
	cout << endl;
	//Zwiêkszenie ceny bilety ³¹cznie o 3 dziêki przeci¹¿eniu operatorów pre- i post- ikrementacji.
	przewoz_osob++; ++przewoz_osob; przewoz_osob++;
	//Ponowne wyœwietlenie danych obiektu przewoz_osob w tym równie¿ zmienionej ceny biletu dziêki metodzie wyswietlCel().
	przewoz_osob.wyswietlCel();
	cout << endl;
	//Dodanie do tablicy pasazerowanie obiektu przewoz_osob czterech elementów tablicy tab_pas dziêki przeci¹¿onemu operatorowi +=.
	przewoz_osob += tab_pas[0]; przewoz_osob += tab_pas[1]; przewoz_osob += tab_pas[2]; przewoz_osob += tab_pas[3];
	cout << endl;
	//Wyswietlenie listy pasazerow obiektu przewoz_osob dziêki metodzie wyswietlPas().
	przewoz_osob.wyswietlPas();
	cout << endl;
	//Usuniêcie z tablicy pasazerowie obiektu przewoz_osob elementu tablicy tab_pas dziêki przeci¹zonemu operatorowi -=.
	przewoz_osob -= tab_pas[0];
	//Ponowne wyœwietlenie listy pasazerow obiektu przewoz_osob dziêki metodzie wyswietlPas().
	przewoz_osob.wyswietlPas();
	return 0;
}