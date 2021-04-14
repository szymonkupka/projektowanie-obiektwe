#include <iostream>

using namespace std;

float roundTwoDigits(float l) { //Funkcja przyjmuj¹ca wartoœæ zmiennoprzecinkow¹, a na jej podstawie zwraca liczbê zaokr¹glon¹ do dwóch miejsc po przecinku zgodnie z zasadami zaokr¹glania.
	//Pomno¿enie liczby przez sto w celu przesuniêcia przecinka o dwa miejsca w prawo, a nastêpnie dodanie wartoœci 0.5 które umo¿liwi zaokr¹glenie zgodnie z zasadami zookr¹glenia. Liczba ta nastêpnie jest konwertowana do wartoœci ca³kowitej, co ucina 
	//cyfry po przecinku.
	int temp = static_cast <int> (l * 100 + 0.5);
	//Nastêpnie wartoœæ konwertowana jest na liczbê zmiennoprzecinkow¹ i dzielona przez 100 aby uzyskaæ dwie cyfry po przecinku. Liczba ta jest zwracana i jest zgodna z zasadami zaokr¹glania.
	return (static_cast <float> (temp) / 100);
}

class Slodycze {
public:
	Slodycze(string Nazwa, float Cena, int Ilosc) : nazwa(Nazwa), cena(Cena), ilosc_sztuk(Ilosc){}	//Konstruktor parametryzuj¹cy, przypisuje on wartoœci odpowiednim polom prywatnym za pomoc¹ listy inicjalizacyjnej.
	friend ostream& operator<<(ostream&, Slodycze&); //Deklaracja przyjaŸni klasy z przeci¹¿eniem operatora <<.
	float getWartosc() {	//Metoda zwracaj¹ca wartoœæ danego obiektu czyli iloczyn pól cena i ilosc_sztuk. 
		return cena * ilosc_sztuk;
	}
	string getNazwa() {		//Metoda zwracaj¹ca nazwê obiektu na którym jest wykonywana.
		return nazwa;
	}
private:	//Pola prywatne zadeklarowane w treœci zadania.
	string nazwa;
	float cena;
	int ilosc_sztuk;
};
class Owoce {
public:
	Owoce(string Nazwa, float Cena, float Masa) : nazwa(Nazwa), cena(Cena), masa(Masa) {}	//Konstruktor parametryzuj¹cy, przypisuje on wartoœci odpowiednim polom prywatnym za pomoc¹ listy inicjalizacyjnej.
	friend ostream& operator<<(ostream&, Owoce&);	//Deklaracja przyjaŸni klasy z przeci¹¿eniem operatora <<.
	float getWartosc() {	//Metoda zwracaj¹ca wartoœæ pieniê¿n¹ danego obiektu czyli iloczyn pól cena i masa. 
		return cena * masa;
	}
	string getNazwa() {	//Metoda zwracaj¹ca nazwê obiektu na którym jest wykonywana.
		return nazwa;
	}
private:	//Pola prywatne zadeklarowane w treœci zadania.
	string nazwa;
	float cena;
	float masa;
};
template <int wielkosc_koszyka, typename Typ>  //Definicja szablonu klasy Koszyk z parametrami typu int oraz odpowiednim typem danych. Parametr typu int okreœla rozmiar utworzonej w klasie tablicy wskaŸników typu Typ. 
class Koszyk {
public:
	//Konstruktor parametryzuj¹cy, przyjmuj¹cy nazwê i inicjuje jej wartoœæ za pomoc¹ listy inicjalizacyjnej. Konstruktor ten równie¿ nadaje wartoœci wszystkim elementom tablicy produkt_tab_wsk na nullptr.
	Koszyk(string nazwa) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu. 
			produkt_tab_wsk[i] = nullptr;	//Ustawienie wartoœci ka¿dego elementu na nullptr.
	}
	//Konstruktor parametryzuj¹cy, przyjmuj¹cy nazwe i inicjalizuj¹cy jej wartoœæ za pomoc¹ listy inicjalizacyjnej oraz przyjmuj¹cy tablice obiektów typu bêd¹cego parametrem szablonu.
	Koszyk(string nazwa, Typ* tab) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu.
			produkt_tab_wsk[i] = &tab[i];	//Przypisanie referencji do i-tego elementu tablicy przes³anej jako parametr i-temu elementowi tablicy wskaŸników produkt_tab_wsk.
	}
	float wartosc_koszyka() { //Metoda obliczaj¹ca ³¹czn¹ wartoœæ wszystkich elementów tablicy produkt_tab_wsk i zwracaj¹ca tê iloœæ.
		float suma = 0;	//Zmienna pomocnicza przechowuj¹ca sumê wartoœci elementów tablicy produkt_tab_wsk.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu.
			if (produkt_tab_wsk[i] != nullptr)	//Je¿eli obecny element iteracji nie jest równy nullptr to wtedy jest wykonywana na tym obiekcie metoda getWartosc(), która oblicza wartoœæ tego obiektu, a nastêpnie jest ona dodawana do sumy.
				suma += (*produkt_tab_wsk[i]).getWartosc();
		}
		return roundTwoDigits(suma);	//U¿yta jest funkcja roundTwoDigits() na zmiennej suma, aby uzyskana kwota by³a wartoœci¹ zaokr¹glon¹ do dwóch miejsc po przecinku. Wynik tej funkcji jest zwracany. 
	}
	void dodajProdukt(Typ& t) {		//Metoda pozwalaj¹ca dodaæ element do tablicy produkt_tab_wsk.
		bool is_repeated = false;	//Zmienna pomocnicza pozwaj¹ca okreœliæ czy przes³any argument metody jest ju¿ zawarty w tablicy produkt_tab_wsk.
		int first_free_index = -1;	//Zmienna pomocnicza przechowuj¹ca indeks pierwszego wolnego elementu tablicy produkt_tab_wsk. Jej wartoœæ jest ustawiona pocz¹tkowo na -1, poniewa¿ ¿aden element tablicy nie mo¿e mieæ ujemnego indeksu.
		for (int i = 0; i < wielkosc_koszyka; i++){		//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu.
			if (produkt_tab_wsk[i] != nullptr) {	//Je¿eli element tablicy nie jest równy nullptr 
				if (produkt_tab_wsk[i] == &t) {		//to wtedy jeœli element tablicy jest równy referencji na przes³any argument metody to wartoœæ is_repeated jest zmieniana na true, poniewa¿ wys³any argument jest ju¿ elementem tablicy. 
					is_repeated = true;
					break;							//Pêtla jest przerywana.
				}
			} else if (first_free_index == -1) //Je¿eli element tablicy to nie nullptr oraz wartoœæ first_free_index jest równa -1 co oznacza ¿e nie znaleziono jeszcze pustego elementu tablicy to 
				first_free_index = i;			//first_free_index przypisywana jest wartoœæ i.
		}
		if (is_repeated)	//Je¿eli is_repeated jest prawdziwe czyli dany element jest ju¿ w tablicy produkt_tab_wsk to nie jest przypisywany ponownie i zwracany jest odpowiedni komunikat.
			cout << "Dany obiekt byl juz przypisany do tablicy, nie przypisano go ponownie" << endl;
		else if (first_free_index == -1)	//W przeciwnym wypadku jeœli first_free_index jest równe -1 co oznacza ¿e nie napotkano pustego elementu tablicy i ¿e tablica jest pe³na to wypisywany jest odpowiedni komunikat.
			cout << "Tablica obiektow jest pelna, nie przypisano obiektu" << endl;
		else		//Jeœli oba poprzednie warunki s¹ fa³szywe to elementowi tablicy produkt_tab_wsk o indeksie first_free_index przypisywana jest referencja do obiektu przes³anego jako argument metody.
			produkt_tab_wsk[first_free_index] = &t;
	}
	friend ostream& operator<< <wielkosc_koszyka, Typ> (ostream&, Koszyk<wielkosc_koszyka, Typ>&); //Deklaracja przyjaŸni szablonu klasy Koszyk z przeci¹¿eniem operatora <<.
