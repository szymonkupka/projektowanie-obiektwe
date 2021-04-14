#include <iostream>
#include <cmath>

using namespace std;

class Ulamek {
public:
	Ulamek() = delete;				//Usuniêcie konstruktora domyœlnego, nie bêdzie potrzebny w tym zadaniu.
	Ulamek(int l) {					//Konstruktor konwertuj¹cy, przyjmuje jako wartoœæ pojedyñcz¹ liczbê ca³kowit¹ i przypisuje jej
		licznik = l;				//wartoœæ licznikowi a mianownikowi 1 przez co wartoœæ u³amka jest równa liczbie ca³kowitej,
		mianownik = 1;
	}			
	Ulamek(int l, int m) {			//Konstruktor parametryzuj¹cy, przypisuje odpowiednie wartoœci licznikowi i mianownikowi, jak równie¿
		licznik = l;				//sprawdza czy nie jest przesy³ana wartoœæ 0 dla mianownika, która nie mo¿e zostaæ przypisana aby 
		if (m != 0) {				//unikn¹æ dzielenia przez 0. W takim przypadku pokazywany jest komunikat oraz przysywana wartoœæ 1 mianownikowi.
			mianownik = m;
		}
		else {
			cout << "Mianownik nie moze byc rowny 0, przypisanie wartosci 1" << endl;
			mianownik = 1;
		}
	}
	//Funkcje get zwracaj¹ wartoœci odpowiednich prywatnych pól.
	int getLicznik() {
		return licznik;
	}
	int getMianownik() {
		return mianownik;
	}
	void wyswietlUlamek() {			//Funckja wypisuje u³amek na ekranie w postaci zwyk³ej.
		cout << licznik << "/" << mianownik << endl;
	}
	bool czyRowne(Ulamek ulamek2) {		//Funckja sprawdza czy dwa u³amki s¹ równe, a nastêpnie zwraca wartoœæ logiczn¹ tego wyra¿enia.
		int nwd1 = NWD(licznik, mianownik); //W tym celu sprawdzamy wartoœæ najwiêkszego wspolnego dzielnika licznika i mianownika obu u³amków.
		int nwd2 = NWD(ulamek2.getLicznik(), ulamek2.getMianownik());	
		//Oba u³amki s¹ równe jeœli po skróceniu u³amków przez swoje NWD ich liczniki oraz mianowniki s¹ sobie równe. Gdy nie s¹ zwracana jest wartoœæ logiczna false (0).
		if ((licznik / nwd1 == ulamek2.getLicznik() / nwd2) && (mianownik / nwd1 == ulamek2.getMianownik() / nwd2))
			return true;
		else
			return false;
	}
	int NWD(int a, int b) {			//Funckja NWD zwraca najwiêkszy wspólny dzielnik dwóch liczb ca³kowitych. Funkcja wykorzystuje 
		int reszta;					//algorytm Euklidesa w wersji z dzieleniem, gdzie u¿ywana jest reszta z dzielenia. 
		 do{
			reszta = a % b;
			a = b;
			b = reszta;
		}while (reszta != 0);
		return a;
	}
	operator double() {				//Operator konwertuj¹cy, zwraca wartoœæ u³amka w postaci dziesiênej.
		return (double)licznik / (double)mianownik;
	}
private:							//Pola prywatne okreœlone w treœci zadania.
	int licznik;
	int mianownik;
};

Ulamek dzielenie(Ulamek* ul1, Ulamek* ul2) {	//Funkcja dzielenie dzieli przez siebie pierwszy u³amek przez drugi. Przyjmuje jako argumenty
	int nowyLicznik = ul1->getLicznik() * ul2->getMianownik();	 //wskaŸniki do zmiennych aby pracowaæ na oryginalnych wartoœciach.
	int nowyMianownik = ul1->getMianownik() * ul2->getLicznik();
	int nwd = ul1->NWD(nowyLicznik, nowyMianownik);		//Wywo³ywana jest funkcja NWD, aby zwrócony u³amek by³ w swojej najprostszej postaci.
	return Ulamek(nowyLicznik / nwd, nowyMianownik / nwd);
}
Ulamek dzielenie(Ulamek* ul1, Ulamek ul2) {		//Przeci¹¿enie funkcji dzielenie pozwalaj¹ce by drugi argument móg³ byæ liczb¹ ca³kowit¹ 
	int nowyLicznik = ul1->getLicznik() * ul2.getMianownik();	//a nastêpnie konwertowany konstruktorem konwertuj¹cym jako Ulamek.
	int nowyMianownik = ul1->getMianownik() * ul2.getLicznik();	//Dzialanie jest analogiczne do funkcji przyjmuj¹cej dwa wskaŸniki do klasy Ulamek.
	int nwd = ul1->NWD(nowyLicznik, nowyMianownik);
	return Ulamek(nowyLicznik / nwd, nowyMianownik / nwd);
}

double pierwiastek(double liczba) {			//Funckja przyjmuje liczbê typu double, a nastêpnie zwraca pierwiastek kwadratowy tej liczby
	return sqrt(liczba);					//dziêki funkcji sqrt() zawartej w bibliotece cmath.
}


int main() {
	//Zainicjowanie dwóch zmiennych typu Ulamek i przes³anie im odpowiednich wartoœci.
	Ulamek ulamek1(2, 3), ulamek2(3, 4);	
	//Stworzenie nowego u³amka dziêki funkcji dzielenie, w której przekazujemy adresy pamiêci dwóch u³amków, a nastêpnie wyœwietlenie 
	//jego wartoœci.
	Ulamek ulamekDzielenie = dzielenie(&ulamek1, &ulamek2);
	cout << "Wynik dzielenia ulamka pierwszego przez drugi:" << endl;
	ulamekDzielenie.wyswietlUlamek();
	//Stworzenie nowego u³amka poprzez podzielenie u³amka przez liczbê ca³kowit¹. Do funkcji przekazujemy adres pamiêci pierwszego u³amka
	//oraz liczbê ca³kowit¹, aby otrzymaæ nowy u³amek. Nastêpnie wyœwietlana jest jego wartoœæ.
	Ulamek ulamekDzielenie2 = dzielenie(&ulamek1, 5);
	cout << "Wynik dzielenia ulamka pierwszego przez liczbe calkowita 5:" << endl;
	ulamekDzielenie2.wyswietlUlamek();
	//U¿ycie funkcji pierwiastek oraz wypisanie jego wyniku na ekranie.
	cout << "Wynik uzycia funkcji pierwiastek na ulamku pierwszym:" << endl;
	cout << pierwiastek(ulamek1) << endl;
	//Utworzenie dwóch pierwiastków, a nastêpnie sprawdzenie czy s¹ sobie one równe funckj¹ czyRowne(Ulamek*), wywo³anej na pierwszym u³amku.
	//Wynik jest wypisywany w postaci wartoœci logicznej - 1 (prawda), 0 (fa³sz).
	Ulamek ulamek_a(5, 10), ulamek_b(15, 30);
	cout << "Sprawdzenie rownosci ulamkow a i b oraz wypisanie logicznej wartosci tego dzialania:" << endl;
	cout << ulamek_a.czyRowne(ulamek_b)<<endl;
	return 0; 
}