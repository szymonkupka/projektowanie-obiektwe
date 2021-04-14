#include <iostream>
#include <cmath>
#include <ctime>	//Biblioteka potrzebna do generatora liczb pseudolosowych.
#define M_PI       3.14159265358979323846

using namespace std;
//Deklaracja klas, kt�re s� u�ywane projekcie.
class Punkt;
class Prostokat;
class Kolo;

class Punkt {
public:		
	Punkt() : x(0), y(0) {}		//Konstruktor domy�lny, przypisuj�cy warto�ci za pomoc� listy inicjalizacyjnej, przypisuje pocz�tek uk�adu wsp�rz�dnych (0,0).
	Punkt(float x1, float y1) : x(x1), y(y1) {} //Konstruktor parametryzuj�cy, przyjmuj�cy warto�ci dla x i y, zapisuje je za pomoc� listy inicjalizacyjnej.
	void wyswietl() {	//Funkcja wypisuje na ekran sk�adowe x,y danego obiketu.
		cout << "Punkt (" << x << ", " << y << ")" << endl;
	}
	//Funkcje get zwracaj� warto�ci odpowiednich p�l prywatnych.
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	bool czyWspolne(Prostokat&);	//Deklaracja funkcji, jednak jej definicja jest poza klas�, ze wzgl�du na u�ycie obiektu klasy Prostok�t, kt�ry jest definiowany w p�niejszej cz�sci kodu.
	friend void ustawXY(Punkt& p, float x, float y); //Deklaracja przyja�ni funkcji globalnej.
private: 
	float x;	//Pola prywatne okre�lone w zadaniu.
	float y;
};
class Prostokat {
public:
	Prostokat() = delete;	//Usuni�cie domy�lnego konstruktora, nie jest potrzebny w wykonaniu zadania.
	//Konstruktory parametryzuj�ce przypisuj�ce odpowiednie warto�ci polom prywatnym, r�ni� si� tylko tym �e pierwszy przyjmuje dwie
	//zmienne zmiennoprzecinkowe, kt�re za pomoc� listy parametryzuj�cej przekazuje polu lewy_dolny, a drugi otrzymuje obiekt typu Punkt i przekazuje go polu.
	Prostokat(float x1, float y1, float szer1, float wys1) : lewy_dolny(x1,y1), szer(szer1), wys(wys1) {}
	Prostokat(Punkt& p1, float szer1, float wys1) : lewy_dolny(p1), szer(szer1), wys(wys1) {}
	friend void PokazInfo(Prostokat&);	//Definicja przyja�ni funkcji globalnej.
	friend bool Punkt::czyWspolne(Prostokat&); //Definicja przyja�ni metody klasy Punkt.
private:
	Punkt lewy_dolny;	//Pola prywatne okre�lone w zadaniu.
	float szer;
	float wys;
};
class Kolo {
public:
	Kolo() : srodek(0, 0), r(0) {} //Konstruktor domy�lny przypisuj�cy warto�ci 0 wszystkim polom prywatnym za pomoc� listy inicjalizuj�cej.
	//Konstruktory parametryzuj�ce przypisuj�ce odpowiednie warto�ci polom prywatnym, r�ni� si� tym �e pierwszy przyjmuje dwie zmienne
	//zmiennoprzecinkowe, kt�re za pomoc� listy parametryzuj�cej przekazuje polu srodek, a drugi otrzymuje obiekt typu Punkt i przekazuje go polu.
	Kolo(float x, float y, int r1) : srodek(x, y), r(r1) {}
	Kolo(Punkt& p1, int r1) : srodek(p1), r(r1) {}
	void setValues(float x, float y, int r1) { //Funkvja kopiuj�ca warto�ci przekazane wszystkim polom obiektu.
		ustawXY(srodek, x, y);
		r = r1;
	}
	//Funkcje get zwracaj� warto�ci odpowiednich p�l prywatnych.
	Punkt getSrodek() {
		return srodek;
	}
	int getPromien() {
		return r;
	}
	//Funkcja przyjmuje obiekt typu Kolo i sprawdza czy kolo przekazane i na kt�rym jest wywo�ana funkcja s� ze sob� styczne wewn�trznie
	//lub zewn�trznie, je�li tak to zwraca ona warto�� true, w przeciwnym razie false.
	bool czyStyczne(Kolo& kolo1) {
		//Obliczanie odleg�o�ci �rodk�w obu okr�g�w.
		double S = sqrt(pow(kolo1.getSrodek().getX() - srodek.getX(), 2) + pow(kolo1.getSrodek().getY() - srodek.getY(), 2));
		//Je�li okr�gi s� styczne zewn�trznie to odleg�o�� �rodk�w jest r�wna sumie promieni, a gdy wewn�trznie to jest ona r�wna ich r�nicy.
		if (S == abs(kolo1.getPromien() - r) || S == (kolo1.getPromien() + r))
			return true;
		return false;

	}
	friend void PokazInfo(Kolo&);	//Definicja przyja�ni z funkcj� globaln�.
private:
	Punkt srodek;
	int r;
};

void ustawXY(Punkt& p, float x, float y) {	//Funckja zaprzyja�niona z klas� Punkt, przypisuje warto�ci przekazane x,y polom przekazanego obiektu.
	p.x = x;
	p.y = y;
}

