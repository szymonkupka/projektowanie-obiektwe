#include <iostream>

using namespace std;

class Bohater {
public: 
	Bohater() {						//Utworzenie domyœlnego konstruktora przypisuj¹cego domyœlne wartoœci wszystkim prywatnym polom
		pseudonim = "SirStock";		//oraz zwiêkszaj¹cego licznik odpowiadaj¹cy za przechowywanie liczby obiektów utworzonym 
		klasa = "Magik";			//na danej klasie o jeden.
		sila_ataku = 1;
		licznik++;
	}
	Bohater(string nick, string klasa_post, int sila) {		//Utworzenia konstruktora parametryzuj¹cego, który przyjmuje jako 
		pseudonim = nick;			//parametry zmienne, które zostan¹ przypisane odpowiednie pola prywatne. Równie¿ konstruktor
		klasa = klasa_post;			//ten zwiêksza licznik o jeden.
		sila_ataku = sila;
		licznik++;
	}
	~Bohater() {					//Destruktor odpowiada za zmiejszenie licznika o jeden, w trakcie niszczenia obiektu, aby
		licznik--;					//prawid³owo zliczaæ iloœæ obecn¹ iloœæ obiektów.
	}
	//Metody get pobieraj¹ odpowiednie pola oraz zwracaj¹ ich wartoœci. 
	string getPseudonim() {
		return pseudonim;
	}
	string getKlasa() {
		return klasa;
	}
	int getSila(){
		return sila_ataku;
	}
	//Metody set przyjmuj¹ jako parametry odpowiednie wartoœci i przypisuj¹ je prywatnym polom. Metody te przypisuj¹ wartoœci
	//jednemu lub kilku polom. 
	void setSila(int sila){
		sila_ataku = sila;
	}
	void setAll(string nick, string klasa_post, int sila) {
		pseudonim = nick;
		klasa = klasa_post;
		sila_ataku = sila;
	}
	void wyswietlStatystyki() {		//Metoda s³u¿¹ca wyœwietleniu wszystkich pól prywatnych w konsoli.
		cout << pseudonim << " " << klasa << " " << sila_ataku << endl;
	}
	//Statyczna metoda, która wypisuje obecn¹ iloœæ utworzonych obiektów klasy. Metodê statyczn¹ mo¿emy wywo³aæ bez potrzeby 
	//odwo³ania siê do konkretnego obiektu.
	static void getLicznik() {		
		cout << "Liczba obiektow: "<<licznik<<endl;
	}

private:							//Deklaracja prywatnych pól okreœlonych w zadaniu.
	string pseudonim;
	string klasa;
	int sila_ataku;
	static int licznik;
};
int Bohater::licznik = 0;			//Deklaracja poza klas¹ statycznej zmiennej licznik oraz przypisanie jej pocz¹tkowej wartoœci.

class Ekwipunek {
public:
	Ekwipunek() {					//Utworzenie domyœlnego konstruktora przypisuj¹cego domyœlne wartoœci wszystkim prywatnym polom
		rodzaj = "buty";			//oraz utworzenie nowego obiektu typu Bohater z domyœlnym konstruktorem. Równie¿ zostaje przypisana
		material = "skora";			//wartoœæ prawda polu czyDomyslny, który przechowuje informacje o typie wywo³anego konstruktora.
		wartosc = 1;
		wsk_bohater = new Bohater();
		czyDomyslny = true;
	}
	Ekwipunek(string rodzaj, string material, int wartosc, Bohater* wsk){ //Utworzenia konstruktora parametryzuj¹cego,  
		this->rodzaj = rodzaj;		//który przyjmuje wartoœci do przypisania poszczególnym polom prywatnym. Równie¿ zostaje 
		this->material = material;	//przypisana wartoœæ false polu czyDomyslny, poniewa¿ zosta³ u¿yty konstruktor parametryzuj¹cy.
		this->wartosc = wartosc;
		this->wsk_bohater = wsk;
		czyDomyslny = false;
	}
	~Ekwipunek() {					//Destruktor pos³u¿y nam do zniszcznia obiektu utworzenego przez domyœlny konstruktor.
		if (czyDomyslny)			//Sprawdza on funkcj¹ if czy zosta³ u¿yty domyœlny konstruktor dziêki polu czyDomyslny, 
			delete wsk_bohater;		//a nastêpnie usuwa on obiekt operatorem delete.
	}
	//Metody get zwracaj¹ wartoœci odpowiednich pól prywatnych.
	string getRodzaj() {
		return rodzaj;
	}
	string getMaterial() {
		return material;
	}
	int getWartosc() {
		return wartosc;
	}
	Bohater* getBohater() {
		return wsk_bohater;
	}
private:							//Deklaracja prywatnych pól okreœlonych w zadaniu oraz dodatkowego pola typu logicznego czyDomyslny
	string rodzaj;					//który przechowuje informacjê o wywo³aniu konstruktora domyœlnego, s³u¿¹ca do póŸniejszej
	string material;				//destrukcji obiektu utworzonego przez ten konstruktor.
	int wartosc;
	Bohater* wsk_bohater;
	bool czyDomyslny;
};

