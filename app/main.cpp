// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "rectangle.hh"
#include "matrix.hh"
#include "../include/lacze_do_gnuplota.hh"

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

#define DL_KROTKI_BOK 100
#define DL_DLUGI_BOK 150

bool ZapisWspolrzednychDoPliku(const char *sNazwaPliku, rectangle Prostokat)
{
       std::ofstream StrmPlikowy;

       StrmPlikowy.open(sNazwaPliku);
       if (!StrmPlikowy.is_open())
       {
              std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
                        << ":(  nie powiodla sie." << std::endl;
              return false;
       }
       StrmPlikowy << Prostokat;
       StrmPlikowy << Prostokat[0];
       StrmPlikowy.close();
       return !StrmPlikowy.fail();
}

int main()
{
       std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
                 << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
                 << "."
                 << PROJECT_VERSION_MINOR /* istotne zmiany */
                 << "."
                 << PROJECT_VERSION_PATCH /* naprawianie bugów */
                 << "."
                 << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
                 << std::endl;

       PzG::LaczeDoGNUPlota Lacze; // Ta zmienna jest potrzebna do wizualizacji
                                   // rysunku prostokata

       //-------------------------------------------------------
       //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
       //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
       //  na dwa sposoby:
       //   1. Rysowane jako linia ciagl o grubosci 2 piksele
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Ciagly, 2);
       //
       //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
       //      których połowa długości boku wynosi 2.
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Punktowy, 2);
       //
       //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
       //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
       //  jako wspolrzedne punktow podajemy tylko x,y.
       //
       Lacze.ZmienTrybRys(PzG::TR_2D);

       char op;
       rectangle re;
       int n;
       double angle;

       Matrix m;
       std::cout << "o - obrot prostokata o zadany kat" << std::endl;
       std::cout << "p - przesuniecie prostokata o zadany wektor" << std::endl;
       std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
       std::cout << "m - wyswietl menu" << std::endl;
       std::cout << "k - koniec dzialania programu" << std::endl;

       if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
              return 1;
       Lacze.Rysuj();
       while (1)
       {

              std::cout << "Twoj wybor? (m - menu) >" << std::endl;
              std::cin >> op;
              switch (op)
              {
              case 'o':
              {
                     std::cout << "Podaj wartosc kata obrotu w stopniach" << std::endl;
                     std::cin >> angle;
                     std::cout << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
                     std::cin >> n;
                     for (int i = 0; i < n; i++)
                     {
                            m.rotation(angle);
                            re = m * re;

                            if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
                                   return 1;
                     }

                     Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
              }
              break;
              case 'p':
              {
                     Vector tmp;
                     std::cout << "Wprowadz wspolrzedne wektora translacji w postaci dwoch liczbtzn. wspolrzednej x oraz wspolrzednej y   " << std::endl;
                     std::cin >> tmp;

                     re = re + tmp;

                     if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
                            return 1;
                     Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
              }
              break;
              case 'w':
              {
                     std::cout << re;
              }
              break;
              case 'm':
              {
                     std::cout << "o - obrot prostokata o zadany kat" << std::endl;
                     std::cout << "p - przesuniecie prostokata o zadany wektor" << std::endl;
                     std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
                     std::cout << "m - wyswietl menu" << std::endl;
                     std::cout << "k - koniec dzialania programu" << std::endl;
              }
              break;
              case 'k':
              {
                     return 0;
              }
              break;
              default:
                     break;
              }
       }

       // Z bazy projektu-wydmuszki Boiler Plate C++:
       // Bring in the dummy class from the example source,
       // just to show that it is accessible from main.cpp.
       Dummy d = Dummy();
       return d.doSomething() ? 0 : -1;
}
