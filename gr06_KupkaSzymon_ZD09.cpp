#include <iostream>

using namespace std;

float roundTwoDigits(float l) { //Funkcja przyjmuj�ca warto�� zmiennoprzecinkow�, a na jej podstawie zwraca liczb� zaokr�glon� do dw�ch miejsc po przecinku zgodnie z zasadami zaokr�glania.
	//Pomno�enie liczby przez sto w celu przesuni�cia przecinka o dwa miejsca w prawo, a nast�pnie dodanie warto�ci 0.5 kt�re umo�liwi zaokr�glenie zgodnie z zasadami zookr�glenia. Liczba ta nast�pnie jest konwertowana do warto�ci ca�kowitej, co ucina 
	//cyfry po przecinku.
	int temp = static_cast <int> (l * 100 + 0.5);
	//Nast�pnie warto�� konwertowana jest na liczb� zmiennoprzecinkow� i dzielona przez 100 aby uzyska� dwie cyfry po przecinku. Liczba ta jest zwracana i jest zgodna z zasadami zaokr�glania.
	return (static_cast <float> (temp) / 100);
}

class Slodycze {
public:
	Slodycze(string Nazwa, float Cena, int Ilosc) : nazwa(Nazwa), cena(Cena), ilosc_sztuk(Ilosc){}	//Konstruktor parametryzuj�cy, przypisuje on warto�ci odpowiednim polom prywatnym za pomoc� listy inicjalizacyjnej.
	friend ostream& operator<<(ostream&, Slodycze&); //Deklaracja przyja�ni klasy z przeci��eniem operatora <<.
	float getWartosc() {	//Metoda zwracaj�ca warto�� danego obiektu czyli iloczyn p�l cena i ilosc_sztuk. 
		return cena * ilosc_sztuk;
	}
	string getNazwa() {		//Metoda zwracaj�ca nazw� obiektu na kt�rym jest wykonywana.
		return nazwa;
	}
private:	//Pola prywatne zadeklarowane w tre�ci zadania.
	string nazwa;
	float cena;
	int ilosc_sztuk;
};
class Owoce {
public:
	Owoce(string Nazwa, float Cena, float Masa) : nazwa(Nazwa), cena(Cena), masa(Masa) {}	//Konstruktor parametryzuj�cy, przypisuje on warto�ci odpowiednim polom prywatnym za pomoc� listy inicjalizacyjnej.
	friend ostream& operator<<(ostream&, Owoce&);	//Deklaracja przyja�ni klasy z przeci��eniem operatora <<.
	float getWartosc() {	//Metoda zwracaj�ca warto�� pieni�n� danego obiektu czyli iloczyn p�l cena i masa. 
		return cena * masa;
	}
	string getNazwa() {	//Metoda zwracaj�ca nazw� obiektu na kt�rym jest wykonywana.
		return nazwa;
	}
private:	//Pola prywatne zadeklarowane w tre�ci zadania.
	string nazwa;
	float cena;
	float masa;
};
template <int wielkosc_koszyka, typename Typ>  //Definicja szablonu klasy Koszyk z parametrami typu int oraz odpowiednim typem danych. Parametr typu int okre�la rozmiar utworzonej w klasie tablicy wska�nik�w typu Typ. 
class Koszyk {
public:
	//Konstruktor parametryzuj�cy, przyjmuj�cy nazw� i inicjuje jej warto�� za pomoc� listy inicjalizacyjnej. Konstruktor ten r�wnie� nadaje warto�ci wszystkim elementom tablicy produkt_tab_wsk na nullptr.
	Koszyk(string nazwa) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu. 
			produkt_tab_wsk[i] = nullptr;	//Ustawienie warto�ci ka�dego elementu na nullptr.
	}
	//Konstruktor parametryzuj�cy, przyjmuj�cy nazwe i inicjalizuj�cy jej warto�� za pomoc� listy inicjalizacyjnej oraz przyjmuj�cy tablice obiekt�w typu b�d�cego parametrem szablonu.
	Koszyk(string nazwa, Typ* tab) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu.
			produkt_tab_wsk[i] = &tab[i];	//Przypisanie referencji do i-tego elementu tablicy przes�anej jako parametr i-temu elementowi tablicy wska�nik�w produkt_tab_wsk.
	}
	float wartosc_koszyka() { //Metoda obliczaj�ca ��czn� warto�� wszystkich element�w tablicy produkt_tab_wsk i zwracaj�ca t� ilo��.
		float suma = 0;	//Zmienna pomocnicza przechowuj�ca sum� warto�ci element�w tablicy produkt_tab_wsk.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu.
			if (produkt_tab_wsk[i] != nullptr)	//Je�eli obecny element iteracji nie jest r�wny nullptr to wtedy jest wykonywana na tym obiekcie metoda getWartosc(), kt�ra oblicza warto�� tego obiektu, a nast�pnie jest ona dodawana do sumy.
				suma += (*produkt_tab_wsk[i]).getWartosc();
		}
		return roundTwoDigits(suma);	//U�yta jest funkcja roundTwoDigits() na zmiennej suma, aby uzyskana kwota by�a warto�ci� zaokr�glon� do dw�ch miejsc po przecinku. Wynik tej funkcji jest zwracany. 
	}
	void dodajProdukt(Typ& t) {		//Metoda pozwalaj�ca doda� element do tablicy produkt_tab_wsk.
		bool is_repeated = false;	//Zmienna pomocnicza pozwaj�ca okre�li� czy przes�any argument metody jest ju� zawarty w tablicy produkt_tab_wsk.
		int first_free_index = -1;	//Zmienna pomocnicza przechowuj�ca indeks pierwszego wolnego elementu tablicy produkt_tab_wsk. Jej warto�� jest ustawiona pocz�tkowo na -1, poniewa� �aden element tablicy nie mo�e mie� ujemnego indeksu.
		for (int i = 0; i < wielkosc_koszyka; i++){		//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu.
			if (produkt_tab_wsk[i] != nullptr) {	//Je�eli element tablicy nie jest r�wny nullptr 
				if (produkt_tab_wsk[i] == &t) {		//to wtedy je�li element tablicy jest r�wny referencji na przes�any argument metody to warto�� is_repeated jest zmieniana na true, poniewa� wys�any argument jest ju� elementem tablicy. 
					is_repeated = true;
					break;							//P�tla jest przerywana.
				}
			} else if (first_free_index == -1) //Je�eli element tablicy to nie nullptr oraz warto�� first_free_index jest r�wna -1 co oznacza �e nie znaleziono jeszcze pustego elementu tablicy to 
				first_free_index = i;			//first_free_index przypisywana jest warto�� i.
		}
		if (is_repeated)	//Je�eli is_repeated jest prawdziwe czyli dany element jest ju� w tablicy produkt_tab_wsk to nie jest przypisywany ponownie i zwracany jest odpowiedni komunikat.
			cout << "Dany obiekt byl juz przypisany do tablicy, nie przypisano go ponownie" << endl;
		else if (first_free_index == -1)	//W przeciwnym wypadku je�li first_free_index jest r�wne -1 co oznacza �e nie napotkano pustego elementu tablicy i �e tablica jest pe�na to wypisywany jest odpowiedni komunikat.
			cout << "Tablica obiektow jest pelna, nie przypisano obiektu" << endl;
		else		//Je�li oba poprzednie warunki s� fa�szywe to elementowi tablicy produkt_tab_wsk o indeksie first_free_index przypisywana jest referencja do obiektu przes�anego jako argument metody.
			produkt_tab_wsk[first_free_index] = &t;
	}
	friend ostream& operator<< <wielkosc_koszyka, Typ> (ostream&, Koszyk<wielkosc_koszyka, Typ>&); //Deklaracja przyja�ni szablonu klasy Koszyk z przeci��eniem operatora <<.