int main() {
	//Utworzenie obiektu za pomoc¹ operatora new oraz u¿ycie konstruktora parametryzuj¹cego
	Bohater* Gandalf = new Bohater("Gandalf", "Czarodziej", 10);
	//Wyœwietlenie pól obiektu za pomoc¹ metod get
	cout << "Wypisanie wartosci pol po utworzeniu obiektu:" << endl;
	cout << Gandalf->getPseudonim() << " " << Gandalf->getKlasa() << " " << Gandalf->getSila() << endl;
	//Zmiana wartoœci sila_ataku obiektu za pomoc¹ metody setSila(int)
	Gandalf->setSila(30);
	//Wypisanie wartoœci pól obiektu za pomoc¹ metody wyswietlStatystyki()
	cout << "Wypisanie wartosci pol obiektu po modyfikacji pola sila_ataku:" << endl;
	Gandalf->wyswietlStatystyki();

	//Przypisanie zmiennej rozmiar tablicy rozmiaru podanego w zadaniu, a nastêpnie utworzenie dynamicznej tablicy dwuwymiarowej 2x2
	//typu klasy Bohater za pomoc¹ wskaŸników, operatora new oraz pêtli for.
	int rozmiar_tablicy = 2;
	Bohater** druzynaPierscienia = new Bohater* [rozmiar_tablicy];
	for (int i = 0; i < rozmiar_tablicy; ++i)
	{
		druzynaPierscienia[i] = new Bohater[rozmiar_tablicy];
	}
	//Zmiana wartoœci pól z domyœlnych wszystkim elementom tablicy za pomoc¹ metody setAll(string,string,int).
	druzynaPierscienia[0][0].setAll("Frodo", "Hobbit", 2);
	druzynaPierscienia[0][1].setAll("Aragorn", "Krol", 15);
	druzynaPierscienia[1][0].setAll("Legolas", "Elf", 999);
	druzynaPierscienia[1][1].setAll("Gimli", "Krasnolud", 12);
	cout << endl;
	//Wypisywanie pola sila_ataku wszystkich elementów tablicy oraz obliczanie ich sumy, a nastêpnie jej wypisanie.
	cout << "Wypisanie sil poszczegolnego elementu tablicy: " << endl;
	int silaDruzyny = 0;
	for (int i = 0; i < rozmiar_tablicy; i++)
	{
		for (int j = 0; j < rozmiar_tablicy; j++)
		{
			cout << druzynaPierscienia[i][j].getPseudonim() << " sila: " << druzynaPierscienia[i][j].getSila()<<endl;
			silaDruzyny += druzynaPierscienia[i][j].getSila();
		}
	}
	cout << "Laczna sila druzyny: " << silaDruzyny<<endl<<endl;
	//U¿ycie statycznej metody klasy Bohater getLicznik() wyœwietlaj¹cej liczbê obecnie utworzonych obiektów klasy Bohater.
	cout << "Wypisanie liczby obiektow przed usunieciem tablicy: " << endl;
	Bohater::getLicznik();
	//Dealokacja pamiêci przydzielonej tablicy dwuwymiarowej za pomoc¹ operatora delete.
	for (int i = 0; i < rozmiar_tablicy; ++i)
	{
		delete[] druzynaPierscienia[i];
	}
	delete[] druzynaPierscienia;
	//Wyœwietlenie iloœci obiektów po dealokacji pamiêci przeznaczonej dla tablicy obiektów klasy Bohater.
	cout << "Wypisanie liczby obiektow po usunieciu tablicy:" << endl;
	Bohater::getLicznik();
	cout << endl;

	//Utworzenie dwóch obiektów klasy Ekwipunek za pomoc¹ operatora new oraz wykorzystanie konstruktora domyœlnego i parametryzuj¹cego
	Ekwipunek* obiekt_ekw1 = new Ekwipunek();
	Ekwipunek* obiekt_ekw2 = new Ekwipunek("pancerz", "zelazo", 100, Gandalf);
	//Wypisanie na ekranie wartoœci pól prywatnych za pomoc¹ odpowiednich metod get oraz wyœwietlenie wartoœci pola klasa obiektu
	//klasy Bohater, którego wskaŸnik jest przechowywany w polu obiektu klasy Ekwipunek.
	cout << "Wypisanie poszczegolnych pol obiektow utworzonych na klasie Ekwipunek" << endl;
	cout << obiekt_ekw1->getRodzaj() << " " << obiekt_ekw1->getMaterial() << " " << obiekt_ekw1->getWartosc() 
		<< " klasa bohatera: " << obiekt_ekw1->getBohater()->getKlasa() << endl;
	cout << obiekt_ekw2->getRodzaj() << " " << obiekt_ekw2->getMaterial() << " " << obiekt_ekw2->getWartosc() 
		<< " klasa bohatera: " << obiekt_ekw2->getBohater()->getKlasa() << endl;
	//Pozosta³e obiekty zostaj¹ zniszczone, a pamiêæ zwolniona dziêki operatorowi delete.
	delete obiekt_ekw1;
	delete obiekt_ekw2;
	delete Gandalf;
	return 0;
}