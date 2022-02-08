/*
 Plik main.cpp - Eryk Mika ITE PWr Walbrzych
 Odgadniecie szyfru 4-cyfrowego: 7361 udalo sie odgadnac w 16 probach, 9651 - 14 prob, 6631 - 10 prob. 4563 - 12 prob, 7531 - 12 prob
 W przypadku podawania przez uzytkownika niemozliwych wartosci program moze wyswietlac np. powtarzajace sie
 szyfry lub niektore mozliwosci nie wyswietla sie. Im wieksze n, tym wieksze prawdopodobienstwo, ze program bedzie
 dzialal niepoprawnie (najlepiej dziala dla n=4).
*/

#include "odgadywacz.h"


int main()
{

    unsigned int ilosciCyfr[10]; // Tablica przechowujaca ilosci cyfr 0,1,..,9 w szyfrze
    vector<string> zerons; // Vector przechowujacy szyfry, w ktorych zero cyfr jest na swoich miejsach (wszystkie nie sa na swoich miejscach)
    unsigned int n; // Dlugosc szyfru wymyslonego przez gracza
    unsigned int ns = 0; // Liczba cyfr, ktore sa na swoich miejsach.
    unsigned int nns = 0; //Liczba cyfr, ktore nie sa na swoich miejscach.
    unsigned int proby = 0; // Liczba prob, ktore potrzebowal program na odgadniecie szyfru
    unsigned int cyfra = 0; // Cyfra, na ktorej skonczylo sie sprawdzanie, ile danych cyfr znajduje sie w szyfrze
    unsigned int razyzero = 0; // Ile razy dokonano wylosowania szyfru z powtorzeniem zero cyfr na swoich miejscach
    bool czyKomplet = false; // True, jezeli znane sa ilosci wszystkich cyfr wystepujacych w szyfrze
    bool jednakowe = false; // Czy szyfr sklada sie z cyfr jednego rodzaju, np. 0000 dla n=4
    bool koniec = false; // Czy program odgadnal szyfr

    string odgadniecie;

    ZainicujTablice(ilosciCyfr);

    cout<<"Witaj w programie! Wymysl szyfr skladajacy sie z n cyfr.\n";
    cout<<"--------------------------------------------------------\n";
    cout<<"Odgadne Twoj szyfr skladajacy sie z n cyfr. Podaj n: ";
    cin>>n;

    while(cin.fail()||n>INT_MAX||n==0) // Unikam podania przez uzytkownika nieprawidlowego n (<= 0 lub nie liczba)
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Podano nieprawidlowe n! Sprobuj ponownie: ";
        cin>>n;
    }

    cout<<"\nRozpoczynam zgadywanie...\n";
    cout<<"--------------------------------------------------------\n";
    cout<<"UWAGA! Podanie niemozliwych wartosci moze spowodowac koniecznosc ich powtornego podania (z korzyscia dla komputera)!\n\n";

    for (unsigned int i=0; i<10; i++)   // Na poczatku sprawdzam szyfry skladajace sie z tych samych cyfr (do momentu wyczerpania mozliwosci)
    {

        proby++; // Nie sa liczone powtorne proby (wynikajace z podania blednych wartosci) - na korzysc komputera

        do
        {
            odgadniecie = SameCyfry(i,n);
            cout<<"Wymyslilem szyfr: "<<odgadniecie<<".\n";
            ns = NaSwoich();
            nns = NieNaSwoich();

            if(ns==n && CzyWykonalne(ns,nns,n,ZsumujIloscCyfr(ilosciCyfr)))
            {
                jednakowe=true;
                koniec=true;
                break;
            }

            ilosciCyfr[i]=ns;

            if((ZsumujIloscCyfr(ilosciCyfr)==n)&&(CzyWykonalne(ns,nns,n,ZsumujIloscCyfr(ilosciCyfr))))
            {
                czyKomplet=true;
                cyfra = i;
                break;
            }

        }
        while(!CzyWykonalne(ns,nns,n,ZsumujIloscCyfr(ilosciCyfr))||nns!=0); // Gdyz w przypadku szyfrow skladajacych sie z tej samej cyfry niemozliwe jest nns!=0

        if (czyKomplet||jednakowe) break;

    }




    if((!jednakowe)&&(ZsumujIloscCyfr(ilosciCyfr)==n))
    {

        // Druga czesc algorytmu - program podaje uzytkownikowi szyfry powstale z wylosowania odpowiednich cyfr w odpowiedniej ilosci



        string lancuch = StworzLancuch(ilosciCyfr,cyfra); // Tworze string skladajacy sie ze wszystkich cyfr, ktore musza wystepowac w danych ilosciach

        string mozliwosci[LiczbaMozliwosci(ilosciCyfr,n)];

        mozliwosci[0] = lancuch;

        unsigned int indeks = 0; // Indeks szyfru z tablicy bedacego odgadnieciem

        for(unsigned int i=0; i<LiczbaMozliwosci(ilosciCyfr,n); i++) //Petla do momentu, jak uda sie programowi odgadnac szyfr lub wyczerpane zostana mozliwosci
        {
            proby++;

            do
            {
                cout<<"Wymyslilem szyfr: "<<mozliwosci[i]<<".\n";
                ns = NaSwoich();
                nns = NieNaSwoich();

                if(ns==n&&CzyWykonalne(ns,nns,n,0))
                {
                    koniec=true;
                    indeks=i;
                    break;
                }

            }
            while(!CzyWykonalne(ns,nns,n,0)||(ns+nns!=n)||(ns==0&&n==4&&razyzero==4)); // Na tym etapie nie jest bowiem mozliwe, aby liczba cyfr na swoich msc. i nie na swoich != n

            if(koniec) break;

            if(((i+1)<LiczbaMozliwosci(ilosciCyfr,n)))
            {
                // Dodatkowa optymalizacja liczby prob dla zgadywania szyfrow (niepowtarzania szyfrow z pozycjami okreslonych cyfr ktore nie pasuja)

                if((n==4)&&(ns==0)) // Gdy na swoich miejsach jest 0 cyfr
                {
                    zerons.push_back(mozliwosci[i]);
                    mozliwosci[i+1]=BezPowtarzania(mozliwosci,lancuch,i,zerons);
                    razyzero++;
                }

                else
                {
                    mozliwosci[i+1]=BezPowtarzania(mozliwosci,lancuch,i,zerons);
                }

            }

        }

        odgadniecie=mozliwosci[indeks]; // Nadal to nie spowoduje wyswietlenia odgadniecia w dalszej czesci progranu, jezeli koniec == false

    }

    if(koniec)
    {
        cout<<"\n--------------------------------------------------------\n";
        cout<<"Udalo mi sie odgadnac Twoj szyfr: "<<odgadniecie<<". Bylo to mozliwe w "<<proby<<" probach.\n";
    }

    else
    {
        cout<<"\n--------------------------------------------------------\n";
        cout<<"Niestety, nie udalo mi sie odgadnac Twojego szyfru. Probowalem "<<proby<<" razy.\n";
    }

    char wyjscie = '1';

    do
    {
        cout<<"Podaj 0 i wcisnij ENTER, aby zakonczyc...\n";
        cin>>wyjscie;
        cin.clear();
        cin.ignore(1000,'\n');
    }
    while(wyjscie!='0');


    return 0;
}