private:	//Pola prywatne zadeklarowane w zadaniu. 
	string nazwa_koszyka;
	Typ* produkt_tab_wsk[wielkosc_koszyka];		//Tablica statyczna wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu o rozmiarze wielkosc_koszyka b�d�cego parametrem szablonu. 
};

template <int wielkosc_koszyka>				//Specjalizacja cz�ciowa szablonu klasy Koszyk przyjmuj�ca parametr typu int, gdzie drugim parametrem jest klasa Owoce.
class Koszyk <wielkosc_koszyka, Owoce>{
public:
	//Konstruktor parametryzuj�cy, przyjmuj�cy nazw� i inicjuje jej warto�� za pomoc� listy inicjalizacyjnej. Konstruktor ten r�wnie� nadaje warto�ci wszystkim elementom tablicy produkt_tab_wsk na nullptr.
	Koszyk(string nazwa) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Owoce.
			produkt_tab_wsk[i] = nullptr;	//Przypisanie ka�demu elementowi warto�ci nullptr.
	}
	//Konstruktor parametryzuj�cy, przyjmuj�cy nazwe i inicjalizuj�cy jej warto�� za pomoc� listy inicjalizacyjnej oraz przyjmuj�cy tablice obiekt�w typu Owoce.
	Koszyk(string nazwa, Owoce* tab) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Owoce.
			produkt_tab_wsk[i] = &tab[i];	//Przypisanie kolejnym elementom tablicy produkt_tab_wsk referencji do kolejnych element�w tablicy typu Owoce przes�anej jako parametr.
	}
	float wartosc_koszyka() { //Metoda zwracaj�ca warto�� wszystkich owoc�w z tablicy produkt_tab_wsk.
		float suma = 0;	 //Zmienna pomocnicza do obliczania sumy warto�ci element�w tablicy produkt_tab_wsk.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Owoce.
			if (produkt_tab_wsk[i] != nullptr)	//Je�eli element tablicy nie jest r�wny nullptr to wtedy wykonywana jest na tym obiekcie metoda getWartosc(), kt�ra warto�� cena * masa danego obiektu, a nast�pnie jest ona dodawana do sumy.
				suma += (*produkt_tab_wsk[i]).getWartosc();
		}
		return roundTwoDigits(suma); //U�ycie funkcji roundTwoDigits w celu zaokr�glenia zmiennej suma do dw�ch miejsc po przecinku, a nast�pnie zwr�cenie otrzymanej warto�ci.
	}
	void dodajProdukt(Owoce& o) {	//Metoda pozwalaj�ca doda� element do tablicy wska�nik�w na obiektu typu Owoce produkt_tab_wsk.
		bool is_repeated = false;	//Zmienna pomocnicza pozwaj�ca okre�li� czy przes�any argument metody jest ju� zawarty w tablicy produkt_tab_wsk.
		int first_free_index = -1;	//Zmienna pomocnicza przechowuj�ca indeks pierwszego wolnego elementu tablicy produkt_tab_wsk. Jej warto�� jest ustawiona pocz�tkowo na -1, poniewa� �aden element tablicy nie mo�e mie� ujemnego indeksu.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Owoce.
			if (produkt_tab_wsk[i] != nullptr) {	//Je�eli element tablicy nie jest r�wny nullptr 
				if (produkt_tab_wsk[i] == &o) {		//to wtedy je�li element tablicy jest r�wny referencji na przes�any argument metody to warto�� is_repeated jest zmieniana na true, poniewa� otrzymany argument metody jest ju� elementem tablicy.
					is_repeated = true;
					break;							//Przerwanie p�tli instrukcj� break.
				}
			}
			else if (first_free_index == -1)	//Je�eli element tablicy to nie nullptr oraz warto�� first_free_index jest r�wna -1 co oznacza �e nie znaleziono jeszcze pustego elementu tablicy to first_free_index przypisywana jest warto�� i.
				first_free_index = i;			
		}
		if (is_repeated)	//Je�eli is_repeated jest prawdziwe czyli dany element jest ju� w tablicy produkt_tab_wsk to nie jest przypisywany ponownie i zwracany jest odpowiedni komunikat.
			cout << "Dany obiekt byl juz przypisany do tablicy, nie przypisano go ponownie" << endl;
		else if (first_free_index == -1)	//W przeciwnym wypadku je�li first_free_index jest r�wne -1 co oznacza �e nie napotkano pustego elementu tablicy i �e tablica jest pe�na to wypisywany jest odpowiedni komunikat.
			cout << "Tablica obiektow jest pelna, nie przypisano obiektu" << endl;
		else	//Je�li oba poprzednie warunki s� fa�szywe to elementowi tablicy produkt_tab_wsk o indeksie first_free_index przypisywana jest referencja do obiektu przes�anego jako argument metody.
			produkt_tab_wsk[first_free_index] = &o;
	}
	friend ostream& operator<< <wielkosc_koszyka, Owoce> (ostream&, Koszyk<wielkosc_koszyka, Owoce>&); //Deklaracja przyja�ni specjalizacji szablonu klasy Koszyk z przeci��eniem operatora <<.
