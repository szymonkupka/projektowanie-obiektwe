#include <iostream>

using namespace std;

class Bohater {
public: 
	Bohater() {						//Utworzenie domy�lnego konstruktora przypisuj�cego domy�lne warto�ci wszystkim prywatnym polom
		pseudonim = "SirStock";		//oraz zwi�kszaj�cego licznik odpowiadaj�cy za przechowywanie liczby obiekt�w utworzonym 
		klasa = "Magik";			//na danej klasie o jeden.
		sila_ataku = 1;
		licznik++;
	}
	Bohater(string nick, string klasa_post, int sila) {		//Utworzenia konstruktora parametryzuj�cego, kt�ry przyjmuje jako 
		pseudonim = nick;			//parametry zmienne, kt�re zostan� przypisane odpowiednie pola prywatne. R�wnie� konstruktor
		klasa = klasa_post;			//ten zwi�ksza licznik o jeden.
		sila_ataku = sila;
		licznik++;
	}
	~Bohater() {					//Destruktor odpowiada za zmiejszenie licznika o jeden, w trakcie niszczenia obiektu, aby
		licznik--;					//prawid�owo zlicza� ilo�� obecn� ilo�� obiekt�w.
	}
	//Metody get pobieraj� odpowiednie pola oraz zwracaj� ich warto�ci. 
	string getPseudonim() {
		return pseudonim;
	}
	string getKlasa() {
		return klasa;
	}
	int getSila(){
		return sila_ataku;
	}
	//Metody set przyjmuj� jako parametry odpowiednie warto�ci i przypisuj� je prywatnym polom. Metody te przypisuj� warto�ci
	//jednemu lub kilku polom. 
	void setSila(int sila){
		sila_ataku = sila;
	}
	void setAll(string nick, string klasa_post, int sila) {
		pseudonim = nick;
		klasa = klasa_post;
		sila_ataku = sila;
	}
	void wyswietlStatystyki() {		//Metoda s�u��ca wy�wietleniu wszystkich p�l prywatnych w konsoli.
		cout << pseudonim << " " << klasa << " " << sila_ataku << endl;
	}
	//Statyczna metoda, kt�ra wypisuje obecn� ilo�� utworzonych obiekt�w klasy. Metod� statyczn� mo�emy wywo�a� bez potrzeby 
	//odwo�ania si� do konkretnego obiektu.
	static void getLicznik() {		
		cout << "Liczba obiektow: "<<licznik<<endl;
	}

private:							//Deklaracja prywatnych p�l okre�lonych w zadaniu.
	string pseudonim;
	string klasa;
	int sila_ataku;
	static int licznik;
};
int Bohater::licznik = 0;			//Deklaracja poza klas� statycznej zmiennej licznik oraz przypisanie jej pocz�tkowej warto�ci.

class Ekwipunek {
public:
	Ekwipunek() {					//Utworzenie domy�lnego konstruktora przypisuj�cego domy�lne warto�ci wszystkim prywatnym polom
		rodzaj = "buty";			//oraz utworzenie nowego obiektu typu Bohater z domy�lnym konstruktorem. R�wnie� zostaje przypisana
		material = "skora";			//warto�� prawda polu czyDomyslny, kt�ry przechowuje informacje o typie wywo�anego konstruktora.
		wartosc = 1;
		wsk_bohater = new Bohater();
		czyDomyslny = true;
	}
	Ekwipunek(string rodzaj, string material, int wartosc, Bohater* wsk){ //Utworzenia konstruktora parametryzuj�cego,  
		this->rodzaj = rodzaj;		//kt�ry przyjmuje warto�ci do przypisania poszczeg�lnym polom prywatnym. R�wnie� zostaje 
		this->material = material;	//przypisana warto�� false polu czyDomyslny, poniewa� zosta� u�yty konstruktor parametryzuj�cy.
		this->wartosc = wartosc;
		this->wsk_bohater = wsk;
		czyDomyslny = false;
	}
	~Ekwipunek() {					//Destruktor pos�u�y nam do zniszcznia obiektu utworzenego przez domy�lny konstruktor.
		if (czyDomyslny)			//Sprawdza on funkcj� if czy zosta� u�yty domy�lny konstruktor dzi�ki polu czyDomyslny, 
			delete wsk_bohater;		//a nast�pnie usuwa on obiekt operatorem delete.
	}
	//Metody get zwracaj� warto�ci odpowiednich p�l prywatnych.
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
private:							//Deklaracja prywatnych p�l okre�lonych w zadaniu oraz dodatkowego pola typu logicznego czyDomyslny
	string rodzaj;					//kt�ry przechowuje informacj� o wywo�aniu konstruktora domy�lnego, s�u��ca do p�niejszej
	string material;				//destrukcji obiektu utworzonego przez ten konstruktor.
	int wartosc;
	Bohater* wsk_bohater;
	bool czyDomyslny;
};

