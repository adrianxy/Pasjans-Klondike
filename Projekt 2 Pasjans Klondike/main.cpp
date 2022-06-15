#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

struct karta{
    int wartosc;
    int kolor;
    bool odslonieta;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tasowanie_i_rozdawanie_kart(vector<karta> kolumna[], queue<karta> &stos){
    karta* tab_tym_kart = new karta[52], tym_karta_do_tasowania;
    int k=0, id;

    srand(time(NULL));

    for(int i=0; i<13; i++){                // tworzenie kart
        for(int j=0; j<4; j++){             //
            tab_tym_kart[k].wartosc = i;    //
            tab_tym_kart[k].kolor = j;      //
            tab_tym_kart[k].odslonieta = 0;
            k++;
        }
    }
    for(int i=0; i<30; i++){                         // tasowanie kart
        id = rand()%52;                              // 30 razy losuje jedna karte
        tym_karta_do_tasowania = tab_tym_kart[id];   // i zamieniam ja z karta z
        tab_tym_kart[id] = tab_tym_kart[i];          // przedzialu 0-30
        tab_tym_kart[i] = tym_karta_do_tasowania;    //
    }
    k=0;
    for(int i=0; i<7; i++){                             // rozdawanie kart na poszczegolne kolumny
        for(int j=0; j<=i; j++){                        //
            kolumna[i].push_back(tab_tym_kart[k++]);    //
        }
    }
    for(int i=0; i<24; i++){                        //reszta kart idzie na stos
        stos.push(tab_tym_kart[k++]);               //
        stos.back().odslonieta = 1;                 // ustawia karty na stosie jako odsloniete
    }
    delete[] tab_tym_kart;
    tab_tym_kart = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void konwetrowanie_koloru_int_na_tekst(int kolor){       //zamiana inta na tekst (kolor)
    if(kolor==0)      cout << "p";  //pik
    else if(kolor==1) cout << "t";  //trefl
    else if(kolor==2) cout << "s";  //serce
    else              cout << "k";  //karo
}

void konwetrowanie_wartosci_int_na_tekst(int wartosc){     //zamiana inta na tekst (wartosc)
    if(wartosc==0)       cout << setw(2) << "A";           // as
    else if(wartosc<10)  cout << setw(2) << wartosc+1;     // 2-10
    else if(wartosc==10) cout << setw(2) << "W";           // walet
    else if(wartosc==11) cout << setw(2) << "D";           // dama
    else                 cout << setw(2) << "K";           // krol
}

int konwetrowanie_wartosci_tekst_na_int(string a){      // zamiana tekstu wprowadzanej karty na
    if(a=="a") return 0;                                // int (wartosc)
    else if(a=="2") return 1;
    else if(a=="3") return 2;
    else if(a=="4") return 3;
    else if(a=="5") return 4;
    else if(a=="6") return 5;
    else if(a=="7") return 6;
    else if(a=="8") return 7;
    else if(a=="9") return 8;
    else if(a=="10") return 9;
    else if(a=="w") return 10;
    else if(a=="d") return 11;
    else if(a=="k") return 12;
}

int konwetrowanie_koloru_tekst_na_int(string a){        // zamiana tekstu wprowadzonej karty na
    if(a=="p") return 0;                                // int (kolor)
    else if(a=="t") return 1;
    else if(a=="s") return 2;
    else if(a=="k") return 3;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rysuj_stos(queue<karta> stos){                                 // rysuje stos
    if (!stos.empty()) {                                            //
        konwetrowanie_wartosci_int_na_tekst(stos.front().wartosc);  //
        konwetrowanie_koloru_int_na_tekst(stos.front().kolor);      //
    }                                                               //
    else cout << "   ";                                             //
}

void rysuj_cztery_kupki(vector<karta> kupka){                       // rysuje cztery kupki
    if (!kupka.empty()) {                                           //
        konwetrowanie_wartosci_int_na_tekst(kupka.back().wartosc);  //
        konwetrowanie_koloru_int_na_tekst(kupka.back().kolor);      //
    }                                                               //
    else cout << "   ";                                             //
}


void rysuj_karte_dla_vector(vector<karta> kolumna[], int nr_kol, int poziom){   // rysuje karte dla vectora jesli jest odsloniety,
    if(kolumna[nr_kol][poziom].odslonieta == 1){                                // a jesli jest zaktyra to rysuje "==="
        konwetrowanie_wartosci_int_na_tekst(kolumna[nr_kol][poziom].wartosc);   //
        konwetrowanie_koloru_int_na_tekst(kolumna[nr_kol][poziom].kolor);       //
    }                                                                           //
    else cout << "===";                                                         //
}

void rysuj_kolumny(vector<karta> kolumna[]){         //rysowanie kolumn
    int najdluzsza_kolumna = kolumna[0].size();                                                                 // wyznaczanie najdluzszej
    for(int i=1; i<7; i++){                                                                                     // kolumny sposrod (0-6)
        najdluzsza_kolumna = (najdluzsza_kolumna > kolumna[i].size()) ? najdluzsza_kolumna : kolumna[i].size(); //
    }                                                                                                           //

    for(int i=0; i<7; i++){                                 // odslanianie ostatniej
        kolumna[i][kolumna[i].size()-1].odslonieta=1;       // karty w kazdej kolumnie
    }                                                       //

    for(int poziom=0; poziom<najdluzsza_kolumna; poziom++){     // ostateczne rysowanie kolumn
        cout << endl;                                           // na podstawie dlugosci kolumn
        for(int n=0; n<7; n++){                                 //
            if(kolumna[n].size()>poziom){                       // gdy kolumna ma wieksza dlugosc
                cout << "|";                                    // od obecnego poziomu to rysuje
                rysuj_karte_dla_vector(kolumna, n, poziom);     // karte na tym poziomie
            }                                                   //
            else cout << "|   ";                                // gdy <= to wstawia czyste pole
        }                                                       //
        cout << "|";                                            //
    }
}

void rysowanie_planszy(vector<karta> kolumna[], queue<karta> stos, vector<karta> cztery_kupki[]){   // rysowanie planszy
    system("cls");                                                                                  // czyszczenie konsoli
    cout << "-----------------------------" << endl;                                                //
    cout << "|"; rysuj_stos(stos); cout << "|       |";                                             // rysowanie stosu
    for(int i=0; i<4; i++){                                                                         //
        rysuj_cztery_kupki(cztery_kupki[i]);                                                        // rysowanie 4 kupek
        cout << "|";                                                                                //
    }                                                                                               //
    cout << endl << "-----------------------------" << endl;                                        //
    rysuj_kolumny(kolumna);                                                                         // rysowanie wszystkich kolumn (0-6)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool szukanie_karty_na_poczatku_stosu(int wart, int kol, queue<karta> stos){                 // sprawdzanie czy karta o danych wartosciach
    if(!stos.empty() && stos.front().kolor==kol && stos.front().wartosc==wart) return 1;     // jest pierwsza na stosie, jak tak to zwraca 1
    else return 0;                                                                           // jesli nie to zwraca 0
}

bool szukanie_karty_na_7_kolumnach(int wart, int kol, vector<karta> kolumna[], int &a, int &c){                     // sprawdzanie czy karta o danych wartosciach
    for(int i=0; i<7; i++){                                                                                         // jest gdzies posrod 7 kolumn oraz jest widoczna
        if(!kolumna[i].empty()){                                                                                    //
            for(int j=0; j<kolumna[i].size(); j++){                                                                 // jesli jest gdzies tam to zwraca 1
                if(kolumna[i][j].kolor==kol && kolumna[i][j].wartosc==wart && kolumna[i][j].odslonieta==1){         //
                    a=i;                                                                                            //
                    c=j;                                                                                            // zwraca jej kolumne
                    return 1;                                                                                       // i indeks w kolumnie
                }                                                                                                   //
            }                                                                                                       //
        }                                                                                                           //
    }                                                                                                               //
    return 0;                                                                                                       // jesli nie to zwraca 0
}

bool szukanie_karty_na_koncu_vectora(int wart, int kol, vector<karta> kolumna[], int &b, int il_kol){               // sprawdzanie czy karta o danych wartosciach
    for(int i=0; i<il_kol; i++){                                                                                    // jest gdzies na koncu jednej z 7 kolumn
        if(!kolumna[i].empty()){                                                                                    //
            int j=kolumna[i].size()-1;                                                                              //
            if(kolumna[i][j].kolor==kol && kolumna[i][j].wartosc==wart && kolumna[i][j].odslonieta==1){             //
                b=i; cout << "b: " << b;                                                                            // zwraca jej kolumne
                return 1;                                                                                           // jesli tak to zwraca 1
            }                                                                                                       //
        }                                                                                                           //
    }
    return 0;
}

void kladzenie_kart_z_kolumny_na_kolumne(vector<karta> kolumna[], int a, int b, int c, vector<karta>::iterator it){//
    while(kolumna[a].size()-1>=c && kolumna[a].size()>0){                                       // przekladam element o indeksie 'c'
        kolumna[b].push_back(kolumna[a][c]);                                                    // i kazdy po nim
        it = kolumna[a].begin()+c;                                                              // z kolumny o indeksie 'a' na kolumne 'b'
        kolumna[a].erase(it);                                                                   //
    }                                                                                           //
}

void kladzenie_karty_ze_stosu_na_kolumne(queue<karta> &stos, vector<karta> kolumna[], int b){       //przekladanie pierwszej karty
    kolumna[b].push_back(stos.front());                                                             //
    stos.pop();                                                                                     //
}

void klade_na_7_kolumn(int wart[], int kol[], vector<karta> kolumna[], queue<karta> &stos, vector<karta>::iterator it){
    int a, b, c;
    if(wart[1]==wart[0]+1 && (wart[1]<13 && wart[1]>=0) && (((kol[0]<=1 && kol[0]>=0) && (kol[1]>=2 && kol[1]<=3)) || ((kol[0]>=2 && kol[0]<=3) && (kol[1]<=1 && kol[1]>=0)))){
        cout << "przeszedlem przez zerowy warunek";
        if (szukanie_karty_na_koncu_vectora(wart[1], kol[1], kolumna, b, 7)){
            if(szukanie_karty_na_poczatku_stosu(wart[0], kol[0], stos)){
                kladzenie_karty_ze_stosu_na_kolumne(stos, kolumna, b);
            }
            else if(szukanie_karty_na_7_kolumnach(wart[0], kol[0],kolumna, a, c)){
                kladzenie_kart_z_kolumny_na_kolumne(kolumna, a, b, c, it);
            }
        }
    }

    else cout << "Blad";
}

void kladzenie_karty_z_kolumny_na_4_kupki(vector<karta> kolumna[], vector<karta> cztery_kupki[], int b, int kolor){ //kladzenie karty z
    cztery_kupki[kolor].push_back(kolumna[b][kolumna[b].size()-1]);                                                 // kolumny 0-6 na
    kolumna[b].erase(kolumna[b].end()-1);                                                                           // 4 kupke
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void akcja_0(vector<karta> kolumna[], queue<karta> &stos, vector<karta>::iterator it){  // akcja kladzenia karty na pusta kolumne
    string w, k;
    int wartosc, kolor, b, a, c;

    cout << "Karta wartosc_kolor(dane oddziel spacja): ";
    cin >> w >> k;
    cout << "numer kolumny (0-6): ";
    do{                         // wprowadzanie numeru kolumny
        cin.clear();            // plus zabezpieczenia
        cin.sync();             //
        cin >> b;               //
    }while(!cin.good());        //
    wartosc = konwetrowanie_wartosci_tekst_na_int(w);               // konwertowanie danych (string) na inty
    kolor = konwetrowanie_koloru_tekst_na_int(k);                   //

    if(kolumna[b].size()==0){                                               // kladzenie karty na wylacznie pusta kolumne
        if(szukanie_karty_na_7_kolumnach(wartosc, kolor,kolumna, a, c)){    //
            kladzenie_kart_z_kolumny_na_kolumne(kolumna, a, b, c, it);      //
        }                                                                   //
        else if(szukanie_karty_na_poczatku_stosu(wartosc, kolor, stos)){    //
            kladzenie_karty_ze_stosu_na_kolumne(stos, kolumna, b);          //
        }                                                                   //
        else cout << "Blad";                                                //
    }
}
void akcja_1(queue<karta> &stos){       // akcja dobierania karty ze stosu
    if(!stos.empty()){                  //
        stos.push(stos.front());        // stara karta idzie na koniec
        stos.pop();                     // nowa idzie na poczatek
    }
}

void akcja_2(vector<karta> kolumna[], queue<karta> &stos, vector<karta> cztery_kupki[]){    // akcja przenoszenia ostatniej karty z
    string w, k;                                                                            // z kolumny na jedna z 4 kupek
    int wartosc, kolor, b, nic;
    cout << "Karta wartosc_kolor(dane oddziel spacja): ";
    cin >> w >> k;
    wartosc = konwetrowanie_wartosci_tekst_na_int(w);               // konwertowanie danych (string) na inty
    kolor = konwetrowanie_koloru_tekst_na_int(k);                   //

    if (szukanie_karty_na_koncu_vectora(wartosc, kolor, kolumna, b, 7)){                // szukanie karty do przelozenia posrod kolumn
        if(szukanie_karty_na_koncu_vectora(wartosc-1, kolor, cztery_kupki, nic, 4)){    // szukanie karty o jeden mniejszej posrod 4 kupek
            kladzenie_karty_z_kolumny_na_4_kupki(kolumna, cztery_kupki, b, kolor);      //
        }                                                                               //
        else if(wartosc==0){                                                            // jesli podaje asa to moge polozyc
            kladzenie_karty_z_kolumny_na_4_kupki(kolumna, cztery_kupki, b, kolor);      //
        }                                                                               //
    }                                                                                   //
    else if(szukanie_karty_na_poczatku_stosu(wartosc, kolor, stos)){                    // szukanie karty do przelozenia na stosie
        if(szukanie_karty_na_koncu_vectora(wartosc-1, kolor, cztery_kupki, nic, 4)){    // szukanie karty o jeden mniejszej posrod 4 kupek
            kladzenie_karty_ze_stosu_na_kolumne(stos, cztery_kupki, kolor);             //
        }                                                                               //
        else if(wartosc==0){                                                            // jesli podaje asa to moge polozyc
             kladzenie_karty_ze_stosu_na_kolumne(stos, cztery_kupki, kolor);            //
        }                                                                               //
    }                                                                                   //
    else cout << "Blad.";                                                               //
}

void akcja_3(vector<karta> kolumna[], queue<karta> &stos, vector<karta>::iterator it){      // akcja kladzenia karty ze sptsu/kolumny
    string w[2], k[2];                                                                      // na kolumne 0-6
    int wartosc[2], kolor[2];

    cout << ">Podaj wartosc i kolor pierwszej karty (dane oddziel spacja): ";
    cin >> w[0] >> k[0];
    cout << ">Podaj wartosc i kolor drugiej karty (dane oddziel spacja): ";
    cin >> w[1] >> k[1];

    for(int i=0; i<2; i++){
        wartosc[i] = konwetrowanie_wartosci_tekst_na_int(w[i]);             // konwertowanie liczby (string) na inta
        kolor[i] = konwetrowanie_koloru_tekst_na_int(k[i]);
    }
    klade_na_7_kolumn(wartosc, kolor, kolumna, stos, it);           //reszta waznych komend
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int akcja;
    vector<karta> kolumna[7];
    vector<karta> cztery_kupki[4];
    queue<karta> stos;
    vector<karta>::iterator it;

    tasowanie_i_rozdawanie_kart(kolumna, stos);

    int wartosc[2], kolor[2];

    do{
        rysowanie_planszy(kolumna, stos,  cztery_kupki);

        cout << endl << endl
             << "0. Poloz karte na poczatek kulumny (0-6)." << endl <<
                "1. Dobierz karte." << endl <<
                "2. Przenies karte na gorne kupki." << endl <<
                "3. Przenies karty na inna kolumne." << endl <<
                "4. Wyjdz." << endl << "Akcja: " ;
        do{
            cin >> akcja;
        }while(akcja>4 || akcja<0);

        switch(akcja){
            case 0: akcja_0(kolumna, stos, it); break;
            case 1: akcja_1(stos); break;
            case 2: akcja_2(kolumna, stos, cztery_kupki); break;
            case 3: akcja_3(kolumna, stos, it); break;
            case 4: ; break;
            default: break;
        }

        //system("pause");
    }while(akcja!=4);

    return 0;
}