private:	//Pola prywatne zadeklarowane w zadaniu. 
	string nazwa_koszyka;
	Typ* produkt_tab_wsk[wielkosc_koszyka];		//Tablica statyczna wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu o rozmiarze wielkosc_koszyka bêd¹cego parametrem szablonu. 
};

template <int wielkosc_koszyka>				//Specjalizacja czêœciowa szablonu klasy Koszyk przyjmuj¹ca parametr typu int, gdzie drugim parametrem jest klasa Owoce.
class Koszyk <wielkosc_koszyka, Owoce>{
public:
	//Konstruktor parametryzuj¹cy, przyjmuj¹cy nazwê i inicjuje jej wartoœæ za pomoc¹ listy inicjalizacyjnej. Konstruktor ten równie¿ nadaje wartoœci wszystkim elementom tablicy produkt_tab_wsk na nullptr.
	Koszyk(string nazwa) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Owoce.
			produkt_tab_wsk[i] = nullptr;	//Przypisanie ka¿demu elementowi wartoœci nullptr.
	}
	//Konstruktor parametryzuj¹cy, przyjmuj¹cy nazwe i inicjalizuj¹cy jej wartoœæ za pomoc¹ listy inicjalizacyjnej oraz przyjmuj¹cy tablice obiektów typu Owoce.
	Koszyk(string nazwa, Owoce* tab) : nazwa_koszyka(nazwa) {
		for (int i = 0; i < wielkosc_koszyka; i++)	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Owoce.
			produkt_tab_wsk[i] = &tab[i];	//Przypisanie kolejnym elementom tablicy produkt_tab_wsk referencji do kolejnych elementów tablicy typu Owoce przes³anej jako parametr.
	}
	float wartosc_koszyka() { //Metoda zwracaj¹ca wartoœæ wszystkich owoców z tablicy produkt_tab_wsk.
		float suma = 0;	 //Zmienna pomocnicza do obliczania sumy wartoœci elementów tablicy produkt_tab_wsk.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Owoce.
			if (produkt_tab_wsk[i] != nullptr)	//Je¿eli element tablicy nie jest równy nullptr to wtedy wykonywana jest na tym obiekcie metoda getWartosc(), która wartoœæ cena * masa danego obiektu, a nastêpnie jest ona dodawana do sumy.
				suma += (*produkt_tab_wsk[i]).getWartosc();
		}
		return roundTwoDigits(suma); //U¿ycie funkcji roundTwoDigits w celu zaokr¹glenia zmiennej suma do dwóch miejsc po przecinku, a nastêpnie zwrócenie otrzymanej wartoœci.
	}
	void dodajProdukt(Owoce& o) {	//Metoda pozwalaj¹ca dodaæ element do tablicy wskaŸników na obiektu typu Owoce produkt_tab_wsk.
		bool is_repeated = false;	//Zmienna pomocnicza pozwaj¹ca okreœliæ czy przes³any argument metody jest ju¿ zawarty w tablicy produkt_tab_wsk.
		int first_free_index = -1;	//Zmienna pomocnicza przechowuj¹ca indeks pierwszego wolnego elementu tablicy produkt_tab_wsk. Jej wartoœæ jest ustawiona pocz¹tkowo na -1, poniewa¿ ¿aden element tablicy nie mo¿e mieæ ujemnego indeksu.
		for (int i = 0; i < wielkosc_koszyka; i++) {	//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Owoce.
			if (produkt_tab_wsk[i] != nullptr) {	//Je¿eli element tablicy nie jest równy nullptr 
				if (produkt_tab_wsk[i] == &o) {		//to wtedy jeœli element tablicy jest równy referencji na przes³any argument metody to wartoœæ is_repeated jest zmieniana na true, poniewa¿ otrzymany argument metody jest ju¿ elementem tablicy.
					is_repeated = true;
					break;							//Przerwanie pêtli instrukcj¹ break.
				}
			}
			else if (first_free_index == -1)	//Je¿eli element tablicy to nie nullptr oraz wartoœæ first_free_index jest równa -1 co oznacza ¿e nie znaleziono jeszcze pustego elementu tablicy to first_free_index przypisywana jest wartoœæ i.
				first_free_index = i;			
		}
		if (is_repeated)	//Je¿eli is_repeated jest prawdziwe czyli dany element jest ju¿ w tablicy produkt_tab_wsk to nie jest przypisywany ponownie i zwracany jest odpowiedni komunikat.
			cout << "Dany obiekt byl juz przypisany do tablicy, nie przypisano go ponownie" << endl;
		else if (first_free_index == -1)	//W przeciwnym wypadku jeœli first_free_index jest równe -1 co oznacza ¿e nie napotkano pustego elementu tablicy i ¿e tablica jest pe³na to wypisywany jest odpowiedni komunikat.
			cout << "Tablica obiektow jest pelna, nie przypisano obiektu" << endl;
		else	//Jeœli oba poprzednie warunki s¹ fa³szywe to elementowi tablicy produkt_tab_wsk o indeksie first_free_index przypisywana jest referencja do obiektu przes³anego jako argument metody.
			produkt_tab_wsk[first_free_index] = &o;
	}
	friend ostream& operator<< <wielkosc_koszyka, Owoce> (ostream&, Koszyk<wielkosc_koszyka, Owoce>&); //Deklaracja przyjaŸni specjalizacji szablonu klasy Koszyk z przeci¹¿eniem operatora <<.