private:	//Pola prywatne zadeklarowane w zadaniu. 
	string nazwa_koszyka;
	Owoce* produkt_tab_wsk[wielkosc_koszyka];	//Tablica statyczna wska�nik�w do obiekt�w typu Owoce o rozmiarze wielkosc_koszyka b�d�cego parametrem szablonu. 
};

template <typename Typ>							//Deklaracja szablonu funkcji sortujAlfabetycznie(Typ*, int), kt�ra przyjmuje jako argument tablic� nieznanego typu oraz liczb� jej element�w.  
void sortujAlfabetycznie(Typ* tab, int el) {	//Funkcja sortuje otrzyman� tablic� wed�ug nazwy w porz�dku alfabetycznym rosn�cym.
	//Funkcja b�dzie dzia�a�a na tablicach posiadaj�cych metody getNazwa() zwracaj�cej pole nazwa obiektu czyli klasie Owoce i Slodycze. Funkcja ta r�wnie� wykorzystuje operator przypisania jak i konstruktor kopiuj�cy, kt�re nie zosta�y jawnie zdefiniowane
	//w tych klasach wi�c zostan� one wygenerowane automatycznie. Klasy nie posiadaj� p�l b�d�cych wska�nikami, referencjami, wi�c automatycznie wygenerowane przez kompilator operatory przypisania i konstruktory kopiuj�ce b�d� wystarczaj�ce do prawid�owego
	//dzia�ania funkcji i programu.
	for (int i = el-2; i >= 0; i--){	//Algorytm sortowania przez wstawianie. P�tla wykonuj�ca si� od przedostaniego elementu do pierwszego.
		Typ temp = tab[i];	//Utworzenie zmiennej pomocniczej Typ b�d�cej parametrem szablonu warto�ci przes�anej tablicy od obecnej iteracji. 
		int j = i + 1;		//Utworzenie zmiennej pomocniczej steruj�cej p�tl� while i przypisanie jej warto�ci i+1.
		while (j < el && temp.getNazwa() > tab[j].getNazwa()) { //Dop�ki j jest mniejsze od liczby element�w i pole nazwa zmiennej temp jest alfabetycznie p�niejsze od pola nazwa tab[j] uzyskiwanego za pomoc� metody getNazwa() to
			tab[j - 1] = tab[j];	//Poprzedniemu elementowi tab jest przypisywana warto�� obecnego elementu tab[j].
			j++;	//Zwi�kszenie j o 1.
		}	
		tab[j - 1] = temp;	//Przypisanie tab[j-1] warto�ci temp.
	}
}

