#include <iostream>
#include <cmath>
#include <ctime>	//Biblioteka potrzebna do generatora liczb pseudolosowych.
#define M_PI       3.14159265358979323846

using namespace std;
//Deklaracja klas, które s¹ u¿ywane projekcie.
class Punkt;
class Prostokat;
class Kolo;

class Punkt {
public:		
	Punkt() : x(0), y(0) {}		//Konstruktor domyœlny, przypisuj¹cy wartoœci za pomoc¹ listy inicjalizacyjnej, przypisuje pocz¹tek uk³adu wspó³rzêdnych (0,0).
	Punkt(float x1, float y1) : x(x1), y(y1) {} //Konstruktor parametryzuj¹cy, przyjmuj¹cy wartoœci dla x i y, zapisuje je za pomoc¹ listy inicjalizacyjnej.
	void wyswietl() {	//Funkcja wypisuje na ekran sk³adowe x,y danego obiketu.
		cout << "Punkt (" << x << ", " << y << ")" << endl;
	}
	//Funkcje get zwracaj¹ wartoœci odpowiednich pól prywatnych.
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	bool czyWspolne(Prostokat&);	//Deklaracja funkcji, jednak jej definicja jest poza klas¹, ze wzglêdu na u¿ycie obiektu klasy Prostok¹t, który jest definiowany w póŸniejszej czêsci kodu.
	friend void ustawXY(Punkt& p, float x, float y); //Deklaracja przyjaŸni funkcji globalnej.
private: 
	float x;	//Pola prywatne okreœlone w zadaniu.
	float y;
};
class Prostokat {
public:
	Prostokat() = delete;	//Usuniêcie domyœlnego konstruktora, nie jest potrzebny w wykonaniu zadania.
	//Konstruktory parametryzuj¹ce przypisuj¹ce odpowiednie wartoœci polom prywatnym, ró¿ni¹ siê tylko tym ¿e pierwszy przyjmuje dwie
	//zmienne zmiennoprzecinkowe, które za pomoc¹ listy parametryzuj¹cej przekazuje polu lewy_dolny, a drugi otrzymuje obiekt typu Punkt i przekazuje go polu.
	Prostokat(float x1, float y1, float szer1, float wys1) : lewy_dolny(x1,y1), szer(szer1), wys(wys1) {}
	Prostokat(Punkt& p1, float szer1, float wys1) : lewy_dolny(p1), szer(szer1), wys(wys1) {}
	friend void PokazInfo(Prostokat&);	//Definicja przyjaŸni funkcji globalnej.
	friend bool Punkt::czyWspolne(Prostokat&); //Definicja przyjaŸni metody klasy Punkt.
private:
	Punkt lewy_dolny;	//Pola prywatne okreœlone w zadaniu.
	float szer;
	float wys;
};
class Kolo {
public:
	Kolo() : srodek(0, 0), r(0) {} //Konstruktor domyœlny przypisuj¹cy wartoœci 0 wszystkim polom prywatnym za pomoc¹ listy inicjalizuj¹cej.
	//Konstruktory parametryzuj¹ce przypisuj¹ce odpowiednie wartoœci polom prywatnym, ró¿ni¹ siê tym ¿e pierwszy przyjmuje dwie zmienne
	//zmiennoprzecinkowe, które za pomoc¹ listy parametryzuj¹cej przekazuje polu srodek, a drugi otrzymuje obiekt typu Punkt i przekazuje go polu.
	Kolo(float x, float y, int r1) : srodek(x, y), r(r1) {}
	Kolo(Punkt& p1, int r1) : srodek(p1), r(r1) {}
	void setValues(float x, float y, int r1) { //Funkvja kopiuj¹ca wartoœci przekazane wszystkim polom obiektu.
		ustawXY(srodek, x, y);
		r = r1;
	}
	//Funkcje get zwracaj¹ wartoœci odpowiednich pól prywatnych.
	Punkt getSrodek() {
		return srodek;
	}
	int getPromien() {
		return r;
	}
	//Funkcja przyjmuje obiekt typu Kolo i sprawdza czy kolo przekazane i na którym jest wywo³ana funkcja s¹ ze sob¹ styczne wewnêtrznie
	//lub zewnêtrznie, jeœli tak to zwraca ona wartoœæ true, w przeciwnym razie false.
	bool czyStyczne(Kolo& kolo1) {
		//Obliczanie odleg³oœci œrodków obu okrêgów.
		double S = sqrt(pow(kolo1.getSrodek().getX() - srodek.getX(), 2) + pow(kolo1.getSrodek().getY() - srodek.getY(), 2));
		//Jeœli okrêgi s¹ styczne zewnêtrznie to odleg³oœæ œrodków jest równa sumie promieni, a gdy wewnêtrznie to jest ona równa ich ró¿nicy.
		if (S == abs(kolo1.getPromien() - r) || S == (kolo1.getPromien() + r))
			return true;
		return false;

	}
	friend void PokazInfo(Kolo&);	//Definicja przyjaŸni z funkcj¹ globaln¹.
private:
	Punkt srodek;
	int r;
};

void ustawXY(Punkt& p, float x, float y) {	//Funckja zaprzyjaŸniona z klas¹ Punkt, przypisuje wartoœci przekazane x,y polom przekazanego obiektu.
	p.x = x;
	p.y = y;
}