void PokazInfo(Prostokat& pr1) { //Funkcja zaprzyja�niona z klas� Prostok�t, wy�wietla wsp�rz�dne wierzcho�k�w przekazanego obiektu oraz pole tego prostok�ta.
	cout << "D (" << pr1.lewy_dolny.getX() << ", " << pr1.lewy_dolny.getY()+pr1.wys << ")\t";
	cout << "C (" << pr1.lewy_dolny.getX()+pr1.szer << ", " << pr1.lewy_dolny.getY() + pr1.wys << ")" << endl;
	cout << "A (" << pr1.lewy_dolny.getX() << ", " << pr1.lewy_dolny.getY() << ")\t";
	cout << "B (" << pr1.lewy_dolny.getX() + pr1.szer << ", " << pr1.lewy_dolny.getY() << ")" << endl;
	cout << "Pole prostokata wynosi: " << pr1.szer * pr1.wys << endl;
}
void PokazInfo(Kolo& k1) { //Funkcja zaprzyja�niona z klas� Kolo, wy�wietla wsp�rz�dne �rodka przekazanego obiektu, jak r�wnie� jego promie� i pole.
	cout << "Kolo o srodku: ";
	k1.srodek.wyswietl();
	cout << "Promien kola: " << k1.r << ", pole kola: " << k1.r * k1.r * (float)M_PI << endl;
}

int main() {
	//Zainicjowanie generatora liczb pseudolosowych.
	srand(time(NULL));
	//Podpunkt 3, utworzenie obiekt�w klasy Punkt, nast�pnie przypisanie im warto�ci za pomoc� funkcji ustawXY(), a potem wy�wietlanie 
	//ich za pomoc� metody wyswietl().
	Punkt p1, p2, p3;
	ustawXY(p1, 5, 2); ustawXY(p2, -7, -7); ustawXY(p3, 1.25, 2.5);
	p1.wyswietl(); p2.wyswietl(); p3.wyswietl();
	cout << endl;

	//Podpunkt 3, utworzenie obiektu i przypisanie mu warto�ci za pomoc� konstruktora parametryzuj�cego.
	Prostokat prost1(-8, -6, 13, 10);
	//Sprawdzenie czy dane punkty p1,p2,p3 nale�� do prostok�t prost1 za pomoc� metody czyWspolne() klasy Punkt, nast�pnie wypisywanie
	//warto�ci logicznej true, false na ekranie.
	cout << boolalpha;
	cout << "Czy punkt pierwszy zawiera sie w prostokacie: " << p1.czyWspolne(prost1) << endl;
	cout << "Czy punkt drugi zawiera sie w prostokacie: " << p2.czyWspolne(prost1) << endl;
	cout << "Czy punkt trzeci zawiera sie w prostokacie: " << p3.czyWspolne(prost1) << endl << endl;

	//Podpunkt 4, utworzenie obiektu typu Kolo i ustalenie jego warto�ci przez konstruktor parametryzuj�cy, nast�pnie wypisanie danych
	//ko�a k1 i prostok�ta prost1 za pomoc� funkcji globalnej PokazInfo().
	Kolo k1(0, 0, 10);
	PokazInfo(prost1);
	cout << endl;
	PokazInfo(k1);
	cout << endl;

	//Podpunkt 5, dynamiczne zadeklarowanie tablicy 1000 element�w typu Kolo.
	int n = 1000;
	Kolo* tab_kol = new Kolo[n];
	//Przypisanie warto�ci pseudolosowych ka�demu elementowi tablicy, dla x i y z przedzia�u [-20, 20], a dla r [1,20] za pomoc� metody setValues().
	for (int i = 0; i < n; i++)
	{	
		//Aby losowa� z przedzia�u [a,b] u�ywaj�c rand(), wykonujemy dzia�anie a + rand() % (b - a + 1).
		int x = -20 + rand() % 41; 
		int y = -20 + rand() % 41;
		int r = 1 + rand() % 20;
		tab_kol[i].setValues(x,y,r);
	}

	//Podpunkt 6, zliczanie z iloma ko�ami o losowo wylosowanych wsp�rz�dnych �rodka i promieniu obiekt k1 jest styczny za pomoc� metody czyStyczne().
	int liczba_kol_stycznych = 0;
	for (int i = 0; i < n; i++) {
		if (k1.czyStyczne(tab_kol[i]))
			liczba_kol_stycznych++;
	}
	//Wy�wietlanie ilo�ci stycznych z okr�giem k1 okr�g�w. 
	cout << "Z " << n << " losowo wygerowanych kol " << liczba_kol_stycznych << " jest styczna do kola k1" << endl;
	
	//Dealokacja pami�ci tablicy tab_kol, a nast�pnie ustawianie warto�ci wska�nika tab_kol na NULL.
	delete[] tab_kol;
	tab_kol = NULL;
	return 0;
}

bool Punkt::czyWspolne(Prostokat& pr1) { //Definicja metody klasy Punkt przyjmuj�cej jako argument obiekt klasy Prostok�t.
	//Sprawdzanie czy punkt na kt�rym jest wywo�ana funkcja zawiera si� przestrzeni przekazanego prostok�ta, je�li tak to zwracana jest
	//warto�� logiczna true, w przeciwnym razie false.
	if ((x >= pr1.lewy_dolny.x && x <= pr1.lewy_dolny.x + pr1.szer) && (y >= pr1.lewy_dolny.y && y <= pr1.lewy_dolny.y + pr1.wys))
		return true;
	return false;
}