ostream& operator<<(ostream& out, Slodycze& s) {	//Definicja operatora zrzutu do strumienia << z klas� Slodycze, kt�ry pozwoli na wy�wielenie wszystkich p�l klasy Slodycze.
	out << s.nazwa << " " << s.cena << " zl. za sztuke, ilosc sztuk: " << s.ilosc_sztuk;
	return out;
}
ostream& operator<<(ostream& out, Owoce& o) {	//Definicja operatora zrzutu do strumienia << z klas� Owoce, kt�ry pozwoli na wy�wielenie wszystkich p�l klasy Owoce.
	out << o.nazwa << " " << o.cena << " zl. za kilogram, masa: " << o.masa << " kg";
	return out;
}

template <int wielkosc_koszyka, typename Typ>						//Definicja przeci��enia operatora << z szablonem klasy Koszyk pozwalaj�ca wy�wietli� jego nazw�, warto�� jak i zawarto�� tablicy produkt_tab_wsk.
ostream& operator<<(ostream& out, Koszyk<wielkosc_koszyka,Typ>& k){
	out << k.nazwa_koszyka << ", " << k.wartosc_koszyka() << " zl." << endl;	//Zrzucenie do strumienia nazwy jak i warto�ci koszyka za pomoc� metody wartosc_koszyka().
	for (int i = 0; i < wielkosc_koszyka; i++){		//P�tla iteruj�ca po wszystkich elementach tablicy wska�nik�w do obiekt�w typu Typ b�d�cego parametrem szablonu.
		if(k.produkt_tab_wsk[i]!=nullptr)	//Je�eli element tablicy produkt_tab_wsk nie jest r�wny nullptr to obiekt na kt�ry wskazuje wska�nik jest wy�wielany za pomoc� odpowiedniego przeci��enia <<.
			out << *k.produkt_tab_wsk[i] << endl;
	}
	return out;	//Zwrot strumienia.
}