private:	//Pola prywatne zadeklarowane w zadaniu. 
	string nazwa_koszyka;
	Owoce* produkt_tab_wsk[wielkosc_koszyka];	//Tablica statyczna wskaŸników do obiektów typu Owoce o rozmiarze wielkosc_koszyka bêd¹cego parametrem szablonu. 
};

template <typename Typ>							//Deklaracja szablonu funkcji sortujAlfabetycznie(Typ*, int), która przyjmuje jako argument tablicê nieznanego typu oraz liczbê jej elementów.  
void sortujAlfabetycznie(Typ* tab, int el) {	//Funkcja sortuje otrzyman¹ tablicê wed³ug nazwy w porz¹dku alfabetycznym rosn¹cym.
	//Funkcja bêdzie dzia³a³a na tablicach posiadaj¹cych metody getNazwa() zwracaj¹cej pole nazwa obiektu czyli klasie Owoce i Slodycze. Funkcja ta równie¿ wykorzystuje operator przypisania jak i konstruktor kopiuj¹cy, które nie zosta³y jawnie zdefiniowane
	//w tych klasach wiêc zostan¹ one wygenerowane automatycznie. Klasy nie posiadaj¹ pól bêd¹cych wskaŸnikami, referencjami, wiêc automatycznie wygenerowane przez kompilator operatory przypisania i konstruktory kopiuj¹ce bêd¹ wystarczaj¹ce do prawid³owego
	//dzia³ania funkcji i programu.
	for (int i = el-2; i >= 0; i--){	//Algorytm sortowania przez wstawianie. Pêtla wykonuj¹ca siê od przedostaniego elementu do pierwszego.
		Typ temp = tab[i];	//Utworzenie zmiennej pomocniczej Typ bêd¹cej parametrem szablonu wartoœci przes³anej tablicy od obecnej iteracji. 
		int j = i + 1;		//Utworzenie zmiennej pomocniczej steruj¹cej pêtl¹ while i przypisanie jej wartoœci i+1.
		while (j < el && temp.getNazwa() > tab[j].getNazwa()) { //Dopóki j jest mniejsze od liczby elementów i pole nazwa zmiennej temp jest alfabetycznie póŸniejsze od pola nazwa tab[j] uzyskiwanego za pomoc¹ metody getNazwa() to
			tab[j - 1] = tab[j];	//Poprzedniemu elementowi tab jest przypisywana wartoœæ obecnego elementu tab[j].
			j++;	//Zwiêkszenie j o 1.
		}	
		tab[j - 1] = temp;	//Przypisanie tab[j-1] wartoœci temp.
	}
}