void PokazInfo(Prostokat& pr1) { //Funkcja zaprzyjaŸniona z klas¹ Prostok¹t, wyœwietla wspó³rzêdne wierzcho³ków przekazanego obiektu oraz pole tego prostok¹ta.
	cout << "D (" << pr1.lewy_dolny.getX() << ", " << pr1.lewy_dolny.getY()+pr1.wys << ")\t";
	cout << "C (" << pr1.lewy_dolny.getX()+pr1.szer << ", " << pr1.lewy_dolny.getY() + pr1.wys << ")" << endl;
	cout << "A (" << pr1.lewy_dolny.getX() << ", " << pr1.lewy_dolny.getY() << ")\t";
	cout << "B (" << pr1.lewy_dolny.getX() + pr1.szer << ", " << pr1.lewy_dolny.getY() << ")" << endl;
	cout << "Pole prostokata wynosi: " << pr1.szer * pr1.wys << endl;
}
void PokazInfo(Kolo& k1) { //Funkcja zaprzyjaŸniona z klas¹ Kolo, wyœwietla wspó³rzêdne œrodka przekazanego obiektu, jak równie¿ jego promieñ i pole.
	cout << "Kolo o srodku: ";
	k1.srodek.wyswietl();
	cout << "Promien kola: " << k1.r << ", pole kola: " << k1.r * k1.r * (float)M_PI << endl;
}

int main() {
	//Zainicjowanie generatora liczb pseudolosowych.
	srand(time(NULL));
	//Podpunkt 3, utworzenie obiektów klasy Punkt, nastêpnie przypisanie im wartoœci za pomoc¹ funkcji ustawXY(), a potem wyœwietlanie 
	//ich za pomoc¹ metody wyswietl().
	Punkt p1, p2, p3;
	ustawXY(p1, 5, 2); ustawXY(p2, -7, -7); ustawXY(p3, 1.25, 2.5);
	p1.wyswietl(); p2.wyswietl(); p3.wyswietl();
	cout << endl;

	//Podpunkt 3, utworzenie obiektu i przypisanie mu wartoœci za pomoc¹ konstruktora parametryzuj¹cego.
	Prostokat prost1(-8, -6, 13, 10);
	//Sprawdzenie czy dane punkty p1,p2,p3 nale¿¹ do prostok¹t prost1 za pomoc¹ metody czyWspolne() klasy Punkt, nastêpnie wypisywanie
	//wartoœci logicznej true, false na ekranie.
	cout << boolalpha;
	cout << "Czy punkt pierwszy zawiera sie w prostokacie: " << p1.czyWspolne(prost1) << endl;
	cout << "Czy punkt drugi zawiera sie w prostokacie: " << p2.czyWspolne(prost1) << endl;
	cout << "Czy punkt trzeci zawiera sie w prostokacie: " << p3.czyWspolne(prost1) << endl << endl;

	//Podpunkt 4, utworzenie obiektu typu Kolo i ustalenie jego wartoœci przez konstruktor parametryzuj¹cy, nastêpnie wypisanie danych
	//ko³a k1 i prostok¹ta prost1 za pomoc¹ funkcji globalnej PokazInfo().
	Kolo k1(0, 0, 10);
	PokazInfo(prost1);
	cout << endl;
	PokazInfo(k1);
	cout << endl;

	//Podpunkt 5, dynamiczne zadeklarowanie tablicy 1000 elementów typu Kolo.
	int n = 1000;
	Kolo* tab_kol = new Kolo[n];
	//Przypisanie wartoœci pseudolosowych ka¿demu elementowi tablicy, dla x i y z przedzia³u [-20, 20], a dla r [1,20] za pomoc¹ metody setValues().
	for (int i = 0; i < n; i++)
	{	
		//Aby losowaæ z przedzia³u [a,b] u¿ywaj¹c rand(), wykonujemy dzia³anie a + rand() % (b - a + 1).
		int x = -20 + rand() % 41; 
		int y = -20 + rand() % 41;
		int r = 1 + rand() % 20;
		tab_kol[i].setValues(x,y,r);
	}

	//Podpunkt 6, zliczanie z iloma ko³ami o losowo wylosowanych wspó³rzêdnych œrodka i promieniu obiekt k1 jest styczny za pomoc¹ metody czyStyczne().
	int liczba_kol_stycznych = 0;
	for (int i = 0; i < n; i++) {
		if (k1.czyStyczne(tab_kol[i]))
			liczba_kol_stycznych++;
	}
	//Wyœwietlanie iloœci stycznych z okrêgiem k1 okrêgów. 
	cout << "Z " << n << " losowo wygerowanych kol " << liczba_kol_stycznych << " jest styczna do kola k1" << endl;
	
	//Dealokacja pamiêci tablicy tab_kol, a nastêpnie ustawianie wartoœci wskaŸnika tab_kol na NULL.
	delete[] tab_kol;
	tab_kol = NULL;
	return 0;
}

bool Punkt::czyWspolne(Prostokat& pr1) { //Definicja metody klasy Punkt przyjmuj¹cej jako argument obiekt klasy Prostok¹t.
	//Sprawdzanie czy punkt na którym jest wywo³ana funkcja zawiera siê przestrzeni przekazanego prostok¹ta, jeœli tak to zwracana jest
	//wartoœæ logiczna true, w przeciwnym razie false.
	if ((x >= pr1.lewy_dolny.x && x <= pr1.lewy_dolny.x + pr1.szer) && (y >= pr1.lewy_dolny.y && y <= pr1.lewy_dolny.y + pr1.wys))
		return true;
	return false;
}