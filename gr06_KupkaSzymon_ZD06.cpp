#include <iostream>

using namespace std;

class Produkt {
public:
	//Konstruktor parametryzuj¹cy z domyœlnymi wartoœciami przypisuj¹cy wartoœci polom przez listê inicjalizacyjn¹.
	Produkt(string Nazwa="Pikantna Chinska", string Marka="Lewiatan", float Cena=0.89, int Masa=60, float wegl=51.8, float bial=7.6, float tluszcz=19) : nazwa(Nazwa), marka(Marka), cena(Cena), 
		masa(Masa), weglowodany_udzial(wegl), bialko_udzial(bial), tluszcz_udzial(tluszcz){}
	float kalorycznosc(){ //Metoda oblicza i zwraca kalorycznoœæ.
		return masa * (weglowodany_udzial * 4 + bialko_udzial * 4 + tluszcz_udzial * 9) / 100;
	}
	void wyswietl() { //Metoda wypisuje na ekran dane obiektu.
		cout << nazwa << ", " << marka << ", " << cena << " zl, " << masa << "g, Weglowodany " << weglowodany_udzial << "%, bialko " << bialko_udzial << "%, tluszcz " << tluszcz_udzial << "% " << endl;
	}
	//Pola publiczne zadeklarowane w treœci zadania.
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
	//Deklaracja przyjaŸni dwóch funkcji zaprzyjaŸnionych.
	friend void dodajProdukt(ListaZakupow&, Produkt&);
	friend void wyswietlListe(ListaZakupow&);
	//Konstruktor parametryzuj¹cy z domyœlnymi wartoœciami, przypisuj¹cy wartoœci odpowiednim polom prywatnym dziêki liœcie inicjalizacyjnej.
	ListaZakupow(string nazwa="Zakupy", float budzet=5) : nazwa_listy(nazwa), dostepny_budzet(budzet) {
		wsk_produkt = new Produkt * [4];	//Utworzenie czteroelementowej tablicy dynamicznej wskaŸników do klasy Produkt.
		for (int i = 0; i < 4; i++)		//Pêtla iteruj¹ca po ka¿dym elemencie tablicy wsk_produkt.
		{
			wsk_produkt[i] = nullptr;	//Przypisanie nullptr wszystkim elementom tablicy wsk_produkt.
		}
	}
	~ListaZakupow() {	//Destruktor odpowiedzialny za dealokacjê pamiêci tablicy utworzonej w konstruktorze.
		delete[] wsk_produkt;	//Dealokacja pamiêci tablicy dziêki operatorowi delete.
		wsk_produkt = nullptr;	//Przypisanie wskaŸnikowi wsk_produkt nullptr.
	}
	void wyswietl() {	//Metoda wyœwietlaj¹ca nazwê i bud¿et obiektu.
		cout << "Lista: " << nazwa_listy << ", budzet: " << dostepny_budzet << " zl " << endl;
	}
private:
	//Pola prywatne zadeklarowane w zadaniu.
	string nazwa_listy;
	const float dostepny_budzet;
	Produkt** wsk_produkt;	//WskaŸnik na wskaŸnik klasy Produkt potrzebny do utworzenia tablicy wskaŸników.
};
void dodajProdukt(ListaZakupow& lista, Produkt& produkt) //Funckja zaprzyjaŸniona z klas¹ ListaZakupow, odpowiedzialna za dodanie elementu do tablicy wsk_produkt.
{
	//Zmienne pomocnicze potrzebne do przypisania elementu lub wypisania odpowiednich komunikatów.
	float suma = 0;			//Zmienna zliczaj¹ca sumê cen produktów z tablicy wsk_produkt.
	bool is_free = false;	//Wartoœæ logiczna, która przyjmuje wartoœæ true gdy tablica nie jest pe³na, czyli przynajmniej jeden z elementów ma wartoœæ nullptr.
	int free_index = -1;	//Zmienna, która bêdzie przechowywaæ indeks pierwszego pustego elementu tablicy wsk_produkt. Pocz¹tkowa wartoœæ to -1, poniewa¿ ¿adna tablica nie mo¿e mieæ takiego indeksu.
	for (int i = 0; i < 4; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wsk_produkt.
	{
		if (lista.wsk_produkt[i] == nullptr) {	//Je¿eli element tablicy wsk_produkt ma wartoœæ nullptr to wtedy wartoœæ logiczna is_free jest ustawiana na true.
			is_free = true;
			if (free_index == -1)	//Dodatkowo sprawdzane jest czy wartoœæ free_index to -1, jeœli tak to przypisywana jest mu wartoœæ i. Dziêki temu produkty dodawane s¹ do tablicy po kolei.
				free_index = i;
		}else	//W przeciwnym wypadku do obecnej sumy dodawana jest cene obecnego elementu tablicy wsk_produkt.
			suma += lista.wsk_produkt[i]->cena;
	}
	if (is_free) {	//Je¿eli tablica posiada pusty element to:
		if ((suma + produkt.cena) > lista.dostepny_budzet) {	//Jeœli suma cen z cen¹ produktu który chcemy przypisaæ jest wiêksza od dostêpnego bud¿etu wtedy nie dokonujemy przypisania produktu do tablicy i wypisujemy odpowiedni komunikat oraz obecna suma cen.
			cout << "Przekroczono budzet! Nie przypisano produktu do listy" << endl << "Obecna suma cen produktow: " << suma << endl;
		}
		else {	//W przeciwnym wypadku produkt jest przypisywany do tablicy wsk_produkt oraz wyœwietlany jest odpowiedni komunikat wraz z sum¹ cen produktów.
			lista.wsk_produkt[free_index] = &produkt;
			cout<<"Przypisano produkt "<<produkt.nazwa<<" do listy zakupow" << endl << "Obecna suma cen produktow: " << suma+produkt.cena << endl;
		}
	}
	else	//Gdy tablica jest pe³na, produkt nie jest przypisywany i wypisywany jest odpowiedni komunikat.
		cout << "Przekroczono maksymalna liczbe produktow! Nie przypisano produktu do listy" << endl;
}
void wyswietlListe(ListaZakupow& lista) {	//Funckja zaprzyjaŸniona z klas¹ ListaZakupow wyœwietlaj¹ca nazwe i marke produktów bêd¹cych elementami tablicy wsk_produkt.
	string Produkt::* wsk_tab[2];	//Utworzenie dwuelementowej tablicy wskaŸników do pól klasy Produkt typu string.
	wsk_tab[0] = &Produkt::nazwa;	//Przypisanie elementom tablicy referencji do nazwy i marki.
	wsk_tab[1] = &Produkt::marka;
	lista.wyswietl();	//Wyœwietlenie nazwy i bud¿etu listy dziêki metodzie wyswietl().
	for (int i = 0; i < 4; i++)		//Pêtla iteruj¹ca po wszystkich elementach tablicy.
	{
		if (lista.wsk_produkt[i] != nullptr) {	//Je¿eli element tablicy nie jest równy nullptr to wtedy wypisywane s¹ jego nazwa i marka dziêki wskaŸnikom do tych pól.
			cout << lista.wsk_produkt[i]->*wsk_tab[0] << ", " << lista.wsk_produkt[i]->*wsk_tab[1] << endl;
		}
	}
}

int main() {
	//Utworzenie tablicy dynamicznej piêcioelementowej klasy Produkt.
	Produkt* tab_prod = new Produkt[5];
	//Przypisanie wartoœci poszczególnym elementom tablicy.
	tab_prod[0] = Produkt("Szybki i smaczny Rosol");
	tab_prod[1] = Produkt("Kurczak Pikantny", "Vifon", 1.69, 70, 9, 1.2, 3.2);
	tab_prod[2] = Produkt("Pomidorowa", "Amino", 2.19, 61, 10, 1.5, 3.5);
	tab_prod[3] = Produkt("Ser w ziolach", "Knorr", 2.29, 61, 10, 1.8, 4.8);
	for (int i = 0; i < 5; i++) //Pêtla iteruj¹ca po wszystkich elementach tablicy tab_prod i wyœwietlaj¹ca ich dane za pomoc¹ metody wyswietl().
	{
		tab_prod[i].wyswietl();
	}
	cout << endl;
	//Utworzenie wskaŸnika do pól klasy Produkt typu string, a nastêpnie przypisanie mu referencji do pola nazwa.
	string Produkt::*wsk_nazwa = &Produkt::nazwa;
	//Utworzenie wskaŸnika do metod klasy Produkt zwracaj¹cych wartoœæ typu float i nie przyjmuj¹cych argumentów, a nastêpnie przypisanie mu refencji do metody kalorycznoœæ.
	float (Produkt:: * wsk_kal)() = &Produkt::kalorycznosc;
	//Wyœwietlenie nazwy i u¿ycie metody kalorycznoœæ na ostatnim elemencie tablicy tab_prod dziêki wskaŸnikom do odpowiedniego pola i metody klasy Produkt.
	cout << tab_prod[4].*wsk_nazwa << " " << (tab_prod[4].*wsk_kal)() << " kcal" << endl;
	cout << endl;
	//Utworzenie obiektu klasy ListaZakupow u¿ywaj¹c domyœlnego konstruktora.
	ListaZakupow lista;
	//Wyœwietlenie nazwy i bud¿etu obiektu lista dziêki metodzie wyswietl().
	lista.wyswietl();
	cout << endl;
	//Próba dodania 4 produktów do tablicy w obiekcie lista dziêki funkcji dodajProdukt(ListaZakupow&, Produkt&).
	dodajProdukt(lista, tab_prod[4]); dodajProdukt(lista, tab_prod[1]); dodajProdukt(lista, tab_prod[3]); dodajProdukt(lista, tab_prod[2]); 
	cout << endl;
	//Wyœwietlenie produktów znajduj¹cych siê w tablicy obiektu lista dziêki funkcji wyswietlListe(ListaZakupow&).
	wyswietlListe(lista);
	//Dealokacja pamiêci przyznanej tablicy dynamicznej tab_prod operatorem delete[], a nastêpnie przypisanie wskaŸnikowi tab_prod nullptr.
	delete[] tab_prod;
	tab_prod = nullptr;
	return 0;
}