ostream& operator<<(ostream& out, Slodycze& s) {	//Definicja operatora zrzutu do strumienia << z klas¹ Slodycze, który pozwoli na wyœwielenie wszystkich pól klasy Slodycze.
	out << s.nazwa << " " << s.cena << " zl. za sztuke, ilosc sztuk: " << s.ilosc_sztuk;
	return out;
}
ostream& operator<<(ostream& out, Owoce& o) {	//Definicja operatora zrzutu do strumienia << z klas¹ Owoce, który pozwoli na wyœwielenie wszystkich pól klasy Owoce.
	out << o.nazwa << " " << o.cena << " zl. za kilogram, masa: " << o.masa << " kg";
	return out;
}

template <int wielkosc_koszyka, typename Typ>						//Definicja przeci¹¿enia operatora << z szablonem klasy Koszyk pozwalaj¹ca wyœwietliæ jego nazwê, wartoœæ jak i zawartoœæ tablicy produkt_tab_wsk.
ostream& operator<<(ostream& out, Koszyk<wielkosc_koszyka,Typ>& k){
	out << k.nazwa_koszyka << ", " << k.wartosc_koszyka() << " zl." << endl;	//Zrzucenie do strumienia nazwy jak i wartoœci koszyka za pomoc¹ metody wartosc_koszyka().
	for (int i = 0; i < wielkosc_koszyka; i++){		//Pêtla iteruj¹ca po wszystkich elementach tablicy wskaŸników do obiektów typu Typ bêd¹cego parametrem szablonu.
		if(k.produkt_tab_wsk[i]!=nullptr)	//Je¿eli element tablicy produkt_tab_wsk nie jest równy nullptr to obiekt na który wskazuje wskaŸnik jest wyœwielany za pomoc¹ odpowiedniego przeci¹¿enia <<.
			out << *k.produkt_tab_wsk[i] << endl;
	}
	return out;	//Zwrot strumienia.
}

