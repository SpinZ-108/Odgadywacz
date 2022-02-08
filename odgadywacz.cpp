/* Plik odgadywacz.cpp - Eryk Mika ITE PWr Walbrzych */

#include "odgadywacz.h"


void ZainicujTablice(unsigned int tab [])
{
    for(unsigned int i=0; i<10; i++)
    {
        tab[i]=0;
    }
}


string SameCyfry(const unsigned short int & cyfra, unsigned int &n)
{
    string odgadniecie = "";

    for (unsigned int i=0; i<n; i++)
    {
        odgadniecie += to_string(cyfra); //Powstaje string skladajacy sie z cyfr jednego rodzaju
    }

    return odgadniecie;
}


unsigned int NaSwoich()
{
    int ns;
    cout<<"Podaj, ile cyfr jest na swoich miejscach: ";
    cin>>ns;

    while(cin.fail()||ns>INT_MAX) // Unikam podania przez uzytkownika nieprawidlowego n (<0 lub nie liczba)
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Podano nieprawidlowa wartosc! Sprobuj ponownie: ";
        cin>>ns;
    }

    return ns;
}

unsigned int NieNaSwoich()
{
    int nns;
    cout<<"Podaj, ile cyfr nie jest na swoich miejscach (ale wystepuje w szyfrze): ";
    cin>>nns;

    while(cin.fail()||nns>INT_MAX) // Unikam podania przez uzytkownika nieprawidlowego n (<0 lub nie liczba)
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Podano nieprawidlowa wartosc! Sprobuj ponownie: ";
        cin>>nns;
    }

    return nns;
}


bool CzyWykonalne(const unsigned int &ns, const unsigned int &nns, const unsigned int & n, const unsigned int &sum)
{
    if (((ns>n||nns>n)||((ns+nns)>n))||(sum>n)) return false;
    return true;
}


unsigned int ZsumujIloscCyfr(const unsigned int tab[])
{
    unsigned int suma = 0;

    for(unsigned int i=0; i<=9; i++)
    {
        suma+=tab[i];
    }

    return suma;
}


string StworzLancuch(const unsigned int tab[], const unsigned int &docyfry)
{
    string podstawa = "";

    for(unsigned int i=0; i<=docyfry; i++)
    {
        for(unsigned int j=1; j<=tab[i]; j++)
        {
            podstawa += to_string(i);
        }
    }

    return podstawa;

}

string LosowySzyfr(const string &lancuch)
{
    string losowy = lancuch;

    random_shuffle(losowy.begin(), losowy.end());

    return losowy;

}


unsigned int Silnia(const unsigned int &n)
{
    unsigned int wynik = 1;

    for (unsigned int i=1; i<=n; i++) wynik*=i;

    return wynik;

}


unsigned int LiczbaMozliwosci(const unsigned int cyfry[], const unsigned int &n)
{

    /*
    W tej funkcji korzystam ze wzoru na liczbe permutacji (mozliwosci szyfrow) bez powtorzen, przy
    zalozeniu, ze mamy powtarzajace sie elementy (cyfry):
    n!/(k0!*k1!*...k9!), gdzie:
    n - liczba cyfr
    k0, k1,.., k9 - liczba poszczegolnych cyfr: k0 - liczba zer, k1 - liczba jedynek, ..., k9- liczba dziewiatek
    */

    unsigned int mianownik = 1;

    for(unsigned int i=0; i<10; i++)
    {
        mianownik*=Silnia(cyfry[i]);
    }

    return (Silnia(n)/mianownik);

}


string BezPowtarzania(const string mozliwosci[], const string &lancuch, const unsigned int &zakres, const vector <string> &zerons)
{

    string unikat;

    int i=0;                           // Zabezpiecznenie if(i>3000) mozna usunac, jezeli zakladamy, ze uzytkownik podaje zawsze prawidlowe wartosci

    do
    {
        i++;
        unikat = LosowySzyfr(lancuch);
        if(i>3000) break;              // Prowizoryczne zabezpiecznie przed zapetleniem sie programu (potrzebne, gdy uzytkownik podaje niemozliwe wartosci)
    }
    while(CzyPowtarza(mozliwosci,unikat,zakres)||CyfraNaTymSamym(unikat,zerons));


    return unikat;
}


bool CzyPowtarza(const string mozliwosci[], const string &unikat, const unsigned int &zakres)
{
    for(unsigned int i=0; i<=zakres; i++)
    {
        if(unikat==mozliwosci[i])
        {
            return true;
        }
    }

    return false;
}


bool CyfraNaTymSamym(const string &sprawdz, const vector <string> &zerons)
{
    string porownaj;

    for (unsigned int i=0; i<zerons.size(); i++)
    {
        porownaj = zerons[i];

        for (unsigned int j = 0; j<sprawdz.length(); j++)
        {
            if (sprawdz[j]==porownaj[j]) return true;
        }
    }

    return false;
}