int main() {
	//Utworzenie dwuelementowej tablicy slodycze_tab i przypisanie warto�ci wszystkim polom.
	Slodycze slodycze_tab[] = { {"Sledz w sosie slodko-kwasnym", 4.99, 8}, {"Pawelek", 1.65, 2} };
	//Wy�wietlenie warto�ci tablicy slodycze_tab za pomoc� przeci��enia operatora <<.
	cout << "Tablica slodyczy: " << endl;
	cout << slodycze_tab[0] << endl << slodycze_tab[1] << endl;
	cout << endl;
	//Utworzenie trzyelementowej tablicy owoce_tab i przypisanie warto�ci wszystkim polom.
	Owoce owoce_tab[] = { {"Mirabelka", 9.99, 5}, {"Durian", 100, 0.2}, {"Pitaja", 11.99, 3.768} };
	//Wy�wietlenie warto�ci tablicy owoce_tab za pomoc� przeci��enia operatora <<.
	cout << "Tablica owocow:" << endl;
	for (int i = 0; i < 3; i++)	//Wypisanie ka�dego elementu za pomoc� p�tli for i przeci��enia operatora <<.
		cout << owoce_tab[i] << endl;
	cout << endl;
	//Utworzenie obiektu klasy Koszyk o parametrach 2 i Slodycze oraz zainicjowanie jej warto�ci za pomoc� konstruktora parametryzuj�cego przyjmuj�cego nazw� oraz tablic� obiekt�w tego samego typu do przes�any parametr.
	Koszyk <2, Slodycze> k1("Koszyk slodyczy", slodycze_tab);
	//Wy�wietlenie zawarto�ci obiektu k1 za pomoc� przeci��enia operatora <<.
	cout << k1 << endl;
	//Utworzenie obiektu klasy Koszyk o parametrach 3 i Owoce, czyli utworzenie obiektu cz�ciowej specjalizacji szablonu Koszyk oraz nadanie mu nazwy za pomoc� konstruktora parametryzuj�cego.
	Koszyk<3, Owoce> k2 ("Koszyk owocow");
	//Dodanie element�w do tablicy produkt_tab_wsk za pomoc� metody dodajProdukt().
	k2.dodajProdukt(owoce_tab[0]); k2.dodajProdukt(owoce_tab[2]);
	//Wy�wietlenie zawarto�ci obiektu k2 za pomoc� przeci��enia operatora <<.
	cout << k2 << endl;
	//Wywo�anie funkcji sortujAlfabetycznie() na tablicy slodycze_tab.
	sortujAlfabetycznie(slodycze_tab, 2);
	//Wypisanie zawarto�ci tablicy slodycze_tab po sortowaniu za pomoc� przeci��onego operatora <<.
	cout << "Tablica slodyczy po sortowaniu alfabetycznym: " << endl;
	cout << slodycze_tab[0] << endl << slodycze_tab[1] << endl;
	cout << endl;
	//Wywo�anie funkcji sortujAlfabetycznie() na tablicy owoce_tab.
	sortujAlfabetycznie(owoce_tab, 3);
	//Wypisanie zawarto�ci tablicy owoce_tab po sortowaniu.
	cout << "Tablica owocow po sortowaniu alfabetycznym:" << endl;
	for (int i = 0; i < 3; i++)	//Wypisanie zawarto�ci tablicy za pomoc� p�tli for i przeci��eniu operatora <<.
		cout << owoce_tab[i] << endl;
	//Przez czas trwania programu nie zosta�y utworzone �adne dynamiczne obiekty, dlatego nie jest potrzebna dodatkowa dealokacja pami�ci.
	return 0;
}


