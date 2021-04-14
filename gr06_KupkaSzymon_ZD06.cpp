#include <iostream>

using namespace std;

class Produkt {
public:
	//Konstruktor parametryzuj�cy z domy�lnymi warto�ciami przypisuj�cy warto�ci polom przez list� inicjalizacyjn�.
	Produkt(string Nazwa="Pikantna Chinska", string Marka="Lewiatan", float Cena=0.89, int Masa=60, float wegl=51.8, float bial=7.6, float tluszcz=19) : nazwa(Nazwa), marka(Marka), cena(Cena), 
		masa(Masa), weglowodany_udzial(wegl), bialko_udzial(bial), tluszcz_udzial(tluszcz){}
	float kalorycznosc(){ //Metoda oblicza i zwraca kaloryczno��.
		return masa * (weglowodany_udzial * 4 + bialko_udzial * 4 + tluszcz_udzial * 9) / 100;
	}
	void wyswietl() { //Metoda wypisuje na ekran dane obiektu.
		cout << nazwa << ", " << marka << ", " << cena << " zl, " << masa << "g, Weglowodany " << weglowodany_udzial << "%, bialko " << bialko_udzial << "%, tluszcz " << tluszcz_udzial << "% " << endl;
	}
	//Pola publiczne zadeklarowane w tre�ci zadania.
	string nazwa;
	string marka;
	float cena;
	int masa;
	float weglowodany_udzial;
	float bialko_udzial;
	float tluszcz_udzial;
};
class ListaZakupow {
public:
	//Deklaracja przyja�ni dw�ch funkcji zaprzyja�nionych.
	friend void dodajProdukt(ListaZakupow&, Produkt&);
	friend void wyswietlListe(ListaZakupow&);
	//Konstruktor parametryzuj�cy z domy�lnymi warto�ciami, przypisuj�cy warto�ci odpowiednim polom prywatnym dzi�ki li�cie inicjalizacyjnej.
	ListaZakupow(string nazwa="Zakupy", float budzet=5) : nazwa_listy(nazwa), dostepny_budzet(budzet) {
		wsk_produkt = new Produkt * [4];	//Utworzenie czteroelementowej tablicy dynamicznej wska�nik�w do klasy Produkt.
		for (int i = 0; i < 4; i++)		//P�tla iteruj�ca po ka�dym elemencie tablicy wsk_produkt.
		{
			wsk_produkt[i] = nullptr;	//Przypisanie nullptr wszystkim elementom tablicy wsk_produkt.
		}
	}
	~ListaZakupow() {	//Destruktor odpowiedzialny za dealokacj� pami�ci tablicy utworzonej w konstruktorze.
		delete[] wsk_produkt;	//Dealokacja pami�ci tablicy dzi�ki operatorowi delete.
		wsk_produkt = nullptr;	//Przypisanie wska�nikowi wsk_produkt nullptr.
	}
	void wyswietl() {	//Metoda wy�wietlaj�ca nazw� i bud�et obiektu.
		cout << "Lista: " << nazwa_listy << ", budzet: " << dostepny_budzet << " zl " << endl;
	}
private:
	//Pola prywatne zadeklarowane w zadaniu.
	string nazwa_listy;
	const float dostepny_budzet;
	Produkt** wsk_produkt;	//Wska�nik na wska�nik klasy Produkt potrzebny do utworzenia tablicy wska�nik�w.
};
void dodajProdukt(ListaZakupow& lista, Produkt& produkt) //Funckja zaprzyja�niona z klas� ListaZakupow, odpowiedzialna za dodanie elementu do tablicy wsk_produkt.
{
	//Zmienne pomocnicze potrzebne do przypisania elementu lub wypisania odpowiednich komunikat�w.
	float suma = 0;			//Zmienna zliczaj�ca sum� cen produkt�w z tablicy wsk_produkt.
	bool is_free = false;	//Warto�� logiczna, kt�ra przyjmuje warto�� true gdy tablica nie jest pe�na, czyli przynajmniej jeden z element�w ma warto�� nullptr.
	int free_index = -1;	//Zmienna, kt�ra b�dzie przechowywa� indeks pierwszego pustego elementu tablicy wsk_produkt. Pocz�tkowa warto�� to -1, poniewa� �adna tablica nie mo�e mie� takiego indeksu.
	for (int i = 0; i < 4; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wsk_produkt.
	{
		if (lista.wsk_produkt[i] == nullptr) {	//Je�eli element tablicy wsk_produkt ma warto�� nullptr to wtedy warto�� logiczna is_free jest ustawiana na true.
			is_free = true;
			if (free_index == -1)	//Dodatkowo sprawdzane jest czy warto�� free_index to -1, je�li tak to przypisywana jest mu warto�� i. Dzi�ki temu produkty dodawane s� do tablicy po kolei.
				free_index = i;
		}else	//W przeciwnym wypadku do obecnej sumy dodawana jest cene obecnego elementu tablicy wsk_produkt.
			suma += lista.wsk_produkt[i]->cena;
	}
	if (is_free) {	//Je�eli tablica posiada pusty element to:
		if ((suma + produkt.cena) > lista.dostepny_budzet) {	//Je�li suma cen z cen� produktu kt�ry chcemy przypisa� jest wi�ksza od dost�pnego bud�etu wtedy nie dokonujemy przypisania produktu do tablicy i wypisujemy odpowiedni komunikat oraz obecna suma cen.
			cout << "Przekroczono budzet! Nie przypisano produktu do listy" << endl << "Obecna suma cen produktow: " << suma << endl;
		}
		else {	//W przeciwnym wypadku produkt jest przypisywany do tablicy wsk_produkt oraz wy�wietlany jest odpowiedni komunikat wraz z sum� cen produkt�w.
			lista.wsk_produkt[free_index] = &produkt;
			cout<<"Przypisano produkt "<<produkt.nazwa<<" do listy zakupow" << endl << "Obecna suma cen produktow: " << suma+produkt.cena << endl;
		}
	}
	else	//Gdy tablica jest pe�na, produkt nie jest przypisywany i wypisywany jest odpowiedni komunikat.
		cout << "Przekroczono maksymalna liczbe produktow! Nie przypisano produktu do listy" << endl;
}
void wyswietlListe(ListaZakupow& lista) {	//Funckja zaprzyja�niona z klas� ListaZakupow wy�wietlaj�ca nazwe i marke produkt�w b�d�cych elementami tablicy wsk_produkt.
	string Produkt::* wsk_tab[2];	//Utworzenie dwuelementowej tablicy wska�nik�w do p�l klasy Produkt typu string.
	wsk_tab[0] = &Produkt::nazwa;	//Przypisanie elementom tablicy referencji do nazwy i marki.
	wsk_tab[1] = &Produkt::marka;
	lista.wyswietl();	//Wy�wietlenie nazwy i bud�etu listy dzi�ki metodzie wyswietl().
	for (int i = 0; i < 4; i++)		//P�tla iteruj�ca po wszystkich elementach tablicy.
	{
		if (lista.wsk_produkt[i] != nullptr) {	//Je�eli element tablicy nie jest r�wny nullptr to wtedy wypisywane s� jego nazwa i marka dzi�ki wska�nikom do tych p�l.
			cout << lista.wsk_produkt[i]->*wsk_tab[0] << ", " << lista.wsk_produkt[i]->*wsk_tab[1] << endl;
		}
	}
}

int main() {
	//Utworzenie tablicy dynamicznej pi�cioelementowej klasy Produkt.
	Produkt* tab_prod = new Produkt[5];
	//Przypisanie warto�ci poszczeg�lnym elementom tablicy.
	tab_prod[0] = Produkt("Szybki i smaczny Rosol");
	tab_prod[1] = Produkt("Kurczak Pikantny", "Vifon", 1.69, 70, 9, 1.2, 3.2);
	tab_prod[2] = Produkt("Pomidorowa", "Amino", 2.19, 61, 10, 1.5, 3.5);
	tab_prod[3] = Produkt("Ser w ziolach", "Knorr", 2.29, 61, 10, 1.8, 4.8);
	for (int i = 0; i < 5; i++) //P�tla iteruj�ca po wszystkich elementach tablicy tab_prod i wy�wietlaj�ca ich dane za pomoc� metody wyswietl().
	{
		tab_prod[i].wyswietl();
	}
	cout << endl;
	//Utworzenie wska�nika do p�l klasy Produkt typu string, a nast�pnie przypisanie mu referencji do pola nazwa.
	string Produkt::*wsk_nazwa = &Produkt::nazwa;
	//Utworzenie wska�nika do metod klasy Produkt zwracaj�cych warto�� typu float i nie przyjmuj�cych argument�w, a nast�pnie przypisanie mu refencji do metody kaloryczno��.
	float (Produkt:: * wsk_kal)() = &Produkt::kalorycznosc;
	//Wy�wietlenie nazwy i u�ycie metody kaloryczno�� na ostatnim elemencie tablicy tab_prod dzi�ki wska�nikom do odpowiedniego pola i metody klasy Produkt.
	cout << tab_prod[4].*wsk_nazwa << " " << (tab_prod[4].*wsk_kal)() << " kcal" << endl;
	cout << endl;
	//Utworzenie obiektu klasy ListaZakupow u�ywaj�c domy�lnego konstruktora.
	ListaZakupow lista;
	//Wy�wietlenie nazwy i bud�etu obiektu lista dzi�ki metodzie wyswietl().
	lista.wyswietl();
	cout << endl;
	//Pr�ba dodania 4 produkt�w do tablicy w obiekcie lista dzi�ki funkcji dodajProdukt(ListaZakupow&, Produkt&).
	dodajProdukt(lista, tab_prod[4]); dodajProdukt(lista, tab_prod[1]); dodajProdukt(lista, tab_prod[3]); dodajProdukt(lista, tab_prod[2]); 
	cout << endl;
	//Wy�wietlenie produkt�w znajduj�cych si� w tablicy obiektu lista dzi�ki funkcji wyswietlListe(ListaZakupow&).
	wyswietlListe(lista);
	//Dealokacja pami�ci przyznanej tablicy dynamicznej tab_prod operatorem delete[], a nast�pnie przypisanie wska�nikowi tab_prod nullptr.
	delete[] tab_prod;
	tab_prod = nullptr;
	return 0;
}


