/* Plik odgadywacz.h - Eryk Mika ITE PWr Walbrzych */


#ifndef ODGADYWACZ_H_INCLUDED
#define ODGADYWACZ_H_INCLUDED

#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;


void ZainicujTablice(unsigned int []); //Incicuje tablice z ilosciami poszczegolnych cyfr
string SameCyfry(const unsigned short int &, unsigned int&); // Funkcja generuje stringa skladajacego sie z n tych samych cyfr
unsigned int NaSwoich(); // Funkcja umozliwa graczowi podanie, ile cyfr jest na swoich miejsach
unsigned int NieNaSwoich(); // Funkcja umozliwa graczowi podanie, ile cyfr nie jest na swoich miejsach (ale wystepuje w szyfrze)
bool CzyWykonalne(const unsigned int &, const unsigned int &, const unsigned int &n, const unsigned int &); //Funkcja sprawdza, czy dalsze odgadywanie jest mozliwe
unsigned int ZsumujIloscCyfr(const unsigned int []); // Funkcja zwraca sume ilosci poszczegolnych cyfr
string StworzLancuch(const unsigned int [], const unsigned int &); // Funkcja tworzy stringa, z ktorego bedziemy tworzyc losowe szyfry
string LosowySzyfr(const string &lancuch); // Funkcja generuje losowy szyfr z cyfr przekazanych w lancuchu
unsigned int Silnia(const unsigned int &); // Funkcja oblicza silnie (potrzebne do permutacji)
unsigned int LiczbaMozliwosci(const unsigned int [], const unsigned int &); // Funkcja zwraca liczbe ilosci mozliwych szyfrow powstalych z odpowiednych cyfr (bez powtrazania)
string BezPowtarzania(const string[], const string &, const unsigned int &, const vector <string> &); // Funkcja generuje szyfr bez powtarzania
bool CzyPowtarza(const string [], const string &, const unsigned int &); // Funkcja sprawdza, czy szyfr powtorzyl sie juz w przekazanej tablicy
bool CyfraNaTymSamym(const string &, const vector <string> &); // Funkcja sprawdza, czy w szyfrze i vectorze wystepuja takie same cyfry pod odpowiadjacymi sobie indeksami


#endif // ODGADYWACZ_H_INCLUDED