int main() {
	//Utworzenie obiektu za pomoc� operatora new oraz u�ycie konstruktora parametryzuj�cego
	Bohater* Gandalf = new Bohater("Gandalf", "Czarodziej", 10);
	//Wy�wietlenie p�l obiektu za pomoc� metod get
	cout << "Wypisanie wartosci pol po utworzeniu obiektu:" << endl;
	cout << Gandalf->getPseudonim() << " " << Gandalf->getKlasa() << " " << Gandalf->getSila() << endl;
	//Zmiana warto�ci sila_ataku obiektu za pomoc� metody setSila(int)
	Gandalf->setSila(30);
	//Wypisanie warto�ci p�l obiektu za pomoc� metody wyswietlStatystyki()
	cout << "Wypisanie wartosci pol obiektu po modyfikacji pola sila_ataku:" << endl;
	Gandalf->wyswietlStatystyki();

	//Przypisanie zmiennej rozmiar tablicy rozmiaru podanego w zadaniu, a nast�pnie utworzenie dynamicznej tablicy dwuwymiarowej 2x2
	//typu klasy Bohater za pomoc� wska�nik�w, operatora new oraz p�tli for.
	int rozmiar_tablicy = 2;
	Bohater** druzynaPierscienia = new Bohater* [rozmiar_tablicy];
	for (int i = 0; i < rozmiar_tablicy; ++i)
	{
		druzynaPierscienia[i] = new Bohater[rozmiar_tablicy];
	}
	//Zmiana warto�ci p�l z domy�lnych wszystkim elementom tablicy za pomoc� metody setAll(string,string,int).
	druzynaPierscienia[0][0].setAll("Frodo", "Hobbit", 2);
	druzynaPierscienia[0][1].setAll("Aragorn", "Krol", 15);
	druzynaPierscienia[1][0].setAll("Legolas", "Elf", 999);
	druzynaPierscienia[1][1].setAll("Gimli", "Krasnolud", 12);
	cout << endl;
	//Wypisywanie pola sila_ataku wszystkich element�w tablicy oraz obliczanie ich sumy, a nast�pnie jej wypisanie.
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
	//U�ycie statycznej metody klasy Bohater getLicznik() wy�wietlaj�cej liczb� obecnie utworzonych obiekt�w klasy Bohater.
	cout << "Wypisanie liczby obiektow przed usunieciem tablicy: " << endl;
	Bohater::getLicznik();
	//Dealokacja pami�ci przydzielonej tablicy dwuwymiarowej za pomoc� operatora delete.
	for (int i = 0; i < rozmiar_tablicy; ++i)
	{
		delete[] druzynaPierscienia[i];
	}
	delete[] druzynaPierscienia;
	//Wy�wietlenie ilo�ci obiekt�w po dealokacji pami�ci przeznaczonej dla tablicy obiekt�w klasy Bohater.
	cout << "Wypisanie liczby obiektow po usunieciu tablicy:" << endl;
	Bohater::getLicznik();
	cout << endl;

	//Utworzenie dw�ch obiekt�w klasy Ekwipunek za pomoc� operatora new oraz wykorzystanie konstruktora domy�lnego i parametryzuj�cego
	Ekwipunek* obiekt_ekw1 = new Ekwipunek();
	Ekwipunek* obiekt_ekw2 = new Ekwipunek("pancerz", "zelazo", 100, Gandalf);
	//Wypisanie na ekranie warto�ci p�l prywatnych za pomoc� odpowiednich metod get oraz wy�wietlenie warto�ci pola klasa obiektu
	//klasy Bohater, kt�rego wska�nik jest przechowywany w polu obiektu klasy Ekwipunek.
	cout << "Wypisanie poszczegolnych pol obiektow utworzonych na klasie Ekwipunek" << endl;
	cout << obiekt_ekw1->getRodzaj() << " " << obiekt_ekw1->getMaterial() << " " << obiekt_ekw1->getWartosc() 
		<< " klasa bohatera: " << obiekt_ekw1->getBohater()->getKlasa() << endl;
	cout << obiekt_ekw2->getRodzaj() << " " << obiekt_ekw2->getMaterial() << " " << obiekt_ekw2->getWartosc() 
		<< " klasa bohatera: " << obiekt_ekw2->getBohater()->getKlasa() << endl;
	//Pozosta�e obiekty zostaj� zniszczone, a pami�� zwolniona dzi�ki operatorowi delete.
	delete obiekt_ekw1;
	delete obiekt_ekw2;
	delete Gandalf;
	return 0;
}