int main() {
	//Utworzenie dwuelementowej tablicy slodycze_tab i przypisanie wartoœci wszystkim polom.
	Slodycze slodycze_tab[] = { {"Sledz w sosie slodko-kwasnym", 4.99, 8}, {"Pawelek", 1.65, 2} };
	//Wyœwietlenie wartoœci tablicy slodycze_tab za pomoc¹ przeci¹¿enia operatora <<.
	cout << "Tablica slodyczy: " << endl;
	cout << slodycze_tab[0] << endl << slodycze_tab[1] << endl;
	cout << endl;
	//Utworzenie trzyelementowej tablicy owoce_tab i przypisanie wartoœci wszystkim polom.
	Owoce owoce_tab[] = { {"Mirabelka", 9.99, 5}, {"Durian", 100, 0.2}, {"Pitaja", 11.99, 3.768} };
	//Wyœwietlenie wartoœci tablicy owoce_tab za pomoc¹ przeci¹¿enia operatora <<.
	cout << "Tablica owocow:" << endl;
	for (int i = 0; i < 3; i++)	//Wypisanie ka¿dego elementu za pomoc¹ pêtli for i przeci¹¿enia operatora <<.
		cout << owoce_tab[i] << endl;
	cout << endl;
	//Utworzenie obiektu klasy Koszyk o parametrach 2 i Slodycze oraz zainicjowanie jej wartoœci za pomoc¹ konstruktora parametryzuj¹cego przyjmuj¹cego nazwê oraz tablicê obiektów tego samego typu do przes³any parametr.
	Koszyk <2, Slodycze> k1("Koszyk slodyczy", slodycze_tab);
	//Wyœwietlenie zawartoœci obiektu k1 za pomoc¹ przeci¹¿enia operatora <<.
	cout << k1 << endl;
	//Utworzenie obiektu klasy Koszyk o parametrach 3 i Owoce, czyli utworzenie obiektu czêœciowej specjalizacji szablonu Koszyk oraz nadanie mu nazwy za pomoc¹ konstruktora parametryzuj¹cego.
	Koszyk<3, Owoce> k2 ("Koszyk owocow");
	//Dodanie elementów do tablicy produkt_tab_wsk za pomoc¹ metody dodajProdukt().
	k2.dodajProdukt(owoce_tab[0]); k2.dodajProdukt(owoce_tab[2]);
	//Wyœwietlenie zawartoœci obiektu k2 za pomoc¹ przeci¹¿enia operatora <<.
	cout << k2 << endl;
	//Wywo³anie funkcji sortujAlfabetycznie() na tablicy slodycze_tab.
	sortujAlfabetycznie(slodycze_tab, 2);
	//Wypisanie zawartoœci tablicy slodycze_tab po sortowaniu za pomoc¹ przeci¹¿onego operatora <<.
	cout << "Tablica slodyczy po sortowaniu alfabetycznym: " << endl;
	cout << slodycze_tab[0] << endl << slodycze_tab[1] << endl;
	cout << endl;
	//Wywo³anie funkcji sortujAlfabetycznie() na tablicy owoce_tab.
	sortujAlfabetycznie(owoce_tab, 3);
	//Wypisanie zawartoœci tablicy owoce_tab po sortowaniu.
	cout << "Tablica owocow po sortowaniu alfabetycznym:" << endl;
	for (int i = 0; i < 3; i++)	//Wypisanie zawartoœci tablicy za pomoc¹ pêtli for i przeci¹¿eniu operatora <<.
		cout << owoce_tab[i] << endl;
	//Przez czas trwania programu nie zosta³y utworzone ¿adne dynamiczne obiekty, dlatego nie jest potrzebna dodatkowa dealokacja pamiêci.
	return 0;
}


