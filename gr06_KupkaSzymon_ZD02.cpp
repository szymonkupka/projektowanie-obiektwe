#include <iostream>
#include <cmath>

using namespace std;

class Ulamek {
public:
	Ulamek() = delete;				//Usuni�cie konstruktora domy�lnego, nie b�dzie potrzebny w tym zadaniu.
	Ulamek(int l) {					//Konstruktor konwertuj�cy, przyjmuje jako warto�� pojedy�cz� liczb� ca�kowit� i przypisuje jej
		licznik = l;				//warto�� licznikowi a mianownikowi 1 przez co warto�� u�amka jest r�wna liczbie ca�kowitej,
		mianownik = 1;
	}			
	Ulamek(int l, int m) {			//Konstruktor parametryzuj�cy, przypisuje odpowiednie warto�ci licznikowi i mianownikowi, jak r�wnie�
		licznik = l;				//sprawdza czy nie jest przesy�ana warto�� 0 dla mianownika, kt�ra nie mo�e zosta� przypisana aby 
		if (m != 0) {				//unikn�� dzielenia przez 0. W takim przypadku pokazywany jest komunikat oraz przysywana warto�� 1 mianownikowi.
			mianownik = m;
		}
		else {
			cout << "Mianownik nie moze byc rowny 0, przypisanie wartosci 1" << endl;
			mianownik = 1;
		}
	}
	//Funkcje get zwracaj� warto�ci odpowiednich prywatnych p�l.
	int getLicznik() {
		return licznik;
	}
	int getMianownik() {
		return mianownik;
	}
	void wyswietlUlamek() {			//Funckja wypisuje u�amek na ekranie w postaci zwyk�ej.
		cout << licznik << "/" << mianownik << endl;
	}
	bool czyRowne(Ulamek ulamek2) {		//Funckja sprawdza czy dwa u�amki s� r�wne, a nast�pnie zwraca warto�� logiczn� tego wyra�enia.
		int nwd1 = NWD(licznik, mianownik); //W tym celu sprawdzamy warto�� najwi�kszego wspolnego dzielnika licznika i mianownika obu u�amk�w.
		int nwd2 = NWD(ulamek2.getLicznik(), ulamek2.getMianownik());	
		//Oba u�amki s� r�wne je�li po skr�ceniu u�amk�w przez swoje NWD ich liczniki oraz mianowniki s� sobie r�wne. Gdy nie s� zwracana jest warto�� logiczna false (0).
		if ((licznik / nwd1 == ulamek2.getLicznik() / nwd2) && (mianownik / nwd1 == ulamek2.getMianownik() / nwd2))
			return true;
		else
			return false;
	}
	int NWD(int a, int b) {			//Funckja NWD zwraca najwi�kszy wsp�lny dzielnik dw�ch liczb ca�kowitych. Funkcja wykorzystuje 
		int reszta;					//algorytm Euklidesa w wersji z dzieleniem, gdzie u�ywana jest reszta z dzielenia. 
		 do{
			reszta = a % b;
			a = b;
			b = reszta;
		}while (reszta != 0);
		return a;
	}
	operator double() {				//Operator konwertuj�cy, zwraca warto�� u�amka w postaci dziesi�nej.
		return (double)licznik / (double)mianownik;
	}
private:							//Pola prywatne okre�lone w tre�ci zadania.
	int licznik;
	int mianownik;
};

Ulamek dzielenie(Ulamek* ul1, Ulamek* ul2) {	//Funkcja dzielenie dzieli przez siebie pierwszy u�amek przez drugi. Przyjmuje jako argumenty
	int nowyLicznik = ul1->getLicznik() * ul2->getMianownik();	 //wska�niki do zmiennych aby pracowa� na oryginalnych warto�ciach.
	int nowyMianownik = ul1->getMianownik() * ul2->getLicznik();
	int nwd = ul1->NWD(nowyLicznik, nowyMianownik);		//Wywo�ywana jest funkcja NWD, aby zwr�cony u�amek by� w swojej najprostszej postaci.
	return Ulamek(nowyLicznik / nwd, nowyMianownik / nwd);
}
Ulamek dzielenie(Ulamek* ul1, Ulamek ul2) {		//Przeci��enie funkcji dzielenie pozwalaj�ce by drugi argument m�g� by� liczb� ca�kowit� 
	int nowyLicznik = ul1->getLicznik() * ul2.getMianownik();	//a nast�pnie konwertowany konstruktorem konwertuj�cym jako Ulamek.
	int nowyMianownik = ul1->getMianownik() * ul2.getLicznik();	//Dzialanie jest analogiczne do funkcji przyjmuj�cej dwa wska�niki do klasy Ulamek.
	int nwd = ul1->NWD(nowyLicznik, nowyMianownik);
	return Ulamek(nowyLicznik / nwd, nowyMianownik / nwd);
}

double pierwiastek(double liczba) {			//Funckja przyjmuje liczb� typu double, a nast�pnie zwraca pierwiastek kwadratowy tej liczby
	return sqrt(liczba);					//dzi�ki funkcji sqrt() zawartej w bibliotece cmath.
}


int main() {
	//Zainicjowanie dw�ch zmiennych typu Ulamek i przes�anie im odpowiednich warto�ci.
	Ulamek ulamek1(2, 3), ulamek2(3, 4);	
	//Stworzenie nowego u�amka dzi�ki funkcji dzielenie, w kt�rej przekazujemy adresy pami�ci dw�ch u�amk�w, a nast�pnie wy�wietlenie 
	//jego warto�ci.
	Ulamek ulamekDzielenie = dzielenie(&ulamek1, &ulamek2);
	cout << "Wynik dzielenia ulamka pierwszego przez drugi:" << endl;
	ulamekDzielenie.wyswietlUlamek();
	//Stworzenie nowego u�amka poprzez podzielenie u�amka przez liczb� ca�kowit�. Do funkcji przekazujemy adres pami�ci pierwszego u�amka
	//oraz liczb� ca�kowit�, aby otrzyma� nowy u�amek. Nast�pnie wy�wietlana jest jego warto��.
	Ulamek ulamekDzielenie2 = dzielenie(&ulamek1, 5);
	cout << "Wynik dzielenia ulamka pierwszego przez liczbe calkowita 5:" << endl;
	ulamekDzielenie2.wyswietlUlamek();
	//U�ycie funkcji pierwiastek oraz wypisanie jego wyniku na ekranie.
	cout << "Wynik uzycia funkcji pierwiastek na ulamku pierwszym:" << endl;
	cout << pierwiastek(ulamek1) << endl;
	//Utworzenie dw�ch pierwiastk�w, a nast�pnie sprawdzenie czy s� sobie one r�wne funckj� czyRowne(Ulamek*), wywo�anej na pierwszym u�amku.
	//Wynik jest wypisywany w postaci warto�ci logicznej - 1 (prawda), 0 (fa�sz).
	Ulamek ulamek_a(5, 10), ulamek_b(15, 30);
	cout << "Sprawdzenie rownosci ulamkow a i b oraz wypisanie logicznej wartosci tego dzialania:" << endl;
	cout << ulamek_a.czyRowne(ulamek_b)<<endl;
	return 0; 
}